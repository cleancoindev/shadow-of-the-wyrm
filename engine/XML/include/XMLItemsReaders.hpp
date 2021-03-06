#pragma once
#include "XMLDataStructures.hpp"
#include "Ammunition.hpp"
#include "Armour.hpp"
#include "Currency.hpp"
#include "Food.hpp"
#include "GenerationValues.hpp"
#include "Plant.hpp"
#include "Weapon.hpp"
#include "Wearable.hpp"
#include "XMLAmuletReader.hpp"
#include "XMLArmourReader.hpp"
#include "XMLBoatReader.hpp"
#include "XMLFoodReader.hpp"
#include "XMLPlantReader.hpp"
#include "XMLPotionReader.hpp"
#include "XMLRingReader.hpp"
#include "XMLScrollReader.hpp"
#include "XMLSpellbookReader.hpp"
#include "XMLToolReader.hpp"
#include "XMLWandReader.hpp"
#include "XMLWeaponsReaders.hpp"

class XMLItemsReader
{
  public:
    XMLItemsReader();
    ~XMLItemsReader();
    
    std::pair<ItemMap, GenerationValuesMap> get_items(const XMLNode& items_node, const bool force_ascii);

  protected:
    std::pair<ItemMap, GenerationValuesMap> get_misc_items(const XMLNode& misc_items_node, const bool force_ascii);
    std::pair<ItemMap, GenerationValuesMap> get_amulets(const XMLNode& amulets_node, const bool force_ascii);
    std::pair<ItemMap, GenerationValuesMap> get_armour(const XMLNode& armour_node, const bool force_ascii);
    std::pair<ItemMap, GenerationValuesMap> get_rings(const XMLNode& rings_node, const bool force_ascii);
    std::pair<ItemMap, GenerationValuesMap> get_weapons(const XMLNode& weapons_node, const bool force_ascii);
    std::pair<ItemMap, GenerationValuesMap> get_ranged_weapons(const XMLNode& ranged_weapons_node, const bool force_ascii);
    std::pair<ItemMap, GenerationValuesMap> get_ammunition(const XMLNode& ammunition_node, const bool force_ascii);
    std::pair<ItemMap, GenerationValuesMap> get_food(const XMLNode& foodstuffs_node, const bool force_ascii);
    std::pair<ItemMap, GenerationValuesMap> get_plants(const XMLNode& plants_node, const bool force_ascii);
    std::pair<ItemMap, GenerationValuesMap> get_boats(const XMLNode& boats_node, const bool force_ascii);
    std::pair<ItemMap, GenerationValuesMap> get_potions(const XMLNode& potions_node, const bool force_ascii);
    std::pair<ItemMap, GenerationValuesMap> get_scrolls(const XMLNode& scrolls_node, const bool force_ascii);
    std::pair<ItemMap, GenerationValuesMap> get_currencies(const XMLNode& currencies_node, const bool force_ascii);
    std::pair<ItemMap, GenerationValuesMap> get_tools(const XMLNode& tools_node, const bool force_ascii);
    std::pair<ItemMap, GenerationValuesMap> get_wands(const XMLNode& wands_node, const bool force_ascii);
    std::pair<ItemMap, GenerationValuesMap> get_spellbooks(const XMLNode& spellbooks_node, const bool force_ascii);
    
    XMLItemReader item_reader;
    XMLAmuletReader amulet_reader;
    XMLArmourReader armour_reader;
    XMLBoatReader boat_reader;
    XMLWeaponsReader weapons_reader;
    XMLAmmunitionReader ammunition_reader;
    XMLFoodReader food_reader;
    XMLPlantReader plant_reader;
    XMLPotionReader potion_reader;
    XMLRingReader ring_reader;
    XMLScrollReader scroll_reader;
    XMLSpellbookReader spellbook_reader;
    XMLToolReader tool_reader;
    XMLWandReader wand_reader;
};

