#include <chrono>
#include <iostream>
#include <map>
#include <random>
using namespace std;

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

struct Player {
    mt19937 eng;
    int weapon1;
    int weapon2;
    // Does r beat c?   R  P  S  L  S         -1 = No, 0 = Tie, 1 = Yes
    int lookup[5][5] = {
        0,  -1, 1,  1,  -1, // R
        1,  0,  -1, -1, 1,  // P
        -1, 1,  0,  1,  -1, // S
        -1, 1,  -1, 0,  1,  // L
        1,  -1, 1,  -1, 0,
    }; // S

    /**
     * Constructor guarantees a player has two different "weapons"
     */
    Player() {

        eng = seeded_engine();

        weapon1 = GenerateWeapon();
        weapon2 = GenerateWeapon();

        // if both weapons are the same
        // choose another.
        while (weapon2 == weapon1) {
            weapon2 = GenerateWeapon();
        }
    }

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

    mt19937 seeded_engine() {
        random_device r;
        seed_seq seed{ r(), r(), r(), r(), r(), r(), r(), r() };
        return (mt19937(seed));
    }

    int GenerateWeapon() { return uniform_int_distribution<>(0, 4)(eng); }

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

class RPSLS {
private:
    bool endGame = true;

public:
    RPSLS() {};

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
