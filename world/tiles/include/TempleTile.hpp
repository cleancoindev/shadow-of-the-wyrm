#pragma once
#include "WorshipSiteTile.hpp"

class TempleTile : public WorshipSiteTile
{
  public:
    TempleTile(const TileType subtype);
    
    TileType get_tile_type() const;

    std::string get_tile_description_sid() const;
};
