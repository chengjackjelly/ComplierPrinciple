#include "SimpleCalculator.hpp"
#include <iostream>
using namespace std;

int main()
{
    SimpleCalculator test;
    test.parse(" 2+5*4");
    test.print();
    cout << ">" << endl;
}
