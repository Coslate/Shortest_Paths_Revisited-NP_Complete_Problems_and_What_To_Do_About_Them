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

int total_nodes = 0;

//All the node (x, y)
std::vector<dblpair> input_node_list;

//Whether the node is visited.
std::vector<bool> input_node_visited;

//The answer of the visited order.
std::vector<int> ans_node_order;

//The answer of the tour distance.
double ans_dist = 0;

//The answer of the visited order.
std::vector<double> dist_record;

void readFile(std::string filename, std::vector<dblpair> &input_node_list, int &total_nodes){
    std::string line;
    std::ifstream myfile (filename);
    if (myfile.is_open()){
        int  count_line = 0;
        while ( std::getline (myfile,line) ){
            std::istringstream iss(line); 
            dblpair tmp_pair;
            std::string s; 

            if(count_line == 0){
                std::string s; 
                iss >> s;
                total_nodes = std::stoi(s);
                ++count_line;
                continue;
            }
                
            iss >> s;
            iss >> s;
            tmp_pair.first = std::stod(s.c_str());
            iss >> s;
            tmp_pair.second = std::stod(s.c_str());
            input_node_list.push_back(tmp_pair);
            input_node_visited.push_back(false);
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
    readFile(argv[1], input_node_list, total_nodes);

/*
    std::cout<<total_nodes<<std::endl;
    int cnter = 1;
    for(const auto &pair : input_node_list){
        std::cout<<std::fixed<<std::setprecision(4)<<cnter<<" "<<pair.first<<" "<<pair.second<<std::endl;
        ++cnter;
    }
*/
    std::cout<<"> nnHeuristicTSP..."<<std::endl;
    nnHeuristicTSP(input_node_list, total_nodes, input_node_visited, ans_node_order, ans_dist, dist_record);

    std::cout<<"> Print the result..."<<std::endl;
    std::cout<<std::fixed<<std::setprecision(6);
    std::cout<<"ans_tsp = "<<std::endl;
    for(int i=0;i<(int)ans_node_order.size();++i){
        if(i == (int)ans_node_order.size()-1){
            std::cout<<ans_node_order[i]<<"("<<dist_record[i]<<")"<<std::endl;
        }else{
            std::cout<<ans_node_order[i]<<"("<<dist_record[i]<<") -> ";
        }
    }
    std::cout<<"ans_dist = "<<ans_dist<<std::endl;
    return EXIT_SUCCESS;
}
