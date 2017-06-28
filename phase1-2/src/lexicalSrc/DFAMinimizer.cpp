#include "../../include/LexicalInclude/DFAMinimizer.h"


DFAMinimizer::DFAMinimizer(Data_Wrapper d)

{
    int len = d.inputs.size();
    for(int i = 0 ; i < len ; i++){
        inputs.push_back(d.inputs[i]);
    }
    dfa_minimizer(d.transitions, d.final_states, d.token_types);
}


void DFAMinimizer::dfa_minimizer(vector<vector<int>> trans, vector<int> final_states, vector<string> types)
{
    fill_map(final_states, types);

    int states_number = trans.size();
    bool is_final_states[states_number];
    for(int i = 0 ; i < states_number ; i++){
        is_final_states[i] = false;
    }

    int inputs_number = trans[0].size();

    int number_of_final_states = final_states.size();
    for(int i = 0 ; i < number_of_final_states ; i++){
        is_final_states[final_states[i]] = true;
    }

    int partition_one[states_number];
    int partition_two[states_number];

    for(int i = 0 ; i < states_number ;i++){
        partition_one[i] = 0;
        partition_two[i] = 0;

    }

    bool final_state_marked[number_of_final_states];
    for(int i = 0 ; i < number_of_final_states ; i++){
        final_state_marked[i] = false;
    }
    int temp_count_one = 1;
    for(int i = 0 ; i < number_of_final_states ; i++){
        if(final_state_marked[i]){
            continue;
        }
        for(int j = i ; j < number_of_final_states ; j++){
            if(final_state_marked[j]){
                continue;
            }
            if(types[i]==types[j]){
                //cout << partition_one[final_states[j]] << "\n" <<endl;
                partition_one[final_states[j]] = temp_count_one;
                if(partition_one[final_states[j]] != temp_count_one){
                    /**/
                }
                final_state_marked[j] = true;
            }
        }
        final_state_marked[i] = true;

        partition_one[final_states[i]] = temp_count_one;
        if(partition_one[final_states[i]] != temp_count_one){
                    /**/
        }
        temp_count_one++;
    }
    int current_number_of_partition = 0;
    int prev_number_of_partition = temp_count_one;
    while(prev_number_of_partition != current_number_of_partition){
        prev_number_of_partition = current_number_of_partition;
        current_number_of_partition = 0;
        bool similar[states_number];
        for(int i = 0 ; i < states_number ; i++){
            similar[i] = false;
        }
        for(int k = 0 ; k < states_number ; k++){
            if(similar[k]){
                continue;
            }
            for(int i =k+1 ; i < states_number ; i++){
                if(partition_one[k]!= partition_one[i]){
                    continue;
                }
                bool is_similar= true;
                for(int j = 0 ; j < inputs_number ; j++){
                    if(trans[k][j] == -1 && trans[i][j] == -1){
                        continue;
                    }
                    if((trans[k][j] == -1 || trans[i][j] == -1)){
                        is_similar = false;
                        break;
                    }
                    if(partition_one[trans[k][j]] != partition_one[trans[i][j]]){
                        is_similar = false;
                        break;
                    }
                }
                if(is_similar){
                    partition_two[i] = current_number_of_partition;
                    similar[i] = true;
                }

            }

            partition_two[k] = current_number_of_partition;
            similar[k] = true;
            current_number_of_partition++;
        }
        memcpy(partition_one, partition_two, states_number*sizeof(int));
        cout << "print Groups ########### \n" <<endl;
        for(int i = 0 ; i < states_number ; i++){
            cout << "state # "<< i << "in group" << partition_one[i] <<endl;
        }
        cout <<"\n"<<endl;
	}

    string final_states_type[current_number_of_partition];
    for(int i = 0 ; i < states_number ; i++){
        if(is_final_states[i]){
            final_states_type[partition_one[i]] = final_states_types[i];
        }
    }


    bool g[current_number_of_partition];
    int a[current_number_of_partition][inputs_number];
    bool isFinal[current_number_of_partition];
    for(int i = 0 ; i < current_number_of_partition ; i++){
        isFinal[i] = false;
        g[i] = false;
    }
    int numberOfFinalStatesGroups = 0;
    int row = 0;

    for(int i = 0 ; i < states_number ; i++){
        if(!g[partition_one[i]]){
            g[partition_one[i]] = true;
            if(is_final_states[i]){
                isFinal[row] = true;
                numberOfFinalStatesGroups++;
            }
            for(int j = 0 ; j < inputs_number ; j++){
                if(trans[i][j] == -1){
                    a[row][j] = -1;

                }
                else{
                    a[row][j] = partition_one[trans[i][j]];
                }

            }
            row++;
        }
    }
    int finialStatesGroup[numberOfFinalStatesGroups];

    int k = 0;
    string min_ty[numberOfFinalStatesGroups];
    for(int i = 0 ;i < current_number_of_partition ; i++){
        if(final_states_type[i] == ""){

        }else{
            min_ty[k++]= final_states_type[i];
        }
    }

    cout << "final states hassan"<<endl;
    for(int i = 0 ; i < numberOfFinalStatesGroups ; i++){
        cout << min_ty[i] <<endl;
    }
    cout << "\n end final states hassan" <<endl;

    int tempCount = 0;

    for(int i = 0 ; i < current_number_of_partition ; i++){
        if(isFinal[i]){
            finialStatesGroup[tempCount] = i;
            //final_states_type[tempCount] = final_states_types[i];
            tempCount++;
        }
    }
    cout << "inputs\n"<<endl;
    for(int i = 0 ; i < inputs_number ; i++){
        cout << " "<< inputs[i] << ", ";
    }
    cout << "\n end inputs"<<endl;
    cout << "final states kareem\n" <<endl;
    for(int i = 0 ; i < number_of_final_states ; i++){
        cout << final_states[i] << ", ";
    }
    cout << "end final states kareem\n" <<endl;
    cout << "types karim"<<endl;
    for(int i = 0 ; i < number_of_final_states ; i++){
        cout << types[i]<<", ";
    }
    cout << "\n end types karim" <<endl;
    cout << "print trans" <<endl;
    for(int i = 0 ; i < states_number ; i++){
        cout <<i << ", ";
        for(int j = 0 ; j < inputs_number ; j++){

            cout <<trans[i][j] << ", " ;
        }

        cout << "\n" <<endl;
    }

    cout << "end\n" <<endl;
    cout << "inputs\n"<<endl;
    for(int i = 0 ; i < inputs_number ; i++){
        cout << " "<< inputs[i] << ", ";
    }
    cout << "\n end inputs"<<endl;
    cout << "print a" <<endl;
    for(int i = 0 ; i < current_number_of_partition ; i++){
        cout <<i << ", ";
        for(int j = 0 ; j < inputs_number ; j++){
            cout << a[i][j] << ", " ;
        }
        cout << "\n" <<endl;
    }
    cout << "end\n" <<endl;

    vector<int> temp;
    for(int i = 0 ; i < numberOfFinalStatesGroups ; i++){
        final_states_min.push_back(finialStatesGroup[i]);
        types_min.push_back(min_ty[i]);
    }


    for(int i = 0 ; i < current_number_of_partition ; i++){
        for(int j = 0 ; j < inputs_number ; j++){
            temp.push_back(a[i][j]);
        }
        transistions.push_back(temp);
        temp.clear();
    }




}

void DFAMinimizer::fill_map(vector<int> a, vector<string> b)
{
    std::map<int,string>::iterator it = final_states_types.begin();
    for(int i = 0 ; i < (int)a.size() ; i++){
        final_states_types.insert (it, std::pair<int,string>(a[i], b[i]));

    }

    cout << "mappp"<<endl;
    std::map<int,string>::iterator it1 = final_states_types.begin();
    for (it1=final_states_types.begin(); it1!=final_states_types.end(); ++it1){
        std::cout << it1->first << " => " << '\n';
        std::cout << it1->second << " => " << '\n';
    }
    cout << "*****************************************"<<endl;
}
vector<vector<int>> DFAMinimizer::get_transitions()
{
    return transistions;
}

vector<string> DFAMinimizer::get_type_of_final_states()
{
    return types_min;
}

vector<int> DFAMinimizer::get_final_states()
{
    return final_states_min;
}
vector<string> DFAMinimizer::get_inputs()
{
    return inputs;
}

Data_Wrapper DFAMinimizer::get_data()
{
    dw.final_states = get_final_states();
    dw.token_types = get_type_of_final_states();

    dw.transitions = get_transitions();
    return dw;
}

