#pragma once
#include <optional>

#include "geo.h"
#include "map_renderer.h"
#include "transport_catalogue.h"

using namespace geo;
using namespace transport_catalogue;
/*
 * Здесь можно было бы разместить код обработчика запросов к базе, содержащего логику, которую не
 * хотелось бы помещать ни в transport_catalogue, ни в json reader.
 *
 * В качестве источника для идей предлагаем взглянуть на нашу версию обработчика запросов.
 * Вы можете реализовать обработку запросов способом, который удобнее вам.
 *
 * Если вы затрудняетесь выбрать, что можно было бы поместить в этот файл,
 * можете оставить его пустым.
 */

// Класс RequestHandler играет роль Фасада, упрощающего взаимодействие JSON reader-а
// с другими подсистемами приложения.
// См. паттерн проектирования Фасад: https://ru.wikipedia.org/wiki/Фасад_(шаблон_проектирования)

double CalculateRouteLengthCoordinate(const Bus& bus);
double CalculateRouteLength(const TransportCatalogue& transport_catalogue, const Bus& bus);
double CalculateCurvature(const double route_length, const double route_length_coordinate);



class RequestHandler {
public:
    // MapRenderer понадобится в следующей части итогового проекта

    RequestHandler(const TransportCatalogue& db, renderer::MapRenderer& renderer);

    std::optional<Bus> GetBusStat(const std::string_view& bus_name) const;

    // Возвращает маршруты, проходящие через (запрос Stop)
    //const std::set<Bus*, BusCompare >* GetBusesByStop(const std::string_view& stop_name) const;
    
    std::ostream& RenderMap(std::ostream& os) const;

private:
    // RequestHandler использует агрегацию объектов "Транспортный Справочник" и "Визуализатор Карты"
    const transport_catalogue::TransportCatalogue& db_;
    
    renderer::MapRenderer& renderer_;
};
