#include <iostream>
#include <cstdlib>  // create random number
#include <ctime>    // create seed
#include <cmath> // log
#include <fstream> // input file
#include <sstream> // input file
#include <string>
#include "Pokemon_battle_index.h"
#include"itemHeader.h"


#ifndef CHARACTER_H
#define CHARACTER_H

using namespace std;

class Character {
protected:
    string name;
    vector<Pokemon> MyPokemon;
    int PokemonNum = 0;

public:
    Character(const string& n);
    string getName() const;
//    virtual vector<Pokemon> getMyPokemon();
    void addPokemon(Pokemon pokemon);
    friend class Battle;
};

//=================================================

class Enemy : public Character {
public:
    Enemy(const string& n);
    vector<Pokemon> getMyPokemon() ;
};

//=================================================

class Player : public Character {
private :
	ItemList itemList; 

public :
	Player (const string & n);
	void Action (int n,vector<Skill> Database);
	void MyPokemonprint();
    	void getitem(int id);
    	friend class Game;
    	friend class Battle;
    	friend main();
};

//=================================================


//類別_戰鬥
class Battle	//注意此區的call by reference
{
private:
	Player player;
	Enemy enemy;
	vector <Pokemon>& playerPokemon;
	vector <Pokemon*> pickedPokemon;
	vector <Pokemon> enemyPokemon;
	vector <Pokemon> enemyPickedPokemon;

	void ending();

public:
	Battle(Player& player, Enemy& enemy);
//	~Battle();
	void start();
	void round(vector<Skill> Database);

};

#endif
