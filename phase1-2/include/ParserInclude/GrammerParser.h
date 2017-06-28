#ifndef GRAMMERPARSER_H
#define GRAMMERPARSER_H
#include <bits/stdc++.h>
#include <sstream>

using namespace std;

class GrammerParser
{
    public:

        GrammerParser();
        virtual ~GrammerParser();
        int getSymCount();/*return the size of the overall grammar*/
        int get_epsilon();/*return the number of epsilon*/
        int symbol_to_number(const string& symbol);/*return the string given the number of the grammar*/
        string number_to_symbol(int number);/*return the number given the string of the grammar*/
        struct NonTerminal{
            string symbol;
            vector<vector<int>> rule;
            vector<vector<int*>> rule_ptr;
            vector< set<int> > mappedFirst;
            set<int> first;
            set<int> follow;
            vector<int> adjList;
        };/*used to represent rules of the grammar in numbers*/
        vector<NonTerminal>* get_grammer();/*returns the grammar*/
        bool isterminal(int symbol);/*determine whether the symbol is terminal*/
        void print_map();/*print maps*/
        void print_rep_ptr();/*print grammar*/
        bool exist(string symbol);


    protected:

    private:
        vector<NonTerminal> grammer;/*this contains the grammar rules in numbers*/
        map<string, int> string_to_number;/*this map contains the string of the grammar terminal/nonterminal and corresponding number before left recursion eliminated*/
        map<int, string> number_to_string;/*this map contains the number of the grammar terminal/nonterminal and corresponding string before left recursion eliminated*/
        map<string, int> string_to_number1;/*this map contains the string of the grammar terminal/nonterminal and corresponding number after left recursion eliminated*/
        map<int, string> number_to_string1;/*this map contains the number of the grammar terminal/nonterminal and corresponding string after left recursion eliminated*/
        int fill_maps_terminals(string g, int counter);/*it fill the maps with terminals placed between single quotes*/
        void replace_string(string& subject, const string& search,
                          const string& replace);/*it replaces strings in place*/
        string remove_end_spaces(const string &s);/*removes extra end spaces from string*/
        map<int, int> left_rec;/*this map contain the number of line that has left recursion and the corresponding number of new nonterminal added*/
        vector<NonTerminal> added;/*it contains all added grammars after eliminating left recursion*/
        vector<string> new_name;/*it contain the new name of nonterminals added after eliminating left recursion*/
        void adjust_maps();/*it modify maps after eliminating left recursion*/
        void eliminate_left_recursion();/*it iterates on=ver the grammar and eliminates the left recursion*/
        void replace_rules(int i, int j, int c);/*it replaces any Ai = Aj a | b , Aj = c d to => Ai = c d a | b*/
        void eliminate_immediate_left_recursion(int i);/*it eliminates immediate left recursion after rules replacing*/
        vector<string> gram;/*it contains the string grammar*/
        vector<int> contain(int i, int j);/*returns all occurrence of nonterminal j in nonterminal i's rule*/
        void read(string file_name);/*read the grammar from file and changes it  to numbers*/
        void eliminate_left_factoring();/*this function eliminates left factoring*/
        void pr_P(vector<vector<int>> v);/*print the nonterminal containing left factoring*/
        void pr_map(map<int, vector<vector<int>>> m);/*print for test purpose*/
        int find_LCP(vector<vector<int>> v);/*find longest common postfix*/
        void adjust_prod(int s, int id, vector<int> newV, vector<int*> new_v_ptr);/*adjust nonterminal containing left factoring*/
        void create_newP(int s,int num,int id, vector<vector<int>> v);/*create replacement for the nonterminal containing left factoring*/
        void eliminate_LF(int id);/*eliminate left factoring*/
        vector<vector<int>> prod;/*production rule*/
        vector<vector<int*>> v_ptr;
        int counter;
        vector<string> new_name_lf;/*it contain the new name of nonterminals added after eliminating left factoring*/
        map<int, int> left_fac;/*this map contain the number of line that has left recursion and the corresponding number of new nonterminal added*/
        vector<NonTerminal> added_lf;/*it contains all added grammars after eliminating left factoring*/


};

#endif // GRAMMERPARSER_H
