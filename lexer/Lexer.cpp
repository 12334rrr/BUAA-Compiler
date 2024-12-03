/**
 * @Author: 王春博
 * @Date: 2024-9-20
 * @Version: 1.0
 * @Description: 词法分析程序
*/


#include "Lexer.h"
#include "../util/Constants.h"
#include "../util/Util.h"
#include"../token/Token.h"
#include<iostream>
#include <cstdio>
#include <fstream>
#include <cstring>

#define NUM_RESERVED 14
#define NUM_SYMBOL 23
#define MAX_TOKEN_LEN 1000

const char *reservedWords[NUM_RESERVED] = {
        "main", "const", "int", "char", "break", "continue", "if", "else",
        "for", "getint", "getchar", "printf", "return", "void"
};
const char *symbolWords[NUM_SYMBOL] = {
        "!", "&&", "||", "+", "-", "*", "/", "%", "<", "<=", ">", ">=", "==", "!=", "=", ";", ",", "(", ")", "[", "]",
        "{", "}"
};
const char *reservedWordsType[NUM_RESERVED] = {
        "MAINTK", "CONSTTK", "INTTK", "CHARTK", "BREAKTK", "CONTINUETK", "IFTK", "ELSETK",
        "FORTK", "GETINTTK", "GETCHARTK", "PRINTFTK", "RETURNTK", "VOIDTK"
};
const char *symbolType[NUM_SYMBOL] = {
        "NOT", "AND", "OR", "PLUS", "MINU", "MULT", "DIV", "MOD", "LSS", "LEQ", "GRE", "GEQ",
        "EQL", "NEQ", "ASSIGN", "SEMICN", "COMMA", "LPARENT", "RPARENT", "LBRACK", "RBRACK", "LBRACE", "RBRACE"
};
const char escapeCharacter[10] = {
        '\'', '\"', '\\', 'a', 'b', 'f', 'n', 'r', 't', 'v'
};
int line_count = 1;

char *token = (char *) malloc(MAX_TOKEN_LEN * sizeof(char) * 2);

char getChar(FILE *file) {
    char ch;
    if ((ch = fgetc(file)) != EOF) {
        return ch;
    } else {
        return EOF;
    }
}

void getNBC(FILE *file) {
    char ch;
    while ((ch = getChar(file)) != EOF) {
        if (ch == ' ' || ch == '\n' || ch == '\t') {
            if (ch == '\n') {
                line_count++;
            }
            continue;
        } else {
            break;
        }
    }
    if (ch != EOF) {
        ungetc(ch, file);
    }
}

void clearToken() {
    memset(token, 0, MAX_TOKEN_LEN * sizeof(char) * 2);
}

void cat(char ch) {
    int len = strlen(token);
    if (len < MAX_TOKEN_LEN - 1) {
        token[len] = ch;
        token[len + 1] = '\0';
    }
}

void getToken(char ch, FILE *fp) {
    while (Util::isTokenItem(ch)) {
        cat(ch);
        ch = getChar(fp);
    }
    ungetc(ch, fp);
}

int isReservedWord(char *token, std::ofstream &rightFile) {
    char *p = (char *) malloc(MAX_TOKEN_LEN * sizeof(char) * 2);
    memset(p, 0, MAX_TOKEN_LEN * sizeof(char) * 2);
    int index = 0;
    while (token[index] != '\0') {
        p[index] = token[index];
        if(token[index]>='A'&&token[index]<='Z') {
            token[index] = token[index] - 'A' + 'a';
        }
        index++;
    }
    for (int i = 0; i < NUM_RESERVED; i++) {
        if (strcmp(token, reservedWords[i]) == 0) {
            rightFile << reservedWordsType[i] << " " << token << "\n";
            Token::addToken(token, reservedWordsType[i], line_count);
            return i + 1;
        }
    }
    index = 0;
    while (p[index] != '\0') {
        token[index] = p[index];
        index++;
    }
    return -1;
}

void skipSingleLineComment(FILE *fp) {
    char ch;
    while ((ch = getChar(fp)) != EOF) {
        if (ch == '\n') {
            line_count++;
            break;
        }
    }
}

void skipMultiLineComment(FILE *fp) {
    char ch;
    int nestedCount = 1;

    while ((ch = getChar(fp)) != EOF) {
        if (ch == '*') {
            ch = getChar(fp);
            if (ch == '/') {
                nestedCount--;
                if (nestedCount == 0) {
                    break;
                }
            } else {
                ungetc(ch, fp);
            }
        } else if (ch == '/') {
            ch = getChar(fp);
            if (ch == '*') {
                nestedCount++;
            } else {
                ungetc(ch, fp);
            }
        }
        if (ch == '\n') {
            line_count++;
        }
    }
}


