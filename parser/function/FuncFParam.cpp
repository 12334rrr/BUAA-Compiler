/**
 * FuncFParam.cpp -- 语法分析器的 FuncFParam 类实现
 */

#include "FuncFParam.h"
#include "../../token/Token.h"
#include "../../util/Util.h"
#include "../Parser.h"
#include "../../symbolTable/blockTree/BlockTree.h"
#include "../../codeGeneration/llvm/LlvmIRGenerator.h"
#include "../../util/Constants.h"

void FuncFParam::funcFParamParser(std::vector<SymbolItem> &itemList) {
    SymbolItem item = SymbolItem();
    tokenItem token = Token::getNowToken();
    if(Parser::isBType(token)){
        if(token.name == "int"){
            item.type = "Int";
        }
        else if(token.name == "char"){
            item.type = "Char";
        }
        token = Token::getNextToken();
    }
    if(token.type == "IDENFR"){
        if(BlockTree::nowBlockNode->symbolTable->isSymbolPresent(token.name)|| SymbolTable::isFunc(token.name)){
            Util::printSemanticErrorInfo(token.lineNum, "b");
        }
        item.name = token.name;
        token = Token::getNextToken();
    }
    if(token.name == "["){
        item.type += "Array";
        token = Token::getNextToken();
        if(token.name == "]"){
            token = Token::getNextToken();
        }
        else{
            Util::printErrorInfo(token.lineNum, "k");
        }
    }
    item.scopeIndex = BlockTree::nowBlockIndex;

    //形参定义
    LlvmIRGenerator::getRegName(item, curFuncSymbol);
    LlvmIRGenerator::getRegType(item, true);
    LlvmIRGenerator::FuncFParam(item);

    Util::printParserInfo("<FuncFParam>");
    Util::printSemanticInfo(&item);
    itemList.push_back(item);
    BlockTree::nowBlockNode->symbolTable->addSymbol(item);
}
