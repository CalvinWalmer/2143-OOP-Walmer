#include <iostream>
#include <fstream>
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

        InOrderPush(int val)

    */

   //Constructors
    Vector()
    {
        array = new int[10];
        vindex = 0;
        size = 10;
    }

    Vector(int _size)
    {
        array = new int[size];
        vindex = 0;
        size = _size;
    }

    Vector(int *A, int _size)
    {
        array = new int[_size];
        vindex = 0;
        size = _size;

        for(int i = 0; i < _size; i++)
        {
            array[i] = A[i];
            vindex++;
        }
    }

    Vector(string fileName)
    {
        ifstream inpf;
        int temp;

        array = new int[10];
        vindex = 0;
        size = 10;

        inpf.open(fileName);

        while (!inpf.eof())
        {
            inpf >> temp;
            this->PushRear(temp);
        }

        inpf.close();
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
        int* temp;
        
    }

    void PushRear(int val)
    {
        ISFULL

        array[vindex] = val;

        vindex++;
    }

    void PushRear(Vector v)
    {
        int newSize = size + v.size;
        int i, j;
        int* temp= new int[newSize];

        for (i = 0; i < size; i++)
        {
            temp[i] = array[i];
        }
        for(i = i, j = 0; i < newSize, j < v.size; i++, j++)
        {
            temp[i] = v.array[j];
            vindex++;
        }

        delete[] array;
        array = temp;
        size = newSize;

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

        vindex--;

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

        vindex--;
        
        for(int i = location; i < vindex; i++)
        {
            array[i] = array[i + 1];
        }

        return temp;
    }

    int SearchPop(int val)
    {
        ISEMPTY

        int temp = 0;
        int i = 0;

        for(i = 0; i < vindex; i++)
        {
            if (val == array[i])
            {
                temp = i;
                vindex--;
                break;
            }
        }
        if (temp)
        {
            for(i = i; i < vindex; i++)
            {
                array[i] = array[i + 1];
            }      
        }

        return temp;
    }

    void Print(int num = 0)
    {
        int to;

        to = num ? num : vindex;

        cout << "[";
        for(int i = 0; i < to; i++)
        {
            
            cout << array[i] << ", ";
        }

        cout <<  "]" << endl;
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
    int arr[] = {1};
    int arr2[] = {2, 3};
    Vector V(arr, size(arr));

    Vector V2(arr2, size(arr2));

    V.Print();
    V2.Print();
    V.PushRear(V2);
    V.Print();

    return(0);
}