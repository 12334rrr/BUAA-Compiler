/**
 * @file BlockTree.cpp
 * @author 王春博
 */

#include "BlockTree.h"
#include "../../token/Token.h"
#include "../../parser/function/FuncDef.h"

int BlockTree::nowBlockIndex = -1;
int BlockTree::treeNodeNum = 0;
BlockTreeNode *BlockTree::nowBlockNode = nullptr;
BlockTreeNode *BlockTree::blockRoot = nullptr;
std::vector<BlockTreeNode*> BlockTree::blockNodeList = std::vector<BlockTreeNode*>();

void BlockTree::createBlockNode() {
    //节点间的联系
    auto *blockTreeNode = (BlockTreeNode *) malloc(sizeof(BlockTreeNode)*2);
    blockTreeNode->parent = BlockTree::nowBlockNode;
    blockTreeNode->parent->children[blockTreeNode->parent->childrenNum++] = blockTreeNode;
    blockTreeNode->childrenNum = 0;
    BlockTree::nowBlockIndex = ++BlockTree::treeNodeNum;
    blockTreeNode->blockIndex = BlockTree::nowBlockIndex;
    BlockTree::nowBlockNode = blockTreeNode;
    BlockTree::blockNodeList.push_back(blockTreeNode);
    //向该节点挂载符号表
    blockTreeNode->symbolTable = new SymbolTable();
    blockTreeNode->symbolTable->init();
}

void BlockTree::destroyBlockTree() {
//    SymbolTable::printAllSymbolInfo();
    BlockTreeNode *node = BlockTree::nowBlockNode;
    if (node->parent->childrenNum > 0) {
        node->parent->childrenNum--;
    }
    BlockTree::nowBlockIndex = node->parent->blockIndex;
    BlockTree::nowBlockNode = node->parent;
    BlockTree::blockNodeList.pop_back();
    free(node->symbolTable);
    free(node);
    node = nullptr;
}

void BlockTree::init() {
    BlockTree::nowBlockIndex = 1;
    auto *blockTreeNode = (BlockTreeNode *) malloc(sizeof(BlockTreeNode)*2);
    blockTreeNode->parent = nullptr;
    blockTreeNode->childrenNum = 0;
    blockTreeNode->blockIndex = BlockTree::nowBlockIndex;
    BlockTree::blockRoot = blockTreeNode;
    BlockTree::nowBlockNode = blockTreeNode;
    BlockTree::blockNodeList.push_back(blockTreeNode);
    BlockTree::treeNodeNum = 1;
    blockTreeNode->symbolTable = new SymbolTable();
    blockTreeNode->symbolTable->init();
}