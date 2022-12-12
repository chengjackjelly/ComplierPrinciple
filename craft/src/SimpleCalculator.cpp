#include "SimpleCalculator.hpp"
#include <exception>
#include <assert.h>

void SimpleCalculator::calculate(string code)
{
}
void SimpleCalculator::parse(string code)
{
    SimpleLexer lexer;
    tokens = TokenReader(lexer.tokenize(code));
    root = new ASTNode(ASTNodeType::Programm, "calculator");
    ASTNode *child = this->additive();
    root->addChild(child);
}
void SimpleCalculator::print()
{
    this->dumAST(this->root, " ");
}
void SimpleCalculator::dumAST(ASTNode *node, string indent)
{
    if (node->getType() != ASTNodeType::Undefined)
    {
        ASTNodeType type = node->getType();
        cout << indent << type << " " << node->getText() << endl;
        for (ASTNode *child : node->getChildren())
        {
            dumAST(child, indent + "\t");
        }
    }
}
ASTNode *SimpleCalculator::additive()
{
    ASTNode *node = this->multiplicative();
    ASTNode *child1 = node;
    Token tmp = tokens.peek();
    if (child1->getType() != ASTNodeType::Undefined || tmp.getType() != TokenType::Undefined)
    {
        if (tmp.getType() == TokenType::Plus)
        {
            tokens.read();
            ASTNode *child2 = this->additive();
            if (child2->getType() != ASTNodeType::Undefined)
            {
                node = new ASTNode(ASTNodeType::Additive, "additive");
                node->addChild(child1);
                node->addChild(child2);
            }
            else
            {
                throw "invalid additive expression";
            }
        }
    }

    return node;
}
ASTNode *SimpleCalculator::multiplicative()
{
    ASTNode *node = this->primary();
    ASTNode *child1 = node;
    Token tmp = tokens.peek();
    if (child1->getType() != ASTNodeType::Undefined || tmp.getType() != TokenType::Undefined)
    {
        if (tmp.getType() == TokenType::Star)
        {
            tokens.read();
            ASTNode *child2 = this->multiplicative();
            if (child2->getType() != ASTNodeType::Undefined)
            {
                node = new ASTNode(ASTNodeType::Multiplicative, "multiplicative");
                node->addChild(child1);
                node->addChild(child2);
            }
            else
            {
                throw "invalid multiplicative expression";
            }
        }
    }

    return node;
}
ASTNode *SimpleCalculator::primary()
{
    ASTNode *node;
    Token tmp = tokens.peek();
    if (tmp.getType() != TokenType::Undefined)
    {
        if (tmp.getType() == TokenType::IntLiteral)
        {
            tokens.read();
            node = new ASTNode(ASTNodeType::IntLiteral, tmp.getText());
        }
        else if (tmp.getType() == TokenType::Identifier)
        {
            tokens.read();
            node = new ASTNode(ASTNodeType::Identifier, tmp.getText());
        }
        else
        {
            // TODO *()*
            throw "unexpecting character";
        }
    }
    return node;
}