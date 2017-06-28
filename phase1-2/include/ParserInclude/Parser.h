#ifndef PARSER_H
#define PARSER_H

#include <bits/stdc++.h>
#include "../../include/LexicalInclude/LexicalAnalyzer.h"

using namespace std;

class Lexical_analyzer;

class Parser
{
    public:
        Parser(Lexical_analyzer* _lexer);
        Parser();
        void parse(const string& output_file);
        virtual ~Parser();

    protected:

    private:
        Lexical_analyzer* lexer;
};

#endif // PARSER_H
