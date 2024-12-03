/**
 *
 */

#include "Number.h"
#include "../../../token/Token.h"
#include "../../../util/Util.h"
#include "Exp.h"
#include <fstream>

Value Number::numberParser() {
    tokenItem token = Token::getNowToken();
    Value value(token.name,"i32",true);
    if (token.type == "INTCON") {
        token = Token::getNextToken();
        Exp::expType = "Int";
    }
    Util::printParserInfo("<Number>");
    return value;
}
