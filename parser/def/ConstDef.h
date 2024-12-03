/**
 * @file ConstDef.h
 * @brief ConstDef class
 * @version 1.0
 * @date 2024-10-10
 * @Author  王春博
 */

#ifndef COMPILER_CONSTDEF_H
#define COMPILER_CONSTDEF_H


#include "../../symbolTable/SymbolTable.h"

class ConstDef {
public:
    static int constVal;
public:
    static void constDefParser(std::vector<SymbolItem> &itemList, const std::string &type);

    static int constArraySize;
};


#endif //COMPILER_CONSTDEF_H
