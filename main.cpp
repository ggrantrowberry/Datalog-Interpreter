//
//  main.cpp
//  P4 Datalog Interpreter
//
//  Created by Grant Rowberry on 11/10/16.
//  Copyright © 2016 Grant Rowberry. All rights reserved.
//

#include <iostream>
#include "Lexer.hpp"
#include "Token.hpp"
#include "Parser.hpp"
#include "Relation.hpp"

using namespace std;

/*void test1(){ //Tests to see if a basic union of two union compatible relations actually perform the union.
    Relation* r = new Relation;
    Relation* s = new Relation;
    vector<string> att1 = {"A","B","C"};
    r->addAttVec(att1);
    vector<string> att2 = {"A","B","C"};
    s->addAttVec(att2);
    vector<string> row11 = {"a","b","c"};
    vector<string> row12 = {"b","c","d"};
    vector<string> row13 = {"b","b","b"};
    vector<string> row21 = {"e","f","g"};
    vector<string> row22 = {"f","f","f"};
    vector<vector<string>> facts1 = {row11,row12,row13};
    r->addFactsVec(facts1);
    vector<vector<string>> facts2 = {row21,row22};
    s->addFactsVec(facts2);
    Relation* n = r->relUnion(s);
    n->printRelation();
}
void test2(){ //Tests to see if a union will catch the fact that it's not union compatible.
    Relation* r = new Relation;
    Relation* s = new Relation;
    vector<string> att1 = {"A","B","C"};
    r->addAttVec(att1);
    vector<string> att2 = {"A","C","C"};
    s->addAttVec(att2);
    vector<string> row11 = {"a","b","c"};
    vector<string> row12 = {"b","c","d"};
    vector<string> row13 = {"b","b","b"};
    vector<string> row21 = {"e","f","g"};
    vector<string> row22 = {"f","f","f"};
    vector<vector<string>> facts1 = {row11,row12,row13};
    r->addFactsVec(facts1);
    vector<vector<string>> facts2 = {row21,row22};
    s->addFactsVec(facts2);
    Relation* n = r->relUnion(s);
    n->printRelation();
}

void test3(){ //Tests to see if a simple natural join works.
    Relation* r = new Relation;
    Relation* s = new Relation;
    vector<string> att1 = {"A","B","C"};
    r->addAttVec(att1);
    vector<string> att2 = {"A","C","D"};
    s->addAttVec(att2);
    vector<string> row11 = {"a","b","y"};
    //vector<string> row12 = {"b","c","d"};
    vector<string> row13 = {"b","b","b"};
    //vector<string> row21 = {"e","f","g"};
    //vector<string> row22 = {"f","f","f"};
    vector<string> row23 = {"a","y","x"};
    vector<vector<string>> facts1 = {row11,row13};
    r->addFactsVec(facts1);
    vector<vector<string>> facts2 = {row23};
    s->addFactsVec(facts2);
    Relation* n = r->relNaturalJoin(s);
    n->printRelation();
}
void test4(){ //This tests a more complicated Natural Join. It should output two rows.
    Relation* r = new Relation;
    Relation* s = new Relation;
    vector<string> att1 = {"A","B","C"};
    r->addAttVec(att1);
    vector<string> att2 = {"A","C","D"};
    s->addAttVec(att2);
    vector<string> row11 = {"a","b","y"};
    vector<string> row12 = {"b","c","d"};
    vector<string> row13 = {"b","b","b"};
    
    vector<string> row21 = {"e","f","g"};
    vector<string> row22 = {"f","f","f"};
    vector<string> row23 = {"a","y","x"};
    vector<string> row24 = {"b","d","z"};
    vector<vector<string>> facts1 = {row11,row12};
    r->addFactsVec(facts1);
    vector<vector<string>> facts2 = {row23,row24};
    s->addFactsVec(facts2);
    Relation* n = r->relNaturalJoin(s);
    n->printRelation();
}

void test5(){ //Test a natural join with two relations with different numbers of attributes
    Relation* r = new Relation;
    Relation* s = new Relation;
    vector<string> att1 = {"A","B","C"};
    r->addAttVec(att1);
    vector<string> att2 = {"A","D","Y","Z"};
    s->addAttVec(att2);
    vector<string> row11 = {"a","b","y"};
    vector<string> row12 = {"b","c","d"};
    vector<string> row13 = {"b","b","b"};
    
    vector<string> row21 = {"e","g","x","z"};
    vector<string> row22 = {"f","f","a","d"};
    vector<string> row23 = {"a","x","c","e"};
    vector<string> row24 = {"b","z","a","p"};
    vector<vector<string>> facts1 = {row11,row12,row13};
    r->addFactsVec(facts1);
    vector<vector<string>> facts2 = {row23,row24,row21,row22};
    s->addFactsVec(facts2);
    Relation* n = r->relNaturalJoin(s);
    n->printRelation();
}

void test6(){ //Test natural join where there are multiple of the same elements in a row.
    Relation* r = new Relation;
    Relation* s = new Relation;
    vector<string> att1 = {"A","B","C"};
    r->addAttVec(att1);
    vector<string> att2 = {"A","D","Y","Z"};
    s->addAttVec(att2);
    vector<string> row11 = {"a","b","y"};
    vector<string> row12 = {"b","c","d"};
    vector<string> row13 = {"b","b","b"};
    
    vector<string> row21 = {"e","g","x","z"};
    vector<string> row22 = {"f","f","a","d"};
    vector<string> row23 = {"a","x","c","e"};
    vector<string> row24 = {"b","z","b","b"};
    vector<vector<string>> facts1 = {row11,row12};
    r->addFactsVec(facts1);
    vector<vector<string>> facts2 = {row23,row24};
    s->addFactsVec(facts2);
    Relation* n = r->relNaturalJoin(s);
    n->printRelation();
}

void test7(){ //Tests cross product.
    Relation* r = new Relation;
    Relation* s = new Relation;
    vector<string> att1 = {"A","B","C"};
    r->addAttVec(att1);
    vector<string> att2 = {"E","F","G","H"};
    s->addAttVec(att2);
    vector<string> row11 = {"a","b","y"};
    vector<string> row12 = {"b","c","d"};
    vector<string> row13 = {"b","b","b"};
    
    vector<string> row21 = {"e","g","x","z"};
    vector<string> row22 = {"f","f","a","d"};
    vector<string> row23 = {"a","x","c","e"};
    vector<string> row24 = {"b","z","b","b"};
    vector<vector<string>> facts1 = {row11,row12};
    r->addFactsVec(facts1);
    vector<vector<string>> facts2 = {row23,row24, row21, row22};
    s->addFactsVec(facts2);
    Relation* n = r->relNaturalJoin(s);
    n->printRelation();
}
void test8(){ //Tests much more complex natural join.
    Relation* r = new Relation;
    Relation* s = new Relation;
    vector<string> att1 = {"B","C","A"};
    r->addAttVec(att1);
    vector<string> att2 = {"A","F","B","C"};
    s->addAttVec(att2);
    vector<string> row11 = {"a","b","y"};
    vector<string> row12 = {"b","c","d"};
    vector<string> row13 = {"b","b","b"};
    
    vector<string> row21 = {"e","g","x","z"};
    vector<string> row22 = {"f","f","a","d"};
    vector<string> row23 = {"a","x","c","e"};
    vector<string> row24 = {"b","z","b","b"};
    vector<string> row25 = {"y","x","a","b"};
    vector<vector<string>> facts1 = {row11,row12, row13};
    r->addFactsVec(facts1);
    vector<vector<string>> facts2 = {row23,row24, row21, row22, row25};
    s->addFactsVec(facts2);
    Relation* n = r->relNaturalJoin(s);
    n->printRelation();
}
void test9(){ //Tests a natural join that only has one column
    Relation* r = new Relation;
    Relation* s = new Relation;
    vector<string> att1 = {"B"};
    r->addAttVec(att1);
    vector<string> att2 = {"A","F","B","C"};
    s->addAttVec(att2);
    vector<string> row11 = {"a"};
    vector<string> row12 = {"b"};
    vector<string> row13 = {"b"};
    
    vector<string> row21 = {"e","g","x","z"};
    vector<string> row22 = {"f","f","a","d"};
    vector<string> row23 = {"a","x","b","e"};
    vector<string> row24 = {"b","z","b","b"};
    vector<string> row25 = {"y","x","a","b"};
    vector<vector<string>> facts1 = {row11,row12, row13};
    r->addFactsVec(facts1);
    vector<vector<string>> facts2 = {row23,row24, row21, row22, row25};
    s->addFactsVec(facts2);
    Relation* n = r->relNaturalJoin(s);
    n->printRelation();
}

void test10(){ //Tests a cross product with one relation that has only one column
    Relation* r = new Relation;
    Relation* s = new Relation;
    vector<string> att1 = {"D"};
    r->addAttVec(att1);
    vector<string> att2 = {"A","F","B","C"};
    s->addAttVec(att2);
    vector<string> row11 = {"a"};
    vector<string> row12 = {"b"};
    vector<string> row13 = {"b"};
    
    vector<string> row21 = {"e","g","x","z"};
    vector<string> row22 = {"f","f","a","d"};
    vector<string> row23 = {"a","x","b","e"};
    vector<string> row24 = {"b","z","b","b"};
    vector<string> row25 = {"y","x","a","b"};
    vector<vector<string>> facts1 = {row11,row12,row13};
    r->addFactsVec(facts1);
    vector<vector<string>> facts2 = {row23,row24, row21, row22, row25};
    s->addFactsVec(facts2);
    Relation* n = r->relNaturalJoin(s);
    n->printRelation();
}*/

int main(int argc, const char * argv[]) {
    Lexer lex;
    Parser parse;
    //lex.readFile(argv[1]);
    
    lex.readFile("/Users/GrantRowberry/Documents/School/Fall 2016/CS 236/Projects/P4 Datalog Interpreter/P4 Datalog Interpreter/ex42.txt");
    lex.run();    //lex.print();
    
    parse.createVec(lex.getTokens());
    DatalogProgram dlp = parse.dataLogProgram();
    dlp.answerQueries();
    
    
    
    
    return 0;
}
