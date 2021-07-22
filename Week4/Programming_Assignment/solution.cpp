//solution.cpp
#include <solution.h>

void buildAdjList(std::unordered_map<std::string, LinkedListNode*> &map_node_st2lln, const std::vector<std::vector<std::string>> &input_edge_list, AdjList &adj_list, AdjList &adj_list_rev){
    //Build the mapping of node_name -> address for all nodes.
    for (auto &itRow : input_edge_list){
        for (size_t i=0; i<itRow.size();++i){
            if(map_node_st2lln.find(itRow[i]) == map_node_st2lln.end()){//not found
                LinkedListNode* new_node = new LinkedListNode(0, itRow[i]);
                map_node_st2lln[itRow[i]] = new_node;
            }
        }

        //Build the adjacent list for all nodes.
        adj_list.SetAdjList(map_node_st2lln[itRow[0]], map_node_st2lln[itRow[1]], 0);
        adj_list_rev.SetAdjList(map_node_st2lln[itRow[1]], map_node_st2lln[itRow[0]], 0);
    }
}

void resetAllNodeToUnexplored(std::unordered_map<std::string, LinkedListNode*> &map_node_st2lln){
    for (auto element : map_node_st2lln) {
        LinkedListNode* the_node = element.second;
        the_node -> SetExplored(false);
        the_node -> SetColor(0);
    }
}

void collectResult(std::unordered_map<LinkedListNode*, LinkedListNode*> &map_leader_lln2lln, std::unordered_map<LinkedListNode*, LinkedList*> &map_leader2scc){
    for(auto element : map_leader_lln2lln){
        LinkedListNode* invoke_node = element.first;
        LinkedListNode* leader_node = element.second;

        if(map_leader2scc.find(leader_node) == map_leader2scc.end()){//not found
            LinkedList* the_scc_linked_list = new LinkedList();
            the_scc_linked_list->InsertTail(0, invoke_node->GetName());
            map_leader2scc[leader_node] = the_scc_linked_list;
        }else{
            LinkedList* the_scc_linked_list = map_leader2scc[leader_node];
            the_scc_linked_list->InsertTail(0, invoke_node->GetName());
        }
    }
}

void printResult(std::unordered_map<LinkedListNode*, LinkedList*> &map_leader2scc, std::vector<int> &scc_size_result){
    for(auto element : map_leader2scc){
        LinkedListNode* leader_node     = element.first;
        LinkedList* the_linked_list     = element.second;

        int count = 0;
        int scc_size = the_linked_list->GetListSize();
        LinkedListNode* current_node = the_linked_list->GetFristNode();
        while(current_node != NULL){
            if((count == 0) && (count == (scc_size-1))){
                std::cout<<"scc["<<leader_node->GetName()<<"] = ["<<current_node->GetName()<<"]"<<std::endl;
            }else if(count == 0){
                std::cout<<"scc["<<leader_node->GetName()<<"] = ["<<current_node->GetName()<<", ";
            }else if(count == scc_size-1){
                std::cout<<current_node->GetName()<<"]"<<std::endl;
            }else{
                std::cout<<current_node->GetName()<<", ";
            }
            ++count;
            current_node = current_node->GetNext();
        } 
        std::cout<<"size = "<<scc_size<<std::endl;
        scc_size_result.push_back(scc_size);
        std::cout<<"----------------"<<std::endl;
    }

    std::sort(scc_size_result.begin(), scc_size_result.end(), std::greater<>());
    std::cout<<"All size of the SCC in descending order(max 5) : ";
    if(scc_size_result.size() < 5){
        for(size_t i=0;i<scc_size_result.size();++i){
            if(i==scc_size_result.size()-1){
                std::cout<<scc_size_result[i]<<std::endl;
            }else{
                std::cout<<scc_size_result[i]<<",";
            }
        }
    }else{
        for(size_t i=0;i<5;++i){
            if(i==5-1){
                std::cout<<scc_size_result[i]<<std::endl;
            }else{
                std::cout<<scc_size_result[i]<<",";
            }
        }
    }
    std::cout<<std::endl;
}

