#pragma once

#include <vector>
#include "Point.h"

class Map
{
private:
	IntVector2 point;
	std::vector < std::vector < char > > source;
public:
	Map(const char* file_name = "map.txt");
	~Map() {};
	void display();
	void move(const IntVector2& src_point_1, const IntVector2& src_point_2);
	void new_obj(const IntVector2& src_point, const char src_symbol);
	void delete_obj(const IntVector2& src_point);
	void change_map_size(const IntVector2& src_point);
	IntVector2 get_point() const;
	bool is_precipice(const IntVector2& src_point) const;
	bool is_empty(const IntVector2& src_point) const;
	bool is_wall(const IntVector2& src_point) const;
	bool is_knight(const IntVector2& src_point) const;
	bool is_princess(const IntVector2& src_point) const;
	bool is_monster(const IntVector2& src_point) const;
	bool is_dragon(const IntVector2& src_point) const;
	bool is_zombie(const IntVector2& src_point) const;
	bool is_wizard(const IntVector2& src_point) const;
	bool is_fireball(const IntVector2& src_point) const;
	bool is_health(const IntVector2& src_point) const;
	bool is_respawn(const IntVector2& src_point) const;
	bool is_respawn_dragon(const IntVector2& src_point) const;
	bool is_respawn_zombie(const IntVector2& src_point) const;
	bool is_respawn_wizard(const IntVector2& src_point) const;
	const std::vector < std::vector < char > >& get_source() const;
};