//
// Created by hp on 2024/10/9.
//

#include <fstream>
#include "RelExp.h"
#include "AddExp.h"
#include "../../../token/Token.h"
#include "../../../util/Util.h"

void RelExp::relExpParser() {
    AddExp::addExpParser();
    Util::printParserInfo("<RelExp>");
    tokenItem token = Token::getNowToken();
    while(token.type == "LSS" || token.type == "LEQ" || token.type == "GRE" || token.type == "GEQ") {
        token = Token::getNextToken();
        AddExp::addExpParser();
        Util::printParserInfo("<RelExp>");
        token = Token::getNowToken();
    }
}
