#include <iostream>
#include <cstdlib>  // create random number
#include <ctime>    // create seed
#include <cmath> // log
#include <fstream> // input file
#include <sstream> // input file
#include"itemHeader.h"
#include "Pokemon_battle_index.h"
#include <windows.h>
#include <random>

using namespace std;

Item::Item(const std :: string& n, const std :: string& ch): name (n), chName(ch), num(0), type(""){}

void Item::print() const
{
	std::cout << type << "：" << std::endl << description << std::endl;
}

//====================================================


PokeBall::PokeBall (const std :: string& n, const std :: string& ch): Item(n, ch)
{
	type = "精靈球";
	this->description = "精靈球用來捕捉寶可夢，有一般球、高級球、超級球三種，分別能為捕捉機率帶來不同的加成，一次捕捉僅能使用一顆。";
	if (n == "Normal Ball")
		catchChance = 0.4;// enhance the capture rate of a pokemon
	else if (n == "Great Ball")
		catchChance = 0.6;
	else if (n == "Master Ball")
		catchChance = 0.75;
}

bool PokeBall:: catchPokemon(WildPokemon w, double charmRate)
{
	double catchprob = charmRate + catchChance + w.getCatchProb(); //need function "getCatchProb()"

	auto seed = static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
   	std::mt19937 rng(seed);
	std::uniform_int_distribution<int> unif(0, 1000);
		
	double catched = unif(rng) / (RAND_MAX + 1.0); // create random number between [0,1]
	if (catched <= catchprob)
		return true;
	else
		return false;
}

void PokeBall:: printBallInfo() const
{
	Item::print();//print description
	cout <<"一般球：取得難度最低，捕捉機率加成最低。" << endl;
	cout <<"高級球：取得難度中等，捕捉機率加成中等。" << endl;
	cout <<"超級球：取得難度最高，捕捉機率加成最高。" << endl;
}
//====================================================

//Heal player or pokemon which get injured in battle by increasing hp


HealingPotion::HealingPotion(const std::string& n, const std :: string& ch): Item(n, ch)
{
	type = "治療藥水";
	description = "治療藥水可用來治療在戰鬥中受傷的寶可夢，可在戰鬥中使用，有一般藥水、高級藥水、超級藥水三種，一次可使用多個。";
	if(n == "Normal Potion")
		healAmount = 10;
	else if (n == "Great Potion")
		healAmount = 20;
	else if (n == "Master Potion")
		healAmount = 30;
}
//healing amount can be changed(not cercain about the amount of hp)

void HealingPotion::healing(Pokemon& p, int useCnt)
{
	p.HP += this->healAmount * useCnt;
	cout << "回復了" << this->healAmount * useCnt << "點血量" << endl;
	Sleep(1500);
}

void HealingPotion::printPotionInfo() const
{
	Item::print(); // print description
	cout <<"一般藥水：取得難度最低，血量回復最低。" << endl;
	cout <<"高級藥水：取得難度中等，血量回復中等。" << endl;
	cout <<"超級藥水：取得難度最高，血量回復最高。" << endl;
}

//====================================================

//expApple is used to increase ex for pokemon


ExpApple::ExpApple(const std :: string&n, const std :: string& ch): Item(n, ch)
{
	type = "經驗果";
	this->description = "經驗果用來提升寶可夢的經驗值，分為一般和高級兩種，實際提升值依等級不同而有所不同，可在道具欄使用，一次可使用多個";
	if (n == "Great Apple")
		this->expBoost = 30;
	else if (n == "Normal Apple")
		this->expBoost = 20;
}
//experienceboost can be altered considering the total amount of exp
// real gain is std::log(playerLevel + 1)* expBoost

//training pokemon
void ExpApple::training(Pokemon& p, vector<Skill> Database)
{
	p.exp += std::log(p.LV + 1)* this->expBoost;
	cout << "增加了" << p.exp << "點經驗" << endl;
 	while(p.exp >= p.nextlevelExp){
		p.levelUP(Database);
	}
	return;
}

void ExpApple::printExpAppleInfo() const
{
	Item::print();
	cout <<"一般經驗果：取得難度較低，提升經驗較少。" << endl;
	cout <<"高級經驗果：取得難度較高，提升經驗較多。" << endl;
}

//====================================================

//LuckyCham is used to increase the probability of capture
//or increase skill damage or heal or get a random item


LuckyCharm::LuckyCharm(const std :: string&n, const std :: string& ch): Item(n, ch)
{
	type = "幸運符";
	description = "幸運符分為捕捉幸運符、戰鬥幸運符、獎勵符三種，各自有不同用途及使用時間，一次僅能使用一個。";
	if(n == "Capture Charm")
	{
		srand( time(NULL) );// set seed
		captureBoost = (0.3 - 0.05) * (double)rand() / (RAND_MAX + 1.0) + 0.05;
		skillBoost = 0;
		rewardItem = false;
	}
	else if (n == "Battle Charm")
	{
		srand( time(NULL) );// set seed
		captureBoost = 0;
		skillBoost = (0.3 - 0.05) * (double)rand() / (RAND_MAX + 1.0) + 1.05;
		rewardItem = false;
	}
	else if (n == "Reward Charm")
	{
		captureBoost = 0;
		skillBoost = 0;
		rewardItem = true;
	}
}
//captureBoost and SkilBoost is in [0.05, 0.3] , can be altered

