#pragma once
#include <string>
#include <deque>
#include <unordered_set>

#include "geo.h"

/*
 * В этом файле вы можете разместить классы/структуры, которые являются частью предметной области (domain)
 * вашего приложения и не зависят от транспортного справочника. Например Автобусные маршруты и Остановки. 
 *
 * Их можно было бы разместить и в transport_catalogue.h, однако вынесение их в отдельный
 * заголовочный файл может оказаться полезным, когда дело дойдёт до визуализации карты маршрутов:
 * визуализатор карты (map_renderer) можно будет сделать независящим от транспортного справочника.
 *
 * Если структура вашего приложения не позволяет так сделать, просто оставьте этот файл пустым.
 *
 */



struct Stop {
	std::string stop_name;
	geo::Coordinates coordinates;
	bool operator==(Stop& rhs) const;
};

struct Bus {
	std::string bus_name;	
	std::deque<Stop*> route;
	bool is_roundtrip;
	std::unordered_set<Stop*> unique_stops;
	
};