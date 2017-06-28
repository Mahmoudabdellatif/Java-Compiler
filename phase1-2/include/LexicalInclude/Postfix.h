#ifndef POSTFIX_H
#define POSTFIX_H
#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include<string>
#include<string.h>
#include <vector>
#include <strings.h>
#include<stack>

using namespace std;

class Postfix
{
    public:
        Postfix();
        virtual ~Postfix();
        vector<string> to_postfix(vector<string> input);
        int contains(string s, char c);
        bool is_open_paranthesis(string character);
        bool is_relop(string character);
        bool is_closed_paranthesis(string character);
        bool is_any_operator(string character);
        bool is_higher_operator(string character);
        bool is_or(string a);
        bool is_character(string character);
        bool is_concatenation(string character);
        int precedence(string a, string b);
        bool possible_concatenation(vector<string> str);
        bool is_conc(string s);
        vector<string> add_conc(vector<string> str);

    protected:

    private:


};

#endif // POSTFIX_H
