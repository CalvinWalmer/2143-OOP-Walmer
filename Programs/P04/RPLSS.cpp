#include <iostream>

using namespace std;

class RPSLS
{
    private:
    // Does r beat c?   R  P  S  L  S         -1 = No, 0 = Tie, 1 = Yes
    int lookup[5][5] = {0, -1, 1, 1, -1,   //R
                        1, 0, -1, -1, 1,   //P
                        -1, 1, 0, 1, -1,   //S
                        -1, 1, -1, 0, 1,   //L
                        1, -1, 1, -1, 0,}; //S
    public:

    RPSLS(){};

    void Start()
    {

    }

};

int main()
{
    RPSLS r;

    r.Start();
}