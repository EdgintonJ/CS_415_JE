// Author: Jordan Edginton
// Class: CS 415
// Project 3a

#include "btree.h"
#include "time.h"
#include <iomanip>
#include <sstream>
#include <iostream>
#include <deque>

using namespace std;

//Constructor
Btree::Btree(){
    root = nullptr;
}

//Returns true if there are no nodes in the tree
bool Btree::isEmpty(){
    return root == nullptr;
}

//Used to implement the search function in the main
//program.
void Btree::contains() const{
    string input;
    node *foundNode = NULL;
    cout << "Search word: ";
    cin >> input;
    if(containsHelper(input, root, foundNode)){
        if (input == get<0>(foundNode->key2)){
            cout << "Line Numbers: " << get<1>(foundNode->key2)[0];
            for(int i = 1; i < get<1>(foundNode->key2).size(); i++)
                cout << ", " <<get<1>(foundNode->key2)[i];
            cout << '\n';
        }
        else{
            cout << "Line Numbers: " << get<1>(foundNode->key1)[0];
            for(int i = 1; i < get<1>(foundNode->key1).size(); i++)
                cout << ", " <<get<1>(foundNode->key1)[i];
            cout << '\n';
        }
    }
    else
        cout << '\"' << input <<"\" is not in the document\n";
}

//Prints the index to the supplied receiver, either
//cout or the output file
void Btree::printTree(ostream & out) const {
    out << "2-3 Tree Index:\n-------------------------\n";
    printTreeHelper(root, out);
}

//Receives the specified input file and constructs
//the actual tree. Prints a message when finished.
void Btree::buildTree(ifstream & input){
    int line = 1, numWords = 0, distWords = 0, treeHeight = 0;
    stringstream tempWord;
    double totalTime, finishTime, startTime = clock();
    root = new node(" ", nullptr, nullptr);

    while (!input.eof()) {
        string tempLine, tempWord;
        //Read a whole line of text from the file
        getline(input, tempLine);
        for (int i = 0; i < tempLine.length(); i++) {
            //Insert valid chars into tempWord until a delimiter( newline or space) is found
            while (tempLine[i] != ' '&& tempLine[i] != '\n' && i < tempLine.length() ) {
                tempWord.insert(tempWord.end(), tempLine[i]);
                i++;
            }

            //Trim any punctuation off end of word. Will leave things like apostrophes
            //and decimal points
            while(tempWord.length() > 0 && !isalnum(tempWord[tempWord.length() - 1]))
                tempWord.resize(tempWord.size() -1);
            if (tempWord.length() > 0)
            {
                //Once word is formatted,call insert with the word, the line of the input
                //file it came from, the root of our tree, and the distinct word counter

                insertHelper(tempWord, line, root, distWords);

                //Increment our total number of words inserted
                numWords++;
                //Clear out tempWord so we can use it again
                tempWord.clear();
            }

        }
        line++;
    }
    //Do time and height calculation
    finishTime = clock();
    totalTime = (double) (finishTime - startTime)/CLOCKS_PER_SEC;
    treeHeight = findHeight(root);
    //Print output
    cout << setw(40) << std::left;
    cout << "Total number of words: " << numWords<< endl;

    cout << setw(40) << std::left
         << "Total number of distinct words: " << distWords << endl;

    cout << setw(40) << std::left
         <<"Total time spent building index: " << totalTime << endl;

    cout << setw(40) << std::left
         <<"Height of 2-3 tree is : " << treeHeight << endl;

}

