//
//  Parameter.cpp
//  P2 Datalog Parser
//
//  Created by Grant Rowberry on 10/5/16.
//  Copyright © 2016 Grant Rowberry. All rights reserved.
//

#include "Parameter.hpp"




string Param::toString(){
    //cout << tok.getContent() << endl;
    return tok.getContent();
}
void Param::setToken(Token Tok){
    tok = Tok;
}

Token Param::getToken(){
    return tok;
}

/*string StringParam::toString(){
    return tok.getContent();
}*/
