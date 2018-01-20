//
//  Lexer.cpp
//  Proj1 Lexical Analyzer
//
//  Created by Grant Rowberry on 9/21/16.
//  Copyright © 2016 Grant Rowberry. All rights reserved.
//

#include "Lexer.hpp"

void Lexer::readFile(string filePath){
    
    ifstream charStream;

    charStream.open(filePath, ios::in);
    char c;
    
    if(charStream.is_open()){
        while(charStream.get(c)){
            //charStream >> noskipws >> c
            chars.push_back(c);
           // cout << c << " ";
        }
        if (charStream.eof()){
            chars.push_back(EOF);
        }
    } else cout << "Could not open" << endl;
    //cout << endl;
    charStream.close();
    
}

void Lexer::print(){
    for(int i = 0; i < finalTokens.size(); i++){
        if (finalTokens[i].getType() != Token::WHITESPACE && finalTokens[i].getType() != Token::ENDLINE){
        string s = finalTokens[i].toString();
        cout << s << endl;
            totalTokens++;
        }
        
    }
    cout << "Total Tokens = " << totalTokens;
}


void Lexer::run(){
    int undef = 0;
    for(int i = 0; i < chars.size(); i++)
    {
        currentIndex = i;
        undef = 0;
        undef += commaMech(chars[i]);
        undef += periodMech(chars[i]);
         undef += qMarkMech(chars[i]);
         undef += leftParenMech(chars[i]);
         undef += rightParenMech(chars[i]);
         undef += colonMech(chars[i]);
         undef += multiplyMech(chars[i]);
         undef += addMech(chars[i]);
        undef += colonDashMech(chars[i]);
        undef += whitespaceMech(chars[i]);
        undef += factsMech(chars[i]);
        undef += rulesMech(chars[i]);
        undef += schemesMech(chars[i]);
        undef += queriesMech(chars[i]);
        undef += idMech(chars[i]);
        undef += stringMech(chars[i]);
        undef += commentMech(chars[i]);
        undef += eofMech(chars[i]);
        if(undef == 0){
            undefinedMech1(chars[i]);
        }
        
        if (max!= 0){
            i+= max-1;
            max = 0;
        }
       // cout << lineNumberToAdd << endl;
        finalTokens.push_back(createToken(maxToken, maxContent, lineNumber));
        lineNumber += lineNumberToAdd;

        maxContent = "";
        lineNumberToAdd = 0;
        
    };
    
    
    
}

int Lexer::commaMech(char c){
    int charCount = 1;
    
    
    if(c == ','){
        string s(1,c);
        if (charCount > max){ //checks to see if this should be the token used
            max = charCount;
            maxContent = s;
            maxToken = Token::COMMA;
            
        }
        return 1;
    }
    return 0;
}

int Lexer::periodMech(char c){
    int charCount = 1;
    
    
    if(c == '.'){
        string s(1,c);
        if (charCount > max){ //checks to see if this should be the token used
            max = charCount;
            maxContent = s;
            maxToken = Token::PERIOD;
            
        }
        return 1;
    }
    return 0;
}

int Lexer::qMarkMech(char c){
    int charCount = 1;
    
    
    if(c == '?'){
        string s(1,c);
        if (charCount > max){ //checks to see if this should be the token used
            max = charCount;
            maxContent = s;
            maxToken = Token::Q_MARK;
            
        }
        return 1;
    }
    return 0;
}

int Lexer::leftParenMech(char c){
    int charCount = 1;
    
    
    if(c == '('){
        string s(1,c);
        if (charCount > max){ //checks to see if this should be the token used
            max = charCount;
            maxContent = s;
            maxToken = Token::LEFT_PAREN;
            
        }
        return 1;
    }
    return 0;
}

int Lexer::rightParenMech(char c){
    int charCount = 1;
    
    
    if(c == ')'){
        string s(1,c);
        if (charCount > max){ //checks to see if this should be the token used
            max = charCount;
            maxContent = s;
            maxToken = Token::RIGHT_PAREN;
            
        }
        return 1;
    }
    return 0;
}

int Lexer::colonMech(char c){
    int charCount = 1;
    
    
    if(c == ':'){
        string s(1,c);
        if (charCount > max){ //checks to see if this should be the token used
            max = charCount;
            maxContent = s;
            maxToken = Token::COLON;
            
        }
        return 1;
    }
    return 0;
}

