#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>
#include "Pokemon_battle_index.h"
#include <random>
#include <chrono>

using namespace std;


void Skill::print()
{
 cout << name << " 技能編號:" << skillID << " 屬性:" << type << " 傷害值:" << damage << " 回復值:" << heal << endl;
}
//==================================================================================
Pokemon::Pokemon(string name, int ID, string type) : name(name), ID(ID), type(type)
{
		auto seed = static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    	std::mt19937 rng(seed);
		std::uniform_int_distribution<int> unif(0, 1000);
	this->LV = unif(rng)  % 9 + 1;				//隨機範圍待定
	this->HP = 5 * LV + 11;
	this->exp = 0;
	this->nextlevelExp = LV * LV;
	this->defeatedExp = LV * (unif(rng) % LV + 1);
}//為初始化技能列表，在construct後要使用addSkill()
 //可能可以有更好的方法 

Pokemon::Pokemon(const Pokemon& p):name(p.name), ID(p.ID), type(p.type),LV(p.LV),HP(p.HP),exp(p.exp)
,nextlevelExp(p.nextlevelExp),defeatedExp(p.defeatedExp)
{
	for(int i = 0; i < p.MySkill.size(); i++)
	{
		this->MySkill.push_back(p.MySkill[i]);
	}
}


void Pokemon::levelUP(vector<Skill> Database)		//戰鬥過程中打敗對手會獲得經驗值，那時要while(exp >= nextlevelExp){呼叫此函數}
{
	LV++;
	exp -= nextlevelExp;
	nextlevelExp = LV * LV;
	HP = (8 * LV + 11);
	cout << "等級提升!!" << endl;
	this->print(); 
	if(LV % 2 == 0 or LV % 5 == 0)
	{
		addSkill(Database);			//隨機新增一該寶可夢屬性技能
	}
}

void Pokemon::addSkill(vector<Skill> Database)	//這個database是預先寫好的檔案，會在主程式中被input成vector，丟入所有addSkill函數
{
		auto seed = static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    	std::mt19937 rng(seed);
		std::uniform_int_distribution<int> unif(0, 1000);
	while(true)
	{
		int randomNumber = unif(rng) % Database.size();
		bool check = 0;
		if(Database[randomNumber].type != this->type)
		{
			continue;
		}
		
		for(int i = 0 ; i < this->MySkill.size(); i++)
		{
			if(Database[randomNumber].skillID == MySkill[i].skillID)
			{
				check = 1;
				break;
			}
		}
		if(check == 0)
		{
			(this->MySkill).push_back(Database[randomNumber]);
			break;
		}
	}
	
	cout << "新增技能!!" << endl;   
	this->printSkill();
}

void Pokemon::print()
{
	cout << name << " 編號:" << ID << " 生命值:" << HP << " LV:" << LV << " EXP:" << exp << "/" << nextlevelExp << " 屬性:" << type << endl;
}

void Pokemon::printSkill()
{
	for(int i = 0; i < MySkill.size(); i++)
	{
		MySkill[i].print();
	}
}

void Pokemon::useSkill(int skillUsedID, Pokemon& targetPokemon, double Rate)  throw(logic_error) 
{
	bool haveTheSkill = false;
	for(int i = 0; i < MySkill.size(); i++)
	{
		if(MySkill[i].skillID == skillUsedID)
		{
			haveTheSkill = true;
			cout << this->getName() << "使用了" << MySkill[i].name << " 造成" << MySkill[i].damage * Rate << "點傷害, 回復" << MySkill[i].heal * Rate << "點血量" << endl;  
			targetPokemon.HP -= MySkill[i].damage * Rate;
			this->HP += MySkill[i].heal * Rate;
			cout << this->getName() << "HP為" << this->HP << ", " << targetPokemon.getName() << "HP為" << targetPokemon.HP << endl;
			break;
		}
	}
	if(haveTheSkill == false)
	{ 
		throw logic_error("無此技能");
	} 
}

void Pokemon::useSkillRandom(Pokemon& targetPokemon)
{
		auto seed = static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    	std::mt19937 rng(seed);
		std::uniform_int_distribution<int> unif(0, 1000);
		
	int i = unif(rng) % MySkill.size();
	cout << this->getName() << "使用了" << MySkill[i].name << " 造成" << MySkill[i].damage << "點傷害, 回復" << MySkill[i].heal << "點血量" << endl;  
	targetPokemon.HP -= MySkill[i].damage;
	this->HP += MySkill[i].heal;
	cout << targetPokemon.getName() << "HP為" << targetPokemon.HP << ", " << this->getName() << "HP為" << this->HP << endl;
}
//==================================================================================
WildPokemon::WildPokemon(string name, int ID, string type) : Pokemon(name, ID, type)
{
	this->catchProb = (70 - LV)/100;
}

double WildPokemon:: getCatchProb(){
	return this->catchProb;
}



