#pragma once
#include <sstream>
 
#include "json_builder.h"
#include "json.h"
#include "map_renderer.h"
#include "request_handler.h"
#include "transport_catalogue.h"
#include "transport_router.h"
#include "serialization.h"

class JsonReader {
public:
	JsonReader(std::istream& input, renderer::MapRenderer&  map_renderer);
	void ProcessRequest();
	RequestHandler GetRequestHandler()const;
	void GetStat(std::ostream& os);
	~JsonReader() = default;

private:	
	void WriteBusInfo(json::Builder& builder, json::Dict& dict_request);
	void WriteStopInfo(json::Builder& builder, json::Dict& dict_request);
	void WriteSVGInfo(json::Builder& builder);
	void WriteRouteInfo(json::Builder& builder, json::Dict& dict_request);
	svg::Color AddCollor(const json::Node& value_setting);

	void AddStops();
	void AddBusses();
	void AddStopsLength();
	void AddStatRequests();
	void AddRenderRettings();
	void AddRoutingSettings();	
	void AddSerializationSettings();	
	void SerializeTC();

private:	
	json::Document input_doc_;
	renderer::MapRenderer& map_renderer_;
	transport_catalogue::TransportCatalogue transport_catalogue_;	

	json::Array response_request_;
	RequestHandler request_handler{ transport_catalogue_, map_renderer_ };
	transport_router::TransportRouter transport_router_;
 
	serialization::Serializer serializer;
};
