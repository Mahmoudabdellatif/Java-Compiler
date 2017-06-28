#include "../../include/LexicalInclude/Postfix.h"
#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include<string>
#include<string.h>
#include <vector>
#include <strings.h>
#include<stack>
#include <sstream>
#include <iterator>
#include <fstream>
#include <regex>

Postfix::Postfix()
{
    //ctor
}

Postfix::~Postfix()
{
    //dtor
}

int Postfix::contains(string s, char c){
    for(int i = 0 ; i < (int)s.length() ; i++){
        if(s.at(i) == c){
            return i;
        }
    }
    return -1;
}


vector<string> Postfix::to_postfix(vector<string> input){
    input = add_conc(input);
    stack <string> operator_stack ;
    vector<string> outputString ;
    for(int i = 0; i < (int)input.size(); i++){
        string c = input[i];
        if(is_any_operator(c)){
            if(operator_stack.empty()){
                 operator_stack.push(c);
            }
            else{
                string top_of_stack = operator_stack.top();
                if(is_any_operator(top_of_stack)){
                    int presedenceValue = precedence(c, top_of_stack);
                    if (presedenceValue <= 0){
                        top_of_stack = operator_stack.top();
                        operator_stack.pop();
                        outputString.push_back(top_of_stack);
                    }
                }
                operator_stack.push(c);
            }
        }else if(is_open_paranthesis(c)){
           operator_stack.push(c);

        }else if(is_closed_paranthesis(c)){
           string top_of_stack = operator_stack.top();
           operator_stack.pop();
           while(!is_open_paranthesis(top_of_stack)){
               outputString.push_back(top_of_stack);
               top_of_stack = operator_stack.top();
               operator_stack.pop();
           }
        }
        else{
            outputString.push_back(c);
        }
    }
    while(!operator_stack.empty()){
        outputString.push_back(operator_stack.top());
        operator_stack.pop();

    }
    return (outputString);
}
bool Postfix::is_relop(string character){
    return character == "\\=" || character == "<" || character == ">" || character == "!";
}
bool Postfix::is_open_paranthesis(string character){
    return character == "(";
}
bool Postfix::is_closed_paranthesis(string character){
    return character == ")";
}
bool Postfix::is_any_operator(string character){
    return character == "*" || character == "+" || character == "@" || character == "|" || character == "?";
}
bool Postfix::is_higher_operator(string character) {
    return character == "*" || character == "+" || character == "?";
}
bool Postfix::is_or(string a) {
    return a == "|";
}
bool Postfix::is_character(string character){
    regex r("\\w+");
    if(regex_match(character, r)){
        return true;
    }else{

      return  false;
    }
    //return !is_any_operator(character) && !is_closed_paranthesis(character) && !is_open_paranthesis(character);
}
bool Postfix::is_conc(string character){
    return character == ".";
}
bool Postfix::is_concatenation(string character){
    return character == "@";
}
int Postfix::precedence(string a, string b){
    if(is_higher_operator(a)){
        if(is_higher_operator(b))
            return 0;
        else
            return 1;
    }
    else if(is_concatenation(a)){
        if(is_higher_operator(b))
            return -1;
        else if (b == a)
            return 0;
        else
            return 1;
    }

    else if(is_or(a)){
        if(a == b)
            return 0;
        else return -1;
    }

    return -2;
}
bool Postfix::possible_concatenation(vector<string> str) {
    return is_character(str[str.size() - 1])
            || is_closed_paranthesis(str[str.size() - 1])
            || is_higher_operator(str[str.size() - 1])
            || is_relop(str[str.size() - 1])
            || is_conc(str[str.size() - 1]);
}
vector<string> Postfix::add_conc(vector<string> str){
    vector<string> s ;
    s.push_back(str[0]);

    for(int i = 1; i < (int)str.size(); i++){
        string c = str[i];
        if(possible_concatenation(s))
            if(is_character(c) || is_open_paranthesis(c) || c == "\\" || is_conc(c) || is_relop(c))
                s.push_back("@");
        s.push_back(c);

    }
    return s;
}
