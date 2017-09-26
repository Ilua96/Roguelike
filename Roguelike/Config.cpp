#include "Config.h"
#include <fstream>

using namespace std;

Config::Config() {
	int c, count;
	string n;
	int d, h, t;
	ifstream fin("config.txt");
	if (!fin.is_open()) {
		printf("Can not open file: config.txt");
		fin.close();
		exit(1);
	}
	fin >> c;
	for (int j = 0; j < c; j++) {
		fin >> n >> count;
		if (n == "Characters")
			for (int i = 0; i < count; i++) {
				fin >> n >> d >> h;
				characters.insert(make_pair(n, make_pair(d, h)));
			}
		else if (n == "Respawns")
			for (int i = 0; i < count; i++) {
				fin >> n >> t;
				respawns.insert(make_pair(n, t));
			}
		else {
			printf("The data is invalid");
			fin.close();
			exit(1);
		}
	}
	string  e;
	fin >> e;
	if (e != "endf") {
		printf("The data is invalid");
		fin.close();
		exit(1);
	}
	fin.close();
}

void Config::find_obj(const string name) const {
	if (characters.find(name) == characters.end() && respawns.find(name) == respawns.end()) {
		printf("The data is invalid");
		exit(1);
	}
}

int Config::get_character_damage(const string name) const{
	find_obj(name);
	return characters.find(name)->second.first;
}

int Config::get_character_health(const string name) const {
	find_obj(name);
	return characters.find(name)->second.second;
}

int Config::get_respawn_time(const string name) const {
	find_obj(name);
	return respawns.find(name)->second;
}