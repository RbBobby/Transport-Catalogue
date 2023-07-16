#pragma once
#include <deque>
#include <set>
#include <string>
#include <utility>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

#include "geo.h"
namespace transport_catalogue {
	struct Stop {
		std::string stop_name;
		double latitude;
		double longitude;
		bool operator==(Stop& rhs) const {
			return this->stop_name == rhs.stop_name &&
				this->latitude == rhs.latitude &&
				this->longitude == rhs.longitude;
		}
	};


	struct Bus {
		std::string bus_name;
		std::deque<Stop*> route;
		std::unordered_set<Stop*> unique_stops;
	};

	struct hash_neighbor_stops {
		std::size_t operator()(const std::pair<std::string*, std::string*>& stops) const {
			return std::hash<std::string*>()(stops.first) ^ std::hash<std::string*>()(stops.second);
		}
	};

	class TransportCatalogue {
	public:
		void AddBus(Bus& bus);
		void AddStop(Stop& stop);
		void AddStopLength(std::string* first_stop, std::string* second_stop, double& length);
		Stop* FindStop(std::string_view stop_name) const;
		const Bus* FindBus(std::string& bus_name) const;
		const std::deque<Bus>* GetBasses() const;
		const double* GetLengthBetweenStops(Stop* first_stop, Stop* second_stop) const;
		const std::set<std::string_view>* GetBassesForStop(std::string_view stop_name);

	private:
		std::deque<Stop> stops_;
		std::deque<Bus> buses_;
		std::unordered_map<std::string*, Stop*> stop_name_to_stop_ptr_;
		std::unordered_map<std::string_view, std::set<std::string_view>> stop_name_to_bus_ptr_;
		std::unordered_map<std::pair<std::string*, std::string*>, double, hash_neighbor_stops> pair_stops_to_length_;
	};
}