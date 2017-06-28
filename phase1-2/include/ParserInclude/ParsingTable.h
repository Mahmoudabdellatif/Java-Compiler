#ifndef PARSINGTABLE_H
#define PARSINGTABLE_H
#include "GrammerParser.h"
#include <string>
#include <vector>

using namespace std;

class Parser;

class ParsingTable
{
    friend class Parser;
    public:
        enum class eleState;
        ParsingTable(vector<GrammerParser::NonTerminal>* _non_terminals, GrammerParser* _gp);
        virtual ~ParsingTable();
        int symbol_to_number(const string& symbol);
        string number_to_symbol(int number);
        vector<int> get_entry(int nonterminal, int terminal);
        void init();
        bool isterminal(int number);
        bool exist(string symbol);
        ParsingTable::eleState try_entery(int nonterminal, int terminal);
        const vector<int>** getParsingTable();
        void construct_table();

        enum class eleState {
            SUCCESS,
            SYNC,
            ERROR,
            EPS
        };

    private:
        /* member variables */
        GrammerParser* gp;
        bool *producesEps;
        int eps;
        int end_of_input;
        int symCount;
        int numberOfNonTerminal;
        vector<GrammerParser::NonTerminal>* grammar;
        vector<int>** parsing_table;
        ParsingTable::eleState** parsing_table_states;

        /* member functions */
        void compute_first();
        void computeFirst(int, bool*);
        void compute_follow();
        void init_follow();
};

#endif // PARSINGTABLE_H
