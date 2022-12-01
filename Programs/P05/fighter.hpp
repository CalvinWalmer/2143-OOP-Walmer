#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "weapon.hpp"
#include "helpers.hpp"

using namespace std;

#pragma once


class BaseFighter {
protected:
    string name;
    int max_HP;
    int HP;
    float RR;
    Weapon* weapon;

public:
    BaseFighter() {
        name = "None";
        int max_HP = 1;
        HP = max_HP;
        float RR = 0;
        weapon = new Weapon;
    }

    virtual double attack() {
        return weapon->use();
    }

    int GetHP() { return HP; }
    string GetWeapon() { return weapon->GetName(); }
    string GetFighterType() { return name; }

    void Regen()
    {
        HP = HP + (max_HP * RR) > max_HP ? max_HP : HP + (max_HP * RR);
    }

    friend ostream& operator<<(ostream& os, const BaseFighter& f) {
        return os << "[" << f.name << " , " << *f.weapon << "]";
    }

};

class Warrior : public BaseFighter
{
public:
    Warrior()
    {
        name = "Warrior";
        max_HP = (new Dice("1.d.10"))->roll();
        RR = .25;
        weapon = WeaponFactory::createWeapon("Sword");
    }
};

class Wizard : public BaseFighter
{
public:
    Wizard()
    {
        name = "Wizard";
        max_HP = (new Dice("1.d.10"))->roll();
        HP = max_HP;
        RR = .3;
        weapon = WeaponFactory::createWeapon("Spell");
    }
};

class Dragonborn : public BaseFighter
{
public:
    Dragonborn()
    {
        name = "Dragonborn";
        max_HP = (new Dice("1.d.10"))->roll();
        HP = max_HP;
        RR = .3;
        weapon = WeaponFactory::createWeapon("Fire Sword");
    }
};

class Archer : public BaseFighter
{
public:
    Archer()
    {
        name = "Archer";
        max_HP = (new Dice("1.d.10"))->roll();
        HP = max_HP;
        RR = .25;
        weapon = WeaponFactory::createWeapon("Bow");
    }
};

class Elf : public BaseFighter
{
public:
    Elf()
    {
        name = "Elf";
        max_HP = (new Dice("1.d.10"))->roll();
        HP = max_HP;
        RR = .35;
        weapon = WeaponFactory::createWeapon("Enchanted Sword");
    }
};

class FighterFactory
{
public:
    static BaseFighter* createFighter(string type)
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
        else if (type == "Dragonborn")
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

    static BaseFighter* createFighter(int type)
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