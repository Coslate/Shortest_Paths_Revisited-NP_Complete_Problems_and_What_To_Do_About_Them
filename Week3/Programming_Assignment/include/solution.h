#ifndef _SOLUTION_H_
#define _SOLUTION_H_

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include <stack> 
#include <cfloat>
#include <cmath>

using dblpair = std::pair<double, double>;

void nnHeuristicTSP(const std::vector<dblpair> &input_node_list, const int &total_nodes, std::vector<bool> &input_node_visited, std::vector<int> &ans_node_order, double &ans_dist, std::vector<double> &dist_record);
#endif
