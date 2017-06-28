#include "../../include/LexicalInclude/DFA.h"
#include "../../include/LexicalInclude/graph.h"
#include <bits/stdc++.h>

typedef pair<string, vertex*> ve;
typedef map<int, vertex*> vmap;
class Number_set;

using namespace std;
vector<int>* e_closure(vector<int>* vertices, graph* NFA);
vector<int>* e_closure(vertex* v);
vector<int>* mass_move(vector<int>* vertices, const string& input, graph* NFA);
vector<int>* mass_move(vertex* v, const string& input);
vector<string>* all_inputs(vmap& work);
string* get_accepting_type(Number_set* num_set, graph* NFA);
void make_transitions(Number_set* num_set);
bool verify(Data_Wrapper* data);
string remove_back_slash(const string& s);


class Number_set {
public:
    Number_set(vector<int>* _nums) : nums(_nums), transitions(new map<string, Number_set*>())
    {
        sort(nums->begin(), nums->end());
    }
    Number_set() : nums(NULL), transitions(NULL) {}

    bool operator()(Number_set* a, Number_set* b)
    {
        if (a->nums->size() != b->nums->size()) {
            return a->nums->size() < b->nums->size();
        }
        for (int i = 0; i < (int)a->nums->size(); i++) {
            if (a->nums->at(i) < b->nums->at(i)) {
                return true;
            } else if (a->nums->at(i) > b->nums->at(i)){
                return false;
            }
        }
        return false;
    }
    bool add_transition(const string& input, Number_set* dest)
    {
        pair<string, Number_set*> temp(input, dest);
        return transitions->insert(temp).second;
    }

public:
    vector<int>* nums;
    map<string, Number_set*>* transitions;
    bool is_accepting;
    DFA_state* equiv_state;
    int node_num;
};


//====================== DFA ===============================


DFA::DFA()
    : NFA(NULL), start(NULL), accepting(NULL), DFA_inputs(NULL), state_count(0) {}

void DFA::from_NFA(graph* NFA)
{
    assert(NFA != NULL);
    this->clear();
    this->NFA = NFA;

    set<Number_set*, Number_set>* marked_states = new set<Number_set*, Number_set>();
    stack<Number_set*>* dfs_stack = new stack<Number_set*>();
    vector<string>* inputs = all_inputs(NFA->work);
    this->DFA_inputs = inputs;
    //initialize stack
    Number_set* start = new Number_set(e_closure(NFA->get_vertex(0)));

    dfs_stack->push(start);
    marked_states->insert(start);
    int node_number = 0;
    start->node_num = node_number++;
    //begin dfs
    while (!dfs_stack->empty()) {
        Number_set* current = dfs_stack->top();
        dfs_stack->pop();
        //iterate over all possible inputs
        vector<string>::iterator iter = inputs->begin();
        for (; iter != inputs->end(); iter++) {
            //get states reachable through this input
            //vector<int>* state_nums = mass_move(e_closure(current->nums, NFA), *iter, NFA);
            vector<int>* temp1 = e_closure(mass_move(current->nums, *iter, NFA), NFA);
            vector<int>* temp2 = e_closure(mass_move(current->nums, "\\" + *iter, NFA), NFA);
            set<int> temp3(temp1->begin(), temp1->end());
            temp3.insert(temp2->begin(), temp2->end());

            vector<int>* state_nums = new vector<int>(temp3.begin(), temp3.end());
            delete temp1;
            delete temp2;

            if (state_nums->empty()) {continue;}
            Number_set* num_set = new Number_set(state_nums);
            //check if the sate is marked
            if (marked_states->find(num_set) == marked_states->end()) {
                num_set->node_num = node_number++;
                marked_states->insert(num_set);
                dfs_stack->push(num_set);
            } else {
                Number_set* temp = num_set;
                num_set = *marked_states->find(num_set);
                delete temp;
            }
            current->add_transition(*iter, num_set);
        }
    }

    //set dfa size
    this->state_count = node_number;

    delete dfs_stack;
    //construct equivalent DFA for each number set
    set<Number_set*, Number_set>::iterator iter;
    accepting = new vector<DFA_state*>();
    for (iter = marked_states->begin(); iter != marked_states->end(); iter++) {
        Number_set* num_set = *iter;

        cout << endl;
        cout << num_set->node_num << endl;
        for (auto iter2 = num_set->transitions->begin(); iter2 != num_set->transitions->end(); iter2++) {
            cout << "\t" << iter2->first << " : " << iter2->second->node_num << endl;
        }


        string* type = get_accepting_type(num_set, NFA);
        if (type != NULL) {
            *type = remove_back_slash(*type);
        }
        num_set->equiv_state = new DFA_state(type != NULL, num_set->node_num, type);
        //if accepting, keep it
        if (type != NULL) {
            this->accepting->push_back(num_set->equiv_state);
        }
    }
    //construct transitions
    for (iter = marked_states->begin(); iter != marked_states->end(); iter++) {
        Number_set* num_set = *iter;
        make_transitions(num_set);
    }
    //start state
    this->start = start->equiv_state;
    set<string> *temp = new set<string>();
    for (string s : *this->DFA_inputs) {
        temp->insert(remove_back_slash(s));
    }//correct the inputs
    delete this->DFA_inputs;
    this->DFA_inputs = new vector<string>(temp->begin(), temp->end());
    delete temp;

}

