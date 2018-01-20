//
//  Relation.cpp
//  P3 Relational Database
//
//  Created by Grant Rowberry on 10/24/16.
//  Copyright © 2016 Grant Rowberry. All rights reserved.
//

#include "Relation.hpp"

struct target_less
{
    template<class It>
    bool operator()(It const &a, It const &b) const { return *a < *b; }
};
struct target_equal
{
    template<class It>
    bool operator()(It const &a, It const &b) const { return *a == *b; }
};
template<class It> It uniquify(It begin, It const end)
{
    std::vector<It> v;
    v.reserve(static_cast<size_t>(std::distance(begin, end)));
    for (It i = begin; i != end; ++i)
    { v.push_back(i); }
    std::sort(v.begin(), v.end(), target_less());
    v.erase(std::unique(v.begin(), v.end(), target_equal()), v.end());
    std::sort(v.begin(), v.end());
    size_t j = 0;
    for (It i = begin; i != end && j != v.size(); ++i)
    {
        if (i == v[j])
        {
            using std::iter_swap; iter_swap(i, begin);
            ++j;
            ++begin;
        }
    }
    return begin;
}

/*void Relation::testRun(){
    vector<string> one;
    one.push_back("a");
    one.push_back("b");
    vector<string> two;
    two.push_back("b");
    two.push_back("c");
    vector<string> three;
    three.push_back("a");
    three.push_back("c");
    vector<string> four;
    four.push_back("a");
    four.push_back("a");
    vector<string> five;
    five.push_back("c");
    five.push_back("a");
    
    test.push_back(one);
    test.push_back(two);
    test.push_back(three);
    test.push_back(four);
    test.push_back(five);
    
    vector<string> six;
    six.push_back("a");
    six.push_back("b");
    six.push_back("c");
    vector<string> seven;
    seven.push_back("b");
    seven.push_back("c");
    seven.push_back("b");
    vector<string> eight;
    eight.push_back("a");
    eight.push_back("c");
    eight.push_back("c");
    vector<string> nine;
    nine.push_back("a");
    nine.push_back("a");
    nine.push_back("a");
    vector<string> ten;
    ten.push_back("c");
    ten.push_back("a");
    ten.push_back("b");
    test2.push_back(six);
    test2.push_back(seven);
    test2.push_back(eight);
    test2.push_back(nine);
    test2.push_back(ten);
    
    
    //test 1 S(a,b)
    vector<vector<string>> v = test;
    //testPrint(v);
    //cout << "-------" << endl;
    v = select("a",0, v);
    //testPrint(v);
    //cout << "-------" << endl;
    v = select("b",1, v);
    //testPrint(v);
    //cout << "-------" << endl;
    cout << "Test 1: Pass" << endl;
    
    //test 2 S(d,a)
    vector<vector<string>> a = test;
   // testPrint(a);
    //cout << "-------" << endl;
    a = select("d",0, a);
    //testPrint(a);
    //cout << "-------" << endl;
    a = select("a",1, a);
    //testPrint(a);
    //cout << "-------" << endl;
    cout << "Test 2: Pass" << endl;
    
    
    //test 3 S(X,a)
    vector<vector<string>> b = test;
    vector<int> bIndices;
    bIndices.push_back(0);
    vector<string> s1;
    s1.push_back("X");
    //testPrint(b);
    //cout << "-------" << endl;
    b = select("a",1,b);
    //testPrint(b);
    //cout << "-------" << endl;
    b = project(bIndices,b);
    //testPrint(b);
    //cout << "-------" << endl;
    b = rename(s1, b);
    //testPrint(b);
    //cout << "-------" << endl;
    cout << "Test 3: Pass" << endl;
    
    //test 4 S(X,X)
    vector<vector<string>> c = test;
    vector<string> s2;
    s2.push_back("X");
    vector<int> cpIndices;
    cpIndices.push_back(0);
    //testPrint(c);
    //cout << "-------" << endl;
    c = sameSelect(0,1,c);
    //testPrint(c);
    //cout << "-------" << endl;
    c = project(cpIndices,c);
    //testPrint(c);
    //cout << "-------" << endl;
    c = rename(s2, c);
    //testPrint(c);
    //cout << "-------" << endl;
    cout << "Test 4: Pass" << endl;
    
    
    //test 5 (S(X,X,X)
    vector<vector<string>> d = test2;
   
    vector<int> dpIndicies;
    dpIndicies.push_back(0);
    vector<string> s3;
    s3.push_back("X");
    //testPrint(d);
    //cout << "-------" << endl;
    d = sameSelect(0,1, d);
    //testPrint(d);
    //cout << "-------" << endl;
    d = sameSelect(1,2,d);
    //testPrint(d);
    //cout << "-------" << endl;
    d = project(dpIndicies, d);
    //testPrint(d);
    //cout << "-------" << endl;
    d = rename(s3,d);
    //testPrint(d);
    //cout << "-------" << endl;
    cout << "Test 5: Pass" << endl;
    
    //test 6 S(X,c,X);
    vector<vector<string>> e = test2;
    vector<int> epIndicies;
    epIndicies.push_back(0);
    vector<string> s4;
    s4.push_back("X");
    //testPrint(e);
    //cout << "-------" << endl;
    e = select("c",1,e);
    //testPrint(e);
    //cout << "-------" << endl;
    e = sameSelect(0,2, e);
    //testPrint(e);
    //cout << "-------" << endl;
    e = project(epIndicies, e);
    //testPrint(e);
    //cout << "-------" << endl;
    e = rename(s4, e);
    //testPrint(e);
    //cout << "-------" << endl;
    cout << "Test 6: Pass" << endl;
    
    //test 7 S(X,Y,Y)
    vector<vector<string>> f = test2;
    vector<int> fpIndicies;
    fpIndicies.push_back(0);
    fpIndicies.push_back(1);
    vector<string> s5;
    s5.push_back("X");
    s5.push_back("Y");
    
    //testPrint(f);
    //cout << "-------" << endl;
    f = sameSelect(1,2, f);
    //testPrint(f);
    //cout << "-------" << endl;
    f = project(fpIndicies, f);
    //testPrint(f);
    //cout << "-------" << endl;
    f = rename(s5,f);
    //testPrint(f);
    //cout << "-------" << endl;
    cout << "Test 7: Pass" << endl;
    
    //test 8 S(b,c,b)
    vector<vector<string>> g = test2;
    //testPrint(g);
    //cout << "-------" << endl;
    g = select("b",0,g);
    //testPrint(g);
    //cout << "-------" << endl;
    g = select("c",1,g);
    //testPrint(g);
    //cout << "-------" << endl;
    g = select("b",2,g);
    //testPrint(g);
    //cout << "-------" << endl;
    cout << "Test 8: Pass" << endl;
    
    //test 9 S(X,Y,Z)
    vector<vector<string>> h = test2;
    vector<int> hpIndices;
    vector<string> s6;
    s6.push_back("X");
    s6.push_back("Y");
    s6.push_back("Z");
    hpIndices.push_back(0);
    hpIndices.push_back(1);
    hpIndices.push_back(2);
    
    //testPrint(h);
    //cout << "-------" << endl;
    h = project(hpIndices,h);
    //testPrint(h);
    //cout << "-------" << endl;
    h = rename(s6,h);
    //testPrint(h);
    //cout << "-------" << endl;
    cout << "Test 9: Pass" << endl;
    
    //test 10 S(a,b,d)
    vector<vector<string>> l = test2;
    //testPrint(l);
    //cout << "-------" << endl;
    l = select("a",0,l);
    //testPrint(l);
    //cout << "-------" << endl;
    l = select("b",1,l);
    //testPrint(l);
    //cout << "-------" << endl;
    l = select("d",2,l);
    //testPrint(l);
    //cout << "-------" << endl;
    cout << "Test 10: Pass" << endl;






    
    
    
}*/
void Relation::testPrint(vector<vector<string>> v){
 for(int i = 0; i < v.size(); i++){
 for (int j = 0; j < v[i].size(); j++){
 cout << v[i][j] << " ";
 }
 cout << endl;
 }
    cout << "--------" << endl;
 }

