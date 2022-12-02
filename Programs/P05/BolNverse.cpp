#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
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
	int roundsFought;

	BaseFighter* opponent;
	BaseFighter* character;

public:
	BolNverse() 
	{
		string filename;
		cout << "Enter attacker input filename: ";
		cin >> filename;

		if (FileFound(filename)) 
			init(); 
		else 
		{
			cout << "File not found!";
			exit;
		}
	};

	void Start()
	{
		int selection = 0;
		bool swapped = false;
		//Allowing user to choose their party
		ChooseFriends();
		//Setting up first opponent
		opponent = enemies.back();
		//After user picks their party, allow them to select a fighter to send up.
		cout << string(80, '\n') << endl;
		character = SelectFriend();

		//GAME BEGINS HERE
		while(!(friends.empty() || enemies.empty())) //while either list is not empty
		{
			Upkeep();
			DisplayGUI();

			if (!swapped)
			{
				cout << "ACTIONS: 1. Attack | 2. Swap |" << endl;
				cout << "SELECT ACTION: ";
				if (GetIntInput(1,2) == 1)
				{
					opponent->Damage(character->attack());
					swapped = false;
				}
				else
				{
					cout << string(80, '\n') << endl;
					character = SelectFriend();
					swapped = true;
				}
			}
			else
			{
				swapped = false;
			}

			if(!opponent->isDead())
				character->Damage(opponent->attack());

			if(character->isDead() && friends.size() == 1)
			{
				friends.clear();
				break;
			}
				
			if(opponent->isDead() && enemies.size() == 1)
			{
				enemies.clear();
				break;
			}

			roundsFought++;
		}

		cout << string(80, '\n') << endl;
		cout << "GAME STATISTICS" << endl;
		cout << "ATTACKERS DEFEATED: " << numEnemies - enemies.size() << "/" << numEnemies << endl;
		cout << "TOTAL DEFENDERS: " << numFriends << endl;
		cout << "ROUNDS FOUGHT: " << roundsFought << endl;
		cout << (friends.empty() ? "ATTACKERS WON! :(" : "DEFENDERS WON! :D") << endl;
		cout << "THANKS FOR PLAYING!" << endl;

	}
private:
	bool FileFound(string filename)
	{
		infile.open(filename);
		return infile.is_open();
	}
	void init()
	{
		string line;
		roundsFought = 0;

		Die::Seed(); //seeding Die ONCE, and not every time Die is instantiated

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
		
		for (int i = 0; i < numFriends; i++)
		{
			cout << string(80, '\n') << endl;
			cout << "Choose a friend to help you fight!" << endl;
			cout << "You have " << numFriends - i << " friends left to choose" << endl << endl;
			cout << "1. Warrior\n2. Wizard\n3. Dragonborn\n4. Archer\n5. Elf" << endl;
			cout << "Select: ";
			friends.push_back(FighterFactory::createFighter(GetIntInput(1,5)));
		}
	}

	void DisplayGUI()
	{
		cout << string(80, '\n') << endl;
		cout << string(80, '-') << endl;
		cout << *opponent << endl;

		cout << string(8, '\n');

		cout << *character << endl;

		
		
	}

	BaseFighter* SelectFriend()
	{
		int selection;
		int i;

		cout << string(30, '-') << "SELECT-FRIEND" << string(30, '-') << endl;
		for(i = 0; i < friends.size(); i++)
		{
			if (friends.at(i) == character)
			cout << "***ACTIVE*** " << setw(10) << *friends.at(i) << endl;
			else
			cout << setw(4) << i + 1 << ". " << setw(10) << *friends.at(i) << endl;
		}
		cout << "CHOICE (1-" << i << "): ";

		return friends.at(GetIntInput(1, i) - 1);
	}

	void Upkeep()
	{
		if (opponent->isDead())
		{
			opponent = nullptr;
			enemies.pop_back();
			opponent = enemies.back();
		}

		if(character->isDead())
		{
			int counter = 0;
			for(BaseFighter* f : friends)
			{
				if (character == f)
				{
					break;
				}
				counter++;
			}
			friends.erase(friends.begin() + counter);
			cout << string(80, '\n') << endl;
			cout << "YOUR CHARACTER WAS KILLED IN COMBAT..." << endl;
			character = SelectFriend();
		}

		for(BaseFighter* f : friends)
		{
			f->Regen();
		}

		opponent->Regen();
		return;
	}

};


int main() {
	BolNverse game;
	game.Start();
}