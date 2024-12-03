/**
 * @file Block.cpp
 * @brief 块语句类
 * @version 1.0
 * @date 2024-10-03
 * @Author  王春博
 */

#include<iostream>
#include "Block.h"
#include "BlockItem.h"
#include "Stmt.h"
#include "../declaration/Decl.h"
#include "../../util/Util.h"
#include "../../symbolTable/blockTree/BlockTree.h"
#include "../function/FuncDef.h"
#include "../function/MainFuncDef.h"

void Block::blockParser() {
    tokenItem token = Token::getNowToken();
    if (token.name == "{") {
        if(FuncDef::isInParam){
            FuncDef::isInParam = false;
        }
        else if(FuncDef::isInFunc != 0){
            FuncDef::isInFunc ++;
        }
        if (FuncDef::isInFunc != 1) {
            BlockTree::createBlockNode();
        }
        if(MainFuncDef::isInMainDef){
            MainFuncDef::mainNestingLevel ++;
        }
        token = Token::getNextToken();
    }
    while (isBlockItem(token)) {
        BlockItem::blockItemParser();
        token = Token::getNowToken();
    }
    token = Token::getNowToken();

    if (token.name == "}") {
        //TODO:g类型的错误必须是检查最后一句话吗,目前的逻辑是函数内有return就可以，但是不一定是最后一句
        //不可以,最后一句必须是return,而不是函数内有return就可以
        if(FuncDef::isInFunc == 1 && !FuncDef::isReturn && SymbolTable::getSymbolItem(FuncDef::funcName).type!= "VoidFunc"){
            Util::printSemanticErrorInfo(token.lineNum, "g");
        }
        //Main函数的return错误处理
        if(MainFuncDef::isInMainDef && !MainFuncDef::isMainReturn && MainFuncDef::mainNestingLevel == 1){
            Util::printSemanticErrorInfo(token.lineNum, "g");
        }
        if(FuncDef::isInFunc > 0){
            FuncDef::isInFunc --;
        }
        if(MainFuncDef::isInMainDef){
            MainFuncDef::mainNestingLevel --;
        }
        token = Token::getNextToken();
    }
    BlockTree::destroyBlockTree();
    Util::printParserInfo("<Block>");
}

bool Block::isBlockItem(const tokenItem &token) {
    return Decl::isDecl(token) || Stmt::isStmt(token);
}