int Lexer::multiplyMech(char c){
    int charCount = 1;
    
    
    if(c == '*'){
        string s(1,c);
        if (charCount > max){ //checks to see if this should be the token used
            max = charCount;
            maxContent = s;
            maxToken = Token::MULTIPLY;
            
        }
        return 1;
    }
    return 0;
}

int Lexer::addMech(char c){
    int charCount = 1;
    
    
    if(c == '+'){
        string s(1,c);
        if (charCount > max){ //checks to see if this should be the token used
            max = charCount;
            maxContent = s;
            maxToken = Token::ADD;
            
        }
        return 1;
    }
    return 0;
}

int Lexer::whitespaceMech(char c){
    int charCount = 1;
    
    if(c == '\n' || c == '\r'){
        //string s(1,c);
        //if (charCount > max){ //checks to see if this should be the token used
            max = charCount;
            maxContent = "";
            maxToken = Token::ENDLINE;
            lineNumber++;
        //}
        return 1;
    }    
    
    
    if(c == ' ' || c == '\t' || c == '\f' || c == '\v'){
        string s(1,c);
        //if (charCount > max){ //checks to see if this should be the token used
            max = charCount;
            maxContent = s;
            maxToken = Token::WHITESPACE;
            
        //}
        return 1;
    }
    return 0;
}

int Lexer::colonDashMech(char c){
    int charCount = 2;
    stringstream s;
    
    char a = chars[currentIndex+1];
    if(c == ':'){
        if(a =='-'){
            s << ":" << "-";
            if(charCount > max){
                max = charCount;
                maxContent = s.str();
                maxToken = Token::COLON_DASH;
            }
            return 1;
        }
    }
    return 0;
}

