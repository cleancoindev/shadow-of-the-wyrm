#include "Feature.hpp"

class Bed : public Feature
{
  public:
    Bed();
    virtual Feature* clone() override;

    bool operator==(const Bed& t) const;

    virtual uchar get_symbol() const override;

  protected:
    virtual std::string get_description_sid() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};
