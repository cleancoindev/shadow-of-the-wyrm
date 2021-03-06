#pragma once
#include "Readable.hpp"

class Spellbook : public Readable
{
  public:
    Spellbook();
    ~Spellbook();

    bool operator==(const Spellbook& book) const;
    
    bool destroy_on_read() const override;

    void set_spell_id(const std::string& new_spell_id);
    std::string get_spell_id() const;

    void set_difficulty(const int new_difficulty);
    int get_difficulty() const;
    
    Item* clone() override;

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

  protected:
    virtual void do_enchant_item(const int points) override;

    std::string spell_id;
    int difficulty;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

using SpellbookPtr = std::shared_ptr<Spellbook>;