DFA_state* DFA::get_start()
{
    return start;
}

vector<int>* DFA::get_accepting()
{
    vector<int>* accepting_nums = new vector<int>();
    for (DFA_state* state : *this->accepting) {
        accepting_nums->push_back(state->state_num);
    }
    return accepting_nums;
}

vector<DFA_state*>* DFA::get_all()
{
    if (start == NULL) {
        return NULL;
    }
    vector<DFA_state*>* states = new vector<DFA_state*>();
    queue<DFA_state*>* bfs_queue = new queue<DFA_state*>();
    set<int> is_visited;

    bfs_queue->push(start);
    is_visited.insert(start->state_num);
    while (!bfs_queue->empty()) {
        DFA_state* current = bfs_queue->front();
        bfs_queue->pop();
        states->push_back(current);

        vector<pair<string, DFA_state*> >* temp = current->get_all();
        for (vector<pair<string, DFA_state*> >::iterator iter = temp->begin()
                ; iter != temp->end(); iter++) {
            pair<string, DFA_state*> temp = *iter;
            if (is_visited.find(temp.second->state_num) == is_visited.end()) {
                is_visited.insert(temp.second->state_num);
                bfs_queue->push(temp.second);
            }
        }
        delete temp;
    }

    delete bfs_queue;
    return states;
}

void DFA::print_all()
{
    ofstream fcout("dfa.txt");

    vector<DFA_state*>* v = get_all();
    for (auto iter = v->begin(); iter != v->end(); iter++) {
        DFA_state* current = *iter;
        vector<pair<string, DFA_state*> >* reachable = current->get_all();
        fcout << "node " << current->state_num;
        if (current->is_accepting())fcout << "(final) : " << *current->type;
        fcout << ":" << endl;
        for (auto iter2 = reachable->begin(); iter2 != reachable->end(); iter2++) {
            pair<string, DFA_state*> edge = *iter2;
            fcout << "\t\"" << edge.first << "\" -> ";
            if (edge.second == NULL) {
                fcout << "null";
            } else {
                fcout << "node " << edge.second->state_num;
            }
            fcout << endl;
        }
    }
    fcout.close();
}

