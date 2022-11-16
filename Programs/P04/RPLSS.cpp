#include <iostream>
#include <map>
#include <chrono>
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
    int weapon1;
    int weapon2;
    int weaponT;
    // Does r beat c?   R  P  S  L  S         -1 = No, 0 = Tie, 1 = Yes
    int lookup[5][5] = { 0, -1, 1, 1, -1,   //R
                        1, 0, -1, -1, 1,   //P
                        -1, 1, 0, 1, -1,   //S
                        -1, 1, -1, 0, 1,   //L
                        1, -1, 1, -1, 0, }; //S

    /**
     * Constructor guarantees a player has two different "weapons"
     */
    Player() {

        srand();
        weapon1 = GenerateWeapon();
        weapon2 = GenerateWeapon();
        weaponT = GenerateWeapon();

        // if both weapons are the same
        // choose another.
        while (weapon2 == weapon1) {
            weapon2 = GenerateWeapon();
        }
    }

    int GenerateWeapon()
    {
        return (rand() % 5);
    }

    bool TieBreaker(Player rhs)
    {
        while (weaponT == rhs.weapon1) {
            weaponT = GenerateWeapon();
            rhs.weaponT = GenerateWeapon();
        }
        if (weaponT > rhs.weaponT)
            return true;
        else
            return false;
    }

    bool operator<(Player rhs)
    {
        switch (lookup[weapon1][rhs.weapon1])
        {
            case -1:
                return true;
            case 1:
                return false;
            case 0:
                return !TieBreaker(rhs);
        }
    }

    bool operator>(Player rhs)
    {
        switch (lookup[weapon1][rhs.weapon1])
        {
        case -1:
            return false;
        case 1:
            return true;
        case 0:
            return TieBreaker(rhs);
        }
    }

    bool operator==(const Player rhs)
    {
        switch (lookup[weapon1][rhs.weapon1])
        {
        case 0:
            return true;
        default:
            return false;
        }
    }

    // other possible methods
};



class RPSLS
{
private:

    bool endGame = false;
public:

    RPSLS() {};
    void Start()
    {
        while (!endGame)
        {
            Player p1, p2;

            cout << p1.weapon1 << endl;
            cout << p1.weapon2 << endl;
            cout << p2.weapon1 << endl;
            cout << p2.weapon2 << endl;


            //if (p1.weapon1 > p2.weapon1) {
            //    cout << "Player 1's " << p1.weapon1 << " beat Player 2's " << p2.weapon1 << "!" << endl;
            //}
            //else if (p2.weapon1 > p1.weapon1) {
            //    cout << "Player 2's " << p2.weapon1 << " beat Player 1's " << p1.weapon1 << "!" << endl;
            //}
            //else {
            //    cout << "In the Tie Breaker Round: " << endl;
            //    if (p1.weaponT > p2.weaponT) {
            //        cout << "Player 1's " << p1.weaponT << " beat Player 2's " << p2.weaponT << "!" << endl;
            //    }
            //    else if (p2.weaponT > p1.weaponT) {
            //        cout << "Player 2's " << p2.weaponT << " beat Player 1's " << p1.weaponT << "!" << endl;

            //    }
            //}

            //if (p1.weapon2 > p2.weapon2) {
            //    cout << "Player 1's " << p1.weapon2 << " beat Player 2's " << p2.weapon2 << "!" << endl;
            //}
            //else if (p2.weapon2 > p1.weapon2) {
            //    cout << "Player 2's " << p2.weapon2 << " beat Player 1's " << p1.weapon2 << "!" << endl;
            //}
            //else {
            //    cout << "In the Tie Breaker Round: " << endl;
            //    if (p1.weaponT > p2.weaponT) {
            //        cout << "Player 1's " << p1.weaponT << " beat Player 2's " << p2.weaponT << "!" << endl;
            //    }
            //    else if (p2.weaponT > p1.weaponT) {
            //        cout << "Player 2's " << p2.weaponT << " beat Player 1's " << p1.weaponT << "!" << endl;

            //    }
            //}

            cin >> endGame;

        }
    }
};

int main()
{
    RPSLS r;

    r.Start();

    return(0);
}
