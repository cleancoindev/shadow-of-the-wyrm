#pragma once

enum struct ConductType
{
  CONDUCT_TYPE_FOODLESS = 0,
  CONDUCT_TYPE_VEGETARIAN = 1,
  CONDUCT_TYPE_CORPSELESS = 2,
  CONDUCT_TYPE_AGNOSTIC = 3,
  CONDUCT_TYPE_ILLITERATE = 4,
  CONDUCT_TYPE_WEAPONLESS = 5, // Never hits something with a weapon, rather than not wielding one.
  CONDUCT_TYPE_NO_GRAVEDIGGING = 6,
  CONDUCT_TYPE_QUESTLESS = 7,
  CONDUCT_TYPE_SILENT = 8,
  CONDUCT_TYPE_ARTIFACTLESS = 9, // Never equips an artifact
  CONDUCT_SIZE = 10
};

