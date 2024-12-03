/**
 * @refitem LOrExp
 * @brief Class for logical or expression.
 * @version 1.0
 * @date 2024-10-03
 * @Author  王春博
 */

#include <fstream>
#include "LOrExp.h"
#include "RelExp.h"
#include "../../../token/Token.h"
#include "LAndExp.h"
#include "../../../util/Util.h"

void LOrExp::lOrExpParser() {
    LAndExp::lAndExpParser();
    Util::printParserInfo("<LOrExp>");

    tokenItem token = Token::getNowToken();
    while(token.type == "OR") {
        token = Token::getNextToken();
        LAndExp::lAndExpParser();
        Util::printParserInfo("<LOrExp>");
        token = Token::getNowToken();
    }
}
