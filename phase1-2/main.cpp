#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "include\LexicalInclude\NFABuilder.h"
#include "include\LexicalInclude\LexicalAnalyzer.h"
#include <stdio.h>
#include "include\LexicalInclude\Reader.h"
#include "include\LexicalInclude\DFA.h"
#include "include/ParserInclude/Parser.h"
#include "include/ParserInclude/GrammerParser.h"
#include <regex>

using namespace std;



int main()
{


    //freopen("out.txt", "w", stdout);
    /*GrammerParser gp;
    vector<GrammerParser::NonTerminal>& v = *gp.get_grammer();
    gp.print_map();
    gp.print_rep_ptr();*/


    Lexical_analyzer analyzer("source.txt", "output.txt");
    //while (analyzer.next_token() != NULL);
    Parser parser(&analyzer);
    parser.parse("parsing_output.txt");

    freopen("sym.txt", "w", stdout);
    set<string>* sym_table = analyzer.get_symbol_table();
    for (string s : *sym_table) {
        cout << s << endl;
    }


    return 0;
}
