#pragma once

#include "Point.h"
#include "Map.h"
#include <vector>

#define HEALTH_SUMBOL '+'
#define RESPAWN_ZOMBIE_SYMBOL 'C'
#define RESPAWN_DRAGON_SYMBOL 'N'
#define RESPAWN_WIZARD_SYMBOL 'T'

namespace Respawns
{
	class Respawn
	{
	protected:
		IntVector2 point;
		int time = 0;
		int respawn_time;
		virtual void creat_obj(Map& map) = 0;
	public:
		Respawn(const IntVector2& src_point, const int src_time) : point(src_point), respawn_time(src_time) {};
		~Respawn() {};
		void check_time(Map& map);
		IntVector2 get_point() const;
		int get_time() const;
		int get_respawn_time() const;
	};

	class Respawn_Health : public Respawn
	{
	private:
		int helth = 25;
		int count = 5;
		bool stop_respawn = false;
		std::vector < IntVector2 > obj;
		void creat_obj(Map& map) override;
	public:
		Respawn_Health();
		void delete_obj(const IntVector2& src_point);
		int get_health() const;
	};

	class Respawn_Monsters : public Respawn
	{
	private:
		virtual void creat_obj(Map& map);
	public:
		Respawn_Monsters(const IntVector2& src_point, const int src_time) : Respawn(src_point, src_time) {};
		virtual char get_symbol() const = 0;
	};

	class Respawn_Zombie : public Respawn_Monsters
	{
	public:
		Respawn_Zombie(const IntVector2& src_point);
		char get_symbol() const;
	};

	class Respawn_Dragon : public Respawn_Monsters
	{
	public:
		Respawn_Dragon(const IntVector2& src_point);
		char get_symbol() const;
	};

	class Respawn_Wizard : public Respawn_Monsters
	{
	public:
		Respawn_Wizard(const IntVector2& src_point);
		char get_symbol() const;
	};
}