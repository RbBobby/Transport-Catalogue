#include "map_renderer.h"

/*
 * В этом файле вы можете разместить код, отвечающий за визуализацию карты маршрутов в формате SVG.
 * Визуализация маршрутов вам понадобится во второй части итогового проекта.
 * Пока можете оставить файл пустым.
 */

bool renderer::IsZero(double value)
{
    return std::abs(value) < EPSILON;
}

svg::Polyline renderer::CreateRoad(std::vector<svg::Point>& points)
{
    using namespace svg;
    Polyline polyline;    
    for (const auto& point : points) {
        polyline.AddPoint(point);
    }
    return polyline;
}

svg::Point renderer::SphereProjector::operator()(geo::Coordinates coords) const
{
    return {
        (coords.lng - min_lon_) * zoom_coeff_ + padding_,
        (max_lat_ - coords.lat) * zoom_coeff_ + padding_
    };
}

void renderer::MapRenderer::Draw(svg::ObjectContainer& container) const
{
    //создаем контейнер со сферическими координатами  
    std::vector<geo::Coordinates> geo_coords = MakeGeoCoords(buses_);  
    //создаем проекции 
    const SphereProjector proj{                                       
        geo_coords.begin(), geo_coords.end(), map_setting_.width, map_setting_.height, map_setting_.padding
    };
    std::deque<Bus> buses = *buses_;
    std::sort(buses.begin(), buses.end(), [](const auto& lhs, const auto& rhs) {
        return lhs.bus_name <= rhs.bus_name; });
    std::map<std::string, Stop*> stops = *stops_;
    
    //рисуем 
    AddImageRoadMap(container, proj, buses);
    AddTextRoadMap(container, proj, buses);
    AddStopPointsRoadMap(container, proj, stops);
    AddStopNamesRoadMap(container, proj, stops);
}

//создаем контейнер координат по остановкам
std::vector<geo::Coordinates> renderer::MapRenderer::MakeGeoCoords(const std::deque<Bus>* buses_)const
{
    std::vector<geo::Coordinates> geo_coords;
    for (const auto& bus : *buses_) {
            for (const auto& stop : bus.route) {
                geo_coords.push_back(stop->coordinates);
        }
    }
    return geo_coords;
}

//рисуем для каждого маршрута отдельно карту остановок

void renderer::MapRenderer::AddImageRoadMap(svg::ObjectContainer& container, const SphereProjector& proj, const std::deque<Bus>& buses)const
{
    //если в маршруте нет остановок, то увеличиваем ind на 1.
    //Тем самым пропускаем пустой маршрут и сохраняем цвет для следующего    
    int ind = 0;                
    for (size_t i = 0; i != buses.size(); ++i) {
        if (buses[i].route.empty()) {
            ++ind;
        }else{
            std::vector<svg::Point> proj_geo_coords;
            for (const auto& stop : buses[i].route) {
                proj_geo_coords.push_back(proj({ stop->coordinates.lat,stop->coordinates.lng }));
            }
            int num_color = (i + ind) % map_setting_.color_palette.size();

            svg::Color color = map_setting_.color_palette[num_color];// выбираем цвет
            container.Add(CreateRoad(proj_geo_coords)
                .SetFillColor("none")
                .SetStrokeColor(color)
                .SetStrokeWidth(map_setting_.line_width)
                .SetStrokeLineCap(svg::StrokeLineCap::ROUND)
                .SetStrokeLineJoin(svg::StrokeLineJoin::ROUND));
        }
    }        
}

