#include "Controller.h"
#include "curses.h"

using namespace std;

map < char, IntVector2 > Controller::direction =
{
	{ LEFT, IntVector2(-1, 0) },
	{ UP, IntVector2(0, -1) },
	{ RIGHT, IntVector2(1, 0) },
	{ DOWN, IntVector2(0, 1) }
};

void Controller::restart(const char* map_file) {
	map = Map(map_file);
	delete Knight;
	Knight = nullptr;
	delete Princess;
	Princess = nullptr;
	delete Health;
	Health = nullptr;
	Monsters.clear();
	Fireballs.clear();
	Respawns_Monsters.clear();
	logs.clear();
}

void Controller::game_loop() {
	find_characters();
	bool game_over = check_missing_characters();
	Health = new Respawns::Respawn_Health();
	while (!game_over) {
		clear();
		map.display();
		print_log();
		logs.clear();
		Knight->move(map);
		fireballs_move();
		monsters_move();
		respawns_move();
		if (Princess->get_hp() <= 0) {
			clear();
			printw("You win!!!\n");
			game_over = true;
		}
		else if (Knight->get_hp() <= 0){
			clear();
			printw("You lose!!!\n");
			game_over = true;
		}
	}
}

void Controller::find_characters() {
	vector < vector <char> > source = map.get_source();
	for (unsigned int i = 0; i < source.size(); i++)
		for (unsigned int j = 0; j < source[i].size(); j++)
			switch (source[i][j])
			{
			case KNIGHT_SYMBOL:
			{
				if (Knight != nullptr) {
					map.delete_obj(IntVector2(i, j));
					break;
				}
				Knight = new Characters::Knight(IntVector2(j, i));
				break;
			}
			case PRINCESS_SYMBOL:
			{
				if (Princess != nullptr) {
					map.delete_obj(IntVector2(i, j));
					break;
				}
				Princess = new Characters::Princess(IntVector2(j, i));
				break;
			}
			case DRAGON_SYMBOL:
			{
				Monsters.push_back(new Characters::Dragon(IntVector2(j, i)));
				break;
			}
			case ZOMBIE_SYMBOL:
			{
				Monsters.push_back(new Characters::Zombie(IntVector2(j, i)));
				break;
			}
			case WIZARD_SYMBOL:
			{
				Monsters.push_back(new Characters::Wizard(IntVector2(j, i)));
				break;
			}
			case RESPAWN_ZOMBIE_SYMBOL:
			{
				Respawns_Monsters.push_back(new Respawns::Respawn_Zombie(IntVector2(j, i)));
				break;
			}
			case RESPAWN_DRAGON_SYMBOL:
			{
				Respawns_Monsters.push_back(new Respawns::Respawn_Dragon(IntVector2(j, i)));
				break;
			}
			case RESPAWN_WIZARD_SYMBOL:
			{
				Respawns_Monsters.push_back(new Respawns::Respawn_Wizard(IntVector2(j, i)));
				break;
			}
			}
}

void Controller::monsters_move() {
	for (unsigned int i = 0; i < Monsters.size(); i++)
		Monsters[i]->move(map);
}

void Controller::fireballs_move() {
	unsigned int i = 0;
	int l;
	while (i < Fireballs.size()) {
		l = Fireballs.size();
		Fireballs[i]->move(map);
		if (l == Fireballs.size())
			i++;
	}
}

void Controller::respawns_move() {
	for (unsigned int i = 0; i < Respawns_Monsters.size(); i++)
		Respawns_Monsters[i]->check_time(map);
	Health->check_time(map);
}

void Controller::delete_monster(const IntVector2& src_point) {
	int i = find_monster(src_point);
	delete Monsters[i];
	Monsters.erase(Monsters.begin() + i);
	map.delete_obj(src_point);
}

void Controller::delete_fireball(const IntVector2& src_point) {
	int i = find_fireball(src_point);
	map.delete_obj(src_point);
	delete Fireballs[i];
	Fireballs.erase(Fireballs.begin() + i);
}

void Controller::delete_health(const IntVector2& src_point) {
	Health->delete_obj(src_point);
}

void Controller::new_fireball(const IntVector2& src_point, const char path) {
	switch (path)
	{
		case LEFT:
		{
			Fireballs.push_back(new Characters::Fireball_Left(src_point));
			map.new_obj(src_point, FIREBALL_SYMBOL_LEFT);
			break;
		}
		case RIGHT:
		{
			Fireballs.push_back(new Characters::Fireball_Right(src_point));
			map.new_obj(src_point, FIREBALL_SYMBOL_RIGHT);
			break;
		}
		case UP:
		{
			Fireballs.push_back(new Characters::Fireball_Up(src_point));
			map.new_obj(src_point, FIREBALL_SYMBOL_UP);
			break;
		}
		case DOWN:
		{
			Fireballs.push_back(new Characters::Fireball_Down(src_point));
			map.new_obj(src_point, FIREBALL_SYMBOL_DOWN);
			break;
		}
	}
}

void Controller::new_monster(const IntVector2& src_point, const char monster) {
	if (ZOMBIE_SYMBOL == monster || RESPAWN_ZOMBIE_SYMBOL == monster) {
		Monsters.push_back(new Characters::Zombie(src_point));
		map.new_obj(src_point, ZOMBIE_SYMBOL);
	}
	if (DRAGON_SYMBOL == monster || RESPAWN_DRAGON_SYMBOL == monster) {
		Monsters.push_back(new Characters::Dragon(src_point));
		map.new_obj(src_point, DRAGON_SYMBOL);
	}
	if (WIZARD_SYMBOL == monster || RESPAWN_WIZARD_SYMBOL == monster) {
		Monsters.push_back(new Characters::Wizard(src_point));
		map.new_obj(src_point, WIZARD_SYMBOL);
	}
}

void Controller::push_log(const string src_log) {
	logs.push_back(src_log);
}

void Controller::print_log() const {
	mvprintw(0, map.get_point().get_x() + 1, "HP: %d", Knight->get_hp());
	for (unsigned int i = 0; i < logs.size(); i++)
		mvprintw(i + 1, map.get_point().get_x() + 1, "%s", logs[i].c_str());
}

int Controller::find_monster(const IntVector2& src_point) const{
	for (unsigned int i = 0; i < Monsters.size(); i++)
		if (Monsters[i]->get_point() == src_point)
			return i;
	return -1;
}

int Controller::find_fireball(const IntVector2& src_point) const {
	for (unsigned int i = 0; i < Fireballs.size(); i++)
		if (Fireballs[i]->get_point() == src_point)
			return i;
	return -1;
}

bool Controller::check_missing_characters() const {
	if (Knight == nullptr || Princess == nullptr) {
		clear();
		printw("Knight or Princess couldn't be found. Press anything to continue.");
		getch();
		return true;
	}
	else
		return false;
}



Controller& Controller::instance() {
	static Controller Controller("map.txt");
	return Controller;
}

Map& Controller::get_map() {
	return map;
}

Config& Controller::get_config() {
	return config;
}

Characters::Knight& Controller::get_knight() const {
	return *Knight;
}

Characters::Princess& Controller::get_princess() const {
	return *Princess;
}

Characters::Monster& Controller::get_monster(const IntVector2& src_point) const {
	return *Monsters[find_monster(src_point)];
}

Characters::Fireball& Controller::get_fireball(const IntVector2& src_point) const {
	return *Fireballs[find_fireball(src_point)];
}

Respawns::Respawn_Health& Controller::get_health() const {
	return *Health;
}

const map < char, IntVector2 >& Controller::get_direction() {
	return direction;
}