#pragma once
#include "ISerializable.hpp"

class DeityStatus : public ISerializable
{
  public:
    DeityStatus();
    ~DeityStatus();
    virtual bool operator==(const DeityStatus& status);
    
    void set_piety(const int new_piety);
    int get_piety() const;
    void increment_piety(const int inc_amount);
    void decrement_piety(const int dec_amount);

    void set_crowned(const bool new_crowned_status);
    bool get_crowned() const;

    bool serialize(std::ostream& stream);
    bool deserialize(std::istream& stream);
    
  protected:
    int piety;
    bool crowned;

  private:
    ClassIdentifier internal_class_identifier() const;
};
