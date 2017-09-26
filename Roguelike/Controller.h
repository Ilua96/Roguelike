#pragma once

#include "Map.h"
#include "Characters.h"
#include "Respawns.h"
#include "Config.h"
#include <vector>
#include <string>
#include <map>

#define LEFT 'a'
#define RIGHT 'd'
#define UP 'w'
#define DOWN 's'

class Controller
{
private:
	Controller(const char* map_file) : map(map_file), config() {};
	Map map;
	Config config;
	Characters::Knight* Knight;
	Characters::Princess* Princess;
	Respawns::Respawn_Health* Health;
	std::vector < Characters::Monster* > Monsters;
	std::vector < Characters::Fireball* > Fireballs;
	std::vector < Respawns::Respawn_Monsters* > Respawns_Monsters;
	std::vector < std::string > logs;
	static std::map < char, IntVector2 > direction;
	void find_characters();
	void monsters_move();
	void fireballs_move();
	void respawns_move();
	void print_log() const;
	int find_monster(const IntVector2& src_point) const;
	int find_fireball(const IntVector2& src_point) const;
	bool check_missing_characters() const;
public:
	~Controller() {};
	void restart(const char* map_file = "map.txt");
	void game_loop();
	void delete_monster(const IntVector2& src_point);
	void delete_fireball(const IntVector2& src_point);
	void delete_health(const IntVector2& src_point);
	void new_fireball(const IntVector2& src_point, const char path);
	void new_monster(const IntVector2& src_point, const char monster);
	void push_log(const std::string src_log);
	static Controller& instance();
	Map& get_map();
	Config& get_config();
	Characters::Knight& get_knight() const;
	Characters::Princess& get_princess() const;
	Characters::Monster& get_monster(const IntVector2& src_point) const;
	Characters::Fireball& get_fireball(const IntVector2& src_point) const;
	Respawns::Respawn_Health& get_health() const;
	const static std::map < char, IntVector2 >& get_direction();
};