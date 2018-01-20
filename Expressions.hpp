//
//  Expressions.hpp
//  P2 Datalog Parser
//
//  Created by Grant Rowberry on 10/5/16.
//  Copyright © 2016 Grant Rowberry. All rights reserved.
//

#ifndef Expressions_hpp
#define Expressions_hpp

#include <stdio.h>
#include "Parameter.hpp"
#include "Token.hpp"


class Expression: public Parameter{
public:
    string toString();
    void setLeftParam(Parameter* param);
    void setRightParam(Parameter* param);
    void setOperator(Token op);
    Expression (){};
    ~Expression();
private:
    //vector<Token> express;
    Parameter* leftParam;
    Parameter* rightParam;
    Token oper;
};
#endif  /*Expressions_hpp */
