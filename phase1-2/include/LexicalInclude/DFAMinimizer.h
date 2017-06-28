#ifndef DFAMINIMIZER_H
#define DFAMINIMIZER_H
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <set>
#include <string.h> // memcpy
#include <stdlib.h> //realloc
#include "DFA.h"
using namespace std;
class DFAMinimizer
{
    public:
        DFAMinimizer(Data_Wrapper d);
        /*vector<vector<int>>*/void dfa_minimizer(vector<vector<int>> trans, vector<int> final_states, vector<string> s);
        vector<vector<int>> get_transitions();
        vector<string> get_type_of_final_states();
        vector<int> get_final_states();
        Data_Wrapper get_data();
        vector<string> get_inputs();


    private:
        Data_Wrapper dw;
        vector<string> inputs;


        vector<vector<int>> transistions;
        vector<string> types_min;
        vector<int> final_states_min;
        //vector<string> types_of_final_states;
        map<int, string> final_states_types;
        void fill_map(vector<int> a, vector<string> b);




};

#endif // DFAMINIMIZER_H
