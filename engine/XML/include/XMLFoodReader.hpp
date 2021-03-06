#pragma once
#include "Food.hpp"
#include "XMLConsumableReader.hpp"

// JCD FIXME: Define a Consumable reader.
// Then, change the inherited class for plant and food...
class XMLFoodReader : public XMLConsumableReader
{
  public:
    XMLFoodReader();
    ~XMLFoodReader();
    
  protected:
    friend class XMLItemsReader;
    void parse(FoodPtr food, GenerationValues& gv, const XMLNode& food_node, const bool force_ascii);
};

