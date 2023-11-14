#include "json_reader.h"

/*
 * Здесь можно разместить код наполнения транспортного справочника данными из JSON,
 * а также код обработки запросов к базе и формирование массива ответов в формате JSON
 */
using Dict = json::Dict;
using Array = json::Array;
using Document = json::Document;
using TransportCatalogue = transport_catalogue::TransportCatalogue;

using namespace std::literals;

JsonReader::JsonReader(std::istream& input, renderer::MapRenderer& map_renderer)
	: input_doc_(json::Load(input))
	, map_renderer_(map_renderer)
{
}

void JsonReader::ProcessRequest()
{
	AddStops();	
	AddBusses();
	AddRenderRettings();
	AddRoutingSettings();
	AddSerializationSettings();	
	SerializeTC();
}

RequestHandler JsonReader::GetRequestHandler() const
{
	return  request_handler;
}

void JsonReader::WriteBusInfo(json::Builder& builder, Dict& dict_request)
{	
	auto bus = request_handler.GetBusStat(dict_request.at("name").AsString());
	if (!bus) {
		builder
			.Key("error_message")
			.Value(std::string("not found"));
	}
	else {
	double route_length = CalculateRouteLength(transport_catalogue_, bus.value());

		builder
			.Key("stop_count")
			.Value(static_cast<int>(bus->route.size()))
			.Key("route_length")
			.Value(route_length)
			.Key("unique_stop_count")
			.Value(static_cast<int>(bus->unique_stops.size()))
			.Key("curvature")
			.Value(CalculateCurvature(route_length, CalculateRouteLengthCoordinate(bus.value())));	
	}
}

void JsonReader::WriteStopInfo(json::Builder& builder, Dict& dict_request)
{
	auto list_buses_for_stop = transport_catalogue_.GetBasesForStop(transport_catalogue_.FindStop(dict_request.at("name").AsString()));

	if (!transport_catalogue_.FindStop(dict_request.at("name").AsString())) {
		builder
			.Key("error_message")
			.Value(std::string("not found"));
	}
	else if (!list_buses_for_stop) {
		builder
			.Key("buses")
			.Value(Array{}); 
	}
	else {
		Array buses{};
		for (const auto& bus : *list_buses_for_stop) {
			buses.emplace_back(bus->bus_name);
		}
		builder
			.Key("buses")
			.Value(buses);
	}
}

void JsonReader::WriteSVGInfo(json::Builder& builder)
{	
	std::ostringstream svg_doc;	
	request_handler.RenderMap(svg_doc);
	std::string str = svg_doc.str();
		
	builder
		.Key("map")
		.Value(str);
}

void JsonReader::WriteRouteInfo(json::Builder& builder, json::Dict& dict_request)
{
	auto route_build = transport_router_.BuildRoute(transport_catalogue_,
		dict_request.at("from"s).AsString(),
		dict_request.at("to"s).AsString());
	if (route_build) {
		builder.Key("total_time"s).Value(route_build.value().first);
		builder.Key("items"s).StartArray();
		for (const auto& item : route_build.value().second) {
			builder.StartDict();
			if (item.type == transport_router::RouteSegmentType::Wait) {
				builder.Key("stop_name"s).Value(item.stop_name);
				builder.Key("time"s).Value(item.time);
				builder.Key("type"s).Value("Wait"s);
			}
			else {
				builder.Key("bus"s).Value(item.bus);
				builder.Key("span_count"s).Value(item.span_count);
				builder.Key("time"s).Value(item.time);
				builder.Key("type"s).Value("Bus"s);
			}
			builder.EndDict();
		}
		builder.EndArray();
	}
	else {
		builder.Key("error_message"s).Value("not found"s);
	}
}

void JsonReader::AddStops()
{
	auto& base_requests = input_doc_.GetRoot().AsDict().at("base_requests");	
	for (const auto& base_request : base_requests.AsArray()) {
		auto& query = base_request.AsDict();
		if (query.at("type").AsString() == "Stop") {
			Stop stop;
			stop.stop_name = query.at("name").AsString();
			stop.coordinates = { query.at("latitude").AsDouble(), query.at("longitude").AsDouble() };
			transport_catalogue_.AddStop(stop);
		}
	}
	AddStopsLength();
}

void JsonReader::AddStopsLength()
{
	auto& base_requests = input_doc_.GetRoot().AsDict().at("base_requests");
	for (const auto& base_request : base_requests.AsArray()) {
		if (base_request.AsDict().at("type").AsString() == "Stop") {
			std::string stop_name_1 = base_request.AsDict().at("name").AsString();
			for (const auto& [stop_name_2, lenght] : base_request.AsDict().at("road_distances").AsDict()) {
				double lenght_between = lenght.AsDouble();
				transport_catalogue_.AddStopLength({ transport_catalogue_.FindStop(stop_name_1), transport_catalogue_.FindStop(stop_name_2) }, lenght_between);
			}
		}
	}
}

void JsonReader::AddBusses()
{
	auto& base_requests = input_doc_.GetRoot().AsDict().at("base_requests");
	for (const auto& base_request : base_requests.AsArray()) {
		if (base_request.AsDict().at("type").AsString() == "Bus") {
			Bus bus;
			bus.bus_name = base_request.AsDict().at("name").AsString();
			if (base_request.AsDict().count("stops")) {
				for (const auto& stop : base_request.AsDict().at("stops").AsArray()) {
					Stop* finding_stop = transport_catalogue_.FindStop(stop.AsString());
					transport_catalogue_.AddStopNames(finding_stop);
					bus.route.push_back(finding_stop);
					bus.unique_stops.insert(finding_stop);
				}			
			}
			bus.is_roundtrip = base_request.AsDict().at("is_roundtrip").AsBool();
			if (!bus.is_roundtrip && !bus.route.empty()) {
				auto route_buf = bus.route;
				auto it = ++route_buf.rbegin();
				for (; it != route_buf.rend(); ++it) {
					bus.route.push_back(std::move(*it));
				}
			}		
			transport_catalogue_.AddBus(bus);
		}
	}
}

