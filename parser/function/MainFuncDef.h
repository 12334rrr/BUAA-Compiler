/**
 * @file MainFuncDef.h
 * @brief 主函数类
 * @version 1.0
 * @date 2024-10-03
 * @Author  王春博
 */

#ifndef COMPILER_MAINFUNCDEF_H
#define COMPILER_MAINFUNCDEF_H

#include "../../symbolTable/SymbolItem.h"

class MainFuncDef {
public :
    static void mainFuncDefParser();

    static bool isMainReturn;
    static bool isInMainDef;
    static int mainNestingLevel;
};


#endif //COMPILER_MAINFUNCDEF_H
