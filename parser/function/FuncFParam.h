/**
 * @file FuncFParam.h
 * @brief FuncFParam class
 * @version 1.0
 * @date 2024-10-12
 * @Author  王春博
 */

#ifndef COMPILER_FUNCFPARAM_H
#define COMPILER_FUNCFPARAM_H


#include "../../symbolTable/SymbolItem.h"

class FuncFParam {
public:
    static void funcFParamParser(std::vector<SymbolItem> &paramList);
};


#endif //COMPILER_FUNCFPARAM_H
