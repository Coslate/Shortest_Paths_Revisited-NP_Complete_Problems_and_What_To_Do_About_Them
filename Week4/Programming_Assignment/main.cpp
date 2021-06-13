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

int total_num_var = 0;

int total_num_var_reduced = 0;

//All the node (x, y)
std::vector<intpair> input_clause_list;

std::vector<intpair> reduced_clause_list;

std::unordered_map<int, bool> variable_val;

long long int total_trial_num = 0;

long long int repeat_num = 0;

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

    srand (time(NULL));
    //std::cout<<"RAND_MAX = "<<RAND_MAX<<std::endl;
    
    std::cout<<"> clauseReduction..."<<std::endl;
    clauseReduction(input_clause_list, reduced_clause_list, total_num_var_reduced);
    std::cout<<"  reduced_clause_list.size() = "<<reduced_clause_list.size()<<std::endl;

    std::cout<<"> algoPapadimitriou..."<<std::endl;
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

    /*
    std::cout<<"The variable setting is : "<<std::endl;
    for(const auto &var : variable_val){
        std::cout<<"var = "<<var.first<<", value = "<<var.second<<std::endl;
    }
    */

    return EXIT_SUCCESS;
}
