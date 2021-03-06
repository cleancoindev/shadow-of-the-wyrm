#pragma once
#include <map>
#include "ISeason.hpp"
#include "Date.hpp"

using SeasonSerializationMap = std::map<ClassIdentifier, ISeasonPtr>;

class SeasonFactory
{
  public:
    static ISeasonPtr create_season(const Season season);
    static ISeasonPtr create_season(const uint month_of_year);
    static ISeasonPtr create_season(const ClassIdentifier ci);

  protected:
    SeasonFactory();
    ~SeasonFactory();

    static void initialize_season_map();

    static SeasonSerializationMap season_map;
};
