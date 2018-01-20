//
//  Expressions.cpp
//  P2 Datalog Parser
//
//  Created by Grant Rowberry on 10/5/16.
//  Copyright © 2016 Grant Rowberry. All rights reserved.
//

#include "Expressions.hpp"

string Expression::toString(){
    string s;
    s += "(";
    s += leftParam->toString();
    s += oper.getContent();
    s += rightParam->toString();
    s += ")";
    return s;
};

void Expression::setLeftParam(Parameter* param){
    leftParam = param;
}

void Expression::setRightParam(Parameter* param){
    rightParam = param;
}

void Expression::setOperator(Token op){
    oper = op;
}

Expression::~Expression(){
    delete [] leftParam;
    delete [] rightParam;
}
