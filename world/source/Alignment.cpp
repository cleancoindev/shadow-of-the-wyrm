#include "Alignment.hpp"
#include "Serialize.hpp"

using namespace std;

// Static const members.  These define the maximum range for an alignment,
// as well as the ranges for the various good/neutral/evil types.
const int Alignment::ALIGNMENT_MIN = -2500;
const int Alignment::ALIGNMENT_MAX = 2500;
const int Alignment::EVIL_MIN = -2500;
const int Alignment::EVIL_MAX = -751;
const int Alignment::NEUTRAL_MIN = -750;
const int Alignment::NEUTRAL_MAX = 750;
const int Alignment::GOOD_MIN = 751;
const int Alignment::GOOD_MAX = 2500;


Alignment::Alignment()
: alignment(0)
{
}

Alignment::Alignment(const int new_alignment)
: alignment(new_alignment)
{
}

bool Alignment::operator==(const Alignment& a) const
{
  bool result = true;

  result = result && alignment == a.alignment;

  return result;
}

// Set/get the alignment
void Alignment::set_alignment(const int new_alignment)
{
  if (new_alignment >= ALIGNMENT_MIN && new_alignment <= ALIGNMENT_MAX)
  {
    alignment = new_alignment;
  }
}

int Alignment::get_alignment() const
{
  return alignment;
}

int& Alignment::get_alignment_ref()
{
  return alignment;
}

// Get the alignment range, based off the raw alignment.
AlignmentRange Alignment::get_alignment_range() const
{
  // Default to neutral.
  AlignmentRange align_range;

  if (alignment >= EVIL_MIN && alignment <= EVIL_MAX)
  {
    align_range = ALIGNMENT_RANGE_EVIL;
  }
  else if (alignment >= GOOD_MIN && alignment <= GOOD_MAX)
  {
    align_range = ALIGNMENT_RANGE_GOOD;
  }
  else
  {
    align_range = ALIGNMENT_RANGE_NEUTRAL;
  }

  return align_range;
}

bool Alignment::serialize(ostream& stream) const
{
  Serialize::write_int(stream, alignment);

  return true;
}

bool Alignment::deserialize(istream& stream)
{
  Serialize::read_int(stream, alignment);

  return true;
}

ClassIdentifier Alignment::internal_class_identifier() const
{
  return CLASS_ID_ALIGNMENT;
}

#ifdef UNIT_TESTS
#include "unit_tests/Alignment_test.cpp"
#endif
