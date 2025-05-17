#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>

#ifndef POKEMON_BATTLE_INDEX_H
#define POKEMON_BATTLE_INDEX_H

using namespace std;


//自定義型態_技能
struct Skill
{
	string name;	//技能名
	int skillID;	//技能編號
	string type;	//屬性
	int damage;		//技能傷害
	int heal;		//技能回復

	void print();	//輸出本技能資訊
};


//類別_寶可夢
class Pokemon
{
protected:
	string name;			//名字
	int ID;					//編號
	int nextlevelExp;		//到達下一階段的經驗值量
	int HP;					//生命值
	int exp;				//目前擁有的經驗值
	int LV;					//等級
	int defeatedExp;		//打敗後能獲得的經驗值
	string type;			//屬性
	vector <Skill> MySkill; //技能列表

public:


	Pokemon(string name, int ID, string type);
	Pokemon(const Pokemon& p);			//constructor
//	~Pokemon();				//destructor
	void print();			//輸出寶可夢資訊
	void printSkill();		//輸出寶可夢所有技能資訊
	void useSkill(int skillUsedID, Pokemon& targetPokemon, double Rate) throw(logic_error);	//對寶可夢使用技能(傳入技能ID)
	void useSkillRandom(Pokemon& targetPokemon);
	void levelUP(vector<Skill> Database);			//當exp大於nextlevelExp，levelUP，執行一些指令
	void addSkill(vector<Skill> Database);		//隨機新增一該寶可夢屬性技能
	string getName(){return name;}
	int getID(){return ID;}

friend class Battle;
friend class Item;
friend class ItemList;
friend class HealingPotion;
friend class ExpApple;
};

//類別_野生寶可夢
class WildPokemon : public Pokemon
{
private:
	double catchProb;		//捕捉機率

public:
	WildPokemon(string name, int ID, string type);			//constructor
	~WildPokemon(){}			//destructor
	double getCatchProb();

};


#endif // POKEMON_BATTLE_INDEX_H


