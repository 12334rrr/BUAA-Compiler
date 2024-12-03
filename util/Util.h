/**
 * Util.h
 * 工具类的头文件
 * @Author 王春博
 * @Date 2021-10-03
 * @Version 1.0
 */

#ifndef COMPILER_UTIL_H
#define COMPILER_UTIL_H


#include <string>
#include "../symbolTable/SymbolTable.h"

class Util {
public:

    static bool isIdentItem(char c);

    static bool isOperator(char c);

    static bool isBinaryOperator(char c);

    static bool isDelimiter(char c);

    static bool isTokenItem(char c);

    static bool isUnaryOperator(const std::string& c);

    static void printParserInfo(const char *info);

    static void printErrorInfo(int lineNum, const char *error);

    static void clearFile();
    static void clearParserInfo();

    static void initEnv();

    static void createFile();

    static void releaseEnv();

    static bool isExistEQL();

    static void printSemanticInfo(SymbolItem *item);

    static void printSemanticInfo(const std::vector<SymbolItem> *itemList);

    static void printSemanticErrorInfo(int lineNum, const std::string &error);

    static int calConstExp(const std::string &exp);

    void mvFileInfo();

    static void mvFileInfo(const std::string &sourcePath, const std::string &destinationPath);
};

#endif //COMPILER_UTIL_H
