/**
 * @file InitVal.cpp
 * @brief Initialize value class
 * @version 1.0
 * @date 2024-10-10
 * @Author  王春博
 */

#include "InitVal.h"
#include "../../../token/Token.h"
#include "../../../util/Util.h"
#include "../../Parser.h"
#include "../../expression/unaryexp/Exp.h"
#include "../../../codeGeneration/llvm/LlvmIRConstructor.h"
#include "../../../codeGeneration/llvm/LlvmIRGenerator.h"

std::vector<std::string> InitVal::arrayValue = std::vector<std::string>();
void initValInit() {
    InitVal::arrayValue.clear();
}

std::vector<Value> InitVal::initValParser(const std::string& name,const std::string& type) {
    initValInit();
    Value value;
    std::vector<Value> valueList;
    int index =0;
    tokenItem token = Token::getNowToken();
    if (token.type == "STRCON") {
        valueList = LlvmIRGenerator::stringConst(token.name);
        token = Token::getNextToken();
    } else if (Parser::isUnaryExp(token)) {
        value = Exp::expParser();
        valueList.emplace_back(value);
//        LlvmIRConstructor::defArrayByIndex(name, type, std::to_string(index), LlvmIRConstructor::expString);
        token = Token::getNowToken();
    } else if (token.name == "{") {
        token = Token::getNextToken();
        if (Parser::isUnaryExp(token)) {
            value = Exp::expParser();
//            LlvmIRConstructor::defArrayByIndex(name, type, std::to_string(index), LlvmIRConstructor::expString);
            token = Token::getNowToken();
            while (token.name == ",") {
                index++;
                token = Token::getNextToken();
                value = Exp::expParser();
                valueList.push_back(value);
//                LlvmIRConstructor::defArrayByIndex(name, type, std::to_string(index), LlvmIRConstructor::expString);
                token = Token::getNowToken();
            }
        }
        if (token.name == "}") {
            token = Token::getNextToken();
        }
    }
    Util::printParserInfo("<InitVal>");
    return valueList;
}