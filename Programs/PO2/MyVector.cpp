/*****************************************************************************
*                    
*  Author:           Calvin Walmer
*  Title:            Program 2 - My Vector Class 2
*  Course:           2143
*  Semester:         Fall 2022
* 
*  Description:
*        Uses a singly linked list as the backend for an STL like "vector" 
*        class definition. Written by Prof Griffin. Modified by Calvin Walmer
* 
*  Usage:
*        Use it like a linked list now. More like a vector next program
* 
*  Files:   MyVector.cpp : Implementation of features
            source.cpp : Driver code for class
*****************************************************************************/

#include <fstream>
#include <iostream>
#include <string>

#define INF 1000000000  // infinity

using namespace std;

// Node for our linked list
struct Node {
    int data;

    Node* next;

    Node(int x) {
        data = x;
        next = NULL;
    }
};

class MyVector {
private:
    Node*           head;  // base pointer of list
    Node*           tail;
    int             size;
    static ofstream fout;
    string          fileName;
    bool            sorted;

    /**
     * @brief Private version of inOrder push. 
     * 
     * @param x 
     */
    void _inorderPush(int x) {
        Node* tempPtr = new Node(x);  // allocate new node
        Node* prev = head;            // get previous and next pointers
        Node* curr = head;

        while (curr->data > x) {  // loop to find proper location
            prev = curr;
            curr = curr->next;
        }

        tempPtr->next = prev->next;  // add new node in its proper position
        prev->next = tempPtr;

        size++;  // add to size :)
    }

public:
    /**
     * @brief Default constructor 
     * 
     */
    MyVector() {
        init();
    }

    /**
     * @brief Overloaded Constructor 
     * 
     * @param int   *A - pointer to array 
     * @param int   aSize - size of array
     */
    MyVector(int A[], int aSize) {
        init();

        for (int i = 0; i < aSize; i++) {
            pushRear(A[i]);
        }
    }

    /**
     * @brief Overloaded Constructor 
     * 
     * @param string FileName - file to open and read
     * 
     * Assumes infile will contain numbers only delimited by spaces or 
     * new lines.
     */
    MyVector(string FileName) {
        init();

        ifstream fin;
        int      x = 0;

        fin.open(FileName);
        while (!fin.eof()) {
            fin >> x;
            pushRear(x);
        }
    }

    /**
     * @brief Copy Constructor 
     * 
     * @param MyVector &other 
     */
    MyVector(const MyVector& other) {
        init();

        Node* temp = other.head;

        while (temp) {
            pushRear(temp->data);
            temp = temp->next;
        }
    }

    /**
     * @brief - Initialize the data members so we don't
     *      have duplicate lines in each constructor.
     * 
     */
    void init() {
        head = tail = NULL;
        fileName = "";
        size = 0;
        sorted = 0;
    }


    /**
     * @brief Public version of inOrder push.
     * 
     * @param x 
     */
    void inorderPush(int x) {
        if (!sorted) {
            sortList();
        }

        if (!head) {
            pushFront(x);  // call push front for empty list (or pushRear would work)
        } else if (x < head->data) {
            pushFront(x);  // call push front if x is less than head
        } else if (x > tail->data) {
            pushRear(x);  // call push rear if x > tail
        } else {
            _inorderPush(x);  // call private version of push in order
        }
    }

    /**
     * @brief Sort the current values in the linked list.
     * 
     * @returns None
     */
    void sortList() {
        Node* newFront = head;
        while (newFront->next) {
            Node* thisest = newFront;
            Node* current = newFront;
            int   minimum = INF;
            while (current) {
                if (current->data < minimum) {
                    thisest = current;
                    minimum = current->data;
                }
                current = current->next;
            }
            thisest->data = newFront->data;
            newFront->data = minimum;
            newFront = newFront->next;
        }
        sorted = true;
    }

    /**
     * @brief Add value to front of list.
     * 
     * @param x 
     */
    void pushFront(int x) {
        Node* tempPtr = new Node(x);

        // empty list make head and tail
        // point to new value
        if (!head) {
            head = tail = tempPtr;
            // otherwise adjust head pointer
        } else {
            tempPtr->next = head;
            head = tempPtr;
        }
        size++;
    }

