#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "fighter.hpp"

using namespace std;

#pragma once

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
};