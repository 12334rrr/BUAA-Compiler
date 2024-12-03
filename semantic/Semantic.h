/**
 * @file Semantic.h
 * @brief This file contains the declaration of the class Semantic.
 * @version 1.0
 * @date 2024-10-14
 * @Author  王春博
 */

#ifndef COMPILER_SEMANTIC_H
#define COMPILER_SEMANTIC_H

struct semanticItem {
    int blockIndex;
    std::string name;
    std::string semanticType;
};

class Semantic {
    static void semanticAnalysis();

public:
    static void sortSemantic();

    static void clearRoot();
};


#endif //COMPILER_SEMANTIC_H
