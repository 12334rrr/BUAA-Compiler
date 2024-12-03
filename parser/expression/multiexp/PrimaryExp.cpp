/**
 * @file PrimaryExp.cpp
 * @brief PrimaryExp class
 * @version 1.0
 * @date 2024-10-03
 * @Author  王春博
 */

#include "PrimaryExp.h"
#include "../unaryexp/Number.h"
#include "../unaryexp/Character.h"
#include "../unaryexp/Lval.h"
#include "../unaryexp/Exp.h"
#include "../../../util/Util.h"

Value PrimaryExp::primaryExpParser() {
    Value value;
    tokenItem token = Token::getNowToken();
    if(token.type == "INTCON"){
        value = Number::numberParser();
        token = Token::getNowToken();
    }
    else if(token.type == "CHRCON"){
        value = Character::characterParser();
        token = Token::getNowToken();
    }
    else if(token.type == "IDENFR"){
        printf("************%s\n", value.numValue.c_str());
        value = Lval::lvalParser(true);
        printf("************%s\n", value.numValue.c_str());
        token = Token::getNowToken();
    }
    else if(token.name == "("){
        token = Token::getNextToken();
        value = Exp::expParser();
        Exp::expType = Exp::expType;
        token = Token::getNowToken();
        if(token.name == ")"){
            token = Token::getNextToken();
        }
        else{
            Util::printErrorInfo(token.lineNum, "j");
        }
    }
    Util::printParserInfo("<PrimaryExp>");
    return value;
}

bool PrimaryExp::isPrimaryExp(const tokenItem &token) {
    return token.name == "(" ;
}
