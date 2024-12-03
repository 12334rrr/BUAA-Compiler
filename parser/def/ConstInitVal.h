/**
 * @file ConstInitVal.h
 * @brief ConstInitVal class
 * @version 1.0
 * @date 2024-10-10
 * @Author  王春博
 */
#ifndef COMPILER_CONSTINITVAL_H
#define COMPILER_CONSTINITVAL_H


#include <vector>
#include "../../util/Value.h"

class ConstInitVal {
public:
    static bool isConstInitValFlag ;
    static std::vector<int> constInitValValueList;
    static std::vector<Value> constInitValParser();
};


#endif //COMPILER_CONSTINITVAL_H
