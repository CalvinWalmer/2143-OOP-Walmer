#include <iostream>
#include <vector>
#include <random>
#include <string>

using namespace std;

#pragma once

/**
 * @brief Splits a string into parts based on a delimiter
 *
 *      For example the string: "2.d.12" would be turned into
 *      a vector => ["2","d","12"] and returned
 *
 * @param s
 * @param delimiter
 * @return vector<string>
 */
vector<string> tokenize(string s, string delimiter) {
    size_t pos = 0;
    vector<string> tokens;
    while ((pos = s.find(delimiter)) != string::npos) {
        tokens.push_back(s.substr(0, pos));
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);
    return tokens;
}

/**
 * @brief Chooses a random item from a vector of strings
 *
 *      Example:
 *          given => ["1.d.4","1.d.6","1.d.8"]
 *          Choose one of the 3 choices at random and return it.
 *
 * @param choices
 * @return string
 */
string randomChoice(vector<string> choices) {
    return choices[rand() % choices.size()];
}


    /**
     * Public GetIntInput
     * 
     * Description:
     *      Given an upper and a lower bound, perform input validation on the user's input.
     *      Safely converts characters to numbers. Based on code from
     *      https://stackoverflow.com/a/4990923/19922415
     *      Credit: ari-free, LPL
     * 
     * Params:
     *      - int   lBound  lowest acceptable value
     *      - int   uBound  highest acceptable value
     * 
     * Returns:
     *      - int   an integer that falls within the bounds
     */
int GetIntInput(int lBound, int uBound)
{
    string inp;
	int choice;
    do
    {
        getline(cin, inp);
        stringstream stream(inp);

        if(stream >> choice)
            if (choice >= lBound && choice <= uBound)
                break;
        cout << "Invalid Input" << endl;
    }while(true);

    return choice;
}