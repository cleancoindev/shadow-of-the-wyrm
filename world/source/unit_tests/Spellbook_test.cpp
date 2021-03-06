#include "gtest/gtest.h"

TEST(SW_World_Spellbook, serialization_id)
{
  Spellbook book;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_SPELLBOOK, book.get_class_identifier());
}

TEST(SW_World_Spellbook, saveload)
{
  Spellbook book, book2;

  book.set_unidentified_description_sid("serialize_break_test!");
  book.set_spell_id("big_spell");
  book.set_difficulty(105);
  book.set_text_sid("fdsafdsa");

  ostringstream ss;

  book.serialize(ss);

  istringstream iss(ss.str());

  book2.deserialize(iss);

  EXPECT_TRUE(book == book2);

  book.set_text_sid("not a match");

  EXPECT_FALSE(book == book2);
}
