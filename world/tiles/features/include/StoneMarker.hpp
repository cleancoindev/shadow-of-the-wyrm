#pragma once
#include "Feature.hpp"
#include "Symbol.hpp"

class StoneMarker : public Feature
{
  public:
    StoneMarker(const Symbol& new_symbol);
    virtual Feature* clone() override;

    bool operator==(const StoneMarker& t) const;

    virtual float get_hp_regeneration_multiplier() const override;
    virtual float get_ap_regeneration_multiplier() const override;

  protected:
    virtual std::string get_description_sid() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

