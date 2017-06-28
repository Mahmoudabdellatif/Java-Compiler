#include "../../include/LexicalInclude/NFABuilder.h"
#include "../../include/LexicalInclude/graph.h"
#include <string>
#include <iterator>
#include <stack>
#include <vector>
#include <iostream>
#include <utility>
#include "../../include/LexicalInclude/Reader.h"

using namespace std;

typedef pair<string, vertex*> ve;
int counter;
graph g;

NFABuilder::NFABuilder()
{
    counter = 1;
}

graph* NFABuilder::build()
{
    Reader r;
    r.read();
    cout << "zkzk\n";
    r.print_definitions();
    r.print_key_words();
    r.print_punc();
    r.print_re();

    g.addvertex(0);

    keywords_auto(r.get_key_words());

    punc_auto(r.get_punctuation());

    map<string, vector<string>> reg = r.get_regular_exp();
    map<string, vector<string>>::iterator it;
    for (it=reg.begin(); it!=reg.end(); ++it){
        int fr = makeAuto(it->second, it->first);
        g.addedge(0, fr, "\\L");
    }
    g.print();
    return &g;
}

void NFABuilder::punc_auto(vector<string> punc){
    for(vector<string>::const_iterator i = punc.begin() ; i != punc.end(); ++i){
        string p = *i;
        int fr = counter++;
        int to = counter++;
        g.addvertex(fr);
        g.addvertex(to);
        g.addedge(fr, to, p);
        vertex *f = g.get_vertex(to);
        f->is_final = true;
        f->id = p;
        g.addedge(0, fr, "\\L");
    }
}

void NFABuilder::keywords_auto(vector<string> keywords){
    for(vector<string>::const_iterator i = keywords.begin() ; i != keywords.end(); ++i){
        string key = *i;
        int fr = counter++;
        g.addvertex(fr);
        int last = fr;
        for (unsigned j=0; j<key.length(); ++j)
        {
            string sym(1, key[j]);
            int to = counter++;
            g.addvertex(to);
            g.addedge(last, to, sym);
            last = to;
        }
        vertex *f = g.get_vertex(last);
        f->is_final = true;
        f->id = key;
        g.addedge(0, fr, "\\L");
    }
}

int NFABuilder::makeAuto(vector<string> tokens, string id)
{
    stack<pair<int, int>> stk;

    stk.push(make_new_trans(tokens[0]));

    for(vector<string>::const_iterator i = tokens.begin()+1 ; i != tokens.end(); ++i){
        if(*i=="*"){
            stk = null_or_more(stk);
        }else if(*i=="?"){
            stk = once_or_null(stk);
        }else if(*i=="+"){
            stk = once_or_more(stk);
        }else if(*i=="@"){
            stk = cont(stk);
        }else if(*i=="|"){
            stk = first_or_second(stk);
        }else{
            stk.push(make_new_trans(*i));
        }
    }
    if(stk.size()>1){
        cout << "error" << endl;
    }
    pair<int, int> p = stk.top();
    stk.pop();
    vertex *f = g.get_vertex(p.second);
    f->is_final = true;
    f->id = id;
    return p.first;
}

stack<pair<int, int>> NFABuilder::cont(stack<pair<int, int>> stk){

    pair<int, int> p2 = stk.top();
    stk.pop();
    pair<int, int> p1 = stk.top();
    stk.pop();
    g.addedge(p1.second, p2.first, "\\L");
    pair<int, int> p = make_pair(p1.first, p2.second);
    stk.push(p);
    return stk;
}

stack<pair<int, int>> NFABuilder::first_or_second(stack<pair<int, int>> stk){

    int fr = counter++;
    int to = counter++;
    g.addvertex(fr);
    g.addvertex(to);
    pair<int, int> p2 = stk.top();
    stk.pop();
    pair<int, int> p1 = stk.top();
    stk.pop();
    g.addedge(fr, p1.first, "\\L");
    g.addedge(fr, p2.first, "\\L");
    g.addedge(p1.second, to, "\\L");
    g.addedge(p2.second, to, "\\L");
    pair<int, int> p = make_pair(fr, to);
    stk.push(p);
    return stk;
}

stack<pair<int, int>> NFABuilder::once_or_null(stack<pair<int, int>> stk){
    pair<int, int> p = stk.top();
    stk.pop();
    g.addedge(p.first, p.second, "\\L");
    stk.push(p);
    return stk;
}

stack<pair<int, int>> NFABuilder::null_or_more(stack<pair<int, int>> stk){
    int fr = counter++;
    int to = counter++;
    g.addvertex(fr);
    g.addvertex(to);
    pair<int, int> p = stk.top();
    stk.pop();
    g.addedge(p.second, p.first, "\\L");
    g.addedge(fr, p.first, "\\L");
    g.addedge(p.second, to, "\\L");
    g.addedge(fr, to, "\\L");
    pair<int, int> p2 = make_pair(fr, to);
    stk.push(p2);
    return stk;
}

pair<int, int> NFABuilder::make_new_trans(string token)
{
    int fr = counter++;
    int to = counter++;
    g.addvertex(fr);
    g.addvertex(to);
    g.addedge(fr, to, token);
    pair<int, int> p = make_pair(fr, to);
    return p;
}

stack<pair<int, int>> NFABuilder::once_or_more(stack<pair<int, int>> stk){
    pair<int, int> p = stk.top();
    map<int, int> m;

    bool *visited = new bool[counter];
    for(int i = 0; i < counter; i++)
        visited[i] = false;

    stack<int> s;
    s.push(p.first);
    m[p.first] = counter++;
    int fr = m[p.first];
    g.addvertex(fr);
    int to;
    while(!s.empty()){
        int i = s.top();
        s.pop();
        if(!visited[i]){
            visited[i] = true;
            //cout << "state: " << s.get_num() << endl;
            vertex *f = g.get_vertex(i);
            vector<ve>::iterator it;
            for (it=f->adj.begin(); it!=f->adj.end(); ++it){
                if(m.find(it->second->name) == m.end()){
                    m[it->second->name] = counter++;
                    g.addvertex(m[it->second->name]);
                    s.push(it->second->name);
                }
                g.addedge(m[i], m[it->second->name], it->first);
            }
        }
    }
    to = m[p.second];
    pair<int, int> p1 = make_pair(fr, to);
    stk.push(p1);
    stk = null_or_more(stk);

    stk = cont(stk);
    return stk;
}
