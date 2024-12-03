/**
 * @file UnaryExp.h
 * @brief UnaryExp class
 * @version 1.0
 * @date 2024-10-03
 * @Author  王春博
 */

#ifndef COMPILER_UNARYEXP_H
#define COMPILER_UNARYEXP_H


#include "../../../util/Value.h"

class UnaryExp {
public:
    static Value unaryExpParser();
};


#endif //COMPILER_UNARYEXP_H