    /**
     * @brief This method loads values from 'other' list in 'this' list.
     *          It loads an array first so we can process the values in
     *          reverse so they end up on 'this' list in the proper order.
     *          If we didn't use the array, we would reverse the values
     *          from the 'other' list.
     * 
     * @depends - Uses `pushFront(int)`
     * @param MyVector& other 
     * @return None
     */
    void pushFront(const MyVector& other) {
        Node* otherPtr = other.head;           // get copy of other lists head
        int*  tempData = new int[other.size];  // allocate memory to hold values

        // load other list into array
        int i = 0;
        while (otherPtr) {
            tempData[i] = otherPtr->data;
            otherPtr = otherPtr->next;
            ++i;
        }

        // process list in reverse in order to keep them
        // in their original order.
        for (int i = other.size - 1; i >= 0; i--) {
            pushFront(tempData[i]);
        }
    }

    /**
     * @brief -  Add 'other' list's values to end of 'this' list.
     * @note - Uses `pushRear(int)`
     * @param MyVector& other 
     * @return None
     */
    void pushRear(const MyVector& other) {
        Node* otherPtr = other.head;  // get copy of other lists head

        while (otherPtr) {  // traverse and add
            pushRear(otherPtr->data);
            otherPtr = otherPtr->next;
        }
    }

    /**
     * @brief Push value onto list at soecified position, if it exists.
     * 
     * @param int i - location index 
     * @param inr x - value to add 
     * @return bool - true add successful / false add failed 
     */
    bool pushAt(int i, int x) {
        if(i >= size){
            return false;
        }
        
        Node* tempPtr = new Node(x);  // allocate new node
        Node* prev = head;            // get previous and next pointers
        Node* curr = head;

        while (i>0) {  // loop to find proper location
            prev = curr;
            curr = curr->next;
            i--;
        }

        tempPtr->next = prev->next;  // add new node in its proper position
        prev->next = tempPtr;

        size++;  // add to size :)
        return true;
    }

    /**
     * @brief - Add value to rear of list
     * 
     * @param int x - value to be added 
     * @return None
     */
    void pushRear(int x) {
        Node* tempPtr = new Node(x);

        if (!head) {
            head = tail = tempPtr;

        } else {
            tail->next = tempPtr;
            tail = tempPtr;
        }
        size++;  // add to size of list
    }

    friend ostream& operator<<(ostream& os, const MyVector& rhs) {
        Node* temp = rhs.head;  // temp pointer copies head

        os << "[";
        while (temp) {  // this loops until temp is NULL
                        // same as `while(temp != NULL)`

            os << temp->data;  // print data from Node
            if (temp->next) {
                os << ", ";
            }
            temp = temp->next;  // move to next Node
        }
        os << "]";
        return os;
    }



    /**
     * Public : operator<<
     * 
     * Description:
     *      Overloads the << operator to be used with an out file stream.
     * 
     * Params:
     *      - ofstream& : reference to the out stream that is being accessed
     *      - const MyVector& : reference to the vector that is to be printed.
     * 
     * Returns:
     *      - ofstream& : the full content of the vector
     */
    friend ofstream& operator<<(ofstream& os, const MyVector& rhs) 
    {
    Node* temp = rhs.head;  // temp pointer copies head

    os << "[";
    while (temp) {  // this loops until temp is NULL
                    // same as `while(temp != NULL)`

        os << temp->data;  // print data from Node
        if (temp->next) {
            os << ", ";
        }
        temp = temp->next;  // move to next Node
    }
    os << "]";
    return os;
    }


    /**
     * Public : operator[]
     * 
     * Description:
     *      Overloads the [] operator so that the vector can be accessed in the
     *      same wya that an array can be accessed.
     * 
     * Params:
     *      - int : the location of the item that is to be returned
     * 
     * Returns:
     *      - int : the value at location, loc
     */
    int operator[](int loc)
    {
        Node* temp = this->head;
        int i= 0;

        if (loc > this-> size)
        {
            return(-1);
        }
        
        while(i < loc - 1)
        {
            temp = temp->next;
            i++;
        }

        i = temp->data;
        delete temp;

        return i;
    }

