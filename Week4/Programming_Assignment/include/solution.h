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
#include <unordered_map>
#include <unordered_set>
#include <time.h>
#include <AdjList.h>
#include <iostream>
#include <algorithm>

using intpair = std::pair<int, int>;

void buildAdjList(std::unordered_map<std::string, LinkedListNode*> &map_node_st2lln, const std::vector<std::vector<std::string>> &input_edge_list, AdjList &adj_list, AdjList &adj_list_rev);

void checkSatisfiability(const std::vector<intpair> &input_clause_list, std::unordered_map<LinkedListNode*, LinkedListNode*> map_leader_lln2lln, std::unordered_map<std::string, LinkedListNode*> map_node_st2lln, bool &satisfied);

void resetAllNodeToUnexplored(std::unordered_map<std::string, LinkedListNode*> &map_node_st2lln);

void collectResult(std::unordered_map<LinkedListNode*, LinkedListNode*> &map_leader_lln2lln, std::unordered_map<LinkedListNode*, LinkedList*> &map_leader2scc);

void printResult(std::unordered_map<LinkedListNode*, LinkedList*> &map_leader2scc, std::vector<int> &scc_size_result);

void DFSIterative2(std::unordered_map<std::string, LinkedListNode*> &map_node_st2lln, AdjList &adj_list, LinkedListNode *invoke_node, LinkedListNode *first_invoke_node, std::unordered_map<LinkedListNode*, LinkedListNode*> &map_leader_lln2lln, int &finish_time, std::unordered_map<LinkedListNode*, int> &map_lln2ft, std::unordered_map<int, LinkedList*> &map_ft2ll, const bool cal_finish_time);

void DFSLoop2(std::unordered_map<std::string, LinkedListNode*> &map_node_st2lln, AdjList &adj_list, std::unordered_map<LinkedListNode*, LinkedListNode*> &map_leader_lln2lln, std::unordered_map<LinkedListNode*, int> &map_lln2ft, std::unordered_map<int, LinkedList*> &map_ft2ll, const bool cal_finish_time, const bool use_decreasing_finish_time, int &finish_time);

bool estimateClause(const std::vector<intpair> &input_clause_list, std::unordered_map<int, bool> &variable_val, std::vector<intpair> & unsatisfied_clause_list);

void randomSetVariable(const std::vector<intpair> &unsatisfied_clause_list, std::unordered_map<int, bool> &variable_val);

void clauseReduction(const std::vector<intpair> &input_clause_list, std::vector<intpair> &reduced_clause_list, int &total_num_var_reduced);

bool algoPapadimitriou(const std::vector<intpair> &input_clause_list, std::unordered_map<int, bool> &variable_val, const long long int &total_trial_num, const long long int &repeat_num);

void transClause2Graph(const std::vector<intpair> &input_clause_list, std::vector<std::vector<std::string>> &output_edge_list);


#endif