//x is the word to insert, line is the line in the text file
//the word was found at, node is the node of the tree being
//examined, and distWord is incremented if a new word is created
//and used by buildTree
void Btree::insertHelper(const string &x, int line, node *& t, int &distWord){
    if(t->left == nullptr){
        if (x.compare(get<0>(t->key2)) == 0){
            get<1>(t->key2).push_back(line);
            return;
        }
        if (x.compare(get<0>(t->key1)) == 0){
            get<1>(t->key1).push_back(line);
            return;
        }
        tuple<string, vector<int>> new_key;
        get<0>(new_key) = x;
        get<1>(new_key).push_back(line);
        int key_size = addKey(t, new_key);
        if (key_size > 2)
            reOrgTree();
        distWord++;
        return;
    }
    else {
        //If word is already in tree, then add the line the inserted word
        //came from the the nodes lines vector
        if (t->middle != nullptr) {
            if (x.compare(get<0>(t->key2)) > 0)
                insertHelper(x, line, t->right, distWord);
            else if (x.compare(get<0>(t->key2)) == 0)
                get<1>(t->key2).push_back(line);
            else if (x.compare(get<0>(t->key1)) > 0)
                insertHelper(x, line, t->middle, distWord);
            else if (x.compare(get<0>(t->key1)) == 0)
                get<1>(t->key1).push_back(line);
            else
                insertHelper(x, line, t->left, distWord);
        }
        else {
            if (x.compare(get<0>(t->key1)) > 0)
                insertHelper(x, line, t->right, distWord);
            else if (x.compare(get<0>(t->key1)) == 0)
                get<1>(t->key1).push_back(line);
            else
                insertHelper(x, line, t->left, distWord);
        }
    }
}

//Used by contains() to see if a words is present or not. Will
//give contains() a pointer to the found node so that contains()
//can prints the lines the word was found on.
bool Btree::containsHelper(const string & x, node * t, node * &result) const{
    if (t ==nullptr)
        return false;
    if (get<0>(t->key1).compare(x) == 0 || get<0>(t->key2).compare(x) == 0){
        result = t;
        return true;
    }
    else if (x < get<0>(t->key1))
        return containsHelper(x, t->left, result);
    else if (t->middle != nullptr){
        if (x > get<0>(t->key2))
            return containsHelper(x, t->right, result);
        else if (x > get<0>(t->key1))
            return containsHelper(x, t->middle, result);
    }
    return containsHelper(x, t->right, result);
}

//Called by printTree(), does the actual formatted printing
void Btree::printTreeHelper(node *t, ostream & out) const{
    if(t == nullptr){
        return;
    }
    printTreeHelper(t->left, out);
    out << setw(30) << std::left;
    out << get<0>(t->key1) << " " << get<1>(t->key1)[0];
    for (int i = 1; i < get<1>(t->key1).size(); i++) {
        out << ", " << get<1>(t->key1)[i];
    }

    out << endl;
    if (get<0>(t->key2) != " "){
        printTreeHelper(t->middle, out);
        out << setw(30) << std::left;
        out << get<0>(t->key2) << " " << get<1>(t->key2)[0];
        for (int i = 1; i < get<1>(t->key2).size(); i++) {
            out << ", " << get<1>(t->key2)[i];
        }
        out << endl;
    }
    printTreeHelper(t->right, out);
}

//Returns height of tree. If tree has only one node, height is 1
int Btree::findHeight(node *t){
    if(t == nullptr)
        return 0;
    else{
        int leftHeight = findHeight(t->left), rightHeight = findHeight(t->right), middleHeight = findHeight(t->middle);
        if(leftHeight > rightHeight && leftHeight > middleHeight)
            return(leftHeight+1);
        else if (middleHeight > rightHeight)
            return(middleHeight+1);
        else
            return(rightHeight+1);
    }
}

int Btree::addKey(Btree::node* t, tuple<string, vector<int>> new_key) {
    // Here we add an item/key to the first open space in a node.
    // Node must be reorganized afterword.
    if (get<0>(t->key1) == " "){
        t->key1 = new_key;
        return 1;
    }
    if (get<0>(t->key2) == " "){
        t->key2 = new_key;
        reOrgNode(t);
        return 2;
    }
    else{
        t->key3 = new_key;
        reOrgNode(t);
        return 3;
    }

}

void Btree::reOrgNode(Btree::node *t) {
    // Here we organize a node to make sure both the keys and the middle pointers are organized.
    // we return 3 if there are 3 items in node, signaling a tree reorganization is needed.
    tuple<string, vector<int>> temp;
    if (get<0>(t->key3) != " ") {
            if (get<0>(t->key2) == " " || get<0>(t->key3).compare(get<0>(t->key2)) < 0) {
            temp = t->key2;
            t->key2 = t->key3;
            t->key3 = temp;
        }
    }
    if (get<0>(t->key1) == " " || get<0>(t->key2).compare(get<0>(t->key1)) < 0){
        temp = t->key2;
        t->key2 = t->key1;
        t->key1 = temp;
    }
    if (t->middle4 != nullptr){
        if (get<0>(t->middle->key2).compare(get<0>(t->middle4->key2)) > 0){
            node* temp_node = t->middle;
            t->middle = t->middle4;
            t->middle4 = temp_node;
        }
    }
}

