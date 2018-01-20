//
//  Parser.cpp
//  P2 Datalog Parser
//
//  Created by Grant Rowberry on 9/28/16.
//  Copyright © 2016 Grant Rowberry. All rights reserved.
//

#include "Parser.hpp"


DatalogProgram Parser::dataLogProgram(){
  
    try{
        
        DatalogProgram dlp;
        vector<Predicate> schemes;
        vector<Predicate> queries;
        SCHEMES(); COLON();
        schemes.push_back(scheme());
        vector<Predicate> p = schemeList();
        schemes.insert(schemes.end(), p.begin(), p.end());
        //cout << schemes.size() << endl;
        dlp.addSchemePred(schemes);
        FACTS(); COLON();
        dlp.addFactPred(factList());
        RULES(); COLON();
        dlp.addRule(ruleList());
        QUERIES(); COLON();
        queries.push_back(query());
        vector<Predicate> q = queryList();
        queries.insert(queries.end(), q.begin(), q.end());
        dlp.addQueryPred(queries);
        dlp.createDomain();
        //dlp.print();
        return dlp;
    } catch(Token exception){
        cout << "Failure!" << endl << "  " << exception.toString();
    }
    DatalogProgram a;
    return a;
    
}


Predicate Parser::scheme(){
    Predicate p;
    p.setName(ID());
    p.setType(Predicate::Scheme);
    vector<Parameter*> params;
    Param* param = new Param;
    LEFT_PAREN();
    param->setToken(ID());
    params.push_back(param);
    vector<Parameter*> q = idList();
    params.insert(params.end(), q.begin(), q.end());
    p.addParam(params);
    //cout << "Scheme Param Size: " << params.size() << endl;
    RIGHT_PAREN();
    return p;
    
    //Lambda??
}

vector<Predicate> Parser::schemeList(){
    vector<Predicate> p;
    if(tokens[currentIndex].getType() == Token::FACTS/* || tokens[currentIndex].getType() == Token::RULES || tokens[currentIndex].getType() == Token::QUERIES*/){
        
        return p;
        
    }else if(tokens[currentIndex].getType() == Token::EoF) {
        
        throw(tokens[currentIndex]);
        
    } // else if (tokens[currentIndex].getType() == Token::EoF){
       // return lambda();
     else {
        p.push_back(scheme());
         vector<Predicate> q = schemeList();
         p.insert(p.end(), q.begin(), q.end());
         return p;
    }
}
vector<Parameter*> Parser::idList(){
    vector<Parameter*> vec;
    if(tokens[currentIndex].getType() == Token::RIGHT_PAREN){
        
        return vec;
        
    } else if(tokens[currentIndex].getType() == Token::EoF) {
        
        throw(tokens[currentIndex]);
        
    } else {
        
        COMMA();
        Param* p = new Param;
        p->setToken(ID());
        vec.push_back(p);
        vector<Parameter*> q = idList();
        vec.insert(vec.end(), q.begin(), q.end());
        return vec;
    }
}
Predicate Parser::fact(){
    Predicate p;
    p.setName(ID());
    p.setType(Predicate::Fact);
    vector<Parameter*> params;
    Param* param = new Param;
    LEFT_PAREN();
    param->setToken(STRING());
    params.push_back(param);
    vector<Parameter*> q = stringList();
    params.insert(params.end(), q.begin(), q.end());
    p.addParam(params);
    RIGHT_PAREN();
    PERIOD();
    return p;
    
}
vector<Predicate> Parser::factList(){
    vector<Predicate> p;
    //if(tokens[currentIndex].getType() == Token::EoF){
        
      //  return lambda();
    //}
    if(/*tokens[currentIndex].getType() == Token::SCHEMES ||*/ tokens[currentIndex].getType() == Token::RULES /*|| tokens[currentIndex].getType() == Token::QUERIES*/) {
        
        return p;
        
    }else if(tokens[currentIndex].getType() == Token::EoF) {
        
        throw(tokens[currentIndex]);
        
    }  else {
        p.push_back(fact());
        vector<Predicate> q = factList();
        p.insert(p.end(), q.begin(), q.end());
        return p;
        
    }
}
vector<Parameter*> Parser::stringList(){
    vector<Parameter*> vec;
    if(tokens[currentIndex].getType() == Token::RIGHT_PAREN){
        
        return vec;
        
    } else if(tokens[currentIndex].getType() == Token::EoF) {
        
        throw(tokens[currentIndex]);
        
    } else {COMMA();
        Param* p = new Param;
        p->setToken(STRING());
        vec.push_back(p);
        vector<Parameter*> q = stringList();
        vec.insert(vec.end(), q.begin(), q.end());
        return vec;
    }
}
Rule Parser::rule(){
    Rule r;
    r.setHeadPred(headPredicate());
    COLON_DASH();
    vector<Predicate> preds;
    preds.push_back(predicate());
    vector<Predicate> q = predicateList();
    preds.insert(preds.end(), q.begin(), q.end());
    r.addPred(preds);
    PERIOD();
    
    return r;
}
vector<Rule> Parser::ruleList(){
    //if(tokens[currentIndex].getType() == Token::EoF){
        
        //return lambda();
        
   // } else
    
    vector<Rule> vec;
    if(/*tokens[currentIndex].getType() == Token::FACTS || tokens[currentIndex].getType() == Token::SCHEMES ||*/ tokens[currentIndex].getType() == Token::QUERIES){
        
        return vec;
        
    } else if(tokens[currentIndex].getType() == Token::EoF) {
        
        throw(tokens[currentIndex]);
        
    } else {
        vec.push_back(rule());
        vector<Rule> r = ruleList();
        vec.insert(vec.end(), r.begin(), r.end());
        return vec;
    }
}

