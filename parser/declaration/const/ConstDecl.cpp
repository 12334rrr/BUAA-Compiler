/**
 * @file ConstDecl.cpp
 * @brief 常量声明类
 * @version 1.0
 * @date 2024-10-03
 * @Author  王春博
 */

#include "ConstDecl.h"
#include "../../../token/Token.h"
#include "../../Parser.h"
#include "../../def/ConstDef.h"
#include "../../../util/Util.h"
#include "../../../symbolTable/blockTree/BlockTree.h"
#include "../../../codeGeneration/llvm/LlvmIRConstructor.h"

std::vector<constVarInfo> ConstDecl::constInfoList;

void ConstDecl::constDeclParser() {
    constDeclInit();
    std::string type;
    std::vector<SymbolItem> itemList;
    tokenItem token = Token::getNowToken();
    if (token.name == "const") {
        token = Token::getNextToken();
    }
    if (Parser::isBType(token)) {
        if (token.name == "int") {
            type = "ConstInt";
        } else if (token.name == "char") {
            type = "ConstChar";
        } else {
            printf("常量定义时类型错误\n");
        }
        token = Token::getNextToken();
    }
    ConstDef::constDefParser(itemList,type);
    token = Token::getNowToken();
    while (token.name == ",") {
        token = Token::getNextToken();
        ConstDef::constDefParser(itemList,type);
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
    for(auto &item : itemList){
        item.paramNum = 0;
        BlockTree::nowBlockNode->symbolTable->addSymbol(item);
    }
    Util::printParserInfo("<ConstDecl>");
    Util::printSemanticInfo(&itemList);
}

void ConstDecl::constDeclInit() {
    constInfoList.clear();
}