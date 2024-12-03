/**
 *
 */

#ifndef COMPILER_SYMBOLITEM_H
#define COMPILER_SYMBOLITEM_H

#include <string>
#include <vector>
#include "../util/Value.h"


class SymbolItem {
public:
    std::string name;
    std::string type;
    int scopeIndex{};
    int arraySize{};
    int paramNum{};
    std::vector<std::string> paramTypeList;
    std::vector<std::string> paramNameList;
    std::vector<int> arrayValueList;

    int llvmIRStoreReg{};
    Value value;

public:
    explicit SymbolItem();
    explicit SymbolItem(std::string name);
    explicit SymbolItem(int scopeIndex);
    explicit SymbolItem(const std::string& name, const std::string& type);
    explicit SymbolItem(std::string name, std::string type, int scopeIndex, int value, int arraySize, int paramNum);
    explicit SymbolItem(std::string name, std::string type, int scopeIndex, int value, int arraySize, int paramNum,
               const std::vector<std::string> &paramTypeList);

    static void initCurrentFuncSymbol(SymbolItem *symbolItem);
};

#endif // COMPILER_SYMBOLITEM_H