void Relation::printRelation(){
    for(int i = 0; i < attributes.size(); i++){
        cout << attributes[i] << " ";
    }
        cout << endl;
    for(int i = 0; i < relationFacts.size(); i++){
        for(int j = 0; j < relationFacts[i].size(); j++){
            cout << relationFacts[i][j] << " ";
        }
        cout << endl;
    }

}

vector<vector<string>> Relation::select(string s, int i, vector<vector<string>>v){
    vector<vector<string>> x;
    for(int j = 0; j < v.size(); j++){
        if (v[j][i] == s){
            x.push_back(v[j]);
        }
        
        }
    
    
    return x;
    
}



vector<vector<string>> Relation::project(vector<int> indices, vector<vector<string>> v){
    vector<vector<string>> x;
    for (int j = 0; j < v.size(); j++){
        vector<string> c;
        for(int i = 0; i < indices.size(); i++){
        
        c.push_back(v[j][indices[i]]);
        
        }
        x.push_back(c);
    }
    return x;
}

vector<vector<string>> Relation::sameSelect(long int index1, int index2, vector<vector<string>> v){
    vector<vector<string>> x;
    
   // cout << v.size() << " size for same select" << endl;
    
    for(int j = 0; j < v.size(); j++){
        if(v[j][index1] == v[j][index2]){
            x.push_back(v[j]);
        }
        
    }
    return x;
}

