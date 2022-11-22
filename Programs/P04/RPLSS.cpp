/*****************************************************************************
*                    
*  Author:           Calvin Walmer
*  Email:            calvinw@calvinwalmer.com
*  Label:            P04
*  Title:            Rock Paper Scissors Lizard Spock
*  Course:           CMPS 2134
*  Semester:         Fall 2022
* 
*  Description:
*   This program implements a class that plays games of Rock Paper Scissors Lizard Spock (RPSLS) 
*   indefinitely. The class contains two players that are instantiated each game and generate weapons upon
*   creation. Then, the class pits them against each other and uses a lookup table to determine a winner.
*        
*  Usage: 
*   Run the main function and continue to spectate for as long as desired!
*       
*  Files:            
*  RPSLS.cpp        main driver code and class declarations
*****************************************************************************/
#include <chrono>
#include <iostream>
#include <map>
#include <random>
using namespace std;


//Defining Emoji shortcuts
#define ROCK u8"\U0000270A"
#define PAPER u8"\U0000270B"
#define SCISSORS u8"\U0001F44C"
#define LIZARD u8"\U0001F918"
#define SPOCK u8"\U0001F596"

#define ROCK2 u8"\U0001F5FB"
#define PAPER2 u8"\U0001F4C3"
#define SCISSORS2 u8"\U0001F52A"
#define LIZARD2 u8"\U0001F438"
#define SPOCK2 u8"\U0001F596"

const string rock = ROCK2;
const string paper = PAPER2;
const string scissors = SCISSORS2;
const string lizard = LIZARD2;
const string spock = SPOCK2;


/**
 * Player
 * 
 * Description:
 *      Player structure that contains the weapons and several untility functions related to
 *      emoji conversion.
 * 
 * Public Methods:
 *      - Player        constructor
 *      - emoji         string      returns the emoji code of the integer emoji equivalent
 *      - seeded_engine mt19937     returns an engine for RNG
 *      - TieBreaker    bool        returns a win status after generating new weapons until there is a winner
 *      - Battle        bool        returns a win status after looking up each players weapons on the table
 * 
 * 
 * Usage: 
 * 
 * Player p1, p2
 *   cout << p1.weapon1;  "4"
 *   cout << p1.emoji(1); ":spock: or u8"\U0001F596""
 *   cout << p1.Battle(p2, 1); "true"
 *      
 */
struct Player {
    mt19937 eng;
    int weapon1;
    int weapon2;
    
    // Does row beat column?
    int lookup[5][5] = {  //R    P   S  L    S       -1 = No, 0 = Tie, 1 = Yes
                            0,  -1, 1,  1,  -1, // R
                            1,  0,  -1, -1, 1,  // P
                            -1, 1,  0,  1,  -1, // S
                            -1, 1,  -1, 0,  1,  // L
                            1,  -1, 1,  -1, 0}; // S


     /**
     * Public : Player
     * 
     * Description:
     *      Seeds the RNG and generates weapons.
     */
    Player() {
        //seeding each player with a different engine
        eng = seeded_engine();

        //generating weapons
        weapon1 = GenerateWeapon();
        weapon2 = GenerateWeapon();

        // if both weapons are the same
        // choose another.
        while (weapon2 == weapon1) {
            weapon2 = GenerateWeapon();
        }
    }

     /**
     * Public : emoji
     * 
     * Description:
     *      Converts an emoji integer into its actual emoji equivalent.
     * 
     * Params:
     *      int     :  the roudn that the game is on (round 1 corresponds to weapon1. and so on)
     * 
     * Returns:
     *      string  :   the emoji code
     */
    string emoji(int round) {
        if (round == 1) {
            switch (weapon1) {
            case 0:
                return rock;
            case 1:
                return paper;
            case 2:
                return scissors;
            case 3:
                return lizard;
            case 4:
                return spock;
            }
        }
        else {
            switch (weapon2) {
            case 0:
                return rock;
            case 1:
                return paper;
            case 2:
                return scissors;
            case 3:
                return lizard;
            case 4:
                return spock;
            }
        }
    }

