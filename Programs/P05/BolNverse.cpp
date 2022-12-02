
/*****************************************************************************
*                    
*  Author:           Calvin Walmer
*  Email:            calvinw@calvinwalmer.com
*  Label:            P05
*  Title:            BolNverse
*  Course:           2143 - Object Oriented Programming
*  Semester:         Fall 2022
* 
*  Description:
*        This program is a game in which a large group of attackers outnumber your small group of defenders by 100 to 1. 
*        A mighty battle is waged between the attackers and defenders. The defenders are allowed in a room so they are allowed
*        to switch out freely at will and rest. The defenders however are in a hallway and can only attack one at a time. The 
*        program implements simple turn based combat. Under the hood there are examples of dyanmic polymorphism and a factory 
*		 design pattern utilization. The program reads enemies from an input fill and then lets the user pick thier party based 
*        off the number of enemies.
* 
*  Usage:
*        Compile and run BolNverse.cpp
* 
*  Files:           |   #   | File            | Description                                        									|
*					| :---: | --------------- | ----------------------------------------------------------------------------------- |
*					|   1   | BolNverse.cpp   | Main driver of my project that launches game.      									|
*					|   2   | helpers.hpp     | helper functions for input validation and tokenization								|
*					|   3   | fighter.hpp     | Contains FighterFactory factory and the parent class and children fighter classes 	|
*					|   4   | weapon.hpp      | Contains WeaponFactory factory and the parent class and children weapon classes 	|
*					|   5   | dice.hpp        | Contains die and dice classes for RNG 												|
*					|   6   | attackers.in    | Sample input file containing 1700 enemies											|
*					|   7   | attackers.txt   | Sample input file containing 1700 enemies											|
*					|   8   | attackers100.txt| Sample input file containing 100 enemies											|	
*****************************************************************************/
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include "fighter.hpp"

using namespace std;

