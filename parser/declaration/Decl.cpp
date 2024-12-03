/**
 * Decl.cpp -- Parse the declaration of the program
 * @file Decl.cpp
 * @brief Parse the declaration of the program
 * @version 1.0
 * @date 2024-10-03
 * @Author  王春博
 */

#include "Decl.h"
#include "../../parser/Parser.h"
#include "const/ConstDecl.h"
#include "variable/VarDecl.h"

void Decl::declParser() {
    tokenItem token = Token::getNowToken();
    if(token.name == "const"){
        ConstDecl::constDeclParser();
    }
    else{
        VarDecl::varDeclParser();
    }
    token = Token::getNowToken();
}

bool Decl::isDecl(const tokenItem& token) {
    if(Parser::isBType(token) || token.name == "const"){
        return true;
    }
    else{
        return false;
    }
}
