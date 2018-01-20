//
//  Rule.cpp
//  P2 Datalog Parser
//
//  Created by Grant Rowberry on 10/5/16.
//  Copyright © 2016 Grant Rowberry. All rights reserved.
//

#include "Rule.hpp"

string Rule::toString(){
    string s;

    s += headPred.toString();
    s += " :- ";
    for(int i = 0; i < preds.size(); i++){
       
        s += preds[i].toString();
        if(i != preds.size()-1){
            s += ",";
        }
    }
    s += ".";
    return s;
}

void Rule::setHeadPred(Predicate HP){
    headPred = HP;
}

void Rule::addPred(vector<Predicate> Pred){
    preds = Pred;
}

vector<Predicate> Rule::getPredicates(){
    return preds;
}

vector<string> Rule::getHeadPredAttributes(){
    return headPred.getSParamContent();
}

string Rule::getRuleName(){
   return headPred.getName();
}