/**
 * BolNverse
 * 
 * Description:
 *      Main contain for all the logic related to the game's turns and win conditions.
 * 
 * Public Methods:
 * 		BolNverse
 * 		void Start()
 * 
 * Private Methods:
 * 		void init()
 * 		bool FileFound(string filename)
 * 		void ChooseFriends()
 * 		void DisplayGUI()
 * 		BaseFighter* SelectFriend()
 * 		void Upkeep()		
 * 
 * Usage: 
 * 
 *		BolNverse game;
 * 		game.Start();
 *      
 */
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

    /**
     * Public: BolNverse()
     * 
     * Description:
     *      Constructor for BolNverse class
	 * 		Gets a filename and only calls init() if 
	 * 		the file is found.
     * 
     * Params:
	 * 		- none
     * 
     * Returns:
     *      - nothing
     */
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


    /**
     * Public : Start
     * 
     * Description:
     *      Runs the BolNverse game. Contains most of the logic for turns.
	 * 		Contains the main loop of the game.
     * 
     * Params:
	 * 		- none
     * 
     * Returns:
     *      - nothing
     */
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

			if (!swapped) //if player swapped characters last turn then attackers get a free turn
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
					character = SelectFriend(); //selection dialogue
					swapped = true; //flag
				}
			}
			else
			{
				swapped = false;
			}

			if(!opponent->isDead()) //if the opponent was not killed, it attacks the player
				character->Damage(opponent->attack());

			if(character->isDead() && friends.size() == 1) //logic for if all friends are dead
			{
				friends.clear();
				break;
			}
				
			if(opponent->isDead() && enemies.size() == 1) //logic for if all enemies are dead
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

    /**
     * Private: init
     * 
     * Description:
     *      Seeds the Die class statically once and iterates through the input file
	 * 		to get a list of enemies that are added to a vector. Also calculates the number of
	 * 		friends the player gets to choose.
     * 
     * Params:
	 * 		- none
     * 
     * Returns:
     *      - none
     */
	void init()
	{
		roundsFought = 0; //initializing counter

		Die::Seed(); //seeding Die ONCE, and not every time Die is instantiated

		string line;
		while (!infile.eof()) //looping through input file and adding to vector
		{
			infile >> line;
			enemies.push_back(FighterFactory::createFighter(line));
		}

		numEnemies = enemies.size();
		numFriends = numEnemies / 100; //1 to 100 ratio
	}


    /**
     * Private : FileFound
     * 
     * Description:
     *      Opens a file if it exists and passes back true if it does!
     * 
     * Params:
	 * 		- string filename		the name of the file to check.
     * 
     * Returns:
     *      - bool 					true if file was found. false if not
     */
	bool FileFound(string filename)
	{
		infile.open(filename);
		return infile.is_open();
	}


    /**
     * Private : ChooseFriends
     * 
     * Description:
     *      Function to only be called once at the beginning of the game.
	 * 		Lets the player pick their party and adds them to the friends vector.
     * 
     * Params:
	 * 		- none
     * 
     * Returns:
     *      - nothing
     */
	void ChooseFriends()
	{
		
		for (int i = 0; i < numFriends; i++)
		{
			cout << string(80, '\n') << endl;
			cout << "Choose a friend to help you fight!" << endl;
			cout << "You have " << numFriends - i << " friends left to choose" << endl << endl;
			cout << "1. Warrior\n2. Wizard\n3. Dragonborn\n4. Archer\n5. Elf" << endl;
			cout << "Select: ";
			friends.push_back(FighterFactory::createFighter(GetIntInput(1,5))); //creating fighter with input validation in helpers.hpp
		}
	}


    /**
     * Private : DisplayGUI
     * 
     * Description:
     *      Very simple function that prints out an enemy and a friend
	 * 		that are currently doing battle.
     * 
     * Params:
	 * 		- none
     * 
     * Returns:
     *      - nothing
     */
	void DisplayGUI()
	{
		cout << string(80, '\n') << endl;
		cout << string(80, '-') << endl;
		cout << *opponent << endl;

		cout << string(8, '\n');

		cout << *character << endl;

		
		
	}


	
    /**
     * Private : SelectFriend
     * 
     * Description:
     *      Prints a list of friends that are still alive and prompts the user to pick one.
	 * 		This function is to be called after a friend dies and needs to be replaced or the
	 * 		player entered the swap command.
     * 
     * Params:
	 * 		- none
     * 
     * Returns:
     *      - BaseFighter* 		A pointer to the new friend the player wants to use.
     */
	BaseFighter* SelectFriend()
	{
		int selection;
		int i;

		cout << string(30, '-') << "SELECT-FRIEND" << string(30, '-') << endl;

		for(i = 0; i < friends.size(); i++)
		{
			if (friends.at(i) == character) //if the item on the list is the active character
				cout << "***ACTIVE*** " << setw(10) << *friends.at(i) << endl;
			else
				cout << setw(4) << i + 1 << ". " << setw(10) << *friends.at(i) << endl;
		}

		cout << "CHOICE (1-" << i << "): "; //prompt
		return friends.at(GetIntInput(1, i) - 1);  //input validation in helpers.hpp
	}


    /**
     * Private : Upkeep
     * 
     * Description:
     *      Performs logical operations like removing a fighter from a list if they are dead.
	 * 		If a friend dies, it will prompt the user to replace them. Also performs regen operations
	 * 		for the friends list and on the active opponent.
     * 
     * Params:
	 * 		- none
     * 
     * Returns:
     *      - nothing
     */
	void Upkeep()
	{
		if (opponent->isDead()) //remove dead opponent and replace
		{
			opponent = nullptr;
			enemies.pop_back();
			opponent = enemies.back();
		}

		if(character->isDead())
		{
			int counter = 0;

			for(BaseFighter* f : friends) //find character since the player can choose any on the list
			{
				if (character == f)
				{
					break;
				}
				counter++;
			}
			friends.erase(friends.begin() + counter); //delete dead friend
			cout << string(80, '\n') << endl;
			cout << "YOUR CHARACTER WAS KILLED IN COMBAT..." << endl;
			character = SelectFriend(); //prompt for replacement
		}

		for(BaseFighter* f : friends) //regen all friends
		{
			f->Regen();
		}

		opponent->Regen(); //regen active enemy

		return;
	}
};


int main() {
	BolNverse game; //driver code :)
	game.Start();
}