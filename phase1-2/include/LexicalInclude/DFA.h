#ifndef DFA_H_INCLUDED
#define DFA_H_INCLUDED

#include <bits/stdc++.h>

#include "graph.h"

using namespace std;

class DFA_state;
class Data_Wrapper;

class DFA {
public:
    /* takes the NFA graph object, when the DFA object is created. */
    DFA();
    /* called after the object is created. It runs the subset construction
       algorithm to convert the NFA to DFA. */
    void from_NFA(graph* NFA);
    /* returns the start state of the DFA. */
    DFA_state* get_start();
    /* returns the accepting states of the DFA. */
    vector<int>* get_accepting();
    /* returns all the states in the DFA. */
    vector<DFA_state*>* get_all();
    /* Returns the DFA's transition table */
    Data_Wrapper* transition_table();
    /* from transition table */
    bool from_transition_table(Data_Wrapper* data);
    /* clears all data */
    void clear();

    void print_all();

private:
    /* the NFA first given to this object on its creation. */
    graph* NFA;
    /* the DFA's start state */
    DFA_state* start;
    /* all the DFA's accepting states. */
    vector<DFA_state*>* accepting;
    /* defined inputs of this automaton */
    vector<string>* DFA_inputs;
    /* Automaton's size */
    int state_count;

};

class DFA_state {
    friend class DFA;

public:
    DFA_state(bool accepting, int state_num, string* type);
    /* returns true if this state is an accepting state. */
    bool is_accepting();
    /* adds a transition from this state to the given destination state
       under the given input. */
    bool add_transition(const string& input, DFA_state* state);
    /* returns the state associated with this state under the given input. It returns
       NULL if no transition exits for the given input. */
    DFA_state* move(string* input);
    /* returns all the states reachable from this state. */
    vector<pair<string, DFA_state*> >* get_all();
    /* Returns token type */
    string get_type();

private:
    /* is this state accepting or not. */
    bool accepting;
    /* the number assigned to this state. */
    int state_num;
    /* transition table. maps each state, reachable from this state, to its input. */
    map<string, DFA_state*>* trans_table;
    /* the type of the token we get when a match occurs. It is NULL if the state is
       not accepting. */
    string* type;
};

class Data_Wrapper {
public:
    vector<string> inputs;
    vector<vector<int> > transitions;

    vector<int> final_states;
    vector<string> token_types;
};

#endif
