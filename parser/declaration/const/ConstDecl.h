/**
 * @file ConstDecl.h
 * @brief 常量声明类
 * @version 1.0
 * @date 2024-10-03
 * @Author  王春博
 */

#ifndef COMPILER_CONSTDECL_H
#define COMPILER_CONSTDECL_H


#include <string>
#include <vector>
#include "../../../codeGeneration/llvm/constVarInfo.h"

class ConstDecl {
public:
    static std::vector<constVarInfo> constInfoList;

public:
    static void constDeclParser();

    static void constDeclInit();

    static void codeGeneration(std::vector<constVarInfo> vector1);
};


#endif //COMPILER_CONSTDECL_H
