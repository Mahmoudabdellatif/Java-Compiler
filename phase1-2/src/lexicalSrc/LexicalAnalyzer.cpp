#include <bits/stdc++.h>
#include "../../include/LexicalInclude/LexicalAnalyzer.h"
#include "../../include/LexicalInclude/NFABuilder.h"
#include "../../include/LexicalInclude/DFA.h"
#include "../../include/LexicalInclude/DFAMinimizer.h"


using namespace std;

Lexical_analyzer::Lexical_analyzer(string source_file, string output_file)
        : source(source_file), lex_output(output_file), current_pos(0), current_token(""),
        eof_reached(false), sym_tab(new set<string>()) {

    NFABuilder engine;
    this->automaton = new DFA();


    automaton->from_NFA(engine.build());
//    DFAMinimizer dfa (*automaton->transition_table());
//
//    Data_Wrapper* temp = new Data_Wrapper();
//    *temp = dfa.get_data();
//    automaton->from_transition_table(temp);
}

set<string>* Lexical_analyzer::get_symbol_table()
{
    return this->sym_tab;
}

pair<string, string>* Lexical_analyzer::next_token()
{
  if (source.eof() && !has_next()) {
        return NULL;
    }
    //check if token read is out
    if (!has_next()) {
        source >> current_token;
        if (source.eof()) {
        }
        current_pos = 0;
    }

    pair<string, string> *token = get_token();
    string bad_string("");
    while (has_next() && token == NULL) {
        bad_string += string(1, next_char());
        token = get_token();
    }

    if (!bad_string.empty()) {
        lex_output << bad_string << " is not defined...." << endl;
    }
    if (token != NULL) {
        //print to output file
        lex_output << token->first << endl;
        return token;
    }
    return next_token();
}

pair<string, string>* Lexical_analyzer::get_token()
{
    //end of file reached
    if (!has_next()) {
        return NULL;
    }


    DFA_state* last_accepting = NULL;
    int chars_accepted = 0;
    int chars_read = 0;
    string input_read;

    DFA_state* current_state = this->automaton->get_start();

    if (current_state->is_accepting()) {
        last_accepting = current_state;
    }

    while (current_state != NULL && has_next()) {
        char c = next_char();
        chars_read++;
        string input(1, c);
        input_read += input;
        current_state = current_state->move(&input);
        if (current_state != NULL && current_state->is_accepting()) {
            last_accepting = current_state;
            chars_accepted = chars_read;
        }
    }
    if (last_accepting == NULL) {//cout << "no match";
        //return every thing as it was
        current_pos = current_pos - chars_read;
        return NULL;
    }
    //generate token value
    string value = input_read.substr(0, chars_accepted);
    //push into symbol table if identifier
    if (last_accepting->get_type() == "id") {
        sym_tab->insert(value);
    }

    current_pos -= chars_read - chars_accepted;
    return new pair<string, string>(last_accepting->get_type(), value);

}

char Lexical_analyzer::next_char()
{
    if (!has_next()) {//cannot read from file
        return '\0';
    }
return current_token[current_pos++];
}

bool Lexical_analyzer::has_next()
{
    return current_pos < (int)this->current_token.size();
}
