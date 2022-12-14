#include "SimpleParser.hpp"
#include <exception>
#include <assert.h>
void SimpleParser::parse(string code)
{
    SimpleLexer lexer;
    tokens = TokenReader(lexer.tokenize(code));
    root = new ASTNode(ASTNodeType::Programm, "parser");
    ASTNode *child;
    child = intDeclare();
    if (child->getType() == ASTNodeType::Undefined)
    {
        child = expressionStatement();
    }
    if (child->getType() == ASTNodeType::Undefined)
    {
        child = assignmentStatement();
    }
    if (child->getType() != ASTNodeType::Undefined)
    {
        root->addChild(child);
    }
    else
    {
        throw "unknow statement";
    }
}

/* intDeclare -> 'int' Id ( = additive) ';'*/
ASTNode *SimpleParser::intDeclare()
{
    ASTNode *node = new ASTNode();
    Token tmp = tokens.peek();
    if (tmp.getType() == TokenType::Int)
    {
        tokens.read();
        tmp = tokens.peek();
        if (tmp.getType() == TokenType::Identifier)
        {
            node = new ASTNode(ASTNodeType::IntDeclaration, tmp.getText());
            tokens.read();
            tmp = tokens.peek();
            if (tmp.getType() == TokenType::Assignment)
            {
                tokens.read();
                ASTNode *child = additive();
                if (child->getType() != ASTNodeType::Undefined)
                {
                    node->addChild(child);
                    tmp = tokens.peek();
                    if (tmp.getType() == TokenType::SemiColon)
                    {
                        tokens.read();
                    }
                    else
                    {
                        throw "expecting a semicolon ';'";
                    }
                }
                else
                {
                    throw "unknow statement after '=' ";
                }
            }
            else if (tmp.getType() == TokenType::SemiColon)
            {
                tokens.read();
            }
            else
            {
                throw "expecting a semicolon ';'";
            }
        }
        else
        {
            throw "variable name expected";
        }
    }

    return node;
}
/* expressionStatement -> addtive ';'*/
ASTNode *SimpleParser::expressionStatement()
{
    int start = tokens.getPosition();
    ASTNode *node = additive();
    if (node->getType() != ASTNodeType::Undefined)
    {
        Token tmp = tokens.peek();
        if (tmp.getType() != TokenType::SemiColon)
        {
            tokens.setPosition(start);
            node->reset();
        }
        else
        {
            tokens.read();
        }
    }

    return node;
}

/*assignmentStatement -> Id = additive';'*/
ASTNode *SimpleParser::assignmentStatement()
{
    ASTNode *node = new ASTNode();
    Token tmp = tokens.peek();
    if (tmp.getType() == TokenType::Identifier)
    {
        node = new ASTNode(ASTNodeType::AssignmentStmt, tmp.getText());
        tokens.read();
        tmp = tokens.peek();
        if (tmp.getType() == TokenType::Assignment)
        {
            tokens.read();
            ASTNode *child = additive();
            if (child->getType() == ASTNodeType::Undefined)
            {
                throw "expecting a expression after '='";
            }
            else
            {
                node->addChild(child);
            }
        }
        else
        {
            tokens.unread();
            node->reset();
        }
    }
    if (node->getType() != ASTNodeType::Undefined)
    {
        tmp = tokens.peek();
        if (tmp.getType() != TokenType::SemiColon)
        {
            throw "expecting a semicolon ';'";
        }
        else
        {
            tokens.read();
        }
    }
    return node;
}
/*addtive -> multiplicative ( (+ | -) multiplicative)*/
ASTNode *SimpleParser::additive()
{
    ASTNode *child1 = multiplicative();
    ASTNode *node = child1;
    ASTNode *child2 = new ASTNode();
    while (true)
    {
        Token tmp = tokens.peek();
        if (node->getType() != ASTNodeType::Undefined && tmp.getType() == TokenType::Plus || tmp.getType() == TokenType::Minus)
        {
            tokens.read();
            child2 = multiplicative();
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
        else
        {
            break;
        }
    }
    return node;
}
/* * multiplicative -> primary ( (* | /) primary)* */
ASTNode *SimpleParser::multiplicative()
{
    ASTNode *child1 = primary();
    ASTNode *node = child1;
    ASTNode *child2 = new ASTNode();
    while (true)
    {
        Token tmp = tokens.peek();
        if (node->getType() != ASTNodeType::Undefined && tmp.getType() == TokenType::Star || tmp.getType() == TokenType::Slash)
        {
            tokens.read();
            child2 = primary();
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
        else
        {
            break;
        }
    }
    return node;
}
/*primary -> IntLiteral | Id | (additive)*/
ASTNode *SimpleParser::primary()
{
    ASTNode *node = new ASTNode();
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
void SimpleParser::dumAST(ASTNode *node, string indent)
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