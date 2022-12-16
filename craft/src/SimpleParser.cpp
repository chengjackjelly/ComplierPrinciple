#include "SimpleParser.hpp"
#include <exception>
#include <assert.h>
#include <stdexcept>
#include <string.h>
string trim(string s)
{
    if (s.empty())
    {
        return s;
    }

    s.erase(0, s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);
    return s;
}
void SimpleParser::parse(string code)
{
    SimpleLexer lexer;
    tokens = TokenReader(lexer.tokenize(code));
    root = new ASTNode(ASTNodeType::Programm, "parser");
    ASTNode *child;
    while (tokens.peek().getType() != TokenType::Undefined)
    {
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
            throw("unknow statement");
        }
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
                        throw("expecting a semicolon ';'");
                    }
                }
                else
                {
                    throw("unknow statement after '=' ");
                }
            }
            else if (tmp.getType() == TokenType::SemiColon)
            {
                tokens.read();
            }
            else
            {
                throw("expecting a semicolon ';'");
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
                throw("expecting a expression after '='");
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
            throw("expecting a semicolon ';'");
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
                throw("invalid additive expression");
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
                throw("invalid multiplicative expression");
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
                throw("expecting a right paren");
            }
        }
        else
        {
            // TODO *()*
            throw("unexpecting character");
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
int SimpleParser::evaluate(ASTNode *node)
{
    ASTNodeType type = node->getType();
    ASTNode *child1;
    ASTNode *child2;
    int left;
    int right;
    string varname;
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
    case ASTNodeType::Identifier:
        varname = node->getText();
        if (variables.find(varname) == variables.end())
        {
            throw "undefine variables";
        }
        result = variables[varname];
        break;
    case AssignmentStmt:
        varname = node->getText();
        if (variables.find(varname) == variables.end())
        {
            throw "undefine variables";
        }
    case IntDeclaration:
        child1 = node->getChildren()[0];
        right = evaluate(child1);
        varname = node->getText();
        variables[varname] = right;
        result = right;
        break;
    default:
        break;
    }
    if (node->getType() == ASTNodeType::IntDeclaration || node->getType() == ASTNodeType::AssignmentStmt)
    {
        cout << node->getText() << ":" << result << endl;
    }
    else if (node->getType() == ASTNodeType::Programm)
    {
        cout << result << endl;
    }
    return result;
}
void SimpleParser::prog()
{
    evaluate(root);
}
void SimpleParser::REPL(int argc, char *argv[])
{
    verbose = false;
    if (argc > 1 && strcmp(argv[1], "-v") == 0)
    {
        verbose = true;
    }

    cout << "Simple Script Language!" << endl;
    string reader;
    string scripttext;
    cout << "\n>";
    while (true)
    {
        try
        {
            cin >> reader;
            string line = trim(reader);
            if (line == "exit();")
            {
                cout << "Good Bye!" << endl;
                break;
            }
            scripttext += line + "\n";
            if (line[line.length() - 1] == ';')
            {
                parse(scripttext);
                if (verbose)
                {
                    dumAST(root, " ");
                }
                evaluate(root);
                cout << "\n>";
                scripttext = "";
            }
        }
        catch (const char *s)
        {
            cout << s << endl;
            cout << "\n>";
            scripttext = "";
        }
        catch (string s)
        {
            cout << s << endl;
            cout << "\n>";
            scripttext = "";
        }
    }
}