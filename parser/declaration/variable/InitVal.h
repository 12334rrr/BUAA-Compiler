/**
 * @file InitVal.h
 * @brief Initialize value class
 * @version 1.0
 * @date 2024-10-10
 * @Author  王春博
 */

#ifndef COMPILER_INITVAL_H
#define COMPILER_INITVAL_H


#include <vector>
#include <string>
#include "../../../util/Value.h"

class InitVal {
public:
    static std::vector<std::string> arrayValue;
public:
    static void initValParser();

    static std::vector<Value> initValParser(const std::string& name, const std::string& type);

};


#endif //COMPILER_INITVAL_H
