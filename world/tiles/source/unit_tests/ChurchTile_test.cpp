#include "gtest/gtest.h"

TEST(SW_World_Tiles_ChurchTile, type_is_TILE_TYPE_CHURCH)
{
  ChurchTile church_tile;

  EXPECT_EQ(TileType::TILE_TYPE_CHURCH, church_tile.get_tile_type());
}

TEST(SW_World_Tiles_ChurchTile, tile_description_sid)
{
  ChurchTile church_tile;

  EXPECT_EQ(TileTextKeys::TILE_DESC_CHURCH, church_tile.get_tile_description_sid());
}

TEST(SW_World_Tiles_ChurchTile, worship_site_deity_id)
{
  ChurchTile church_tile;

  EXPECT_EQ("", church_tile.get_deity_id());

  church_tile.set_deity_id("test");

  EXPECT_EQ("test", church_tile.get_deity_id());
}

TEST(SW_World_Tiles_ChurchTile, serialization_id)
{
  ChurchTile church_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_CHURCH_TILE, church_tile.get_class_identifier());
}

