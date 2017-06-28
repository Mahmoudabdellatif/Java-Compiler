#ifndef PARSERENGINE_H
#define PARSERENGINE_H
#include "ParsingTable.h"
#include <string>
#include <vector>
#include <fstream>
#include "../LexicalInclude/LexicalAnalyzer.h"

using namespace std;

class ParserEngine
{
    public:
        ParserEngine(Lexical_analyzer* la, ParsingTable* pt);
        virtual ~ParserEngine();
        void parse(string file_name);

    private:
        Lexical_analyzer* lexer;
        ofstream output;
        vector<string> current_line;
        ParsingTable* parsing_table;
        void prepare_new_line(int top, vector<int> v);
        void print_error(int top, int cur, bool flag);
        void print_line();
        void remove_selected(int top);
};

#endif // PARSERENGINE_H
