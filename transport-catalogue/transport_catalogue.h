#pragma once
#include <deque>
#include <set>
#include <map>
#include <string>
#include <utility>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <iostream>

#include "geo.h"
#include "domain.h"
namespace transport_catalogue {
	

	struct hash_neighbor_stops {
		std::size_t operator()(const std::pair<const Stop*, const  Stop*>& stops) const {
			return std::hash<const std::string*>()(&stops.first->stop_name) ^ std::hash<const std::string*>()(&stops.second->stop_name);//Можно ли считать такой хешшер хорошим в данном случае? 
			}
	};

	struct BusCompare {
		bool operator() (const Bus* l_bus, const Bus* r_bus) const {
			return l_bus->bus_name < r_bus->bus_name;
		}
	};

	struct StopComparator {
		bool operator()(const Stop& lhs, const Stop& rhs) const {
			return lhs.stop_name < rhs.stop_name;
		}
	};

	class TransportCatalogue {
	public:
		void AddBus(const Bus& bus);
		void AddStop(const Stop& stop);
		void AddStopNames(Stop* stop);
		void AddStopLength(const std::pair<Stop*, Stop*>& pair_stops, double& length);
		Stop* FindStop(std::string_view stop_name) const;
		const std::deque<Bus>* GetBases() const;
		const std::deque<Stop>* GetStops() const;
		double GetLengthBetweenStops(Stop* first_stop, Stop* second_stop) const; 
		const std::set<Bus*, BusCompare>* GetBasesForStop(Stop* stop) const;
		const std::map<std::string, Stop*>* GetStopNames() const;
		size_t GetStopsCount() const;
		const std::map<std::string, Stop*>& GetStopsOnRoutes()const;
	private:
		std::map<std::string, Stop*> stop_names_;//остановки, через который проходит хотя бы один автобус
		std::deque<Stop> stops_;
		std::deque<Bus> buses_;
		std::unordered_map<std::string_view, Stop*> stop_name_to_stop_ptr_;
		std::unordered_map<Stop*, std::set<Bus*, BusCompare>> stop_name_to_bus_ptr_; //BusCompare сортирует лескикографически по именам Bus			
	};
}