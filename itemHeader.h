#include <iostream>
#include <cstdlib>  // create random number
#include <ctime>    // create seed
#include <cmath> // log
#include <fstream> // input file
#include <sstream> // input file
#include <string>
#include <chrono>
#include "Pokemon_battle_index.h"


#ifndef ITEMHEADER_H
#define ITEMHEADER_H


class Item {
protected :
	std :: string name;
	std :: string chName;
	std :: string description; //print out to let player know what can this item do
	std :: string type;
	int num;
public :
	Item (const std :: string& n, const std :: string& ch);
	std :: string getName () const {return name ;}
	void print()const;
	friend class ItemList;
};

class PokeBall : public Item{
private :
	double catchChance; //probability to catch the pokemon
	//name will be normal, great, master
public :
	PokeBall (const std :: string& n,const std :: string& ch);
	void printBallInfo() const; // print info of the ball
	bool catchPokemon(WildPokemon w, double CharmRate); // return weather successfully catch a pokemon
	double getCatchChance () const { return catchChance;}

};

class HealingPotion : public Item {
private :
	int healAmount;
public :
	HealingPotion(const std :: string&n, const std :: string& ch);
	void healing(Pokemon& p, int num);
	void printPotionInfo() const;
};

class ExpApple : public Item {
private :
	int expBoost;
public :
	ExpApple(const std :: string&n, const std :: string& ch);
	void training(Pokemon& p,vector<Skill> Database);
	void printExpAppleInfo() const;
};

class LuckyCharm : public Item{
private :
	double captureBoost;
	double skillBoost;
	bool rewardItem;
public :
	LuckyCharm(const std :: string&n, const std :: string& ch);
	void printCharmInfo() const;
	double getCapRate() const{return captureBoost;	}
	double getSkillRate() const{return skillBoost;	}
	int getRewardItem();
};

class ItemList {
private:
    Item* items[11];
	int itemCnt;
public:
	ItemList();
    void addItem(int id);
	void printItemList();
	bool usePokeBall(WildPokemon w);
	void usePotion(Pokemon& p);
	bool useExpApple(Pokemon& p,vector<Skill> Database);
	int useCharm();//reward
	double useBatCharm();//battle
	double useCapCharm();//capture
    void createItemDic(const std::string& filename);
    int getRandomItem();
    Item* getItem(int index);
};

#endif
