#include "transport_router.h"

using namespace transport_router;

void TransportRouter::SetRoutingSetting(RoutingSettings& settings)
{
	settings_ = settings;
}

std::optional<std::pair<double, std::vector<RouteEdgeInfo>>>
TransportRouter::BuildRoute(const TransportCatalogue& transport_catalogue, std::string from,
    std::string to) {
    if (!graph_) {
       //заполнение графа
        BuildBusRoutesGraph(transport_catalogue);
        //создание маршрута на графе
        if (graph_->GetEdgeCount() > 0) {
            router_ = std::make_shared<graph::Router<double>>(std::move(graph::Router<double>(graph_.value())));
        }
    }
    //Если граф пустой, то маршрут не строится
    
    if (graph_->GetEdgeCount() == 0) {
        return std::nullopt;
    }
    
    std::vector<RouteEdgeInfo> route_segments;
    if (from == to) { 
        return std::pair{ 0, route_segments };
    }
    //Если остановка входит в stop_to_vertex_,то строим до нее маршрут
    if (stop_to_vertex_.count(from) > 0 && stop_to_vertex_.count(to) > 0) {
        auto route_build = router_->BuildRoute(stop_to_vertex_.at(from),
            stop_to_vertex_.at(to));

        if (route_build) {
            
            if (route_build.value().edges.size() == 0 && route_build.value().weight == 0) {
                return std::nullopt;
            }
            for (const auto& edge_id : route_build.value().edges) {
                route_segments.emplace_back(edge_to_route_segment_.at(edge_id));
            }
            return std::pair{ route_build.value().weight, route_segments };
        }       
    }   
    return std::nullopt;
}

void transport_router::TransportRouter::BuildRoute(const TransportCatalogue &transport_catalogue)
{
    if (!graph_) {
       //заполнение графа
       BuildBusRoutesGraph(transport_catalogue);
        if (graph_->GetEdgeCount() > 0) {
            router_ = std::make_shared<graph::Router<double>>(std::move(graph::Router<double>(graph_.value())));
        }
    }
}

void TransportRouter::BuildBusRoutesGraph(const TransportCatalogue& transport_catalogue) {
    //создаем пустой граф с двумя вершинами на каждую остановку
    graph_ = std::move(graph::DirectedWeightedGraph<double>(2.0 * transport_catalogue.GetStopsCount()));
    //переберем все маршруты, заполним Vertexes
    for (const auto& [stop_name, stop_ptr] : transport_catalogue.GetStopsOnRoutes()) {
        //добавляем вершины
        AddVertexes(stop_name);
    }
    for (const auto& bus : *transport_catalogue.GetBases()) {
        //добавляем ребра
        AddEdges(transport_catalogue, bus);        
    }
}

void transport_router::TransportRouter::AddVertexes(const std::string& stop_name)
{
    using namespace std::literals;
        //добавляем вершину
        if (stop_to_vertex_.count(stop_name) == 0) {
            stop_to_vertex_[stop_name] = stop_to_vertex_.size();
        }
        //добавляем вершину - ожидание, вдруг здесь будет куда пересаживаться
        if (stop_to_vertex_.count(stop_name + "_wait"s) == 0) {
            
            stop_to_vertex_[stop_name + "_wait"s] = stop_to_vertex_.size();
            //вершину ожидания добавили - сделаем к нему ребро из остановки
            auto edge_id = graph_->AddEdge(Edge{ stop_to_vertex_.at(stop_name),
                                                stop_to_vertex_.at(stop_name + "_wait"s),
                                                settings_.bus_wait_time + 0.0 });
            edge_to_route_segment_[edge_id] = std::move(RouteEdgeInfo{ stop_name, ""s,
                                                             0, settings_.bus_wait_time + 0.0,
                                                            RouteSegmentType::Wait });
        }    
}

