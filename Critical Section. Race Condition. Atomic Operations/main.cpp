// Critical Section. Race Condition. Atomic Operations.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "first.hpp"
#include "second.hpp"

using namespace std;

int main()
{
    cout << "First task" << endl;
    first();
    cout << endl << endl;

    cout << "Second task" << endl;
    second();

    return 0;
}