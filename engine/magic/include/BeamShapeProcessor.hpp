#pragma once
#include "SpellShapeProcessor.hpp"

// A class for processing beam-type spells.
class BeamShapeProcessor : public SpellShapeProcessor
{
  protected:
    virtual std::vector<TilePtr> get_affected_tiles_for_spell(MapPtr map, const Coordinate& caster_coord, const Direction d, const Spell& spell);
};

