#include "gtest/gtest.h"

TEST(SW_World_AutomaticMovement, engaged_status)
{
  AutomaticMovement am;

  am.set_direction(Direction::DIRECTION_NORTH);
  am.set_engaged(false);

  EXPECT_FALSE(am.get_engaged());

  am.set_engaged(true);

  EXPECT_TRUE(am.get_engaged());

  am.set_direction(Direction::DIRECTION_NULL);

  EXPECT_FALSE(am.get_engaged());

  am.set_direction(Direction::DIRECTION_UP);

  EXPECT_FALSE(am.get_engaged());

  am.set_direction(Direction::DIRECTION_DOWN);

  EXPECT_FALSE(am.get_engaged());

  am.set_direction(Direction::DIRECTION_NORTH_WEST);

  EXPECT_TRUE(am.get_engaged());

  am.set_turns(12);

  am.set_direction(Direction::DIRECTION_NULL);

  EXPECT_TRUE(am.get_engaged());

  am.set_direction(Direction::DIRECTION_UP);

  EXPECT_TRUE(am.get_engaged());

  am.set_direction(Direction::DIRECTION_DOWN);

  EXPECT_TRUE(am.get_engaged());
}

TEST(SW_World_AutomaticMovement, turn_counter)
{
  AutomaticMovement am;

  am.set_engaged(true);
  am.set_turns(15);

  EXPECT_EQ(15, am.get_turns());

  am.set_engaged(false);

  EXPECT_EQ(-1, am.get_turns());
}

TEST(SW_World_AutomaticMovement, serialization_id)
{
  AutomaticMovement auto_move;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_AUTOMATIC_MOVEMENT, auto_move.get_class_identifier());
}

TEST(SW_World_AutomaticMovement, saveload)
{
  AutomaticMovement am, am2;

  am.set_engaged(true);
  am.set_direction(Direction::DIRECTION_SOUTH_WEST);

  ostringstream oss;

  am.serialize(oss);

  istringstream iss(oss.str());

  am2.deserialize(iss);

  EXPECT_TRUE(am == am2);
}