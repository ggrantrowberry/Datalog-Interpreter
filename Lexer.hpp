//
//  Lexer.hpp
//  Proj1 Lexical Analyzer
//
//  Created by Grant Rowberry on 9/21/16.
//  Copyright © 2016 Grant Rowberry. All rights reserved.
//

#ifndef Lexer_hpp
#define Lexer_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include "Token.hpp"
#include <fstream>
#include <iostream>
#include <ctype.h>
using namespace std;



class Lexer {
public:
    void readFile(string fileName);
    void run();
    //enum tokentype {COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, WHITESPACE,UNDEFINED};
    void print();
    Token createToken(Token::tokentype type, string content, int lineNumber);
    int commaMech(char c);
    int periodMech(char c);
    int qMarkMech(char c);
    int leftParenMech(char c);
    int rightParenMech(char c);
    int colonMech(char c);
    int colonDashMech(char c);
    int multiplyMech(char c);
    int addMech(char c);
    int schemesMech(char c);
    int factsMech(char c);
    int rulesMech(char c);
    int queriesMech(char c);
    int idMech(char c);
    int stringMech(char c);
    //int stringHelp(char c);
    int commentMech(char c);
    int whitespaceMech(char c);
    int undefinedMech1(char c);
    int undefinedMech2(string s, int charCount);
    int eofMech(char c);
    vector<Token> getTokens();
    
private:
    vector<char> chars;

    int max = 0;
    int currentIndex = 0;
    Token::tokentype maxToken;
    int lineNumber = 1;
    string maxContent;
    vector<Token> finalTokens;
    int lineNumberToAdd = 0;
    int totalTokens = 0;
};



#endif /* Lexer_hpp */
