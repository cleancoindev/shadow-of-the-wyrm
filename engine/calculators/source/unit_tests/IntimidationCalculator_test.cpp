#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_IntimidationCalculator, calculate_pct_chance_intimidated)
{
  CreaturePtr attacking_creature;
  CreaturePtr attacked_creature;
  IntimidationCalculator ic;

  EXPECT_EQ(0, ic.calculate_pct_chance_intimidated(attacking_creature, attacked_creature));

  // The attacked creature doesn't have intimidation.
  attacking_creature = std::make_shared<Creature>();
  attacked_creature = std::make_shared<Creature>();
  Statistic attacker_cha(20);
  Statistic attacked_cha(28);

  attacking_creature->get_skills().set_value(SkillType::SKILL_GENERAL_INTIMIDATION, 30);
  attacking_creature->set_charisma(attacker_cha);

  EXPECT_EQ(0, ic.calculate_pct_chance_intimidated(attacking_creature, attacked_creature));

  // The attacked creature has intimidation.
  attacked_creature->get_skills().set_value(SkillType::SKILL_GENERAL_INTIMIDATION, 100);
  attacked_creature->set_charisma(attacked_cha);

  // Ensure the basic opposed calculation works.
  EXPECT_EQ(25, ic.calculate_pct_chance_intimidated(attacking_creature, attacked_creature));
}