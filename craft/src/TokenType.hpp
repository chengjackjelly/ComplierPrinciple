#ifndef TOKENTYPE
#define TOKENTYPE
namespace Tokens
{
    enum TokenType
    {
        Plus,  // + 0
        Minus, // - 1
        Star,  // * 2
        Slash, // / 3

        GE, // >= 4
        GT, // > 5
        EQ, // == 6
        LE, // <= 7
        LT, // < 8

        SemiColon,  // ; 9
        LeftParen,  // ( 10
        RightParen, // ) 11

        Assignment, // = 12

        If,   // 13
        Else, // 14

        Int, // 15

        Identifier, // 标识符 16

        IntLiteral,   // 整型字面量 17
        StringLiteral // 字符串字面量 18
    };
}
#endif