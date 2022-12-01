#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "fighter.hpp"

using namespace  std;

class BolNverse
{
	ifstream infile;
	vector<BaseFighter*> enemies;
	vector<BaseFighter*> friends;
	int numFriends;
	int numEnemies;

	BaseFighter* opponent;
	BaseFighter* character;

public:
	BolNverse() 
	{
		if (FileFound()) init();
	};

	void Start()
	{
		//ChooseFriends();
		character = FighterFactory::createFighter(3);
		opponent = FighterFactory::createFighter(2);
		DisplayGUI();
	}
private:
	bool FileFound()
	{
		infile.open("attackers.txt");
		return infile.is_open();
	}
	void init()
	{
		string line;

		while (!infile.eof())
		{
			infile >> line;
			enemies.push_back(FighterFactory::createFighter(line));
		}

		numEnemies = enemies.size();
		numFriends = numEnemies / 100;
	}

	void ChooseFriends()
	{
		int choice;
		for (int i = 0; i < numFriends; i++)
		{
			cout << "Choose a friend to help you fight!" << endl;
			cout << "You have " << numFriends - i << " friends left to choose" << endl << endl;
			cout << "Options: 1. Warrior | 2. Wizard | 3. Dragonborn | 4. Archer | 5. Elf" << endl;
			cout << "Select: ";
			cin >> choice;
			friends.push_back(FighterFactory::createFighter(choice));
		}
	}

	void DisplayGUI()
	{
		cout << string(80, '-') << endl;
		cout << "An enemy " << opponent->GetFighterType() << " wielding a " << opponent->GetWeapon() << " approaches!!" << endl;
		cout << opponent->GetFighterType() << "'s HP: " << opponent->GetHP();

		cout << string(8, '\n');

		cout << *character << endl;

		
		
	}
};


int main() {
	BolNverse game;
	game.Start();


	//ifstream infile;

	//infile.open("attackers.txt");

	//string line;
	//while (!infile.eof()) {
	//	infile >> line;
	//	cout << line << endl;
	//}
}