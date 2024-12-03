/**
 * @file Llvm.h
 * @brief The file that contains the declaration of the class Llvm
 * @version 1.0
 * @date 2024-10-30
 * @Author  王春博
 */

#ifndef COMPILER_LLVM_H
#define COMPILER_LLVM_H


#include <string>

class Llvm {
public:
    static void printLlvmCode(const std::string &code);
};


#endif //COMPILER_LLVM_H
