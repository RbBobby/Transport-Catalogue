#pragma once
#include <vector>

#include "transport_catalogue.h"
#include "log_duration.h"

namespace transport_catalogue {
	namespace input {
		class InputReader {
		public:
			InputReader(std::istream& input, TransportCatalogue& transport_catalogue);
		private:
			void CreateRequestList(std::istream& input);
			void AddStops(TransportCatalogue& transport_catalogue);
			void AddBusses(TransportCatalogue& transport_catalogue);
			void AddStopsLength(TransportCatalogue& transport_catalogue);
			std::vector<std::pair<std::string, std::string>> stops_and_buses_;
		};
	}
}