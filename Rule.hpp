//
//  Rule.hpp
//  P2 Datalog Parser
//
//  Created by Grant Rowberry on 10/5/16.
//  Copyright © 2016 Grant Rowberry. All rights reserved.
//

#ifndef Rule_hpp
#define Rule_hpp

#include <stdio.h>
#include <vector>
#include "Token.hpp"
#include "Predicate.hpp"


class Rule{
public:
    string toString();
    void setHeadPred(Predicate HP);
    void addPred(vector<Predicate> pred);
    vector<Predicate> getPredicates();
    vector<string> getHeadPredAttributes();
    string getRuleName();
private:
    Predicate headPred;
    vector<Predicate> preds;
    string ruleName;
    
};

#endif /* Rule_hpp */