void transport_router::TransportRouter::AddVertexesForDesserialize(const std::string& stop_name)
{
    using namespace std::literals;
       
        //добавляем вершину
        if (stop_to_vertex_.count(stop_name) == 0) {
            stop_to_vertex_[stop_name] = stop_to_vertex_.size();
        }
        //добавляем вершину - ожидание, вдруг здесь будет куда пересаживаться
        if (stop_to_vertex_.count(stop_name + "_wait"s) == 0) {
            stop_to_vertex_[stop_name + "_wait"s] = stop_to_vertex_.size();
        }    
}

void transport_router::TransportRouter::AddEdges(const TransportCatalogue& transport_catalogue, const Bus& bus)
{
    using namespace std::literals;
    for (auto it_start = bus.route.begin(); it_start != bus.route.end(); ++it_start) {
        if (!bus.is_roundtrip &&
            std::distance(it_start, bus.route.begin()) == long(bus.route.size() / 2)) {
            break;
        }
        double time_to_drive_forward = 0;
        double time_to_drive_reverse = 0;
        int span_count = 0;
        auto prev_stop = it_start;
        for (auto it_end = std::next(it_start); it_end != bus.route.end(); ++it_end) {
            time_to_drive_forward += transport_catalogue.GetLengthBetweenStops(*prev_stop, *it_end)
                / settings_.bus_velocity;
                       
            auto edge_id = graph_->AddEdge(std::move(Edge{stop_to_vertex_.at((*it_start)->stop_name + "_wait"s),
                                                stop_to_vertex_.at((*it_end)->stop_name),
                                                time_to_drive_forward }));
            edge_to_route_segment_[edge_id] = std::move(RouteEdgeInfo{ (*it_start)->stop_name, bus.bus_name,
                                                            ++span_count, time_to_drive_forward,
                                                            RouteSegmentType::GoesByBus });

            if (!bus.is_roundtrip) {
                 time_to_drive_reverse += transport_catalogue.GetLengthBetweenStops(*it_end, *prev_stop)
                / settings_.bus_velocity;
                edge_id = graph_->AddEdge(std::move(Edge{stop_to_vertex_.at((*it_end)->stop_name + "_wait"s),
                                               stop_to_vertex_.at((*it_start)->stop_name),
                                               time_to_drive_reverse }));
                edge_to_route_segment_[edge_id] = std::move(RouteEdgeInfo{ (*it_end)->stop_name, bus.bus_name,
                                                                span_count, time_to_drive_reverse,
                                                                RouteSegmentType::GoesByBus });
            }
            prev_stop = it_end;

            if (!bus.is_roundtrip &&
                std::distance(it_end, bus.route.begin()) == long(bus.route.size() / 2)) {
                break;
            }
        }
    }
}

const RoutingSettings &transport_router::TransportRouter::GetRoutingSettings()const
{
    return settings_;
}

const std::unordered_map<std::string, graph::VertexId>& transport_router::TransportRouter::GetStopToVertex() const
{
    return stop_to_vertex_;
}

void transport_router::TransportRouter::SetStopToVertex(std::unordered_map<std::string, graph::VertexId> &&stop_to_vertex)
{
    stop_to_vertex_ = std::move(stop_to_vertex);
}

const std::unordered_map<graph::EdgeId, RouteEdgeInfo>& transport_router::TransportRouter::GetEdgeToRouteSegment() const
{
    return edge_to_route_segment_;
}

void transport_router::TransportRouter::SetEdgeToRouteSegment(std::unordered_map<graph::EdgeId, RouteEdgeInfo> &&edge_to_route_segment)
{
    edge_to_route_segment_ = std::move(edge_to_route_segment);
}

const std::optional<graph::DirectedWeightedGraph<double>>& transport_router::TransportRouter::GetGraph() const
{
    return graph_;
}

void transport_router::TransportRouter::SetGraph(std::optional<graph::DirectedWeightedGraph<double>> &&graph)
{
graph_ = std::move(graph);
}

const std::shared_ptr<graph::Router<double>>& transport_router::TransportRouter::GetRouter() const
{
    return router_;
}

void transport_router::TransportRouter::SetRouter(graph::Router<double> &&router)
{
    router_ = std::make_shared<graph::Router<double>>(std::move(router));
}
