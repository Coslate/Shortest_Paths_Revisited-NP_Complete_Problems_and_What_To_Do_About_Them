//solution.cpp
#include <solution.h>

inline double calcDist(const dblpair &pt1, const dblpair &pt2){
    double tmp_diff1 = (pt1.first - pt2.first);
    double tmp_diff2 = (pt1.second - pt2.second);
//    result =  (double)sqrtf((tmp_diff1*tmp_diff1) + (tmp_diff2*tmp_diff2));
    return (double)(tmp_diff1*tmp_diff1) + (double)(tmp_diff2*tmp_diff2);//do the sqrtf() later
}

inline bool cmpDBL(const double &x, const double &y, const double epsilon = std::numeric_limits<double>::epsilon()){
    return (fabs(x-y) < epsilon) ? true : false;
}

void nnHeuristicTSP(const std::vector<dblpair> &input_node_list, const int &total_nodes, std::vector<bool> &input_node_visited, std::vector<int> &ans_node_order, double &ans_dist, std::vector<double> &dist_record){
    int  current_visit_index    = 0;
    int  already_visited        = 1;
    input_node_visited[0]       = true;
    ans_node_order.push_back(1);
    dist_record.push_back(0);

    while(already_visited < total_nodes){
        double min_dist = DBL_MAX;
        int min_dist_index = -1;

        for(int i=0;i<total_nodes;++i){
            if(input_node_visited[i] == true) continue; //only check those non-visited nodes.
            double cal_dist = calcDist(input_node_list[current_visit_index], input_node_list[i]);

            if(cmpDBL(cal_dist, min_dist)){//only get the smallest index when the distance of nodes are equal.
                continue;
            }else if(cal_dist < min_dist){
                min_dist = cal_dist;
                min_dist_index = i;
            }
        }

        if(min_dist_index == -1){
            std::cerr<<"Error: No distance to node '"<<current_visit_index<<"' is smaller than "<<DBL_MAX<<"."<<std::endl;
            std::exit(EXIT_FAILURE);
        }

        input_node_visited[min_dist_index] = true;
        ans_node_order.push_back(min_dist_index+1);
        ans_dist += sqrtf(min_dist);//get the right value of the distance
        dist_record.push_back(ans_dist);//for debug
        current_visit_index = min_dist_index;
        ++already_visited;

        //Calculate the distance from the last visited node to the first node and add it up.
        if(already_visited == total_nodes){
            double cal_dist = calcDist(input_node_list[min_dist_index], input_node_list[0]);
            ans_dist += sqrtf(cal_dist);//get the right value of the distance
            dist_record.push_back(ans_dist);
            ans_node_order.push_back(1);
        }
    }
}
