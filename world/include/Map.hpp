#pragma once
#include <string>
#include <map>
#include <vector>
#include "common.hpp"
#include "Dimensions.hpp"
#include "Tile.hpp"
#include "MapExit.hpp"

// Forward declarations.
class Creature;
class Tile;

enum MapType
{
  MAP_TYPE_WORLD = 0
, MAP_TYPE_OVERWORLD = 1
, MAP_TYPE_UNDERWORLD = 2
};

// JCD FIXME: Before delving too deep into things, it might be nice to  make this pair<int,int,int>
// to represent a truly three dimensional map.  Maybe for v0.2.0?
typedef std::map<std::string, Coordinate> NamedMapLocations;

class Map
{
	public:
    Map(const Map& new_map);
		Map(const Dimensions& new_dimensions);
		
		// Functions used when creating a view map - reset the
		// creatures and locations after copying the map.
		void reset_creatures_and_locations();

		// These functions work on a list built up from the map itself.
		// This allows for quicker lookup.
		bool has_creature(const std::string& creature_id);
		boost::shared_ptr<Creature> get_creature(const uint idx_in_creature_list);
		std::vector<boost::shared_ptr<Creature> > get_creatures();
		void remove_creature(const std::string& creature_id);
		// Other get_creature... fns here.
		// Other remove_creature... fns here.

		bool insert(int row, int col, boost::shared_ptr<Tile> tile);
		boost::shared_ptr<Tile> at(int row, int col);
		boost::shared_ptr<Tile> at(const Coordinate& c);

		void set_size(const Dimensions& new_dimensions);
		Dimensions size() const;
		
		void set_terrain_type(const TileType new_terrain_type);
		TileType get_terrain_type() const;

		void set_map_type(const MapType& new_type);
		MapType get_map_type() const;
		
		std::map<std::string, boost::shared_ptr<Tile> > get_tiles() const;

    void clear_locations();
    void add_or_update_location(const std::string& location, const Coordinate& coordinate);
    bool has_location(const std::string& location);
    Coordinate get_location(const std::string& location) const;
    boost::shared_ptr<Tile> get_tile_at_location(const std::string& location);
    
    void set_map_exit(MapExitPtr new_map_exit);
    MapExitPtr get_map_exit() const;
    
    void set_map_id(const std::string& new_map_id);
    std::string get_map_id() const;
    
    std::string get_map_exit_id() const;
    
    void set_permanent(const bool permenance);
    bool get_permanent() const;

	protected:
    friend class SL_Engine_Map;
    
		void create_creatures();		
		std::string make_key(const int row, const int col);
		Coordinate convert_map_key_to_coordinate(const std::string& map_key);

    // NOTE: This information is also stored at the Tile level, but since it's a shared_ptr, that's okay.
    // Ensure that when creatures are created or killed, both data structures are updated accordingly.
    std::vector<boost::shared_ptr<Creature> > creatures;

		std::map<std::string, boost::shared_ptr<Tile> > tiles;
		Dimensions dimensions;
    NamedMapLocations locations;
    TileType terrain_type; // field, forest, village, etc.
    MapType map_type;
    MapExitPtr map_exit;
    std::string map_id;
    bool permanent;
};

typedef boost::shared_ptr<Map> MapPtr;
