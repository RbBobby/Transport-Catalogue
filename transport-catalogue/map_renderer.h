#pragma once
#include "svg.h"
#include "geo.h"
#include "domain.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <optional>
#include <vector>
#include <map>

namespace renderer {

struct MapSetting {
    // ширина и высота изображения в пикселях. Вещественное число в диапазоне от 0 до 100000.
    double width;
    double height;

    //отступ краёв карты от границ SVG - документа.Вещественное число не меньше 0 и меньше min(width, height) / 2
    double padding;

    //толщина линий, которыми рисуются автобусные маршруты. Вещественное число в диапазоне от 0 до 100000.
    double line_width;

    //радиус окружностей, которыми обозначаются остановки. Вещественное число в диапазоне от 0 до 100000.
    double stop_radius;

    //размер текста, которым написаны названия автобусных маршрутов. Целое число в диапазоне от 0 до 100000.
    double bus_label_font_size;

    //смещение надписи с названием маршрута относительно координат конечной остановки на карте. Массив из двух элементов типа double.
    //Задаёт значения свойств dx и dy SVG-элемента <text>. Элементы массива — числа в диапазоне от –100000 до 100000.
    svg::Point bus_label_offset;

    //размер текста, которым отображаются названия остановок. Целое число в диапазоне от 0 до 100000.
    int stop_label_font_size;

    //смещение названия остановки относительно её координат на карте. Массив из двух элементов типа double.
    //Задаёт значения свойств dx и dy SVG-элемента <text>. Числа в диапазоне от –100000 до 100000.
    svg::Point stop_label_offset;

    //цвет подложки под названиями остановок и маршрутов. Формат хранения цвета будет ниже.
    svg::Color underlayer_color;

    //толщина подложки под названиями остановок и маршрутов.
    //Задаёт значение атрибута stroke-width элемента <text>.
    //Вещественное число в диапазоне от 0 до 100000.
    double underlayer_width;

    //цветовая палитра. Непустой массив.
    std::vector<svg::Color> color_palette;
};

inline const double EPSILON = 1e-6;
bool IsZero(double value);

class SphereProjector {
public:
    // points_begin и points_end задают начало и конец интервала элементов geo::Coordinates
    template <typename PointInputIt>
    SphereProjector(PointInputIt points_begin, PointInputIt points_end,
        double max_width, double max_height, double padding);

    // Проецирует широту и долготу в координаты внутри SVG-изображения
    svg::Point operator()(geo::Coordinates coords) const;

private:
    double padding_;
    double min_lon_ = 0;
    double max_lat_ = 0;
    double zoom_coeff_ = 0;
};

svg::Polyline CreateRoad(std::vector<svg::Point>& point);

class MapRenderer : public svg::Drawable {
public:
    MapRenderer() = default;
   
    // Реализует метод Draw интерфейса svg::Drawable
    
    void Draw(svg::ObjectContainer& container) const override; 
    std::vector<geo::Coordinates> MakeGeoCoords(const std::deque<Bus>* buses_)const;
    void AddImageRoadMap(svg::ObjectContainer& container, const SphereProjector& proj, const std::deque<Bus>& buses_)const;
    void AddTextRoadMap(svg::ObjectContainer& container, const SphereProjector& proj, const std::deque<Bus>& buses_) const;
    void AddStopPointsRoadMap(svg::ObjectContainer& container, const SphereProjector& proj, const std::map<std::string, Stop*>& stops) const;
    void AddStopNamesRoadMap(svg::ObjectContainer& container, const SphereProjector& proj, const std::map<std::string, Stop*>& stops) const;
    void SetTextBus(svg::ObjectContainer& container, const std::string bus_name, const svg::Point proj_geo_coord, int num_color) const;
    void SetTextStop(svg::ObjectContainer& container, const std::string str_stop_name, const svg::Point proj_geo_coord) const;
    void SetSetting(const MapSetting& map_setting);
    void SetBusesAndStops(const std::deque<Bus>* buses, const std::map<std::string, Stop*>* stops_);
    const MapSetting& GetSetting()const;
private:
    MapSetting map_setting_;
    const std::deque<Bus>* buses_;
    const std::map<std::string, Stop*>* stops_;
};

template<typename PointInputIt>
SphereProjector::SphereProjector(PointInputIt points_begin, PointInputIt points_end, double max_width, double max_height, double padding)

    : padding_(padding) //
{
    // Если точки поверхности сферы не заданы, вычислять нечего
    if (points_begin == points_end) {
        return;
    }

    // Находим точки с минимальной и максимальной долготой
    const auto [left_it, right_it] = std::minmax_element(
        points_begin, points_end,
        [](auto lhs, auto rhs) { return lhs.lng < rhs.lng; });
    min_lon_ = left_it->lng;
    const double max_lon = right_it->lng;

    // Находим точки с минимальной и максимальной широтой
    const auto [bottom_it, top_it] = std::minmax_element(
        points_begin, points_end,
        [](auto lhs, auto rhs) { return lhs.lat < rhs.lat; });
    const double min_lat = bottom_it->lat;
    max_lat_ = top_it->lat;

    // Вычисляем коэффициент масштабирования вдоль координаты x
    std::optional<double> width_zoom;
    if (!IsZero(max_lon - min_lon_)) {
        width_zoom = (max_width - 2 * padding) / (max_lon - min_lon_);
    }

    // Вычисляем коэффициент масштабирования вдоль координаты y
    std::optional<double> height_zoom;
    if (!IsZero(max_lat_ - min_lat)) {
        height_zoom = (max_height - 2 * padding) / (max_lat_ - min_lat);
    }

    if (width_zoom && height_zoom) {
        // Коэффициенты масштабирования по ширине и высоте ненулевые,
        // берём минимальный из них
        zoom_coeff_ = std::min(*width_zoom, *height_zoom);
    }
    else if (width_zoom) {
        // Коэффициент масштабирования по ширине ненулевой, используем его
        zoom_coeff_ = *width_zoom;
    }
    else if (height_zoom) {
        // Коэффициент масштабирования по высоте ненулевой, используем его
        zoom_coeff_ = *height_zoom;
    }
}
}
//namespace