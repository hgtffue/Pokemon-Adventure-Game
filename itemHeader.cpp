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
	std::cout << type << "�G" << std::endl << description << std::endl;
}

//====================================================


PokeBall::PokeBall (const std :: string& n, const std :: string& ch): Item(n, ch)
{
	type = "���F�y";
	this->description = "���F�y�ΨӮ����_�i�ڡA���@��y�B���Ųy�B�W�Ųy�T�ءA���O�ର�������v�a�Ӥ��P���[���A�@�������ȯ�ϥΤ@���C";
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
	cout <<"�@��y�G���o���׳̧C�A�������v�[���̧C�C" << endl;
	cout <<"���Ųy�G���o���פ����A�������v�[�������C" << endl;
	cout <<"�W�Ųy�G���o���׳̰��A�������v�[���̰��C" << endl;
}
//====================================================

//Heal player or pokemon which get injured in battle by increasing hp


HealingPotion::HealingPotion(const std::string& n, const std :: string& ch): Item(n, ch)
{
	type = "�v���Ĥ�";
	description = "�v���Ĥ��i�ΨӪv���b�԰������˪��_�i�ڡA�i�b�԰����ϥΡA���@���Ĥ��B�����Ĥ��B�W���Ĥ��T�ءA�@���i�ϥΦh�ӡC";
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
	cout << "�^�_�F" << this->healAmount * useCnt << "�I��q" << endl;
	Sleep(1500);
}

void HealingPotion::printPotionInfo() const
{
	Item::print(); // print description
	cout <<"�@���Ĥ��G���o���׳̧C�A��q�^�_�̧C�C" << endl;
	cout <<"�����Ĥ��G���o���פ����A��q�^�_�����C" << endl;
	cout <<"�W���Ĥ��G���o���׳̰��A��q�^�_�̰��C" << endl;
}

//====================================================

//expApple is used to increase ex for pokemon


ExpApple::ExpApple(const std :: string&n, const std :: string& ch): Item(n, ch)
{
	type = "�g��G";
	this->description = "�g��G�ΨӴ����_�i�ڪ��g��ȡA�����@��M���Ũ�ءA��ڴ��ɭȨ̵��Ť��P�Ӧ��Ҥ��P�A�i�b�D����ϥΡA�@���i�ϥΦh��";
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
	cout << "�W�[�F" << p.exp << "�I�g��" << endl;
 	while(p.exp >= p.nextlevelExp){
		p.levelUP(Database);
	}
	return;
}

void ExpApple::printExpAppleInfo() const
{
	Item::print();
	cout <<"�@��g��G�G���o���׸��C�A���ɸg����֡C" << endl;
	cout <<"���Ÿg��G�G���o���׸����A���ɸg����h�C" << endl;
}

//====================================================

//LuckyCham is used to increase the probability of capture
//or increase skill damage or heal or get a random item


LuckyCharm::LuckyCharm(const std :: string&n, const std :: string& ch): Item(n, ch)
{
	type = "���B��";
	description = "���B�Ť����������B�šB�԰����B�šB���y�ŤT�ءA�U�ۦ����P�γ~�Ψϥήɶ��A�@���ȯ�ϥΤ@�ӡC";
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
    return 0;  // �w���N�~�A�z�פW���|�����o��
}

void LuckyCharm::printCharmInfo() const
{
	Item::print();
	cout << "�������B�šG�b���������_�i�ڡB�ϥκ��F�y�e�ϥΡA�i�H���ɮ������v�C" <<endl;
	cout << "�԰����B�šG�b�԰����ϥΡA�i�H���ɤ@�ӧޯ઺�ˮ`�M�^�_" << endl;
	cout << "���y�šG�b�D����ϥΡA�i�H�H����o�@�Ө�L�D��C" << endl;
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
        std::cerr << "�L�k���}�ɮ�: " << filename << std::endl;
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
            // �Ыطs�� Item
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

            // �N Item �[�J itemDic
            items[index] = newItem;

            index++;
        }
		else
		{
            std::cerr << "�L�Ī���: " << line << std::endl;
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
        // �B�z���~���p
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
    return 0;  // �w���N�~�A�z�פW���|�����o��
}

void ItemList::addItem(int id)
{
	if(id >= 0 and id <= 10)
	{
		cout << "�A��o�F1��" << this->items[id]->chName << endl;
		this->items[id]->num ++;
		this->itemCnt ++;
		cout << "�ثe�֦�" << this->items[id]->num << "��" <<this->items[id]->chName << endl;
	}
	
}

