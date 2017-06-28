#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

//structure of state
struct vertex {
    typedef pair<string, vertex*> ve;
    vector<ve> adj; //symbol of transition, destination state
    int name;       //number of state
    bool is_final; //if final state
    string id;          //id of automata of this state is final
    vertex(int s) : name(s), is_final(false) {}
};

//structure for automata
class graph
{
    public:
        graph();
        typedef map<int, vertex *> vmap;
        vmap work;
        vertex* get_vertex(const int&);
        void print();   //print automata
        void addvertex(const int&);         //make new state
        void addedge(const int& from, const int& to, string cost);  //make new transition
};

#endif // GRAPH_H
