#include <iostream>
#include <memory>
//#include <fstream>

#include "map_renderer.h"
#include "json_reader.h"
#include "request_handler.h"

using namespace transport_catalogue;

int main() {
   // std::ifstream in("input_1.json");
    renderer::MapRenderer road_map;

    JsonReader json_reader(std::cin, road_map);

    json_reader.ProcessRequest();

    RequestHandler request_handler(json_reader.GetRequestHandler());

    json_reader.GetStat(std::cout);
   // request_handler.RenderMap(std::cout);
}
    