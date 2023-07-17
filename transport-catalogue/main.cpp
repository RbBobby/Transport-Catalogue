#include "stat_reader.h"
#include "input_reader.h"
#include "transport_catalogue.h"
#include "Test.h"

using namespace std;

int main() {
    //TestTaskData();
    //TestFileData();
    //TestOneRoute();
    //TestEmptyStopAndRoute();
    //TestTaskBData();
    //while (true) {
        TestNearbyStopsLengthData();
   // }
   TransportCatalogue transport_catalogue;
   
   InputReader Input(cin, transport_catalogue);

   StatReader Stat(cin, std::cout, transport_catalogue);

    
}


