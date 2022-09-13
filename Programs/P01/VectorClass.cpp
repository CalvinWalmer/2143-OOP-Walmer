#include <iostream>
#include <string>

using namespace std;

struct Vector
{
    int* array;
    int vindex;
    int size;

    bool isEmpty;

    /*
        Functions
        PushFront(int val)
        PushFront(Vector v)

        PushRear(int val)
        PushRear(Vector v)

        PushAt(int location, int val)

        InOrderPush(int val)

        PopFront()

        PopRear()

        PopAt(int loc)

        SearchPop(int val)
    */

    Vector()
    {
        array = new int[10];
        vindex = 0;
        size = 10;
    }

    Vector(int *A, int size)
    {

    }

    Vector(string fileName)
    {

    }

    ~Vector()
    {
        delete[] array;

    }


    void Push(int val)
    {
        if (isFull()) 
            Resize();

        array[vindex] = val;
        vindex++;
    }

    int Pop()
    {
        return(0);
    }

    void PushAt(int index, int val)
    {
    }

    void Print()
    {
        for(int i = 0; i < size; i++)
        {
            cout << array[i] << endl;
        }
    }

    bool isFull()
    {
        return vindex < size ? false : true;
    }

    void Resize()
    {
        int* temp;
        size *= 2;
        temp = new int[size];
        for(int i; i < size; i++)
        {
            temp[i] = array[i];
        }
        array[0] = temp[0];
        delete[] temp;
    }


};


int main()
{
    Vector V;
    for(int i = 0; i < 15; i++)
    {
        V.Push(i);
    }

    V.Print();
    return(0);
}