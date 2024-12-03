/**
 * @file FuncDef.h
 * @brief FuncDef class header file
 * @version 1.0
 * @date 2024-10-10
 * @Author  王春博
 */

#ifndef COMPILER_FUNCDEF_H
#define COMPILER_FUNCDEF_H


class FuncDef {
public:
    static int isInFunc;
    static bool isInParam;
    static std::string funcName;
    static bool isReturn;
    static void funcDefParser();

public:
    static void funcDefInit();
};


#endif //COMPILER_FUNCDEF_H