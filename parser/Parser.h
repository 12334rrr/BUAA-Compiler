/**
 * Parser class
 * @brief Parser class
 * @version 1.0
 * @date 2024-10-03
 * @Author  王春博
 */

#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H

#include <string>
#include "../token/Token.h"

class Parser {
public:
    static void parse();
    static bool isConst(const tokenItem &token);
    static bool isFuncType(const tokenItem &token);
    static bool isUnaryExp(const tokenItem &token);
    static bool isUnaryOp(const tokenItem &token);
    static bool isBType(const tokenItem &token);
};


#endif //COMPILER_PARSER_H
