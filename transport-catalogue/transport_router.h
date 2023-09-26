#pragma once
#include <memory>

#include "transport_catalogue.h"
#include "graph.h"
#include "router.h"

struct RoutingSettings {
	int bus_wait_time;
	double bus_velocity;
};

namespace transport_router{

    using namespace transport_catalogue;
    using namespace graph;

enum RouteSegmentType {
	Wait,
	GoesByBus,
};

struct RouteEdgeInfo {
	std::string stop_name;
	std::string bus;
	int span_count;
	double time;
	RouteSegmentType type;
};

class TransportRouter {
public:
    using Edge = graph::Edge<double>;
    using Router = graph::Router<double>;

    TransportRouter() = default;

    void SetRoutingSetting(RoutingSettings& settings);

    std::optional<std::pair<double, std::vector<RouteEdgeInfo>>>
        BuildRoute(TransportCatalogue& transport_catalogue, std::string, std::string);

private:
    RoutingSettings settings_;
    std::unordered_map<std::string, graph::VertexId> stop_to_vertex_;
    std::unordered_map<graph::EdgeId, RouteEdgeInfo> edge_to_route_segment_;
    std::optional<graph::DirectedWeightedGraph<double>> graph_ = std::nullopt;
    std::shared_ptr<graph::Router<double>> router_ = nullptr;
    
    void BuildBusRoutesGraph(const TransportCatalogue& transport_catalogue);
    void AddVertexes(const Bus& bus);
    void AddEdges(const TransportCatalogue& transport_catalogue, const Bus& bus);
};
}