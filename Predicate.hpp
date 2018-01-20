//
//  Predicate.hpp
//  P2 Datalog Parser
//
//  Created by Grant Rowberry on 10/5/16.
//  Copyright © 2016 Grant Rowberry. All rights reserved.
//

#ifndef Predicate_hpp
#define Predicate_hpp

#include <stdio.h>
#include "Token.hpp"
#include "Parameter.hpp"
#include <vector>


class Predicate{
public:
    enum predType{Scheme, Fact, HeadPredicate, Normal, Query};
    string toString();
    Predicate(){};
    void setName(Token tname);
    void setType(predType ptype);
    void addParam(vector<Parameter*> param);
    vector<Parameter*> getParamContent();
    string getName();
    vector<string> getSParamContent();
    vector<Token> getParamTokens();
private:
    Token name;
    vector<Token> ids;
    vector<Parameter*> params;
    predType type;
    
    
};

#endif /* Predicate_hpp */
