//main.cpp
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <solution.h>

int num_of_nodes1 = 0;
int num_of_edges1 = 0;
int num_of_nodes2 = 0;
int num_of_edges2 = 0;
int num_of_nodes3 = 0;
int num_of_edges3 = 0;

//All of the edges and the correspondent weight from input text file.
std::vector<std::vector<std::string>> input_edge_list1;
std::vector<std::vector<std::string>> input_edge_list2;
std::vector<std::vector<std::string>> input_edge_list3;

std::unordered_map<StrPair, int> total_edge1;
std::unordered_map<StrPair, int> total_edge2;
std::unordered_map<StrPair, int> total_edge3;

//The dynamic programming answer of the Floyed Warshall algo.
int *** A1;
int *** A2;
int *** A3;

int min_d1 = INT_MAX;
int min_d2 = INT_MAX;
int min_d3 = INT_MAX;

bool has_neg_cost_cycles1 = false;
bool has_neg_cost_cycles2 = false;
bool has_neg_cost_cycles3 = false;

inline void releaseArray(int*** &A, const int &num_of_nodes){
    for (int i=0; i < num_of_nodes; i++){
        for (int j=0; j < num_of_nodes; j++){
            delete[] A[i][j];
        }
        delete[] A[i];
    }
 
    delete[] A;
}

void readFile(std::string filename, std::vector<std::vector<std::string>> &input_edge_list, int &num_of_edges, int &num_of_nodes){
    std::string line;
    std::ifstream myfile (filename);
    if (myfile.is_open()){
        int  count_line = 0;
        while ( std::getline (myfile,line) ){
            std::istringstream iss(line); 

            if(count_line == 0){
                std::string s; 
                iss >> s;
                num_of_nodes = std::stoi(s);
                iss >> s;
                num_of_edges = std::stoi(s);
                ++count_line;
                continue;
            }
                
            std::vector<std::string> tmp_vec;
            for(std::string s; iss >> s;){
                tmp_vec.push_back(s);
            }
            input_edge_list.push_back(tmp_vec);
        }
        myfile.close();
    }else std::cout << "Unable to open file"; 
}

int main(int argc, char*argv[]){
    if(argc < 4){
        std::cerr<<"Error: There should be at least one input argument like ./main arg1 arg2 arg3."<<std::endl;
        return EXIT_FAILURE;
    }
    
    readFile(argv[1], input_edge_list1, num_of_edges1, num_of_nodes1);
    readFile(argv[2], input_edge_list2, num_of_edges2, num_of_nodes2);
    readFile(argv[3], input_edge_list3, num_of_edges3, num_of_nodes3);

    std::cout<<"> buildEdgeInfo..."<<std::endl;
    buildEdgeInfo(input_edge_list1, total_edge1);
    buildEdgeInfo(input_edge_list2, total_edge2);
    buildEdgeInfo(input_edge_list3, total_edge3);

    std::cout<<"> apspFloydWarshallAlgo..."<<std::endl;
    apspFloydWarshallAlgo(total_edge1, A1, num_of_nodes1, min_d1, has_neg_cost_cycles1);
    apspFloydWarshallAlgo(total_edge2, A2, num_of_nodes2, min_d2, has_neg_cost_cycles2);
    apspFloydWarshallAlgo(total_edge3, A3, num_of_nodes3, min_d3, has_neg_cost_cycles3);

    std::cout<<"> Print the Result..."<<std::endl;
    std::cout<<">>G1(V, E) : "<<std::endl;
    if(has_neg_cost_cycles1 == true){
        std::cout<<">> has_neg_cost_cycles1 = true"<<std::endl;
    }else{
        std::cout<<">> min_d1 = "<<min_d1<<std::endl;
    }
    std::cout<<">>G2(V, E) : "<<std::endl;
    if(has_neg_cost_cycles2 == true){
        std::cout<<">> has_neg_cost_cycles2 = true"<<std::endl;
    }else{
        std::cout<<">> min_d2 = "<<min_d2<<std::endl;
    }
    std::cout<<">>G3(V, E) : "<<std::endl;
    if(has_neg_cost_cycles3 == true){
        std::cout<<">> has_neg_cost_cycles3 = true"<<std::endl;
    }else{
        std::cout<<">> min_d3 = "<<min_d3<<std::endl;
    }

/*
    for(int k=0;k<=num_of_nodes1;++k){
        std::cout<<"---------k = "<<k<<"----------"<<std::endl;
        for(int i=0;i<num_of_nodes1;++i){
            for(int j=0;j<num_of_nodes1;++j){
                std::cout<<A1[i][j][k]<<" ";
            }
            std::cout<<std::endl;
        }
    }
*/

    std::cout<<"> releaseArray..."<<std::endl;
    releaseArray(A1, num_of_nodes1);
    releaseArray(A2, num_of_nodes2);
    releaseArray(A3, num_of_nodes3);

    return EXIT_SUCCESS;
}
