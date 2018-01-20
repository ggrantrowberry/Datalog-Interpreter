//
//  Relation.hpp
//  P3 Relational Database
//
//  Created by Grant Rowberry on 10/24/16.
//  Copyright © 2016 Grant Rowberry. All rights reserved.
//
#pragma once
#ifndef Relation_hpp
#define Relation_hpp

#include <stdio.h>
#include <stdio.h>
#include "Token.hpp"
#include "Predicate.hpp"
#include "Rule.hpp"
#include "Lexer.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <set>
#include <array>
#include <algorithm>
using namespace std;

class Relation {
public:
    vector<vector<string>> select(string s, int i, vector<vector<string>> v);
    vector<vector<string>> rename(vector<string> s, vector<vector<string>> v);
    vector<vector<string>> project(vector<int> indices, vector<vector<string>> v);
    vector<vector<string>> sameSelect(long int index1, int index2, vector<vector<string>> v);
    //void testRun();
    void testPrint(vector<vector<string>>);
    void setName(string s);
    void addAttribute(string s);
    void addFacts(vector<string> v);
    vector<vector<string>> getFacts();
    void addFactsVec(vector<vector<string>> v);
    void addAttVec(vector<string> v);
    vector<string> getAtt();
    void changeEmpty(bool b);
    Relation* relUnion(Relation* r);
    Relation* relNaturalJoin(Relation* r);
    long int findAtt(string s);
    long int getAttSize();
    vector<vector<string>> compareRows(vector<string> rowA, vector<pair<int,int>> headerPairs);
    void printRelation();
    void sortFacts();
    void printOneAtt(int i);
    vector<string> uniqueRow(vector<string> rows, vector<int>indices);
    vector<vector<string>> cross(vector<string> rowA);
    vector<vector<string>> doCross(vector<vector<string>> rows);
    void setForPrinting(string s);
    string getForPrinting();
    Relation* relSelect();
    Relation* relProject(vector<long int> indices);
    string getName();
    long int getFactsSize();
private:
    
    string name;
    vector<string> attributes;
    vector<vector<string>> relationFacts;
    bool isEmpty;
    string forPrinting;
    
};




#endif /* Relation_hpp */
