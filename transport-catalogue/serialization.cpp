#include "serialization.h"

namespace serialization {
    void serialization::Serializer::SetSettings(const SerializerSettings &settings) {
        settings_ = settings;
    }

    bool Serializer::FileDefined() const {
        return !settings_.file.empty();
    }

    void Serializer::Serialize(const transport_catalogue::TransportCatalogue& t_c, const renderer::MapSetting& map_setting, const RoutingSettings& routing_settings, transport_router::TransportRouter& transport_router)
{
    SerializeBuses(t_c);
    SerializeStops(t_c);
    SerializeRenderSettings(map_setting);
    SerializeRoutingSettings(routing_settings);
    //SerializeTransportRouter(t_c, transport_router);

    FlushToFile();
}

void Serializer::SerializeBuses(const transport_catalogue::TransportCatalogue& t_c) {
    for(const auto & bus : *t_c.GetBases()){
    auto &bus_ = *transport_package_.mutable_catalogue()->add_buses();
    bus_.set_name(bus.bus_name);
    bus_.set_is_roundtrip(bus.is_roundtrip);
        for (auto& stop : bus.route) {
            bus_.add_stops(stop->stop_name);
        }
    }
}

    void Serializer::SerializeStops(const transport_catalogue::TransportCatalogue& t_c) {
        for(const auto & stop : *t_c.GetStops()){
            auto &stop_ = *transport_package_.mutable_catalogue()->add_stops();
            stop_.set_name(stop.stop_name);
            auto &coordinates = *stop_.mutable_coordinates();
            coordinates.set_lat(stop.coordinates.lat);
            coordinates.set_lng(stop.coordinates.lng);
            for (const auto &e: stop.set_length_to_this_stop) {
                auto &distance = *stop_.add_distances_to_stop();
                distance.set_stop_name(e.first->stop_name);
                distance.set_distance(e.second);                
            }           
        }
    }

void Serializer::SerializeColor(const renderer::MapSetting& map_setting, transport_catalogue_pb::RenderSettings &map_setting_pb){
        if(std::holds_alternative<std::string>(map_setting.underlayer_color)){
            *map_setting_pb.mutable_underlayer_color()->mutable_str_color() = 
             std::get<std::string>(map_setting.underlayer_color);
        }else if(std::holds_alternative<svg::Rgb>(map_setting.underlayer_color)){
            svg::Rgb rgb = std::get<svg::Rgb>((map_setting.underlayer_color));
            auto &rgb_pb = *map_setting_pb.mutable_underlayer_color()->mutable_rgb();
            rgb_pb.set_red( rgb.red);
            rgb_pb.set_green( rgb.green);
            rgb_pb.set_blue( rgb.blue);
        }else if(std::holds_alternative<svg::Rgba>(map_setting.underlayer_color)){
            svg::Rgba rgba = std::get<svg::Rgba>((map_setting.underlayer_color));
            auto &rgba_pb = *map_setting_pb.mutable_underlayer_color()->mutable_rgba();
            rgba_pb.set_red(rgba.red);
            rgba_pb.set_green(rgba.green);
            rgba_pb.set_blue(rgba.blue);
            rgba_pb.set_opacity(rgba.opacity);
        }
}

void Serializer::SerializeColorPalette(const renderer::MapSetting &map_setting, transport_catalogue_pb::RenderSettings &map_setting_pb)
{
    for(const auto& color : map_setting.color_palette){
           auto &color_pb = *map_setting_pb.add_color_palette();
            if(std::holds_alternative<std::string>(color)){
                *color_pb.mutable_str_color() = 
                std::get<std::string>(color);
            }else if(std::holds_alternative<svg::Rgb>(color)){
                svg::Rgb rgb = std::get<svg::Rgb>(color);
                auto &rgb_pb = *color_pb.mutable_rgb();
                rgb_pb.set_red( rgb.red);
                rgb_pb.set_green( rgb.green);
                rgb_pb.set_blue( rgb.blue);
            }else if(std::holds_alternative<svg::Rgba>(color)){
                svg::Rgba rgba = std::get<svg::Rgba>((color));
                auto &rgba_pb = *color_pb.mutable_rgba();
                rgba_pb.set_red(rgba.red);
                rgba_pb.set_green(rgba.green);
                rgba_pb.set_blue(rgba.blue);
                rgba_pb.set_opacity(rgba.opacity);
            }
        }
}

void Serializer::SerializeEdgeToRouteSegment(transport_router::TransportRouter &transport_router, transport_catalogue_pb::TransportRouter &transport_router_pb)
{
    for (const auto&[key, value] : transport_router.GetEdgeToRouteSegment()) {
            auto& edge_to_route_segment = *transport_router_pb.add_edge_to_route_segment();
            edge_to_route_segment.set_edge_id(key);
            auto& route_edge_info = *edge_to_route_segment.mutable_route_edge_info();
            route_edge_info.set_stop_name(value.stop_name);
            route_edge_info.set_bus(value.bus);
            route_edge_info.set_span_count(value.span_count);
            route_edge_info.set_time(value.time);
            if (value.type == transport_router::RouteSegmentType::Wait) {
                route_edge_info.set_type(0);
            } 
            else {
                route_edge_info.set_type(1);
            }
    }
}

void Serializer::SerializeGraph(transport_router::TransportRouter &transport_router, transport_catalogue_pb::TransportRouter &transport_router_pb)
{
    const auto& edges = transport_router.GetGraph().value().GetEdges(); 
    const auto& incidence_lists = transport_router.GetGraph().value().GetIncidenceLists(); 

    auto &mutable_graph = *transport_router_pb.mutable_graph();
    mutable_graph.mutable_edges()->Reserve(edges.size());
    mutable_graph.mutable_incidence_lists()->Reserve(incidence_lists.size());

    for (const auto &edge: edges) {
        auto &add_edges = *mutable_graph.add_edges();
        add_edges.set_from(edge.from);
        add_edges.set_to(edge.to);
        add_edges.set_weight(edge.weight);
    }

    for (const auto &incidence_list: incidence_lists) {
        auto &add_incidence_lists = *mutable_graph.add_incidence_lists();
        for (const auto &id : incidence_list) {
            add_incidence_lists.add_edge_id(id);
        }
    }
}


void Serializer::SerializeRenderSettings(const renderer::MapSetting& map_setting)
{
        auto& map_setting_pb = *transport_package_.mutable_render_settings();
        map_setting_pb.set_width(map_setting.width);
        map_setting_pb.set_height(map_setting.height);
        map_setting_pb.set_padding(map_setting.padding);
        map_setting_pb.set_line_width(map_setting.line_width);
        map_setting_pb.set_stop_radius(map_setting.stop_radius);
        map_setting_pb.set_bus_label_font_size(map_setting.bus_label_font_size);
        map_setting_pb.mutable_bus_label_offset()->set_x(map_setting.bus_label_offset.x);
        map_setting_pb.mutable_bus_label_offset()->set_y(map_setting.bus_label_offset.y);
        map_setting_pb.set_stop_label_font_size(map_setting.stop_label_font_size);
        map_setting_pb.mutable_stop_label_offset()->set_x(map_setting.stop_label_offset.x);
        map_setting_pb.mutable_stop_label_offset()->set_y(map_setting.stop_label_offset.y);
        SerializeColor(map_setting, map_setting_pb);
        map_setting_pb.set_underlayer_width(map_setting.underlayer_width);
        SerializeColorPalette(map_setting, map_setting_pb);
    }

