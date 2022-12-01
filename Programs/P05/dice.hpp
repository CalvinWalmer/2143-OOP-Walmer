#include <iostream>
#include <vector>
#include <string>
#include <random>
#include "helpers.hpp"

using namespace std;

#pragma once

class Die {
    int sides;
    mt19937 eng;

    void Seed()
    {
        eng = seeded_engine();
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
public:
    Die() :sides{ 6 } {}
    Die(int sides) :sides{ sides } {  }
    int roll(int rolls = 1) {
        int sum = 0;
        while (rolls--) {
            sum += uniform_int_distribution<>(1, sides)(eng);
        }
        return sum;
    };

    friend ostream& operator<<(ostream& os, const Die& d) {
        return os << "[" << d.sides << "]";
    }
};


class Dice {
private:
    vector< Die > dice;
    bool average;
    bool best;
    bool constant;

public:

    Dice() {
        init(1, 6);
    }
    Dice(int n, int s) {
        init(n, s);
    }
    Dice(string d) {
        vector<string> parts = tokenize(d, ".");

        int n = stoi(parts[0]);
        int s = stoi(parts[2]);

        init(n, s);
    }

    void init(int n, int s) {
        while (n--) {
            dice.push_back(Die(s));
        }
    }

    /**
     * @brief Roll the dice and return the sum
     *
     * @param rolls
     * @return int : sum of rolls
     */
    int roll(int rolls = 1) {
        int sum = 0;
        while (rolls--) {
            for (int i = 0; i < dice.size(); i++) {
                sum += dice[i].roll();
            }
        }
        return sum;
    }

    /**
     * @brief Roll the dice and return the maximum dice value
     *
     * @param None
     * @return int : max value of all die being rolled
     */
    int maxRoll(int rolls = 1) {
        int max = 1;
        while (rolls--) {
            for (int i = 0; i < dice.size(); i++) {
                int val = dice[i].roll();
                if (max < val)
                {
                    max = val;
                }
            }
        }
        return max;
    }

    /**
     * @brief Roll the dice and return the AVG dice value
     *
     * @param None
     * @return int : AVG value of all die being rolled
     */
    int avgRoll(int rolls = 1) {
        int sum = 0;
        while (rolls--) {
            for (int i = 0; i < dice.size(); i++) {
                sum += dice[i].roll();
            }
        }
        return sum / dice.size();
    }


    friend ostream& operator<<(ostream& os, const Dice& d) {
        for (int i = 0; i < d.dice.size(); i++) {
            os << d.dice[i];
        }
        return os;
    }
};