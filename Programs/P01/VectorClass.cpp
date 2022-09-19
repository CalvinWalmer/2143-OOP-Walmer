#include <iostream>
#include <fstream>
#include <string>

#define ISFULL if(IsFull()){Resize();}
#define ISEMPTY if(IsEmpty()){cout << "Vector is empty. No values to pop!"; return 0;}

using namespace std;

class Vector
{
    int* array = nullptr;
    int vindex = 0;
    int size = 0;

public:
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

        if (!inpf)
        {
            cout << "File not found!" << endl;
            exit;
        }

        while (!inpf.eof())
        {
            inpf >> temp;
            this->pushRear(temp);
        }

        inpf.close();
    }

    ~Vector()
    {
        delete[] array;

    }

    //Push Methods
    void pushFront(int val)
    {
        ISFULL

        for(int i = vindex; i > 0; i--)
        {
            array[i] = array[i - 1];
        }

        array[0] = val;

        vindex++;
    }

    void pushFront(Vector &v)
    {
        int newSize = vindex + v.vindex;
        int i, j;
        int* temp = nullptr;
        cout << newSize << endl;
        cout << temp;
        temp = new int[newSize];
        cout << "Moo" << endl;
        for (i = 0; i < v.vindex; i++)
        {
            temp[i] = v.array[i];
        }

        for(i = i, j = 0; i < newSize; i++, j++)
        {
            temp[i] = array[j];
        }
        cout << "M" << endl;
        array = nullptr;
        delete[] array;
        array = temp;
        size = newSize;
        vindex = newSize;
        
    }

    void pushRear(int val)
    {
        ISFULL

        array[vindex] = val;

        vindex++;
    }

    void pushRear(Vector &v)
    {
        int newSize = vindex + v.vindex;
        int i, j;
        int* temp = new int[newSize];

        for (i = 0; i < vindex; i++)
        {
            temp[i] = array[i];
        }
        for(i = i, j = 0; i < newSize, j < v.size; i++, j++)
        {
            temp[i] = v.array[j];
        }


        array = nullptr;
        delete[] array;
        array = temp;
        size = newSize;
        vindex = newSize;
        


    }

    void pushAt(int location, int val)
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
    int popFront()
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

    int popRear()
    {
        ISEMPTY
        vindex--;
        return(array[vindex]);
    }

    int popAt(int location)
    {
        ISEMPTY

        int temp = array[location-1];

        vindex--;
        
        for(int i = location-1; i < vindex; i++)
        {
            array[i] = array[i + 1];
        }

        return temp;
    }

    int find(int val)
    {
        ISEMPTY

        int temp = -2;
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

        return temp + 1;
    }

    void print(int num = 0)
    {
        int to;

        to = num ? num : vindex;

        cout << "[";
        // cout << VIN=" << vindex << " SZ=" << size << "|";
        for(int i = 0; i < to; i++)
        {
            
            cout << array[i] << ", ";
        }

        cout <<  "]" << endl;
    }

    private:
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

int x = 0;

Vector v1;
v1.pushFront(18);
v1.pushFront(20);
v1.pushFront(25);
v1.pushRear(18);
v1.pushRear(20);
v1.pushRear(25);
v1.print();
// [25, 20, 18, 18, 20, 25]

int A[] = {11,25,33,47,51};
Vector v2(A,5);
v2.print();
// [11, 25, 33, 47, 51]

v2.pushFront(9);
//v2.inOrderPush(27);
v2.pushRear(63);
v2.print();
// [9, 11, 25, 33, 47, 51, 63]

v1.pushRear(v2);
v1.print();
// [25, 20, 18, 18, 20, 25, 9, 11, 25, 33, 47, 51, 63]

x = v1.popFront();
x = v1.popFront();
x = v1.popFront();
v1.print();
// [18, 20, 25, 9, 11, 25, 27, 33, 47, 51, 63]
cout<<x<<endl;
// 18

x = v1.popRear();
x = v1.popRear();
x = v1.popRear();
v1.print();
// [18, 20, 25, 9, 11, 25, 27, 33]
cout<<x<<endl;
// 47

x = v2.popAt(3);
v2.print();
// [9, 11, 33, 47, 51, 63]
cout<<x<<endl;
// 25

x = v2.find(51);
cout<<x<<endl;
// 5

x = v2.find(99);
cout<<x<<endl;
// -1

Vector v3(v1);
v3.print();
// [18, 20, 25, 9, 11, 25, 27, 33]

//v3.pushFront(v2);
v3.print();
//[9, 11, 25, 33, 47, 51, 63, 18, 20, 25, 9, 11, 25, 27, 33]

Vector v4("input.dat");
v4.pushRear(v3);
v4.print();
// [56, 61, 97, 66, 83, 25, 26, 11, 53, 49, 62, 18, 10, 18, 14, 3, 4, 23, 18, 24, 26, 27, 54, 14, 12, 45, 65, 98, 56, 97, 15, 84, 98, 9, 11, 25, 33, 47, 51, 63, 18, 20, 25, 9, 11, 25, 27, 33]

    return(0);
}