#include "CreatureAlcoholTimer.hpp"
#include "CreatureAPRegeneration.hpp"
#include "CreatureHPRegeneration.hpp"
#include "CreatureHungerTimer.hpp"
#include "CreaturePietyRegeneration.hpp"
#include "CreatureSkillIncrementer.hpp"
#include "CreatureSkillMarkerChecker.hpp"
#include "CreatureStatsIncrementer.hpp"
#include "CreatureStatisticsMarkerChecker.hpp"
#include "CreatureModifiers.hpp"
#include "CreatureStatuses.hpp"
#include "CreatureTimeObserver.hpp"
#include "Game.hpp"
#include "MapUtils.hpp"
#include "MovementAccumulationChecker.hpp"
#include "MovementAccumulator.hpp"
#include "RegenerationConstants.hpp"
#include "Serialize.hpp"

using namespace std;

CreatureTimeObserver::CreatureTimeObserver()
: ITimeObserver()
{
  initialize_regeneration_helpers();
}

// Set the list of regeneration helpers to apply to each creature on each "tick" (1 min passed)
void CreatureTimeObserver::initialize_regeneration_helpers()
{
  regen.clear();

  // Regenerate the creature's HP
  ICreatureRegenerationPtr hp_regen     = std::make_shared<CreatureHPRegeneration>();
  // Regenerate the creature's AP
  ICreatureRegenerationPtr ap_regen     = std::make_shared<CreatureAPRegeneration>();
  // Regenerate or degenerate the creature's piety, depending on the value.
  ICreatureRegenerationPtr piety_regen  = std::make_shared<CreaturePietyRegeneration>();
  // Update the minute values for the current movement accumulations.
  ICreatureRegenerationPtr move_accum   = std::make_shared<MovementAccumulator>();
  // Do things based on current movement accumulations - drown, fall from mountains, etc.
  ICreatureRegenerationPtr move_checkr  = std::make_shared<MovementAccumulationChecker>();
  // Every two days, increment each creature's stats if they've been exercised enough.
  ICreatureRegenerationPtr stats_checkr = std::make_shared<CreatureStatsIncrementer>(2880);
  // Every day, increment the creature's skills if they have been used enough.
  ICreatureRegenerationPtr skill_checkr = std::make_shared<CreatureSkillIncrementer>(1440);
  // Every minute, check to see if the creature has modifiers that should be removed.
  ICreatureRegenerationPtr mod_chkr = std::make_shared<CreatureModifiers>();
  // Every minute, reduce the player's hunger clock...
  ICreatureRegenerationPtr hungr_checkr = std::make_shared<CreatureHungerTimer>();
  // Every minute, call the tick() function for each status the creature has.
  ICreatureRegenerationPtr status_chekr = std::make_shared<CreatureStatuses>();
  // Every half an hour to an hour, do alcohol absorption and metabolism.
  ICreatureRegenerationPtr alcohol_chkr = std::make_shared<CreatureAlcoholTimer>();
  // Every few hours, check to see if the creature meets any of the conditions
  // for marking statistics.
  ICreatureRegenerationPtr st_mark_chkr = std::make_shared<CreatureStatisticsMarkerChecker>(360);
  // Every few hours, do the same, but for miscellaneous skills (like Carrying).
  ICreatureRegenerationPtr sk_mark_chkr = std::make_shared<CreatureSkillMarkerChecker>(360);

  regen.push_back(hp_regen    );
  regen.push_back(ap_regen    );
  regen.push_back(piety_regen );
  regen.push_back(move_accum  );
  regen.push_back(move_checkr );
  regen.push_back(stats_checkr);
  regen.push_back(skill_checkr);
  regen.push_back(mod_chkr    );
  regen.push_back(hungr_checkr);
  regen.push_back(status_chekr);
  regen.push_back(alcohol_chkr);
  regen.push_back(st_mark_chkr);
  regen.push_back(sk_mark_chkr);
}

void CreatureTimeObserver::notify(const ulonglong minutes_this_tick)
{
  update_minutes_elapsed(minutes_this_tick);

  Game& game = Game::instance();

  // Get the list of creatures.
  MapPtr current_map = game.get_current_map();
  map<string, CreaturePtr> creatures = current_map->get_creatures();
    
  // Apply each creature regeneration helper to each creature on the map
  for (map<string, CreaturePtr>::iterator c_it = creatures.begin(); c_it != creatures.end(); c_it++)
  {
    CreaturePtr creature = c_it->second;
    TilePtr tile = MapUtils::get_tile_for_creature(current_map, creature);
      
    for (ICreatureRegenerationPtr regen_helper : regen)
    {
      if (game.should_keep_playing() && creature != nullptr)
      {
        if (regen_helper)
        {
          regen_helper->tick(creature, tile, minutes_this_tick, minutes_elapsed); 
        }
      }
      else
      {
        return;
      }
    }
  }
}

ITimeObserver* CreatureTimeObserver::clone()
{
  CreatureTimeObserver* creature_observer = new CreatureTimeObserver(*this);

  // Ensure that the new CreatureTimeObserver points to a *different*
  // set of regeneration helpers than the current object.
  if (creature_observer != nullptr)
  {
    creature_observer->initialize_regeneration_helpers();
  }

  return creature_observer;
}

// No need to serialize the vector - a new list gets built up each time the object is created,
// and it's never actually updated (yet, anyway).
bool CreatureTimeObserver::serialize(ostream& stream) const
{
  ITimeObserver::serialize(stream);

  return true;
}

// See serialization note.
bool CreatureTimeObserver::deserialize(istream& stream)
{
  ITimeObserver::deserialize(stream);

  return true;
}

ClassIdentifier CreatureTimeObserver::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_CREATURE_TIME_OBSERVER;
}

#ifdef UNIT_TESTS
#include "unit_tests/CreatureTimeObserver_test.cpp"
#endif

