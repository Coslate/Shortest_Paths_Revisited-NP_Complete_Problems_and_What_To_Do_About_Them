//solution.cpp
#include <solution.h>

inline void randomInitialAssignment(const std::vector<intpair> &input_clause_list, std::unordered_map<int, bool> &variable_val){
    for(const auto &val_pair : input_clause_list){
        variable_val[abs(val_pair.first)] = (bool)(rand() % 2);
        variable_val[abs(val_pair.second)] = (bool)(rand() % 2);
    }
}

inline bool evalClause(std::unordered_map<int, bool> &variable_val, const intpair &val_pair, const int &first_index, const int &second_index){
    bool first_val  = (val_pair.first < 0)  ? !variable_val[first_index]  : variable_val[first_index];
    bool second_val = (val_pair.second < 0) ? !variable_val[second_index] : variable_val[second_index];
    
    return (first_val | second_val);
}

void clauseReduction(const std::vector<intpair> &input_clause_list, std::vector<intpair> &reduced_clause_list, int &total_num_var_reduced){
    std::vector<intpair> inspect_clause_list = input_clause_list;

    while(inspect_clause_list.size() != 0){
        std::unordered_map<int, int> map_index2freq;
        std::vector<intpair> reduced_clause_iter_list;
        bool get_new_ruled_out = false;

        //do the statistic of the occurence of each variable. xi and ~xi are two individual variables.
        for(const auto &clause_pair : inspect_clause_list){
            //std::cout<<"inspect : "<<clause_pair.first<<", "<<clause_pair.second<<std::endl;
            if(map_index2freq.find(clause_pair.first) == map_index2freq.end()){
                map_index2freq[clause_pair.first] = 1;
            }else{
                ++map_index2freq[clause_pair.first];
            }

            if(map_index2freq.find(clause_pair.second) == map_index2freq.end()){
                map_index2freq[clause_pair.second] = 1;
            }else{
                ++map_index2freq[clause_pair.second];
            }
        }

        //reduce those input clause that only has one occurence of a variable
        for(const auto &clause_pair : inspect_clause_list){
            if(((map_index2freq.find(clause_pair.first) != map_index2freq.end()) && (map_index2freq.find((clause_pair.first*-1)) == map_index2freq.end())) || ((map_index2freq.find(clause_pair.second) != map_index2freq.end()) && (map_index2freq.find((clause_pair.second*-1)) == map_index2freq.end()))){
                get_new_ruled_out = true;
                continue;
            }else{
                reduced_clause_iter_list.push_back(clause_pair);
            }
        }

        if(!get_new_ruled_out){
            reduced_clause_list.assign(reduced_clause_iter_list.begin(), reduced_clause_iter_list.end());
            std::unordered_set<int> map_existed_var;

            for(const auto &clause_pair : reduced_clause_list){
                int first_var = (clause_pair.first > 0) ? clause_pair.first : !clause_pair.first;
                int second_var = (clause_pair.second > 0) ? clause_pair.second : !clause_pair.second;

                if(map_existed_var.find(first_var) == map_existed_var.end()){
                    ++total_num_var_reduced;
                    map_existed_var.insert(first_var);
                }

                if(map_existed_var.find(second_var) == map_existed_var.end()){
                    ++total_num_var_reduced;
                    map_existed_var.insert(second_var);
                }
            }
            break;
        }

        //copying vector by assign function 
	    inspect_clause_list.assign(reduced_clause_iter_list.begin(), reduced_clause_iter_list.end()); 
    }

    if(inspect_clause_list.size() == 0){
        total_num_var_reduced = 0;
    }
}

bool estimateClause(const std::vector<intpair> &input_clause_list, std::unordered_map<int, bool> &variable_val, std::vector<intpair> & unsatisfied_clause_list){
    bool ret_val = true;
    for(const auto &val_pair : input_clause_list){
        bool clause_value = evalClause(variable_val, val_pair, abs(val_pair.first), abs(val_pair.second));

        if(!clause_value){
            unsatisfied_clause_list.push_back(val_pair);
        }

        ret_val = ret_val & clause_value;
    }

    return ret_val;
}

//This random set is to do more work to gaurantee that the clause after the flipping one of the variable will be positive.
//Not work every time.
/*
void randomSetVariable(const std::vector<intpair> &unsatisfied_clause_list, std::unordered_map<int, bool> &variable_val){
    int random_index = rand()%unsatisfied_clause_list.size();
    intpair chosen_pair = unsatisfied_clause_list[random_index];

    int chosen_first_index = abs(chosen_pair.first);
    int chosen_second_index = abs(chosen_pair.second);
    variable_val[chosen_first_index] = !variable_val[chosen_first_index];//flip the first variable;
    if(evalClause(variable_val, chosen_pair, chosen_first_index, chosen_second_index)){
        return;
    }
    
    variable_val[chosen_first_index]  = !variable_val[chosen_first_index];//variable 1 reset;
    variable_val[chosen_second_index] = !variable_val[chosen_second_index];//flip the variable 2;
}
*/

//This is the implementation from the course. Only random choose one of the variable and flip it. No checking whether the clause turn into positive.
void randomSetVariable(const std::vector<intpair> &unsatisfied_clause_list, std::unordered_map<int, bool> &variable_val){
    int random_index = rand()%unsatisfied_clause_list.size();
    int random_chosen_var = rand()%2;
    intpair chosen_pair = unsatisfied_clause_list[random_index];

    int chosen_first_index = abs(chosen_pair.first);
    int chosen_second_index = abs(chosen_pair.second);
    
    if(random_chosen_var == 0){
        variable_val[chosen_first_index] = !variable_val[chosen_first_index];//flip the first variable;
    }else{
        variable_val[chosen_second_index] = !variable_val[chosen_second_index];//flip the seconde variable;
    }
}

bool algoPapadimitriou(const std::vector<intpair> &input_clause_list, std::unordered_map<int, bool> &variable_val, const long long int &total_trial_num, const long long int &repeat_num){
    int trial_num = 0;
    bool got_satisified = false;

    if(total_trial_num <= 0){//If there is no variable input.
        return true;
    }

    while(trial_num < total_trial_num){
        randomInitialAssignment(input_clause_list, variable_val);

        for(int repeat_time = 0;repeat_time < repeat_num;++repeat_time){
            std::vector<intpair> unsatisfied_clause_list;
            bool eval_val = estimateClause(input_clause_list,  variable_val, unsatisfied_clause_list);

            if(eval_val){
                got_satisified = true;
                break;
            }

            randomSetVariable(unsatisfied_clause_list, variable_val);
            //printf("1. Progress = %lf%%, repeat_time = %d\n", (double)((trial_num*repeat_num) + repeat_time)/((double)(total_trial_num*repeat_num))*100, repeat_time);
        }

        if(got_satisified){
            break;
        }
        ++trial_num;
        //printf("2. Progress = %lf\n", (double)trial_num/(double)total_trial_num);
    }

    return got_satisified;
}
