#include "../../include/ParserInclude/ParsingTable.h"
#include "../../include/ParserInclude/ParsingTableHelpingFunctions.h"


ParsingTable::ParsingTable(vector<GrammerParser::NonTerminal>* _non_terminals,
                           GrammerParser* _gp) : gp(_gp), producesEps(NULL),
                                                 eps(-1),
                                                 end_of_input(-1),
                                                 symCount(-1),
                                                 numberOfNonTerminal(-1),
                                                 grammar(_non_terminals),
                                                 parsing_table(NULL),
                                                 parsing_table_states(NULL){}

ParsingTable::~ParsingTable()
{
    if (gp != NULL) {
        delete gp;
    }
    if (producesEps != NULL) {
        delete[] producesEps;
    }
    if (grammar != NULL) {
        delete grammar;
    }
    if (parsing_table != NULL) {
        for (int i = 0; i < numberOfNonTerminal; i++) {
            if (parsing_table[i] != NULL) {
                delete[] parsing_table[i];
            }
        }
        delete[] parsing_table;
    }
}
int ParsingTable::symbol_to_number(const string& symbol)
{
    if (gp == NULL) {
        throwErrors(Error::SYM_TO_NUM);
    }
    return this->gp->symbol_to_number(symbol);
}

string ParsingTable::number_to_symbol(int number)
{
    if (gp == NULL) {
        throwErrors(Error::NUM_TO_SYM);
    }
    return this->gp->number_to_symbol(number);
}

vector<int> ParsingTable::get_entry(int nonterminal, int terminal)
{
    if (gp == NULL) {
        throwErrors(Error::GET_ENTRY_UNINIT);
    }
    if (!validSymNums(nonterminal, terminal, symCount, numberOfNonTerminal)) {
        throwErrors(Error::GET_ENTRY_INVALID, nonterminal, terminal);
    }
    return parsing_table[nonterminal][terminal-numberOfNonTerminal];
}

void ParsingTable::init()
{
    this->numberOfNonTerminal = this->grammar->size();
    this->symCount = gp->getSymCount();
    this->eps = gp->get_epsilon();
    assert(eps != -1);
    this->end_of_input = this->symCount - 1;

    this->producesEps = new bool[this->numberOfNonTerminal]();

    for(int i = 0 ; i < numberOfNonTerminal ; i++){
        vector< vector<int> >& tempVec = grammar->at(i).rule;
        int x = tempVec.size();
        for (int j = 0; j < x; j++) {
            int y = tempVec[j].size();
            if(y == 1 && tempVec[j][0] == eps){
                producesEps[i] = true;
            }
        }
    }
}

bool ParsingTable::exist(string symbol)
{
    if (gp == NULL) {
        throwErrors(Error::IS_TERMINAL_UNINIT);
    }
    return this->gp->exist(symbol);
}


bool ParsingTable::isterminal(int number)
{
    if (gp == NULL) {
        throwErrors(Error::IS_TERMINAL_UNINIT);
    }
    return this->gp->isterminal(number);
}

ParsingTable::eleState ParsingTable::try_entery(int nonterminal, int terminal)
{
    if (gp == NULL) {
        throwErrors(Error::TRY_ENTRY_UNINIT);
    }
    if (!validSymNums(nonterminal, terminal, symCount, numberOfNonTerminal)) {
        throwErrors(Error::TRY_ENTRY_INVALID, nonterminal, terminal);
    }
    return parsing_table_states[nonterminal][terminal-numberOfNonTerminal];
}

//+++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++first+++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++

void ParsingTable::compute_first()
{
    bool* ready = new bool[numberOfNonTerminal]();
    for(int i = 0 ; i < numberOfNonTerminal ; i++){
        computeFirst(i,ready);
    }
    delete[] ready;
    printFirst(*this->grammar, this->numberOfNonTerminal);
}