    void Serializer::SerializeRoutingSettings(const RoutingSettings& routing_settings)
    {
         auto& routing_settings_pb = *transport_package_.mutable_routing_settings();
         routing_settings_pb.set_bus_velocity(routing_settings.bus_velocity);
         routing_settings_pb.set_bus_wait_time(routing_settings.bus_wait_time);
    }

    void Serializer::SerializeTransportRouter(const transport_catalogue::TransportCatalogue& t_c, transport_router::TransportRouter& transport_router)
    {
        if(FileDefined()){
        transport_router.BuildRoute(t_c);
            if( transport_router.GetRouter() != nullptr){
                auto& transport_router_pb = *transport_package_.mutable_transport_router();        
                SerializeEdgeToRouteSegment(transport_router, transport_router_pb);
                SerializeGraph(transport_router, transport_router_pb);
            }
        }
    }

    void Serializer::FlushToFile() {
        std::fstream ofs(settings_.file, std::ios::binary | std::ios::out);
            if (ofs.is_open()) {
                transport_package_.SerializeToOstream(&ofs);
        }
    }

    void Serializer::DeserializeStops(transport_catalogue_pb::TransportCatalogue& t_c_pb, transport_catalogue::TransportCatalogue &t_c)
    {
        for (int i = 0; i < t_c_pb.stops_size(); i++) {
            const auto &stop = t_c_pb.stops(i);
            Stop stop_;
            stop_.stop_name = stop.name();
            stop_.coordinates = geo::Coordinates{stop.coordinates().lat(),
            stop.coordinates().lng()};
            t_c.AddStop(stop_);    
        }
            for (int i = 0; i < t_c_pb.stops_size(); i++) {
                const auto &stop = t_c_pb.stops(i);
                    for (int j = 0; j < stop.distances_to_stop_size(); ++j) {
            
                        auto distance = stop.distances_to_stop(j);
                        double distance_between = distance.distance();
                        t_c.AddStopLength({ t_c.FindStop(stop.name()),
                                                t_c.FindStop(distance.stop_name()) },
                                                                    distance_between);                                               
                    } 
            }    
    }

