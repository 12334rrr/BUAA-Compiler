/**
 * File: FuncRParams.h
 */

#ifndef COMPILER_FUNCRPARAMS_H
#define COMPILER_FUNCRPARAMS_H


#include "../../symbolTable/SymbolItem.h"

class FuncRParams {
public:
    static std::vector<std::string> funcRParamsTypeList;
    static std::vector<std::string> funcRParamsNameList;
    static std::string funcName;
public :
    static std::vector<Value> funcRParamsParser(const SymbolItem &item, int lineNum);
    static bool checkFuncRParams(const std::string &callerType,const std::string &calleeType);
};


#endif //COMPILER_FUNCRPARAMS_H
