#ifndef DFASTATE
#define DFASTATE
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
};
#endif