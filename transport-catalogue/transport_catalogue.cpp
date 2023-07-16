#include "transport_catalogue.h"

using namespace transport_catalogue;

	void TransportCatalogue::AddStop(Stop& stop) {
		stops_.push_back(std::move(stop));
		Stop* stop_ptr = &stops_.back();
		std::string* stop_view = &stops_.back().stop_name;
		stop_name_to_stop_ptr_[stop_view] = stop_ptr;
	}

	void TransportCatalogue::AddStopLength(std::string* first_stop, std::string* second_stop, double& length) {
		pair_stops_to_length_.insert({ std::pair(first_stop, second_stop), length });
	}

	void TransportCatalogue::AddBus(Bus& bus) {
		for (auto& stop : bus.route) {
			bus.unique_stops.insert(std::move(stop));
		}
		buses_.push_back(std::move(bus));
		for (auto& stop : buses_.back().route) {
			stop_name_to_bus_ptr_[stop->stop_name].insert(buses_.back().bus_name);
		}
	}

	Stop* TransportCatalogue::FindStop(std::string_view stop_name) const {
		auto it = std::find_if(stop_name_to_stop_ptr_.begin(), stop_name_to_stop_ptr_.end(), [&stop_name](const auto s) {
			return *(s.first) == stop_name;
			});
		if (it == stop_name_to_stop_ptr_.end()) {
			return nullptr;
		}
		return (*it).second;
	}

	const Bus* TransportCatalogue::FindBus(std::string& bus_name) const {
		auto it = std::find_if(buses_.begin(), buses_.end(), [&bus_name](const auto& bus) {return bus.bus_name == bus_name; });
		if (it == buses_.end()) {
			return nullptr;
		}
		const Bus* bus_ptr = &(*it);
		return bus_ptr;
	}

	const std::deque<Bus>* TransportCatalogue::GetBasses() const {
		return &buses_;
	}

	const std::set<std::string_view>* TransportCatalogue::GetBassesForStop(std::string_view stop_name) {
		if (stop_name_to_bus_ptr_.count(stop_name)) {
			return &stop_name_to_bus_ptr_.at(stop_name);
		}
		else {
			return nullptr;
		}
	}

	const double* TransportCatalogue::GetLengthBetweenStops(Stop* first_stop, Stop* second_stop) const {

		if (pair_stops_to_length_.count({ &first_stop->stop_name, &second_stop->stop_name })) {
			return &pair_stops_to_length_.at({ &first_stop->stop_name, &second_stop->stop_name });
		}
		else {
			return &pair_stops_to_length_.at({ &second_stop->stop_name, &first_stop->stop_name });
		}
		//return nullptr;
	}

