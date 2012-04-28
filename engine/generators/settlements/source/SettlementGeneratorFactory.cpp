#include <boost/make_shared.hpp>
#include "SettlementGeneratorFactory.hpp"
#include "SettlementGenerator.hpp"
#include "HamletGenerator.hpp"
#include "WalledSettlementGenerator.hpp"
#include "ScatteredSettlementGenerator.hpp"

using boost::make_shared;

SettlementGeneratorFactory::SettlementGeneratorFactory()
{
}

SettlementGeneratorFactory::~SettlementGeneratorFactory()
{
}

// Create a specific type of settlement generator
GeneratorPtr SettlementGeneratorFactory::create_settlement_generator(const SettlementType settlement_type, MapPtr base_map)
{
  GeneratorPtr settlement_generator;

  switch(settlement_type)
  {
    case SETTLEMENT_TYPE_ORDERLY_VILLAGE:
      settlement_generator = make_shared<SettlementGenerator>(base_map);
      break;
    case SETTLEMENT_TYPE_HAMLET:
      settlement_generator = make_shared<HamletGenerator>(base_map);
      break;
    case SETTLEMENT_TYPE_WALLED:
      settlement_generator = make_shared<WalledSettlementGenerator>(base_map);
      break;
    case SETTLEMENT_TYPE_SCATTERED:
      settlement_generator = make_shared<ScatteredSettlementGenerator>(base_map);
      break;
    default:
      break;
  }

  return settlement_generator;
}
