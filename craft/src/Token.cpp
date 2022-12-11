#include "Token.hpp"
#include <string>
string Token::getText()
{
    return this->text;
}
void Token::setText(string text_)
{
    this->text = text_;
}

void Token::reset()
{
    this->text = "";
}
void Token::setType(TokenType type_)
{
    this->type = type_;
}

TokenType Token::getType()
{
    return this->type;
}