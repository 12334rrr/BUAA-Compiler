/**
 * @file Block.h
 * @brief 块语句类
 * @version 1.0
 * @date 2024-10-03
 * @Author  王春博
 */

#ifndef COMPILER_BLOCK_H
#define COMPILER_BLOCK_H


#include "../../token/Token.h"

class Block {
public:
    static void blockParser();

    static bool isBlockItem(const tokenItem& token);

};


#endif //COMPILER_BLOCK_H