Predicate Parser::headPredicate(){
    Predicate p;
    p.setName(ID());
    vector<Parameter*> params;
    Param* param = new Param;
    LEFT_PAREN();
    param->setToken(ID());
    params.push_back(param);
    vector<Parameter*> q = idList();
    params.insert(params.end(), q.begin(), q.end());
    p.addParam(params);
    RIGHT_PAREN();
    return p;
    
}

Predicate Parser::predicate(){
    Predicate p;
    p.setName(ID());
    LEFT_PAREN();
    vector<Parameter*> params;
    params.push_back(parameter());
    vector<Parameter*> q = parameterList();
    params.insert(params.end(), q.begin(), q.end());
    p.addParam(params);
    RIGHT_PAREN();
    return p;
}

vector<Predicate> Parser::predicateList(){
    vector<Predicate> vec;
    if(tokens[currentIndex].getType() == Token::PERIOD){
        
        return vec;
        
    } else {
        
        COMMA();
        vec.push_back(predicate());
        vector<Predicate> q = predicateList();
        vec.insert(vec.end(),q.begin(),q.end());
        return vec;
    }
}
Parameter* Parser::parameter(){
    Param* p = new Param;
    if(tokens[currentIndex].getType() == Token::LEFT_PAREN){
        
        return expression();
        
    } else if(tokens[currentIndex].getType() == Token::ID){
        
        p->setToken(ID());
        return p;
        
    } else if(tokens[currentIndex].getType() == Token::STRING){
        
        p->setToken(STRING());
        return p;
    }
    //failedTokenInfo = tokens[currentIndex].getType();
    throw(tokens[currentIndex]);
}

vector<Parameter*> Parser::parameterList(){
    vector<Parameter*> vec;
    if(tokens[currentIndex].getType() == Token::RIGHT_PAREN){
        
        return vec;
        
    } else if(tokens[currentIndex].getType() == Token::EoF) {
        
        throw(tokens[currentIndex]);
        
    } else {
        
        COMMA();
        vec.push_back(parameter());
        vector<Parameter*> p = parameterList();
        vec.insert(vec.end(), p.begin(), p.end());
        //cout << vec.size() << endl;
        return vec;
    
    }
}

