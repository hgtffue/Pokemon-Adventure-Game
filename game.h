#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include "Pokemon_battle_index.h"
#include"character.h"

#ifndef GAME_H
#define GAME_H

using namespace std;

class Game {
private:
	vector <WildPokemon> wildPokemon;
	Enemy enemy;
	ItemList itemList;
	int min = 1;
	int max = 3;
public:
	Game(const vector <WildPokemon> wildPokemon, Enemy enemy, ItemList itemList)
	: wildPokemon(wildPokemon), enemy(enemy), itemList(itemList){}
	void action(Player& player,vector<Skill>Database);
	void initial();
	int chooseaction(int Num);
};

#endif
