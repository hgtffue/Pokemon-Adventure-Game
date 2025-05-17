#include "Pokemon_battle_index.h"
#include"character.h"
#include <windows.h>

Character::Character(const string& n): name(n) { MyPokemon = {}; }

string Character::getName() const { return name; }

void Character::addPokemon(Pokemon pokemon)
{
    MyPokemon.push_back(pokemon);
    PokemonNum++;
}

Enemy:: Enemy(const string& n) : Character(n) {};

vector<Pokemon> Enemy::getMyPokemon()
{
    vector<Pokemon> battlePokemon;
    int PokemonCnt = this->PokemonNum;

    for (int i = 0; i < 3; i++)
	{
        srand(time(nullptr));
        int min = 1;
        int max = PokemonCnt;
        // 產生 [min , max] 的整數亂數 //
        int PokemonId = rand() % (max - min + 1) + min;
        for (int j = 0; j < PokemonNum; j++)
		{
            if (MyPokemon[j].getID() == PokemonId)
			{
                battlePokemon.push_back(MyPokemon[j]);
                PokemonCnt--;
                break;
            }
        }

    }
    return battlePokemon;
}

Player::Player(const string & n): Character (n), itemList(ItemList())
{
	for(int i = 0; i < 5; i++)
	{
		itemList.addItem(0);
		itemList.addItem(1);
		itemList.addItem(2);
	}
};

void Player::Action(int n, vector<Skill> Database)
{
    if (n == 4)//查看隊伍
	{
	    if(this->PokemonNum == 0)
		{
			cout << "你沒有任何寶可夢" << endl;
			cout << "按任意鍵回到主畫面" << endl;
            string a;
			cin >> a;
			return;
		}
		else
		{
			MyPokemonprint();
	    	bool rightpokemon=0;
	        while(rightpokemon==0)
			{
	        	cout <<"輸入編號選擇你要查看技能的寶可夢："<<endl;
	            int idNumber;
	            cin >> idNumber;
	        	if (cin.fail())
				{
	           	cin.clear();
		        cin.ignore();
		        cout<<"你沒有此寶可夢，請重新選擇"<<endl;
				}
				else
				{
					for(int i = 0 ; i < PokemonNum ; i++)
					{
                    	if(MyPokemon[i].getID() == idNumber)
						{
                        	MyPokemon[i].printSkill();
                        	rightpokemon = 1;
                        	cout << "按任意鍵回到主畫面" << endl;
				            string a;
							cin >> a;
							return;
                    	}
            		}
            	if (rightpokemon == 0)
				{
                	cout<<"你沒有此寶可夢，請重新選擇"<<endl;
            	}
				}
			}
        }
    }
    if (n==5)//打開背包
	{
        this->itemList.printItemList();//輸出背包內物品
		cout << "請選擇你要使用的道具：" << endl << "1:經驗果" << endl
		<< "2:獎勵符" << endl << "其他：回到主畫面" << endl;
        string act;
        int k;
        while(cin >> act)
		{
			try
				{
	        		k = std::stoi(act);
	    		}
			catch (exception e) {}
	        if (k != 1 and k != 2)
			{
			return;
        	}
        	if (k==1)
			{
	            MyPokemonprint();
	            cout << "請輸入編號選擇你要升級的寶可夢：" << endl;
	            int idNumber;
	            bool haveA = true;
	            while(cin >> idNumber)
            	{
            		bool rightpokemon=0;
            		for(int i = 0 ; i < PokemonNum ; i++)
					{
                		if(MyPokemon[i].getID() == idNumber)
						{
                   			haveA = this->itemList.useExpApple(MyPokemon[i],Database);
                    		rightpokemon = 1;
//                    		Sleep(1500);
                    		break;
                		}
            		}
            		if(haveA == false)
		            {
		            	Sleep(1500);
		            	return;
					}
            		if (rightpokemon == 0)
					{
		                cout<<"你沒有此寶可夢，請重新輸入或按N回到主畫面" << endl;
		                string a;
						cin >> a;
						if(a == "N")
						    return;
            		}
            	}
        	}

        	if (k==2)
			{
	            int n = this->itemList.useCharm();
			    this->itemList.addItem(n);
			    cout << "按任意鍵回到主畫面" << endl;
	            string a;
				cin >> a;
				return;

        	}
		}
    }
}

void Player::MyPokemonprint()
{
	for(int i = 0 ; i < PokemonNum ; i++)
	{
        MyPokemon[i].print();
    }
}

void Player::getitem(int id){this->itemList.addItem(id); }

//==================================================================================
Battle::Battle(Player& player, Enemy& enemy) : player(player), enemy(enemy),
 playerPokemon(player.MyPokemon), enemyPokemon(enemy.MyPokemon){}

void Battle::start()
{
	for(int i = 0; i < 3; i++)
	{
		enemyPickedPokemon.push_back(enemy.getMyPokemon()[i]);
	}
	
	cout << "對手的出戰寶可夢有" << endl;
	for(int i = 0; i < 3; i++)
		enemyPickedPokemon[i].print();
	cout << " " << endl;
	
	cout << "選擇三個寶可夢出戰" << endl;
	for(int i = 0; i < playerPokemon.size(); i++)
	{
		playerPokemon[i].print();
	}
	cout << "輸入三個編號" << endl;
	int ID[3] = {0};
	for(int i = 0; i < 3; i++)
	{
		bool have = false;
		bool repeat = false;
		cin >> ID[i];
		if(cin.fail())
		{
  		    cin.clear();
    	    cin.ignore();
    	    cout << "輸入錯誤，請重新選擇" << endl;
		    i--;
		    continue;
    	}
		for(int j = 0; j < i; j++)
		{
			if(ID[i] == ID[j])
			{
				repeat = true;
				cout << "不可重複選擇寶可夢" << endl;
				i--;
				break;
			}
		}
		if(repeat == true)
			continue;
		for(int j = 0; j < playerPokemon.size(); j++)
		{
			if(ID[i] == playerPokemon[j].getID())
			{
				have = true;
				pickedPokemon.push_back(&playerPokemon[j]);
				break;
			}
		}
		if(have == false){
			cout << "你並沒有編號為" << ID[i] << "的寶可夢，請重新選擇" << endl;
			i--;
			continue;
		}
	}
}

