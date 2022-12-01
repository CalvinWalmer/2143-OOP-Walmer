#include <iostream>
#include <string>
#include <vector>

#include "dice.hpp"
#include "helpers.hpp"

using namespace std;

#pragma once

class Weapon {
protected:
    string name;    // name of weapon
    string damage;  // damage per roll or "use"
    Dice* die;

public:
    /**
     * @brief Construct a new Base Weapon object
     *  Also invokes the Dice class constructor with the "die" type
     */
    Weapon() {
        name = "Fists&Feet";
        damage = "1.d.4";
        die = new Dice(damage);
    }
    /**
     * @brief Overloaded Constructor for a new Base Weapon object
     *  Also invokes the Dice class constructor with the "die" type
     * @param choices-vector of string "die" choices like {"2.d.8","2.d.10","3.d.4"}
     */
    Weapon(vector< string > choices) {
        name = "Fists&Feet";
        damage = randomChoice(choices);
        die = new Dice(damage);
    }

    string GetName() { return name; };

    double use() {
        return die->roll();
    }

    friend ostream& operator<<(ostream& os, const Weapon& w) {
        return os << "[" << w.name << " , " << w.damage << "]";
    }
};

class Sword : public Weapon
{
public:
    Sword()
    {
        name = "Sword";
        damage = "3.d.4";
        die = new Dice(damage);
    }
};

class Bow : public Weapon
{
public:
    Bow()
    {
        name = "Bow";
        damage = "1.d.8";
        die = new Dice(damage);
    }
};

class Spell : public Weapon
{
public:
    Spell()
    {
        name = "Magic Spell";
        damage = "3.d.6";
        die = new Dice(damage);
    }
};

class EnchantedSword : public Weapon
{
public:
    EnchantedSword()
    {
        name = "Enchanted Sword";
        damage = "3.d.6";
        die = new Dice(damage);
    }
};

class FireSword : public Weapon
{
public:
    FireSword()
    {
        name = "Fire Sword";
        damage = "4.d.5";
        die = new Dice(damage);
    }
};


class WeaponFactory
{
public:
    static Weapon* createWeapon(string type)
    {
        Weapon* weapon = nullptr;

        if (type == "Sword")
        {
            weapon = new Sword;
        }
        else if (type == "Bow")
        {
            weapon = new Bow;
        }
        else if (type == "Spell")
        {
            weapon = new Spell;
        }
        else if (type == "Enchanted Sword")
        {
            weapon = new EnchantedSword;
        }
        else if (type == "Fire Sword")
        {
            weapon = new FireSword;
        }
        else
        {
            weapon = new Weapon;
        }

        return weapon;
    }
};