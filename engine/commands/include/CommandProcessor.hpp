#pragma once
#include "ActionCost.hpp"
#include "Commands.hpp"
#include "Creature.hpp"
#include "Display.hpp"
#include "Game.hpp"

// Return values of true mean "advance to next creature".  false indicates
// failure, and that the creature should be allowed to repeat.  Things like
// checking the game version, trying to move off the world map, etc., will
// return false.  Successfully moving, attacking, etc., return true.
class CommandProcessor
{
  public:
    static ActionCost process(CreaturePtr creature, CommandPtr command, DisplayPtr display);

  protected:
    CommandProcessor();
    ~CommandProcessor();

    static ActionCost process_command(CreaturePtr creature, Command* command, DisplayPtr display);
    static ActionCost process_directional_command(CreaturePtr creature, DirectionalCommand* command, DisplayPtr display);
    static ActionCost process_spell_casting_command(CreaturePtr creature, Command* command, Game& game);
    static bool process_confirmation(CreaturePtr creature, Command* command, DisplayPtr display);
};
