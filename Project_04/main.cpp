// Author: Jordan Edginton
// Class: CS 415
// Project 4
// Description: Takes a text file supplied by the user and forms a knapsack using the
// data within the input files. We then sort our knapsack using 4 different algorithms
// and print out the results.

#include <iostream>
#include <vector>
#include <tuple>
#include <fstream>
#include "knapsack.h"

using namespace std;

void print_subset(vector<int> set){
    // prints the subset array from the results of the knapsack algorithms.
    cout << set[0];
    for(int i = 1; i < set.size(); i++){
        cout << ", " << set[i];
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Incorrect input. Correct format: ./<exectuable.out> <text_file_index>\n";
        return 1;
    }
    string idx = {argv[1]};

    // if the argument is 1 digit, we need to add a "" to the beginning for the index
    if (idx.size() < 2){
        idx = "0" + idx;
    }
    Knapsack knapsack(idx);         // initialize the knapsack, but we aren't sorting it here
    cout << endl;

    int cap = knapsack.get_capacity();
    int items = knapsack.get_tot_items();
    cout << "File containing the capacity, weights, and values are: "
            "p" << idx << "_c.txt, p" << idx << "_w.txt, and p" << idx << "_v.txt" << endl;
    cout << "\nKnapsack capacity = "<< cap << ". Total number of items = " << items << endl;

    tuple<int, int, vector<int>> trad_res = knapsack.trad_dyn_pro();    // <0> = Operations, <1> = Value, <2> = subset
    cout << "\n(1a) Traditional Dynamic Programming Optimal value: " << get<1>(trad_res) << endl;
    cout << "(1a) Traditional Dynamic Programming Optimal subset: {";
    print_subset(get<2>(trad_res));
    cout << "}\n(1a) Traditional Dynamic Programming Total Basic Ops: " << get<0>(trad_res) << endl;


    tuple<int, int, vector<int>> mem_res = knapsack.mem_dyn_pro();      // <0> = Operations, <1> = Value, <2> = subset
    cout << "\n(1b) Traditional Dynamic Programming Optimal value: " << get<1>(mem_res) << endl;
    cout << "(1b) Traditional Dynamic Programming Optimal subset: {";
    print_subset(get<2>(mem_res));
    cout << "}\n(1b) Traditional Dynamic Programming Total Basic Ops: " << get<0>(mem_res) << endl;


    tuple<int, int, vector<int>> greedy_res = knapsack.greedy();        // <0> = Operations, <1> = Value, <2> = subset
    cout << "\n(2a) Traditional Dynamic Programming Optimal value: " << get<1>(greedy_res) << endl;
    cout << "(2a) Traditional Dynamic Programming Optimal subset: {";
    print_subset(get<2>(greedy_res));
    cout << "}\n(2a) Traditional Dynamic Programming Total Basic Ops: " << get<0>(greedy_res) << endl;

    tuple<int, int, vector<int>> heap_res = knapsack.heap_greedy();
    cout << "\n(2b) Traditional Dynamic Programming Optimal value: " << get<1>(heap_res) << endl;
    cout << "(2b) Traditional Dynamic Programming Optimal subset: {";
    print_subset(get<2>(heap_res));
    cout << "}\n(2b) Traditional Dynamic Programming Total Basic Ops: " << get<0>(heap_res) << endl;
    return 0;
}