vector<vector<string>> Relation::rename(vector<string> s, vector<vector<string>> v){
    vector<string> c;
    for (int i = 0; i < s.size(); i++){
        c.push_back(s[i]);
    }
    v.insert(v.begin(),c);
    return v;
}

void Relation::setName(string s){
    name = s;
}
void Relation::printOneAtt(int i){
    cout << attributes[i];
}

void Relation::addAttribute(string s){
    attributes.push_back(s);
}

void Relation::addFacts(vector<string> v){
    relationFacts.push_back(v);
}

vector<vector<string>> Relation::getFacts(){
    return relationFacts;
}

void Relation::addFactsVec(vector<vector<string>> v){
    relationFacts = v;
}

void Relation::addAttVec(vector<string> v){
    attributes = v;
}

vector<string> Relation::getAtt(){
    return attributes;
}

void Relation::changeEmpty(bool b){
    isEmpty = b;
}

long int Relation::findAtt(string s){
    return (find(attributes.begin(), attributes.end(), s) - attributes.begin());
   
}

long int Relation::getAttSize(){
    return attributes.size();
}

void Relation::sortFacts(){
    sort(relationFacts.begin(),relationFacts.end());
    relationFacts.erase(unique(relationFacts.begin(),relationFacts.end()),relationFacts.end());
}

vector<string> Relation::uniqueRow(vector<string> row, vector<int> indices){
    vector<string> unique;
    for(int i = 0; i < row.size(); i++){
        if(find(indices.begin(),indices.end(), i) == indices.end()){
            unique.push_back(row[i]);

        }
    }
    return unique;
}

vector<vector<string>> Relation::doCross(vector<vector<string>> rows){
    vector<vector<string>> finalTable;
    for(int i = 0; i < rows.size(); i++){
        vector<vector<string>> toCopy = cross(rows[i]);
        for(int j = 0; j < toCopy.size(); j++){
            finalTable.push_back(toCopy[j]);
        }
    }
    return finalTable;

}

vector<vector<string>> Relation::cross(vector<string> rowA){
    vector<vector<string>> v;
    for(int i = 0; i < relationFacts.size(); i++){
        vector<string> a = rowA;
        vector<string> b = relationFacts[i];
        b.insert(b.end(), a.begin(), a.end());
        v.push_back(b);
    }
    return v;
    
}

