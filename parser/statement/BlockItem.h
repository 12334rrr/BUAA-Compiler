/**
 * @file BlockItem.h
 * @brief 块语句类
 * @version 1.0
 * @date 2024-10-03
 * @Author  王春博
 */

#ifndef COMPILER_BLOCKITEM_H
#define COMPILER_BLOCKITEM_H


#include<string>

class BlockItem {
public:
    static void blockItemParser();
    static bool isBlockItem(const std::string& string);
};


#endif //COMPILER_BLOCKITEM_H
