#pragma once
#include <iostream>

#include "transport_catalogue.h"
#include "log_duration.h"


namespace transport_catalogue {
	namespace stat {
		class StatReader {
		public:
			StatReader(std::istream& input, std::ostream& output, TransportCatalogue& transport_catalogue);
		private:
			double CalculateRouteLengthCoordinate(const Bus* bus) const;
			double CalculateRouteLength(const TransportCatalogue& transport_catalogue, const Bus* bus) const;
			void WriteBusInfo(std::ostream& output, const TransportCatalogue& transport_catalogue, const std::string& text);
			void WriteStopInfo(std::ostream& output, const TransportCatalogue& transport_catalogue, const std::string& text);
		};
	}
}