    /**
     * Public : operator+
     * 
     * Description:
     *      Overloads the + operator so that two vectors can easily be added.
     *      Adds items in the same location in both vectors and stores them in a new 
     *      vector.
     * 
     * Params:
     *      - const MyVector& : reference to the vector that is being added to THIS vector.
     * 
     * Returns:
     *      - MyVector : a vector that is the result of adding both vectors item-wise
     */
    MyVector operator+(const MyVector &rhs)
    {

        int i = 0;
        int tempSize = (this->size > rhs.size ? this->size : rhs.size);
        MyVector retVector;


        Node* thisTemp = this->head;
        Node* rhsTemp = rhs.head;

        while(i < tempSize)
        {

            if (thisTemp == nullptr & rhsTemp == nullptr)
            {
                retVector.pushRear(0);
            }
            else if (thisTemp == nullptr)
            {
                retVector.pushRear(rhsTemp->data);
                rhsTemp = rhsTemp->next;
            }
            else if (rhsTemp == nullptr)
            {
                retVector.pushRear(thisTemp->data);
                thisTemp = thisTemp->next;
            }
            else
            {
                retVector.pushRear(thisTemp->data + rhsTemp->data);
                thisTemp = thisTemp->next;
                rhsTemp = rhsTemp->next;
            }

            i++;
        }

        delete thisTemp, rhsTemp;

        return(retVector);

    }

    /**
     * Public : operator-
     * 
     * Description:
     *      Overloads the - operator so that two vectors can easily be subtracted from each other.
     *      Subtracts items in the same location in both vectors and stores them in a new 
     *      vector.
     * 
     * Params:
     *      - const MyVector& : reference to the vector that is being subtracted from THIS vector.
     * 
     * Returns:
     *      - MyVector : a vector that is the result of subtracting a second vector from this vector item-wise.
     */
    MyVector operator-(const MyVector &rhs)
    {

        int i = 0;
        int tempSize = (this->size > rhs.size ? this->size : rhs.size);
        MyVector retVector;


        Node* thisTemp = this->head;
        Node* rhsTemp = rhs.head;

        while(i < tempSize)
        {

            if (thisTemp == nullptr & rhsTemp == nullptr)
            {
                retVector.pushRear(0);
            }
            else if (thisTemp == nullptr)
            {
                retVector.pushRear(rhsTemp->data);
                rhsTemp = rhsTemp->next;
            }
            else if (rhsTemp == nullptr)
            {
                retVector.pushRear(thisTemp->data);
                thisTemp = thisTemp->next;
            }
            else
            {
                retVector.pushRear(thisTemp->data - rhsTemp->data);
                thisTemp = thisTemp->next;
                rhsTemp = rhsTemp->next;
            }

            i++;
        }

        delete thisTemp, rhsTemp;

        return(retVector);

    }

    /**
     * Public : operator*
     * 
     * Description:
     *      Overloads the * operator so that two vectors can easily be multiplied.
     *      Multiplies items in the same location in both vectors and stores them in a new 
     *      vector.
     * 
     * Params:
     *      - const MyVector& : reference to the vector that is being multiplied by THIS vector.
     * 
     * Returns:
     *      - MyVector : a vector that is the result of multiplying both vectors item-wise
     */
    MyVector operator*(const MyVector &rhs)
    {

        int i = 0;
        int tempSize = (this->size > rhs.size ? this->size : rhs.size);
        MyVector retVector;


        Node* thisTemp = this->head;
        Node* rhsTemp = rhs.head;

        while(i < tempSize)
        {

            if (thisTemp == nullptr & rhsTemp == nullptr)
            {
                retVector.pushRear(0);
            }
            else if (thisTemp == nullptr)
            {
                retVector.pushRear(rhsTemp->data);
                rhsTemp = rhsTemp->next;
            }
            else if (rhsTemp == nullptr)
            {
                retVector.pushRear(thisTemp->data);
                thisTemp = thisTemp->next;
            }
            else
            {
                retVector.pushRear(thisTemp->data * rhsTemp->data);
                thisTemp = thisTemp->next;
                rhsTemp = rhsTemp->next;
            }

            i++;
        }

        delete thisTemp, rhsTemp;

        return(retVector);

    }

