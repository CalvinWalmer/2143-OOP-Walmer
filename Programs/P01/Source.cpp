
/*****************************************************************************
*                    
*  Author:           Calvin Walmer
*  Email:            calvinw@calvinwalmer.com
*  Label:            P01
*  Title:            Vector Class
*  Course:           CMPS 2143
*  Semester:         Fall 2022
* 
*  Description:
*        Program implements a dynamically sized array in the form of the class
*        Vector. Includes methods to push and pop from the list as well as a search method.
        Members can be pushed or popped from either side of the list.
* 
*  Usage:
*        Instantiate a vector in main and then use its pop methods to add items. Use the pop
        functions to remove items.
* 
*  Files:            Source.cpp             : Driver code
                    (Optional) input.dat    : Optional user input
*****************************************************************************/
#include <iostream>
#include <fstream>
#include <string>

#define ISFULL if(IsFull()){Resize();}
#define ISEMPTY if(IsEmpty()){cout << "Vector is empty. No values to pop!"; return 0;}

using namespace std;

/**
 * Vector
 * 
 * Description:
 *      Class implements a dynamically allocated array capable of resizing
 *      and processing changes to items anywhere within the array.
 * 
 * Public Methods:
 *                  Vector()
 *                  Vector(int _size)
 *                  Vector(int *A, int _size)
 *                  Vector(string filename)
 *                  Vector(const Vector &v)
 *                  ~Vector()
 *      void        pushFront(int val)
 *      void        pushFront(const Vector &v)
 *      void        pushRear(int val)
 *      void        pushRear(const Vector &v)
 *      void        pushAt(int location, int val)
 *      int         popFront()
 *      int         popRear()
 *      int         popAt(int location)
 *      int         find(int val)
 *      void        print(int num = 0)
 * 
 * 
 * 
 * 
 * Private Methods:
 *      bool        IsFull()
 *      bool        IsEmpty()
 *      void        Resize()
 * 
 * Usage: 
 *      Vector v1;
 *      v1.pushRear(25);
 *      v1.pushFront(65);
 *      v1.pushFront(34);
 *      cout << v1.Pop << endl;
 *      v1.print()
 *      
 */

class Vector
{
    int* array = nullptr;
    int vindex = 0;
    int size = 0;

public:
   //Constructors
    Vector()
    {
        array = new int[10]; //Defaule size of 10
        vindex = 0;
        size = 10;
    }

    Vector(int _size)
    {
        array = new int[size]; //Allowing user to declare a size
        vindex = 0;
        size = _size;
    }

    Vector(int *A, int _size)
    {
        array = new int[_size];
        vindex = 0;
        size = _size;

        for(int i = 0; i < _size; i++) //Looping to array to input values into this array
        {
            array[i] = A[i];
            vindex++;
        }
    }

    Vector(string fileName)
    {
        ifstream inpf; //input stream
        int temp;

        array = new int[10];

        vindex = 0;
        size = 10;

        inpf.open(fileName);

        if (!inpf) //if file was not found
        {
            cout << "File not found!" << endl;
            exit;
        }

        while (!inpf.eof()) //while not empty
        {
            inpf >> temp;
            this->pushRear(temp);
        }

        inpf.close();
    }