vector<vector<string>> Relation::compareRows(vector<string> rowA, vector<pair<int,int>> headerPairs){
    vector<vector<string>> finalRows;
    vector<int> notToCopy;
    bool isCompatible = false;

    for(int i = 0; i < relationFacts.size(); i++){
        //cout << relationFacts.size() << endl;
        bool canCopy = true;

        for (int j = 0; j < headerPairs.size(); j++){

            // cout << headerPairs[j].second << "," << headerPairs[j].first << endl;
            //cout << rowA[headerPairs[j].second] << "," << relationFacts[i][headerPairs[j].first] << endl;
            /*for(int k = 0; k < rowA.size; k++){
                cout << rowA[k] << ",";
            }
            cout << endl;
            for (int k = 0; k < relationFacts[i].size(); k++){
                cout << relationFacts[i][k] << ",";
            }
                cout << endl;}*/
            if(rowA[headerPairs[j].second] == relationFacts[i][headerPairs[j].first]){
                isCompatible = true;
            } else {
                isCompatible = false;
            }
            notToCopy.push_back(headerPairs[j].second);
            canCopy = canCopy && isCompatible;
        }
        if(canCopy){
            vector<string> row = relationFacts[i];
            vector<string> row2 = uniqueRow(rowA, notToCopy);
            row.insert(row.end(), row2.begin(), row2.end());
            /*for(int k = 0; k < row.size(); k++){
             cout << row[k] << ",";
             }
             cout << endl;*/
            //row.erase(uniquify (row.begin(), row.end()), row.end());
            /*for(int k = 0; k < row.size(); k++){
             cout << row[k] << ",";
             }
             cout << endl;*/
            finalRows.push_back(row);

        }
    }
    return finalRows;
}



Relation* Relation::relUnion(Relation* r){
    if(r->getAtt() == attributes){
        for(int i = 0; i < relationFacts.size(); i++){
            r->addFacts(relationFacts[i]);
        }
        r->sortFacts();
        return r;

    } else {
        Relation* n = new Relation;
        n->changeEmpty(true);
        cout << "Not Union Compatible" << endl;
        return n;
    }
}

Relation* Relation::relNaturalJoin(Relation* r){
    vector<pair<int,int>> equalHeaders;
    vector<vector<string>> finalTable;
    vector<string> finalAtt;
    for(int i = 0; i < attributes.size(); i++){
        long int attIndex = r->findAtt(attributes[i]);
        //cout << attributes[i] << ",";
        //r->printOneAtt(attIndex);
        //cout << endl;
        if(attIndex < r->getAttSize()){
           // cout << "<" << i << "," << attIndex << ">" << endl;
            pair<int,int> p (i,attIndex);
            equalHeaders.push_back(p);
        }
    }
    const vector<vector<string>> &rFacts = r->getFacts();
   // cout << rFacts.size() << endl;
    if(equalHeaders.size() == 0){
        finalTable = doCross(rFacts);
    } else {
    for(int i = 0; i < rFacts.size(); i++){
        vector<vector<string>> toCopy = compareRows(rFacts[i], equalHeaders);
        for(int j = 0; j < toCopy.size(); j++){
            finalTable.push_back(toCopy[j]);
        }
    }
    }
    finalAtt = attributes;
    vector<string> otherAtts = r->getAtt();
    
    finalAtt.insert(finalAtt.end(), otherAtts.begin(),otherAtts.end());
    finalAtt.erase(uniquify(finalAtt.begin(), finalAtt.end()), finalAtt.end());

    
    sort (finalTable.begin(), finalTable.end());
    finalTable.erase(unique (finalTable.begin(), finalTable.end()), finalTable.end());
    
    Relation* q = new Relation;
    
    q->addAttVec(finalAtt);
    q->addFactsVec(finalTable);
    return q;
    
}
void Relation::setForPrinting(string s){
    forPrinting = s;
}

string Relation::getForPrinting(){
    return forPrinting;
}


Relation* relSelect(){
    Relation* r = nullptr;
    return r;
}

Relation* Relation::relProject(vector<long int> indices){
     vector<vector<string>> x;
    for (int j = 0; j < relationFacts.size(); j++){
     vector<string> c;
     for(int i = 0; i < indices.size(); i++){
     
     c.push_back(relationFacts[j][indices[i]]);
     
     }
     x.push_back(c);
     }
    vector<string> newAttributes;
    for(int i = 0; i < indices.size(); i++){
        newAttributes.push_back(attributes[indices[i]]);
    }
    Relation* r = new Relation;
    r->addAttVec(attributes);
    r->addFactsVec(x);
    return r;
    
}
string Relation::getName(){
    return name;
}

long int Relation::getFactsSize(){
    return relationFacts.size();
}