// use reward charm to get a random item except reward charm
int LuckyCharm::getRewardItem()
{
	srand(time(NULL));
    const int probabilities[] = {20, 10, 5, 15, 10, 5, 10, 5, 10, 10};
    int randomValue = rand() % 100;
    int cumulativeWeight = 0;
    for (int i = 0; i < 10; ++i)
	{
        cumulativeWeight += probabilities[i];
        if (randomValue < cumulativeWeight)
		{
            return i;
        }
    }
    return 0;  // 預防意外，理論上不會執行到這裡
}

void LuckyCharm::printCharmInfo() const
{
	Item::print();
	cout << "捕捉幸運符：在捕捉野生寶可夢、使用精靈球前使用，可以提升捕捉機率。" <<endl;
	cout << "戰鬥幸運符：在戰鬥中使用，可以提升一個技能的傷害和回復" << endl;
	cout << "獎勵符：在道具欄使用，可以隨機獲得一個其他道具。" << endl;
}

//====================================================



ItemList::ItemList()
{
	for (int i = 0; i < 11; ++i)
	{
        items[i] = new Item("","");
	}
	itemCnt = 0;
	createItemDic("dic.txt");

}

void ItemList::createItemDic(const std::string& filename)
{
    ifstream file(filename);
    if (!file.is_open())
	{
        std::cerr << "無法打開檔案: " << filename << std::endl;
        return;
    }
   	string line;
    int index = 0;

    while (getline(file, line) && index < 11)
	{
        istringstream iss(line);
        string itemName, chName;
        
        if (std::getline(iss, itemName, ',') && std::getline(iss, chName))
		{
            // 創建新的 Item
            Item* newItem = nullptr;
            if(index < 3)
            {
           	newItem = new PokeBall(itemName, chName);
			}
			if(index >=3 and index < 6)
			{
			newItem = new HealingPotion(itemName, chName);
			}
			if(index >= 6 and index < 8)
			{
			newItem = new ExpApple(itemName, chName);
			}
			if(index >= 8)
			{
			newItem = new LuckyCharm(itemName, chName);
			}

            // 將 Item 加入 itemDic
            items[index] = newItem;

            index++;
        }
		else
		{
            std::cerr << "無效的行: " << line << std::endl;
        }
    }
    file.close();
}

//ItemList::~ItemList()
//{
//    for (int i = 0; i < 11; ++i)
//	{
//        delete items[i];
//    }
//}

Item* ItemList::getItem(int index)
{
    if (index >= 0 && index < 11)
	{
        return items[index];
    }
	else
	{
        // 處理錯誤情況
        return nullptr;
    }
}

//get a random item
int ItemList::getRandomItem()
{
	auto seed = static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	std::mt19937 rng(seed);
    std::uniform_int_distribution<int> unif(0, 1000);

    const int probYesRe[] = {19, 9, 4, 14, 9, 4, 9, 4, 9, 9, 10};
    int randomValue = unif(rng) % 100;
    int cumulativeWeight = 0;
    for (int i = 0; i < 11; ++i)
	{
        cumulativeWeight += probYesRe[i];
        if (randomValue < cumulativeWeight)
		{
            return i;
        }
    }
    return 0;  // 預防意外，理論上不會執行到這裡
}

void ItemList::addItem(int id)
{
	if(id >= 0 and id <= 10)
	{
		cout << "你獲得了1個" << this->items[id]->chName << endl;
		this->items[id]->num ++;
		this->itemCnt ++;
		cout << "目前擁有" << this->items[id]->num << "個" <<this->items[id]->chName << endl;
	}
	
}

bool ItemList::usePokeBall(WildPokemon w)
{
	double charmRate = this->useCapCharm();
	if(this->items[0]->num == 0 and this->items[1]->num == 0 and this->items[2]->num == 0 )
	{
		cout << "你沒有任何精靈球，無法捕捉" << endl;
		return false;
	}
	string action;
	int act = 0;
	string name;
	cout <<"選擇你要使用的精靈球:"<< endl;
    cout <<"1：一般球 (剩餘數量："<< this->items[0]->num << ")" << endl;
	cout <<"2：高級球 (剩餘數量："<< this->items[1]->num << ")" << endl;
	cout <<"3：超級球 (剩餘數量："<< this->items[2]->num << ")" << endl;
    while(cin >> action)
    {	try
			{
        		act = std::stoi(action);
    		}
		catch (exception e) {}
    	if(act <= 3 and act >= 1)
		{
			
			if(this->items[act - 1]->num > 0)
			{
				name = this->items[act - 1]->name;
				this->items[act - 1]->num --;
				break;
			}
			else
			{
				cout << "你沒有任何" << this->items[act - 1]->chName << "，請重新選擇。" << endl;
			}
		}
		else
		{
			cout << "請輸入1或2或3。" << endl;
		}
	}
	PokeBall ball(this->items[act - 1]->name, this->items[act - 1]->chName);
	itemCnt --;
	if(ball.catchPokemon(w, charmRate))
	{
		cout << "恭喜你抓到" << w.getName() << endl;
	}
	else
		cout << "捕捉失敗" << endl;
	return ball.catchPokemon(w, charmRate);
}

