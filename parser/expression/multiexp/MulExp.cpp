/**
 * File: MulExp.cpp
 * ----------------
 * This file implements the MulExp.h interface.
 * @version 1.0
 * @date 2024-10-03
 * @Author  王春博
 */

#include <fstream>
#include "MulExp.h"
#include "../../../token/Token.h"
#include "../unaryexp/UnaryExp.h"
#include "../../../util/Util.h"
#include "../unaryexp/Exp.h"
#include "../../../codeGeneration/llvm/LlvmIRGenerator.h"

extern SymbolItem *curFuncSymbol;
Value MulExp::mulExpParser() {
    Value value1 = UnaryExp::unaryExpParser();
    Util::printParserInfo("<MulExp>");
    tokenItem token = Token::getNowToken();
    while(token.type == "MULT" || token.type == "DIV" || token.type == "MOD") {
        std::string temp = token.name;
        token = Token::getNextToken();
        Value value2 = UnaryExp::unaryExpParser();
        Util::printParserInfo("<MulExp>");
        value1 = LlvmIRGenerator::MulOrDivOp(temp, value1, value2, curFuncSymbol);
        token = Token::getNowToken();
        Exp::expType = "Int";
    }
    return value1;
}
