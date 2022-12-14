#include <iostream>
#include "TokenReader.hpp"
#include "ASTNode.hpp"
using namespace std;

/**
 * 一个简单的语法解析器。
 * 能够解析简单的表达式、变量声明和初始化语句、赋值语句。
 * 它支持的语法规则为：
 *
 * programm -> intDeclare | expressionStatement | assignmentStatement
 * intDeclare -> 'int' Id ( = additive) ';'
 * expressionStatement -> addtive ';'
 * assignmentStatement -> Id = additive';'
 * addtive -> multiplicative ( (+ | -) multiplicative)*
 * multiplicative -> primary ( (* | /) primary)*
 * primary -> IntLiteral | Id | (additive)
 */
class SimpleParser
{
private:
    TokenReader tokens;
    ASTNode *root;
    ASTNode *additive();
    ASTNode *multiplicative();
    ASTNode *primary();
    ASTNode *intDeclare();
    ASTNode *expressionStatement();
    ASTNode *assignmentStatement();
    void dumAST(ASTNode *node, string indent);

public:
    void parse(string code); // build AST
    void print()
    {
        this->dumAST(this->root, " ");
    }
};