    void Serializer::DeserializeBuses(transport_catalogue_pb::TransportCatalogue& t_c_pb, transport_catalogue::TransportCatalogue &t_c)
    {
        for (int i = 0; i < t_c_pb.buses_size(); i++) {
            const auto &bus = t_c_pb.buses(i);
            Bus bus_;
            bus_.bus_name = bus.name();
            bus_.is_roundtrip = bus.is_roundtrip();
            for (int j = 0; j < bus.stops_size(); ++j) {
                Stop* finding_stop = t_c.FindStop(bus.stops(j));
                bus_.route.push_back(finding_stop);
                bus_.unique_stops.insert(finding_stop);
                t_c.AddStopNames(finding_stop);	                
            }
            t_c.AddBus(bus_);
        }
    }

    void Serializer::DeserializeRenderer(transport_catalogue_pb::RenderSettings &render_settings_pb, renderer::MapRenderer &map_renderer)
    {
        renderer::MapSetting map_setting;
        map_setting.width = render_settings_pb.width();
        map_setting.height = render_settings_pb.height();
        map_setting.padding = render_settings_pb.padding();
        map_setting.line_width = render_settings_pb.line_width();
        map_setting.stop_radius = render_settings_pb.stop_radius();
        map_setting.bus_label_font_size = render_settings_pb.bus_label_font_size();
        map_setting.bus_label_offset = {render_settings_pb.bus_label_offset().x(), render_settings_pb.bus_label_offset().y()};
        map_setting.stop_label_font_size = render_settings_pb.stop_label_font_size();
        map_setting.stop_label_offset = {render_settings_pb.stop_label_offset().x(), render_settings_pb.stop_label_offset().y()};
        
       if(render_settings_pb.underlayer_color().has_rgb()){
            svg::Rgb rgb;
            rgb.red = render_settings_pb.underlayer_color().rgb().red();
            rgb.green = render_settings_pb.underlayer_color().rgb().green();
            rgb.blue = render_settings_pb.underlayer_color().rgb().blue();
            map_setting.underlayer_color = rgb;
        }else if (render_settings_pb.underlayer_color().has_rgba()){
            svg::Rgba rgba;
            rgba.red = render_settings_pb.underlayer_color().rgba().red();
            rgba.green = render_settings_pb.underlayer_color().rgba().green();
            rgba.blue = render_settings_pb.underlayer_color().rgba().blue();
            rgba.opacity = render_settings_pb.underlayer_color().rgba().opacity();
            map_setting.underlayer_color = rgba;
        }  else {
            map_setting.underlayer_color = render_settings_pb.underlayer_color().str_color();
        }
        
        map_setting.underlayer_width = render_settings_pb.underlayer_width();
        for(int i = 0; i != render_settings_pb.color_palette_size(); i++)
        {
            const auto &color_pb = render_settings_pb.color_palette(i);

            if(color_pb.has_rgb()){
                svg::Rgb rgb;
                rgb.red = color_pb.rgb().red();
                rgb.green = color_pb.rgb().green();
                rgb.blue = color_pb.rgb().blue();
                map_setting.color_palette.push_back(rgb);
            }else if (color_pb.has_rgba()){
                svg::Rgba rgba;
                rgba.red = color_pb.rgba().red();
                rgba.green = color_pb.rgba().green();
                rgba.blue = color_pb.rgba().blue();
                rgba.opacity = color_pb.rgba().opacity();
                map_setting.color_palette.push_back(rgba);
            }else {
                map_setting.color_palette.push_back(color_pb.str_color());
            }
        }
        map_renderer.SetSetting(map_setting);
    }

    void Serializer::DeserializeRoutingSetting(transport_catalogue_pb::RoutingSettings &routing_settings_pb, transport_router::TransportRouter &transport_router)
    {
        RoutingSettings routing_settings;
        routing_settings.bus_velocity = routing_settings_pb.bus_velocity();
        routing_settings.bus_wait_time = routing_settings_pb.bus_wait_time();
        transport_router.SetRoutingSetting(routing_settings);
    }