    Vector(const Vector &v) //Deep Copy Constructor
    {   
        size = v.size;
        vindex = v.vindex;
        array = new int[v.size];

        for(int i = 0; i < vindex; i++) //looping through other vector's array
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
    /**
     * Public : pushFront
     * 
     * Description:
     *      Adds a single integer value to the front of the internal array.
     * 
     * Params:
     *      int     :  the value to be added to the array.
     * 
     * Returns:
     *      nothing
     */
    void pushFront(int val)
    {
        ISFULL //check if full, then resize

        for(int i = vindex; i > 0; i--) //increases array items' index by 1
        {
            array[i] = array[i - 1];
        }

        array[0] = val;

        vindex++;
    }
    /**
     * Public : pushFront
     * 
     * Description:
     *      Adds another vector to the front of this vector
     * 
     * Params:
     *     const Vector : a second vector, passed by reference, that will be appended.
     * Returns:
     *      nothing
     */
    void pushFront(const Vector &v)
    {
        int newSize = vindex + v.vindex; //new size is the number of items in both arrays
        int i, j;
        int* temp = new int[newSize];
        for (i = 0; i < v.vindex; i++) //looping through other array
        {
            temp[i] = v.array[i];
        }

        for(i = i, j = 0; i < newSize; i++, j++) //looping though this array
        {
            temp[i] = array[j];
        }
        array = nullptr; //avoiding memory errors
        delete[] array;
        array = temp; //setting internal array to the temp array
        size = newSize;
        vindex = newSize;
        
    }
    /**
     * Public : pushRear
     * 
     * Description:
     *      Adds a single integer value to the end of the internal array.
     * 
     * Params:
     *      int     :  the value to be added to the array.
     * 
     * Returns:
     *      nothing
     */
    void pushRear(int val)
    {
        ISFULL

        array[vindex] = val;

        vindex++;
    }
    /**
     * Public : pushFront
     * 
     * Description:
     *      Adds another vector to the end of this vector
     * 
     * Params:
     *     const Vector : a second vector, passed by reference, that will be appended.
     * Returns:
     *      nothing
     */
    void pushRear(const Vector &v)
    {
        int newSize = vindex + v.vindex;
        int i, j;
        int* temp = new int[newSize];

        for (i = 0; i < vindex; i++) //looping though this array first
        {
            temp[i] = array[i];
        }
        for(i = i, j = 0; i < newSize, j < v.size; i++, j++) //then other array
        {
            temp[i] = v.array[j];
        }


        array = nullptr; //avoiding memory errors
        delete[] array;
        array = temp;
        size = newSize;
        vindex = newSize;
    }
    /**
     * Public : pushRear
     * 
     * Description:
     *      Adds a single integer value to a specified position in the internal array.
     * 
     * Params:
     *      int     :  the index of where the value will be added in the array.
     *      int     :  the value to be added to the array.
     * 
     * Returns:
     *      nothing
     */
    void pushAt(int location, int val)
    {
        ISFULL

        for(int i = vindex; i > location; i--) //moving array items' index up by 1
        {
            array[i] = array[i - 1];
        }
        
        array[location] = val;

        vindex++;
    }

    //POP METHODS
    /**
     * Public : popFront
     * 
     * Description:
     *      Removes a single integer value from the front of the internal array.
     * 
     * Params:
     *      nothing
     * 
     * Returns:
     *      int     :  the removed element
     */
    int popFront()
    {
        ISEMPTY

        int temp = array[0]; //setting to the front

        vindex--;

        for(int i = 0; i < vindex; i++) //decreasing items index by 1
        {
            array[i] = array[i + 1];
        }

        return(temp);
    }
    /**
     * Public : popRear
     * 
     * Description:
     *      Removes a single integer value from the end of the internal array.
     * 
     * Params:
     *      nothing
     * 
     * Returns:
     *      int     :  the removed element
     */
    int popRear()
    {
        ISEMPTY
        vindex--;
        return(array[vindex]);
    }
    /**
     * Public : popAt
     * 
     * Description:
     *      Removes a single integer value from the a specified position in the internal array.
     * 
     * Params:
     *      int     :  the index location of the element to be removed
     * 
     * Returns:
     *      int     :  the removed element
     */
    int popAt(int location)
    {
        ISEMPTY

        int temp = array[location-1]; //return value

        vindex--;
        
        for(int i = location-1; i < vindex; i++)//increasing items' index by 1
        {
            array[i] = array[i + 1];
        }

        return temp;
    }
    /**
     * Public : find
     * 
     * Description:
     *      Searches for, and the removes a single value from the internal array.
     * 
     * Params:
     *      int     :  the value of the element to be removed
     * 
     * Returns:
     *      int     :  the removed element
     */
    int find(int val)
    {
        ISEMPTY

        int temp = -1; //default return value
        int i = 0;

        for(i = 0; i < vindex; i++) //loops through this vector's array to see if item is present
        {
            if (val == array[i])
            {
                temp = i + 1;
                vindex--;
                break; //no need to loop after item is found
            }
        }
        if (temp != -1) //if item was found
        {
            for(i = i; i < vindex; i++)//increase items' index by 1
            {
                array[i] = array[i + 1];
            }      
        }

        return temp;
    }
    /**
     * Public : print
     * 
     * Description:
     *      Prints out the internal array.
     * 
     * Params:
     *      Optional int     :  the index of the location you want to print up to.
     * 
     * Returns:
     *      nothing
     */
    void print(int num = 0)
    {
        int to;
        ofstream opf;

        opf.open("test.out" , ios_base::app); //append mode

        to = num ? num : vindex; //if number is not vindex set the loop control to the user defined value

        cout << "[";
        opf << "[";
        for(int i = 0; i < to; i++) //looping through internal array
        {
            
            cout << array[i];
            opf << array[i];
            if(i != to -1){
                cout << ", ";
                opf << ", ";
            }
        }

        cout <<  "]" << endl;
        opf << "]" << endl;
    }

    private:
    /**
     * Private : IsFull
     * 
     * Description:
     *      Checks if the internal array is full
     * 
     * Params:
     *      nothing
     * 
     * Returns:
     *      bool     :  true if full, false if not full
     */
    bool IsFull()
    {
        return vindex < size ? false : true;
    }
    /**
     * Private : IsEmpty
     * 
     * Description:
     *      Checks if the internal array is empty
     * 
     * Params:
     *      nothing
     * 
     * Returns:
     *      bool     :  true if empty, false if not empty
     */
    bool IsEmpty()
    {
        return vindex == 0;
    }
    /**
     * Private : Resize
     * 
     * Description:
     *      Resizes the internal array by allocating twice as much memory as the previous array.
     * 
     * Params:
     *      nothing
     * 
     * Returns:
     *      nothing
     */
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

ofstream opf; //output file stream 
opf.open("test.out");
opf << "Calvin Walmer\nSeptember 19, 2022\nFall2143\n"; //Headers for output file and console
opf.close();
cout << "Calvin Walmer\nSeptember 19, 2022\nFall2143\n";
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
// [9, 11, 25, 33, 47, 51, 63]
cout<<x<<endl;
// 27

x = v2.find(51);
cout<<x<<endl;
// 5

x = v2.find(99);
cout<<x<<endl;
// -1

Vector v3(v1);
v3.print();
// [18, 20, 25, 9, 11, 25, 27, 33]

v3.pushFront(v2);
v3.print();
//[9, 11, 25, 33, 47, 51, 63, 18, 20, 25, 9, 11, 25, 27, 33]

Vector v4("input.dat");
v4.pushRear(v3);
v4.print();
// [56, 61, 97, 66, 83, 25, 26, 11, 53, 49, 62, 18, 10, 18, 14, 3, 4, 23, 18, 24, 26, 27, 54, 14, 12, 45, 65, 98, 56, 97, 15, 84, 98, 9, 11, 25, 33, 47, 51, 63, 18, 20, 25, 9, 11, 25, 27, 33]
    return(0);
}