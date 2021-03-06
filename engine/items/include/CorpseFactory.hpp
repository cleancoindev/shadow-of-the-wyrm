#pragma once
#include "Creature.hpp"
#include "Item.hpp"

// CorpseFactory is responsible for creating (or not creating) corpses,
// given a creature that's currently fixin' to die.  It takes into
// whether the creature can leave a corpse or not, etc.  This function
// returns a null ItemPtr when a corpse cannot be left.
class CorpseFactory
{
  public:
    CorpseFactory();
    ~CorpseFactory();

    ItemPtr create_corpse(CreaturePtr attacking_creature, CreaturePtr creature);

  protected:
    void initialize_size_weight_multipliers();

    void set_internal_details(CreaturePtr dead_creature, ItemPtr corpse);
    void set_display_details(CreaturePtr dead_creature, ItemPtr corpse);
    void set_weight(CreaturePtr dead_creature, ItemPtr corpse);
    void set_poisoned_if_necessary(CreaturePtr dead_creature, ItemPtr corpse);
    void set_resistances(CreaturePtr attacking_creature, CreaturePtr dead_creature, ItemPtr corpse);
    void set_additional_details(CreaturePtr dead_creature, ItemPtr corpse);

    static std::map<CreatureSize, float> size_weight_multipliers;
};

