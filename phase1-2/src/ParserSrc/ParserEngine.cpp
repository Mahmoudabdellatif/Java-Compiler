#include "../../include/ParserInclude/ParserEngine.h"
#include "../../include/ParserInclude/ParsingTable.h"
#include <string>
#include <stack>
#include <vector>
#include <iterator>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

ParserEngine::ParserEngine(Lexical_analyzer* la, ParsingTable* pt)
{
    this->lexer = la;
    this->parsing_table = pt;
}

ParserEngine::~ParserEngine(){}

void ParserEngine::parse(string file_name)
{
    bool flag = true;
    output.open(file_name);
    stack<int> stk;
    int initial = parsing_table->symbol_to_number("$");
    stk.push(initial);
    stk.push(0);
    current_line.push_back(parsing_table->number_to_symbol(0));
    print_line();
    pair<string, string>* token;
    while(true){
        if(flag){
            token = lexer->next_token();
        }
        int cur;
        if(token == NULL){
            if(stk.top()==initial) {
                output << "parse complete" << endl;
                break;
            }
            cur = initial;
        }else{
            if(!parsing_table->exist(token->first)){
                output << "Error: "<< token->first << " doesn't exist among terminals" << endl;
                continue;
            }
            cur = parsing_table->symbol_to_number(token->first);
        }
        if(stk.top()==initial) {
            output << "Error: can't continue parsing ..." << endl;
            break;
        }
        int top = stk.top();
        if(parsing_table->isterminal(top)){
            if(top == cur){
                flag = true;
            }else{
                flag = false;
                output << "Error: missing "<< parsing_table->number_to_symbol(top) << ", inserted" <<endl;
            }
            stk.pop();
        }
        else{
            ParsingTable::eleState state = parsing_table->try_entery(top, cur);
            switch(state){
                case ParsingTable::eleState::ERROR: // error
                    flag = true;
                    print_error(top, cur, true);
                    break;

                case ParsingTable::eleState::SYNC:  // sync
                    flag = false;
                    stk.pop();
                    print_error(top, cur, false);
                    remove_selected(top);
                    print_line();
                    break;

                case ParsingTable::eleState::EPS:  // \L
                    flag = false;
                    stk.pop();
                    remove_selected(top);
                    print_line();
                    break;

                case ParsingTable::eleState::SUCCESS: // valid
                    flag = false;
                    stk.pop();
                    vector<int> v = parsing_table->get_entry(top, cur);
                    prepare_new_line(top, v);
                    print_line();
                    while (!v.empty())
                    {
                        stk.push(v.back());
                        v.pop_back();
                    }
                    break;
            }
        }

    }
    output.close();
}

void ParserEngine::prepare_new_line(int top, vector<int> v)
{
    string selected = parsing_table->number_to_symbol(top);
    int i = 0;
    for(i=0; i<(int)current_line.size(); i++){
        if(current_line[i] == selected){
            current_line[i] = parsing_table->number_to_symbol(v[0]);
            break;
        }
    }
    if( i == ((int)current_line.size()-1)){
        for(int j=1; j<(int)v.size(); j++){
            current_line.push_back(parsing_table->number_to_symbol(v[j]));
        }
    }
    else{
        for(int j=1; j<(int)v.size(); j++){
            current_line.insert(current_line.begin()+i+j, parsing_table->number_to_symbol(v[j]));
        }
    }
}

void ParserEngine::print_error(int top, int cur, bool flag)
{
    if(flag){
        output << "Error: (illegal "<< parsing_table->number_to_symbol(top) <<" ) - discard "
        << parsing_table->number_to_symbol(cur) << endl;
    }
    else{
        output << "Error: missing "<< parsing_table->number_to_symbol(top) <<endl;
    }
}

void ParserEngine::remove_selected(int top)
{
    string selected = parsing_table->number_to_symbol(top);
    vector<string>::iterator it;
    it = find(current_line.begin(), current_line.end(), selected);
    if(it != current_line.end()){
        current_line.erase(it);
    }
}

void ParserEngine::print_line()
{
    for (vector<string>::const_iterator i = current_line.begin(); i != current_line.end(); ++i)
        output << *i << ' ';
    output << endl;
}

