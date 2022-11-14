// Author: Jordan Edginton
// Class: CS 415
// Project 4
// Description: this is our knapsack class that we use for our 4 algorithms.
// it only stores the values from the input file and doesn't store any of the
// results of the knapsack algorithms.

#ifndef PROJECT_04_KNAPSACK_H
#define PROJECT_04_KNAPSACK_H
#include <iostream>
#include <tuple>
#include <vector>
#include <fstream>
#include <deque>

using namespace std;

class Knapsack {
public:
    Knapsack();
    Knapsack(string  &idx);
    void read_file(string  &idx);
    int get_capacity();
    int get_tot_items();
    tuple<int, int, vector<int>> trad_dyn_pro();                    // task 1a
    tuple<int, int, vector<int>> mem_dyn_pro();                     // task 1b
    tuple<int, int, vector<int>> greedy();                          // task 2a
    tuple<int, int, vector<int>> heap_greedy();                     // task 2b
    void print_sack();                                              // used for debugging

private:
    int basic_ops;                     // keeps track of basic operations performed
    int capacity;
    int n;                             // n is the size of the values vector
    vector<int> values;
    vector<int> weights;

    vector<int> optimal_items(vector<vector<int>> table);                 // task 1a
    int fill_table_rec(vector<vector<int>> &table, int row, int col);     // task 1b
    vector<tuple<float, int>> get_ratios();                               // task 2a, 2b
    void merge_ratio(vector<tuple<float, int>> &ratio_vec, int l, int r); // task 2a, merge sort
    void merge(vector<tuple<float, int>> &vec, int l, int m,  int r);     // task 2a, merge sort
    void arr_sort(vector<int> &vec);                                      // task 2a
    void bottomUp_heap(deque<tuple<float, int>> &heap);                   // task 2b
    int deleteMax(deque<tuple<float, int>> &heap);                        // task 2b
    int get_optimal_value(vector<int> opt_vec);                           // all tasks
    void print_table( vector<vector<int>> table);                         // used for debugging task 1

};


#endif //PROJECT_04_KNAPSACK_H
