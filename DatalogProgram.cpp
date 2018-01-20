//
//  DatalogProgram.cpp
//  P2 Datalog Parser
//
//  Created by Grant Rowberry on 10/5/16.
//  Copyright © 2016 Grant Rowberry. All rights reserved.
//

#include "DatalogProgram.hpp"


void DatalogProgram::addSchemePred(vector<Predicate> pred){
    scheme = pred;
}

void DatalogProgram::addRule(vector<Rule> Rule){
    rule = Rule;
}

void DatalogProgram::addFactPred(vector<Predicate> pred){
    fact = pred;
}

void DatalogProgram::addQueryPred(vector<Predicate> pred){
    query = pred;
}

void DatalogProgram::createDomain(){
    vector<Parameter*> p;

    for(int i = 0; i < fact.size(); i++){
        vector<Parameter*> q = fact[i].getParamContent();
        p.insert(p.end(), q.begin(), q.end());
    }
    for(int i = 0; i < p.size(); i++){
        domain.push_back(p[i]->toString());
    }
    sort (domain.begin(), domain.end());
    domain.erase(unique (domain.begin(), domain.end()), domain.end());
}

void DatalogProgram::print(){
    cout << "Success!" << endl;
    cout << "Schemes" << "(" << scheme.size() << "):" << endl;
    for (int i = 0; i < scheme.size(); i++){
        cout << "  " << scheme[i].toString() << endl;
    }
    cout << "Facts" << "(" << fact.size() << "):" << endl;
    for (int i = 0; i < fact.size(); i++){
        cout << "  " << fact[i].toString() << endl;
    }
    cout << "Rules" << "(" << rule.size() << "):" << endl;
    for (int i = 0; i < rule.size(); i++){
        cout << "  " << rule[i].toString() << endl;
    }
    cout << "Queries" << "(" << query.size() << "):" << endl;
    for (int i = 0; i < query.size(); i++){
        cout << "  " << query[i].toString() << endl;
    }
    cout << "Domain" << "(" << domain.size() << "):" << endl;
    for (int i = 0; i < domain.size(); i++){
        cout << "  " << domain[i] << endl;
    }
    
}
void DatalogProgram::answerQueries(){
   RDB r(scheme, fact, query, rule);
    r.run();
}
