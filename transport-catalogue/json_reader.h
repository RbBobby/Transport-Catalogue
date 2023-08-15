#pragma once
#include <sstream>
 
#include "json.h"
#include "map_renderer.h"
#include "request_handler.h"
#include "transport_catalogue.h"


class JsonReader {
public:

	JsonReader(std::istream& input, renderer::MapRenderer&  map_renderer);
	void ProcessRequest();
	RequestHandler GetRequestHandler()const;
	void GetStat(std::ostream& os) const;
	~JsonReader() = default;

private:	
	void WriteBusInfo(json::Dict& response, json::Dict& dict_request);
	void WriteStopInfo(json::Dict& response, json::Dict& dict_request);
	void WriteSVGInfo(json::Dict& response);
	svg::Color AddCollor(const json::Node& value_setting);

	void AddStops();
	void AddBusses();
	void AddStopsLength();
	void AddStatRequests();
	void AddRenderRettings();

	
	
	json::Document input_doc_;
	renderer::MapRenderer& map_renderer_;
	transport_catalogue::TransportCatalogue transport_catalogue_;	

	json::Array response_request_;
	RequestHandler request_handler{ transport_catalogue_, map_renderer_ };
};
