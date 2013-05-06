#pragma once
#include "Generator.hpp"

class SeaGenerator : public SL::Generator
{
  public:
    SeaGenerator(const std::string& map_exit_id);
    
    virtual MapPtr generate(const Dimensions& dim);
};
