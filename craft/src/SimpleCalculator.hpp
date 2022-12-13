#include <iostream>
#include "TokenReader.hpp"
#include "ASTNode.hpp"
using namespace std;

/**
 * 实现一个计算器，但计算的结合性是有问题的。因为它使用了下面的语法规则：
 *
 * additive -> multiplicative | multiplicative + additive
 * multiplicative -> primary | primary * multiplicative    //感谢@Void_seT，原来写成+号了，写错了。
 *
 * 递归项在右边，会自然的对应右结合。我们真正需要的是左结合。
 */
class SimpleCalculator
{
private:
    TokenReader tokens;
    ASTNode *root;
    ASTNode *additive();
    ASTNode *multiplicative();
    ASTNode *primary();
    void dumAST(ASTNode *node, string indent); // print AST

public:
    void calculate(string code); // program entrance
    void parse(string code);     // build AST
    void print();                // print AST
    int evaluate(ASTNode *node); // evaluate AST
};