bool ItemList::usePokeBall(WildPokemon w)
{
	double charmRate = this->useCapCharm();
	if(this->items[0]->num == 0 and this->items[1]->num == 0 and this->items[2]->num == 0 )
	{
		cout << "�A�S��������F�y�A�L�k����" << endl;
		return false;
	}
	string action;
	int act = 0;
	string name;
	cout <<"��ܧA�n�ϥΪ����F�y:"<< endl;
    cout <<"1�G�@��y (�Ѿl�ƶq�G"<< this->items[0]->num << ")" << endl;
	cout <<"2�G���Ųy (�Ѿl�ƶq�G"<< this->items[1]->num << ")" << endl;
	cout <<"3�G�W�Ųy (�Ѿl�ƶq�G"<< this->items[2]->num << ")" << endl;
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
				cout << "�A�S������" << this->items[act - 1]->chName << "�A�Э��s��ܡC" << endl;
			}
		}
		else
		{
			cout << "�п�J1��2��3�C" << endl;
		}
	}
	PokeBall ball(this->items[act - 1]->name, this->items[act - 1]->chName);
	itemCnt --;
	if(ball.catchPokemon(w, charmRate))
	{
		cout << "���ߧA���" << w.getName() << endl;
	}
	else
		cout << "��������" << endl;
	return ball.catchPokemon(w, charmRate);
}

void ItemList::usePotion(Pokemon& p)
{
	if(this->items[3]->num == 0 and this->items[4]->num == 0 and this->items[5]->num == 0)
		{
			cout << "�A�S������v���Ĥ��A�L�k�ϥΡC";
			return;
  		}
	string action;
	int act = 0;
	cout <<"��ܧA�n�ϥΪ��v���Ĥ�:"<< endl;
    cout <<"1�G�@���Ĥ� (�Ѿl�ƶq�G"<< this->items[3]->num << ")" << endl;
	cout <<"2�G�����Ĥ� (�Ѿl�ƶq�G"<< this->items[4]->num << ")" << endl;
	cout <<"3�G�W���Ĥ� (�Ѿl�ƶq�G"<< this->items[5]->num << ")" << endl;
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
				cout << "�A�S������" << this->items[act + 2]->chName << "�A�Э��s��ܡC" << endl;
			}
		}
		else
		{
			cout << "�п�J1��2��3�C" << endl;
		}
	}
	
	HealingPotion heal(this->items[act + 2]->name,this->items[act + 2]->chName);
	int useCnt = 0;
	cout << "�п�J�n�ϥΪ��ƶq�G"<< endl;
	while(cin >> useCnt)
	{
		if((act == 1 and this->items[3]->num < useCnt) or
		(act == 2 and this->items[4]->num < useCnt) or(act == 3 and this->items[5]->num < useCnt))
		{
			cout << "��J�ƶq�j��i�μƶq�A�Э��s��J�C" << endl;
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
		cout <<"�A�S������g��G�A�L�k�ϥΡC" << endl;
		return false;
	}
	
	cout << "�п�ܤ@��g��G�ΰ��Ÿg��G" << endl;
	cout << "1�G�@��g��G" << endl << "2�G���Ÿg��G" <<endl;
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
					cout << "�A�S������"<< this->items[act + 5]->chName << "�A�L�k�ϥΡA�Э��s��J�C" << endl;
				else
				{
					ExpApple nor(this->items[act + 5]->name, this->items[act + 5]->chName);
					this->items[act + 5]->num --;
					nor.training(p,Database);
					return false;
				}
			}
			else
				cout << "�п�J1��2" << endl;
		}
}
int ItemList::useCharm()
{
	if(this->items[10]->num == 0)
	{
		cout << "�A�S��������y�šA�L�k�ϥΡC" << endl;
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
		cout << "�A�S�����󮷮����B�šA�L�k�ϥΡC" << endl;
		return 0;
	}
	else
	{
		cout << "�A�O�_�n�ϥΩ��B�šH(Y/N)" << endl;
		string a;
		cin >> a;
		if(a == "Y" or a == "y")
		{LuckyCharm cap(this->items[8]->name,this->items[8]->chName);
			this->items[8]->num --;
			cout << "�A�ϥΤF���B�šA�W�[�F" << cap.getCapRate() << "���������v" << endl;
			return cap.getCapRate();
		}
	}
}

double ItemList::useBatCharm()//battle charm
{
	if(this->items[9]->num == 0)
 	{
		cout << "�A�S������԰����B�šA�L�k�ϥΡC" << endl;
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
	cout << "�ثe�I�]�����~�G" << endl;
	for(int i = 0; i < 11; i++)
	{
		if (i == 0 or i == 3 or i == 6 or i == 8)
		{
			cout << endl;
			cout << this->items[i]->type << "�G" << endl;

		}
		cout << this->items[i]->chName <<"�G" << this->items[i]->num << endl;
	}
	cout << endl;
}
