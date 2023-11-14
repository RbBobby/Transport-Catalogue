#include <iostream>
#include <sstream>
#include <memory>
#include <fstream>

#include "map_renderer.h"
#include "json_reader.h"
#include "request_handler.h"

using namespace transport_catalogue;

using namespace std::literals;

void PrintUsage(std::ostream& stream = std::cerr) {
    stream << "Usage: transp ort_catalogue [make_base|process_requests]\n"sv;
}

int main(int argc, char* argv[]) {
   
    if (argc != 2) {
        PrintUsage();
        return 1;
    } 

    const std::string_view mode(argv[1]);

    if (mode == "make_base"sv) {

      renderer::MapRenderer road_map;
      JsonReader json_reader(std::cin, road_map);

      json_reader.ProcessRequest();

    } else if (mode == "process_requests"sv) {
      
      renderer::MapRenderer road_map;
      JsonReader json_reader(std::cin, road_map);

      json_reader.GetStat(std::cout);
        // process requests here

    } else {
      std::cout << argv[1] << argv[2];
        PrintUsage();
        return 1;
    }
}

    