void renderer::MapRenderer::AddTextRoadMap(svg::ObjectContainer& container, const SphereProjector& proj, const std::deque<Bus>& buses)const
{
    //если в маршруте нет остановок, то увеличиваем ind на 1.
    //Тем самым пропускаем пустой маршрут и сохраняем цвет для следующего
   int ind = 0;
   for (size_t i = 0; i != buses.size(); ++i) {
        if (buses[i].route.empty()) {
            ++ind;
        }
        else {
            std::string bus_name = buses[i].bus_name;
            int num_color = (i + ind) % map_setting_.color_palette.size();
            svg::Point proj_geo_coord = proj({ buses[i].route[0]->coordinates.lat, buses[i].route[0]->coordinates.lng });
            if (buses[i].is_roundtrip) {
                SetTextBus(container, bus_name, proj_geo_coord, num_color);
            }
            else {      
                SetTextBus(container, bus_name, proj_geo_coord, num_color);                
                if (buses[i].route[buses[i].route.size() / 2] != buses[i].route[0]) {
                    svg::Point proj_geo_coord_1 = proj({ buses[i].route[buses[i].route.size() / 2]->coordinates.lat, buses[i].route[buses[i].route.size() / 2]->coordinates.lng });
                    SetTextBus(container, bus_name, proj_geo_coord_1, num_color);
                }
            }
        }
    }
}

void renderer::MapRenderer::AddStopPointsRoadMap(svg::ObjectContainer& container, const SphereProjector& proj, const std::map<std::string, Stop*>& stops)const
{

    for (const auto& [name, stop] : stops) {

        svg::Point proj_geo_coord = proj({ stop->coordinates.lat,stop->coordinates.lng });
        svg::Circle StopPoint =
            svg::Circle()
            .SetCenter(proj_geo_coord)
            .SetRadius(map_setting_.stop_radius)
            .SetFillColor("white");
        container.Add(StopPoint);
    }
}

void renderer::MapRenderer::AddStopNamesRoadMap(svg::ObjectContainer& container, const SphereProjector& proj, const std::map<std::string, Stop*>& stops) const
{
    for (const auto& [name, stop] : stops) {
        
        svg::Point proj_geo_coord = proj({ stop->coordinates.lat, stop->coordinates.lng });
        SetTextStop(container, name, proj_geo_coord);
    }
}

void renderer::MapRenderer::SetTextBus(svg::ObjectContainer& container, const std::string bus_name, const svg::Point proj_geo_coord, int num_color) const{
    svg::Color color = map_setting_.color_palette[num_color];// выбираем цвет
    svg::Text base_text =
        svg::Text()
        .SetFontFamily("Verdana")
        .SetFontWeight("bold")
        .SetPosition(proj_geo_coord)
        .SetOffset(map_setting_.bus_label_offset)
        .SetFontSize(map_setting_.bus_label_font_size)
        .SetData(bus_name);
    container.Add(svg::Text{ base_text }
        .SetStrokeColor(map_setting_.underlayer_color)
        .SetFillColor(map_setting_.underlayer_color)
        .SetStrokeWidth(map_setting_.underlayer_width)
        .SetStrokeLineJoin(svg::StrokeLineJoin::ROUND)
        .SetStrokeLineCap(svg::StrokeLineCap::ROUND));
    container.Add(svg::Text{ base_text }.SetFillColor(color));
}

void renderer::MapRenderer::SetTextStop(svg::ObjectContainer& container, const std::string str_stop_name, const svg::Point proj_geo_coord) const {
    
    svg::Text stop_name =
        svg::Text()
        .SetFontFamily("Verdana")
        .SetPosition(proj_geo_coord)
        .SetOffset(map_setting_.stop_label_offset)
        .SetFontSize(map_setting_.stop_label_font_size)
        .SetData(str_stop_name);
    container.Add(svg::Text{ stop_name }
        .SetStrokeColor(map_setting_.underlayer_color)
        .SetFillColor(map_setting_.underlayer_color)
        .SetStrokeWidth(map_setting_.underlayer_width)
        .SetStrokeLineJoin(svg::StrokeLineJoin::ROUND)
        .SetStrokeLineCap(svg::StrokeLineCap::ROUND));
    container.Add(svg::Text{ stop_name }.SetFillColor("black"));
}

void renderer::MapRenderer::SetSetting(const MapSetting& map_setting)
{
    map_setting_ = map_setting;
}

void renderer::MapRenderer::SetBusesAndStops(const std::deque<Bus>* buses, const std::map<std::string, Stop*>* stops)
{
    buses_ = buses;
    stops_ = stops;
}

