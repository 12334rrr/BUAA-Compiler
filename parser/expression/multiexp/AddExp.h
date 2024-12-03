/**
 * @file AddExp.h
 * @brief AddExp class
 * @version 1.0
 * @date 2024-10-03
 * @Author  王春博
 */

#ifndef COMPILER_ADDEXP_H
#define COMPILER_ADDEXP_H


#include "../../../util/Value.h"
#include "../../../symbolTable/SymbolItem.h"

class AddExp {
public:
    static Value addExpParser();
};


#endif //COMPILER_ADDEXP_H
