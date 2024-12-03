/**
 * Character:
 */

#include <fstream>
#include "Character.h"
#include "../../../token/Token.h"
#include "../../../util/Util.h"
#include "../../function/FuncRParams.h"
#include "Exp.h"

Value Character::characterParser() {
    tokenItem token = Token::getNowToken();
    Value value(std::to_string(static_cast<int>(Token::getNowToken().name[0])),"i8",true);

    if(token.type == "CHRCON"){
        token = Token::getNextToken();
        Exp::expType = "Char";
    }
    Util::printParserInfo("<Character>");
    return value;
}