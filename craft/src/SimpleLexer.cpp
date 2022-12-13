#include "SimpleLexer.hpp"
#include <vector>

class StringBuffer
{
private:
    int pointer;
    string text;

public:
    StringBuffer(string text_)
    {
        text = text_;
        pointer = 0;
    }
    char read()
    {
        if (pointer >= 0 && pointer < text.length())
        {
            return text[pointer++];
        }
        else
        {
            return -1;
        }
    }
};
bool isAlpha(char ch)
{
    return ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z';
}
bool isDigit(char ch)
{
    return ch >= '0' && ch <= '9';
}
bool isBlank(char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n';
}

SimpleLexer::DfaState SimpleLexer::initToken(char ch)
{
    if (tokentext.length() > 0)
    {
        // save token
        token.setText(tokentext);
        tokens.push_back(token);

        // reset token
        tokentext = "";
        token.reset();
    }
    DfaState newState = DfaState::Initial;
    if (isAlpha(ch))
    {
        if (ch == 'i')
        {
            newState = DfaState::Id_int1;
        }
        else
        {
            newState = DfaState::Id; // 进入Id状态
        }
        token.setType(TokenType::Identifier);
        tokentext += ch;
    }
    else if (isDigit(ch))
    {
        newState = DfaState::IntLiteral;
        token.setType(TokenType::IntLiteral);
        tokentext += ch;
    }
    else if (ch == '>')
    {
        newState = DfaState::GT;
        token.setType(TokenType::GT);
        tokentext += ch;
    }
    else if (ch == '+')
    {
        newState = DfaState::Plus;
        token.setType(TokenType::Plus);
        tokentext += ch;
    }
    else if (ch == '-')
    {
        newState = DfaState::Minus;
        token.setType(TokenType::Minus);
        tokentext += ch;
    }
    else if (ch == '*')
    {
        newState = DfaState::Star;
        token.setType(TokenType::Star);
        tokentext += ch;
    }
    else if (ch == '/')
    {
        newState = DfaState::Slash;
        token.setType(TokenType::Slash);
        tokentext += ch;
    }
    else if (ch == '=')
    {
        newState = DfaState::Assignment;
        token.setType(TokenType::Assignment);
        tokentext += ch;
    }
    else if (ch == '(')
    {
        newState = DfaState::LeftParen;
        token.setType(TokenType::LeftParen);
        tokentext += ch;
    }
    else if (ch == ')')
    {
        newState = DfaState::RightParen;
        token.setType(TokenType::RightParen);
        tokentext += ch;
    }
    else if (isBlank(ch))
    {
        newState = DfaState::Initial;
    }
    else
    {
        cout << "sign " << ch << " can not be regonized." << endl;
        newState = DfaState::Initial;
    }
    return newState;
}
vector<Token> &SimpleLexer::tokenize(string code)
{
    DfaState state = DfaState::Initial;
    StringBuffer reader(code);
    int ich = 0;
    char ch = 0;
    while ((ich = reader.read()) != -1)
    {
        ch = (char)ich;
        switch (state)
        {
        case Initial:
            /* code */
            state = initToken(ch);
            break;
        case Id:
            if (isAlpha(ch) || isDigit(ch))
            {
                tokentext += ch;
            }
            else
            {
                state = initToken(ch);
            }
            break;
        case IntLiteral:
            if (isDigit(ch))
            {
                tokentext += ch;
            }
            else
            {
                state = initToken(ch);
            }
            break;
        case GT:
            if (ch == '=')
            {
                tokentext += ch;
                token.setType(TokenType::GE);
                state = DfaState::GE;
            }
            else
            {
                state = initToken(ch);
            }
            break;
        case GE:
        case Plus:
        case Minus:
        case Star:
        case Assignment:
        case LeftParen:
        case RightParen:
        case Slash:
            state = initToken(ch);
            break;
        case Id_int1:
            if (ch == 'n')
            {
                tokentext += ch;
                state = DfaState::Id_int2;
            }
            else
            {
                tokentext += ch;
                state = DfaState::Id;
            }
            break;
        case Id_int2:
            if (ch == 't')
            {
                tokentext += ch;
                state = DfaState::Id_int3;
            }
            else
            {
                tokentext += ch;
                state = DfaState::Id;
            }
            break;
        case Id_int3:
            if (isBlank(ch))
            {
                token.setType(TokenType::Int);
                state = initToken(ch);
            }
            else
            {
                tokentext += ch;
                state = DfaState::Id;
            }
            break;
        default:
            break;
        }
    }
    if (tokentext.length() > 0)
    {
        initToken(ch);
    }
    return tokens;
}