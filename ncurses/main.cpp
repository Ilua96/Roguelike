#include "curses.h"
#include "Controller.h"
#include "Editor.h"

#define MAP_EDITOR '1'
#define START_GAME '2'

int main() {
	initscr();
	unsigned rand_value = 5;
	srand(rand_value);
	char command = '\0';
	Controller::instance();
	while (command != EXIT) {
		printw("0 - Exit\n");
		printw("1 - Execute map editor\n");
		printw("2 - Start game\n");
		command = char(getch());
		switch (command)
		{
			case MAP_EDITOR:
			{
				Editor::inctance().map_editor();
				break;
			}
			case START_GAME:
			{
				clear();
				Editor::find_files();
				printw("Write map file\n");
				char str[100];
				getstr(str);
				char file[106] = "maps/";
				for (int i = 0; i < 100; i++)
					file[i + 5] = str[i];
				Controller::instance().restart(file);
				Controller::instance().game_loop();
				break;
			}
			default:
				clear();
		}
	}
	endwin();
	return 0;
}