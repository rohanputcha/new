#ifndef CLASS_H
#define CLASS_H
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;
//Header begins here

class entity 
{
private:
	int attack;
	int magic;
	int health;
	bool energy[2];
	string name;
public:
	entity(int att, int heal, int mag, string name)
	{
		attack = att;
		magic = mag;
		health = heal;
		energy[0] = 0, energy[1] = 0;
		this->name = name;
	}
	entity(int att, int heal, string name)
	{
		attack = att;
		health = heal;
		energy[0] = 0, energy[1] = 0;
		this->name = name;
	}

public:
	int GetHealth();
	int GetAttack();
	int GetMagic();
	string GetName();
	void printbattle(entity);
	void printstats();
	void slash(entity*);
	void magicatt(entity*);
	int checkhealth();
	int checkcharging1();
	int checkcharging2();
	void charging();
	void charged();
	void chargereset();
	void battle(entity);
	void defeated(entity*);
};

int entity::GetHealth()
{
	return health;
}

int entity::GetAttack()
{
	return attack;
}

int entity::GetMagic()
{
	return magic;
}

string entity::GetName()
{
	return name;
}

void entity::printbattle(entity enemy)
{
	cout << "YOU: " << health << endl;
	cout << "ENEMY: " << enemy.GetHealth() << endl;
}
void entity::printstats()
{
	cout << "Attack: " << attack << endl;
	cout << "Magic: " << magic << endl;
	cout << "Health: " << health << endl;
}
void entity::slash(entity *enemy)
{
	(*enemy).health -= attack;
	if ((*enemy).health < 0)
		(*enemy).health = 0;
	cout << endl << name << " hit " << (*enemy).name << " for " << attack << " damage!\n";
}
void entity::magicatt(entity *enemy)
{
	(*enemy).health -= magic;
	if ((*enemy).health < 0)
		(*enemy).health = 0;
	cout << endl << name << " hit " << (*enemy).name << " for " << magic << " damage!\n";
}
int entity::checkhealth()
{
	if (health == 0)
		return 0;
	else
		return 1;
}
int entity::checkcharging1()
{
	if (energy[0] == 1)
		return 1;
	else
		return 0;
}
int entity::checkcharging2()
{
	if (energy[1] == 1)
		return 1;
	else
		return 0;
}
void entity::charging()
{
	cout << endl << name << " is charging!\n";
	energy[0] = 1;
}

void entity::charged()
{
	cout << endl << name << " finished charging!\n";
	energy[1] = 1;
}

void entity::chargereset()
{
	energy[0] = 0;
	energy[1] = 0;
}

void entity::battle(entity enemy)
{
	int choice;
	printbattle(enemy);
	while (enemy.checkhealth() == 1 && checkhealth() == 1)
	{
		if (checkcharging1() == 0)
		{
			cout << "\nYour Turn-\nWould you like to:\n1) Slash with your sword\n2) Attack with magic" << endl;
			cin >> choice;
			if (choice == 1)
			{
				slash(&enemy);
				printbattle(enemy);
				if (enemy.checkhealth() == 0)
				{
					defeated(&enemy);
					break;
				}
			}
			else if (choice == 2)
			{
				charging();
			}
			else
			{
				cout << "Try again!" << endl;
				continue;
			}
		}
		else if (checkcharging1() == 1 && checkcharging2() == 0)
		{
			charged();
		}
		else if (checkcharging1() == 1 && checkcharging2() == 1)
		{
			magicatt(&enemy);
			chargereset();
			printbattle(enemy);
			if (enemy.checkhealth() == 0)
			{
				defeated(&enemy);
				break;
			}
		}
		cout << endl;
		cout << enemy.GetName() << "'s turn-";
		enemy.slash(this);
		printbattle(enemy);
		if (checkhealth() == 0)
		{
			enemy.defeated(this);
			break;
		}
	}
}

void entity::defeated(entity *enemy)
{
	cout << endl << name << " defeated " << (*enemy).GetName() << "!\n";
}

//Header ends here
#endif
