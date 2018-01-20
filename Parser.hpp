//
//  Parser.hpp
//  P2 Datalog Parser
//
//  Created by Grant Rowberry on 9/28/16.
//  Copyright © 2016 Grant Rowberry. All rights reserved.
//

#ifndef Parser_hpp
#define Parser_hpp

#include <stdio.h>
#include "Lexer.hpp"
#include "Token.hpp"
#include "DatalogProgram.hpp"
#include "Rule.hpp"
#include "Expressions.hpp"
#include "Predicate.hpp"
#include "Parameter.hpp"
#include <iostream>
using namespace std;

class Parser {
public:
    DatalogProgram dataLogProgram();
    Predicate scheme();
    vector<Predicate> schemeList();
    vector<Parameter*> idList();
    Predicate fact();
    vector<Predicate> factList();
    Rule rule();
    vector<Rule> ruleList();
    Predicate headPredicate();
    Predicate predicate();
    vector<Predicate> predicateList();
    Parameter* parameter();
    vector<Parameter*> parameterList();
    Parameter* expression();
    Token Operator();
    Predicate query();
    vector<Predicate> queryList();
    vector<Parameter*> stringList();
    Token COMMA();
    Token PERIOD();
    Token Q_MARK();
    Token LEFT_PAREN();
    Token RIGHT_PAREN();
    Token COLON();
    Token COLON_DASH();
    Token MULTIPLY();
    Token ADD();
    Token SCHEMES();
    Token FACTS();
    Token RULES();
    Token QUERIES();
    Token ID();
    Token STRING();
    void createVec(vector<Token> finalTokens);
    void printFailed();
    
private:
    vector<Token>tokens;
    int currentIndex = 0;
    string failedTokenInfo;
    
    
    
};

#endif /* Parser_hpp */