    void Serializer::DeserializeTransportRouter(transport_catalogue::TransportCatalogue& t_c, transport_router::TransportRouter& transport_router)
    {
        if (t_c.GetStops()->size() > 0) {
            auto& transport_router_pb = transport_package_.transport_router();
            
            for (const auto& [stop_name, stop_ptr] : t_c.GetStopsOnRoutes()) {
                //добавляем вершины
                transport_router.AddVertexesForDesserialize(stop_name);
            }
            DeserializeEdgeToRouteSegment(transport_router_pb, transport_router);
            DeserializeGraph(transport_router_pb, transport_router);
            DeserializeRouter(transport_router_pb, transport_router);
        }
    }

    void Serializer::DeserializeEdgeToRouteSegment(const transport_catalogue_pb::TransportRouter &transport_router_pb, transport_router::TransportRouter &transport_router)
    {
        std::unordered_map<graph::EdgeId, transport_router::RouteEdgeInfo> edge_to_route_segment;
            for (int i = 0; i < transport_router_pb.edge_to_route_segment_size(); ++i) {
                const auto edge_to_route_segment_pb = transport_router_pb.edge_to_route_segment(i);
                transport_router::RouteEdgeInfo route_edge_info;
                route_edge_info.stop_name = edge_to_route_segment_pb.route_edge_info().stop_name();
                route_edge_info.bus = edge_to_route_segment_pb.route_edge_info().bus();
                route_edge_info.span_count = edge_to_route_segment_pb.route_edge_info().span_count();
                route_edge_info.time = edge_to_route_segment_pb.route_edge_info().time();
                route_edge_info.type = edge_to_route_segment_pb.route_edge_info().type() ?
                transport_router::RouteSegmentType::GoesByBus : transport_router::RouteSegmentType::Wait;
                edge_to_route_segment.emplace(edge_to_route_segment_pb.edge_id(), route_edge_info);
             }
            transport_router.SetEdgeToRouteSegment(std::move(edge_to_route_segment));
    }

    void Serializer::DeserializeGraph(const transport_catalogue_pb::TransportRouter &transport_router_pb, transport_router::TransportRouter &transport_router)
    {
        std::vector<graph::Edge<double>> edges;
               for (int i = 0; i < transport_router_pb.graph().edges_size(); ++i) {
                    auto edge_pack = transport_router_pb.graph().edges(i);
                    auto &add_edge = edges.emplace_back();
                    add_edge.from = edge_pack.from();
                    add_edge.to = edge_pack.to();
                    add_edge.weight = edge_pack.weight();
                }
                std::vector<std::vector<graph::EdgeId>> incidence_lists;
                for (int i = 0; i < transport_router_pb.graph().incidence_lists_size(); ++i) {
                    auto incidence_lists_pack = transport_router_pb.graph().incidence_lists(i);
                    auto &incidence_lists_element = incidence_lists.emplace_back();
                    for (int j = 0; j < incidence_lists_pack.edge_id_size(); ++j) {
                        incidence_lists_element.emplace_back(incidence_lists_pack.edge_id(j));
                    }
                }
               //static auto graph_ = graph::DirectedWeightedGraph<double>(std::move(edges), std::move(incidence_lists));
               transport_router.SetGraph(std::move(graph::DirectedWeightedGraph<double>(std::move(edges), std::move(incidence_lists))));
    }

    void Serializer::DeserializeRouter(const transport_catalogue_pb::TransportRouter &transport_router_pb, transport_router::TransportRouter &transport_router)
    {
                 transport_router.SetRouter(std::move(graph::Router<double>(transport_router.GetGraph().value())));  
    }

    void Serializer::Deserialize(transport_catalogue::TransportCatalogue& t_c, renderer::MapRenderer& map_renderer, transport_router::TransportRouter& transport_router) {
        if (FileDefined()) {
            std::fstream ifs(settings_.file, std::ios::binary | std::ios::in);
            if (ifs.is_open()) {
                transport_package_.Clear();
                if (transport_package_.ParseFromIstream(&ifs)) {
                    //Deserialize transport catalogue
                    auto &catalogue = *transport_package_.mutable_catalogue();
                    //Deserialize stops
                    DeserializeStops(catalogue, t_c);
                    //Deserialize buses
                    DeserializeBuses(catalogue, t_c);
                    //Deserialize render settings
                    auto render_settings_pb = transport_package_.render_settings();
                    DeserializeRenderer(render_settings_pb, map_renderer);
                    auto routing_settings_pb = transport_package_.routing_settings();
                    DeserializeRoutingSetting(routing_settings_pb, transport_router);
                    //DeserializeTransportRouter(t_c, transport_router);
                }
            }
        }
    }
} //namespace serialization 
