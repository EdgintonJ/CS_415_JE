// Author: Jordan Edginton
// Class: CS 415
// Project 4

#include "knapsack.h"
#include <iostream>
#include <tuple>
#include <vector>
#include <fstream>
#include <cmath>
#include <deque>

using namespace std;

Knapsack::Knapsack(){
    capacity = 0;
}

Knapsack::Knapsack(string &idx){
    read_file(idx);
}

void Knapsack::read_file(string &idx){
    // Reads the input file specified by the user and puts the value into their respective variables/vectors.
    string file_c = "KnapsackTestData/p" + idx + "_c.txt";
    string file_v = "KnapsackTestData/p" + idx + "_v.txt";
    string file_w = "KnapsackTestData/p" + idx + "_w.txt";

    ifstream i_file_c(file_c);
    if (! i_file_c.is_open()){
        cout << "Unable to open input file: " << file_c;
        exit(1);
    }
    i_file_c >> capacity;
    i_file_c.close();
    int inp;
    ifstream i_file_v(file_v);
    while ((i_file_v >> inp)){
       values.push_back(inp);
    }
    i_file_v.close();

    ifstream i_file_w(file_w); // capacity, values, weights
    while ((i_file_w >> inp)){
        weights.push_back(inp);
    }
    i_file_w.close();
    n = values.size();
}


// task 1
tuple<int, int, vector<int>> Knapsack::trad_dyn_pro(){
    // task 1a
    // Here we completely create a table and go through each item one by one to determine its
    // maximum value. After the table is filled we traverse it starting at the end to find the optimal items.
    basic_ops = 0;
    int curr_cap;
    vector<vector<int>> table(n + 1);
    for (int p = 0; p < n + 1; p++) {
        table[p].resize(capacity + 1);
    }

    // fill first row & col with 0's
    for (int k = 0; k < n + 1 ; k++){
        basic_ops++;
        table[k][0] = 0;
    }
    for (int q = 0; q < capacity + 1; q++){
        basic_ops++;
        table[0][q] = 0;
    }

    // fill rest of table
    for (int j = 1; j <= capacity ; j++) {
        basic_ops++;
        curr_cap = 0;
        for (int i = 0; i < n ; i++) {
            basic_ops++;
            if (weights[i] <= j){
                basic_ops++;
                table[i+1][j] = max(table[i][j-weights[i]] + values[i], table[i][j]);
                curr_cap += weights[i];
            } else{
                basic_ops++;
                table[i+1][j] = table[i][j];
            }
        }
    }

    // create return vector
    tuple<int, int, vector<int>> ret;
    vector<int> temp = optimal_items(table);
    for (int r = temp.size() - 1; r >= 0; r--){
        get<2>(ret).push_back(temp[r]);
    }
    get<1>(ret) = get_optimal_value(get<2>(ret));
    get<0>(ret) = basic_ops;
    return ret;
}

tuple<int, int, vector<int>> Knapsack::mem_dyn_pro(){
    // task 1b
    // Here we set up the table by initializing all items to -1, set the items in row[0] and col[0] to 0, then call
    // the fill_table_rec function to fill what is needed in the rest of the table.
    basic_ops = 0;
    vector<vector<int>> table(n + 1);
    for (int p = 0; p < n + 1; p++) {
        table[p].resize(capacity + 1);
    }

    // set every cell to -1
    for (int k = 1; k < n + 1 ; k++){
        for (int q = 1; q < capacity + 1; q++){
            basic_ops++;
            table[k][q] = -1;
        }
    }

    // fill first row & col with 0's
    for (int k = 0; k < n + 1 ; k++){
        basic_ops++;
        table[k][0] = 0;
    }
    for (int q = 0; q < capacity + 1; q++){
        basic_ops++;
        table[0][q] = 0;
    }

    // fill table
    fill_table_rec(table, n, capacity);

    // create return vector
    tuple<int, int, vector<int>> ret;
    vector<int> temp = optimal_items(table);
    for (int r = temp.size() - 1; r >= 0; r--){
        get<2>(ret).push_back(temp[r]);
    }
    get<1>(ret) = get_optimal_value(get<2>(ret));
    get<0>(ret) = basic_ops;
    return ret;
}

