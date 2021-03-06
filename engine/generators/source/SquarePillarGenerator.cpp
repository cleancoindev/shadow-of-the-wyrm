#include "SquarePillarGenerator.hpp"
#include "TileGenerator.hpp"

int SquarePillarGenerator::get_height() const
{
  return 2;
}

int SquarePillarGenerator::get_width() const
{
  return 2;
}

// Generate a square pillar and insert it into the map.
void SquarePillarGenerator::generate(MapPtr map, const int y_topleft, const int x_topleft)
{
  int end_y = y_topleft + get_height() - 1;
  int end_x = x_topleft + get_width() - 1;

  TileGenerator tg;
  TilePtr tile;
  for (int y = y_topleft; y <= end_y; y++)
  {
    for (int x = x_topleft; x <= end_x; x++)
    {
      tile = tg.generate(TileType::TILE_TYPE_ROCK);
      map->insert(y, x, tile);
    }
  }
}

#ifdef UNIT_TESTS
#include "unit_tests/SquarePillarGenerator_test.cpp"
#endif