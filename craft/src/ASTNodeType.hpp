#ifndef ASTNODETYPE
#define ASTNODETYPE
namespace ASTNodes
{
    enum ASTNodeType
    {
        Programm, // 程序入口，根节点0

        IntDeclaration, // 整型变量声明1
        ExpressionStmt, // 表达式语句，即表达式后面跟个分号2
        AssignmentStmt, // 赋值语句3

        Primary,        // 基础表达式4
        Multiplicative, // 乘法表达式5
        Additive,       // 加法表达式6

        Identifier, // 标识符7
        IntLiteral, // 整型字面量8
        Undefined,  // 9
    };
}
#endif