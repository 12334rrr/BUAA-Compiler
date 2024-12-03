/**
 * File: ForStmt.cpp
 * @brief For statement class
 * @version 1.0
 * @date 2024-10-10
 * @Author  王春博
 */
#include "ForStmt.h"
#include "../../token/Token.h"
#include "../expression/unaryexp/Lval.h"
#include "../expression/unaryexp/Exp.h"
#include "../../util/Util.h"

void ForStmt::forStmtParser() {
    tokenItem tokenTemp = Token::getNowToken();
    Lval::lvalParser(false);
    tokenItem token = Token::getNowToken();
    if(token.name == "="){
        if(SymbolTable::getSymbolItem(tokenTemp.name).type.find("Const") != std::string::npos){
            Util::printSemanticErrorInfo(tokenTemp.lineNum, "h");
        }
        token = Token::getNextToken();
    }
    Exp::expParser();
    Util::printParserInfo("<ForStmt>");
}
