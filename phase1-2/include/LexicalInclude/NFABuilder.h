#ifndef NFABUILDER_H
#define NFABUILDER_H

#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <stack>
#include <map>
#include "graph.h"

using namespace std;

//Engine for building NFA
class NFABuilder
{
    public:
        NFABuilder();

        //combines all automatas to one big NFA
        graph* build();

    private:

        //this function constracts new automata with postfix input vector
        int makeAuto(vector<string> tokens, string id);

        //make new transition to the automata
        pair<int, int> make_new_trans(string token);

        //concatenate two automatas
        stack<pair<int, int>> cont(stack<pair<int, int>> stk);

        //dealing with ( ? )
        stack<pair<int, int>> once_or_null(stack<pair<int, int>> stk);

        //dealing with ( * )
        stack<pair<int, int>> null_or_more(stack<pair<int, int>> stk);

        //dealing with ( + )
        stack<pair<int, int>> once_or_more(stack<pair<int, int>> stk);

        //dealing with ( OR )
        stack<pair<int, int>> first_or_second(stack<pair<int, int>> stk);

        //this function constracts new automata for keywords with keywords input vector
        void keywords_auto(vector<string> keywords);

        //this function constracts new automata for punctuations with punctuations input vector
        void punc_auto(vector<string> punc);
};

#endif // NFABUILDER_H
