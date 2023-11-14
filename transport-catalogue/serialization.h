#pragma once

#include "transport_catalogue.pb.h"
#include "domain.h"
#include "transport_catalogue.h"
#include "map_renderer.h"
#include "transport_router.h"

#include <string>
#include <fstream>
#include <iostream>
struct SerializerSettings {
    std::string file;
};

namespace serialization {
    class Serializer {
    private:
        SerializerSettings settings_;
        transport_catalogue_pb::TransportPackage transport_package_;

    public:
        void SetSettings(const SerializerSettings &settings);
        bool FileDefined() const;

        void Serialize(const transport_catalogue::TransportCatalogue& t_c, const renderer::MapSetting& map_setting, const RoutingSettings& routing_settings, transport_router::TransportRouter& transport_router);
       
        void FlushToFile();        

        void Deserialize(transport_catalogue::TransportCatalogue& t_c, renderer::MapRenderer& map_renderer, transport_router::TransportRouter& transport_router );
        
    private:

        void SerializeColor(const renderer::MapSetting& map_setting, transport_catalogue_pb::RenderSettings &map_setting_pb);
        void SerializeColorPalette(const renderer::MapSetting& map_setting, transport_catalogue_pb::RenderSettings &map_setting_pb);

        void SerializeStopToVertex(transport_router::TransportRouter& transport_router, transport_catalogue_pb::TransportRouter &transport_router_pb );
        void SerializeEdgeToRouteSegment(transport_router::TransportRouter& transport_router, transport_catalogue_pb::TransportRouter &transport_router_pb );
        void SerializeGraph(transport_router::TransportRouter& transport_router, transport_catalogue_pb::TransportRouter &transport_router_pb );

        void SerializeBuses(const transport_catalogue::TransportCatalogue& t_c);
        void SerializeStops(const transport_catalogue::TransportCatalogue& t_c);
        void SerializeRenderSettings(const renderer::MapSetting& map_setting);
        void SerializeRoutingSettings(const RoutingSettings& routing_settings);
        void SerializeTransportRouter(const transport_catalogue::TransportCatalogue& t_c, transport_router::TransportRouter& transport_router);

        void SerializeRouter(transport_router::TransportRouter& transport_router, transport_catalogue_pb::TransportRouter &transport_router_pb );


        void DeserializeStops(transport_catalogue_pb::TransportCatalogue& t_c_pb, transport_catalogue::TransportCatalogue& t_c);
        void DeserializeBuses(transport_catalogue_pb::TransportCatalogue& t_c_pb, transport_catalogue::TransportCatalogue& t_c);
        void DeserializeRenderer(transport_catalogue_pb::RenderSettings& render_settings, renderer::MapRenderer& map_renderer);
        void DeserializeRoutingSetting(transport_catalogue_pb::RoutingSettings& routing_settings_pb, transport_router::TransportRouter& transport_router);
        void DeserializeTransportRouter(transport_catalogue::TransportCatalogue& t_c, transport_router::TransportRouter& transport_router);
        
        void DeserializeStopToVertex(const transport_catalogue_pb::TransportRouter &transport_router_pb, transport_router::TransportRouter& transport_router);
        void DeserializeEdgeToRouteSegment(const transport_catalogue_pb::TransportRouter &transport_router_pb, transport_router::TransportRouter& transport_router);
        void DeserializeGraph(const transport_catalogue_pb::TransportRouter &transport_router_pb, transport_router::TransportRouter& transport_router);
        void DeserializeRouter(const transport_catalogue_pb::TransportRouter &transport_router_pb, transport_router::TransportRouter& transport_router);
    };
} //namespace serialization