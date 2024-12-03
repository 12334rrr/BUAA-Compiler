#include <iostream>
#include "BlockTreeNode.h"
#include "../SymbolTable.h"
#include "BlockTree.h"

void BlockTreeNode::printBlockTreeNodeInfo(BlockTreeNode *node) {
    if (node == nullptr) {
        printf("BlockTreeNode: nullptr\n");
    }
    printf("BlockTreeNode: %p\n", node);
    printf("Parent: %p\n", node->parent);
    printf("ChildrenNum: %d\n", node->childrenNum);
    printf("SymbolTable: %p\n", node->symbolTable);
    for (int i = 0; i < node->childrenNum; i++) {
        printf("Children[%d]: %p\n", i, node->children[i]);
    }
}

[[maybe_unused]] void BlockTreeNode::destroyBlockTreeNode(BlockTreeNode *node) {
    if (node == nullptr) {
        printf("BlockTreeNode: nullptr\n");
        return;
    }
    try {
        delete node->symbolTable;
        delete node;
    }catch (...) {
        std::cerr << "Unknown exception caught during deletion." << std::endl;
    }
}
