//
// Created by hp on 2024/10/9.
//

#ifndef COMPILER_DECL_H
#define COMPILER_DECL_H


#include <string>
#include "../../token/Token.h"

class Decl {
public:
    static void declParser();

    static bool isDecl(const tokenItem& token);
};


#endif //COMPILER_DECL_H