void Lexer::lexicalAnalysis() {
    Token::tokenInit();
    FILE *fp = fopen(FILE_TEST_PATH, "r");
    if (fp == nullptr) {
        printf("文件打开失败\n");
    }
    //创建输出文件
    std::ofstream rightFile(FILE_RIGHT_PATH);
    std::ofstream errorFile(FILE_ERROR_PATH);

    char ch;
    getNBC(fp);
    ch = getChar(fp);
    while (ch != EOF) {
        clearToken();
        if (Util::isIdentItem(ch)) {
            //字母开头
            getToken(ch, fp);
            //判断是否是保留字
            if (isReservedWord(token, rightFile) == -1) {
                //不是保留字
                rightFile << "IDENFR" << " " << token << "\n";
                Token::addToken(token, "IDENFR", line_count);
            }
        } else if (isdigit(ch)) {
            getToken(ch, fp);
            rightFile << "INTCON" << " " << token << "\n";
            Token::addToken(token, "INTCON", line_count);
        } else if (ch == '&') {
            ch = getChar(fp);
            if (ch != '&') {
                errorFile << line_count << " " << "a" << "\n";
                Token::addToken("&&", "AND", line_count);
//                rightFile << "AND" << " " << "&&" << "\n";
                ungetc(ch, fp);
            } else {
                rightFile << "AND" << " " << "&&" << "\n";
                Token::addToken("&&", "AND", line_count);
            }
        } else if (ch == '|') {
            ch = getChar(fp);
            if (ch != '|') {
                errorFile << line_count << " " << "a" << "\n";
//                Util::printErrorInfo(line_count, "a");
//                rightFile << "OR" << " " << "||" << "\n";
                Token::addToken("||", "OR", line_count);
                ungetc(ch, fp);
            } else {
                rightFile << "OR" << " " << "||" << "\n";
                Token::addToken("||", "OR", line_count);
            }
        } else if (ch == '"') {
            cat(ch);
            ch = getChar(fp);
            while (ch != '"') {
                cat(ch);
                ch = getChar(fp);
            }
            cat(ch);
            rightFile << "STRCON" << " " << token << "\n";
            Token::addToken(token, "STRCON", line_count);
        } else if (ch == '\'') {
            ch = getChar(fp);
            cat(ch);
            ch = getChar(fp);
            if (strcmp(token, "\\") != 0) {
                rightFile << "CHRCON" << " \'" << token << "\'\n";
                Token::addToken(token, "CHRCON", line_count);
            } else {
                cat(ch);
                rightFile << "CHRCON" << " \'" << token << "\'\n";
                Token::addToken(token, "CHRCON", line_count);
                getChar(fp);
            }
        } else if (ch == '/') {
            // 处理注释
            ch = getChar(fp);
            if (ch == '/') {
                skipSingleLineComment(fp);
            } else if (ch == '*') {
                skipMultiLineComment(fp);
            } else {
                ungetc(ch, fp);
                cat('/');
                rightFile << "DIV" << " " << token << "\n";
                Token::addToken(token, "DIV", line_count);
            }
        } else {
            cat(ch);
            if (ch == '<' || ch == '>' || ch == '!' || ch == '=') {
                ch = getChar(fp);
                if (ch == '=') {
                    cat(ch);
                    for (int i = 0; i < NUM_SYMBOL; i++) {
                        if (strcmp(token, symbolWords[i]) == 0) {
                            rightFile << symbolType[i] << " " << token << "\n";
                            Token::addToken(token, symbolType[i], line_count);
                            break;
                        }
                    }
                } else {
                    for (int i = 0; i < NUM_SYMBOL; i++) {
                        if (strcmp(token, symbolWords[i]) == 0) {
                            rightFile << symbolType[i] << " " << token << "\n";
                            Token::addToken(token, symbolType[i], line_count);
                            break;
                        }
                    }
                    ungetc(ch, fp);
                }
            } else {
                for (int i = 0; i < NUM_SYMBOL; i++) {
                    if (strcmp(token, symbolWords[i]) == 0) {
                        rightFile << symbolType[i] << " " << token << "\n";
                        Token::addToken(token, symbolType[i], line_count);
                        break;
                    }
                }
            }
        }
        getNBC(fp);
        ch = getChar(fp);
    }

    //关闭文件
    fclose(fp);
    rightFile.close();
    errorFile.close();
}
