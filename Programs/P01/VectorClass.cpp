#include <iostream>
#include <string>

#define ISFULL if(IsFull()){Resize();}
#define ISEMPTY if(IsEmpty()){cout << "Vector is empty. No values to pop!"; return 0;}

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
        ISFULL

        for(int i = vindex; i > 0; i--)
        {
            array[i] = array[i - 1];
        }

        array[0] = val;

        vindex++;
    }

    void PushFront(Vector v)
    {
        
    }

    void PushRear(int val)
    {
        ISFULL

        array[vindex] = val;

        vindex++;
    }

    void PushRear(Vector v)
    {

    }

    void PushAt(int location, int val)
    {
        ISFULL

        for(int i = vindex; i > location; i--)
        {
            array[i] = array[i - 1];
        }
        
        array[location] = val;

        vindex++;
    }



    //POP METHODS
    int PopFront()
    {
        ISEMPTY

        int temp = array[0];

        for(int i = 0; i < vindex; i++)
        {
            array[i] = array[i + 1];
        }

        return(temp);
    }

    int PopRear()
    {
        ISEMPTY
        vindex--;
        return(array[vindex]);
    }

    int PopAt(int location)
    {
        ISEMPTY

        int temp = array[location];
        
        for(int i = location; i < vindex; i++)
        {
            array[i] = array[i + 1];
        }

        return temp;
    }

    int SearchPop(int val)
    {
        int temp;

        for(int i = 0; i < vindex; i++)
        {
            temp = array[i];
        }
        
    }

    void Print(int num = 0)
    {
        int to;

        to = num ? num : size;

        for(int i = 0; i < to; i++)
        {
            cout << array[i] << endl;
        }

        cout << "---" << endl;
    }

    bool IsFull()
    {
        return vindex < size ? false : true;
    }

    bool IsEmpty()
    {
        return vindex == 0;
    }

    void Resize()
    {
        size *= 2;
        int *tempArray = new int[size];
        for (int i = 0; i < vindex; i++) {
            tempArray[i] = array[i];
        }
        delete[] array;
        array = tempArray;
    }


};


int main()
{
    Vector V;
    for(int i = 0; i < 15; i++)
    {
        V.PushRear(i);
    }

    for(int i = 0; i < 15; i++)
    {
        V.PushFront(i);
    }

    V.PushAt(0, 555);


    V.Print(V.vindex);
    cout << V.PopRear() << endl;
    V.Print(V.vindex);
    cout << V.PopAt(13) << endl;
    V.Print(V.vindex);
    return(0);
}