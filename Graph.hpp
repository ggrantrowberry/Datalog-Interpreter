//
//  Graph.hpp
//  Graphs
//
//  Created by Grant Rowberry on 11/29/16.
//  Copyright © 2016 Grant Rowberry. All rights reserved.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <stdio.h>
#include <stack>
#include "Node.hpp"
#include <iostream>
#include <string>
#include "Rule.hpp"
#include <algorithm>
using namespace std;

class Graph{
public:
    Graph* reverseGraph();
    void pot(Graph* g);
    void dfs();
    vector<Node*> dfsHelp(Node* n);
    void addVertex(Node* n);
    void execute();
    void printGraph();
    void printSCC();
    void setVertices(vector<Node*> v);
    void potHelp(Node* n);
    vector<Node*> getVertices();
    void printReverseGraph();
    void printPotNums();
    void setRule(Rule* r);
    vector<vector<Node*>> getSCC();
private:
    stack<Node*> potNums;
    vector<Node*> vertices;
    vector<vector<Node*>> scc;
    
    
    
    
    
};
#endif /* Graph_hpp */
