#include "gtest/gtest.h"

TEST(SL_World_Weapon, serialization_ids)
{
  MeleeWeapon melee;
  RangedWeapon ranged;

  EXPECT_EQ(CLASS_ID_MELEE_WEAPON, melee.get_class_identifier());
  EXPECT_EQ(CLASS_ID_RANGED_WEAPON, ranged.get_class_identifier());
}

TEST(SL_World_Weapon, saveload)
{
  MeleeWeapon m, m2;
  RangedWeapon r, r2;

  ostringstream ss, ss2;

  m.set_quantity(3);
  r.set_quantity(1333);
  r.set_glowing(true);

  vector<string> slay_races;
  slay_races.push_back("elf");
  slay_races.push_back("dwarf");

  m.set_slays_races(slay_races);
  r.set_slays_races(slay_races);

  m.serialize(ss);
  r.serialize(ss2);

  istringstream iss(ss.str());
  istringstream iss2(ss2.str());

  m2.deserialize(iss);
  r2.deserialize(iss2);

  slay_races = m2.get_slays_races();
  EXPECT_TRUE(find(slay_races.begin(), slay_races.end(), "elf") != slay_races.end());
}