void ParsingTable::computeFirst(int row , bool ready[])
{
    if(ready[row]){
        return;
    }
    vector< vector<int> >& tempRow = grammar->at(row).rule;
    int tempRowLen = tempRow.size();
    for(int j = 0 ; j < tempRowLen ; j++){
        vector<int>& tempVec = tempRow[j];
        int tempVecLen = tempVec.size();
        bool allHaveEps = true;
        grammar->at(row).mappedFirst.push_back(set<int>());
        for(int k = 0 ; k < tempVecLen ; k++){
            if(tempVec[k] >= numberOfNonTerminal){
                grammar->at(row).first.insert(tempVec[k]);
                grammar->at(row).mappedFirst[j].erase(eps);
                grammar->at(row).mappedFirst[j].insert(tempVec[k]);
                allHaveEps = false;
                break;
            }
            else{
                if(!ready[tempVec[k]] && tempVec[k] != row){
                    computeFirst(tempVec[k],ready);
                }
                grammar->at(row).first.insert(grammar->at(tempVec[k]).first.begin(), grammar->at(tempVec[k]).first.end());
                grammar->at(row).mappedFirst[j]
                                .insert(grammar->at(tempVec[k]).first.begin(),
                                        grammar->at(tempVec[k]).first.end());

                if(!producesEps[tempVec[k]]){
                    grammar->at(row).mappedFirst[j].erase(eps);
                    allHaveEps = false;
                    break;
                }
                // get +++++++++++++++++
                grammar->at(row).first.erase(eps);
                // *******************************
                // copy all values in first of tempVec[k]
                // if epslion found don't copy and go for next itration
            }
        }
        if(allHaveEps || producesEps[row]){
            grammar->at(row).first.insert(eps);
            producesEps[row] = true;
        }
    }
    ready[row] = true;
}

//+++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++follow+++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++

void ParsingTable::init_follow()
{
    //add end-of-input marker to the follow of start symbol
    grammar->at(0).follow.insert(end_of_input);

    memset(producesEps, false, numberOfNonTerminal);
    for(int i = 0 ; i < numberOfNonTerminal ; i++){
        set<int>& tempSet = grammar->at(i).first;
        if (tempSet.find(this->eps) != tempSet.end()) {
            producesEps[i] = true;
        }
    }
}

void ParsingTable::compute_follow()
{
    //initialize array producesEps
    init_follow();

    for(int i = 0 ; i < numberOfNonTerminal ; i++){
        for(vector<int> tempVec : grammar->at(i).rule){
            int tempVecLen = tempVec.size();
            bool inGraph = true;
            set<int> probagatedFollow;
            for(int j = tempVecLen - 1 ; j >= 0 ; j--){
                if(tempVec[j] >= numberOfNonTerminal){
                    inGraph = false;
                    probagatedFollow.clear();
                    probagatedFollow.insert(tempVec[j]);
                    continue;
                }
                if(inGraph){
                    grammar->at(tempVec[j]).adjList.push_back(i);

                }
                inGraph &= producesEps[tempVec[j]];
                grammar->at(tempVec[j]).follow.insert(probagatedFollow.begin(), probagatedFollow.end());
                if(!producesEps[tempVec[j]]){
                    probagatedFollow.clear();
                }
                probagatedFollow.insert(grammar->at(tempVec[j]).first.begin(), grammar->at(tempVec[j]).first.end());
            }
        }
    }
    for(int i = 0 ; i < numberOfNonTerminal ; i++){
        grammar->at(i).follow.erase(eps);
    }
    //topological sort
    vector<int> revAdjList[numberOfNonTerminal];
    reverseGraph(revAdjList, *grammar, numberOfNonTerminal);
    //order to traverse the graphwith, for top sort
    stack<int> *s = new stack<int>();
    bool *isVisited = new bool[numberOfNonTerminal]();
    for (int node = 0; node < numberOfNonTerminal; node++) {
        if (!isVisited[node]) {
            dfs(*s, node, revAdjList, isVisited);
        }
    }

    //follow of each group
    memset(isVisited, false, numberOfNonTerminal);
    vector<set<int> > groupFollow;

    int group = 0;
    int termToGroup[numberOfNonTerminal];
    while (!s->empty()) {
        int node = s->top();
        s->pop();
        if (!isVisited[node]) {
            set<int> temp;
            collectGroupFollow(node, isVisited, temp, group, termToGroup, *grammar);
            groupFollow.push_back(temp);
            group++;
        }
    }

    //groups adjacency list
    set<int> groupAdjList[group];
    for (int i = 0; i < numberOfNonTerminal; i++) {
        for (int node : grammar->at(i).adjList) {
            int source = termToGroup[i];
            int dest = termToGroup[node];
            if (source != dest) {
                groupAdjList[source].insert(dest);
            }
        }
    }
    //traverse groups
    memset(isVisited, false, numberOfNonTerminal);
    for (int i = 0; i < group; i++) {
        if (isVisited[i]) {
            continue;
        }
        groups_dfs(*s, i, groupAdjList, isVisited);
    }
    memset(isVisited, false, numberOfNonTerminal);
    while (!s->empty()) {
        int node = s->top();
        s->pop();
        if (isVisited[node]) {
            continue;
        }
        propagateFollow(node, groupAdjList, groupFollow, isVisited);
    }

    for (int i = 0; i < numberOfNonTerminal; i++) {
        int groupNum = termToGroup[i];
        grammar->at(i).follow = groupFollow[groupNum];
    }

    delete[] isVisited;
    delete s;
    printFollow(*this->grammar, this->numberOfNonTerminal);
}

