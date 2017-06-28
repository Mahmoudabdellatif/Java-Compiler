#include "../../include/LexicalInclude/graph.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

graph::graph()
{
    //ctor
}

void graph::print()
{
    typedef pair<string, vertex*> ve;
    vmap::iterator it;
    for (it=work.begin(); it!=work.end(); ++it){
        cout << "node: "<< it->first;
        vertex *f = (it->second);
        if(f->is_final){
            cout << "   final, id: "<< f->id;
        }
        cout<<endl;
        vector<ve>::iterator i;
        for (i=f->adj.begin(); i!=f->adj.end(); ++i){
            cout << "\tedge: "<< i->first << " to " << i->second->name <<endl;
        }
    }
}

vertex* graph::get_vertex(const int &name)
{
    return work[name];
}

void graph::addvertex(const int &name)
{
    vmap::iterator itr = work.find(name);
    if (itr == work.end())
    {
        vertex *v;
        v = new vertex(name);
        work[name] = v;
        return;
    }
    cout << "\nVertex already exists!";
}

void graph::addedge(const int& from, const int& to, string cost)
{
    vertex *f = (work.find(from)->second);
    vertex *t = (work.find(to)->second);
    pair<string, vertex *> edge = make_pair(cost, t);
    f->adj.push_back(edge);
}
