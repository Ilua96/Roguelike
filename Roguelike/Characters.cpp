#include "Characters.h"
#include "Controller.h"
#include "curses.h"

using namespace std;

namespace Characters {

	//Character

	int Character::get_hp() const {
		return hp;
	}

	int Character::get_damage() const {
		return damage;
	}

	IntVector2 Character::get_point() const {
		return point;
	}

	void Character::set_hp(const int Hp) {
		hp = Hp;
	}

	void Character::set_coordinate(const IntVector2& src_point, Map& map) {
		map.move(point, src_point);
		point = IntVector2(src_point);
	}

	void Character::collide(Map& map, const IntVector2& src_point) {
		if (map.is_knight(src_point))
			collide_knight(map, src_point);
		else if (map.is_princess(src_point))
			collide_princess(map, src_point);
		else if (map.is_monster(src_point))
			collide_monster(map, src_point);
		else if (map.is_fireball(src_point))
			collide_fireball(map, src_point);
		else if (map.is_health(src_point))
			collide_health(map, src_point);
		else if (map.is_empty(src_point))
			no_collide(map, src_point);
	}

	void Character::collide_health(Map& map, const IntVector2& src_point) {
		hp += Controller::instance().get_health().get_health();
		if (hp > max_hp)
			hp = max_hp;
		Controller::instance().push_log(string(1, get_symbol()) +  " + 25 HP. " + to_string(src_point.get_x()) + " " + to_string(src_point.get_y()));
		Controller::instance().delete_health(src_point);
		set_coordinate(src_point, map);
	}

	void Character::no_collide(Map& map, const IntVector2& src_point) {
		set_coordinate(src_point, map);
	}

	//Knight

	Knight::Knight(const IntVector2& src_point) : Character(src_point){
		 hp = Controller::instance().get_config().get_character_health("Knight"); 
		 max_hp = hp; 
		 damage = Controller::instance().get_config().get_character_damage("Knight");
	} 

	void Knight::collide_princess(Map& map, const IntVector2& src_point) {
		Controller::instance().get_princess().set_hp(-1);
	}

	void Knight::collide_monster(Map& map, const IntVector2& src_point) {
		Monster& monster = Controller::instance().get_monster(src_point);
		monster.set_hp(monster.get_hp() - damage);
		Controller::instance().push_log(string(1, get_symbol()) + " attack " + string(1, monster.get_symbol()) + ". " + string(1, monster.get_symbol()) +
			" HP: " + to_string(monster.get_hp()));
		if (monster.get_hp() <= 0) {
			Controller::instance().delete_monster(src_point);
			set_coordinate(src_point, map);
		}
	}

	void Knight::move(Map& map) {
		char command = char(getch());
		auto dir = Controller::get_direction().find(command);
		if (dir == Controller::get_direction().end())
			return;
		collide(map, IntVector2(point + (dir->second)));
	}

	char Knight::get_symbol() const {
		return KNIGHT_SYMBOL;
	}

	//Princess

	Princess::Princess(const IntVector2& src_point) : Character(src_point) {
		hp = Controller::instance().get_config().get_character_health("Princess");
		max_hp = hp;
		damage = Controller::instance().get_config().get_character_damage("Princess");
	}

	char Princess::get_symbol() const {
		return PRINCESS_SYMBOL;
	}

	//Monster

	void Monster::collide_knight(Map& map, const IntVector2& src_point) {
		Controller::instance().get_knight().set_hp(Controller::instance().get_knight().get_hp() - damage);
		Controller::instance().push_log(string(1, get_symbol()) + " attack K.");
	}

	void Monster::move(Map& map) {
		char buttons[] = "awds";
		int path = rand() % 4;
		auto dir = Controller::get_direction().find(buttons[path]);
		collide(map, IntVector2(point + (dir->second)));
		action(map);
	}

	//Dragon

	Dragon::Dragon(const IntVector2& src_point) : Monster(src_point) {
		hp = Controller::instance().get_config().get_character_health("Dragon");
		max_hp = hp;
		damage = Controller::instance().get_config().get_character_damage("Dragon");
	}

