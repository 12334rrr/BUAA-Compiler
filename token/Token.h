/**
 * Token.h -- Token class header file
 * @file Token.h
 * @brief Token class header file
 * @version 1.0
 * @date 2024-10-03
 * @Author  王春博
 */

#ifndef COMPILER_TOKEN_H
#define COMPILER_TOKEN_H

#include<vector>
#include<string>

struct tokenItem{
    std::string name;
    std::string type;
    int lineNum;
};

class Token {

public:
    static int tokenIndex;
    static std::vector<tokenItem> tokenList;
    static std::vector<tokenItem> lookAheadList;
    std::vector<std::string> tokenTypeList;
    static void tokenInit();
    static void addToken(std::string name, std::string type, int lineNum);
    static tokenItem getNextToken();
    static tokenItem getNowToken();
    static void unGetToken();
    static void lookAhead(int num);
    friend std::ostream& operator<<(std::ostream& os, const tokenItem& item);
};


#endif //COMPILER_TOKEN_H
