#ifndef _SOLUTION_H_
#define _SOLUTION_H_

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <stack> 
#include <cfloat>
#include <Linked_List.h>

using StrPair = std::pair<std::string, std::string>;

namespace std {

  // A minor detail: std::hash is a struct, not a class.
  // In C++, a struct is very similar to a class, but it has public
  // members by default.

  // The "template <>" syntax indicates that we are specializing an existing
  // template for std::hash.

  template <>
  struct hash<StrPair> {

    // By overriding the () "operator", we can make an instance of a class
    // respond to similar syntax as if it were merely a function name.
    // The std::hash type is intended to work this way, as a "function object".
    // See also: https://en.cppreference.com/w/cpp/utility/functional

    // The () operator definition is where we will essentially define
    // our custom hashing function, and it returns the actual hash
    // as a std::size_t value (which is an integral type).
    std::size_t operator() (const StrPair& p) const {

        // We know that std::string has a well-defined hasher already,
        // so we'll turn our pair of ints into a unique string representation,
        // and then just hash that. We'll turn each integer into a string
        // and concatenate them with "##" in the middle, which should make
        // a unique string for any given pair of ints.
        std::string uniqueStrPairString = p.first + "##" + p.second;

        // Get the default hashing function object for a std::string.
        std::hash<std::string> stringHasher;
        // Use the string hasher on our unique string.
        return stringHasher(uniqueStrPairString);
    }
  };
}

void buildEdgeInfo(const std::vector<std::vector<std::string>> &input_edge_list, std::unordered_map<StrPair, int> &total_edge);

void apspFloydWarshallAlgo(std::unordered_map<StrPair, int> &total_edge, int *** &A, const int &num_of_nodes, int &min_d, bool &has_neg_cost_cycles);

#endif
