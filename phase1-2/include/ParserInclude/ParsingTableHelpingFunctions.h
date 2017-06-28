#ifndef PARSINGTABLEHELPINGFUNCTIONS_H_INCLUDED
#define PARSINGTABLEHELPINGFUNCTIONS_H_INCLUDED

#include<bits/stdc++.h>
#include "ParsingTable.h"
#include "GrammerParser.h"

using namespace std;
/* errors */
enum class Error {
    SYM_TO_NUM,
    NUM_TO_SYM,
    GET_ENTRY_UNINIT,
    GET_ENTRY_INVALID,
    IS_TERMINAL_UNINIT,
    TRY_ENTRY_UNINIT,
    TRY_ENTRY_INVALID,
    CONS_UNINIT,
    TWO_EPS,
    TWO_TRANS
};

/*
    prints first of grammar
*/
void printFirst(const vector<GrammerParser::NonTerminal>& nonTerminals, int numberOfNonTerminal);

/*
    reverses the given graph
*/
void reverseGraph(vector<int>* revAdjList, const vector<GrammerParser::NonTerminal>& nonTerminals, int nodeCount);

/*
    traverses the graph with the given graph and pushed nodes in the reverse order
    of the search.
*/
void dfs(stack<int>& s, int node, vector<int>* revAdjList, bool isVisited[]);

/*
    traverses the graph of group-nods with the given graph and pushes nodes in the reverse order
    of the search.
*/
void groups_dfs(stack<int>& s, int node, set<int>* groupAdjList, bool isVisited[]);

void collectGroupFollow(int node, bool isVisited[], set<int>& fol, int group,
                        int termToGroup[], vector<GrammerParser::NonTerminal>& grammar);

set<int>* propagateFollow(int node, set<int>* groupAdjList, vector<set<int> >& groupFollow, bool isVisited[]);

void printFollow(const vector<GrammerParser::NonTerminal>& grammar, int numberOfNonTerminal);

bool validSymNums(int nonTerm, int term, int symCount, int nonTermCount);

void throwErrors(Error error, ...);

#endif // PARSINGTABLEHELPINGFUNCTIONS_H_INCLUDED
