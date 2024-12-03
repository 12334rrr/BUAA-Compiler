/**
 * @file Lval.h
 * @brief 左值表达式类
 * @version 1.0
 * @date 2024-10-03
 * @Author  王春博
 */

#ifndef COMPILER_LVAL_H
#define COMPILER_LVAL_H


#include "../../../util/Value.h"

class Lval {
public:
    static Value lvalParser(bool needLoad);
};


#endif //COMPILER_LVAL_H
