#include "SimpleLexer.hpp"
#include <iostream>
using namespace std;

int main()
{
    SimpleLexer testcase;
    testcase.tokenize("int a = 4");
    testcase.tmp_printtokens();
}
