/**
 * FuncFParams class
 * @brief FuncFParams class
 * @version 1.0
 * @date 2024-10-12
 * @Author  王春博
 */

#ifndef COMPILER_FUNCFPARAMS_H
#define COMPILER_FUNCFPARAMS_H


#include "../../symbolTable/SymbolItem.h"

class FuncFParams {
public:
    static void funcFParamsParser(SymbolItem &item);
};


#endif //COMPILER_FUNCFPARAMS_H
