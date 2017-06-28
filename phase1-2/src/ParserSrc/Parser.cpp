#include "../../include/ParserInclude/Parser.h"
#include "../../include/ParserInclude/GrammerParser.h"
#include "../../include/ParserInclude/ParsingTable.h"
#include "../../include/ParserInclude/ParserEngine.h"
#include "../../include/LexicalInclude/LexicalAnalyzer.h"
#include "../../include/ParserInclude/ParserEngine.h"

Parser::Parser(Lexical_analyzer* _lexer)
    : lexer(_lexer) {}

Parser::Parser() {}

void Parser::parse(const string& output_file)
{
    GrammerParser* grammar_parser = new GrammerParser();

    ParsingTable* parsing_table =
        new ParsingTable(grammar_parser->get_grammer(),
                         grammar_parser);
    //initializing table
    //cout << "shadyyyy\n" <<endl;
    grammar_parser->print_rep_ptr();
    grammar_parser->print_map();
    parsing_table->init();
    parsing_table->compute_first();
    parsing_table->compute_follow();



    parsing_table->construct_table();
    const vector<int>** table = parsing_table->getParsingTable();
    for (int i = 0; i < parsing_table->numberOfNonTerminal; i++) {
        int numt = parsing_table->symCount - parsing_table->numberOfNonTerminal;
        cout << "nonterm " << i << endl;
        for (int j = 0; j < numt; j++) {
            cout << "\tterm " << (j + parsing_table->numberOfNonTerminal) << ": ";
            for (int term : table[i][j]) {
                cout << term << " ";
            }
            cout << endl;
        }
    }

    ParserEngine* engine = new ParserEngine(this->lexer, parsing_table);

    try {
        engine->parse(output_file);
    } catch (runtime_error* e) {
        cout << e->what();
        throw e;
    }
}


Parser::~Parser()
{
    if (lexer != NULL) {
       // delete lexer;
    }
}
