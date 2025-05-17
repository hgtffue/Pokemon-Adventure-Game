#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include"game.h"
#include "Pokemon_battle_index.h"
#include <random>
#include <chrono>

using namespace std;

void Game::action(Player& player,vector<Skill>Database)
{
		auto seed = static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    	std::mt19937 rng(seed);
		std::uniform_int_distribution<int> unif(0, 1000);
	int scenes = unif(rng) % (this->max - this->min + 1) + this->min;
//		scenes =3;
	if(scenes == 1)			//wildPokemon
	{
		cout <<"�����_�i�ڥX�{�F�I" <<endl;
		WildPokemon wildPoke("",0,"");
		int pokemonCnt = wildPokemon.size();
		auto seed = static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    	std::mt19937 rng(seed);
		std::uniform_int_distribution<int> unif(0, 1000);
		
		while(true)			//���X�����_�i��(���a�S�����_�i�ں���) 
		{
			bool isWildPokemon = 1;
			int pokemonId = unif(rng) % (pokemonCnt - this->min + 1) + this->min;
			for(int i = 0 ; i < player.PokemonNum ; i++)
			{
				if(player.MyPokemon[i].getID() == pokemonId)
				{
					isWildPokemon = 0;
					break;
				}
			}
			
			if(isWildPokemon == 1)
			{
				wildPoke = wildPokemon[pokemonId - 1];
				break;
			}
		}
		wildPoke.print();
		bool addPokemonOrNot = player.itemList.usePokeBall(wildPoke);
		if(addPokemonOrNot == 1)
		{
			player.addPokemon(wildPoke);

			
		}
			cout << "���������^" << endl;
			string act;
			cin >> act;
		return;
	}
	else if(scenes == 2)	//enemy
	{
		cout <<"�ĤH�X�{�F�I" <<endl;
//		vector <Pokemon> enemyPickedPokemon = this->enemy.getMyPokemon();
//		for(int i = 0 ; i < 3 ; i++)
//			battlePokemon[i].print();
		if(player.PokemonNum < 3)
		{
			cout <<"�_�i�ڤ����T�ӡA�L�k�԰��I���������^" <<endl;
			string act;
			cin >> act;
			return;
		}
		Battle battle(player, this->enemy);
		battle.start();
		battle.round(Database);
		return;
	}
	else if(scenes == 3)	//item
	{
		cout << "�o�̦����_�c�I"<< endl;
		int itemNum = this->itemList.getRandomItem();
		player.itemList.addItem(itemNum);
		cout << "���������^" << endl;
		string act;
		cin >> act;
		return;
	}
	else
	{
		cout << scenes;
		cout << "���������^" << endl;
		string act;
		cin >> act;
		return;
	}
}


void Game::initial()//��l�Ƭɭ�
{
    using namespace std;
    system("cls");
//    cout <<"Welcome to the pokemon world!"<<endl;
    //cout<<"���гo�ӹC��"<<endl;
    cout <<"��J�A�����:"<<endl;
    cout <<"1: �����䪺�� "<<endl <<"2: ���������� "<<endl<<
	"3: ���k�䪺�� "<<endl<<"4: �d�ݶ���"<<endl<<"5: ���}�I�]" <<endl<<"��L�G�h�X�C��" <<endl ;
}

int Game::chooseaction(int Num)//���a??�ʧ@�A�Q��???���a����?�J
{
    cin >> Num;
    if (cin.fail()) {
  		cin.clear();
    	cin.ignore();
    	cout <<"�T�w�h�X�C���H(Y/N)" <<endl;
		string yn;
		while(cin >> yn)
		{
			if(yn == "N" or yn == "n")
			{
			return  9;
			}
			else if(yn == "Y" or yn == "y")
			{exit(1);}
			else
			{
				cout << "�L�Ŀ�J�A�Э��s��J"<<endl;
			}
 		}
 	}
    else if(Num!=1&&Num!=2&&Num!=3 && Num !=4 && Num !=5)
    {
        cout <<"�T�w�h�X�C���H(Y/N)" <<endl;
		string yn;
		while(cin >> yn)
		{
			if(yn == "N")
			{
///			Num=chooseaction(Num);
			return  9;
			}
			else if(yn == "Y")
			{exit(1);}
			else
			{
				cout << "�L�Ŀ�J�A�Э��s��J"<<endl;
			}
        
    	}
	}

    return Num;
}
