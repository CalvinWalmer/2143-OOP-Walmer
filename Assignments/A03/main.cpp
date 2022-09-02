
/*****************************************************************************
*                    
*  Author:           Calvin Walmer
*  Email:            calvinw@calvinwalmer.com
*  Label:            A03
*  Title:            Basic Project Organization
*  Course:           CMPS 2143
*  Semester:         Fall 2022
* 
*  Description:
*        This program implements a queue by way of a dynamically declared array
*        whose size can be defined by the user. The program also overloads the ostream
*        so that the entire queue can be printed without having to reach into the memory.
*        The queue can be accessed by "Pushing" and "Popping" elements.
* 
*  Usage:
*           After instantiating a CircularArrayQue and use the Push method to add elements to the
*           queue. The Pop method can be used to remove elements from the queue.
* 
*  Files:            main.cpp
*****************************************************************************/

#include <iostream>

using namespace std;

/**
 * Class CircularArrayQue:
 * 
 * Description:
 *      This class creates a queue array of a user defined size.
 * 
 * Public Methods:
 *      -       CircularArrayQue()
 *      -       CircularArrayQue(int size)
 *      - void  Push(int item)
 *      - int   Pop()
 * 
 * Private Methods:
 *      - void  init(int size)
 *      - bool full()
 * 
 * Usage: 
 * 
 *      CircularArrayQue Q(size);           // Creates an instance of CircularArrayQue
 *      
 *      Q.Push(int item);                   // Adds an item to the queue
 *
 *      Q.Pop();                            // Removes an item according to FIFO
 *
 *      cout << Q;                          // Prints the entire queue to console
 *      
 */
class CircularArrayQue {
private:
    int *Container;         // pointer to the first item in the queue
    int Front;
    int Rear;
    int QueSize;            // total elements in the queue
    int CurrentSize;        // filled elements in the queue
     /**
     * Private : init
     * 
     * Description:
     *      Sets up the underlying mechanics of the queue
     * 
     * Params:
     *      - [int] size - user defined size of the array
     * 
     * Returns:
     *      - nothing
     */
    void init(int size = 0) {
        Front = Rear = CurrentSize = 0;     // setting all flags to the first index
        QueSize = size;                     // setting the size from user
    }

     /**
     * Private : Full
     * 
     * Description:
     *      Provides a flag if the queue is full of items
     * 
     * Params:
     *      - nothing
     * 
     * Returns:
     *      - [bool] - true if each element in the queue has an int; false if not.
     */
    bool Full() {
        return CurrentSize == QueSize; // if filled elements = total elements, the queue is full
    }

public:
     /**
     * Public : CircularArrayQue
     * 
     * Description:
     *      Default constructor for the class. Sets the queue size to 10 elements.
     * 
     * Params:
     *      - nothing
     * 
     * Returns:
     *      - nothing
     */
    CircularArrayQue() {
        Container = new int[10];
        init(10);
    }
    
     /**
     * Public : CircularArrayQue
     * 
     * Description:
     *      Constructor for the class. Sets the queue size to a user defined integer size.
     * 
     * Params:
     *      - [int] size - The number of elements the user wants there to be in the queue
     * 
     * Returns:
     *      - nothing
     */
    CircularArrayQue(int size) {
        Container = new int[size];
        init(size);
    }

     /**
     * Public : Push
     * 
     * Description:
     *      Adds an integer element to the queue if the queue is not already full.
     * 
     * Params:
     *      - [int] item - The integer that the user wants to store in the queue
     * 
     * Returns:
     *      - nothing
     */
    void Push(int item) {
        if (!Full()) {                      //if the queue is not full
            Container[Rear] = item;         //add the item to the back of the queue
            Rear = (Rear + 1) % QueSize;    //increases rear and keeps value within size constraint
            CurrentSize++;                  //increase number of filled elements
        } else {                            //if queue is not full
            cout << "FULL!!!!" << endl;
        }
    }
    
     /**
     * Public : Push
     * 
     * Description:
     *      Removes and element from the queue according to FIFO
     * 
     * Params:
     *      - nothing
     * 
     * Returns:
     *      - [int] temp - The integer value that was taken away from the queue
     */
    int Pop() {
        int temp = Container[Front];    // set temp to the first item in the queue
        Front = (Front + 1) % QueSize;  // increases front and keeps value within size constraint
        CurrentSize--;                  // decrease number of filled elements
        return temp;
    }
    friend ostream &operator<<(ostream &os, const CircularArrayQue &other);
};

ostream &operator<<(ostream &os, const CircularArrayQue &other) {

    for (int i = other.Front; i < other.CurrentSize; i = (i + 1) % other.QueSize) {
        os << other.Container[i] << " ";
    }
    os << endl;
    return os;
}

/**
 * Main Driver
 * 
 * For this program, the main driver was used to test the CircularArrayQue class
 * 
 */
int main() {
    CircularArrayQue C1(5);

    // C1.Push(34);
    // C1.Push(38);
    // C1.Push(44);
    // C1.Push(22);
    // C1.Push(99);
    // C1.Push(100);

    C1.Push(1);
    C1.Push(2);
    C1.Push(3);
    // C1.Push(6);
    // C1.Push(7);
    cout << C1 << endl;

    // C1.Push(1);
    // C1.Push(2);
    // C1.Push(3);

    cout << C1 << endl;
}