int Knapsack::fill_table_rec(vector<vector<int>> &table, int row, int col){
    // task 1b
    // Here we recursively traverse through the table and first check if the item has already been filled.
    // If so, we return the item. If not, we call the cells in the row above that would be where we either
    // we use the item or not use the item.
    basic_ops++;
    if (table[row][col] < 0){
        basic_ops++;
        if (col < weights[row-1]) {
            table[row][col] = fill_table_rec(table, row - 1, col);
        }
        else{
            table[row][col] = max(fill_table_rec(table, row - 1, col),
                                  fill_table_rec(table, row - 1, col - weights[row-1]) + values[row-1]);
        }
        basic_ops++;
    }
    return table[row][col];
}

vector<int> Knapsack::optimal_items(vector<vector<int>> table){
    // task 1a & 1b
    // This traverses through the tables in tasks 1a and 1b and returns a
    // vector of the path it took to get the optimal items.
    vector<int> ret_vec;
    int cap_left = capacity;
    for (int i = n; i > 0 ; i--){
        basic_ops++;
        if (table[i-1][cap_left] < table[i][cap_left]){
            basic_ops++;
            ret_vec.push_back(i);
            cap_left -= weights[i - 1];
        }
    }
    return ret_vec;
}


// task 2
tuple<int, int, vector<int>> Knapsack::greedy(){
    // task 2a
    // Here we first create a vector of all the value:weight ratios for our input items.
    // We then use a merge sort to sort them and log their order to get us the optimal items.
    // Since this is a greedy algorithm though, we stop checking items once we reach the first item
    // that puts us over the capacity.
    basic_ops = 0;
    vector<tuple<float, int>> ratio_vec = get_ratios();       // 0: ratio, 1: original index
    merge_ratio(ratio_vec, 0, n - 1);

    // create return vector
    tuple<int, int, vector<int>> ret;
    int cap = 0;
    for (int r = n - 1; r > 0; r--){
        cap += weights[get<1>(ratio_vec[r])];
        if (cap > capacity){
            break;
        }
        get<2>(ret).push_back(get<1>(ratio_vec[r]) + 1);
    }
    get<1>(ret) = get_optimal_value(get<2>(ret));
    get<0>(ret) = basic_ops;
    arr_sort(get<2>(ret));
    return ret;

}

void Knapsack::merge_ratio(vector<tuple<float, int>> &ratio_vec, int l , int r){
    // task 2a
    // merge sort
    basic_ops++;
    if (l >= r){
        return;
    }
    basic_ops++;
    int m = l + (r - l) / 2;
    merge_ratio(ratio_vec, l, m);
    merge_ratio(ratio_vec, m + 1, r);
    merge(ratio_vec, l, m, r);
}

void Knapsack::merge(vector<tuple<float, int>> &vec, int l , int m, int r){
    // task 2a
    // This is a merge sort algorithm to sort our ratio vector in 2a. I chose merge sort since
    // the task requires an nlogn algorithm and merge sort was the first to come to mind.
    basic_ops++;
    int n1 = m - l + 1;
    basic_ops++;
    int n2 = r - m;

    vector<tuple<float, int>> left_vec;
    vector<tuple<float, int>> right_vec;
    for(int i = 0; i < n1; i++){
        basic_ops++;
        left_vec.push_back(vec[l + i]);
    }
    for(int j = 0; j < n2; j++){
        basic_ops++;
        right_vec.push_back(vec[m + 1 + j]);
    }

    int a = 0, b = 0, k = l;
    while(a < n1 && b < n2){
        basic_ops++;
        if (get<0>(left_vec[a]) <= get<0>(right_vec[b])){
            basic_ops++;
            vec[k] = left_vec[a];
            a++;
        } else{
            basic_ops++;
            vec[k] = right_vec[b];
            b++;
        }
        k++;
    }

    basic_ops++;
    while(a < n1){
        basic_ops++;
        vec[k] = left_vec[a];
        a++;
        k++;
    }
    while(b < n2){
        basic_ops++;
        vec[k] = right_vec[b];
        b++;
        k++;
    }
}

void Knapsack::arr_sort(vector<int> &vec){
    // task 2a
    // This is used to sort the optimal subarray that is unsorted in the greedy algorithm.
    // since this is only sorting a small array, I'm just brute forcing it.
    int temp, idx;
    for (int i = 0; i < vec.size(); i++){
        temp = vec[i];
        idx = i;
        for (int j = i; j < vec.size(); j++) {
            if (temp > vec[j]) {
                temp = vec[j];
                idx = j;
            }
        }
        vec[idx] = vec[i];
        vec[i] = temp;
    }
}

