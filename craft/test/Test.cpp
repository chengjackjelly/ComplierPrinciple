#include "SimpleParser.hpp"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    SimpleParser test;
    // test.parse("t+4;");
    // test.prog();
    test.REPL(argc, argv);
}