void DFSIterative2(std::unordered_map<std::string, LinkedListNode*> &map_node_st2lln, AdjList &adj_list, LinkedListNode *invoke_node, LinkedListNode *first_invoke_node, std::unordered_map<LinkedListNode*, LinkedListNode*> &map_leader_lln2lln, int &finish_time, std::unordered_map<LinkedListNode*, int> &map_lln2ft, std::unordered_map<int, LinkedList*> &map_ft2ll, const bool cal_finish_time){

    //Color-0: WHITE
    //Color-1: GRAY
    //Color-2: BLACK
    
    std::stack<LinkedListNode*> mystack;
    mystack.push(invoke_node);

    while(!mystack.empty()){
        LinkedListNode* proc_node = mystack.top();
        mystack.pop();
        bool all_adj_discovered;

        if(proc_node -> GetColor() != 2){
            mystack.push(proc_node);

            if(proc_node ->GetColor() == 0){
                proc_node->SetColor(1);
            }

            all_adj_discovered = true;
//            std::cout<<"proc_node = "<<proc_node->GetName()<<"("<<proc_node<<"), color = "<<proc_node->GetColor()<<std::endl;
            LinkedList* the_linked_list = adj_list.ReadAdjList(proc_node);

            if(the_linked_list == NULL){
//                std::cout<<"The proc_node: "<<proc_node->GetName()<<"("<<proc_node<<")"<<", explored = "<<proc_node->GetExplored()<<", has no adjacent List."<<std::endl;
            }

            //Traversing all the adjacent nodes.
            if(the_linked_list != NULL){
                LinkedListNode* current_node = the_linked_list->GetFristNode();
                while(current_node != NULL){
                    if(map_node_st2lln[current_node->GetName()]->GetColor() == 0){
                        mystack.push(map_node_st2lln[current_node->GetName()]);
                        all_adj_discovered = false;
                    }
                    current_node = current_node->GetNext();
                }
            }
            
            if(all_adj_discovered){
                proc_node->SetColor(2);
                if(cal_finish_time){
                    ++finish_time;
                    map_lln2ft[proc_node] = finish_time;

                    if(map_ft2ll.find(finish_time) == map_ft2ll.end()){//not found
                        LinkedList* the_finish_time_node_linked_list = new LinkedList();
                        the_finish_time_node_linked_list->InsertTail(0, proc_node->GetName());
                        map_ft2ll[finish_time] = the_finish_time_node_linked_list;
                    }else{
                        LinkedList* the_finish_time_node_linked_list = map_ft2ll[finish_time];
                        the_finish_time_node_linked_list->InsertTail(0, proc_node->GetName());
                    }
                }
                mystack.pop();
                map_leader_lln2lln[proc_node] = first_invoke_node;
//                std::cout<<"finish_time = "<<finish_time<<", "<<"pop out proc_node: "<<proc_node->GetName()<<"("<<proc_node<<"), color = "<<proc_node->GetColor()<<std::endl;
            }
        }
    }
}

void DFSLoop2(std::unordered_map<std::string, LinkedListNode*> &map_node_st2lln, AdjList &adj_list, std::unordered_map<LinkedListNode*, LinkedListNode*> &map_leader_lln2lln, std::unordered_map<LinkedListNode*, int> &map_lln2ft, std::unordered_map<int, LinkedList*> &map_ft2ll, const bool cal_finish_time, const bool use_decreasing_finish_time, int &finish_time){
    if(use_decreasing_finish_time == false){
        for (auto element : map_node_st2lln) {
            LinkedListNode* the_node = element.second;
//            std::cout<<"the_node = "<<the_node->GetName()<<"("<<the_node<<")"<<", color = "<<the_node->GetColor()<<std::endl;
            if(the_node -> GetColor() == 0){
                DFSIterative2(map_node_st2lln, adj_list, the_node, the_node, map_leader_lln2lln, finish_time, map_lln2ft, map_ft2ll, cal_finish_time);
            }
        }
    }else{
        for(int i=finish_time;i>0;--i){
            if(map_ft2ll.find(i) != map_ft2ll.end()){//found
                LinkedList* the_linked_list_time = map_ft2ll[i];
                LinkedListNode* current_node     = the_linked_list_time->GetFristNode();
                while(current_node != NULL){
                    LinkedListNode* the_node = map_node_st2lln[current_node->GetName()];
//                    std::cout<<"the_node = "<<the_node->GetName()<<"("<<the_node<<")"<<std::endl;
                    if(the_node->GetColor() == 0){
                        DFSIterative2(map_node_st2lln, adj_list, the_node, the_node, map_leader_lln2lln, finish_time, map_lln2ft, map_ft2ll, cal_finish_time);
                    }
                    current_node = current_node->GetNext();
                }
            }
        }
    }
}

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

void transClause2Graph(const std::vector<intpair> &input_clause_list, std::vector<std::vector<std::string>> &output_edge_list){
    for(const auto &elem : input_clause_list){
        std::vector<std::string> tmp_vec1;
        std::vector<std::string> tmp_vec2;
        tmp_vec1.push_back(std::to_string(-1*elem.first));
        tmp_vec1.push_back(std::to_string(elem.second));
        tmp_vec2.push_back(std::to_string(-1*elem.second));
        tmp_vec2.push_back(std::to_string(elem.first));

        output_edge_list.push_back(tmp_vec1);
        output_edge_list.push_back(tmp_vec2);
    }
}

void checkSatisfiability(const std::vector<intpair> &input_clause_list, std::unordered_map<LinkedListNode*, LinkedListNode*> map_leader_lln2lln, std::unordered_map<std::string, LinkedListNode*> map_node_st2lln, bool &satisfied){
    satisfied = true;
    for(const auto &elem : input_clause_list){
        std::string variable_1  = std::to_string(elem.first);
        std::string variable_n1 = std::to_string(-1*elem.first);
        std::string variable_2  = std::to_string(elem.second);
        std::string variable_n2 = std::to_string(-1*elem.second);

        if((map_leader_lln2lln[map_node_st2lln[variable_1]] == map_leader_lln2lln[map_node_st2lln[variable_n1]])
            || (map_leader_lln2lln[map_node_st2lln[variable_2]] == map_leader_lln2lln[map_node_st2lln[variable_n2]])){
            satisfied = false;
            return;
        }
    }
}
