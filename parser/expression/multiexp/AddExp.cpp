/**
 * File: AddExp.cpp
 * @brief AddExp class
 * @version 1.0
 * @date 2024-10-03
 * @Author  王春博
 */

#include <fstream>
#include "AddExp.h"
#include "MulExp.h"
#include "../../../token/Token.h"
#include "../../../util/Util.h"
#include "../unaryexp/Exp.h"
#include "../../../codeGeneration/llvm/LlvmIRGenerator.h"
#include "../../../util/Constants.h"


Value AddExp::addExpParser() {
    Value value1 = MulExp::mulExpParser();
    Util::printParserInfo("<AddExp>");
    tokenItem token = Token::getNowToken();
    while(token.name == "+" || token.name == "-") {
        std::string temp = token.name;
        token = Token::getNextToken();

        Value value2 = MulExp::mulExpParser();
        value1 = LlvmIRGenerator::AddOrSubOp(temp, value1, value2, curFuncSymbol);
        Util::printParserInfo("<AddExp>");
        token = Token::getNowToken();
        Exp::expType = "Int";
    }
    return value1;
}