tuple<int, int, vector<int>> Knapsack::heap_greedy(){
    // task 2b
    // Here we first create a vector of all the value:weight ratios for our input items.
    // We then create a max heap of our items and use deleteMax() to both delete the highest item,
    // but also to reheapify (I don't know what word to use) our max heap.
    // Since this is a greedy algorithm though, we stop checking items once we reach the first item
    // that puts us over the capacity.
    basic_ops = 0;
    vector<tuple<float, int>> ratio_vec = get_ratios();       // 0: ratio, 1: original index
    deque<tuple<float, int>> heap(ratio_vec.begin(), ratio_vec.end());
    bottomUp_heap(heap);

    // create return vector
    tuple<int, int, vector<int>> ret;
    int cap = 0;
    for (int r = 0; r < n; r++){
        cap += weights[get<1>(heap[0])];
        if (cap > capacity){
            break;
        }
        get<2>(ret).push_back(deleteMax(heap) + 1);
    }
    get<1>(ret) = get_optimal_value(get<2>(ret));
    get<0>(ret) = basic_ops;
    arr_sort(get<2>(ret));
    return ret;
}

void Knapsack::bottomUp_heap(deque<tuple<float, int>> &heap){
    // Task 2b
    // This is where we use the bottom-up algorithm to construct (or reconstruct) our max heap.
    // We fist need to add a blank item (0,0) to the start of the heap to make this work.
    // We delete the blank item at the end before returning.
    bool h;
    int j;
    int k;
    tuple<float, int> v;
    heap.push_front(v);
    for(int i = floor(heap.size()/2); i > 0; i--){
        basic_ops++;
        k = i;
        v = heap[k];
        h = false;
        while (!h && 2*k <= n){
            j = 2 * k;
            basic_ops++;
            if (j < n) {
                basic_ops++;
                if (get<0>(heap[j]) < get<0>(heap[j + 1])) {
                    basic_ops++;
                    j++;
                }
            }
            basic_ops++;
            if (get<0>(v) >= get<0>(heap[j])){
                h = true;
            }
            else{
                basic_ops++;
                heap[k] = heap[j];
                k = j;
            }
            basic_ops++;
        }
        basic_ops++;
        heap[k] = v;
    }
    heap.pop_front();
}

int Knapsack::deleteMax(deque<tuple<float, int>> &heap){
    // Task 2b
    // Here we delete the max item (first item) in the max heap, return the deleted item, and reorder
    // the heap using the bottom-up algorithm
    basic_ops++;
    int max = get<1>(heap[0]);
    basic_ops++;
    heap.pop_front();
    bottomUp_heap(heap);
    return max;
}

vector<tuple<float, int>> Knapsack::get_ratios(){
    // Task 2a, 2b
    // This calculates the ratios for all items/weights in the input and puts them into a vector.
    // We return this vector.
    vector<tuple<float, int>> ret_vec;          // 0: ratio, 1: original index
    ret_vec.resize(n);
    for (int i = 0; i < n; i++){
        basic_ops++;
        get<0>(ret_vec[i]) = float(values[i]) / weights[i];
        basic_ops++;
        get<1>(ret_vec[i]) = i;
    }
    return ret_vec;
}


// all tasks
int Knapsack::get_optimal_value(vector<int> opt_vec){
    // This is called by all 4 tasks.
    // This is used to calculate the value that the knapsack would hold with the optimal subset of items.
    int tot = 0;
    for (int i = 0; i < opt_vec.size() ; i++) {
        tot += values[opt_vec[i] - 1];
    }
    return tot;
}


// methods for main.cpp
int Knapsack::get_capacity(){
    // This is used for main.cpp and is public.
    // returns the capacity of the knapsack.
    return capacity;
}

int Knapsack::get_tot_items(){
    // This is used for main.cpp and is public.
    // returns the total items in the list.
    return n;
}


// debugging methods
void Knapsack::print_table( vector<vector<int>> table){
    // prints the table for task 1a and 1b. Only used for debugging
    for (int i = 0; i < n + 1 ; i++){
        for (int j = 0; j < capacity + 1; j++){
            cout << table[i][j] << ", ";
        }
        cout << endl;
    }
}

void Knapsack::print_sack(){
    // prints out the values and weights of the items that are to be place in the knapsack.
    // used only for debugging
    cout << "Capacity: " << capacity << endl;
    cout << "\nValues: ";
    for (int i = 0; i < n ; i++){
        cout << values.at(i) << ", ";
    }
    cout << "\n\nWeights: ";
    for (int j = 0; j < n; j++){
        cout << weights.at(j) << ", ";
    }
    cout << endl;
}
