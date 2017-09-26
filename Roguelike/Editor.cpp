#include "Editor.h"
#include "Characters.h"
#include "Respawns.h"
#include "Controller.h"
#include "curses.h"
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;

void Editor::open_file() {
	clear();
	find_files();
	printw("Write map file\n");
	char str[100];
	getstr(str);
	for (int i = 0; i < 100; i++)
		file_name[i + 5] = str[i];
	map = Map(file_name);
}

void Editor::save_file() {
	ofstream fout(file_name);
	fout << map.get_point().get_x() << " " << map.get_point().get_y() << '\n';
	vector < vector < char > > source = map.get_source();
	for (unsigned int i = 0; i < source.size(); i++) {
		for (unsigned int j = 0; j < source[i].size(); j++)
			fout << source[i][j];
		fout << '\n';
	}
	fout.close();
}

void Editor::map_editor() {
	char command = '\0';
	for (;;) {
		clear();
		map.display();
		mvprintw(1, map.get_point().get_x() + 1, "0 - Exit\n");
		mvprintw(2, map.get_point().get_x() + 1, "1 - Change object\n");
		mvprintw(3, map.get_point().get_x() + 1, "2 - Change map size\n");
		mvprintw(4, map.get_point().get_x() + 1, "3 - Open map file\n");
		mvprintw(5, map.get_point().get_x() + 1, "4 - Save map file\n");
		mvprintw(6, map.get_point().get_x() + 1, "5 - Play\n");
		select_obj();
		command = char(getch());
		auto dir = Controller::get_direction().find(command);
		if (dir != Controller::get_direction().end())
			point = IntVector2(point + (dir->second));
		switch (command)
		{
			case EXIT:
			{
				clear();
				return;
			}
			case CHANGE:
			{
				change_obj();
				break;
			}
			case CHANGE_SIZE:
			{
				map.change_map_size(choose_point());
				break;
			}
			case OPEN_FILE:
			{
				open_file();
				break;
			}
			case SAVE_FILE:
			{
				save_file();
				break;
			}
			case PLAY:
			{
				save_file();
				Controller::instance().restart(file_name);
				Controller::instance().game_loop();
			}
			default:
				break;
		}
	}
}

void Editor::change_obj() {
	char command = '\0';
	for (;;) {
		clear();
		map.display();
		mvprintw(0, map.get_point().get_x() + 1, "0 - Exit\n");
		mvprintw(1, map.get_point().get_x() + 1, "1 - Add wall\n");
		mvprintw(2, map.get_point().get_x() + 1, "2 - Add knight\n");
		mvprintw(3, map.get_point().get_x() + 1, "3 - Add princess\n");
		mvprintw(4, map.get_point().get_x() + 1, "4 - Add dragon\n");
		mvprintw(5, map.get_point().get_x() + 1, "5 - Add zombie\n");
		mvprintw(6, map.get_point().get_x() + 1, "6 - Add wizard\n");
		mvprintw(7, map.get_point().get_x() + 1, "7 - Add respawn dragon\n");
		mvprintw(8, map.get_point().get_x() + 1, "8 - Add respawn zombie\n");
		mvprintw(9, map.get_point().get_x() + 1, "9 - Add respawn wizard\n");
		mvprintw(10, map.get_point().get_x() + 1, "d - Delete object\n");
		mvprintw(point.get_y(), point.get_x(), "");
		command = char(getch());
		switch (command)
		{
			case EXIT:
			{
				clear();
				return;
			}
			case WALL:
			{
				map.new_obj(point, '#');
				break;
			}
			case KNIGHT:
			{
				map.new_obj(point, KNIGHT_SYMBOL);
				break;
			}
			case PRINCESS:
			{
				map.new_obj(point, PRINCESS_SYMBOL);
				break;
			}
			case DRAGON:
			{
				map.new_obj(point, DRAGON_SYMBOL);
				break;
			}
			case ZOMBIE:
			{
				map.new_obj(point, ZOMBIE_SYMBOL);
				break;
			}
			case WIZARD:
			{
				map.new_obj(point, WIZARD_SYMBOL);
				break;
			}
			case RESPAWN_DRAGON:
			{
				map.new_obj(point, RESPAWN_DRAGON_SYMBOL);
				break;
			}
			case RESPAWN_ZOMBIE:
			{
				map.new_obj(point, RESPAWN_ZOMBIE_SYMBOL);
				break;
			}
			case RESPAWN_WIZARD:
			{
				map.new_obj(point, RESPAWN_WIZARD_SYMBOL);
				break;
			}
			case DELETE:
			{
				map.delete_obj(point);
				break;
			}
			default:
				break;
		}
	}
}

void Editor::select_obj() {
	if (point.get_x() < 0)
		point = IntVector2(0, point.get_y());
	if (point.get_y() < 0)
		point = IntVector2(point.get_x(), 0);
	if (point.get_x() == map.get_point().get_x())
		point = IntVector2(point.get_x() - 1, point.get_y());
	if (point.get_y() == map.get_point().get_y())
		point = IntVector2(point.get_x(), point.get_y() - 1);
	if (map.is_wall(point))
		mvprintw(0, map.get_point().get_x() + 1, "This is wall");
	if (map.is_empty(point))
		mvprintw(0, map.get_point().get_x() + 1, "This is empty");
	if (map.is_knight(point))
		mvprintw(0, map.get_point().get_x() + 1, "This is knight");
	if (map.is_princess(point))
		mvprintw(0, map.get_point().get_x() + 1, "This is princess");
	if (map.is_dragon(point))
		mvprintw(0, map.get_point().get_x() + 1, "This is dragon");
	if (map.is_zombie(point))
		mvprintw(0, map.get_point().get_x() + 1, "This is zombie");
	if (map.is_wizard(point))
		mvprintw(0, map.get_point().get_x() + 1, "This is wizard");
	if (map.is_respawn_dragon(point))
		mvprintw(0, map.get_point().get_x() + 1, "This is respaw dragon");
	if (map.is_respawn_zombie(point))
		mvprintw(0, map.get_point().get_x() + 1, "This is respawn zombie");
	if (map.is_respawn_wizard(point))
		mvprintw(0, map.get_point().get_x() + 1, "This is respawn wizard");
	mvprintw(point.get_y(), point.get_x(), "");
}

IntVector2 Editor::choose_point() {
	clear();
	map.display();
	mvprintw(0, map.get_point().get_x() + 1, "Write X. Only two digite\n");
	mvprintw(1, map.get_point().get_x() + 1, "");
	char str[3];
	getstr(str);
	int x = stoi(str, string::size_type());
	mvprintw(2, map.get_point().get_x() + 1, "Write Y. Only two digite\n");
	mvprintw(3, map.get_point().get_x() + 1, "");
	getstr(str);
	int y = stoi(str, string::size_type());
	clear();
	return IntVector2(x, y);
}

void Editor::find_files() {
	WIN32_FIND_DATA f;
	HANDLE h = FindFirstFile("./maps/*", &f);
	if (h != INVALID_HANDLE_VALUE) {
		FindNextFile(h, &f);
		printw("all files:\n");
		while (FindNextFile(h, &f))
			printw("%s\n", f.cFileName);
	}
	else
		fprintf(stderr, "Error opening directory\n");
	printw("\n");
	return;
}

Editor& Editor::inctance() {
	static Editor Editor("maps/map.txt");
	return Editor;
}