/**
 *
 */

#ifndef COMPILER_EXP_H
#define COMPILER_EXP_H


#include <string>
#include "../../../util/Value.h"

class Exp {
public:
    static std::string expType;
    static std::string expString;
public:
    static Value expParser();
};


#endif //COMPILER_EXP_H
