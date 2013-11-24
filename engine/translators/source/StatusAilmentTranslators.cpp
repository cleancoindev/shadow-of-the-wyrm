#include "Conversion.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StatusAilmentTranslators.hpp"
#include "StringTable.hpp"
#include "StatusTypes.hpp"

using namespace std;

// Hunger

map<HungerLevel, string> HungerStatusAilmentTranslator::text_sid_map;
map<HungerLevel, Colour> HungerStatusAilmentTranslator::colour_map;

// Initialize the text SIDs
void HungerStatusAilmentTranslator::initialize_text_sid_map()
{
  text_sid_map.clear();
  text_sid_map = map<HungerLevel, string>{{HUNGER_LEVEL_STUFFED, StatusAilmentTextKeys::STATUS_HUNGER_STUFFED},
                                          {HUNGER_LEVEL_FULL, StatusAilmentTextKeys::STATUS_HUNGER_FULL},
                                          {HUNGER_LEVEL_NORMAL, StatusAilmentTextKeys::STATUS_HUNGER_NORMAL},
                                          {HUNGER_LEVEL_HUNGRY, StatusAilmentTextKeys::STATUS_HUNGER_HUNGRY},
                                          {HUNGER_LEVEL_STARVING, StatusAilmentTextKeys::STATUS_HUNGER_STARVING},
                                          {HUNGER_LEVEL_DYING, StatusAilmentTextKeys::STATUS_HUNGER_DYING}};
}

// Initialize the colour mapping
void HungerStatusAilmentTranslator::initialize_colour_map()
{
  colour_map.clear();
  colour_map = map<HungerLevel, Colour>{{HUNGER_LEVEL_STUFFED, COLOUR_WHITE},
                                        {HUNGER_LEVEL_FULL, COLOUR_WHITE},
                                        {HUNGER_LEVEL_NORMAL, COLOUR_WHITE},
                                        {HUNGER_LEVEL_HUNGRY, COLOUR_WHITE},
                                        {HUNGER_LEVEL_STARVING, COLOUR_BOLD_YELLOW},
                                        {HUNGER_LEVEL_DYING, COLOUR_RED}};
}

// Check to see if the hunger level is anything other than normal.
bool HungerStatusAilmentTranslator::has_ailment(const CreaturePtr& creature) const
{
  bool ailment = false;

  if (creature)
  {
    HungerClock clock = creature->get_hunger_clock();

    ailment = (HungerLevelConverter::to_hunger_level(clock.get_hunger()) != HUNGER_LEVEL_NORMAL);
  }

  return ailment;
}

string HungerStatusAilmentTranslator::get_status_ailment_text(const CreaturePtr& creature) const
{
  string hunger_text;

  if (text_sid_map.empty())
  {
    initialize_text_sid_map();
  }

  if (has_ailment(creature))
  {
    hunger_text = StringTable::get(text_sid_map[HungerLevelConverter::to_hunger_level(creature->get_hunger_clock().get_hunger())]);
  }

  return hunger_text;
}

Colour HungerStatusAilmentTranslator::get_status_ailment_colour(const CreaturePtr& creature) const
{
  Colour colour = COLOUR_WHITE;

  if (colour_map.empty())
  {
    initialize_colour_map();
  }

  return colour_map[HungerLevelConverter::to_hunger_level(creature->get_hunger_clock().get_hunger())];
}

StatusAilmentTranslator::StatusAilmentTranslator(const string& id, const string& t_sid, const Colour c)
: identifier(id), text_sid(t_sid), colour(c)
{
}

bool StatusAilmentTranslator::has_ailment(const CreaturePtr& creature) const
{
  bool ailment = creature && creature->has_status(identifier);

  return ailment;
}

string StatusAilmentTranslator::get_status_ailment_text(const CreaturePtr& creature) const
{
  return StringTable::get(text_sid);
}

Colour StatusAilmentTranslator::get_status_ailment_colour(const CreaturePtr& creature) const
{
  return colour;
}

