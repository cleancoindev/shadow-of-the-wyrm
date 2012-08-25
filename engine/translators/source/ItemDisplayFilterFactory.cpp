#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
#include "ItemDisplayFilterFactory.hpp"
#include "NullDisplayFilter.hpp"
#include "SquishyEquipWornLocationDisplayFilter.hpp"

using std::list;
using boost::make_shared;

// Create a 1-item list that always passes - used for things like pickup,
// drop, etc., where the initial filter is always empty.
list<IItemDisplayFilterPtr> ItemDisplayFilterFactory::create_empty_filter()
{
  list<IItemDisplayFilterPtr> null_filter_list;

  IItemDisplayFilterPtr null_filter = make_shared<NullDisplayFilter>();
  null_filter_list.push_back(null_filter);

  return null_filter_list;
}

// Create a list of filters for the passed-in worn locations.
list<IItemDisplayFilterPtr> ItemDisplayFilterFactory::create_equipment_filter(const std::list<EquipmentWornLocation>& eq_loc_list)
{
  list<IItemDisplayFilterPtr> ewl_list;
  
  BOOST_FOREACH(const EquipmentWornLocation& ewl, eq_loc_list)
  {
    IItemDisplayFilterPtr eq_filter = create_equipment_worn_location_filter(ewl);
    ewl_list.push_back(eq_filter);
  }
  
  return ewl_list;
}

// Create a filter by equipment worn location
IItemDisplayFilterPtr ItemDisplayFilterFactory::create_equipment_worn_location_filter(const EquipmentWornLocation& ewl)
{
  IItemDisplayFilterPtr eq_filter = make_shared<SquishyEquipWornLocationDisplayFilter>(ewl);
  return eq_filter;
}

