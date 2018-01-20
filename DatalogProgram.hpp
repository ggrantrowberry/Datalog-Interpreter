//
//  DatalogProgram.hpp
//  P2 Datalog Parser
//
//  Created by Grant Rowberry on 10/5/16.
//  Copyright © 2016 Grant Rowberry. All rights reserved.
//
#pragma once
#ifndef DatalogProgram_hpp
#define DatalogProgram_hpp

#include <stdio.h>
#include <vector>
#include "Rule.hpp"
#include "Predicate.hpp"
#include <iostream>
#include <algorithm>
#include "RDB.hpp"
#include "Relation.hpp"

using namespace std;

class DatalogProgram {
public:
    Predicate createPred();
    Rule createRule();
    void addSchemePred(vector<Predicate> pred);
    void addFactPred(vector<Predicate> pred);
    void addQueryPred(vector<Predicate> pred);
    void addRule(vector<Rule> rule);
    void createDomain();
    void print();
    void answerQueries();
    
private:
    vector<Predicate> scheme;
    vector<Predicate> fact;
    vector<Predicate> query;
    vector<Rule> rule;
    vector<string> domain;
    
    
};

#endif /* DatalogProgram_hpp */