	char Dragon::get_symbol() const {
		return DRAGON_SYMBOL;
	}

	//Zombie

	Zombie::Zombie(const IntVector2& src_point) : Monster(src_point) {
		hp = Controller::instance().get_config().get_character_health("Zombie");
		max_hp = hp;
		damage = Controller::instance().get_config().get_character_damage("Zombie");
	}

	char Zombie::get_symbol() const {
		return ZOMBIE_SYMBOL;
	}

	//Wizard

	Wizard::Wizard(const IntVector2& src_point) : Monster(src_point) {
		hp = Controller::instance().get_config().get_character_health("Wizard");
		max_hp = hp;
		damage = Controller::instance().get_config().get_character_damage("Wizard");
	}

	void Wizard::action(Map& map) {
		char buttons[] = "awds";
		int path = rand() % 4;
		auto dir = Controller::get_direction().find(buttons[path]);
		IntVector2 new_point = IntVector2(point + (dir->second));
		if (map.is_empty(new_point))
			Controller::instance().new_fireball(new_point, buttons[path]);
	}

	char Wizard::get_symbol() const {
		return WIZARD_SYMBOL;
	}

	//Fireball

	void Fireball::collide_knight(Map& map, const IntVector2& src_point) {
		Controller::instance().get_knight().set_hp(Controller::instance().get_knight().get_hp() - damage);
		Controller::instance().push_log("Fireball attack K.");
		Controller::instance().delete_fireball(point);
	}
	
	void Fireball::collide_princess(Map& map, const IntVector2& src_point) {
		if (map.is_princess(src_point))
			Controller::instance().delete_fireball(point);
	}

	void Fireball::collide_monster(Map& map, const IntVector2& src_point) {
		Monster& monster = Controller::instance().get_monster(src_point);
		monster.set_hp(monster.get_hp() - damage);
		Controller::instance().push_log("Fireball attack " + string(1, monster.get_symbol()) + ". " + string(1, monster.get_symbol()) +
			" HP: " + to_string(monster.get_hp()) + ". "  + to_string(monster.get_point().get_x()) + " " + to_string(monster.get_point().get_y()));
		if (monster.get_hp() <= 0)
			Controller::instance().delete_monster(src_point);
		Controller::instance().delete_fireball(point);
	}

	void Fireball::collide_fireball(Map& map, const IntVector2& src_point) {
		Controller::instance().delete_fireball(src_point);
		Controller::instance().delete_fireball(point);
	}

	void Fireball::collide_health(Map& map, const IntVector2& src_point) {
		if (map.is_health(src_point))
			Controller::instance().delete_fireball(point);
	}

	Fireball::Fireball(const IntVector2& src_point, const char path) : Character(src_point), path(path) {
		hp = Controller::instance().get_config().get_character_health("Fireball");
		max_hp = hp;
		damage = Controller::instance().get_config().get_character_damage("Fireball");
	}

	void Fireball::move(Map& map) {
		auto dir = Controller::get_direction().find(path);
		IntVector2 new_point = IntVector2(point + (dir->second));
		if (new_point == IntVector2(15, 6))
			int i = 0;
		if (map.is_wall(new_point) || map.is_respawn(new_point))
			Controller::instance().delete_fireball(point);
		else
			collide(map, new_point);

	}

	char Fireball::get_path() const {
		return path;
	}

	//Fireball_Left

	char Fireball_Left::get_symbol() const {
		return FIREBALL_SYMBOL_LEFT;
	}

	//Fireball_Right

	char Fireball_Right::get_symbol() const {
		return FIREBALL_SYMBOL_RIGHT;
	}

	//Fireball_Up

	char Fireball_Up::get_symbol() const {
		return FIREBALL_SYMBOL_UP;
	}

	//Fireball_Down

	char Fireball_Down::get_symbol() const {
		return FIREBALL_SYMBOL_DOWN;
	}
}