     /**
     * Public : seeded_engine
     * 
     * Description:
     *      generates a seed
     * 
     * Returns:
     *      mt19937   : a seed?
     *
     *  Code sourced from 
     *  https://stackoverflow.com/questions/13215461/seeding-rand-for-a-c-class
     *  Credit: bames53
     */
    mt19937 seeded_engine() {
        random_device r;
        seed_seq seed{ r(), r(), r(), r(), r(), r(), r(), r() };
        return (mt19937(seed));
    }
    
     /**
     * Public : GenerateWeapon
     * 
     * Description:
     *      Generates a weapon by choosing a random number beyween 0 and 4.
     * Returns:
     *      int     :   an integer representation of the weapon
     */
    int GenerateWeapon() { return uniform_int_distribution<>(0, 4)(eng); }

     /**
     * Public : TieBreaker
     * 
     * Description:
     *      replaces both players weapons for a given round until there is a winner
     * 
     * Params:
     *      Player  :   the opponent that is battling this player
     *      int     :   the round that is being played on
     * 
     * Returns:
     *      bool    : represents who won the tie breaker.
     */
    bool TieBreaker(Player opponent, int round) {

        if (round == 1) {
            while (weapon1 == opponent.weapon1) {
                weapon1 = GenerateWeapon();
                opponent.weapon1 = GenerateWeapon();
            }

            switch (lookup[weapon1][opponent.weapon1]) {
            case -1:
                return false;
            case 1:
                return true;
            }
        }
        else {
            while (weapon2 == opponent.weapon2) {
                weapon2 = GenerateWeapon();
                opponent.weapon2 = GenerateWeapon();
            }

            switch (lookup[weapon2][opponent.weapon2]) {
            case -1:
                return false;
            case 1:
                return true;
            }
        }
    }

    
     /**
     * Public : Battle
     * 
     * Description:
     *      Compares both players weapons on the lookup table and determines a winner.
     *      If a winner cannot be decided then tiebreaker is called
     * 
     * Params:
     *      Player  :   the opponent that is battling this player
     *      int     :   the round that is being played on
     * 
     * Returns:
     *      bool    : represents who won the round.
     */
    bool Battle(Player opponent, int round) {
        if (round == 1) {
            switch (lookup[weapon1][opponent.weapon1]) {
            case -1:
                return false;
            case 1:
                return true;
            case 0:
                return TieBreaker(opponent, round);
            }
        }
        else {
            switch (lookup[weapon2][opponent.weapon2]) {
            case -1:
                return false;
            case 1:
                return true;
            case 0:
                return TieBreaker(opponent, round);
            }
        }
    }
};


/**
 * RPSLS
 * 
 * Description:
 *      Wrapper for the game so that it can be executed with one function.
 * 
 * Public Methods:
 *      RPSLS       :   Empty constructor
 *      Start       :   Starts the game
 * Usage: 
 * 
 *  RPSLS r;
 *  r.Start();
 *      
 */
class RPSLS {
private:
    bool endGame = true;

public:
    RPSLS() {};
    
     /**
     * Public : Start
     * 
     * Description:
     *      Driver code of the game. Displays results based of boolean results from the battle method.
     */
    void Start() {
        while (endGame) {
            Player p1, p2;

            if (p1.Battle(p2, 1)) {
                cout << "Player 1's " << p1.emoji(1) << " beat Player 2's "
                    << p2.emoji(1) << "!" << endl;
            }
            else {
                cout << "Player 2's " << p2.emoji(1) << " beat Player 1's "
                    << p1.emoji(1) << "!" << endl;
            }

            if (p1.Battle(p2, 2)) {
                cout << "Player 1's " << p1.emoji(2) << " beat Player 2's "
                    << p2.emoji(2) << "!" << endl;
            }
            else {
                cout << "Player 2's " << p2.emoji(2) << " beat Player 1's "
                    << p1.emoji(2) << "!" << endl;
            }

            cout << "Play another round? (1/0): ";
            cin >> endGame;
        }
    }
};

int main() {
    RPSLS r;

    r.Start();

    return (0);
}
