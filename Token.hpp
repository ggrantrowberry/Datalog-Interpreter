//
//  Token.hpp
//  Proj1 Lexical Analyzer
//
//  Created by Grant Rowberry on 9/21/16.
//  Copyright © 2016 Grant Rowberry. All rights reserved.
//

#ifndef Token_hpp
#define Token_hpp

#include <stdio.h>
#include <string>
#include <sstream>

using namespace std;



class Token {
public:
    enum tokentype {COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, WHITESPACE, UNDEFINED, EoF, ENDLINE};
    Token(){};
    Token(string s);
    Token(tokentype type, string content, int charCount);
    ~Token(){}
    
    
    string toString();
    
    tokentype getType();
    string getContent();
    
private:
    tokentype tokenName;
    //int charCount;
    int tokLineNumber;
    string tokContent;

};


#endif /* Token_hpp */
