//
//  RDB.cpp
//  P3 Relational Database
//
//  Created by Grant Rowberry on 10/24/16.
//  Copyright © 2016 Grant Rowberry. All rights reserved.
//

#include "RDB.hpp"

RDB::RDB(vector<Predicate> Schemes, vector<Predicate> Facts, vector<Predicate> Queries, vector<Rule> Rules){
    schemes = Schemes;
    facts = Facts;
    queries = Queries;
    rules = Rules;
}

void RDB::analyzeSchemes(){
    for(int i = 0; i < schemes.size(); i++){
        Relation* r = new Relation;
        
        r -> setName(schemes[i].getName());
        schemeNames.push_back(schemes[i].getName()); //compiles a list of all the names of the schemes to be checked later
        vector<string> v = schemes[i].getSParamContent();
        for(int j = 0; j < v.size(); j++){
            r-> addAttribute(v[j]);
        }
        relations.push_back(r);
        
    }
    
}
void RDB::compileFacts(){
    for(int i = 0; i < facts.size(); i++){
        long int index = find(schemeNames.begin(), schemeNames.end(), facts[i].getName()) - schemeNames.begin();
        if(index != schemeNames.size()){
            relations[index]->addFacts(facts[i].getSParamContent());
        }
    }
}
void RDB::answerQueries(){
    string s;
    Relation* r;
    s += "Query Evaluation\n";
    for(int i = 0; i < queries.size(); i++){
        r = singleQuery(queries[i]);
        s += r->getForPrinting();
    }
    cout << s;
}

void RDB::evaluateRules(){
    //bool keepGoing = true;
    
    cout << "Schemes populated after " << ruleHelper(0) << " passes through the Rules." << endl;
    
    
}

int RDB::ruleHelper(int count){
    int changeCount = 1;
    while(changeCount != 0){
        changeCount = 0;
        for(int i = 0; i < rules.size(); i++){
            if(singleRule(rules[i])){
                changeCount++;
            }
        }
        count++;
    }
   
    return count;
}

bool RDB::singleRule(Rule rule){
    vector<Predicate> preds = rule.getPredicates();
    vector<Relation*> inter;
    Relation* finalRelation = nullptr;
    setRelationNames();
    for(int i = 0; i < preds.size(); i++){

        inter.push_back(singleQuery(preds[i]));
    }
    for(int i = 0; i < inter.size(); i++){
        if(i == 0){
            finalRelation = inter[i];
        } else {
            finalRelation = finalRelation->relNaturalJoin(inter[i]);
            //finalRelation->printRelation();
        }
    }
    finalRelation = finalRelation->relProject(getIndices(rule,finalRelation));
    //finalRelation->printRelation();
    finalRelation->setName(rule.getRuleName());
    long int relation = (find(relationNames.begin(), relationNames.end(), finalRelation->getName())-relationNames.begin());
    finalRelation->addAttVec(relations[relation]->getAtt());
    //finalRelation->printRelation();
     long int before = relations[relation]->getFactsSize();
    //relations[relation]->printRelation();
    relations[relation] = relations[relation]->relUnion(finalRelation);
    long int after = relations[relation]->getFactsSize();
    //relations[relation]->printRelation();
    if (before == after){
        return false;
    } else {
        return true;
    }
}


vector<long int> RDB::getIndices(Rule rule, Relation* r){
    vector<string> targetAttributes = rule.getHeadPredAttributes();
    vector<string> relationAttributes = r->getAtt();
    vector<long int> indices;
    for (int i = 0; i < targetAttributes.size(); i++){
        long int index = find(relationAttributes.begin(),relationAttributes.end(),targetAttributes[i]) - relationAttributes.begin();
        if(index != relationAttributes.size()){
            indices.push_back(index);
        }
    }
    return indices;
}

void RDB::setRelationNames(){
    vector<string> names;
    for(int i = 0; i < relations.size(); i++){
        names.push_back(relations[i]->getName());
    }
    relationNames = names;
}








Relation*  RDB::singleQuery(Predicate p){
    long int index = find(schemeNames.begin(), schemeNames.end(), p.getName()) - schemeNames.begin(); //find the right relation to perform the query on.
    vector<Token> tokens = p.getParamTokens();
      vector<string> uniqueAttribute;
        vector<int> indices;
    vector<vector<string>> facts = relations[index]->getFacts();
    for(int i = 0; i < tokens.size(); i++){ // for iterating through the query
        if (tokens[i].getType() == Token::ID){
            long int mapIndex = find(uniqueAttribute.begin(), uniqueAttribute.end(), tokens[i].getContent()) - uniqueAttribute.begin();
            if(mapIndex < uniqueAttribute.size()){
                //relations[index] -> testPrint(facts);
                facts = relations[index]->sameSelect(mapIndex, i, facts);
                //relations[index] -> testPrint(facts);
            }
            else {
                uniqueAttribute.push_back(tokens[i].getContent());
                indices.push_back(i);
            }
        } else {
            facts = relations[index] -> select(tokens[i].getContent(), i, facts);
        }
    }

    facts = relations[index]->project(indices, facts);
    //relations[index] -> testPrint(facts);
    sort (facts.begin(), facts.end());
    facts.erase(unique (facts.begin(), facts.end()), facts.end());
    
    Relation* R = new Relation;
    R->addAttVec(uniqueAttribute);
    R->addFactsVec(facts);
    R->setName(p.getName());
    string s;
    s += p.toString();
    s += toPrint(R);
    R->setForPrinting(s);
    //R->printRelation();
    return R;
    
}

