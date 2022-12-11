#ifndef TOKEN
#define TOKEN
#include <iostream>
#include "TokenType.hpp"
#include <string>
using namespace std;
using namespace Tokens;
class Token
{
private:
    TokenType type;
    string text;

public:
    TokenType getType();
    string getText();
    void setText(string text_);
    void setType(TokenType type_);
    void reset();
};
#endif