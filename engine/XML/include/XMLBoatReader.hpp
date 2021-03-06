#pragma once
#include "Boat.hpp"
#include "XMLItemReader.hpp"

class XMLBoatReader : public XMLItemReader
{
  public:
    XMLBoatReader();
    ~XMLBoatReader();
  
  protected:
    friend class XMLItemsReader;
    void parse(BoatPtr boat, GenerationValues& gv, const XMLNode& boat_node, const bool force_ascii);
};

