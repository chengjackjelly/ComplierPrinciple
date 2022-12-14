#include "SimpleParser.hpp"
#include <iostream>
using namespace std;

int main()
{
    SimpleParser test;
    test.parse("1*5+2*3;");
    test.print();
    cout << ">" << endl;
}
