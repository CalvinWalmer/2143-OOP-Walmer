### Program 2 - MyVector Class 2

### Calvin Walmer

## Description:

Using code from a previously written Vector class, this program creates a more robust MyVector class that includes some added functionality with the overloading of some C++ operators. The final working product is a class that can write to a file and can be edited with the use of operators such as +, -, *, and /.

## Files

|   #   | File            | Description                                        |
| :---: | --------------- | -------------------------------------------------- |
|   1   | source.cpp      | Main driver of the project. Sets up a test scenario|
|   2   | MyVector.cpp    | Implementation of the Vector Class. Includes all vector implementation|

## Insctructions

- Make sure to use #include "MyVector.cpp"
- Create an instance of MyVector and add some integers to it either with [] or using the PushBack or PushFront methods.
- Arithmetic operators are performed on each item in each array

- Example
    int a1[] = { 1, 2, 3, 4, 5 };
    int a2[] = { 10, 20, 30 };

    MyVector v1(a1,5);
    MyVector v2(a2,3);

    v1 = v1 + v2;

    cout << v1 << endl;
    // 11, 22, 33, 4, 5
