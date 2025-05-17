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
		cout <<"野生寶可夢出現了！" <<endl;
		WildPokemon wildPoke("",0,"");
		int pokemonCnt = wildPokemon.size();
		auto seed = static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    	std::mt19937 rng(seed);
		std::uniform_int_distribution<int> unif(0, 1000);
		
		while(true)			//產出野生寶可夢(玩家沒有的寶可夢種類) 
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
			cout << "按任何鍵返回" << endl;
			string act;
			cin >> act;
		return;
	}
	else if(scenes == 2)	//enemy
	{
		cout <<"敵人出現了！" <<endl;
//		vector <Pokemon> enemyPickedPokemon = this->enemy.getMyPokemon();
//		for(int i = 0 ; i < 3 ; i++)
//			battlePokemon[i].print();
		if(player.PokemonNum < 3)
		{
			cout <<"寶可夢不足三個，無法戰鬥！按任何鍵返回" <<endl;
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
		cout << "這裡有個寶箱！"<< endl;
		int itemNum = this->itemList.getRandomItem();
		player.itemList.addItem(itemNum);
		cout << "按任何鍵返回" << endl;
		string act;
		cin >> act;
		return;
	}
	else
	{
		cout << scenes;
		cout << "按任何鍵返回" << endl;
		string act;
		cin >> act;
		return;
	}
}


void Game::initial()//初始化界面
{
    using namespace std;
    system("cls");
//    cout <<"Welcome to the pokemon world!"<<endl;
    //cout<<"介紹這個遊戲"<<endl;
    cout <<"輸入你的選擇:"<<endl;
    cout <<"1: 走左邊的路 "<<endl <<"2: 走中間的路 "<<endl<<
	"3: 走右邊的路 "<<endl<<"4: 查看隊伍"<<endl<<"5: 打開背包" <<endl<<"其他：退出遊戲" <<endl ;
}

int Game::chooseaction(int Num)//玩家??動作，利用???玩家正确?入
{
    cin >> Num;
    if (cin.fail()) {
  		cin.clear();
    	cin.ignore();
    	cout <<"確定退出遊戲？(Y/N)" <<endl;
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
				cout << "無效輸入，請重新輸入"<<endl;
			}
 		}
 	}
    else if(Num!=1&&Num!=2&&Num!=3 && Num !=4 && Num !=5)
    {
        cout <<"確定退出遊戲？(Y/N)" <<endl;
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
				cout << "無效輸入，請重新輸入"<<endl;
			}
        
    	}
	}

    return Num;
}
