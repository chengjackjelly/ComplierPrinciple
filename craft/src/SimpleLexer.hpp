
#ifndef SIMPLELEXER_H
#define SIMPLELEXER_H
#include <iostream>
#include <vector>
#include <string>
#include "Token.hpp"
using namespace std;
using namespace Tokens;
class SimpleLexer
{
private:
    vector<Token> tokens;
    Token token;
    string tokentext;
    enum DfaState
    {
        Initial,
        Id,
        IntLiteral,
        GT,
        GE,
        Id_int1,
        Id_int2,
        Id_int3,
        Plus,
        Minus,
        Star,
        Slash,
        SemiColon,
        Assignment,
        LeftParen,
        RightParen,
    };

public:
    vector<Token> &tokenize(string code);
    DfaState initToken(char ch);
    void tmp_printtokens()
    {
        vector<Token>::iterator it;
        for (it = tokens.begin(); it != tokens.end(); it++)
        {
            cout << it->getText() << " " << it->getType() << endl;
        }
    }
};
#endif