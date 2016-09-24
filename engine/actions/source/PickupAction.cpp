#include <list>
#include "ActionTextKeys.hpp"
#include "CreatureUtils.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "Inventory.hpp"
#include "ItemFilterFactory.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "PickupAction.hpp"
#include "TextMessages.hpp"

using namespace std;

// Try to pick up.
ActionCostValue PickupAction::pick_up(CreaturePtr creature, ActionManager * const am)
{  
  ActionCostValue action_cost_value = 0;
  Game& game = Game::instance();
  
  if (creature)
  {
    MapPtr map = game.get_current_map();
    
    if (map->get_map_type() == MapType::MAP_TYPE_WORLD)
    {
      handle_world_map_pickup(creature);
    }
    else
    {
      action_cost_value = handle_pickup(creature, map, am);
    }
  }

  return action_cost_value;
}

ActionCostValue PickupAction::handle_pickup(CreaturePtr creature, MapPtr map, ActionManager * const am)
{
  ActionCostValue action_cost_value = 0;
  
  if (creature)
  {
    TilePtr tile = MapUtils::get_tile_for_creature(map, creature);
    
    if (tile)
    {
      IInventoryPtr inv = tile->get_items();

      // If there is no item, inform the user.
      if (inv->empty())
      {
        handle_empty_tile_pickup(creature);
      }
      else
      {
        // If there is one item, pick it up.
        uint num_items = inv->size();
        bool can_pick_up = true;
        
        ItemPtr pick_up_item;
        
        if (num_items == 1)
        {
          ItemPtr item = inv->at(0);

          if (CreatureUtils::can_pick_up(creature, item))
          {
            pick_up_item = item;
          }
          else
          {
            can_pick_up = false;
          }
        }

        // If there are many items, get one of them.
        else
        {
          list<IItemFilterPtr> no_filter = ItemFilterFactory::create_empty_filter();
          pick_up_item = am->inventory(creature, inv, no_filter, {}, false);

          can_pick_up = CreatureUtils::can_pick_up(creature, pick_up_item);
        }
        
        if (pick_up_item != nullptr && !can_pick_up)
        {
          handle_max_item_pickup(creature);
        }
        else
        {
          if (pick_up_item)
          {
            // Remove the item from the ground.
            inv->remove(pick_up_item->get_id());

            if (!merge_into_equipment(creature, pick_up_item))
            {
              merge_or_add_into_inventory(creature, pick_up_item);
            }
          }
        }
        
        // Advance the turn
        action_cost_value = get_action_cost_value(creature);
      }   
    }      
  }
  
  return action_cost_value;
}

// Handle the case where the creature already has the maximum number of items
// it can hold.
void PickupAction::handle_max_item_pickup(CreaturePtr creature)
{
  IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());

  if (creature && creature->get_is_player())
  {
    string pick_up_not_allowed = StringTable::get(ActionTextKeys::ACTION_PICK_UP_MAX_ITEMS);

    manager.add_new_message(pick_up_not_allowed);
    manager.send();
  }
}

// Handle the case where we're trying to pick up on the world map, which is an invalid case.
void PickupAction::handle_world_map_pickup(CreaturePtr creature)
{
  IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
  
  if (creature && creature->get_is_player())
  {
    string pick_up_not_allowed = StringTable::get(ActionTextKeys::ACTION_PICK_UP_NOT_ALLOWED);
    
    manager.add_new_message(pick_up_not_allowed);
    manager.send();
  }
}

// Handle the case where we're trying to pick up from a tile that contains no items.
void PickupAction::handle_empty_tile_pickup(CreaturePtr creature)
{
  IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
  
  if (creature && creature->get_is_player())
  {
    string no_item_on_ground = StringTable::get(ActionTextKeys::ACTION_PICK_UP_NOTHING_ON_GROUND);
    
    manager.add_new_message(no_item_on_ground);
    manager.send();
  }  
}

// Merge into the equipment, if possible (true is returned).
// If the item can't be merged into the equipment, return false.
bool PickupAction::merge_into_equipment(CreaturePtr creature, ItemPtr item)
{
  if (creature)
  {
    Equipment& equipment = creature->get_equipment();
    
    if (equipment.merge(item))
    {
      Game& game = Game::instance();
      CreaturePtr player = game.get_current_player();

      // As all creatures can pick up items, check to see if:
      // - player is blind
      // - player or monster is picking up.
      //
      // If the player is blind, only add a message if it is the player
      // picking up an item.  Otherwise, always add a message.
      CurrentCreatureAbilities cca;
      bool player_blind = !cca.can_see(player);
      string item_merged_into_equipment;

      // Only broadcast if it's the player, or the monster's in range.
      IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, GameUtils::is_player_among_creatures(creature, player));

      if (!player_blind || (player_blind && creature->get_is_player()))
      {
        item_merged_into_equipment = TextMessages::get_item_pick_up_and_merge_message(player_blind, creature, item);
      }

      if (!item_merged_into_equipment.empty())
      {
        manager.add_new_message(item_merged_into_equipment);
        manager.send();
      }
      
      return true;
    }
  }
  
  return false;
}

// Merge into the inventory, if possible.  If this is not possible,
// add the item to the inventory.
bool PickupAction::merge_or_add_into_inventory(CreaturePtr creature, ItemPtr item)
{
  if (creature)
  {
    IInventoryPtr creature_inv = creature->get_inventory();
    if (!creature_inv->merge(item))
    {
      // Add to the end of the inventory
      creature_inv->add(item);
    }

    Game& game = Game::instance();
    CreaturePtr player = game.get_current_player();
    CurrentCreatureAbilities cca;
    bool player_blind = !cca.can_see(player);

    // Only broadcast if it's the player, or the monster's in range.
    IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, GameUtils::is_player_among_creatures(creature, player));

    // Display a message if necessary
    string pick_up_message;
    if (!player_blind || (player_blind && creature->get_is_player()))
    {
      pick_up_message = TextMessages::get_item_pick_up_message(player_blind, creature, item);
    }

    if (!pick_up_message.empty())
    {
      manager.add_new_message(pick_up_message);
      manager.send();
    }

    return true;
  }
  
  return false;
}

// Base action cost value is 1.
ActionCostValue PickupAction::get_action_cost_value(CreaturePtr creature) const
{
  return 1;
}
