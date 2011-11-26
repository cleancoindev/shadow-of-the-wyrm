#pragma once

enum SkillType
{
  SKILL_GENERAL_BEGIN = -1,
  SKILL_GENERAL_ARCHERY = 0,
  SKILL_GENERAL_AWARENESS = 1,
  SKILL_GENERAL_BARGAINING = 2,
  SKILL_GENERAL_BEASTMASTERY = 3,
  SKILL_GENERAL_BLIND_FIGHTING = 4,
  SKILL_GENERAL_BOATING = 5,
  SKILL_GENERAL_BOWYER = 6,
  SKILL_GENERAL_BREWING = 7,
  SKILL_GENERAL_CANTRIPS = 8,
  SKILL_GENERAL_CARRYING = 9,
  SKILL_GENERAL_COMBAT = 10,
  SKILL_GENERAL_CRAFTING = 11,
  SKILL_GENERAL_DESERT_LORE = 12,
  SKILL_GENERAL_DETECTION = 13,
  SKILL_GENERAL_DISARM_TRAPS = 14,
  SKILL_GENERAL_DUAL_WIELD = 15,
  SKILL_GENERAL_DUNGEONEERING = 16,
  SKILL_GENERAL_ESCAPE = 17,
  SKILL_GENERAL_FISHING = 18,
  SKILL_GENERAL_FLETCHERY = 19,
  SKILL_GENERAL_FORAGING = 20,
  SKILL_GENERAL_FOREST_LORE = 21,
  SKILL_GENERAL_HERBALISM = 22,
  SKILL_GENERAL_HIDING = 23,
  SKILL_GENERAL_HUNTING = 24,
  SKILL_GENERAL_INTIMIDATION = 25,
  SKILL_GENERAL_JEWELER = 26,
  SKILL_GENERAL_JUMPING = 27,
  SKILL_GENERAL_LEADERSHIP = 28,
  SKILL_GENERAL_LITERACY = 29,
  SKILL_GENERAL_LORE = 30,
  SKILL_GENERAL_MAGIC = 31,
  SKILL_GENERAL_MARSH_LORE = 32,
  SKILL_GENERAL_MEDICINE = 33,
  SKILL_GENERAL_MOUNTAIN_LORE = 34,
  SKILL_GENERAL_MOUNTAINEERING = 35,
  SKILL_GENERAL_MUSIC = 36,
  SKILL_GENERAL_NIGHT_SIGHT = 37,
  SKILL_GENERAL_OCEANOGRAPHY = 38,
  SKILL_GENERAL_PAPERCRAFT = 39,
  SKILL_GENERAL_RELIGION = 40,
  SKILL_GENERAL_SCRIBING = 41,
  SKILL_GENERAL_SKINNING = 42,
  SKILL_GENERAL_SMITHING = 43,
  SKILL_GENERAL_SPELUNKING = 44,
  SKILL_GENERAL_STEALTH = 45,
  SKILL_GENERAL_SWIMMING = 46,
  SKILL_GENERAL_TANNING = 47,
  SKILL_GENERAL_THIEVERY = 48,
  SKILL_GENERAL_WEAVING = 49,
  SKILL_GENERAL_LAST = 50,

  SKILL_MELEE_BEGIN = 999,
  SKILL_MELEE_AXES = 1000,
  SKILL_MELEE_SHORT_BLADES = 1001,
  SKILL_MELEE_LONG_BLADES = 1002,
  SKILL_MELEE_BLUDGEONS = 1003,
  SKILL_MELEE_DAGGERS = 1004,
  SKILL_MELEE_RODS_AND_STAVES = 1005,
  SKILL_MELEE_SPEARS = 1006,
  SKILL_MELEE_UNARMED = 1007,
  SKILL_MELEE_WHIPS = 1008,
  SKILL_MELEE_LAST = 1009,

  SKILL_RANGED_BEGIN = 1999,
  SKILL_RANGED_AXES = 2000,
  SKILL_RANGED_BLADES = 2001,
  SKILL_RANGED_BLUDGEONS = 2002,
  SKILL_RANGED_BOWS = 2003,
  SKILL_RANGED_CROSSBOWS = 2004,
  SKILL_RANGED_DAGGERS = 2005,
  SKILL_RANGED_ROCKS = 2006,
  SKILL_RANGED_SLINGS = 2007,
  SKILL_RANGED_SPEARS = 2008,
  SKILL_RANGED_LAST = 2009,

  SKILL_MAGIC_BEGIN = 2999,
  SKILL_MAGIC_ARCANE = 3000,
  SKILL_MAGIC_DIVINE = 3001,
  SKILL_MAGIC_MYSTIC = 3002,
  SKILL_MAGIC_PRIMORDIAL = 3003,
  SKILL_MAGIC_LAST = 3004
};

enum SkillCategory
{
  SKILL_CATEGORY_UNDEFINED = -1,
  SKILL_CATEGORY_GENERAL = 0,
  SKILL_CATEGORY_MELEE = 1,
  SKILL_CATEGORY_RANGED = 2,
  SKILL_CATEGORY_MAGIC = 3
};

inline SkillType operator--(SkillType &st, int)
{
  return st = SkillType(st-1);
}

inline SkillType operator++(SkillType &st, int)
{
  return st = SkillType(st+1);
}
