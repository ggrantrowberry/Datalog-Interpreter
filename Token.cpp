//
//  Token.cpp
//  Proj1 Lexical Analyzer
//
//  Created by Grant Rowberry on 9/21/16.
//  Copyright © 2016 Grant Rowberry. All rights reserved.
//

#include "Token.hpp"

Token::Token(string s){
    tokContent = s;
    
}

Token::Token(tokentype type, string content, int lineNumber){
    tokenName = type;
    tokContent = content;
    tokLineNumber = lineNumber;
    
}

Token::tokentype Token::getType(){
    return tokenName;
}

string Token::toString(){

    stringstream s;
    string token;
    switch (tokenName) {
        case COMMA:
            token = "COMMA";
            break;
        case PERIOD:
            token = "PERIOD";
            break;
        case Q_MARK:
            token = "Q_MARK";
            break;
        case LEFT_PAREN:
            token = "LEFT_PAREN";
            break;
        case RIGHT_PAREN:
            token = "RIGHT_PAREN";
            break;
        case COLON:
            token = "COLON";
            break;
        case COLON_DASH:
            token = "COLON_DASH";
            break;
        case MULTIPLY:
            token = "MULTIPLY";
            break;
        case ADD:
            token = "ADD";
            break;
        case SCHEMES:
            token = "SCHEMES";
            break;
        case FACTS:
            token = "FACTS";
            break;
        case RULES:
            token = "RULES";
            break;
        case QUERIES:
            token = "QUERIES";
            break;
        case ID:
            token = "ID";
            break;
        case STRING:
            token = "STRING";
            break;
        case COMMENT:
            token = "COMMENT";
            break;
        case UNDEFINED:
            token = "UNDEFINED";
            break;
        case EoF:
            token = "EOF";
            break;
        case WHITESPACE:
            token = "WHITESPACE";
            break;
        case ENDLINE:
            token = "ENDLINE";
            break;

        default:
            break;
    }
    s << "(" << token << ",\"" << tokContent << "\"," << tokLineNumber << ")";
    return s.str();
    
    
}

string Token::getContent(){
    return tokContent;
}
