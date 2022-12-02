## P05 - BolNverse game
### Calvin Walmer
### Description:

This program is a game in which a large group of attackers outnumber your small group of defenders by 100 to 1. A mighty battle is waged between the attackers and defenders. The defenders are allowed in a room so they are allowed to switch out freely at will and rest. The defenders however are in a hallway and can only attack one at a time. The program implements simple turn based combat. Under the hood there are examples of dyanmic polymorphism and a factory design pattern utilization.

The program reads enemies from an input fill and then lets the user pick thier party based off the number of enemies. 

### Files

|   #   | File            | Description                                        |
| :---: | --------------- | -------------------------------------------------- |
|   1   | BolNverse.cpp   | Main driver of my project that launches game.      |
|   2   | helpers.hpp     | helper functions for input validation and tokenization|
|   3   | fighter.hpp     | Contains FighterFactory factory and the parent class and children fighter classes |
|   4   | weapon.hpp      | Contains WeaponFactory factory and the parent class and children weapon classes |
|   3   | dice.hpp        | Contains die and dice classes for RNG |
|   3   | attackers.in    | Sample input file containing 1700 enemies|
|   3   | attackers.txt    | Sample input file containing 1700 enemies|
|   3   | attackers100.txt    | Sample input file containing 100 enemies|

### Instructions

- Make sure all input files are placed in the same director as the executable otherwise specify a path when prompted.
- On compile, make sure all .cpp and .hpp files are located in the same directory

