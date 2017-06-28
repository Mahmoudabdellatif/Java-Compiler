#ifndef READER_H
#define READER_H
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <regex>
#include <fstream>
#include "Postfix.h"
using namespace std;
class Reader
{
    public:
        Reader();
        virtual ~Reader();
        void read();
        void print_definitions();
        void print_re();
        void print_key_words();
        void print_punc();
        map<string, string> get_definitions();
        map<string, vector<string>> get_regular_exp();
        vector<string> get_key_words();
        vector<string> get_punctuation();
        string add_spaces(string s);
        string convert(string s);
        vector<string> get_postfix_vector(string s);
        string convert_postfix(string);
        string pre_add_spaces(string g);
        string remove_in_spaces(string s);

    protected:

    private:
        Postfix p;
        vector<pair<string, string>> def;
        string input;
        map<string, string> definitions;
        map<string, vector<string>> re;
        vector<string> punc;
        vector<string> key_words;
        string remove_end_spaces(const string &s);
        void fill_punc(string str, char verifier);
        void fill_key_words(string str, char verifier);
        void fill_re(string str, char verifier);
        void fill_definitions(string str, char verifier);
        string adjust_input(string input);

};

#endif // READER_H