int Lexer::factsMech(char c){
    int charCount = 5;
    
    if (c == 'F'){
        if(chars[currentIndex+1] == 'a'){
            if(chars[currentIndex+2] == 'c'){
                if(chars[currentIndex+3] == 't'){
                    if(chars[currentIndex+4] == 's'){
                        if(charCount > max){
                            max = charCount;
                            maxContent = "Facts";
                            maxToken = Token::FACTS;
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int Lexer::rulesMech(char c){
    int charCount = 5;
    
    if (c == 'R'){
        if(chars[currentIndex+1] == 'u'){
            if(chars[currentIndex+2] == 'l'){
                if(chars[currentIndex+3] == 'e'){
                    if(chars[currentIndex+4] == 's'){
                        if(charCount > max){
                            max = charCount;
                            maxContent = "Rules";
                            maxToken = Token::RULES;
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int Lexer::schemesMech(char c){
    int charCount = 7;
    
    if(c == 'S'){
        if(chars[currentIndex+1] == 'c'){
            if(chars[currentIndex+2] == 'h'){
                if(chars[currentIndex+3] == 'e'){
                    if(chars[currentIndex+4] == 'm'){
                        if(chars[currentIndex+5] == 'e'){
                            if(chars[currentIndex+6] == 's'){
                                if(charCount > max){
                                    max = charCount;
                                    maxContent = "Schemes";
                                    maxToken = Token::SCHEMES;
                                    return 1;
                            }
                        }
                    }
                }
            }
        }
    }
        
}
    return 0;
}

int Lexer::queriesMech(char c){
    int charCount = 7;
    
    if(c == 'Q'){
        if(chars[currentIndex+1] == 'u'){
            if(chars[currentIndex+2] == 'e'){
                if(chars[currentIndex+3] == 'r'){
                    if(chars[currentIndex+4] == 'i'){
                        if(chars[currentIndex+5] == 'e'){
                            if(chars[currentIndex+6] == 's'){
                                if(charCount > max){
                                    max = charCount;
                                    maxContent = "Queries";
                                    maxToken = Token::QUERIES;
                                    return 1;
                                }
                            }
                        }
                    }
                }
            }
        }
        
    }
    return 0;
}

int Lexer::idMech(char c){
    int charCount = 1;
    int i = 1;
    stringstream s;
    if (isalpha(c)){
        s << c;
        while(isalpha(chars[currentIndex+i]) || isdigit(chars[currentIndex+i])){
            s << chars[currentIndex+i];
            i++;
            charCount++;
        }
        string str = s.str();
        if (str.length() == 5){ //5 is the length of the facts and rules token
            if(str == "Rules" || str == "Facts"){
                return 0;
            }
        }
        if (str.length() == 7){
            if (str == "Schemes" || str == "Queries"){
                return 0;
            }
        }
        max = charCount;
        maxContent = str;
        maxToken = Token::ID;
        return 1;
    }
    return 0;
}


int Lexer::stringMech(char c){
    int charCount = 1;
    int i = 1;
    stringstream s;
    if (c == '\''){
        s << c;
        bool bisEven = false;
        int aCount = 1;
        while(bisEven == false){
            if(chars[currentIndex+i] == '\''){
                aCount++;
            }
            if(chars[currentIndex+i] == '\'' && chars[currentIndex+i+1] != '\''){
                int isEven = aCount%2;
                if (isEven == 0){
                    bisEven = true;
                    
                }
            }
            
            
            
            
            s << chars[currentIndex+i];
            
            if(chars[currentIndex+i] == '\n' || chars[currentIndex+i] == '\r'){
                lineNumberToAdd++;
            }
            
            
            
           // cout << chars[currentIndex+i] << endl;
            
            if(chars[currentIndex+i+1] == EOF){
                charCount++;
                undefinedMech2(s.str(),charCount);
                return 1; //returns 1 because it will pass the undefined string to undefinedMech2 which will prevent the need of callin undefinedMech1
            }
            /*if(chars[currentIndex+i+1] == '\'' && chars[currentIndex+i+2] == '\''){
                s << chars[currentIndex+i+1] << chars[currentIndex+i+2];
                i+=2;
                charCount+=2;
                
            }*/
            
            i++;
            charCount++;
        }
        //s << chars[currentIndex+i];
        //charCount++;
        max = charCount;
        maxContent = s.str();
        maxToken = Token::STRING;
        return 1;
        
    }
    return 0;
}


int Lexer::commentMech(char c){
    int charCount = 1;
    int i = 1;
    stringstream s;
    if (c == '#'){
        s << c;
        
        if (chars[currentIndex+1] == '|'){ //block comment
            //cout << chars[currentIndex+i] << " " << chars[currentIndex+i+1] << endl;
            while(chars[currentIndex+i] != '|' || chars[currentIndex+i+1] != '#'){
                if(chars[currentIndex+i] == '\n' || chars[currentIndex+i] == '\r'){
                    lineNumberToAdd++;
                }
                
                s << chars[currentIndex+i];
                if(chars[currentIndex+i+1] == EOF){
                    charCount++;
                    undefinedMech2(s.str(),charCount);
                    return 1; //returns 1 because it will pass the undefined string to undefinedMech2 which will prevent the need of callin undefinedMech1
                }
                i++;
                charCount++;
            }
            s << chars[currentIndex+i] << chars[currentIndex+i+1];
            charCount += 2;
            max = charCount;
            maxContent = s.str();
            maxToken = Token::COMMENT;
            return 1;
        }
        else { //single line comment
            while(chars[currentIndex+i] != '\n' && chars[currentIndex+i] != '\r'){
                s << chars[currentIndex+i];
                charCount++;
                i++;
            }
            max = charCount;
            maxToken = Token::COMMENT;
            maxContent = s.str();
            return 1;
        }
    }
    return 0;
}

int Lexer::undefinedMech2(string s, int charCount){
    max = charCount;
    maxContent = s;
    maxToken = Token::UNDEFINED;
    return 1;
}

int Lexer::undefinedMech1(char c){
   // int charCount = 1;
    string s(1,c);
    max = 1;
    maxContent = s;
    maxToken = Token::UNDEFINED;
    return 1;
}

int Lexer::eofMech(char c){
    if(c == EOF){
        max = 1;
        maxContent = "";
        maxToken = Token::EoF;
        return 1;
    }
    return 0;
}



Token Lexer::createToken(Token::tokentype type, string content, int lineNumber){
    //if(type != Token::WHITESPACE){
        Token tok(type, content, lineNumber);
   // }
    //cout << content << endl;
    return tok;
}


vector<Token> Lexer::getTokens(){
    return finalTokens;
}
