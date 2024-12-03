/**
 * @file FuncRParams.cpp
 * @brief FuncRParams class
 * @version 1.0
 * @date 2024-10-03
 * @Author  王春博
 */

#include "FuncRParams.h"
#include "../../token/Token.h"
#include "../../util/Util.h"
#include "../expression/unaryexp/Exp.h"
#include <iostream>

std::vector<std::string> FuncRParams::funcRParamsTypeList;
std::vector<std::string> FuncRParams::funcRParamsNameList;

void init(){
    FuncRParams::funcRParamsTypeList.clear();
    FuncRParams::funcRParamsNameList.clear();
}
std::vector<Value> FuncRParams::funcRParamsParser(const SymbolItem &symbolItem, int lineNum) {
    init();
    Exp::expType = SymbolTable::getSymbolItem(symbolItem.name).type;
    std::vector<std::string> expTypeList;
    std::vector<Value> valueList;
    Value value;

    value = Exp::expParser();
    valueList.push_back(value);

    expTypeList.push_back(Exp::expType);
    funcRParamsTypeList.push_back(Exp::expType);
    funcRParamsNameList.push_back(Exp::expString);
    tokenItem token = Token::getNowToken();
    while (token.name == ",") {
        token = Token::getNextToken();
        value = Exp::expParser();
        funcRParamsTypeList.push_back(Exp::expType);
        funcRParamsNameList.push_back(Exp::expString);
        valueList.push_back(value);
        expTypeList.push_back(Exp::expType);
        token = Token::getNowToken();
    }
    if (expTypeList.size() != symbolItem.paramNum) {
        Util::printSemanticErrorInfo(lineNum, "d");
    } else {
        for (auto i = 0; i < expTypeList.size(); i++) {
            if (!checkFuncRParams(expTypeList[i], symbolItem.paramTypeList[i])) {
                Util::printSemanticErrorInfo(lineNum, "e");
                break;
            }
        }
    }
    Util::printParserInfo("<FuncRParams>");
    return valueList;
}

bool FuncRParams::checkFuncRParams(const std::string &callerType, const std::string &calleeType) {
    if (callerType.find("Array") != std::string::npos && calleeType.find("Array") != std::string::npos) {
        return (callerType.find("Int") != std::string::npos && calleeType.find("Int") != std::string::npos) ||
               (callerType.find("Char") != std::string::npos && calleeType.find("Char") != std::string::npos);
    }
    return callerType.find("Array") == std::string::npos && calleeType.find("Array") == std::string::npos;
}
