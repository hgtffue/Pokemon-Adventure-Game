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


//�۩w�q���A_�ޯ�
struct Skill
{
	string name;	//�ޯ�W
	int skillID;	//�ޯ�s��
	string type;	//�ݩ�
	int damage;		//�ޯ�ˮ`
	int heal;		//�ޯ�^�_

	void print();	//��X���ޯ��T
};


//���O_�_�i��
class Pokemon
{
protected:
	string name;			//�W�r
	int ID;					//�s��
	int nextlevelExp;		//��F�U�@���q���g��ȶq
	int HP;					//�ͩR��
	int exp;				//�ثe�֦����g���
	int LV;					//����
	int defeatedExp;		//���ѫ����o���g���
	string type;			//�ݩ�
	vector <Skill> MySkill; //�ޯ�C��

public:


	Pokemon(string name, int ID, string type);
	Pokemon(const Pokemon& p);			//constructor
//	~Pokemon();				//destructor
	void print();			//��X�_�i�ڸ�T
	void printSkill();		//��X�_�i�کҦ��ޯ��T
	void useSkill(int skillUsedID, Pokemon& targetPokemon, double Rate) throw(logic_error);	//���_�i�ڨϥΧޯ�(�ǤJ�ޯ�ID)
	void useSkillRandom(Pokemon& targetPokemon);
	void levelUP(vector<Skill> Database);			//��exp�j��nextlevelExp�AlevelUP�A����@�ǫ��O
	void addSkill(vector<Skill> Database);		//�H���s�W�@���_�i���ݩʧޯ�
	string getName(){return name;}
	int getID(){return ID;}

friend class Battle;
friend class Item;
friend class ItemList;
friend class HealingPotion;
friend class ExpApple;
};

//���O_�����_�i��
class WildPokemon : public Pokemon
{
private:
	double catchProb;		//�������v

public:
	WildPokemon(string name, int ID, string type);			//constructor
	~WildPokemon(){}			//destructor
	double getCatchProb();

};


#endif // POKEMON_BATTLE_INDEX_H


