#include "Respawns.h"
#include "Controller.h"
#include <map>


namespace Respawns
{

	//Respawn

	void Respawn::check_time(Map& map) {
		if (time != respawn_time)
			time++;
		else {
			time = 0;
			creat_obj(map);
		}
	}

	IntVector2 Respawn::get_point() const {
		return point;
	}

	int Respawn::get_time() const {
		return time;
	}

	int Respawn::get_respawn_time() const {
		return respawn_time;
	}

	//Respawn_Health

	Respawn_Health::Respawn_Health() : Respawn(IntVector2(-1, -1), Controller::instance().get_config().get_respawn_time("Respawn_Health")) {}

	void Respawn_Health::creat_obj(Map& map) {
		if (stop_respawn) {
			if (obj.size() == 0)
				stop_respawn = false;
			else
				return;
		}
		else if (obj.size() == count) {
			stop_respawn = true;
			return;
		}
		int x = rand() % map.get_point().get_x();
		int y = rand() % map.get_point().get_y();
		IntVector2 new_point = IntVector2(x, y);
		while (!map.is_empty(new_point)) {
			x = rand() % map.get_point().get_x();
			y = rand() % map.get_point().get_y();
			new_point = IntVector2(x, y);
		}
		obj.push_back(new_point);
		map.new_obj(new_point, HEALTH_SUMBOL);
	}

	void Respawn_Health::delete_obj(const IntVector2& src_point) {
		for (unsigned int i = 0; i < obj.size(); i++)
			if (obj[i] == src_point)
				obj.erase(obj.begin() + i);
	}

	int Respawn_Health::get_health() const {
		return helth;
	}

	//Respawn_Monsters

	void Respawn_Monsters::creat_obj(Map& map) {
		char buttons[] = "awds";
		int path = rand() % 4;
		auto dir = Controller::get_direction().find(buttons[path]);
		IntVector2 new_point = IntVector2(point + (dir->second));
		std::map <IntVector2, int> p;
		p.insert(std::make_pair(new_point, 0));
		while (!map.is_empty(new_point)) {
			if (p.size() == 4)
				return;
			path = rand() % 4;
			dir = Controller::get_direction().find(buttons[path]);
			new_point = IntVector2(point + (dir->second));
			p.insert({ new_point, 0 });
		}
		Controller::instance().new_monster(new_point, get_symbol());
	}

	//Respawn_Zombie

	Respawn_Zombie::Respawn_Zombie(const IntVector2& src_point) : Respawn_Monsters(src_point, Controller::instance().get_config().get_respawn_time("Respawn_Zombie")) {};

	char Respawn_Zombie::get_symbol() const {
		return RESPAWN_ZOMBIE_SYMBOL;
	}

	//Respawn_Dragon

	Respawn_Dragon::Respawn_Dragon(const IntVector2& src_point) : Respawn_Monsters(src_point, Controller::instance().get_config().get_respawn_time("Respawn_Dragon")) {};

	char Respawn_Dragon::get_symbol() const {
		return RESPAWN_DRAGON_SYMBOL;
	}

	//Respawn_Wizard

	Respawn_Wizard::Respawn_Wizard(const IntVector2& src_point) : Respawn_Monsters(src_point, Controller::instance().get_config().get_respawn_time("Respawn_Wizard")) {};

	char Respawn_Wizard::get_symbol() const {
		return RESPAWN_WIZARD_SYMBOL;
	}
}
	