/**
 * @file SymbolTable.h
 * @brief 符号表类
 * @version 1.0
 * @date 2024-10-14
 * @Author  王春博
 */

#ifndef COMPILER_SYMBOLTABLE_H
#define COMPILER_SYMBOLTABLE_H

#include <string>
#include <vector>
#include "SymbolItem.h"

class SymbolTable {
public:
    std::vector<SymbolItem> symbolTableList;
    int nowScopeIndex;

public:
    static bool isSymbolExist(const std::string &name);

    bool isSymbolPresent(const std::string &name);

    void printSymbolTable();

    void destroySymbolTable();

    void addSymbol(std::string name, std::string type, int scopeIndex, int value, int arraySize, int paramNum,
                   const std::vector<std::string> &paramType);

    void addSymbol(const SymbolItem &item);

    void init();

    static SymbolItem getSymbolItem(const std::string &name);

    static void printAllSymbolInfo();

    static void deleteSymbol(SymbolItem symbolItem);

    static bool isFunc(const std::string &name);

    static SymbolItem * getSymbolItemPtr(const std::string &name);
};


#endif //COMPILER_SYMBOLTABLE_H