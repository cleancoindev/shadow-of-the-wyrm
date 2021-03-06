#pragma once
#include "AltarManipulator.hpp"

class EvilAltarManipulator : public AltarManipulator
{
  public:
    EvilAltarManipulator(FeaturePtr feature);

    std::string get_creature_action_key() const override;
};

