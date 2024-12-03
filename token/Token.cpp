/**
 * @Author: 王春博
 * @Date: 2024-10-03
 * @Description: 语法分析程序
 * @refitem
 */
#include "Token.h"
#include "../util/Util.h"
#include <iostream>
#include <vector>
#include <utility>

std::vector<tokenItem> Token::tokenList;
std::vector<tokenItem> Token::lookAheadList;
int Token::tokenIndex = -1;

void Token::tokenInit() {
    tokenIndex = -1;
    tokenList.clear();
    lookAheadList.clear();
}

tokenItem Token::getNextToken() {
    tokenIndex++;
    if (tokenIndex < tokenList.size()) {
        if (tokenIndex > 0) {
            if (tokenList[tokenIndex - 1].type == "CHRCON") {
                tokenList[tokenIndex - 1].name = "\'" + tokenList[tokenIndex - 1].name + "\'";
            }
            Util::printParserInfo((tokenList[tokenIndex - 1].type + " " + tokenList[tokenIndex - 1].name).c_str());
        }
        return tokenList[tokenIndex];
    }
    if (tokenIndex == tokenList.size()) {
        Util::printParserInfo((tokenList[tokenIndex - 1].type + " " + tokenList[tokenIndex - 1].name).c_str());
    }
    return {"", "", -1};
}

void Token::addToken(std::string name, std::string type, int lineNum) {
    tokenItem token;
    token.name = std::move(name);
    token.type = std::move(type);
    token.lineNum = lineNum;
    tokenList.push_back(token);
}

std::ostream &operator<<(std::ostream &os, const tokenItem &item) {
    os << item.name << " " << item.type << " " << item.lineNum << std::endl;
    return os;
}

void Token::unGetToken() {
    if (tokenIndex > 0) {
        tokenIndex--;
    } else {
        printf("Error: unGetToken out of range\n");
    }
}

void Token::lookAhead(int num) {
    lookAheadList.clear();
    if (tokenIndex + num > tokenList.size()) {
        printf("tokenIndex: %d, tokenList.size(): %zu ,num:%d\n", tokenIndex, tokenList.size(), num);
        return;
    }
    for (int i = 1; i <= num; i++) {
        lookAheadList.push_back(tokenList[tokenIndex + i]);
    }
}

tokenItem Token::getNowToken() {
    if (tokenIndex >= 0 && tokenIndex < tokenList.size()) {
        return tokenList[tokenIndex];
    } else {
        return {"", "", -1};
    }
}

std::ostream &operator<<(std::ostream &os, const std::vector<tokenItem> &vec) {
    for (const auto &item: vec) {
        os << item << " ";
    }
    return os;
}