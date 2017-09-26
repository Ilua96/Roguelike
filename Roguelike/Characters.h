#pragma once

#include "Map.h"
#include "Point.h"

#define KNIGHT_SYMBOL 'K'
#define PRINCESS_SYMBOL 'P'
#define ZOMBIE_SYMBOL 'Z'
#define DRAGON_SYMBOL 'D'
#define WIZARD_SYMBOL 'W'
#define FIREBALL_SYMBOL_LEFT '<'
#define FIREBALL_SYMBOL_RIGHT '>'
#define FIREBALL_SYMBOL_UP '^'
#define FIREBALL_SYMBOL_DOWN 'v'

namespace Characters
{
	class Character
	{
	private:
		void no_collide(Map& map, const IntVector2& src_point);
	protected:
		IntVector2 point;
		int hp;
		int max_hp;
		int damage;
		virtual void collide(Map& map, const IntVector2& src_point);
		virtual void collide_knight(Map& map, const IntVector2& src_point) = 0;
		virtual void collide_princess(Map& map, const IntVector2& src_point) = 0;
		virtual void collide_monster(Map& map, const IntVector2& src_point) = 0;
		virtual void collide_fireball(Map& map, const IntVector2& src_point) = 0;
		virtual void collide_health(Map& map, const IntVector2& src_point);
		void set_coordinate(const IntVector2& src_point, Map& map);
	public:
		Character(const IntVector2& src_point) : point(src_point) {};
		virtual ~Character() {};
		virtual void move(Map& map) = 0;
		virtual char get_symbol() const = 0;
		int get_hp() const;
		int get_damage() const;
		IntVector2 get_point() const;
		void set_hp(const int Hp);
	};

	class Knight : public Character
	{
	private:
		void collide_knight(Map& map, const IntVector2& src_point) {};
		void collide_princess(Map& map, const IntVector2& src_point);
		void collide_monster(Map& map, const IntVector2& src_point);
		void collide_fireball(Map& map, const IntVector2& src_point) {};
	public:
		Knight(const IntVector2& src_point);
		void move(Map& map);
		char get_symbol() const;
	};

	class Princess : public Character
	{
	private:
		void collide_knight(Map& map, const IntVector2& src_point) {};
		void collide_princess(Map& map, const IntVector2& src_point) {};
		void collide_monster(Map& map, const IntVector2& src_point) {};
		void collide_fireball(Map& map, const IntVector2& src_point) {};
	public:
		Princess(const IntVector2& src_point);
		void move(Map& map) {};
		char get_symbol() const;
	};

	class Monster : public Character
	{
	private:
		void collide_knight(Map& map, const IntVector2& src_point);
		void collide_princess(Map& map, const IntVector2& src_point) {};
		void collide_monster(Map& map, const IntVector2& src_point) {};
		void collide_fireball(Map& map, const IntVector2& src_point) {};
	protected:
		virtual void action(Map& map) = 0;
	public:
		Monster(const IntVector2& src_point) : Character(src_point) {};
		void move(Map& map);
	};

	class Dragon : public Monster
	{
	private:
		void action(Map& map) {};
	public:
		Dragon(const IntVector2& src_point);
		char get_symbol() const;
	};

	class Zombie : public Monster
	{
	private:
		void action(Map& map) {};
	public:
		Zombie(const IntVector2& src_point);
		char get_symbol() const;
	};

	class Wizard : public Monster
	{
	private:
		void action(Map& map);
	public:
		Wizard(const IntVector2& src_point);
		char get_symbol() const;
	};

	class Fireball : public Character
	{
	private:
		char path;
		void collide_knight(Map& map, const IntVector2& src_point);
		void collide_princess(Map& map, const IntVector2& src_point);
		void collide_monster(Map& map, const IntVector2& src_point);
		void collide_fireball(Map& map, const IntVector2& src_point);
		void collide_health(Map& map, const IntVector2& src_point);
	public:
		Fireball(const IntVector2& src_point, const char path);
		void move(Map& map);
		char get_path() const;
	};

	class Fireball_Left : public Fireball
	{
	public:
		Fireball_Left(const IntVector2& src_point) : Fireball(src_point, 'a') {};
		char get_symbol() const;
	};

	class Fireball_Right : public Fireball
	{
	public:
		Fireball_Right(const IntVector2& src_point) : Fireball(src_point, 'd') {};
		char get_symbol() const;
	};
	
	class Fireball_Up : public Fireball
	{
	public:
		Fireball_Up(const IntVector2& src_point) : Fireball(src_point, 'w') {};
		char get_symbol() const;
	};
	
	class Fireball_Down : public Fireball
	{
	public:
		Fireball_Down(const IntVector2& src_point) : Fireball(src_point, 's') {};
		char get_symbol() const;
	};
}