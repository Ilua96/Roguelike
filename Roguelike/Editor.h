#pragma once

#include "Point.h"
#include "Map.h"

#define EXIT '0'

#define CHANGE '1'
#define CHANGE_SIZE '2'
#define OPEN_FILE '3'
#define SAVE_FILE '4'
#define PLAY '5'

#define WALL '1'
#define KNIGHT '2'
#define PRINCESS '3'
#define DRAGON '4'
#define ZOMBIE '5'
#define WIZARD '6'
#define RESPAWN_DRAGON '7'
#define RESPAWN_ZOMBIE '8'
#define RESPAWN_WIZARD '9'
#define DELETE 'd'

class Editor
{
private:
	Editor(char* map_file) : map(map_file) {};
	IntVector2& point = IntVector2(0, 0);
	char file_name[106] = "maps/map.txt";
	Map map;
	void open_file();
	void save_file();
	void change_obj();
	void select_obj();
	IntVector2 choose_point();
public:
	~Editor() {};
	void map_editor();
	static void find_files();
	static Editor& inctance();
};