    /**
     * Public : operator/
     * 
     * Description:
     *      Overloads the / operator so that two vectors can easily be divided by each other.
     *      Divides items in the same location in both vectors and stores them in a new 
     *      vector.
     * 
     * Params:
     *      - const MyVector& : reference to the vector that THIS vector is being divided by.
     * 
     * Returns:
     *      - MyVector : a vector that is the result of this vector being divided by a second vector item-wise
     */
    MyVector operator/(const MyVector &rhs)
    {

        int i = 0;
        int tempSize = (this->size > rhs.size ? this->size : rhs.size);
        MyVector retVector;


        Node* thisTemp = this->head;
        Node* rhsTemp = rhs.head;

        while(i < tempSize)
        {

            if (thisTemp == nullptr & rhsTemp == nullptr)
            {
                retVector.pushRear(0);
            }
            else if (thisTemp == nullptr)
            {
                retVector.pushRear(rhsTemp->data);
                rhsTemp = rhsTemp->next;
            }
            else if (rhsTemp == nullptr)
            {
                retVector.pushRear(thisTemp->data);
                thisTemp = thisTemp->next;
            }
            else
            {
                retVector.pushRear(thisTemp->data / rhsTemp->data);
                thisTemp = thisTemp->next;
                rhsTemp = rhsTemp->next;
            }

            i++;
        }

        delete thisTemp, rhsTemp;

        return(retVector);

    }

    /**
     * Public : operator+
     * 
     * Description:
     *      Overloads the == operator so that two vectors can easily be compared.
     *      Compares items in the same location in both vectors and returns true if the vectors
     *      contain all the same items.
     * 
     * Params:
     *      - const MyVector& : reference to the vector that is being compared to THIS vector.
     * 
     * Returns:
     *      - bool : true if both vectors contain the same items. false if the vectors contain different items.
     */
    bool operator==(const MyVector &rhs)
    {
        int i = 0;
        int tempSize = (this->size > rhs.size ? this->size : rhs.size);
        Node* thisTemp = this->head;
        Node* rhsTemp = rhs.head;

        while(i < tempSize)
        {

            if (thisTemp == nullptr & rhsTemp == nullptr)
            {
                return(true);
            }
            else if (thisTemp == nullptr)
            {
                return(false);
            }
            else if (rhsTemp == nullptr)
            {
                return(false);
            }
            else
            {
                thisTemp = thisTemp->next;
                rhsTemp = rhsTemp->next;
            }

            i++;
        }

        delete thisTemp, rhsTemp; 
        return(true);
    }

    /**
     * Public : operator=
     * 
     * Description:
     *      Overloads the = operator so that two vectors can easily be copied.
     *      Creates a deep copy of the vector instead of using a primitive copy constructor.
     * 
     * Params:
     *      - const MyVector& : reference to the vector that is being copied by THIS vector.
     * 
     * Returns:
     *      - MyVector : a vector that is the result of the copied vector.
     */
    MyVector operator=(const MyVector &rhs)
    {
        int* arr = new int[rhs.size];
        Node* temp = rhs.head;

        for(int i = 0; i < rhs.size; i++)
        {
            arr[i] = temp->data;
        }
        
        MyVector retVector(arr, rhs.size);
        retVector.sorted = rhs.sorted;
        delete[] arr;
        delete temp;

        return(retVector);
    }

    /**
     * @brief Destroy the My Vector object
     * 
     */
    ~MyVector() {
        Node* curr = head;
        Node* prev = head;

        while(curr){
            prev = curr;
            curr = curr->next;
            // cout << "deleting: " << prev->data << endl;
            delete prev;
        }
    }



};
