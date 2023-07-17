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

	const Bus* TransportCatalogue::FindBus(const std::string& bus_name) const {
		auto it = std::find_if(buses_.begin(), buses_.end(), [&bus_name](const auto& bus) {return bus.bus_name == bus_name; });
		if (it == buses_.end()) {
			return nullptr;
		}
		const Bus* bus_ptr = &(*it);
		return bus_ptr;
	}

	const std::deque<Bus>* TransportCatalogue::GetBases() const {
		return &buses_;
	}

	const std::set<Bus*, BusCompare>* TransportCatalogue::GetBasesForStop(Stop* stop) const {
		if (stop_name_to_bus_ptr_.count(stop)) {
			return &stop_name_to_bus_ptr_.at(stop);
		}
		else {
			return nullptr;
		}
	}

	const double TransportCatalogue::GetLengthBetweenStops(Stop* first_stop, Stop* second_stop) const {

		if (pair_stops_to_length_.count({ first_stop, second_stop })) {
			return pair_stops_to_length_.at({ first_stop, second_stop });
		}
		else {
			return pair_stops_to_length_.at({ second_stop,first_stop });
		}
		
	}

