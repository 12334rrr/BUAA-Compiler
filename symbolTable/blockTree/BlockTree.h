/**
 * BlockTree.h -- Header file for BlockTree.cpp
 *
 */
#ifndef COMPILER_BLOCKTREE_H
#define COMPILER_BLOCKTREE_H


#include "BlockTreeNode.h"

class BlockTree {
public:
    static int nowBlockIndex;
    static int treeNodeNum;
    static BlockTreeNode * blockRoot;
    static BlockTreeNode * nowBlockNode;
    static std::vector<BlockTreeNode *> blockNodeList;
public:
    static void createBlockNode();
    static void destroyBlockTree();

    static void init();
};
#endif //COMPILER_BLOCKTREE_H
