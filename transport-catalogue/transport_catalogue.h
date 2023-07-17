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
		Coordinates coordinates;
		bool operator==(Stop& rhs) const {
			return this->stop_name == rhs.stop_name &&
				this->coordinates == rhs.coordinates;
		}
	};

	struct Bus {
		std::string bus_name;
		std::deque<Stop*> route;
		std::unordered_set<Stop*> unique_stops;
	};

	struct hash_neighbor_stops {
		std::size_t operator()(const std::pair<const Stop*, const  Stop*>& stops) const {
			//return std::hash<const std::string*>()(&stops.first->stop_name) ^ std::hash<const std::string*>()(&stops.second->stop_name);
			return std::hash<const void*>()(stops.first) ^ std::hash<const void*>()(stops.second);
			//return std::hash<const void*>()(&stops);
		}
	};

	struct BusCompare {
		bool operator() (const Bus* l_bus, const Bus* r_bus) const {
			return l_bus->bus_name < r_bus->bus_name;
		}
	};

	class TransportCatalogue {
	public:
		void AddBus(const Bus& bus);
		void AddStop(const Stop& stop);
		void AddStopLength(const std::pair<Stop*, Stop*>& pair_stops, double& length);
		Stop* FindStop(std::string_view stop_name) const;
		const Bus* FindBus(const std::string& bus_name) const;
		const std::deque<Bus>* GetBases() const;
		const double GetLengthBetweenStops(Stop* first_stop, Stop* second_stop) const;
		const std::set<Bus*, BusCompare>* GetBasesForStop(Stop* stop) const;

	private:
		std::deque<Stop> stops_;
		std::deque<Bus> buses_;
		std::unordered_map<std::string_view, Stop*> stop_name_to_stop_ptr_;
		std::unordered_map<Stop*, std::set<Bus*, BusCompare>> stop_name_to_bus_ptr_;
		std::unordered_map<std::pair<Stop*, Stop*>, double, hash_neighbor_stops> pair_stops_to_length_;
	};
}