void Battle::ending()
{
	for(int i = 0; i < playerPokemon.size(); i++)
	{
		playerPokemon[i].HP = 5 * playerPokemon[i].LV + 11;		//same with lv
	}
}

void Battle::round(vector<Skill> Database)
{
	int round = 0;
	bool roundresult[3] = {0};
	cout << "戰鬥開始!" << endl;
	for(int i = 0; i < 3; i++)
	{
		double skillBoostRate = 1;
		round++;
		cout << endl;
 		cout << "第" << round << "輪" << endl;
		cout << "你派出了" << pickedPokemon[i]->getName() << endl;
		cout << "對方派出了" << enemyPickedPokemon[i].getName() << endl;
		while(true)
		{
			string order;
			cout << endl;
			cout << "請輸入指令，查看/使用技能請按z、使用道具請按x。" << endl;
			try{
				cin >> order;
				if(order == "z")
				{
					bool back = false;
					int skillIDtoUse = 0;
					pickedPokemon[i]->printSkill();
					cout << "請輸入技能編號以使用技能，若要返回前一頁請按0" << endl;
					while(true)		//檢查輸入
					{
						try
						{
							cin >> skillIDtoUse;
							if (cin.fail()) {
		           				throw ios_base::failure("請輸入技能編號");
		        			}
		        			else{
		        				if(skillIDtoUse == 0){
		        					back = true;
		        					break;
								}
								else{
									pickedPokemon[i]->useSkill(skillIDtoUse, enemyPickedPokemon[i], skillBoostRate);
									break;
								}
							}
						}
						catch(ios_base::failure e){
							cout << e.what() << endl;
							cin.clear();
							cin.ignore();
							continue;
						}
						catch(logic_error e3){
							cout << e3.what() << endl;
							cin.clear();
							cin.ignore();
							continue;
						}
					}
					if(back == true)
						continue;
					if(enemyPickedPokemon[i].HP <= 0)
					{
						cout << endl;
						cout << "你打敗了對手，恭喜你贏得第" << round << "輪" << endl;
						roundresult[i] = 1;
						cout << pickedPokemon[i]->getName() << "獲得了" << enemyPickedPokemon[i].defeatedExp << "點經驗值" << endl;
						pickedPokemon[i]->exp += enemyPickedPokemon[i].defeatedExp;
						while(pickedPokemon[i]->exp >= pickedPokemon[i]->nextlevelExp){
							pickedPokemon[i]->levelUP(Database);
						}
						Sleep(2000);
						break;
					}
			    }
			    else if(order == "x")
			    {
			    	bool back = false;
			    	int itemInput = 0;
			    	(player.itemList).printItemList();
			    	cout << "請選擇使用的道具，按1使用藥水、按2使用戰鬥幸運符，若要返回前一頁請按0" << endl;
			    	while(true)		//檢查輸入
					{
						try
						{
							cin >> itemInput;
							if (cin.fail()) {
		           				throw ios_base::failure("請輸入0/1/2");
		        			}
		        			else{
		        				if(itemInput == 0){
		        					back = true;
		        					break;
								}
								else if(itemInput == 1){
									(player.itemList).usePotion(*pickedPokemon[i]);
									break;
								}
								else if(itemInput == 2){
									skillBoostRate = (player.itemList).useBatCharm();
									cout << "你使用戰鬥幸運符增加了" << skillBoostRate << "倍技能效果！" << endl;
									Sleep(1500);
									break;
								}
								else
									throw ios_base::failure("請輸入0/1/2");
							}
						}
						catch(ios_base::failure e){
							cout << e.what() << endl;
							cin.clear();
							cin.ignore();
							continue;
						}
					}
					if(back == true)
						continue;
				}
				else
					throw logic_error("無此指令");
			}
			catch(logic_error e2)
			{
				cout << e2.what() << endl;
				cin.clear();
				cin.ignore();
				continue;
			}

			//輪到enemy動作
			cout << endl;
			cout << "輪到對手動作..." << endl;
			Sleep(1000);
			enemyPickedPokemon[i].useSkillRandom(*pickedPokemon[i]);
			if(pickedPokemon[i]->HP <= 0)
			{
				cout << endl;
				cout << "你敗給了對手，很可惜輸了第" << round << "輪" << endl;
				roundresult[i] = 0;
				Sleep(1500);
				break;
			}

		}//while(true)
		//檢查前兩場比賽勝敗
		if(round == 2 && roundresult[0] == 1 && roundresult[1] == 1)
		{
			cout << "你在本次戰鬥獲得勝利!!!" << endl;
			break;
		}
		else if(round == 2 && roundresult[0] == 0 && roundresult[1] == 0)
		{
			cout << "你在本次戰鬥中落敗。" << endl;
			break;
		}
	}
	this->ending();
	if(round == 3 && roundresult[2] == 1)
	{
		cout << "你在本次戰鬥獲得勝利!!!" << endl;
	}
	else if(round == 3 && roundresult[2] == 0)
	{
		cout << "你在本次戰鬥中落敗。" << endl;
	}
	cout << "按任何鍵返回" << endl;
	string s;
	cin >> s;
	return;
}
