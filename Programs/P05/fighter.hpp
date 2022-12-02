#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "weapon.hpp"
#include "helpers.hpp"

using namespace std;

#pragma once

/**
 * BaseFighter
 * 
 * Description:
 *      BaseFighter class provides a default fighter with HP , a regen rate, a basic weapon,
 *      and a name. It is meant to be extended through child classes. Has several unility methods that
 *      handle regen as well as taking damage and attacking.
 * 
 * Public Methods:
 *      - BaseFighter()
 *      - attack()
 *      - GetHP()
 *      - GetMaxHP()
 *      - GetWeapon()
 *      - GetFighterType()
 *      - Regen()
 *      - Damage(int value)
 *      - isDead()
 * 
 * Usage: 
 * 
 *      BaseFighter* f1 = new BaseFighter();
 *      BaseFighter* f2 = new BaseFighter();
 *      
 *      //fight!
 *      f2.Damage(f1.attack()); // f1 attacks f2!
 *      
 */
class BaseFighter {
protected:
    string name;
    int max_HP;
    int HP;
    float RR;
    Weapon* weapon;

public:
    
    /**
     * Public : BaseFighter
     * 
     * Description:
     *      Constructor, initializes values and generates a new default weapon.
     * 
     * Params:
     *      - none
     * 
     * Returns:
     *      - nothing
     */
    BaseFighter() {
        name = "None";
        int max_HP = 1;
        HP = max_HP;
        float RR = 0;
        weapon = new Weapon;
    }


    virtual double attack() {return weapon->use();} //Uses the weapon the fighter is holding
    int GetHP() { return HP; } //returns current HP
    int GetMaxHP() { return max_HP; } // Returns max HP
    string GetWeapon() { return weapon->GetName(); } //returns the name of the weapon they are using
    string GetFighterType() { return name; } //returns the type of fighter this is

    void Regen() { HP = HP + (max_HP * RR) > max_HP ? max_HP : HP + (max_HP * RR);}
    //Regen points (RR * maxHP) are added to the current HP if the total is less than the max HP

    void Damage(int value){ HP -= value; } //subtracts damage amount from HP

    bool isDead(){return (HP <= 0);} //checks if this fighter is dead or not

    //operator overload for convenient use with cout
    friend ostream& operator<<(ostream& os, const BaseFighter& f) {
        return os << f.name << " HP: "  << f.HP << "/" << f.max_HP << " "  << string(f.HP, (char)987) << string(f.max_HP - f.HP, ' ') << "| Weapon: " << *f.weapon;
    }

};

/**
 * Warrior
 * 
 * Description:
 *      Extention of BaseFighter with all the same methods except a modified
 *      constructor that only modifies the name, HP, regen rate, and weapon the fighter
 *      has. Uses the WeaponFactory class to create weapons for the fighter
 * 
 * Note: 
 *      See parent BaseFighter implementation!
 */
class Warrior : public BaseFighter
{
public:
    Warrior()
    {
        name = "Warrior";
        max_HP = (new Dice("3.d.3"))->roll() + 4;
        HP = max_HP;
        RR = .125;
        weapon = WeaponFactory::createWeapon("Sword");
    }
};

/**
 * Wizard
 * 
 * Description:
 *      Extention of BaseFighter with all the same methods except a modified
 *      constructor that only modifies the name, HP, regen rate, and weapon the fighter
 *      has. Uses the WeaponFactory class to create weapons for the fighter
 * 
 * Note: 
 *      See parent BaseFighter implementation!
 */
class Wizard : public BaseFighter
{
public:
    Wizard()
    {
        name = "Wizard";
        max_HP = (new Dice("3.d.3"))->roll() + 4;
        HP = max_HP;
        RR = .14;
        weapon = WeaponFactory::createWeapon("Spell");
    }
};

/**
 * Dragonborn
 * 
 * Description:
 *      Extention of BaseFighter with all the same methods except a modified
 *      constructor that only modifies the name, HP, regen rate, and weapon the fighter
 *      has. Uses the WeaponFactory class to create weapons for the fighter
 * 
 * Note: 
 *      See parent BaseFighter implementation!
 */
class Dragonborn : public BaseFighter
{
public:
    Dragonborn()
    {
        name = "Dragonborn";
        max_HP = (new Dice("3.d.4"))->roll() + 4;
        HP = max_HP;
        RR = .1325;
        weapon = WeaponFactory::createWeapon("Fire Sword");
    }
};

/**
 * Archer
 * 
 * Description:
 *      Extention of BaseFighter with all the same methods except a modified
 *      constructor that only modifies the name, HP, regen rate, and weapon the fighter
 *      has. Uses the WeaponFactory class to create weapons for the fighter
 * 
 * Note: 
 *      See parent BaseFighter implementation!
 */
class Archer : public BaseFighter
{
public:
    Archer()
    {
        name = "Archer";
        max_HP = (new Dice("2.d.2"))->roll() + 4;
        HP = max_HP;
        RR = .125;
        weapon = WeaponFactory::createWeapon("Bow");
    }
};

/**
 * Elf
 * 
 * Description:
 *      Extention of BaseFighter with all the same methods except a modified
 *      constructor that only modifies the name, HP, regen rate, and weapon the fighter
 *      has. Uses the WeaponFactory class to create weapons for the fighter
 * 
 * Note: 
 *      See parent BaseFighter implementation!
 */
class Elf : public BaseFighter
{
public:
    Elf()
    {
        name = "Elf";
        max_HP = (new Dice("3.d.2"))->roll() + 4;
        HP = max_HP;
        RR = .2;
        weapon = WeaponFactory::createWeapon("Enchanted Sword");
    }
};


/**
 *  FighterFactory
 * 
 * Description:
 *      Class is a factory that takes in user input and creates a child BaseFighter object
 *      based upon that input.
 * 
 * Public Methods:
 *      static BaseFighter* createFighter
 * 
 * 
 * Usage: 
 * 
 *  BaseFighter* myFighter = FighterFactory::createFighter("DragonBorn");
 *      
 */
class FighterFactory
{
public:
    static BaseFighter* createFighter(string type) //overloeaded to accept string values
    {
        BaseFighter* fighter = nullptr;

        if (type == "Warrior")
        {
            fighter = new Warrior;
        }
        else if (type == "Wizard")
        {
            fighter = new Wizard;
        }
        else if (type == "DragonBorn")
        {
            fighter = new Dragonborn;
        }
        else if (type == "Archer")
        {
            fighter = new Archer;
        }
        else if (type == "Elf")
        {
            fighter = new Elf;
        }
        else
        {
            fighter = new BaseFighter;
        }

        return fighter;
    }

    static BaseFighter* createFighter(int type) //overloaded to accept int values
    {
        BaseFighter* fighter = nullptr;

        if (type == 1)
        {
            fighter = new Warrior;
        }
        else if (type == 2)
        {
            fighter = new Wizard;
        }
        else if (type == 3)
        {
            fighter = new Dragonborn;
        }
        else if (type == 4)
        {
            fighter = new Archer;
        }
        else if (type == 5)
        {
            fighter = new Elf;
        }
        else
        {
            fighter = new BaseFighter;
        }

        return fighter;
    }
};