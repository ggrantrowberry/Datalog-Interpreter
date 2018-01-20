//
//  Parameter.hpp
//  P2 Datalog Parser
//
//  Created by Grant Rowberry on 10/5/16.
//  Copyright © 2016 Grant Rowberry. All rights reserved.
//

#ifndef Parameter_hpp
#define Parameter_hpp

#include <stdio.h>
#include <vector>
#include "Token.hpp"
#include <iostream>

using namespace std;

class Parameter{
public:
    virtual string toString(){return "parameterbaseclass";}
    virtual Token getToken(){Token t; return t;};
    //Parameter(){}
private:
    
    
};

class Param: public Parameter{
public:
    string toString();
    void setToken(Token Tok);
    Token getToken();
private:
    Token tok;
};
/*
class StringParam: public Parameter{
public:
    string toString();
private:
    Token tok;
};
*/
#endif /* Parameter_hpp */
