#include "stat_reader.h"

using namespace transport_catalogue::stat;


double StatReader::CalculateRouteLengthCoordinate(const Bus* bus) const {
	double route_length = 0;
	for (size_t i = 1; i != bus->route.size(); ++i) {
		Coordinates from = { bus->route[i - 1]->coordinates };
		Coordinates to = { bus->route[i]->coordinates};
		route_length += ComputeDistance(from, to);
	}

	return route_length;
}

double StatReader::CalculateRouteLength(const TransportCatalogue& transport_catalogue, const Bus* bus) const {
	double route_length = 0;
	for (size_t i = 1; i != bus->route.size(); ++i) {
		route_length += transport_catalogue.GetLengthBetweenStops(bus->route[i - 1], bus->route[i]);
	}
	return route_length;
}

void StatReader::WriteBusInfo(std::ostream& output, const TransportCatalogue& transport_catalogue, const std::string& text) {
	auto bus = transport_catalogue.FindBus(text);
	if (bus == nullptr) {
		output << " not found" << std::endl;
	}
	else {
		double route_length = CalculateRouteLength(transport_catalogue, bus);
		double curvature = route_length/CalculateRouteLengthCoordinate(bus);
		output << " " << bus->route.size() << " stops on route, "
			<< bus->unique_stops.size() << " unique stops, " 
			<< route_length << " route length, "
			<< curvature << " curvature" << std::endl;
	}
}

void StatReader::WriteStopInfo(std::ostream& output, const TransportCatalogue& transport_catalogue, const std::string& text) {
	auto list_buses_for_stop = transport_catalogue.GetBasesForStop(transport_catalogue.FindStop(text));
	if (list_buses_for_stop == nullptr) {
		std::string out = transport_catalogue.FindStop(text) != nullptr ? " no buses" : " not found";
		output << out;
	}
	else {
		output << " buses";
		for (const auto& bus : *list_buses_for_stop) {
			output << " " << bus->bus_name;
		}
	}
	output << std::endl;
}

StatReader::StatReader(std::istream& input, std::ostream& output, TransportCatalogue& transport_catalogue)
{
	//LOG_DURATION("StatReader");
	std::string text;
	std::getline(input, text);
	int count_query = std::stoi(text);
	while (count_query > 0) {
		std::getline(input, text);
		output << text<< ":";
		std::string identificator_ = text.substr(text.find_first_not_of(" "));
		identificator_ = identificator_.substr(0, identificator_.find(" "));

		text = text.substr(text.find_first_not_of(" "));
		text = text.substr(text.find_first_of(" "));
		text = text.substr(text.find_first_not_of(" "));
		if (identificator_ == "Bus") {
			WriteBusInfo(output,  transport_catalogue, text);
		}if (identificator_ == "Stop") {
			WriteStopInfo(output, transport_catalogue, text);
		}
		--count_query;
	}
}
