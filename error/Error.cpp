#include "Error.h"
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>

bool compareErrorItems(const errorItem &a, const errorItem &b) {
    return a.lineNum < b.lineNum;
}

void Error::sortError() {
    deleteSameError();
    std::ifstream inputFile("error.txt");
    std::vector<errorItem> errorList;
    errorItem temp;

    // 从文件中读取错误项
    while (inputFile >> temp.lineNum) {
        std::getline(inputFile, temp.errorType);
        errorList.push_back(temp);
    }
    inputFile.close();

    // 对错误项进行稳定排序
    std::stable_sort(errorList.begin(), errorList.end(), compareErrorItems);

    // 将排序后的错误项写回文件
    std::ofstream outputFile("error.txt");
    for (const auto &item : errorList) {
        outputFile << item.lineNum << item.errorType << std::endl;
    }
    outputFile.close();

}

void Error::deleteSameError() {
    // 读取错误项,将类型和行号组合成字符串，存入set，自动去重
    std::ifstream inputFile("error.txt");
    std::string temp;
    std::set<std::string> errorSet;
    while (std::getline(inputFile, temp)) {
        errorSet.insert(temp);
    }
    //写回到文件
    std::ofstream outputFile("error.txt");
    for (const auto &error : errorSet) {
        outputFile << error << std::endl;
    }
    inputFile.close();
}
