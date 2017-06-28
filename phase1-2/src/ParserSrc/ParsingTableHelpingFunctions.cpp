#include<bits/stdc++.h>
#include "../../include/ParserInclude/ParsingTableHelpingFunctions.h"


using namespace std;

/*
    prints first of grammar
*/
void printFirst(const vector<GrammerParser::NonTerminal>& nonTerminals, int numberOfNonTerminal){
    for(int i = 0 ; i < numberOfNonTerminal ; i++){
        const vector< set<int> >& tempVec = nonTerminals[i].mappedFirst;
        cout << "Row #" << i << endl;
        for(set<int> a : tempVec){
            for(int s : a){
                cout << s << " " ;
            }
            cout << " | " ;
        }
        cout << endl;
    }
}

/*
    reverses the given graph
*/
void reverseGraph(vector<int>* revAdjList, const vector<GrammerParser::NonTerminal>& nonTerminals, int nodeCount)
{
    for (int source = 0; source < nodeCount; source++) {
        for (int dest : nonTerminals[source].adjList) {
            revAdjList[dest].push_back(source);
        }
    }
}

/*
    traverses the graph with the given graph and pushed nodes in the reverse order
    of the search.
*/
void dfs(stack<int>& s, int node, vector<int>* revAdjList, bool isVisited[])
{
    isVisited[node] = true;
    for (int dest : revAdjList[node]) {
        if (isVisited[dest]) {
            continue;
        }
        dfs(s, dest, revAdjList, isVisited);
    }
    s.push(node);
}

/*
    traverses the graph of group-nods with the given graph and pushes nodes in the reverse order
    of the search.
*/
void groups_dfs(stack<int>& s, int node, set<int>* groupAdjList, bool isVisited[])
{
    isVisited[node] = true;
    for (int dest : groupAdjList[node]) {
        if (isVisited[dest]) {
            continue;
        }
        groups_dfs(s, dest, groupAdjList, isVisited);
    }
    s.push(node);
}

void collectGroupFollow(int node, bool isVisited[], set<int>& fol, int group,
                        int termToGroup[], vector<GrammerParser::NonTerminal>& grammar)
{
    isVisited[node] = true;
    termToGroup[node] = group;
    for (int dest : grammar[node].adjList) {
        if (isVisited[dest]) {
            continue;
        }
        collectGroupFollow(dest, isVisited, fol, group, termToGroup, grammar);
    }

    const set<int>& temp = grammar[node].follow;
    fol.insert(temp.begin(), temp.end());
}

set<int>* propagateFollow(int node, set<int>* groupAdjList, vector<set<int>>& groupFollow, bool isVisited[])
{
    if (isVisited[node]) {//If ready, return it.
        return &groupFollow[node];
    }
    isVisited[node] = true;
    set<int> *current = &groupFollow[node];
    for (int dest : groupAdjList[node]) {
        set<int> *temp = propagateFollow(dest, groupAdjList, groupFollow, isVisited);
        current->insert(temp->begin(), temp->end());
    }
    return current;
}

void printFollow(const vector<GrammerParser::NonTerminal>& grammar, int numberOfNonTerminal){
    for(int i = 0 ; i < numberOfNonTerminal ; i++){
        cout << "Row #" << i << endl;
        for(int a : grammar[i].follow){
            cout << a << " ";
        }
        cout << endl;
    }
    return;
    cout << "adjacency list" << endl;
    for(int i = 0 ; i < numberOfNonTerminal ; i++){
        cout << "Row #" << i << endl;
        for(int a : grammar[i].adjList){
            cout << a << " ";
        }
        cout << endl;
    }
}

bool validSymNums(int nonTerm, int term, int symCount, int nonTermCount)
{
    if (nonTerm < 0
            || nonTerm > nonTermCount - 1
            || nonTerm >= term
            || term > symCount) {
        return false;
    }
    return true;
}

void throwErrors(Error error, ...)
{
    va_list args;
    va_start(args, error);

    stringstream msg;
    switch (error) {
    case Error::SYM_TO_NUM :
        msg << "Error : Accessing symbol_to_number "
            << "before ParsingTable construction";
    case Error::NUM_TO_SYM :
        msg << "Error : Accessing number_to_symbol "
            << "before ParsingTable construction";
    case Error::GET_ENTRY_UNINIT :
        msg << "Error : Accessing get_entry before "
            << "ParsingTable construction";
    case Error::GET_ENTRY_INVALID :
        msg << "Error : requesting table entry with "
            << "invalid values, nonTerminal=" << va_arg(args, int)
            << "terminal=" << va_arg(args, int);
    case Error::IS_TERMINAL_UNINIT :
        msg << "Error : Accessing isterminal before ParsingTable construction";
    case Error::TRY_ENTRY_UNINIT :
        msg << "Error : Accessing try_entry before ParsingTable construction";
    case Error::TRY_ENTRY_INVALID :
        msg << "Error : requesting to try table "
            << "entry with invalid values, nonTerminal="
            << va_arg(args, int) << "terminal=" << va_arg(args, int);
    case Error::CONS_UNINIT :
        msg << "Error : Constructing ParsingTable before initializing it";
    case Error::TWO_EPS :
        msg << "Error : two productions for non terminal "
            << va_arg(args, int) << ", found at " << va_arg(args, int)
            << " & " << va_arg(args, int);
    case Error::TWO_TRANS :
        msg << "Error : non terminal " << va_arg(args, int)
            << ", has two transitions for terminal "
            << va_arg(args, int) << " from first and follow";
    default :
        msg << "Undefined error thrown";
    }
    msg << endl;
    va_end(args);
    throw new runtime_error(msg.str());
}













