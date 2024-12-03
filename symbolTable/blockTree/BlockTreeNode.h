/**
 * @file BlockTreeNode.h
 */
#ifndef COMPILER_BLOCKTREENODE_H
#define COMPILER_BLOCKTREENODE_H

#include "../SymbolTable.h"

class BlockTreeNode {
public:
    BlockTreeNode *parent;
    int childrenNum;
    int blockIndex;
    SymbolTable *symbolTable;
    BlockTreeNode *children[];

public:
    [[maybe_unused]] static void destroyBlockTreeNode(BlockTreeNode *node);
    static void printBlockTreeNodeInfo(BlockTreeNode *node);
};


#endif //COMPILER_BLOCKTREENODE_H
