#include <iostream>
#include <string>

#define ISFULL if(IsFull()){Resize();}

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

   //Constructors
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

    //Push Methods
    void PushFront(int val)
    {
        ISFULL;

        for(int i = vindex; i > 0; i--)
        {
            array[i] = array[i - 1];
        }

        array[0] = val;

        cout << "PF " << val << endl;

        vindex++;
    }

    void PushFront(Vector v)
    {
        
    }

    void PushRear(int val)
    {
        ISFULL;

        array[vindex] = val;

        cout << "PR " << val << endl;

        vindex++;
    }

    void PushRear(Vector v)
    {

    }

    void PushAt(int location, int val)
    {
        ISFULL;

        for(int i = vindex; i > location; i--)
        {
            array[i] = array[i - 1];
        }
        
        array[location] = val;

        vindex++;
    }

    int Pop()
    {
        return(0);
    }

    void Print(int num = 0)
    {
        int to;

        to = num ? num : size;

        for(int i = 0; i < to; i++)
        {
            cout << array[i] << endl;
        }
    }

    bool IsFull()
    {
        return vindex < size ? false : true;
    }

    void Resize()
    {
        cout << "RESIZE" << endl;
        int* temp;
        size += 10;
        cout << size << endl;
        temp = new int[size];
        cout << "bb" << endl;
        for(int i = 0; i < size; i++)
        {
            temp[i] = array[i];
        }
        cout << "c" << endl;
        array[0] = temp[0];
        delete[] temp;
        cout << "FIN" << endl;
    }


};


int main()
{
    Vector V;
    // for(int i = 0; i < 15; i++)
    // {
    //     V.PushRear(i);
    // }

    // for(int i = 0; i < 15; i++)
    // {
    //     V.PushFront(i);
    // }

    V.Print();
    cout << "Hello!" << endl;
    return(0);
}