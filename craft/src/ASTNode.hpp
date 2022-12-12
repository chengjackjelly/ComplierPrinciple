#ifndef ASTNODE
#define ASTNODE
#include <iostream>
#include <string>
#include <vector>
#include "ASTNodeType.hpp"
using namespace std;
using namespace ASTNodes;
// class ASTTree{

// };
class ASTNode
{

public:
    ASTNodeType nodeType;
    string text;
    ASTNode *parent;
    vector<ASTNode *> children;
    ASTNode()
    {
        nodeType = ASTNodeType::Undefined;
        text = "";
    }
    ASTNode(ASTNodeType nodeType_, string text_)
    {
        nodeType = nodeType_;
        text = text_;
    }
    ASTNode getParent()
    {
        return *parent;
    }
    vector<ASTNode *> &getChildren()
    {
        return this->children;
    }
    void addChild(ASTNode *child)
    {
        children.push_back(child);
        child->parent = this;
    }
    ASTNodeType getType()
    {
        return nodeType;
    }
    string getText()
    {
        return text;
    }
};
#endif