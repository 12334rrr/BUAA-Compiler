/**
 * CompUnit.cpp -- Parse the CompUnit non-terminal
 */

#include <iostream>
#include "CompUnit.h"
#include "../../token/Token.h"
#include "../Parser.h"
#include "../function/MainFuncDef.h"
#include "../function/FuncDef.h"
#include "../declaration/Decl.h"
#include "../../util/Util.h"

void CompUnit::compUnitParser() {
    if(Token::tokenList.empty()){
        std::cout << "No Token to parse." << std::endl;
        return;
    }
    tokenItem token = Token::getNextToken();
    while(Parser::isBType(token) || Parser::isConst(token) || Parser::isFuncType(token)){
        Token::lookAhead(2);
        if(token.name == "int" && Token::lookAheadList[0].name == "main"){
            MainFuncDef::mainFuncDefParser();
        }
        else if(token.type == "CONSTTK"){
            if(Parser::isBType(Token::lookAheadList[0])){
                Decl::declParser();
            }
        }
        else if(Token::lookAheadList[0].type == "IDENFR"){
            if(Token::lookAheadList[1].name == "("){
                FuncDef::funcDefParser();
            }
            else{
                Decl::declParser();
            }
        }
        token = Token::getNowToken();
    }
    Util::printParserInfo("<CompUnit>");
}
