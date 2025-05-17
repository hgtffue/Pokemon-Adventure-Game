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



//寶可夢圖鑑向量和技能圖鑑，全域變數
vector <WildPokemon> WildPokedex;
vector <Skill> SkillDatabase;
void print();

using namespace std;

int main(){
	
	ItemList itemDic;
	vector <Pokemon> Pokedex;

	//處理inputfile，技能圖鑑
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
	
	//先創一個
    Enemy enemy("Enemy");

	//處理inputfile，寶可夢圖鑑
	string PokeName, PokeType;
	int PokeID;
	ifstream PokemonIndex;
	PokemonIndex.open("Pokedex.txt");	//檔案位置
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
	cout <<endl << "按任意鍵開始遊戲" << endl;
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
	cout << "歡迎來到《寶可夢世界大探險》！！！"<< endl;
	cout << "在這個充滿寶可夢的地圖，你可以任意選擇想走的道路，" << endl
	<<"每一條路都會帶領你經歷一次奇妙的發現與冒險！" << endl;
	cout << endl;
	cout <<"探險途中，你可能會找到神秘百寶箱，藏著稀有寶物；" << endl
	<<"可能會發現野生寶可夢，等著你來收服並成為他的好友；" << endl
 	<<"也可能會遇見渴望戰鬥的對手，和他經歷一場緊張刺激的決鬥！" << endl
	<<"現在就出發展開你的寶可夢旅程吧！" << endl;
	string a;
	cout << endl;
	cout << "按任意鍵進入寶物介紹" << endl;
	cin >> a;
	cout <<"寶物介紹：" << endl ;
	cout <<"本遊戲共有四種寶物：" << endl <<
	"1. 精靈球：" << endl <<
	"有一般、高級、超級三種，有不同的捕捉機率，"<< endl <<"一開始玩家會拿到各五顆，可以用來捕捉寶可夢。" << endl <<
	"2. 治療藥水：" << endl <<
	"有一般、高級、超級三種，有不同的恢復力，"<< endl<<"可以在戰鬥中治療受傷的寶可夢幫寶可夢回血。" << endl <<
	"3. 經驗果：" << endl <<
	"有一般、高級兩種，能增加寶可夢的經驗值，可以在背包使用。" << endl <<
	"4. 幸運符：" << endl <<
	"有捕捉幸運符，戰鬥幸運符，獎勵符三種。" << endl <<"捕捉幸運符可以增加捕捉寶可夢的機率，戰鬥幸運符可以提升戰鬥"
	<<"中的技能效果，"<< endl << "獎勵符在背包使用，可以隨機獲得一個其他寶物。"<< endl;
}
