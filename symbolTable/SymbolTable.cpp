/**
 * SymbolTable.cpp -- implementation of the SymbolTable class
 * @Author  王春博
 */

#include "SymbolTable.h"
#include "blockTree/BlockTree.h"
#include <algorithm>
#include <queue>


void SymbolTable::printSymbolTable() {
    if (symbolTableList.empty()) {
        printf("SymbolTable is empty\n");
        return;
    }
    for (auto &i: symbolTableList) {
        printf("Name: %s, Type: %s, ScopeIndex: %d,ArraySize: %d, ParamNum: %d\n", i.name.c_str(),
               i.type.c_str(), i.scopeIndex, i.arraySize, i.paramNum);
        for(auto &j: i.paramTypeList){
            printf("ParamType: %s\n", j.c_str());
        }
        for(auto &j: i.arrayValueList){
            printf("ArrayValue: %d\n", j);
        }
    }

    printf("\n");
}

void SymbolTable::printAllSymbolInfo() {
    printf("-----------------------------------------\n");
    BlockTreeNode *node = BlockTree::blockRoot;
    //声明一个队列进行层序遍历，输出所有的符号表的信息
    std::queue<BlockTreeNode *> queue = std::queue<BlockTreeNode *>();
    queue.push(node);
    while (!queue.empty()) {
        BlockTreeNode *temp = queue.front();
        temp->symbolTable->printSymbolTable();
        for (int i = 0; i < temp->childrenNum; i++) {
            queue.push(temp->children[i]);
        }
        queue.pop();
    }
}
void SymbolTable::init() {
    this->nowScopeIndex = BlockTree::nowBlockIndex;
    this->symbolTableList = std::vector<SymbolItem>();
}

bool SymbolTable::isSymbolExist(const std::string &name) {
    //需要不断向上递归查找直至根节点,已经提前设计好，根节点的父节点为空
    BlockTreeNode *node = BlockTree::nowBlockNode;
    while (node != nullptr) {
        if (node->symbolTable->isSymbolPresent(name)) {
            return true;
        }
        node = node->parent;
    }
    return false;
}

void SymbolTable::addSymbol(const SymbolItem &item) {
    symbolTableList.push_back(item);
}
bool SymbolTable::isFunc(const std::string &name){
    for(auto &item: BlockTree::blockRoot->symbolTable->symbolTableList){
        if(item.name == name){
            if(item.type.find("Func") != std::string::npos){
                return true;
            }
        }
    }
    return false;
}
bool SymbolTable::isSymbolPresent(const std::string &name) {
    if (symbolTableList.empty()) {
        return false;
    }
    auto it = std::find_if(symbolTableList.begin(), symbolTableList.end(), [&name](const SymbolItem &item) {
        return item.name == name;
    });
    return it != symbolTableList.end();
}

SymbolItem SymbolTable::getSymbolItem(const std::string &name) {
    BlockTreeNode *node = BlockTree::nowBlockNode;
    while (node != nullptr) {
        for (auto &item: node->symbolTable->symbolTableList) {
            if (item.name == name) {
                return item;
            }
        }
        node = node->parent;
    }
    return SymbolItem(-1);
}

SymbolItem * SymbolTable::getSymbolItemPtr(const std::string &name) {
    BlockTreeNode *node = BlockTree::nowBlockNode;
    while (node != nullptr) {
        for (auto &item: node->symbolTable->symbolTableList) {
            if (item.name == name) {
                return &item;
            }
        }
        node = node->parent;
    }
    return nullptr;
}

void SymbolTable::deleteSymbol(SymbolItem symbolItem) {
    SymbolTable* symbolTable = BlockTree::nowBlockNode->symbolTable;
    auto it = std::remove_if(symbolTable->symbolTableList.begin(), symbolTable->symbolTableList.end(),
                             [&symbolItem](const SymbolItem &item) {
                                 return item.name == symbolItem.name && item.paramTypeList == symbolItem.paramTypeList;
                             });
    if (it != symbolTable->symbolTableList.end()) {
        symbolTable->symbolTableList.erase(it, symbolTable->symbolTableList.end());
    }
}