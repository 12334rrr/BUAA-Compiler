/**
 * 常量类
 * 包含了一些常量的定义
 * @file Constants.cpp
 * @brief 常量类
 * @version 1.0
 * @date 2024-10-03
 * @Author  王春博
 */

#include "Constants.h"
#include "../symbolTable/SymbolItem.h"

#define NUM_RESERVED 14
#define NUM_SYMBOL 23
#define MAX_TOKEN_LEN 1000

const char* FILE_TEST_PATH = "testfile.txt";
const char* FILE_RIGHT_PATH = "lexer.txt";
const char* FILE_ERROR_PATH = "error.txt";
const char* FILE_PARSER_PATH = "../parser.txt";


SymbolItem *curFuncSymbol = nullptr;