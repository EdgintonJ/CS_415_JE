// Author: Jordan Edginton
// Class: CS 415
// Project 3a

#ifndef PROJECT_03A_BTREE_H
#define PROJECT_03A_BTREE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>


using namespace std;

class Btree {
public:
    Btree();
    void contains() const;
    void contains(string x);
    bool isEmpty();
    void printTree(ostream & out = cout) const;
    void buildTree(ifstream & input);
    vector<string> every_word();
private:
    struct node{
        node(const string &x, node *l, node *r){
            get<0>(key1) = x , get<0>(key2) = ' ', get<0>(key3) = ' ';
            left = l, middle = nullptr, middle4 = nullptr, right = r;
            {
                get<1>(key1).resize(0);
                get<1>(key2).resize(0);
                get<1>(key3).resize(0);
            }
        }
        node * left;
        node * middle;
        node * middle4;                     // only occupied for when there are 4 children and tree must be reorganized
        node * right;
        tuple<string, vector<int>> key1;
        tuple<string, vector<int>> key2;
        tuple<string, vector<int>> key3;    // if occupied, tree must be reorganized
    };
    node * root;
    void insertHelper(const string &X, int line, node *& t, int &distWords);
    bool containsHelper(const string & x, node * t, node* &result) const;
    void printTreeHelper(node *t, ostream & out) const;
    int findHeight(node *t);
    int addKey(node* t, tuple<string, vector<int>> new_key);
    void reOrgNode(node *t);
    void reOrgTree();
};


#endif //PROJECT_03A_BTREE_H
