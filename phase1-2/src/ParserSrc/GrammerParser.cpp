#include "../../include/ParserInclude/GrammerParser.h"
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <fstream>


GrammerParser::GrammerParser()
{
    //ctor
}

GrammerParser::~GrammerParser()
{
    //dtor
}

/*it returns the number equivalent for the epsilon*/
int GrammerParser::get_epsilon()
{
    if(string_to_number.find("\\L") == string_to_number.end()){
        return -1;
    }
    return string_to_number["\\L"];
}
/*it returns the total number of terminal and non terminals*/
int GrammerParser::getSymCount()
{
    return string_to_number1.size();
}

/*it removes the extra spaces from string*/
string GrammerParser::remove_end_spaces(const string &s)
{
    int last = s.size() - 1;
    while (last >= 0 && (s[last] == ' ' || s[last] == '\t'))
      --last;
    return s.substr(0, last + 1);
}
/*given the string of the symbol it returns the equivalent number*/
int GrammerParser::symbol_to_number(const string& symbol)
{
    return string_to_number1[symbol];
}

/*it decides whether the symbol is terminal or nonterminal*/
bool GrammerParser::isterminal(int symbol)
{
        return symbol >= (int)grammer.size()  ;
}

/*given the number of the symbol it returns the equivalent string*/
string GrammerParser::number_to_symbol(int number)
{
    return number_to_string1[number];
}

bool GrammerParser::exist(string symbol)
{
    map<string, int>::iterator it = string_to_number1.find(symbol);
    if(it != string_to_number1.end()){
        return isterminal(string_to_number1[symbol]);
    }
    return false;
}


/*this function used to return the grammar*/
vector<GrammerParser::NonTerminal>* GrammerParser::get_grammer()
{
    read("");
    vector<GrammerParser::NonTerminal> number_grammer;
    GrammerParser::NonTerminal non_term;
    vector<vector<int>> vec;
    vector<int> v;
    for(int i = 0 ; i < (int)gram.size() ; i++){
        std::istringstream buf(gram[i]);
        std::istream_iterator<std::string> beg(buf), end;
        std::vector<std::string> tokens(beg, end);
        for(string s : tokens){
            if(s == "|")
            {
                vec.push_back(v);
                v.clear();
            }
            else
            {
                int thevalue;
                std::istringstream ss(s);
                ss >> thevalue;
                v.push_back(thevalue);

            }
        }
        if(v.size() > 0)
        {
            vec.push_back(v);
            v.clear();
        }
        non_term.rule = vec;

        number_grammer.push_back(non_term);


        vec.clear();
    }

    grammer = number_grammer;


    //added pointer to each integer
    for(size_t i = 0 ; i < grammer.size() ; i++){
        vector<vector<int>> r = grammer[i].rule;
        vector<vector<int*>> v_ptr;
        for(size_t j = 0 ; j < r.size(); j++){
            vector<int*> h;
            for(size_t c = 0 ; c < r[j].size() ; c++){
                int *ptr = &string_to_number[number_to_string[r[j][c]]];
                h.push_back(ptr);
            }
            v_ptr.push_back(h);
        }
        grammer[i].rule_ptr = v_ptr;
    }
    eliminate_left_recursion();

    return &grammer;
}

/*this function prints the pointer array*/
void GrammerParser::print_rep_ptr(){
    for(size_t i = 0 ; i < grammer.size() ; i++){
        vector<vector<int>> v_ptr = grammer[i].rule;
        for(size_t j = 0 ; j < v_ptr.size(); j++){
            for(size_t c = 0 ; c < v_ptr[j].size() ; c++){
                cout << v_ptr[j][c] <<", ";

            }
            cout << " - ";

        }
        cout <<"\n";

    }
}