Parameter* Parser::expression(){
    Expression* e = new Expression;
    LEFT_PAREN();
    e->setLeftParam(parameter());
    e->setOperator(Operator());
    e->setRightParam(parameter());
    RIGHT_PAREN();
    return e;
}

Token Parser::Operator(){
    if(tokens[currentIndex].getType() == Token::MULTIPLY){
        
        return MULTIPLY();
        
    } else if(tokens[currentIndex].getType() == Token::ADD) {
        return ADD();
    }
    //cout << "Operator Failed" << endl << tokens[currentIndex].toString() << endl << "Current Index = " << currentIndex << endl;
    //failedTokenInfo = tokens[currentIndex].toString(); return false;
    throw(tokens[currentIndex]);
}

Predicate Parser::query(){
    Predicate p = predicate();
    p.setType(Predicate::Query);
    Q_MARK();
    return p;
}
vector<Predicate> Parser::queryList(){
    vector<Predicate> vec;
    if(tokens[currentIndex].getType() == Token::EoF){
        
        return vec;
        
   // } else if(tokens[currentIndex].getType() == Token::FACTS || tokens[currentIndex].getType() == Token::SCHEMES || tokens[currentIndex].getType() == Token::RULES){
        
     //   return lambda();
        
    } else {
        
        vec.push_back(query());
        vector<Predicate> q = queryList();
        vec.insert(vec.end(), q.begin(), q.end());
        return vec;
    
    }
}

Token Parser::COMMA(){
    if(tokens[currentIndex].getType() == Token::COMMA){
        currentIndex++;
        return tokens[currentIndex-1];
    }
    //cout << "COMMA Failed" << endl << tokens[currentIndex].toString() << endl << "Current Index = " << currentIndex << endl;
    //failedTokenInfo = tokens[currentIndex].toString(); return false;
    throw(tokens[currentIndex]);
}
Token Parser::PERIOD(){
    
    if(tokens[currentIndex].getType() == Token::PERIOD){
        currentIndex++;
        return tokens[currentIndex-1];
    }
    //cout << "PERIOD Failed" << endl << tokens[currentIndex].toString() << endl << "Current Index = " << currentIndex << endl;
    //failedTokenInfo = tokens[currentIndex].toString(); return false;
    throw(tokens[currentIndex]);
}
Token Parser::Q_MARK(){
    if(tokens[currentIndex].getType() == Token::Q_MARK){
        currentIndex++;
        return tokens[currentIndex-1];
    }
    //cout << "Q_MARK Failed" << endl << tokens[currentIndex].toString() << endl << "Current Index = " << currentIndex << endl;
    //failedTokenInfo = tokens[currentIndex].toString(); return false;
    throw(tokens[currentIndex]);
}
Token Parser::LEFT_PAREN(){
    if(tokens[currentIndex].getType() == Token::LEFT_PAREN){
        currentIndex++;
        return tokens[currentIndex-1];
    }
    //cout << "LEFT_PAREN" << endl;
    //failedTokenInfo = tokens[currentIndex].toString(); return false;
    throw(tokens[currentIndex]);
}
Token Parser::RIGHT_PAREN(){
    if(tokens[currentIndex].getType() == Token::RIGHT_PAREN){
        currentIndex++;
        return tokens[currentIndex-1];
    }
    //cout << "LEFT_PAREN" << endl;
    //failedTokenInfo = tokens[currentIndex].toString(); return false;
    throw(tokens[currentIndex]);
}

