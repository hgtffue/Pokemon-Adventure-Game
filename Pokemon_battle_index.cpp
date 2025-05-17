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
 cout << name << " �ޯ�s��:" << skillID << " �ݩ�:" << type << " �ˮ`��:" << damage << " �^�_��:" << heal << endl;
}
//==================================================================================
Pokemon::Pokemon(string name, int ID, string type) : name(name), ID(ID), type(type)
{
		auto seed = static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    	std::mt19937 rng(seed);
		std::uniform_int_distribution<int> unif(0, 1000);
	this->LV = unif(rng)  % 9 + 1;				//�H���d��ݩw
	this->HP = 5 * LV + 11;
	this->exp = 0;
	this->nextlevelExp = LV * LV;
	this->defeatedExp = LV * (unif(rng) % LV + 1);
}//����l�Ƨޯ�C��A�bconstruct��n�ϥ�addSkill()
 //�i��i�H����n����k 

Pokemon::Pokemon(const Pokemon& p):name(p.name), ID(p.ID), type(p.type),LV(p.LV),HP(p.HP),exp(p.exp)
,nextlevelExp(p.nextlevelExp),defeatedExp(p.defeatedExp)
{
	for(int i = 0; i < p.MySkill.size(); i++)
	{
		this->MySkill.push_back(p.MySkill[i]);
	}
}


void Pokemon::levelUP(vector<Skill> Database)		//�԰��L�{�����ѹ��|��o�g��ȡA���ɭnwhile(exp >= nextlevelExp){�I�s�����}
{
	LV++;
	exp -= nextlevelExp;
	nextlevelExp = LV * LV;
	HP = (8 * LV + 11);
	cout << "���Ŵ���!!" << endl;
	this->print(); 
	if(LV % 2 == 0 or LV % 5 == 0)
	{
		addSkill(Database);			//�H���s�W�@���_�i���ݩʧޯ�
	}
}

void Pokemon::addSkill(vector<Skill> Database)	//�o��database�O�w���g�n���ɮסA�|�b�D�{�����Qinput��vector�A��J�Ҧ�addSkill���
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
	
	cout << "�s�W�ޯ�!!" << endl;   
	this->printSkill();
}

void Pokemon::print()
{
	cout << name << " �s��:" << ID << " �ͩR��:" << HP << " LV:" << LV << " EXP:" << exp << "/" << nextlevelExp << " �ݩ�:" << type << endl;
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
			cout << this->getName() << "�ϥΤF" << MySkill[i].name << " �y��" << MySkill[i].damage * Rate << "�I�ˮ`, �^�_" << MySkill[i].heal * Rate << "�I��q" << endl;  
			targetPokemon.HP -= MySkill[i].damage * Rate;
			this->HP += MySkill[i].heal * Rate;
			cout << this->getName() << "HP��" << this->HP << ", " << targetPokemon.getName() << "HP��" << targetPokemon.HP << endl;
			break;
		}
	}
	if(haveTheSkill == false)
	{ 
		throw logic_error("�L���ޯ�");
	} 
}

void Pokemon::useSkillRandom(Pokemon& targetPokemon)
{
		auto seed = static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    	std::mt19937 rng(seed);
		std::uniform_int_distribution<int> unif(0, 1000);
		
	int i = unif(rng) % MySkill.size();
	cout << this->getName() << "�ϥΤF" << MySkill[i].name << " �y��" << MySkill[i].damage << "�I�ˮ`, �^�_" << MySkill[i].heal << "�I��q" << endl;  
	targetPokemon.HP -= MySkill[i].damage;
	this->HP += MySkill[i].heal;
	cout << targetPokemon.getName() << "HP��" << targetPokemon.HP << ", " << this->getName() << "HP��" << this->HP << endl;
}
//==================================================================================
WildPokemon::WildPokemon(string name, int ID, string type) : Pokemon(name, ID, type)
{
	this->catchProb = (70 - LV)/100;
}

double WildPokemon:: getCatchProb(){
	return this->catchProb;
}



