#include "MyVector.cpp"
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    int A1[] = {1, 2, 3, 4 ,5};
    int A2[] = {10, 20, 30, 40, 50, 60, 70};
    MyVector V1(A1, sizeof(A1) / sizeof(int));
    MyVector V2(A2, sizeof(A2) / sizeof(int));

    cout << V1 << endl;
    cout << V2 << endl;

    cout << V1 + V2 << endl;

    cout << V1 - V2 << endl;

    cout << V1 * V2 << endl;

    cout << V1 / V2 << endl;

    cout << V2 / V1 << endl;

    cout << (V1 == V2) << endl;

    MyVector V3 = V2;

    cout << V2 << endl;

    cout << V3 << endl;

    cout << (V2 == V3) << endl;

    return(0);
}