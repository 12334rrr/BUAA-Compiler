/**
 * @file EqExp.cpp
 * @brief EqExp class
 * @version 1.0
 * @date 2024-10-03
 * @Author  王春博
 */

#include <fstream>
#include "EqExp.h"
#include "RelExp.h"
#include "../../../token/Token.h"
#include "../../../util/Util.h"

void EqExp::eqExpParser() {
    RelExp::relExpParser();
    Util::printParserInfo("<EqExp>");
    tokenItem token = Token::getNowToken();
    while (token.type == "EQL" || token.type == "NEQ") {
        token = Token::getNextToken();
        RelExp::relExpParser();
        Util::printParserInfo("<EqExp>");
        token = Token::getNowToken();
    }
}
