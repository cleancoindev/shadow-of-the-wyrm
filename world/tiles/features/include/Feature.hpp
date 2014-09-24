#pragma once
#include <vector>
#include <memory>
#include "common.hpp"
#include "Lock.hpp"
#include "Trap.hpp"
#include "Material.hpp"
#include "ISerializable.hpp"

class Tile;
class Creature;

// An abstract base class representing a dungeon feature.  A feature is
// like an item, but cannot move.  Examples include fireplaces, thrones,
// bookshelves, levers, etc.
//
// Features can be trapped.
class Feature : public ISerializable
{
  public:
    Feature(const MaterialType new_material);
    Feature(const Feature& feature);
    Feature& operator=(const Feature& feature);

    virtual ~Feature() {};
    virtual Feature* clone() = 0;
    virtual bool operator==(const Feature& feature) const;

    // If a feature is blocking, the square it occupies cannot be
    // occupied by another creature, and any items thrown, kicked, etc.,
    // in its direction will stop before reaching the tile.
    virtual bool get_is_blocking() const;

    // Display information.
    virtual uchar get_symbol()  const = 0;
    virtual Colour get_colour() const; // by default, use the material's colour.
    
    virtual bool has_trap() const;
    virtual void set_trap(TrapPtr new_trap);
    virtual TrapPtr get_trap();

    virtual void set_lock(LockPtr new_lock);
    virtual LockPtr get_lock();

    virtual void set_material_type(const MaterialType new_material);
    virtual MaterialType get_material_type() const;

    virtual std::pair<std::string, std::vector<std::string>> get_description_and_replacement_sids() const;
    
    virtual bool can_offer() const;
    virtual bool can_open() const;
    virtual bool can_lock() const;

    virtual bool kick() = 0;
    virtual bool offer();
    virtual bool open();

    // Can the feature be handled, given whether the tile it is on is
    // currently occupied?
    virtual bool can_handle(const bool feature_tile_occupied) const;

    // Handling a feature can affect the tile on which the feature is present,
    // so include that as a parameter.  Include the creature so that if a message
    // is added (e.g., "You pour yourself a drink!" or "The goblin pours himself
    // a drink!"), the correct message can be added based on the creature, and
    // whether the creature is the player or not.
    virtual bool handle(std::shared_ptr<Tile> tile, std::shared_ptr<Creature> creature) = 0;

    // Potential handle message for the current feature.
    // By default, returns the empty SID.
    virtual std::string get_handle_message_sid() const;

    virtual float get_piety_loss_multiplier() const;

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

  protected:
    virtual std::string get_description_sid() const = 0;

    TrapPtr trap;
    LockPtr lock;
    MaterialType material;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

typedef std::shared_ptr<Feature> FeaturePtr;