Data_Wrapper* DFA::transition_table()
{
    if (this->start == NULL || this->DFA_inputs == NULL) {
        return NULL;
    }
    //map inputs to their indices in the vector of inputs
    map<string, int>* indices = new map<string, int>();
    int counter = 0;
    for (string input : *this->DFA_inputs) {
        indices->insert(make_pair(input, counter++));
    }
    //the vector holding state transitions
    vector<vector<int> >* transitions = new vector<vector<int> >(this->state_count, vector<int>(this->DFA_inputs->size(), -1));
    //get all states in the dfa
    vector<DFA_state*>* all_states = get_all();
    for (DFA_state* current : *all_states) {
        //all states reachable from current state
        vector<pair<string, DFA_state*> >* reachables = current->get_all();
        for (pair<string, DFA_state*> transition : *reachables) {
            int input_index = indices->find(transition.first)->second;
            transitions->at(current->state_num).at(input_index) = transition.second->state_num;
        }
        delete reachables;
    }
    delete all_states;
    delete indices;
    //exit(0);

    //wrap data
    Data_Wrapper* data = new Data_Wrapper();
    data->inputs = *this->DFA_inputs;
    data->transitions = *transitions;
    data->final_states = *get_accepting();

    vector<string>* token_types = new vector<string>();
    for (DFA_state* state : *this->accepting) {
        token_types->push_back(*state->type);
    }
    data->token_types = *token_types;
    return data;
}

void DFA::clear()
{
    //clear NFA if present
    if (NFA != NULL) {
        delete NFA;
        NFA = NULL;
    }
    //clear states if present
    vector<DFA_state*>* states = get_all();
    if (states != NULL) {
        for (DFA_state* state : *states) {
            delete state;
        }
        delete states;
        start = NULL;
    }
    //clear inputs if present
    if (DFA_inputs != NULL) {
        delete DFA_inputs;
        DFA_inputs = NULL;
    }
    //clear accepting
    if (accepting != NULL) {
        delete accepting;
        accepting = NULL;
    }
    state_count = 0;
}

bool DFA::from_transition_table(Data_Wrapper* data)
{
    //check validity
    if (!verify(data)) {
        return false;
    }
    //clear this object
    this->clear();

    this->DFA_inputs = &data->inputs;
    //add accepting states' information
    map<int, string>* acc_info = new map<int, string>();
    for (int i = 0; i < (int)data->final_states.size(); i++) {
        acc_info->insert(make_pair(data->final_states.at(i), data->token_types.at(i)));
    }

    //initialize states to with their numbers
    state_count = data->transitions.size();
    DFA_state** states = new DFA_state*[state_count];
    for (int i = 0; i < state_count; i++) {
        string* type = NULL;
        bool accepting = false;
        if (acc_info->find(i) != acc_info->end()) {
            type = new string(acc_info->find(i)->second);
            accepting = true;
        }
        states[i] = new DFA_state(accepting, i, type);
    }

    //add transitions
    for (int current = 0; current < state_count; current++) {
        vector<int>& temp = data->transitions.at(current);
        for (int i = 0; i < (int)temp.size(); i++) {
            int dest = temp[i];
            if (dest == -1) {
                continue;
            }
            states[current]->add_transition(data->inputs.at(i), states[dest]);
        }
    }

    //set accepting states
    accepting = new vector<DFA_state*>();
    for (int state : data->final_states) {
        accepting->push_back(states[state]);
    }
    //set start state
    start = states[0];

    delete acc_info;
    delete[] states;
    return true;
}

bool verify(Data_Wrapper* data)
{
    if (data->inputs.size() == 0
            || data->final_states.size() != data->token_types.size()) {
        return false;
    }
    for (vector<int>& v : data->transitions) {
        if (v.size() != data->inputs.size()) {
            return false;
        }
    }
    return true;
}



//======================= DFA_state =====================



DFA_state::DFA_state(bool _accepting, int _state_num, string* _type)
    : accepting(_accepting), state_num(_state_num), trans_table(new map<string, DFA_state*>()), type(_type) {}


bool DFA_state::is_accepting()
{
    return accepting;
}

bool DFA_state::add_transition(const string& input, DFA_state* state)
{
    assert(state != NULL);
    return trans_table->insert(make_pair(input, state)).second;
}

string DFA_state::get_type()
{
    if (this->type == NULL) {
        return "";
    }
    return *this->type;
}

DFA_state* DFA_state::move(string* input)
{
    if (input == NULL) {
        return NULL;
    }
    map<string, DFA_state*>::iterator iter = trans_table->find(*input);
    if (iter == trans_table->end()) {
        return NULL;
    }
    return iter->second;
}

