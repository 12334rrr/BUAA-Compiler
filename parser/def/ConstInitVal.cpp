/**
 *
 */
#include <fstream>
#include "ConstInitVal.h"
#include "../../token/Token.h"
#include "../../util/Util.h"
#include "../expression/unaryexp/ConstExp.h"
#include "../Parser.h"
#include "../../codeGeneration/llvm/LlvmIRGenerator.h"

std::vector<int> ConstInitVal::constInitValValueList;
bool ConstInitVal::isConstInitValFlag = false;

std::vector<Value> ConstInitVal::constInitValParser() {
    Value value;
    std::vector<Value> valueList;
    constInitValValueList.clear();
    isConstInitValFlag = true;
    tokenItem token = Token::getNowToken();
    if(token.type == "STRCON"){
        valueList = LlvmIRGenerator::stringConst(token.name);
        token = Token::getNextToken();
    }
    else if(Parser::isUnaryExp(token)){
        value = ConstExp::constExpParser();
        constInitValValueList.push_back(ConstExp::constExpValue);
        valueList.push_back(value);
        token = Token::getNowToken();
    }
    else if(token.name == "{"){
        token = Token::getNextToken();
        if(Parser::isUnaryExp(token)){
            value = ConstExp::constExpParser();
            constInitValValueList.push_back(ConstExp::constExpValue);
            valueList.push_back(value);
            token = Token::getNowToken();
            while(token.name == ","){
                token = Token::getNextToken();
                value = ConstExp::constExpParser();
                constInitValValueList.push_back(ConstExp::constExpValue);
                valueList.push_back(value);
                token = Token::getNowToken();
            }
        }
        token = Token::getNowToken();
        if(token.name == "}"){
            token = Token::getNextToken();
        }
    }
    isConstInitValFlag = false;
    Util::printParserInfo("<ConstInitVal>");
    return valueList;
}
