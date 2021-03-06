#pragma once
#include <map>
#include <string>
#include "ISerializable.hpp"

class CreatureActionKeys
{
  public:
    static const std::string ACTION_ATTACK_FRIENDLY;
    static const std::string ACTION_CANNIBALISM;
    static const std::string ACTION_DESECRATE_GOOD; // Kicking pews, altars, etc.
    static const std::string ACTION_DESECRATE_NEUTRAL;
    static const std::string ACTION_DESECRATE_EVIL;
  	static const std::string ACTION_GRAVEROBBING;
};

using CreatureActionMap = std::map<std::string, bool>;

// Describes creature actions, which the deity can either like, dislike,
// or not care about.  Examples include using magic, attacking friendly
// creatures, eating one's own race, and so on.
class CreatureActions : public ISerializable
{
  public:
    bool operator==(const CreatureActions& ca) const;

    void set_action_value(const std::string& action, const bool val);
    bool get_action_value(const std::string& action) const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    CreatureActionMap creature_action_map;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

