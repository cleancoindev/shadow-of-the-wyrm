#include "CriticalHitTypeCalculator.hpp"
#include "MightyHitTypeCalculator.hpp"
#include "RegularHitTypeCalculator.hpp"
#include "IHitTypeFactory.hpp"

IHitTypeFactory::IHitTypeFactory()
{
}

IHitTypeCalculatorPtr IHitTypeFactory::create_hit_type(const HitTypeEnum hit_type)
{
  IHitTypeCalculatorPtr hit_calc;

  switch(hit_type)
  {
    case HitTypeEnum::HIT_TYPE_REGULAR:
      hit_calc = std::make_unique<RegularHitTypeCalculator>();
      break;
    case HitTypeEnum::HIT_TYPE_MIGHTY:
      hit_calc = std::make_unique<MightyHitTypeCalculator>();
      break;
    case HitTypeEnum::HIT_TYPE_CRITICAL:
      hit_calc = std::make_unique<CriticalHitTypeCalculator>();
      break;
  }

  return hit_calc;
}
