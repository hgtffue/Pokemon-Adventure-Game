#include"itemHeader.h"
#include "Pokemon_battle_index.h"
#include"character.h"
#include"game.h"
#include <iostream>
#include <cstdlib>  // create random number
#include <ctime>    // create seed
#include <cmath> // log
#include <fstream> // input file
#include <sstream> // input file
#include <windows.h> // input file



//�_�i�ڹ�Ų�V�q�M�ޯ��Ų�A�����ܼ�
vector <WildPokemon> WildPokedex;
vector <Skill> SkillDatabase;
void print();

using namespace std;

int main(){
	
	ItemList itemDic;
	vector <Pokemon> Pokedex;

	//�B�zinputfile�A�ޯ��Ų
	Skill inputSkill;
	string Sname, Stype;
	int SID, Sdamage, Sheal;
	ifstream SkillIndex;
	SkillIndex.open("Skilldex.txt");
	if(SkillIndex){
		while(!SkillIndex.eof()){
			SkillIndex >> Sname >> SID >> Stype >> Sdamage >> Sheal;
			inputSkill = {Sname, SID, Stype, Sdamage, Sheal};
			SkillDatabase.push_back(inputSkill);
		}
	}
	else
		cout << "Skilldex File open failed" << endl;
	SkillIndex.close();
	
	//���Ф@��
    Enemy enemy("Enemy");

	//�B�zinputfile�A�_�i�ڹ�Ų
	string PokeName, PokeType;
	int PokeID;
	ifstream PokemonIndex;
	PokemonIndex.open("Pokedex.txt");	//�ɮצ�m
	if(PokemonIndex){
		while(!PokemonIndex.eof())
		{
			PokemonIndex >> PokeName >> PokeID >> PokeType;
			Pokemon inputPokemon(PokeName, PokeID, PokeType);
			for(int i = 0; i < 3; i++)
				inputPokemon.addSkill(SkillDatabase);
			Pokedex.push_back(inputPokemon);
			enemy.addPokemon(inputPokemon);

			WildPokemon inputWildPokemon(PokeName, PokeID, PokeType);
			for(int i = 0; i < 3; i++)
				inputWildPokemon.addSkill(SkillDatabase);
			WildPokedex.push_back(inputWildPokemon);
		}
	}
	else
		cout << "Pokedex File open failed" << endl;
	PokemonIndex.close();

	Player player1("Player");
	player1.addPokemon(Pokedex[0]);
    Game game(WildPokedex, enemy, itemDic);

	system("cls");
	print();
	cout <<endl << "�����N��}�l�C��" << endl;
    string a;
	cin >> a;


	system("cls");
    while (true)
	{
        game.initial();
        int actionnum;
        actionnum = game.chooseaction(actionnum);
        if (actionnum==1 or actionnum == 2 or actionnum == 3)
		{
            game.action(player1,SkillDatabase);
        }
        else if (actionnum==4 or actionnum == 5)
		{
            player1.Action(actionnum,SkillDatabase);
        }
    }

return 0; }

void print()
{
	cout << "�w��Ө�m�_�i�ڥ@�ɤj���I�n�I�I�I"<< endl;
	cout << "�b�o�ӥR���_�i�ڪ��a�ϡA�A�i�H���N��ܷQ�����D���A" << endl
	<<"�C�@�������|�a��A�g���@���_�����o�{�P�_�I�I" << endl;
	cout << endl;
	cout <<"���I�~���A�A�i��|��쯫�����_�c�A�õ۵}���_���F" << endl
	<<"�i��|�o�{�����_�i�ڡA���ۧA�Ӧ��A�æ����L���n�͡F" << endl
 	<<"�]�i��|�J������԰������A�M�L�g���@����i��E���M���I" << endl
	<<"�{�b�N�X�o�i�}�A���_�i�ڮȵ{�a�I" << endl;
	string a;
	cout << endl;
	cout << "�����N��i�J�_������" << endl;
	cin >> a;
	cout <<"�_�����СG" << endl ;
	cout <<"���C���@���|���_���G" << endl <<
	"1. ���F�y�G" << endl <<
	"���@��B���šB�W�ŤT�ءA�����P���������v�A"<< endl <<"�@�}�l���a�|����U�����A�i�H�ΨӮ����_�i�ڡC" << endl <<
	"2. �v���Ĥ��G" << endl <<
	"���@��B���šB�W�ŤT�ءA�����P����_�O�A"<< endl<<"�i�H�b�԰����v�����˪��_�i�����_�i�ڦ^��C" << endl <<
	"3. �g��G�G" << endl <<
	"���@��B���Ũ�ءA��W�[�_�i�ڪ��g��ȡA�i�H�b�I�]�ϥΡC" << endl <<
	"4. ���B�šG" << endl <<
	"���������B�šA�԰����B�šA���y�ŤT�ءC" << endl <<"�������B�ťi�H�W�[�����_�i�ڪ����v�A�԰����B�ťi�H���ɾ԰�"
	<<"�����ޯ�ĪG�A"<< endl << "���y�Ŧb�I�]�ϥΡA�i�H�H����o�@�Ө�L�_���C"<< endl;
}
