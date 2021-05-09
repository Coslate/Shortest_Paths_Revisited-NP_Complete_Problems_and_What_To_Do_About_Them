//solution.cpp
#include <solution.h>

void buildEdgeInfo(const std::vector<std::vector<std::string>> &input_edge_list, std::unordered_map<StrPair, int> &total_edge){
    //Build the mapping of node_name -> address for all nodes.
    for (auto &itRow : input_edge_list){
        for (size_t i=0; i<itRow.size()-1;++i){//only itRow[0] & itRow[1] are nodes. itRow[2] is the edge cost.
            StrPair tmp_edge(itRow[0], itRow[1]);
            if(total_edge.find(tmp_edge) == total_edge.end()){
                total_edge[tmp_edge] = std::stoi(itRow[2]);
            }
        }
    }
}

inline void initArray(int*** &A, const int &num_of_nodes, std::unordered_map<StrPair, int> &total_edge){
    A = new int** [num_of_nodes];
    for (int i=0; i < num_of_nodes; ++i){
        A[i] = new int*[num_of_nodes];
        for (int j=0; j < num_of_nodes; ++j){
            A[i][j] = new int[num_of_nodes+1];
        }
    }

    for(int i=1; i <= num_of_nodes; ++i){
        for(int j=1; j <= num_of_nodes; ++j){
            if(i == j){
                A[i-1][j-1][0] = 0;
            }else{
                StrPair tmp_edge(std::to_string(i), std::to_string(j));
                if(total_edge.find(tmp_edge) != total_edge.end()){
                    A[i-1][j-1][0] = total_edge[tmp_edge];
                }else{
                    A[i-1][j-1][0] = INT_MAX;
                }
            }
        }
    }
}

void apspFloydWarshallAlgo(std::unordered_map<StrPair, int> &total_edge, int *** &A, const int &num_of_nodes, int &min_d, bool &has_neg_cost_cycles){
    initArray(A, num_of_nodes, total_edge);
    min_d = INT_MAX;
    has_neg_cost_cycles = false;

    for(int k=1; k <= num_of_nodes; ++k){
        for(int i=1; i <= num_of_nodes; ++i){
            for(int j=1; j <= num_of_nodes; ++j){
                long long int tmp_add = (long long int)A[i-1][k-1][k-1] + (long long int)A[k-1][j-1][k-1];//A[i][k][k-1] + A[k][j][k-1]
//                std::cout<<"i = "<<i<<", j = "<<j<<", k = "<<k<<", tmp_add = "<<tmp_add<<", "<<A[i-1][k-1][k-1]<<", "<<A[k-1][j-1][k-1]<<std::endl;
                if(tmp_add >= INT_MAX){tmp_add = INT_MAX;}

                A[i-1][j-1][k] = std::min(A[i-1][j-1][k-1], (int)tmp_add);
                if((i != j) && (k == num_of_nodes) && (min_d > A[i-1][j-1][num_of_nodes])){
                    min_d = A[i-1][j-1][num_of_nodes];
                }
            }
        }
    }

    for(int i=1; i <= num_of_nodes; ++i){
        if(A[i-1][i-1][num_of_nodes] < 0){
            has_neg_cost_cycles = true;
        }
    }
}

