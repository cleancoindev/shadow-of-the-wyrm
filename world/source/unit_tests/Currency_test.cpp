#include "gtest/gtest.h"

TEST(SW_World_Currency, serialization_id)
{
  Currency currency;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_CURRENCY, currency.get_class_identifier());
}

TEST(SW_World_Currency, saveload)
{
  Currency currency, currency2;

  currency.set_quantity(5000);

  ostringstream ss;

  currency.serialize(ss);

  istringstream iss(ss.str());

  currency2.deserialize(iss);

  EXPECT_TRUE(currency == currency2);
}
