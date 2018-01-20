//
//  Node.cpp
//  Graphs
//
//  Created by Grant Rowberry on 11/29/16.
//  Copyright © 2016 Grant Rowberry. All rights reserved.
//

#include "Node.hpp"

bool Node::getVisited(){
    return visited;
}

void Node::addEdge(Node* n){
    edges.push_back(n);
}

void Node::clearEdges(){
    edges.clear();
}

vector<Node*> Node::getEdges(){
    return edges;
}

void Node::setVisited(bool b){
    visited = b;
}

string Node::getName(){
    return name;
}

string Node::toPrint(){
    string s;
    s+= "R";
    s+= name;
    s+= ":";
    stringstream ss;
    vector<int> edgeint;
    for (int i = 0; i < edges.size(); i++){
        edgeint.push_back(stoi(edges[i]->getName()));
    }
    sort(edgeint.begin(),edgeint.end());
    for (int i = 0; i < edgeint.size(); i++){
        ss << "R";
        ss << edgeint[i];
        if(i < edgeint.size()-1){
            ss << ",";
        }
    }
    s+= ss.str();
    return s;
}
void Node::setName(string s){
    name = s;
    convertIntName();
}

void Node::addReverseEdge(Node* n){
    reverseEdges.push_back(n);
}

vector<Node*> Node::getReverseEdges(){
    return reverseEdges;
}

string Node::toPrintReverse(){
    string s;
    s+= name;
    s+= ":";
    for (int i = 0; i < reverseEdges.size(); i++){
        s += reverseEdges[i]->getName();
        s += ",";
    }
    return s;
}

void Node::setRule(Rule r){
    rule = r;
}

Rule Node::getRule(){
    return rule;
}

void Node::convertIntName(){
    intName = stoi(name);
}

int Node::getIntName(){
    return intName;
}
bool Node::operator < (const Node*& other) {
    return intName < other->intName;
}

