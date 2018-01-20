//
//  Graph.cpp
//  Graphs
//
//  Created by Grant Rowberry on 11/29/16.
//  Copyright © 2016 Grant Rowberry. All rights reserved.
//

#include "Graph.hpp"

void Graph::printPotNums(){
    stack<Node*> copy = potNums;
    for(int i = 0; i < potNums.size(); i++){
        cout << copy.top()->getName() << endl;
        copy.pop();
    }
}

void Graph::addVertex(Node* n){
    vertices.push_back(n);
}

void Graph::execute(){
    //printGraph();
    Graph* g = reverseGraph();
    //cout <<"-----" << endl;
   // g->printReverseGraph();
    pot(g);
   // cout << potNums.size() << endl;
   // printPotNums();
    dfs();
   // printSCC();
}

Graph* Graph::reverseGraph(){
    Graph* g = new Graph;
    vector<Node*> v = vertices;
   /* for(int i = 0; i < vertices.size(); i++){
        Node* n = vertices[i];
        v.push_back(n);
    }*/
    for (int i = 0; i < vertices.size(); i++){
        vector<Node*> edges = vertices[i]->getEdges();
        for (int j = 0; j < edges.size(); j++){
           long int pos = find(v.begin(), v.end(), edges[j]) - v.begin();
            Node* p = vertices[i];
            v[pos]->addReverseEdge(p);
            
        }
    }
    g->setVertices(v);
    return g;
}
vector<Node*> Graph::getVertices(){
    return vertices;
}



void Graph::setVertices(vector<Node*> n){
    vertices = n;
}

void Graph::pot(Graph* g){
    vector<Node*> v = g->getVertices();
    for(int i = 0; i < v.size(); i++){
        if (!v[i]->getVisited()){
            v[i]->setVisited(true);
            potHelp(v[i]);
            potNums.push(v[i]);
            
        }
    }
    
}

void Graph::potHelp(Node* n){
    vector<Node*> edges = n->getReverseEdges();
    if(edges.size() == 0){
        potNums.push(n);
    } else {
        for (int i = 0; i < edges.size(); i++){
            if(!edges[i]->getVisited()){
                edges[i]->setVisited(true);
                potHelp(edges[i]);
                potNums.push(edges[i]);
            }
        }
    }
}

void Graph::dfs(){
    //cout << "-----" << endl;
    for (int i = 0; i < vertices.size(); i++){
        vertices[i]->setVisited(false);
    }
    while (!potNums.empty()){
        Node* n = potNums.top();
        potNums.pop();
        if(!n->getVisited()){
            n->setVisited(true);
           scc.push_back(dfsHelp(n));
        }
    }
}

vector<Node*> Graph::dfsHelp(Node* n){
    vector<Node*> v;
    //cout << n->getName() << endl;
    vector<Node*> edges = n->getEdges();
    bool allvisited = true;
 for(int i = 0; i < edges.size(); i++){
        if(edges[i]->getVisited()){
           allvisited = allvisited && true;
        } else {
            allvisited = false;
        }
    }
    if(edges.size() == 0){
        v.push_back(n);
    } else if(allvisited)
        {
            v.push_back(n);

        } else{ for(int i = 0; i < edges.size(); i++){
        if (!edges[i]->getVisited()){
            edges[i]->setVisited(true);
            vector<Node*> vec = dfsHelp(edges[i]);
            v.insert(v.end(), vec.begin(),vec.end());
        
        }//else if(allvisited){
          // v.push_back(n);
        //}
    }
            v.push_back(n);
    }
    
    
    return v;
}

void Graph::printSCC(){
    string s;
    //cout << scc.size() << endl;
    for(int i = 0; i < scc.size(); i++){
        s+= "{";
        for(int j = 0; j < scc[i].size(); j++){
            if(j == scc[i].size()-1){
                s+=scc[i][j]->getName();
            } else {
                s+=scc[i][j]->getName();
                s+=",";
            }
            
        }
        if(i == scc.size()-1){
            s+="}\n";
            
        } else {
            s+="},";
        }
    }
    cout << s;
}


void Graph::printGraph(){
    string s;
    s += "Dependency Graph\n";
    for(int i = 0; i < vertices.size(); i++){
        s+= vertices[i]->toPrint();
        s+= "\n";
    }
    cout << s;
}
void Graph::printReverseGraph(){
    string s;
    for(int i = 0; i < vertices.size(); i++){
        s+= vertices[i]->toPrintReverse();
        s+= "\n";
    }
    cout << s;
}

vector<vector<Node*>> Graph::getSCC(){
    return scc;
}

