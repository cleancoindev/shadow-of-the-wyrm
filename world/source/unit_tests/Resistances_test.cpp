#include "gtest/gtest.h"
#include "ResistanceFactory.hpp"

TEST(SL_World_Resistances, serialization_id)
{
  Resistances resistances;

  EXPECT_EQ(CLASS_ID_RESISTANCES, resistances.get_class_identifier());
}

TEST(SL_World_Resistances, serialization_ids_for_individual_types)
{
  SlashResistance sr;
  PierceResistance pr;
  PoundResistance pr2;
  HeatResistance hr;
  ColdResistance cr;
  AcidResistance ar;
  PoisonResistance pr3;
  HolyResistance hr2;
  ShadowResistance sr2;
  ArcaneResistance ar2;
  LightningResistance lr;

  EXPECT_EQ(CLASS_ID_SLASH_RESISTANCE, sr.get_class_identifier());
  EXPECT_EQ(CLASS_ID_PIERCE_RESISTANCE, pr.get_class_identifier());
  EXPECT_EQ(CLASS_ID_POUND_RESISTANCE, pr2.get_class_identifier());
  EXPECT_EQ(CLASS_ID_HEAT_RESISTANCE, hr.get_class_identifier());
  EXPECT_EQ(CLASS_ID_COLD_RESISTANCE, cr.get_class_identifier());
  EXPECT_EQ(CLASS_ID_ACID_RESISTANCE, ar.get_class_identifier());
  EXPECT_EQ(CLASS_ID_POISON_RESISTANCE, pr3.get_class_identifier());
  EXPECT_EQ(CLASS_ID_HOLY_RESISTANCE, hr2.get_class_identifier());
  EXPECT_EQ(CLASS_ID_SHADOW_RESISTANCE, sr2.get_class_identifier());
  EXPECT_EQ(CLASS_ID_ARCANE_RESISTANCE, ar2.get_class_identifier());
  EXPECT_EQ(CLASS_ID_LIGHTNING_RESISTANCE, lr.get_class_identifier());
}

TEST(SL_World_Resistances, saveload)
{
  for (int i = CLASS_ID_SLASH_RESISTANCE; i <= CLASS_ID_LIGHTNING_RESISTANCE; i++)
  {
    boost::shared_ptr<Resistance> res1, res2;
    res1 = ResistanceFactory::create_resistance(static_cast<ClassIdentifier>(i));
    res2 = ResistanceFactory::create_resistance(static_cast<ClassIdentifier>(i));

    res1->set_value(0.23);

    ostringstream ss;

    res1->serialize(ss);

    istringstream iss(ss.str());

    res2->deserialize(iss);

    EXPECT_TRUE(*res1 == *res2);
  }
}
