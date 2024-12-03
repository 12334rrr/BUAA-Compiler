/**
 * @Author: 王春博
 * @Version: 1.0
 * @Date: 2024-10-03
 */

#include <fstream>
#include "LAndExp.h"
#include "EqExp.h"
#include "../../../token/Token.h"
#include "../../../util/Util.h"
#include "../../../codeGeneration/label/Stmt.h"

Value LAndExp::lAndExpParser(Stmt &stmt,) {
    stmt.andCount++;
    std::string andStr = stmt.
    Value value = EqExp::eqExpParser();
    Util::printParserInfo("<LAndExp>");

    tokenItem token = Token::getNowToken();
    while (token.type == "AND") {
        token = Token::getNextToken();
        Value value1 = EqExp::eqExpParser();

        Util::printParserInfo("<LAndExp>");
        token = Token::getNowToken();
    }

}
