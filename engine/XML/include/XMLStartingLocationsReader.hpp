#pragma once
#include <map>
#include "StartingLocation.hpp"
#include "XMLReader.hpp"

class XMLStartingLocationsReader : public XMLReader
{
  public:
    StartingLocationMap get_starting_locations(const XMLNode& starting_locations_node);

  protected:
    void parse_starting_location(StartingLocation& sl, const XMLNode& starting_location_node);
};
