#include "../../include/LexicalInclude/Reader.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <strings.h>
#include <string>
#include <map>
#include <regex>
Reader::Reader()
{
    //ctor
}

Reader::~Reader()
{
    //dtor
}
string Reader::adjust_input(string input)
{
    string out = "";
    int number = 0;
    for(int i = input.size()-1 ; i >= 0 ; i--){
        if(input.at(i) != ' '){
            number = i;
            break;
        }
    }
    for(int i = 0 ; i <= number ; i++){
        out += input.at(i);
    }
    return out;
}

string Reader::remove_in_spaces(string s){
    string out = "";
    for(int i = 0 ; i < s.length() ; i++){
        if(s.at(i) != ' '){
            out += s.at(i);
        }
    }
    return out;
}
vector<string> Reader::get_postfix_vector(string s){

    std::stringstream ss(s);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> vstrings(begin, end);
    std::copy(vstrings.begin(), vstrings.end(), std::ostream_iterator<std::string>(std::cout, ""));
    //
    for(int i = 0 ; i < vstrings.size() ; i++){
        vstrings[i] = convert(vstrings[i]);
        //cout << "vstring "<< i << vstrings[i] <<endl;
    }



    return vstrings;
}
string Reader::convert(string s){
    regex r ("\\s*([0-9])\\s*[-]\\s*([0-9])\\s*");
    regex rr ("\\s*([a-z])\\s*[-]\\s*([a-z])\\s*");
    regex rrr ("\\s*([A-Z])\\s*[-]\\s*([A-Z])\\s*");
    if(regex_match(s, r) || regex_match(s, rr) || regex_match(s, rrr)){
        int i = p.contains(s, '-');
        string temp = "";
        int j = i;
        if(i >=0){
            i--;
            j++;
            char first , second ;
            while(i >= 0 && (s.at(i) == ' ' || s.at(i) == '\t')){
                i--;
            }
            while(j < (int)s.length() && (s.at(j) == ' ' || s.at(j) == '\t')){
                j++;
            }
            first = s.at(i);
            second = s.at(j);

            while(first != second){
                temp += first;
                temp += '|';
                first += 1;

            }
            temp += second;
            return temp;
        }
    }
    else
    {
        return s;
    }


}
string Reader::add_spaces(string s){

    string out = "";
    out += s.at(0);
    if((p.is_any_operator(out) || p.is_open_paranthesis(out))  ){
        out += " ";
    }

    for(int i = 1 ; i < (int)s.length() ; i++){
        string temp = "";
        temp += s.at(i);


        if((p.is_any_operator(temp) || p.is_open_paranthesis(temp) || p.is_closed_paranthesis(temp)  || temp == "\\" || (p.is_character(temp)) && s.at(i-1) != '\\') && s.at(i-1) != '\\' && s.at(i-1) != '-'){

            out += " ";
            out += temp;
            if(temp != "\\" && i+1 < (int)s.length() && s.at(i+1)!='-'){
               out += " ";
            }
        }else{
            out += temp;
        }
    }
    return out;
}
string Reader::pre_add_spaces(string s){
    string out = "";
    out += s.at(0);
    if((p.is_any_operator(out) || p.is_open_paranthesis(out))  ){
        out += " ";
    }

    for(int i = 1 ; i < (int)s.length() ; i++){
        string temp = "";
        temp += s.at(i);
        if((p.is_any_operator(temp) || p.is_open_paranthesis(temp) || p.is_closed_paranthesis(temp)) && s.at(i-1) != '\\' ){
            out += " ";
            out += temp;
            out += " ";

        }else{
            out += temp;
        }
    }
    return out;
}
string Reader::convert_postfix(string g){
    string v = pre_add_spaces(g);

    for (int i = def.size()-1 ; i >= 0 ; i--){

        string s = def[i].first;
        string c = "( ";
        c+=s;
        c+=" )";
        while(v.find(s) >= 0 && v.find(s) < v.length()){
            v = v.replace(v.find(s), sizeof(c)+2, c);
            v = v.replace(v.find(s), sizeof(pre_add_spaces(def[i].second))+2, pre_add_spaces(def[i].second));
        }
        //break;
    }
    return /*p.add_spaces*/pre_add_spaces(v);
}
string Reader::remove_end_spaces(const string &s)
{
    int last = s.size() - 1;
    while (last >= 0 && s[last] == ' ' && s[last] == '\t')
      --last;
    return s.substr(0, last + 1);
}
/*this function used to fill the Punctuations vector with the input string from file*/
void Reader::fill_punc(string str, char verifier){
    str = remove_end_spaces(str);

    int i = 0;
    string temp = "";
    while(str.at(i) == ' ' || str.at(i) == '\t'){
        i++;
    }
    if(str.at(i) == verifier){
        i++;
    }
    while(str.at(i) == ' '){
        i++;
    }
    for(int j = i ; j < (int)str.length(); j++){
        while(str.at(j)!=' '){
            if(str.at(j) == ']' && j == (int)str.length()-1){
                break;
            }
            temp += str.at(j);

            j++;

        }
        regex r("\\s*");
        if(str.at(j) == ' ' || str.at(j) == ']'){
            if(temp != "" && !regex_match(temp, r)){
                punc.push_back(temp);
            }
            temp = "";
        }
        if(str.at(j) == ']' && j == (int)str.length()-1){
            break;
        }
    }
}
/*this function used to fill the key_word vector with the input string from file*/
void Reader::fill_key_words(string str, char verifier){
    str = remove_end_spaces(str);
    int i = 0;
    string temp = "";
    while(str.at(i) == ' '|| str.at(i) == '\t'){
        i++;
    }
    if(str.at(i) == verifier){
        i++;
    }
    while(str.at(i) == ' ' || str.at(i) == '\t'){
        i++;
    }
    for(int j = i ; j < (int)str.length(); j++){
        while(str.at(j)!=' '){
            if(str.at(j) == '}' && j == (int)str.length()-1){
                break;
            }
            temp += str.at(j);

            j++;

        }
        regex r("\\s*");
        if(str.at(j) == ' ' || str.at(j) == '}'){
            if(temp != "" && !regex_match(temp, r)){

                key_words.push_back(temp);
            }
            temp = "";
        }
        if(str.at(j) == '}' && j == (int)str.length()-1){
            break;
        }
    }

}
/*this function used to fill the re map with the input string from file*/
void Reader::fill_re(string str, char verifier){
    string key = "";
    string value = "";
    int i = 0;
    while(str.at(i) == ' ' || str.at(i) == '\t'){
        i++;
    }
    while(i < (int)str.length() && str.at(i) != verifier){
        if(str.at(i) == ' ' || str.at(i) == '\t'){

        }else{
            key += str.at(i);
        }
        i++;
    }
    i++;
    while(str.at(i) == ' ' || str.at(i) == '\t'){
        i++;
    }
    while(i < (int)str.length()){
        value += str.at(i);
        i++;
    }
    value = remove_end_spaces(value);
    vector<string> vstrings = get_postfix_vector(add_spaces(convert_postfix(pre_add_spaces(value))));
    vector<string> f;
    for(int i = 0 ; i < (int)vstrings.size() ; i++){
        if(vstrings[i].length() > 1){
            vstrings[i] = pre_add_spaces(vstrings[i]);
        }
        vector<string> u = get_postfix_vector(vstrings[i]);
        f.insert(f.end(), u.begin(), u.end());
    }
    vector<string> t =p.add_conc(f);
    vector<string> a = p.to_postfix(t);


    std::map<string,vector<string>>::iterator it = re.begin();
    re.insert (it, std::pair<string,vector<string>>(remove_end_spaces(key),a));
}
/*this function used to fill the definitions map with the input string from file*/
void Reader::fill_definitions(string str, char verifier){
    string key = "";
    string value = "";
    int i = 0;
    while(str.at(i) == ' ' || str.at(i) == '\t'){
        i++;

    }

    while(i < (int)str.length() && str.at(i) != verifier){
        if(str.at(i) == ' ' || str.at(i) == '\t'){

        }else{
            key += str.at(i);
        }
        i++;
    }
    i++;

    while(str.at(i) == ' ' || str.at(i) == '\t'){
        i++;
    }
    while(i < (int)str.length()){
        value += str.at(i);
        i++;
    }

    pair<string, string> pa (remove_end_spaces(key), remove_end_spaces(/*add_spaces*/(remove_in_spaces(value))));
    def.push_back(pa);
    std::map<string,string>::iterator it = definitions.begin();
    definitions.insert (it, std::pair<string,string>(remove_end_spaces(key),remove_end_spaces(/*add_spaces*/(remove_in_spaces(value)))));
}
void Reader::read(){
    string input;
    regex definition("\\s*.[^:]+\\s*[=]\\s*.+");
    regex reg("\\s*.[^=]+\\s*[:]\\s*.+");
    regex key("\\s*[{]\\s*.+\\s*[}]");
    regex punct("\\s*\\[\\s*.+\\s*\\]");
    ifstream file ("file.txt");
    if(file.is_open()){
        while(getline(file, input)){
            if (regex_match((input), definition)) {
                fill_definitions(adjust_input(input), '=');
            }else if(regex_match(adjust_input(input), reg)){
                fill_re(input, ':');
            }else if(regex_match(adjust_input(input), key)){
                fill_key_words(adjust_input(input), '{');
            }else if(regex_match(adjust_input(input), punct)){
                fill_punc(input, '[');
            }else{
                cout << "error string"<<endl;
            }
        }
        file.close();
    }

}
/*prints the contents of definitions map*/
void Reader::print_definitions(){
    cout << "definitions_map"<<endl;
    std::map<string,string>::iterator it = definitions.begin();
    for (it=definitions.begin(); it!=definitions.end(); ++it)
        std::cout << it->first << "=> " << it->second << "\n";
    cout << "*****************************************"<<endl;
}
/*prints the contents of re map*/
void Reader::print_re(){
    cout << "re_map"<<endl;
    std::map<string,vector<string>>::iterator it = re.begin();
    for (it=re.begin(); it!=re.end(); ++it){
        std::cout << it->first << " => " << '\n';
        for (std::vector<string>::const_iterator j = re[it->first].begin(); j != re[it->first].end(); ++j)
            std::cout << *j << '\n';
        cout <<'\n'<<endl;
    }
    cout << "*****************************************"<<endl;
}
/*prints the contents of key_words vector*/
void Reader::print_key_words(){
    cout << "key_words_vector"<<endl;
    for (std::vector<string>::const_iterator i = key_words.begin(); i != key_words.end(); ++i)
        std::cout << "--" <<*i<<"--" << ' ';
    cout <<'\n'<<endl;
    cout << "*****************************************"<<endl;
}
/*prints the contents of punctuation vector*/
void Reader::print_punc(){
    cout << "punc_vector"<<endl;
    for (std::vector<string>::const_iterator i = punc.begin(); i != punc.end(); ++i)
        std::cout << "--" <<*i<<"--" << ' ';
    cout << "*****************************************"<<endl;
}
map<string, string> Reader::get_definitions(){

    return definitions;
}
map<string, vector<string>> Reader::get_regular_exp(){

    return re;
}
vector<string> Reader::get_key_words(){

    return key_words;
}
vector<string> Reader::get_punctuation(){

    return punc;
}
