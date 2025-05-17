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
        // ���� [min , max] ����ƶü� //
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
    if (n == 4)//�d�ݶ���
	{
	    if(this->PokemonNum == 0)
		{
			cout << "�A�S�������_�i��" << endl;
			cout << "�����N��^��D�e��" << endl;
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
	        	cout <<"��J�s����ܧA�n�d�ݧޯ઺�_�i�ڡG"<<endl;
	            int idNumber;
	            cin >> idNumber;
	        	if (cin.fail())
				{
	           	cin.clear();
		        cin.ignore();
		        cout<<"�A�S�����_�i�ڡA�Э��s���"<<endl;
				}
				else
				{
					for(int i = 0 ; i < PokemonNum ; i++)
					{
                    	if(MyPokemon[i].getID() == idNumber)
						{
                        	MyPokemon[i].printSkill();
                        	rightpokemon = 1;
                        	cout << "�����N��^��D�e��" << endl;
				            string a;
							cin >> a;
							return;
                    	}
            		}
            	if (rightpokemon == 0)
				{
                	cout<<"�A�S�����_�i�ڡA�Э��s���"<<endl;
            	}
				}
			}
        }
    }
    if (n==5)//���}�I�]
	{
        this->itemList.printItemList();//��X�I�]�����~
		cout << "�п�ܧA�n�ϥΪ��D��G" << endl << "1:�g��G" << endl
		<< "2:���y��" << endl << "��L�G�^��D�e��" << endl;
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
	            cout << "�п�J�s����ܧA�n�ɯŪ��_�i�ڡG" << endl;
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
		                cout<<"�A�S�����_�i�ڡA�Э��s��J�Ϋ�N�^��D�e��" << endl;
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
			    cout << "�����N��^��D�e��" << endl;
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
	
	cout << "��⪺�X���_�i�ڦ�" << endl;
	for(int i = 0; i < 3; i++)
		enemyPickedPokemon[i].print();
	cout << " " << endl;
	
	cout << "��ܤT���_�i�ڥX��" << endl;
	for(int i = 0; i < playerPokemon.size(); i++)
	{
		playerPokemon[i].print();
	}
	cout << "��J�T�ӽs��" << endl;
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
    	    cout << "��J���~�A�Э��s���" << endl;
		    i--;
		    continue;
    	}
		for(int j = 0; j < i; j++)
		{
			if(ID[i] == ID[j])
			{
				repeat = true;
				cout << "���i���ƿ���_�i��" << endl;
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
			cout << "�A�èS���s����" << ID[i] << "���_�i�ڡA�Э��s���" << endl;
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
	cout << "�԰��}�l!" << endl;
	for(int i = 0; i < 3; i++)
	{
		double skillBoostRate = 1;
		round++;
		cout << endl;
 		cout << "��" << round << "��" << endl;
		cout << "�A���X�F" << pickedPokemon[i]->getName() << endl;
		cout << "��謣�X�F" << enemyPickedPokemon[i].getName() << endl;
		while(true)
		{
			string order;
			cout << endl;
			cout << "�п�J���O�A�d��/�ϥΧޯ�Ы�z�B�ϥιD��Ы�x�C" << endl;
			try{
				cin >> order;
				if(order == "z")
				{
					bool back = false;
					int skillIDtoUse = 0;
					pickedPokemon[i]->printSkill();
					cout << "�п�J�ޯ�s���H�ϥΧޯ�A�Y�n��^�e�@���Ы�0" << endl;
					while(true)		//�ˬd��J
					{
						try
						{
							cin >> skillIDtoUse;
							if (cin.fail()) {
		           				throw ios_base::failure("�п�J�ޯ�s��");
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
						cout << "�A���ѤF���A���ߧAĹ�o��" << round << "��" << endl;
						roundresult[i] = 1;
						cout << pickedPokemon[i]->getName() << "��o�F" << enemyPickedPokemon[i].defeatedExp << "�I�g���" << endl;
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
			    	cout << "�п�ܨϥΪ��D��A��1�ϥ��Ĥ��B��2�ϥξ԰����B�šA�Y�n��^�e�@���Ы�0" << endl;
			    	while(true)		//�ˬd��J
					{
						try
						{
							cin >> itemInput;
							if (cin.fail()) {
		           				throw ios_base::failure("�п�J0/1/2");
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
									cout << "�A�ϥξ԰����B�żW�[�F" << skillBoostRate << "���ޯ�ĪG�I" << endl;
									Sleep(1500);
									break;
								}
								else
									throw ios_base::failure("�п�J0/1/2");
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
					throw logic_error("�L�����O");
			}
			catch(logic_error e2)
			{
				cout << e2.what() << endl;
				cin.clear();
				cin.ignore();
				continue;
			}

			//����enemy�ʧ@
			cout << endl;
			cout << "������ʧ@..." << endl;
			Sleep(1000);
			enemyPickedPokemon[i].useSkillRandom(*pickedPokemon[i]);
			if(pickedPokemon[i]->HP <= 0)
			{
				cout << endl;
				cout << "�A�ѵ��F���A�ܥi����F��" << round << "��" << endl;
				roundresult[i] = 0;
				Sleep(1500);
				break;
			}

		}//while(true)
		//�ˬd�e������ɳӱ�
		if(round == 2 && roundresult[0] == 1 && roundresult[1] == 1)
		{
			cout << "�A�b�����԰���o�ӧQ!!!" << endl;
			break;
		}
		else if(round == 2 && roundresult[0] == 0 && roundresult[1] == 0)
		{
			cout << "�A�b�����԰������ѡC" << endl;
			break;
		}
	}
	this->ending();
	if(round == 3 && roundresult[2] == 1)
	{
		cout << "�A�b�����԰���o�ӧQ!!!" << endl;
	}
	else if(round == 3 && roundresult[2] == 0)
	{
		cout << "�A�b�����԰������ѡC" << endl;
	}
	cout << "���������^" << endl;
	string s;
	cin >> s;
	return;
}
