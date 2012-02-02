#pragma once

// Used for player/monster movements, etc.
enum Direction
{
  DIRECTION_SOUTH_WEST = 1,
  DIRECTION_SOUTH = 2,
  DIRECTION_SOUTH_EAST = 3,
  DIRECTION_WEST = 4,
  DIRECTION_EAST = 6,
  DIRECTION_NORTH_WEST = 7,
  DIRECTION_NORTH = 8,
  DIRECTION_NORTH_EAST = 9,
  DIRECTION_UP = 10,
  DIRECTION_DOWN = 11
};

// More general - used in terrain generation, etc.
enum CardinalDirection
{
  CARDINAL_DIRECTION_NORTH = 0,
  CARDINAL_DIRECTION_EAST  = 1,
  CARDINAL_DIRECTION_SOUTH = 2,
  CARDINAL_DIRECTION_WEST  = 3
};