/*this function replace string in place*/
void GrammerParser::replace_string(std::string& subject, const std::string& search, const string& replace)
{
    subject += " ";
    size_t pos = 0;
    string g  = "";
    while ((pos = subject.find(search, pos)) != string::npos) {
         int y = pos + search.size();

         if(search != "\'"){
            if((pos > 0 && subject.at(pos-1)!=' ' && subject.at(pos-1)!='|') || (subject.at(y)!=' '  && subject.at(y)!='|') ){
                break;
             }
         }
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
}
/*this function is used to fill the maps with terminals that presented between single quotes*/
int GrammerParser::fill_maps_terminals(string g, int counter)
{
    std::map<string,int>::iterator it;
    string f = "";
    int c = counter;
    for(size_t i = 0 ; i < g.size(); i++){
        if(g.at(i) == '\''){
            f += g.at(i);
            i++;
            while(g.at(i) != '\''){
                f += g.at(i);
                i++;
            }
            f += g.at(i);
            it = string_to_number.find(f);
            if(!(it != string_to_number.end())){
                string_to_number.insert (std::pair<string,int>((f), c));
                number_to_string.insert (std::pair<int,string>(c, (f)));
                c++;
            }
            f = "";
        }
    }
    if(c > counter){
        return c;
    }else{
        return counter;
    }
}
/*this function used to read the file*/
void GrammerParser::read(string file_name)
{
    int counter = 0;
    string temp = "", input = "";
    regex rgx("\\s*(#)\\s*(.[^=]+)\\s*(=)\\s*(.+)\\s*");
    std::smatch matches;
    ifstream file ("file1.txt");
    if(file.is_open()){
        while(getline(file, input))
        {
            if(regex_match(input, rgx))
            {
                if(temp != "")
                {
                    if(std::regex_search(temp, matches, rgx))
                    {
                        string_to_number.insert (std::pair<string,int>(remove_end_spaces(matches[2].str()),counter));
                        number_to_string.insert (std::pair<int,string>(counter, remove_end_spaces(matches[2].str())));
                        counter++;
                    }
                    else
                    {
                    }
                    gram.push_back(matches[4].str());
                    temp = "";
                }
                temp += input;
            }
            else
            {
                temp += input;
                temp += " ";
            }
        }
        if(temp != ""){
            if(std::regex_search(temp, matches, rgx))
            {
                string_to_number.insert (std::pair<string,int>(remove_end_spaces(matches[2].str()),counter));
                number_to_string.insert (std::pair<int,string>(counter, remove_end_spaces(matches[2].str())));
                counter++;
            }
            else
            {
                //std::cout << "Match not found\n";
            }
            gram.push_back(matches[4].str());
        }
        file.close();

        for(int i = 0 ; i < (int)gram.size() ; i++){
            counter = fill_maps_terminals(gram[i], counter);
        }
        std::map<int,string>::iterator it;
        for(int i = 0 ; i < (int)gram.size() ; i++){
            for (it=number_to_string.begin(); it!=number_to_string.end(); ++it){
                string myint_str =' ' +  static_cast<ostringstream*>( &(ostringstream() << it->first) )->str() + ' ';
                replace_string(gram[i], it->second, myint_str);
            }

        }

    }
}
/*this function prints the maps*/
void GrammerParser::print_map()
{
    std::map<string,int>::iterator it = string_to_number1.begin();
    std::cout << "string to int contains:\n";
    for (it=string_to_number1.begin(); it!=string_to_number1.end(); ++it)
        std::cout << it->first << "=>" << it->second << '\n';

    std::map<int,string>::iterator it1 = number_to_string1.begin();
    std::cout << "int to string contains:\n";
    for (it1=number_to_string1.begin(); it1!=number_to_string1.end(); ++it1)
        std::cout << it1->first << "=>" << it1->second << '\n';
}


/*this function used to replace rules ex: A = B a, B = A b becomes  A = B a, B = B a b*/
void GrammerParser::replace_rules(int i, int c, int j)
{
    vector<int> g = grammer[i].rule[c];
    vector<int*> g_ptr = grammer[i].rule_ptr[c];
    vector<int> after;
    vector<int*> after_ptr;
    for(int z = 1 ; z < (int)g.size() ; z++){
        after.push_back(g[z]);
        after_ptr.push_back(&string_to_number[number_to_string[g[z]]]);

    }
    vector<vector<int>> v = grammer[j].rule;
    vector<vector<int*>> v_ptr = grammer[j].rule_ptr;
    if(after.size() > 0){
        for(int k = 0 ; k < (int)v.size() ; k++){
            for(int u = 0 ; u < (int)after.size() ; u++){
                v[k].push_back(after[u]);
                v_ptr[k].push_back(&string_to_number[number_to_string[after[u]]]);

            }
        }
    }

    grammer[i].rule.erase(grammer[i].rule.begin()+c);
    grammer[i].rule_ptr.erase(grammer[i].rule_ptr.begin()+c);


    for(int x = 0 ; x < (int)v.size() ; x++){
        grammer[i].rule.insert(grammer[i].rule.begin() + c + x, v[x]);
        grammer[i].rule_ptr.insert(grammer[i].rule_ptr.begin() + c + x, v_ptr[x]);
    }



}

/*this function eliminates immediate left recursion from nonterminals after replacing the rules*/
void GrammerParser::eliminate_immediate_left_recursion(int i)
{
    vector<vector<int>> beta; vector<vector<int*>> beta_ptr;
    vector<vector<int>> alpha; vector<vector<int*>> alpha_ptr;
    vector<int> temp_alpha; vector<int*> temp_alpha_ptr;
    vector<int> temp_beta; vector<int*> temp_beta_ptr;
    vector<int> o = contain(i, i);
    if(o.size() > 0){

        new_name.push_back(number_to_string[i] + "`");
        for(int c = 0 ; c < (int)o.size() ; c++){
            for(int j = 1 ; j < (int)grammer[i].rule[o[c]].size() ; j++){
                temp_alpha.push_back(grammer[i].rule[o[c]][j]);
                temp_alpha_ptr.push_back(&string_to_number[number_to_string[grammer[i].rule[o[c]][j]]]);
            }
            if(temp_alpha.size() > 0){
                alpha.push_back(temp_alpha);
                alpha_ptr.push_back(temp_alpha_ptr);
                temp_alpha.clear();
                temp_alpha_ptr.clear();
            }
        }
        //get all vectors contain betas
        vector<int> b;
        for(int j = 0 ; j < (int)grammer[i].rule.size() ; j++){
            if(grammer[i].rule[j][0] != i){
                b.push_back(j);
            }
        }
        //fill beta
        for(int j = 0 ; j < (int)b.size() ; j++){
            for(int h = 0 ; h < (int)grammer[i].rule[b[j]].size() ; h++){
                temp_beta.push_back(grammer[i].rule[b[j]][h]);
                temp_beta_ptr.push_back(&string_to_number[number_to_string[grammer[i].rule[b[j]][h]]]);
            }
            if(temp_beta.size() > 0){
                beta.push_back(temp_beta);
                beta_ptr.push_back(temp_beta_ptr);
                temp_beta.clear();
                temp_beta_ptr.clear();
            }
        }
        int x = grammer.size() + added.size();
        left_rec.insert(std::pair<int,int>(i, x));
        if(alpha.size() > 0){

            for(int j = 0 ; j < (int)alpha.size();  j++){
                alpha[j].push_back(x);
                alpha_ptr[j].push_back(&left_rec[i]);
            }
        }

        if(beta.size() > 0 && alpha.size() > 0){
            for(int j = 0 ; j < (int)beta.size();  j++){
                beta[j].push_back(x);
                beta_ptr[j].push_back(&left_rec[i]);
            }
            grammer[i].rule = beta;
            grammer[i].rule_ptr = beta_ptr;

            GrammerParser::NonTerminal non;
            non.rule = alpha;
            non.rule_ptr = alpha_ptr;
            added.push_back(non);
        }
    }
}
/*this function returns all occurrence of nonterminal j in the nonterminal i  */
vector<int> GrammerParser::contain(int i, int j)
{

    vector<vector<int>> v = grammer[i].rule;
    vector<int> d;
    for(int k = 0 ; k < (int)v.size() ; k++){
        if(v[k][0] == j){
            d.push_back(k);
        }
    }
    return d;
}



/*this function iterate over the whole nonterminals and replace rules and eliminate left recursion if exist*/
void GrammerParser::eliminate_left_recursion()
{
    for(int i = 0 ; i < (int)gram.size() ; i++){
        for(int j = 0 ; j < i ; j++){
            vector<int> r = contain(i, j);
            if(r.size() > 0){
                for(int c = 0 ; c < (int)r.size() ; c++){
                    replace_rules(i, r[c], j);
                }
            }
        }
        eliminate_immediate_left_recursion(i);
    }
    adjust_maps();
}

/*this function modify the map according to the added values of the left recursion*/
void GrammerParser::adjust_maps()
{
    map<string, int>::iterator it = string_to_number.begin();

    for(it = string_to_number.begin() ; it != string_to_number.end() ; ++it){
        if(it->second >=(int)gram.size()){
            it->second += added.size();
        }
    }
    int num = gram.size();
    for(int i = 0 ; i < (int)new_name.size() ; i++){
        string_to_number[new_name[i]] = num++;
        gram.push_back("");
    }

    //3adel el map
    map<string, int>::iterator it8 = string_to_number.find("\\L");

    if(it8 == string_to_number.end()){
        int u = string_to_number.size();
        string_to_number["\\L"] = u;
        number_to_string[u] = "\\L";
    }
    number_to_string.clear();
    map<string, int>::iterator it4;
    for(it4 = string_to_number.begin(); it4 != string_to_number.end(); ++it4){
        number_to_string.insert(pair<int, string> (it4->second, it4->first));
    }
    vector<int> k;
    vector<int*> k_ptr;
    k.push_back(get_epsilon());
    k_ptr.push_back(&string_to_number["\\L"]);
    if(added.size() > 0){
        for(int i = 0 ; i < (int)added.size() ; i++){
            added[i].rule.push_back(k);
            added[i].rule_ptr.push_back(k_ptr);
            grammer.push_back(added[i]);

        }
    }
    for(size_t i = 0 ; i < grammer.size() ; i++){
        for(size_t j = 0 ; j < grammer[i].rule.size() ; j++){
            for(size_t c = 0 ; c < grammer[i].rule[j].size() ; c++){
                grammer[i].rule[j][c] = *grammer[i].rule_ptr[j][c];
            }
        }
    }

    eliminate_left_factoring();
    map<string, int>::iterator it6 = string_to_number.begin();

    for(it6 = string_to_number.begin() ; it6 != string_to_number.end() ; ++it6){
        if(it6->second >=(int)gram.size()){
            it6->second += added_lf.size();
        }
    }
    for(int i = 0 ; i < (int)new_name_lf.size() ; i++){
        string_to_number[new_name_lf[i]] = num++;
        gram.push_back("");
    }

    map<string, int>::iterator it1 = string_to_number.begin();
    for(it1 = string_to_number.begin() ; it1 != string_to_number.end() ; ++it1){
        string temp = it1->first;
        if(it1->second >= (int)gram.size() + (int)added_lf.size()-1){
            replace_string(temp, "'", "");
        }
        string_to_number1.insert(std::pair<string, int>(remove_end_spaces(temp), it1->second));
        number_to_string1.insert(std::pair<int, string>(it1->second, remove_end_spaces(temp)));
    }

    map<string, int>::iterator it2 = string_to_number1.find("\\L");

    if(it2 == string_to_number1.end()){
        int u = string_to_number1.size();
        string_to_number1["\\L"] = u;
        number_to_string1[u] = "\\L";
    }
    string_to_number1.insert(std::pair<string, int>("$", string_to_number1.size()));
    number_to_string1.insert(std::pair<int, string>(number_to_string1.size(), "$"));

    for(size_t i = 0 ; i < grammer.size() ; i++){
        for(size_t j = 0 ; j < grammer[i].rule.size() ; j++){
            for(size_t c = 0 ; c < grammer[i].rule[j].size() ; c++){
                grammer[i].rule[j][c] = *grammer[i].rule_ptr[j][c];
            }
        }
    }
}

void GrammerParser::eliminate_left_factoring()
{
    for(size_t i = 0 ; i < gram.size() ; i++){
        prod = grammer[i].rule;
        v_ptr = grammer[i].rule_ptr;
        counter = grammer.size() + added_lf.size()-1;
        eliminate_LF(i);
        grammer[i].rule = prod;
        grammer[i].rule_ptr = v_ptr;
    }
}

void GrammerParser::eliminate_LF(int id)
{
    int num=1;
    map<int, vector<vector<int>>> m;
    map<int, vector<vector<int>>>::iterator it;
    for(int i=0; i<(int)prod.size(); i++){
        it = m.find(prod[i][0]);
        if(it == m.end()){
            vector<vector<int>> v;
            v.push_back(prod[i]);
            m[prod[i][0]] = v;
        }
        else{
            vector<vector<int>> v = it->second;
            v.push_back(prod[i]);
            m[prod[i][0]] = v;
        }
    }
    pr_map(m);

    for(it=m.begin(); it!=m.end(); it++){
        vector<vector<int>> v = it->second;
        if((int)v.size()==1) continue;
        int e = find_LCP(v);
        vector<int> newV(v[0].begin(), v[0].begin()+e);
        vector<int*> new_v_ptr;
        for(size_t i = 0 ; i < newV.size() ; i++){
            new_v_ptr.push_back(&string_to_number[number_to_string[newV[i]]]);
        }
        adjust_prod(v[0][0], id, newV, new_v_ptr);
        create_newP(e, num, id, v);
    }
    pr_P(prod);

}

void GrammerParser::adjust_prod(int s, int id, vector<int>newV, vector<int*> new_v_ptr)
{

    vector<vector<int>> temp = prod;
    vector<vector<int*>> temp_ptr = v_ptr;
    prod.clear();
    v_ptr.clear();
    counter++;
    left_fac.insert(pair<int, int> (id, counter));
    newV.push_back(counter);
    new_v_ptr.push_back(&left_fac[id]);
    prod.push_back(newV);
    v_ptr.push_back(new_v_ptr);
    for(int i=0; i<(int)temp.size(); i++){
        if(temp[i][0] != s){
            prod.push_back(temp[i]);
            v_ptr.push_back(temp_ptr[i]);
        }
    }
}

void GrammerParser::create_newP(int s, int num, int id, vector<vector<int>>v)
{
    vector<vector<int>> newP;
    vector<vector<int*>> newP_ptr;
    vector<int*> newP_ptr_temp;
    for(int i=0; i<(int)v.size(); i++){
        vector<int> newV(v[i].begin()+s, v[i].end());
        if(newV.empty()){
            map<string, int>::iterator it = string_to_number.find("\\L");
            if(it != string_to_number.end()){
            }else{
                string_to_number.insert(pair<string, int> ("\\L", string_to_number.size()));
                number_to_string.insert(pair<int, string> (number_to_string.size(), "\\L"));
            }
            newV.push_back(string_to_number["\\L"]);
        }
        newP.push_back(newV);
    }
    string sym = number_to_string[id];
    string myint_str =static_cast<ostringstream*>( &(ostringstream() << num) )->str();
    sym += myint_str;
    new_name_lf.push_back(sym);
    for(size_t i = 0 ; i < newP.size() ; i++){
        for(size_t j = 0 ; j < newP[i].size() ; j++){
            newP_ptr_temp.push_back(&string_to_number[number_to_string[newP[i][j]]]);
        }
        newP_ptr.push_back(newP_ptr_temp);
        newP_ptr_temp.clear();
    }


    GrammerParser::NonTerminal non;
    non.rule = newP;
    non.rule_ptr = newP_ptr;
    added_lf.push_back(non);
    grammer.push_back(non);
    // add hena ya shady , el index=counter
    pr_P(newP);
    num++;

}

void GrammerParser::pr_P(vector<vector<int>>v)
{
    for(int i=0; i<(int)v.size(); i++){
        for(int j=0; j<(int)v[i].size(); j++){
            cout<< v[i][j] <<" ";
        }
        cout<< "| ";
    }
    cout<<endl;

}

void GrammerParser::pr_map(map<int, vector<vector<int>>>m)
{
    map<int, vector<vector<int>>>::iterator it;
    for(it=m.begin(); it!=m.end(); it++){
        cout << it->first << " => "<<endl;
        vector<vector<int>> v = it->second;
        for(int j=0; j<(int)v.size(); j++){
            cout <<"\t";
            for(int i=0; i<(int)v[j].size(); i++){
                cout << v[j][i]<<" ";
            }
            cout <<endl;
        }
    }

}

int GrammerParser::find_LCP(vector<vector<int>>v)
{
    vector<int> minStr=v[0];

    for(int i=1;i<(int)v.size();i++){
        if(v[i].size()<minStr.size())
            minStr=v[i];
    }
    int res = (int)minStr.size();
    for(int i=0;i<(int)v.size();i++){
        int j;
        for( j=0;j<res;j++){
            if(minStr[j]!=v[i][j])
                break;
        }
        if(j<res)
            res=j;
    }
    return res;

}
