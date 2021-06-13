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

using intpair = std::pair<int, int>;

bool estimateClause(const std::vector<intpair> &input_clause_list, std::unordered_map<int, bool> &variable_val, std::vector<intpair> & unsatisfied_clause_list);

void randomSetVariable(const std::vector<intpair> &unsatisfied_clause_list, std::unordered_map<int, bool> &variable_val);

void clauseReduction(const std::vector<intpair> &input_clause_list, std::vector<intpair> &reduced_clause_list, int &total_num_var_reduced);

bool algoPapadimitriou(const std::vector<intpair> &input_clause_list, std::unordered_map<int, bool> &variable_val, const long long int &total_trial_num, const long long int &repeat_num);

#endif
