/**
 * @file ConstExp.h
 * @brief 常量表达式类
 * @version 1.0
 * @date 2024-10-03
 * @Author  王春博
 */

#ifndef COMPILER_CONSTEXP_H
#define COMPILER_CONSTEXP_H

#include "../../../token/Token.h"
#include "../../../util/Value.h"

class ConstExp {
public:
    static Value constExpParser();
    bool isConstExp(const tokenItem &token);
    static std::string constExpTypeString;
public:
    static std::string constExpString;
    static int constExpValue;
};


#endif //COMPILER_CONSTEXP_H