void ItemList::usePotion(Pokemon& p)
{
	if(this->items[3]->num == 0 and this->items[4]->num == 0 and this->items[5]->num == 0)
		{
			cout << "你沒有任何治療藥水，無法使用。";
			return;
  		}
	string action;
	int act = 0;
	cout <<"選擇你要使用的治療藥水:"<< endl;
    cout <<"1：一般藥水 (剩餘數量："<< this->items[3]->num << ")" << endl;
	cout <<"2：高級藥水 (剩餘數量："<< this->items[4]->num << ")" << endl;
	cout <<"3：超級藥水 (剩餘數量："<< this->items[5]->num << ")" << endl;
	while (cin >> action)
	{
		try
			{
        		act = std::stoi(action);
    		}
		catch (exception e) {}
    	if(act <= 3 and act >= 1)
		{
			if(this->items[act + 2]->num > 0)
			{
				break;
			}
			else
			{
				cout << "你沒有任何" << this->items[act + 2]->chName << "，請重新選擇。" << endl;
			}
		}
		else
		{
			cout << "請輸入1或2或3。" << endl;
		}
	}
	
	HealingPotion heal(this->items[act + 2]->name,this->items[act + 2]->chName);
	int useCnt = 0;
	cout << "請輸入要使用的數量："<< endl;
	while(cin >> useCnt)
	{
		if((act == 1 and this->items[3]->num < useCnt) or
		(act == 2 and this->items[4]->num < useCnt) or(act == 3 and this->items[5]->num < useCnt))
		{
			cout << "輸入數量大於可用數量，請重新輸入。" << endl;
		}
		else
			break;
	}
	
	this->items[act + 2]->num -= useCnt;
	itemCnt -= useCnt;
	heal.healing(p, useCnt);
}

bool ItemList::useExpApple(Pokemon& p,vector<Skill> Database)
{
	if (this->items[6]->num == 0 and this->items[7]->num == 0)
	{
		cout <<"你沒有任何經驗果，無法使用。" << endl;
		return false;
	}
	
	cout << "請選擇一般經驗果或高級經驗果" << endl;
	cout << "1：一般經驗果" << endl << "2：高級經驗果" <<endl;
  	string action;
  	int act = 0;
		while(cin >> action)
		{
			try
			{
        		act = std::stoi(action);
    		}
			catch (exception e) {}
			if (act == 1 or act == 2)
			{
				if(this->items[act + 5]->num == 0)
					cout << "你沒有任何"<< this->items[act + 5]->chName << "，無法使用，請重新輸入。" << endl;
				else
				{
					ExpApple nor(this->items[act + 5]->name, this->items[act + 5]->chName);
					this->items[act + 5]->num --;
					nor.training(p,Database);
					return false;
				}
			}
			else
				cout << "請輸入1或2" << endl;
		}
}
int ItemList::useCharm()
{
	if(this->items[10]->num == 0)
	{
		cout << "你沒有任何獎勵符，無法使用。" << endl;
		return -1;
	}
	else
	{
		LuckyCharm reward(this->items[10]->name, this->items[10]->chName);
		this->items[10]->num --;
		return reward.getRewardItem();
	}
}

double ItemList::useCapCharm()//capture charm
{
	if(this->items[8]->num == 0)
	{
		cout << "你沒有任何捕捉幸運符，無法使用。" << endl;
		return 0;
	}
	else
	{
		cout << "你是否要使用幸運符？(Y/N)" << endl;
		string a;
		cin >> a;
		if(a == "Y" or a == "y")
		{LuckyCharm cap(this->items[8]->name,this->items[8]->chName);
			this->items[8]->num --;
			cout << "你使用了幸運符，增加了" << cap.getCapRate() << "的捕捉機率" << endl;
			return cap.getCapRate();
		}
	}
}

double ItemList::useBatCharm()//battle charm
{
	if(this->items[9]->num == 0)
 	{
		cout << "你沒有任何戰鬥幸運符，無法使用。" << endl;
		return 0;
	}
	else
	{
		LuckyCharm bat(this->items[9]->name,this->items[9]->chName);
		this->items[9]->num --;
		return bat.getSkillRate();
	}
}

void ItemList::printItemList()
{
	cout << "目前背包內物品：" << endl;
	for(int i = 0; i < 11; i++)
	{
		if (i == 0 or i == 3 or i == 6 or i == 8)
		{
			cout << endl;
			cout << this->items[i]->type << "：" << endl;

		}
		cout << this->items[i]->chName <<"：" << this->items[i]->num << endl;
	}
	cout << endl;
}
