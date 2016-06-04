#include "ActionTextKeys.hpp"
#include "CombatManager.hpp"
#include "MessageManager.hpp"
#include "SwimmingSkillProcessor.hpp"
#include "SwimmingCalculator.hpp"

using std::string;

// "Drown" the creature by applying swimming damage.
// If the creature is the player, display a UI message.
ActionCostValue SwimmingSkillProcessor::process(CreaturePtr creature, MapPtr map /* unused, will be nullptr */)
{
  if (creature)
  {
    string drowning_message_sid;
    
    if (creature->get_is_player())
    {
      drowning_message_sid = ActionTextKeys::ACTION_PLAYER_DROWNING;
    }
    
    CombatManager cm;
    SwimmingCalculator sc;
    CreaturePtr no_attacker;

    cm.deal_damage(no_attacker, creature, sc.calculate_swimming_damage(creature, creature->has_status(StatusIdentifiers::STATUS_ID_INCORPOREAL)), drowning_message_sid);    
  }

  return get_default_skill_action_cost_value(creature);
}