/**
 * File: VarDef.h
 * @brief 变量定义类
 * @version 1.0
 * @date 2024-10-03
 * @Author  王春博
 */

#ifndef COMPILER_VARDEF_H
#define COMPILER_VARDEF_H


#include <vector>
#include "../../../symbolTable/SymbolItem.h"

class VarDef {
public:
    static void varDefParser(std::vector<SymbolItem> &itemList);

    static void varDefParser(std::vector<SymbolItem> &itemList, std::string type);
};


#endif //COMPILER_VARDEF_H
