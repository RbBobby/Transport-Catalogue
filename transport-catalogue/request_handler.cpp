#include "request_handler.h"

double CalculateRouteLengthCoordinate(const Bus& bus){
	double route_length = 0;
	for (size_t i = 1; i != bus.route.size(); ++i) {
		Coordinates from = { bus.route[i - 1]->coordinates };
		Coordinates to = { bus.route[i]->coordinates };
		route_length += ComputeDistance(from, to);
	}

	return route_length;
}

double CalculateRouteLength(const TransportCatalogue& transport_catalogue, const Bus& bus){
	double route_length = 0;
	for (size_t i = 1; i != bus.route.size(); ++i) {
		route_length += transport_catalogue.GetLengthBetweenStops(bus.route[i - 1], bus.route[i]);
	}
	return route_length;
}

double CalculateCurvature(const double route_length, const double route_length_coordinate)
{
	return route_length / route_length_coordinate;
}

RequestHandler::RequestHandler(const TransportCatalogue& db, renderer::MapRenderer& renderer)  :db_(db), renderer_(renderer)
{
}

std::optional<Bus> RequestHandler::GetBusStat(const std::string_view& bus_name) const
{
	auto& buses_ = *db_.GetBases();
	auto it = std::find_if(buses_.begin(), buses_.end(), [&bus_name](const auto& bus) {return bus.bus_name == bus_name; });
	if (it == buses_.end()) {
		return std::nullopt;
	}
	const Bus* bus_ptr = &(*it);
	return *bus_ptr;
}

std::ostream& RequestHandler::RenderMap(std::ostream& os) const
{
	renderer_.SetBusesAndStops(db_.GetBases(), db_.GetStopNames());
	svg::Document doc;
	renderer_.Draw(doc);
	doc.Render(os);

	return os;
}

