/**
 * Llvm.cpp -- implementation of the Llvm class
 * @version 1.0
 * @date 2024-10-30
 * @Author  王春博
 */

#include <fstream>
#include "Llvm.h"

//
extern std::ofstream file;

void Llvm::printLlvmCode(const std::string &code) {
    //向llvm.txt文件中写入code
//    std::ofstream midCodeFile("llvm_ir.txt", std::ios::app);
//    midCodeFile << code ;
//    midCodeFile.close();
//    std::ofstream file("llvm_ir.txt", std::ios::app); // 追加模式
//    file << code <<std::endl;
file << code;
}
