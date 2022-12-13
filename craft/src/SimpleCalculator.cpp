#include "SimpleCalculator.hpp"
#include <exception>
#include <assert.h>

void SimpleCalculator::calculate(string code)
{
    parse(code);
    print();
    cout << "result is :" << endl;
    cout << evaluate(root) << endl;
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
int SimpleCalculator::evaluate(ASTNode *node)
{
    ASTNodeType type = node->getType();
    ASTNode *child1;
    ASTNode *child2;
    int left;
    int right;
    int result;
    switch (type)
    {
    case Programm:
        /* code */
        for (ASTNode *child : node->getChildren())
        {
            result = evaluate(child);
        }
        break;
    case Additive:
        child1 = node->getChildren()[0];
        child2 = node->getChildren()[1];
        left = evaluate(child1);
        right = evaluate(child2);
        if (node->getText() == "+")
        {
            result = left + right;
        }
        else if (node->getText() == "-")
        {
            result = left - right;
        }
        break;
    case Multiplicative:
        child1 = node->getChildren()[0];
        child2 = node->getChildren()[1];
        left = evaluate(child1);
        right = evaluate(child2);
        if (node->getText() == "*")
        {
            result = left * right;
        }
        else if (node->getText() == "/")
        {
            result = left / right;
        }
        break;
    case ASTNodeType::IntLiteral:
        result = atoi(node->getText().c_str()); // swith str to int
        break;
    default:
        break;
    }
    return result;
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
        if (tmp.getType() == TokenType::Plus || tmp.getType() == TokenType::Minus)
        {
            tokens.read();
            ASTNode *child2 = this->additive();
            if (child2->getType() != ASTNodeType::Undefined)
            {
                node = new ASTNode(ASTNodeType::Additive, tmp.getText());
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
        if (tmp.getType() == TokenType::Star || tmp.getType() == TokenType::Slash)
        {
            tokens.read();
            ASTNode *child2 = this->multiplicative();
            if (child2->getType() != ASTNodeType::Undefined)
            {
                node = new ASTNode(ASTNodeType::Multiplicative, tmp.getText());
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
        else if (tmp.getType() == TokenType::LeftParen)
        {
            tokens.read();
            node = additive();
            if (tokens.peek().getType() == TokenType::RightParen)
            {
                tokens.read();
            }
            else
            {
                throw "expecting a right paren";
            }
        }
        else
        {
            // TODO *()*
            throw "unexpecting character";
        }
    }
    return node;
}