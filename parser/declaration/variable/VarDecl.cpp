/**
 * VarDecl.cpp --  Parse the variable declaration
 * @file VarDecl.cpp
 * @brief Parse the variable declaration
 * @version 1.0
 * @date 2024-10-03
 * @Author  王春博
 */

#include "VarDecl.h"
#include "../../../token/Token.h"
#include "../../../util/Util.h"
#include "../../Parser.h"
#include "VarDef.h"
#include "../../../symbolTable/blockTree/BlockTree.h"
#include <fstream>

void VarDecl::varDeclParser() {
    std::string type;
    std::vector<SymbolItem> itemList;
    tokenItem token = Token::getNowToken();
    if (Parser::isBType(token)) {
        if(token.name == "int"){
            type = "Int";
        } else if(token.name == "char"){
            type = "Char";
        }
        token = Token::getNextToken();
    }
    VarDef::varDefParser(itemList,type);

    token = Token::getNowToken();
    while (token.name == ",") {
        token = Token::getNextToken();
        VarDef::varDefParser(itemList,type);
        token = Token::getNowToken();
    }
    token = Token::getNowToken();
    if (token.name == ";") {
        token = Token::getNextToken();
    } else {
        Util::printErrorInfo(token.lineNum, "i");
    }
    for(auto &item : itemList){
        item.type = type + item.type;
        item.scopeIndex = BlockTree::nowBlockIndex;
    }

    Util::printParserInfo("<VarDecl>");
    Util::printSemanticInfo(&itemList);
}
