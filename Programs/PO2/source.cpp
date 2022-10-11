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

    ofstream fout;
    fout.open("output.txt");

    fout << V1 << endl;

    fout << V1 << endl;
    fout << V2 << endl;

    fout << V1 + V2 << endl;

    fout << V1 - V2 << endl;

    fout << V1 * V2 << endl;

    fout << V1 / V2 << endl;

    fout << V2 / V1 << endl;

    fout << (V1 == V2) << endl;

    MyVector V3 = V2;

    fout << V2 << endl;

    fout << V3 << endl;

    fout << (V2 == V3) << endl;

    return(0);
}