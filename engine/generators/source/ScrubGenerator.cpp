#include "ScrubGenerator.hpp"
#include "TileGenerator.hpp"
#include "GameUtils.hpp"
#include "GeneratorUtils.hpp"
#include "RNG.hpp"

ScrubGenerator::ScrubGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id, TileType::TILE_TYPE_SCRUB)
{
}

MapPtr ScrubGenerator::generate(const Dimensions& dimensions)
{
  MapPtr result_map = std::make_shared<Map>(dimensions);

  int rows = dimensions.get_y();
  int cols = dimensions.get_x();

  for (int row = 0; row < rows; row++)
  {
    for (int col = 0; col < cols; col++)
    {
      TilePtr current_tile = generate_tile(result_map, row, col);
      result_map->insert(row, col, current_tile);
    }
  }

  if (RNG::percent_chance(15))
  {
    int gr_row = RNG::range(0, rows - 1);
    int gr_col = RNG::range(0, cols - 1);

    TilePtr grave_or_barrow = GeneratorUtils::generate_grave_or_barrow();
    result_map->insert(gr_row, gr_col, grave_or_barrow);
    result_map->set_permanent(true);
  }
  
  return result_map;
}

// Scrubland is mostly dead grass with a few small bushes thrown in.
TilePtr ScrubGenerator::generate_tile(MapPtr result_map, const int row, const int col)
{
  TilePtr generated_tile;

  int rand = RNG::range(1, 100);

  if (rand < 98)
  {
    generated_tile = tg.generate(TileType::TILE_TYPE_SCRUB);
  }
  else
  {
    generated_tile = tg.generate(TileType::TILE_TYPE_BUSH);
  }

  return generated_tile;
}
