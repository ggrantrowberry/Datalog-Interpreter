//
//  RDB.hpp
//  P3 Relational Database
//
//  Created by Grant Rowberry on 10/24/16.
//  Copyright © 2016 Grant Rowberry. All rights reserved.
//
#pragma once
#ifndef RDB_hpp
#define RDB_hpp
//#include "DatalogProgram.hpp"
#include "Token.hpp"
#include "Predicate.hpp"
#include "Parameter.hpp"
#include "Rule.hpp"
#include "Relation.hpp"
#include <algorithm>
#include <map>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include "Graph.hpp"
#include "Node.hpp"

using namespace std;
class RDB {
public:
    RDB(vector<Predicate> Schemes, vector<Predicate> Facts, vector<Predicate> Queries, vector<Rule> Rules);
    ~RDB(){};
    
    void analyzeSchemes();
    void compileFacts();
    void evaluateRules();
    int ruleHelper(int count);
    void answerQueries();
    Relation* singleQuery(Predicate p);
    string toPrint(Relation* r);
    void run();
    bool singleRule(Rule rule);
    vector<long int> getIndices(Rule rule, Relation* r);
    void setRelationNames();
    void evaluateOptimizedRules();
    vector<vector<Node*>> createGraph();
    void getSCC();
    vector<Node*> nodeFiller(vector<Node*> nodes, vector<string> ruleNames);
    vector<int> indexFinder(vector<string> ruleNames, string nameToFind);
    void printDependencyGraph(vector<Node*> nodes);
    void evaluateSCC(vector<vector<Node*>> scc);
    void printRuleEvaluation(vector<int> passes, vector<vector<Node*>> scc);
    bool nodeChecker(Node* toBeChecked, Node* toCheck);
    void printSCC(vector<vector<Node*>> scc);
    bool isSinglePass(vector<Node*> oneSCC);
    void sccSort(vector<vector<Node*>>& scc);
    
private:
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Predicate> queries;
    vector<Rule> rules;
    vector<Relation*> relations;
    vector<string> schemeNames;
    vector<string> relationNames;
    
    
    
    
};


#endif /* RDB_hpp */
