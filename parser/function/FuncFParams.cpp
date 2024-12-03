/**
 * FuncFParams.cpp --  Parse function parameters
 */

#include "FuncFParams.h"
#include "../../token/Token.h"
#include "../../util/Util.h"
#include "../Parser.h"
#include "FuncFParam.h"
#include "../../symbolTable/blockTree/BlockTree.h"
#include "../../codeGeneration/llvm/Llvm.h"

void FuncFParams::funcFParamsParser(SymbolItem &item) {
    int paramNum = 0;
    std::vector<SymbolItem> paramList;
    tokenItem token = Token::getNowToken();
    if(Parser::isBType(token)) {
        paramNum++;
        FuncFParam::funcFParamParser(paramList);
        token = Token::getNowToken();
    }
    token = Token::getNowToken();
    while (token.name == ",") {
        Llvm::printLlvmCode(",");
        paramNum++;
        token = Token::getNextToken();
        FuncFParam::funcFParamParser(paramList);
        token = Token::getNowToken();
    }
    item.paramNum = paramNum;
    for(auto &param : paramList){
        item.paramNameList.push_back(param.name);
        item.paramTypeList.push_back(param.type);
    }
    Util::printParserInfo("<FuncFParams>");
}
