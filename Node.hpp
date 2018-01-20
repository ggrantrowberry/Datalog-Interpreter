//
//  Node.hpp
//  Graphs
//
//  Created by Grant Rowberry on 11/29/16.
//  Copyright © 2016 Grant Rowberry. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp
#include <vector>
#include <string>
#include <stdio.h>
#include "Rule.hpp"
#include <algorithm>
using namespace std;

class Node {
public:
    bool getVisited();
    void addEdge(Node* n);
    void clearEdges();
    vector<Node*> getEdges();
    void setVisited(bool b);
    string getName();
    string toPrint();
    void setName(string s);
    void addReverseEdge(Node* n);
    vector<Node*> getReverseEdges();
    string toPrintReverse();
    void setRule(Rule r);
    Rule getRule();
    void convertIntName();
    int getIntName();
    bool operator < (const Node*&);
private:
    string name;
    int intName;
    vector<Node*> edges;
    bool visited = false;
    vector<Node*> reverseEdges;
    Rule rule;
};

#endif /* Node_hpp */