vector<pair<string, DFA_state*> >* DFA_state::get_all()
{
    map<string, DFA_state*>::iterator iter;
    vector<pair<string, DFA_state*> >* states = new vector<pair<string, DFA_state*> >();
    for (iter = trans_table->begin(); iter != trans_table->end(); iter++) {
        states->push_back(make_pair(iter->first, iter->second));
    }
    return states;
}

//========================= helper functions =========================

vector<int>* e_closure(vertex* v)
{
    set<int> is_visited;
    stack<vertex*> dfs_stack;
    dfs_stack.push(v);
    is_visited.insert(v->name);

    while (!dfs_stack.empty()) {
        vertex* current = dfs_stack.top();
        dfs_stack.pop();
        vector<ve>& adj = current->adj;
        for (int i = 0; i < (int)adj.size(); i++) {
            pair<string, vertex*> temp = adj[i];
            if (temp.first == "\\L" && is_visited.find(temp.second->name) == is_visited.end()) {
                is_visited.insert(temp.second->name);
                dfs_stack.push(temp.second);
            }
        }
    }

    return new vector<int>(is_visited.begin(), is_visited.end());
}

vector<int>* e_closure(vector<int>* vertices, graph* NFA)
{
    set<int> added_vertices;

    for (vector<int>::iterator ver_iter = vertices->begin(); ver_iter != vertices->end(); ver_iter++) {
        //e-closure of this vertex
        vector<int>* temp = e_closure(NFA->get_vertex(*ver_iter));
        added_vertices.insert(temp->begin(), temp->end());
        delete temp;
    }
    return new vector<int>(added_vertices.begin(), added_vertices.end());
}

vector<int>* mass_move(vector<int>* vertices, const string& input, graph* NFA)
{
    set<int>* added_vertices = new set<int>();

    for (vector<int>::iterator ver_iter = vertices->begin(); ver_iter != vertices->end(); ver_iter++) {
        //e-closure of this vertex
        vector<int>* temp = mass_move(NFA->get_vertex(*ver_iter), input);
        added_vertices->insert(temp->begin(), temp->end());
        delete temp;
    }
    return new vector<int>(added_vertices->begin(), added_vertices->end());
}

vector<int>* mass_move(vertex* v, const string& input)
{
    vector<ve>& adj = v->adj;
    set<int>* result = new set<int>();

    for (int i = 0; i < (int)adj.size(); i++) {
        pair<string, vertex*> temp = adj[i];
        if (temp.first == input) {
            result->insert(temp.second->name);
        }
    }
    return new vector<int>(result->begin(), result->end());
}


vector<string>* all_inputs(vmap& work)
{
    set<string>* inputs = new set<string>();
    for (vmap::iterator iter = work.begin(); iter != work.end(); iter++) {
        vertex* temp_vertex = iter->second;
        const vector<ve> &adj = temp_vertex->adj;
        for (int j = 0; j < (int)adj.size(); j++) {
            inputs->insert(adj[j].first);
        }
    }
    inputs->erase("\\L");
    vector<string>* temp = new vector<string>(inputs->begin(), inputs->end());
    delete inputs;
    return temp;
}

string* get_accepting_type(Number_set* num_set, graph* NFA)
{
    vector<int>::iterator iter;
    for (iter = num_set->nums->begin(); iter != num_set->nums->end(); iter++) {
        vertex* vrtx = NFA->get_vertex(*iter);
        if (!vrtx->is_final) {
            continue;
        }
        return &vrtx->id;
    }
    return NULL;
}

void make_transitions(Number_set* num_set)
{
    DFA_state* dfa_state = num_set->equiv_state;
    map<string, Number_set*>::iterator iter;
    for (iter = num_set->transitions->begin(); iter != num_set->transitions->end(); iter++) {
        dfa_state->add_transition(remove_back_slash(iter->first), iter->second->equiv_state);
    }
}

string remove_back_slash(const string& s)
{
    string temp = s;
    for (int i = 0; i < temp.size(); i++) {
        if (temp[i] == '\\') {
            temp.erase(i, 1);
            break;
        }
    }
    return temp;
}