Token Parser::COLON(){
    if(tokens[currentIndex].getType() == Token::COLON){
        currentIndex++;
        return tokens[currentIndex-1];
    }
    //cout << "LEFT_PAREN" << endl;
    //failedTokenInfo = tokens[currentIndex].toString(); return false;
    throw(tokens[currentIndex]);
}
Token Parser::COLON_DASH(){
    if(tokens[currentIndex].getType() == Token::COLON_DASH){
        currentIndex++;
        return tokens[currentIndex-1];
    }
    //cout << "LEFT_PAREN" << endl;
    //failedTokenInfo = tokens[currentIndex].toString(); return false;
    throw(tokens[currentIndex]);
}
Token Parser::MULTIPLY(){
    if(tokens[currentIndex].getType() == Token::MULTIPLY){
        currentIndex++;
        return tokens[currentIndex-1];
    }
    //cout << "LEFT_PAREN" << endl;
    //failedTokenInfo = tokens[currentIndex].toString(); return false;
    throw(tokens[currentIndex]);
}

Token Parser::ADD(){
    if(tokens[currentIndex].getType() == Token::ADD){
        currentIndex++;
        return tokens[currentIndex-1];
    }
    //cout << "LEFT_PAREN" << endl;
    //failedTokenInfo = tokens[currentIndex].toString(); return false;
    throw(tokens[currentIndex]);
}
Token Parser::SCHEMES(){
    if(tokens[currentIndex].getType() == Token::SCHEMES){
        currentIndex++;
        return tokens[currentIndex-1];
    }
    //cout << "LEFT_PAREN" << endl;
    //failedTokenInfo = tokens[currentIndex].toString(); return false;
    throw(tokens[currentIndex]);
}
Token Parser::FACTS(){
    if(tokens[currentIndex].getType() == Token::FACTS){
        currentIndex++;
        return tokens[currentIndex-1];
    }
    //cout << "LEFT_PAREN" << endl;
    //failedTokenInfo = tokens[currentIndex].toString(); return false;
    throw(tokens[currentIndex]);
}

Token Parser::RULES(){
    if(tokens[currentIndex].getType() == Token::RULES){
        currentIndex++;
        return tokens[currentIndex-1];
    }
    //cout << "LEFT_PAREN" << endl;
    //failedTokenInfo = tokens[currentIndex].toString(); return false;
    throw(tokens[currentIndex]);
}

Token Parser::QUERIES(){
    if(tokens[currentIndex].getType() == Token::QUERIES){
        currentIndex++;
        return tokens[currentIndex-1];
    }
    //cout << "LEFT_PAREN" << endl;
    //failedTokenInfo = tokens[currentIndex].toString(); return false;
    throw(tokens[currentIndex]);
}
Token Parser::ID(){
    ////cout << endl << currentIndex << endl << tokens[currentIndex].toString() << endl;
    if(tokens[currentIndex].getType() == Token::ID){
        currentIndex++;
        return tokens[currentIndex-1];
    }
    //cout << "ID Failed" << endl << tokens[currentIndex].toString() << endl << "Current Index = " << currentIndex << endl;
    //failedTokenInfo = tokens[currentIndex].toString(); return false;
    throw(tokens[currentIndex]);
}
Token Parser::STRING(){
    if(tokens[currentIndex].getType() == Token::STRING){
        currentIndex++;
        return tokens[currentIndex-1];
    }
    //cout << "STRING Failed" << endl << tokens[currentIndex].toString() << endl << "Current Index = " << currentIndex << endl;
    //failedTokenInfo = tokens[currentIndex].toString(); return false;
    throw(tokens[currentIndex]);
}


void Parser::createVec(vector<Token> finalTokens){
    for(int i = 0; i < finalTokens.size(); i++){
        if (finalTokens[i].getType() != Token::COMMENT && finalTokens[i].getType() != Token::ENDLINE && finalTokens[i].getType() != Token::WHITESPACE){
            tokens.push_back(finalTokens[i]);
        }
    }
    //cout << endl << endl;
    for(int i = 0; i < tokens.size(); i++){
        //cout << tokens[i].toString() << endl;
    }
    
}

void Parser::printFailed(){
    cout << endl << "\t" << failedTokenInfo;
}
