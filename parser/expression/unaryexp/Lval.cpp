/**
 * Lval.cpp
 * @brief Lval class
 * @version 1.0
 * @date 2024-10-03
 * @Author  王春博
 */

#include <fstream>
#include "Lval.h"
#include "../../../token/Token.h"
#include "Exp.h"
#include "../../../util/Util.h"
#include "../../../symbolTable/blockTree/BlockTree.h"
#include "../../function/FuncRParams.h"
#include "../../../symbolTable/SymbolTable.h"
#include "../../../codeGeneration/llvm/LlvmIRGenerator.h"
#include "../../../util/Constants.h"

Value Lval::lvalParser(bool needLoad) {
    SymbolItem* symbolItemPtr = SymbolTable::getSymbolItemPtr(Token::getNowToken().name);
//    SymbolTable::printAllSymbolInfo();
    // printf("%s+++++++++++++++++\n", Token::getNowToken().name.c_str());
//    SymbolTable::printAllSymbolInfo();
    // printf("root :%p\n", &(BlockTree::blockRoot->symbolTable[0]));
    SymbolItem symbolItem = *symbolItemPtr;
    // printf("%p\n", &symbolItem);

    // printf("************    %s   *************\n", symbolItem.value.numValue.c_str());
    // printf("%p--------------------+++\n",symbolItemPtr);
    Value value;
    tokenItem token = Token::getNowToken();
    if (token.type == "IDENFR") {
        if(!SymbolTable::isSymbolExist(token.name)){
            Util::printSemanticErrorInfo(token.lineNum, "c");
        }
        Exp::expType = SymbolTable::getSymbolItem(token.name).type;
        token = Token::getNextToken();
    }
    if (token.name == "[") {
        token = Token::getNextToken();
        value = Exp::expParser();
        token = Token::getNowToken();
        if (token.name == "]") {
            token = Token::getNextToken();
        } else {
            Util::printErrorInfo(token.lineNum, "k");
        }
    }
    value = LlvmIRGenerator::LVal(symbolItemPtr, value,needLoad,curFuncSymbol);
    Util::printParserInfo("<LVal>");
    return value;
}