void JsonReader::AddRenderRettings()
{
	auto& render_settings = input_doc_.GetRoot().AsDict().at("render_settings");
	renderer::MapSetting map_setting;
	for (const auto& [name_setting, value_setting] : render_settings.AsDict()) {
		if (name_setting == "width") {
			map_setting.width = value_setting.AsDouble();
		}
		else if (name_setting == "height") {
			map_setting.height = value_setting.AsDouble();
		}
		else if (name_setting == "padding") {
			map_setting.padding = value_setting.AsDouble();
		}
		else if (name_setting == "stop_radius") {
			map_setting.stop_radius = value_setting.AsDouble();
		}
		else if (name_setting == "line_width") {
			map_setting.line_width = value_setting.AsDouble();
		}
		else if (name_setting == "bus_label_font_size") {
			map_setting.bus_label_font_size = value_setting.AsDouble();
		}
		else if (name_setting == "bus_label_offset") {
			map_setting.bus_label_offset = { value_setting.AsArray().at(0).AsDouble(), value_setting.AsArray().at(1).AsDouble() };
		}
		else if (name_setting == "stop_label_font_size") {
			map_setting.stop_label_font_size = value_setting.AsDouble();
		}
		else if (name_setting == "stop_label_offset") {
			map_setting.stop_label_offset = { value_setting.AsArray().at(0).AsDouble(), value_setting.AsArray().at(1).AsDouble() };
		}
		else if (name_setting == "underlayer_color") {								
			map_setting.underlayer_color = AddCollor(value_setting);			
		}
		else if (name_setting == "underlayer_width") {
			map_setting.underlayer_width = value_setting.AsDouble();			
		}
		else if (name_setting == "color_palette") {
			for (const auto& color : value_setting.AsArray())
				map_setting.color_palette.emplace_back(AddCollor(color));
		}
	}
	map_renderer_.SetSetting(map_setting);	
}

void JsonReader::AddRoutingSettings()
{
	auto& routing_settings = input_doc_.GetRoot().AsDict().at("routing_settings");
	const double KPH_TO_MPM = 1000.0 / 60.0;
	int wait = routing_settings.AsDict().at("bus_wait_time").AsInt();
	double velocity = routing_settings.AsDict().at("bus_velocity").AsDouble() * KPH_TO_MPM;
	RoutingSettings routing_setting = { wait, velocity };
	transport_router_.SetRoutingSetting(routing_setting);
}

void JsonReader::AddSerializationSettings()
{ 
	SerializerSettings serializer_settings = {input_doc_.GetRoot().AsDict().at("serialization_settings").AsDict().at("file").AsString()};
	serializer.SetSettings(serializer_settings);
}

svg::Color JsonReader::AddCollor(const json::Node& value_setting) {
	//строковый тип Color
	if (value_setting.IsString()) {
		return value_setting.AsString();
	}//тип RGB
	else if (value_setting.IsArray() && value_setting.AsArray().size() == 3) {
		return svg::Rgb(
			value_setting.AsArray().at(0).AsInt(),
			value_setting.AsArray().at(1).AsInt(),
			value_setting.AsArray().at(2).AsInt()
		);
	}//тип RGBA
	else if (value_setting.IsArray() && value_setting.AsArray().size() == 4) {
		return svg::Rgba(
			value_setting.AsArray().at(0).AsInt(),
			value_setting.AsArray().at(1).AsInt(),
			value_setting.AsArray().at(2).AsInt(),
			value_setting.AsArray().at(3).AsDouble()
		);
	}
	return nullptr;
}

void JsonReader::AddStatRequests()
{	
	auto& stat_requests = input_doc_.GetRoot().AsDict().at("stat_requests");
	
	for (const auto& stat_request : stat_requests.AsArray()) {
		Dict dict_request = stat_request.AsDict();//формируем ответ в этот словарь
		//Dict response{};
		json::Builder builder;
		json::Node id = dict_request.at("id");
		builder
			.StartDict()
			.Key("request_id")
			.Value(std::move(id.GetValueNotConst()));
		if (dict_request.at("type").AsString() == "Bus") {
			WriteBusInfo(builder, dict_request);
		}
		if (dict_request.at("type").AsString() == "Stop") {
			WriteStopInfo(builder, dict_request);
		}
		if (dict_request.at("type").AsString() == "Map") {
			WriteSVGInfo(builder);
		}
		if (dict_request.at("type").AsString() == "Route") {
			WriteRouteInfo(builder, dict_request);
		}
		builder.EndDict();
		response_request_.emplace_back(builder.Build().AsDict());
	}	
}

void JsonReader::SerializeTC(){		
		serializer.Serialize(transport_catalogue_, map_renderer_.GetSetting(), transport_router_.GetRoutingSettings(), transport_router_);
}

void JsonReader::GetStat(std::ostream& os) {
	AddSerializationSettings();	
	serializer.Deserialize(transport_catalogue_, map_renderer_, transport_router_);
	AddStatRequests();
	json::Print(Document{ response_request_ }, os);
}

