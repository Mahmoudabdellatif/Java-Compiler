#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H
#include "graph.h"
#include "NFABuilder.h"
#include <bits/stdc++.h>

using namespace std;

class DFA;

class Lexical_analyzer
{
public:
    Lexical_analyzer(string source_file, string output_file);
    pair<string, string>* next_token();
    set<string>* get_symbol_table();

private:
    bool has_next();
    char next_char();
    pair<string, string>* get_token();


    ifstream source;
    ofstream lex_output;
    DFA *automaton;
    int current_pos;
    string current_token;
    bool eof_reached;
    set<string> *sym_tab;

};

#endif // LEXICALANALYZER_H
