/**
 * @file BlockItem.cpp
 * @brief 块语句类
 * @version 1.0
 * @date 2024-10-03
 * @Author  王春博
 */

#include "BlockItem.h"
#include "../../token/Token.h"
#include "../declaration/Decl.h"
#include "Stmt.h"
#include<iostream>
#include<fstream>

void BlockItem::blockItemParser() {
    tokenItem token = Token::getNowToken();
    if(Decl::isDecl(token)){
        Decl::declParser();
    }
    else if(Stmt::isStmt(token)){
        Stmt::stmtParser();
    }
}

bool BlockItem::isBlockItem(const std::string& string) {
    return false;
}