void Btree::reOrgTree(){
    // This is the function for reorganizting the tree and is called when 3 keys are in 1 node.
    // We first check if the root has 3 items since we will need to create 2 new nodes instead of 1.
    // This function is NOT recursive, but it will call itself if 3 items are still in a node.
    if (get<0>(root->key3) != " "){
        node* new_right = new node(" ", root->middle4, root->right);
        node* new_root = new node(" ", root, new_right);
        addKey(new_root, root->key2);
        addKey(new_right, root->key3);
        root->right = root->middle;
        root->middle4 = nullptr;
        root->middle = nullptr;
        root->key2 = new_right->key3;
        root->key3 = new_right->key3;
        root = new_root;
        return;
    }

    node* t;
    deque<node*> queue;
    queue.push_back(root);
    int key_size = 0;

    // Here we iteratively go through the tree level by level using a double-ended queue to find
    // the node that has 3 keys. when found, we make a new node, promote the middle key,
    // and check if the node with the promoted key has 3 items. If so, we call reOrgTree() again.
    while (!(queue.empty())){
        t = queue.front();
        if (t->left != nullptr) {
            if(get<0>(t->left->key3) != " "){
                key_size = addKey(t, t->left->key2);
                node* new_right = new node(" ", t->left->middle4, t->left->right);
                addKey(new_right, t->left->key3);
                if (t->middle == nullptr)
                    t->middle = new_right;
                else{
                    t->middle4 = t->middle;
                    t->middle = new_right;
                }
                t->left->right = t->left->middle;
                t->left->middle4 = nullptr;
                t->left->middle = nullptr;
                t->left->key2 = new_right->key3;
                t->left->key3 = new_right->key3;
                if (key_size == 3)
                    return reOrgTree();
                return;
            }
            else if(get<0>(t->right->key3) != " ") {
                key_size = addKey(t, t->right->key2);
                node *new_left = new node(" ", t->right->left, t->right->middle);
                addKey(new_left, t->right->key1);
                if (t->middle == nullptr)
                    t->middle = new_left;
                else {
                    t->middle4 = new_left;
                }
                t->right->left = t->right->middle4;
                t->right->middle4 = nullptr;
                t->right->middle = nullptr;
                t->right->key1 = t->right->key3;
                t->right->key2 = new_left->key3;
                t->right->key3 = new_left->key3;
                if (key_size == 3)
                    return reOrgTree();
                return;
            }
            else if(t->middle != nullptr && get<0>(t->middle->key3) != " ") {
                addKey(t, t->middle->key2);
                node *new_middle = new node(" ", t->middle->middle4, t->middle->right);
                addKey(new_middle, t->middle->key3);
                t->middle4 = new_middle;
                t->middle->right = t->middle->middle;
                t->middle->middle4 = nullptr;
                t->middle->middle = nullptr;
                t->middle->key2 = new_middle->key3;
                t->middle->key3 = new_middle->key3;
                return reOrgTree();
            }
            queue.push_back(t->left);
            queue.push_back(t->right);
            if (t->middle != nullptr)
                queue.push_back(t->middle);
        }
        queue.pop_front();

    }
}

void Btree::contains(string x){
    // This is used for option c to search for every word.
    node* temp;
    containsHelper(x, root, temp);
}

vector<string> Btree::every_word() {
    // This is used to create a vector of every word in the index to use for option c.
    vector<string> ret;
    node *t;
    deque<node *> queue;
    queue.push_back(root);
    while (!(queue.empty())) {
        t = queue.front();
        ret.push_back(get<0>(t->key1));
        if (get<0>(t->key2) != " "){
            ret.push_back(get<0>(t->key2));
        }
        if (t->left != nullptr) {
            queue.push_back(t->left);
            queue.push_back(t->right);
            if (t->middle != nullptr){
                queue.push_back(t->middle);
            }
        }
        queue.pop_front();
    }
    return ret;
}