//+++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++parsing table+++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++

void ParsingTable::construct_table()
{
    if (gp == NULL) {
        throwErrors(Error::CONS_UNINIT);
    }
    int numberOfTerminal = symCount - numberOfNonTerminal;
    //initializing parsing table and parsing table states
    parsing_table = new vector<int>*[numberOfNonTerminal];
    parsing_table_states = new ParsingTable::eleState*[numberOfNonTerminal];
    for (int i = 0; i < numberOfNonTerminal; i++) {
        parsing_table[i] = new vector<int>[numberOfTerminal]();
        parsing_table_states[i] = new ParsingTable::eleState[numberOfTerminal];
        for (int j = 0; j < numberOfTerminal; j++) {
            parsing_table_states[i][j] = ParsingTable::eleState::ERROR;
        }
    }

    //filling table with firsts
    for (int i = 0; i < numberOfNonTerminal; i++) {

        const GrammerParser::NonTerminal& nonTerm = grammar->at(i);
        const vector<set<int>>& first_mapped_prod = nonTerm.mappedFirst;
        const vector<vector<int>> productions = nonTerm.rule;

        int prod_num = 0;
        bool has_eps_in_first = false;
        int eps_production = -1;
        for (const set<int>& first_from_prod : first_mapped_prod) {
            for (int term : first_from_prod) {
                if (term != this->eps) {
                    int term_index = term - numberOfNonTerminal;
                    parsing_table[i][term_index] = productions[prod_num];
                    parsing_table_states[i][term_index] = ParsingTable::eleState::SUCCESS;
                } else {
                    if (has_eps_in_first) {
                        throwErrors(Error::TWO_EPS, i, eps_production, prod_num);
                    }
                    has_eps_in_first = true;
                    eps_production = prod_num;
                }
            }
            prod_num++;
        }

        //set state of follow
        ParsingTable::eleState follow_state;
        if (has_eps_in_first) {
            follow_state = ParsingTable::eleState::EPS;
        } else {
            follow_state = ParsingTable::eleState::SYNC;
        }
        set<int> follow = nonTerm.follow;
        for (int term : follow) {
            int term_index = term - numberOfNonTerminal;
            //make sure the grammar is correct
            if (has_eps_in_first) {
                if (parsing_table_states[i][term_index] == ParsingTable::eleState::SUCCESS) {//duplicate transition productions
                    throwErrors(Error::TWO_TRANS, i, term);
                }
                parsing_table[i][term_index] = productions[eps_production];
            }
            //see if the entry is vacant to make it sync
            if (parsing_table_states[i][term_index] != ParsingTable::eleState::SUCCESS) {
                parsing_table_states[i][term_index] = follow_state;
            }
        }

    }

}

const vector<int>** ParsingTable::getParsingTable()
{
    return (const vector<int>**)this->parsing_table;
}
