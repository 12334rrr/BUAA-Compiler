/*
 *
 */
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "Semantic.h"
#include "../symbolTable/blockTree/BlockTree.h"

bool compareSemanticItems(const semanticItem &a, const semanticItem &b) {
    return a.blockIndex < b.blockIndex;
}

void Semantic::sortSemantic() {
    std::ifstream inputFile("symbol.txt");
    std::vector<semanticItem> semanticList;
    semanticItem temp;

    // 从文件中读取语义项
    while (inputFile >> temp.blockIndex) {
        std::getline(inputFile, temp.name,' ' );
        std::getline(inputFile, temp.semanticType);
        semanticList.push_back(temp);
    }
    inputFile.close();

    // 对语义项进行排序
    std::stable_sort(semanticList.begin(), semanticList.end(), compareSemanticItems);

    // 将排序后的语义项写回文件
    std::ofstream outputFile("symbol.txt");
    for (const auto &item : semanticList) {
        outputFile << item.blockIndex <<  item.name << " " << item.semanticType << std::endl;
    }
    outputFile.close();
}

void Semantic::clearRoot(){
    BlockTree::blockNodeList.clear();
    free(BlockTree::blockRoot);
    BlockTree::blockRoot = nullptr;
}