string RDB::toPrint(Relation* r){
    stringstream sstream;
    vector<vector<string>> facts = r->getFacts();
    vector<string> att = r->getAtt();
    if(facts.size() != 0){
        if (att.size() == 0){
            sstream << " Yes(" << facts.size() << ")";
        } else {
            sstream << " Yes(" << facts.size() << ")" << endl;
        }
        for(int i = 0; i < facts.size(); i++){
            if(att.size() != 0){
                sstream <<"  ";}
            for(int j = 0; j < facts[i].size(); j++){
                
                if(j != facts[i].size()-1){
                    sstream << att[j] << "=" << facts[i][j] << ", ";
                } else {
                    sstream << att[j] << "=" << facts[i][j];
                }
                
            }
            sstream << endl;
        }
    } else {
        sstream <<" No" << endl;
    }
    return sstream.str();
}

void RDB::run(){
    analyzeSchemes();
    compileFacts();
    //evaluateRules();
    evaluateOptimizedRules();
    answerQueries();
}

void RDB::evaluateOptimizedRules(){
    vector<vector<Node*>> scc = createGraph();
    sccSort(scc);
    evaluateSCC(scc);
}

vector<vector<Node*>> RDB::createGraph(){
    Graph g;
    vector<string> ruleNames;
    vector<Node*> nodes;
    for(int i = 0; i < rules.size(); i++){
        ruleNames.push_back(rules[i].getRuleName());
        stringstream s;
        s << i;
        Node* x = new Node;
        x->setName(s.str());
        x->setRule(rules[i]);
        nodes.push_back(x);
    }
    
    vector<Node*> fullNodes = nodeFiller(nodes, ruleNames);
    for(int i = 0; i < fullNodes.size(); i++){
        g.addVertex(fullNodes[i]);
    }
    g.execute();
    g.printGraph();
    return g.getSCC();
    
}

vector<Node*> RDB::nodeFiller(vector<Node*> nodes, vector<string> ruleNames){
    vector<Node*> fullNodes;
    vector<int> indexes;
    for(int i = 0; i < rules.size(); i++){
        vector<Predicate> rulePreds = rules[i].getPredicates();
        for(int j = 0; j < rulePreds.size(); j++){
            vector<int> indexes = indexFinder(ruleNames, rulePreds[j].getName());
            for(int k = 0; k < indexes.size(); k++){
                if(!nodeChecker(nodes[i], nodes[indexes[k]])){
                nodes[i]->addEdge(nodes[indexes[k]]);
                }
            }
        }
        fullNodes.push_back(nodes[i]);
    }
    return fullNodes;

}

bool RDB::nodeChecker(Node *toBeChecked, Node *toCheck){
    vector<Node*> edges = toBeChecked->getEdges();
    if(find(edges.begin(), edges.end(), toCheck) - edges.begin() < edges.size()){
        return true;
    } else {
        return false;
    }
}


vector<int> RDB::indexFinder(vector<string> ruleNames, string nameToFind){
    vector<int> indexes;
    for(int i = 0; i < ruleNames.size(); i++){
        if(nameToFind == ruleNames[i]){
            indexes.push_back(i);
        }
    }
    return indexes;
}

void RDB::evaluateSCC(vector<vector<Node*>> scc){
    vector<int> passes;
    for(int i = 0; i < scc.size(); i++){
        int changeCount = 1;
        int count = 0;
        if(isSinglePass(scc[i])){
            singleRule(scc[i][0]->getRule());
            passes.push_back(1);
        } else {
            
            while(changeCount !=0){
                changeCount = 0;

                for(int j = 0; j < scc[i].size(); j++){
                    if(singleRule(scc[i][j]->getRule())){
                        changeCount++;

                    }
                }
                count++;
                
            }

            passes.push_back(count);
        }
    }
    printRuleEvaluation(passes, scc);
    
}

void RDB::printRuleEvaluation(vector<int> passes, vector<vector<Node *>> scc){
    stringstream s;
    s << "\nRule Evaluation\n";
    for(int i = 0; i < scc.size(); i++){
        s << passes[i];
        s << " passes: ";
        vector<int> sccNames;
        for(int j = 0; j < scc[i].size(); j++){
    
            sccNames.push_back(stoi(scc[i][j]->getName()));
        }
        
        sort(sccNames.begin(),sccNames.end());
        
        for(int j = 0; j < sccNames.size(); j++){
            s << "R";
            s << sccNames[j];
            if(j != scc[i].size()-1){
                s << ",";
            }
        }
        s << endl;
    }
    s << endl;
    cout << s.str();
}

void RDB::printSCC(vector<vector<Node *> > scc){
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
    cout << endl;
}


bool RDB::isSinglePass(vector<Node *> oneSCC){
    if(oneSCC.size() == 1){
        vector<Node*> edges = oneSCC[0]->getEdges();
        if(find(edges.begin(), edges.end(), oneSCC[0]) - edges.begin() < edges.size()){
            return false;
        } else {
            return true;
        }
    }
    return false;
}

void RDB::sccSort(vector<vector<Node*>>& scc){
    for(int i = 0; i < scc.size(); i++){
        sort(scc[i].begin(),scc[i].end());
    }
}
