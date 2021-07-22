//main.cpp
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <solution.h>

bool directed       = true;
bool show_debug_msg = false;

int total_num_var = 0;

int total_num_var_reduced = 0;

//All the node (x, y)
std::vector<intpair> input_clause_list;

std::vector<intpair> reduced_clause_list;

std::unordered_map<int, bool> variable_val;

long long int total_trial_num = 0;

long long int repeat_num = 0;

int finish_time = 0;

bool satisfied = true;

std::vector<std::vector<std::string>> output_edge_list;

//Generate the correspondence between Node & LinkedListNode.
std::unordered_map<std::string, LinkedListNode*> map_node_st2lln;

//For storing the leader of a node in a SCC.
std::unordered_map<LinkedListNode*, LinkedListNode*> map_leader_lln2lln;

//For storing the finish time of each node.
std::unordered_map<LinkedListNode*, int> map_lln2ft;

//For storing every node in a given finish time.
std::unordered_map<int, LinkedList*> map_ft2ll;

//Each element is a leader node -> list within the same leader of SCC.
std::unordered_map<LinkedListNode*, LinkedList*> map_leader2scc;

std::vector<int> scc_size_result;

//Declare a new adjacent list to represent Graph(V, E).
AdjList adj_list(directed, show_debug_msg);
AdjList adj_list_rev(directed, show_debug_msg);

void readFile(std::string filename, std::vector<intpair> &input_clause_list, int &total_num_var){
    std::string line;
    std::ifstream myfile (filename);
    if (myfile.is_open()){
        int  count_line = 0;
        while ( std::getline (myfile,line) ){
            std::istringstream iss(line); 
            intpair tmp_pair;
            std::string s; 

            if(count_line == 0){
                std::string s; 
                iss >> s;
                total_num_var = std::stoi(s);
                ++count_line;
                continue;
            }
                
            iss >> s;
            tmp_pair.first = std::stoi(s.c_str());
            iss >> s;
            tmp_pair.second = std::stoi(s.c_str());
            input_clause_list.push_back(tmp_pair);
        }
        myfile.close();
    }else std::cout << "Unable to open file"; 
}

int main(int argc, char*argv[]){
    if(argc < 2){
        std::cerr<<"Error: There should be at least one input argument like ./main arg1."<<std::endl;
        std::exit(EXIT_FAILURE);
    }
    
    std::cout<<"> readFile..."<<std::endl;
    readFile(argv[1], input_clause_list, total_num_var);

    /*
    std::cout<<total_num_var<<std::endl;
    for(const auto &pair : input_clause_list){
        std::cout<<pair.first<<" "<<pair.second<<std::endl;
    }
    */

    int method = 0;
    if(strcmp(argv[2], "-method") == 0){
        method = atoi(argv[3]);
    }
    
    std::cout<<"> clauseReduction..."<<std::endl;
    clauseReduction(input_clause_list, reduced_clause_list, total_num_var_reduced);
    std::cout<<"  input_clause_list.size() = "<<input_clause_list.size()<<std::endl;
    std::cout<<"  input_clause_list = "<<std::endl;
    for(const auto &elem : input_clause_list){
        std::cout<<elem.first<<" "<<elem.second<<std::endl;
    }
    std::cout<<"  reduced_clause_list.size() = "<<reduced_clause_list.size()<<std::endl;
    std::cout<<"  reduced_clause_list = "<<std::endl;
    for(const auto &elem : reduced_clause_list){
        std::cout<<elem.first<<" "<<elem.second<<std::endl;
    }

    if(method == 0){
        //method - Papadimitriou
        std::cout<<"> algoPapadimitriou..."<<std::endl;
        srand (time(NULL));
        total_trial_num = (int)log2(pow(total_num_var_reduced, 2));
        repeat_num      = 2*pow(total_num_var_reduced, 2);

        printf("  total_num_var = %d\n", total_num_var);
        printf("  total_num_var_reduced = %d\n", total_num_var_reduced);
        printf("  total_trial_num = %lld\n", total_trial_num);
        printf("  repeat_num = %lld\n", repeat_num);
        printf("  RAND_MAX = %d\n", RAND_MAX);
        bool satisfied_result = algoPapadimitriou(reduced_clause_list, variable_val, total_trial_num, repeat_num);

        std::cout<<"> show the result..."<<std::endl;
        if(satisfied_result){
            std::cout<<"  ans = Satisfiable,   1"<<std::endl;
        }else{
            std::cout<<"  ans = Unsatisfiable, 0"<<std::endl;
        }
    }else{
        //method - SCC
        std::cout<<"> transClause2Graph..."<<std::endl;
        transClause2Graph(reduced_clause_list, output_edge_list);

        /*
        std::cout<<"  output_edge_list = "<<std::endl;
        for(const auto &elem : output_edge_list){
            std::cout<<elem[0]<<" "<<elem[1]<<std::endl;
        }
        */
        std::cout<<"> buildAdjList..."<<std::endl;
        buildAdjList(map_node_st2lln, output_edge_list, adj_list, adj_list_rev);

        std::cout<<"> Kosaraju's Algo..."<<std::endl;
        std::cout<<"-----------1st-------------"<<std::endl;
        //1st DFSLoop - To calculate the finish time.
        std::cout<<"Use 'DFSLoop2' subroutine..."<<std::endl;
        DFSLoop2(map_node_st2lln, adj_list_rev, map_leader_lln2lln, map_lln2ft, map_ft2ll, true, false, finish_time);

        std::cout<<"-----------2nd-------------"<<std::endl;
        //2nd DFSLoop - To calculate the SCC
        resetAllNodeToUnexplored(map_node_st2lln);
        std::cout<<"Use 'DFSLoop2' subroutine..."<<std::endl;
        DFSLoop2(map_node_st2lln, adj_list, map_leader_lln2lln, map_lln2ft, map_ft2ll, false, true, finish_time);

        //debug
        std::cout<<"> collectResult..."<<std::endl;
        collectResult(map_leader_lln2lln, map_leader2scc);

        std::cout<<"> printResult..."<<std::endl;
        printResult(map_leader2scc, scc_size_result);
        
        std::cout<<"> checkSatisfiability..."<<std::endl;
        checkSatisfiability(reduced_clause_list, map_leader_lln2lln, map_node_st2lln, satisfied);
        std::cout<<"satisfied = "<<satisfied<<std::endl;

        //Release heap memory
        for(auto &elem : map_node_st2lln){
            LinkedListNode *the_node = elem.second;
            delete the_node;
        }

        for(auto &elem : map_ft2ll){
            LinkedList *the_ll = elem.second;
            delete the_ll;
        }

        for(auto &elem : map_leader2scc){
            LinkedList *the_ll = elem.second;
            delete the_ll;
        }
    }

    return EXIT_SUCCESS;
}
