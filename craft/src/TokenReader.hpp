#ifndef TOKENREADER
#define TOKENREADER
#include <iostream>
#include "Token.hpp"
#include "SimpleLexer.hpp"
#include <string>
#include <vector>
using namespace std;
using namespace Tokens;
class TokenReader
{
private:
    vector<Token> tokens;
    int pos;

public:
    TokenReader()
    {
        pos = 0;
    }
    TokenReader(vector<Token> tokens_)
    {
        this->tokens = tokens_;
        pos = 0;
    }
    Token read()
    {
        if (pos < tokens.size())
        {
            return tokens[pos++];
        }
        return Token();
    }
    Token peek()
    {
        if (pos < tokens.size())
        {
            return tokens[pos];
        }
        return Token();
    }
    void unread()
    {
        if (pos > 0)
        {
            pos--;
        }
    }
    int getPosition()
    {
        return pos;
    }
    void setPosition(int position)
    {
        if (position >= 0 && position < tokens.size())
        {
            pos = position;
        }
    }
};
#endif