#pragma once

#include <map>
#include <string>

class Config
{
private:
	std::map < std::string, std::pair < int, int > > characters;
	std::map < std::string, int > respawns;
	void find_obj(const std::string name) const;
public:
	Config();
	~Config() {};
	int get_character_damage(const std::string name) const;
	int get_character_health(const std::string name) const;
	int get_respawn_time(const std::string name) const;
};
