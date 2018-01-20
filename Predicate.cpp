//
//  Predicate.cpp
//  P2 Datalog Parser
//
//  Created by Grant Rowberry on 10/5/16.
//  Copyright © 2016 Grant Rowberry. All rights reserved.
//

#include "Predicate.hpp"


string Predicate::toString(){
    string s;
    s = name.getContent() + "(";
    for(int i = 0; i < params.size(); i++){
        //cout << params.size() << endl;
        s += params[i]->toString();
        if(i != params.size()-1){
            s += ",";
        }
    }
    s += ")";
    
    if(type == Fact){
        s += ".";
    }
    if(type == Query){
        s += "?";
    }
    return s;
}

void Predicate::setName(Token tname){
    name = tname;
}

void Predicate::setType(predType ptype){
    type = ptype;
}

void Predicate::addParam(vector<Parameter*> param){
    params = param;
}

vector<Parameter*> Predicate::getParamContent(){
        return params;
}

string Predicate::getName(){
    return name.getContent();
}

vector<string> Predicate::getSParamContent(){
    vector<string> v;
    for(int i = 0; i < params.size(); i++){
        v.push_back(params[i]->toString());
        
    }
    return v;
}

vector<Token> Predicate::getParamTokens(){
    vector<Token> v;
    for(int i = 0; i < params.size(); i++){
        v.push_back(params[i]->getToken());
    }
    return v;
}
