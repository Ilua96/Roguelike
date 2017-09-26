#include "Map.h"
#include "Characters.h"
#include "Respawns.h"
#include "curses.h"
#include <fstream>

using namespace std;

Map::Map(const char* file_name) {
	int x, y;
	ifstream fin(file_name);
	if (!fin.good()) {
		fin.close();
		ofstream fout(file_name);
		fout << '1' << " " << '1' << '\n';
		fout << '#';
		fout.close();
		fin = ifstream(file_name);
	}
	fin >> x >> y;
	point = IntVector2(x, y);
	source.resize(point.get_y());
	for (int i = 0; i < point.get_y(); i++) {
		source[i].resize(point.get_x());
		for (int j = 0; j < point.get_x(); j++)
			fin >> source[i][j];
	}
}

void Map::display() {
	for (int i = 0; i < point.get_y(); i++) {
		for (int j = 0; j < point.get_x(); j++) {
			printw("%c", source[i][j]);
		}
		printw("\n");
	}
}

void Map::move(const IntVector2& src_point_1, const IntVector2& src_point_2) {
	source[src_point_2.get_y()][src_point_2.get_x()] = source[src_point_1.get_y()][src_point_1.get_x()];
	if (src_point_1.get_x() != src_point_2.get_x() || src_point_1.get_y() != src_point_2.get_y()) {
		source[src_point_1.get_y()][src_point_1.get_x()] = '.';
	}
}

void Map::new_obj(const IntVector2& src_point, const char src_symbol) {
	source[src_point.get_y()][src_point.get_x()] = src_symbol;
}

void Map::delete_obj(const IntVector2& src_point) {
	source[src_point.get_y()][src_point.get_x()] = '.';
}

void Map::change_map_size(const IntVector2& src_point) {
	source.resize(src_point.get_y());
	for (int i = 0; i < src_point.get_y(); i++) {
		source[i].resize(src_point.get_x());
		for (int j = 0; j < src_point.get_x(); j++) {
			if (i == src_point.get_y() - 1 || j == src_point.get_x() - 1)
				new_obj(IntVector2(j, i), '#');
			else if (i == 0 || j == 0)
				new_obj(IntVector2(j, i), '#');
			else if (i == point.get_y() - 1 || j == point.get_x() - 1)
				new_obj(IntVector2(j, i), '.');
			else if (i > point.get_y() - 1 || j > point.get_x() - 1)
				new_obj(IntVector2(j, i), '.');
		}
	}
	point = src_point;
}

IntVector2 Map::get_point() const {
	return point;
}

bool Map::is_precipice(const IntVector2& src_point) const {
	return source[src_point.get_y()][src_point.get_x()] == '\0';
}

bool Map::is_empty(const IntVector2& src_point) const {
	return source[src_point.get_y()][src_point.get_x()] == '.';
}

bool Map::is_wall(const IntVector2& src_point) const {
	return source[src_point.get_y()][src_point.get_x()] == '#';
}

bool Map::is_knight(const IntVector2& src_point) const {
	return source[src_point.get_y()][src_point.get_x()] == KNIGHT_SYMBOL;
}

bool Map::is_princess(const IntVector2& src_point) const {
	return source[src_point.get_y()][src_point.get_x()] == PRINCESS_SYMBOL;
}

bool Map::is_monster(const IntVector2& src_point) const {
	return (source[src_point.get_y()][src_point.get_x()] == DRAGON_SYMBOL) || 
			(source[src_point.get_y()][src_point.get_x()] == ZOMBIE_SYMBOL) ||
			(source[src_point.get_y()][src_point.get_x()] == WIZARD_SYMBOL);
}

bool Map::is_dragon(const IntVector2& src_point) const {
	return source[src_point.get_y()][src_point.get_x()] == DRAGON_SYMBOL;
}

bool Map::is_zombie(const IntVector2& src_point) const {
	return source[src_point.get_y()][src_point.get_x()] == ZOMBIE_SYMBOL;
}

bool Map::is_wizard(const IntVector2& src_point) const {
	return source[src_point.get_y()][src_point.get_x()] == WIZARD_SYMBOL;
}

bool Map::is_fireball(const IntVector2& src_point) const {
	return (source[src_point.get_y()][src_point.get_x()] == FIREBALL_SYMBOL_LEFT) ||
			(source[src_point.get_y()][src_point.get_x()] == FIREBALL_SYMBOL_RIGHT) ||
			(source[src_point.get_y()][src_point.get_x()] == FIREBALL_SYMBOL_UP) ||
			(source[src_point.get_y()][src_point.get_x()] == FIREBALL_SYMBOL_DOWN);
}

bool Map::is_health(const IntVector2& src_point) const {
	return source[src_point.get_y()][src_point.get_x()] == HEALTH_SUMBOL;
}

bool Map::is_respawn(const IntVector2& src_point) const {
	return (source[src_point.get_y()][src_point.get_x()] == RESPAWN_ZOMBIE_SYMBOL) ||
			(source[src_point.get_y()][src_point.get_x()] == RESPAWN_DRAGON_SYMBOL) ||
			(source[src_point.get_y()][src_point.get_x()] == RESPAWN_WIZARD_SYMBOL);
}

bool Map::is_respawn_dragon(const IntVector2& src_point) const {
	return source[src_point.get_y()][src_point.get_x()] == RESPAWN_DRAGON_SYMBOL;
}

bool Map::is_respawn_zombie(const IntVector2& src_point) const {
	return source[src_point.get_y()][src_point.get_x()] == RESPAWN_ZOMBIE_SYMBOL;
}

bool Map::is_respawn_wizard(const IntVector2& src_point) const {
	return source[src_point.get_y()][src_point.get_x()] == RESPAWN_WIZARD_SYMBOL;
}

const vector < vector < char > >& Map::get_source() const {
	return source;
}