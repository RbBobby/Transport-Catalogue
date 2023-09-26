#include "transport_catalogue.h"

using namespace transport_catalogue;

void TransportCatalogue::AddBus(const Bus& bus) {

	buses_.push_back(bus);
	for (auto& stop : buses_.back().route) {
		stop_name_to_bus_ptr_[stop].insert(&buses_.back());
	}
}

void TransportCatalogue::AddStop(const Stop& stop) {
	stops_.push_back(stop);
	Stop* stop_ptr = &stops_.back();
	stop_name_to_stop_ptr_[stops_.back().stop_name] = stop_ptr;
}

void transport_catalogue::TransportCatalogue::AddStopNames(Stop* stop)
{
	stop_names_.insert({stop->stop_name, stop});
	}

void TransportCatalogue::AddStopLength(const std::pair<Stop*, Stop*>& pair_stops, double& length) {
	pair_stops_to_length_.insert({ pair_stops, length });
}

Stop* TransportCatalogue::FindStop(std::string_view stop_name) const {
	auto it = std::find_if(stop_name_to_stop_ptr_.begin(), stop_name_to_stop_ptr_.end(), [&stop_name](const auto s) {
		return s.first == stop_name;
		});
	if (it == stop_name_to_stop_ptr_.end()) {
		return nullptr;
	}
	return (*it).second;
}

const std::deque<Bus>* TransportCatalogue::GetBases() const {
	return &buses_;
}

const std::deque<Stop>* transport_catalogue::TransportCatalogue::GetStops() const
{
	return &stops_;
}

const std::set<Bus*, BusCompare>* TransportCatalogue::GetBasesForStop(Stop* stop) const {
	if (stop_name_to_bus_ptr_.count(stop)) {
		return &stop_name_to_bus_ptr_.at(stop);
	}
	else {
		return nullptr;
	}
}

const std::map<std::string, Stop*>* transport_catalogue::TransportCatalogue::GetStopNames() const
{
	return &stop_names_;
}

size_t transport_catalogue::TransportCatalogue::GetStopsCount() const
{
	return stop_name_to_stop_ptr_.size();
}



double TransportCatalogue::GetLengthBetweenStops(Stop* first_stop, Stop* second_stop) const {

	if (pair_stops_to_length_.count({ first_stop, second_stop })) {
		return pair_stops_to_length_.at({ first_stop, second_stop });
	}
	else {
		return pair_stops_to_length_.at({ second_stop,first_stop });
	}

}

