#include <iostream>
#include <string>
#include <vector>

#include "dice.hpp"
#include "helpers.hpp"

using namespace std;

#pragma once

/**
 * Weapon
 * 
 * Description:
 *      Weapon class provides a basic object with a name, a damage value to be used with 
 *      the Dice class, and a Dice to roll. Class is meant to be extended with child classes
 *      using the WeaponFactory class to create the objects.
 * 
 * Public Methods:
 *      - Weapon()
 *      - Weapon(vector< string > choices)
 *      - GetName()
 *      - use()
 * 
 * Usage: 
 * 
 *      Weapon* myWeapon = new Weapon;
 *      cout << myWeapon->use(); //3
 */
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

    string GetName() { return name; } //returns the name of the weapon

    double use() { return die->roll(); } //uses the weapon by rolling a die. returns the die roll's value.

    friend ostream& operator<<(ostream& os, const Weapon& w) {
        return os << w.name << " Damage: " << w.damage;
    }
};

/**
 * Sword
 * 
 * Description:
 *      Extention of Weapon with all the same methods except a modified
 *      constructor that only modifies the name and damage of the weapon
 * 
 * Note: 
 *      See parent Weapon implementation!
 */
class Sword : public Weapon
{
public:
    Sword()
    {
        name = "Sword";
        damage = "1.d.4";
        die = new Dice(damage);
    }
};

/**
 * Bow
 * 
 * Description:
 *      Extention of Weapon with all the same methods except a modified
 *      constructor that only modifies the name and damage of the weapon
 * 
 * Note: 
 *      See parent Weapon implementation!
 */
class Bow : public Weapon
{
public:
    Bow()
    {
        name = "Bow";
        damage = "2.d.4";
        die = new Dice(damage);
    }
};

/**
 * Spell
 * 
 * Description:
 *      Extention of Weapon with all the same methods except a modified
 *      constructor that only modifies the name and damage of the weapon
 * 
 * Note: 
 *      See parent Weapon implementation!
 */
class Spell : public Weapon
{
public:
    Spell()
    {
        name = "Magic Spell";
        damage = "2.d.3";
        die = new Dice(damage);
    }
};

/**
 * EnchantedSword
 * 
 * Description:
 *      Extention of Weapon with all the same methods except a modified
 *      constructor that only modifies the name and damage of the weapon
 * 
 * Note: 
 *      See parent Weapon implementation!
 */
class EnchantedSword : public Weapon
{
public:
    EnchantedSword()
    {
        name = "Enchanted Sword";
        damage = "2.d.4";
        die = new Dice(damage);
    }
};

/**
 * FireSword
 * 
 * Description:
 *      Extention of Weapon with all the same methods except a modified
 *      constructor that only modifies the name and damage of the weapon
 * 
 * Note: 
 *      See parent Weapon implementation!
 */
class FireSword : public Weapon
{
public:
    FireSword()
    {
        name = "Fire Sword";
        damage = "4.d.2";
        die = new Dice(damage);
    }
};


/**
 * WeaponFactor
 * 
 * Description:
 *      Class is a factory that takes in user input and creates a child weapon object
 *      based upon that input.
 * 
 * Public Methods:
 *      static Weapon* createWeapon
 * 
 * 
 * Usage: 
 * 
 *  Weapon* myWeapon = WeaponFactory::createWeapon("Bow");
 *      
 */
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