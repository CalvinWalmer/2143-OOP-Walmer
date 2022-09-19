#include <iostream>
#include <fstream>
#include <string>

#define ISFULL if(IsFull()){Resize();}
#define ISEMPTY if(IsEmpty()){cout << "Vector is empty. No values to pop!"; return 0;}

using namespace std;

struct Vector
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

    Vector(const Vector &v)
    {
        size = v.size;
        vindex = v.vindex;
        array = new int[v.size];

        for(int i = 0; i < vindex; i++)
        {
            array[i] = v.array[i];
        }
    }

    ~Vector()
    {
        array = nullptr;
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

    void pushFront(const Vector &v)
    {
        int newSize = vindex + v.vindex;
        int i, j;
        int* temp = new int[newSize];
        for (i = 0; i < v.vindex; i++)
        {
            temp[i] = v.array[i];
        }

        for(i = i, j = 0; i < newSize; i++, j++)
        {
            temp[i] = array[j];
        }
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

    void pushRear(const Vector &v)
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

        int temp = -1;
        int i = 0;

        for(i = 0; i < vindex; i++)
        {
            if (val == array[i])
            {
                temp = i + 1;
                vindex--;
                break;
            }
        }
        if (temp != -1)
        {
            for(i = i; i < vindex; i++)
            {
                array[i] = array[i + 1];
            }      
        }

        return temp;
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
        array = nullptr;
        delete[] array;
        array = tempArray;
    }

};


int main()
{

    return(0);
}