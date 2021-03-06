#include "EarthTile.hpp"
#include "ItemTypes.hpp"

using namespace std;

const int EarthTile::EARTH_TILE_HARDNESS = 1;

EarthTile::EarthTile()
: Tile(EARTH_TILE_HARDNESS)
{
}

TileType EarthTile::get_tile_type() const
{
  return TileType::TILE_TYPE_EARTH;
}

TileType EarthTile::get_decomposition_tile_type() const
{
  return TileType::TILE_TYPE_DUNGEON;
}

vector<pair<pair<int, int>, string>> EarthTile::get_decomposition_item_ids() const
{
  vector<pair<pair<int, int>, string>> result = {{{1,5}, ItemIdKeys::ITEM_ID_DIRT}};
  return result;
}

string EarthTile::get_tile_description_sid() const
{
  return TileTextKeys::TILE_DESC_EARTH;
}

int EarthTile::get_movement_multiplier() const
{
  return 0;
}

Tile* EarthTile::clone()
{
  return new EarthTile(*this);
}
ClassIdentifier EarthTile::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_EARTH_TILE;
}

#ifdef UNIT_TESTS
#include "unit_tests/EarthTile_test.cpp"
#endif
