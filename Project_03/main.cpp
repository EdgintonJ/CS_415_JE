// Author: Jordan Edginton
// Class: CS 415
// Project 3a
//Description: Takes a text file supplied by the user
//             and turns it into a word index, implemented
//             through the use of a BST or 2-3 tree.

#include <iostream>
#include <fstream>
#include "btree.h"
#include "bst.h"
#include "time.h"

using namespace std;

int main(int argc, char* argv[]) {
    int choice;
    char choice1 = ' ';
    if (argc != 2) {
        cout << "Incorrect input. Correct format: ./<exectuable.out> <inputtext.txt>\n";
        return 1;
    }

    ifstream input(argv[1]);
    BST myTree;
    Btree myBtree;

    // choice1 = '';
    cout <<"Options: (a) BST, (b) 2-3 Tree, (c) Compare BST and 2-3 Tree, (d) Quit\n";
    while(choice1 != 'a' and choice1 != 'b' and choice1 != 'c'){
        cin >> choice1;
        if (choice1 == 'd')
            return 0;
    }

    if (choice1 == 'a'){
        if(input.is_open()){
            myTree.buildTree(input);
            input.close();
            while(1){
                choice = 0;
                cout <<"Options: (1) display index, (2) search, (3) save index, (4) quit\n";
                cin >> choice;

                //Print index
                if(choice == 1)
                    myTree.printTree(cout);

                    //Search index for a word
                else if(choice == 2)
                    myTree.contains();

                    //Save index
                else if(choice == 3){
                    string outputFile;
                    cout << "Enter a filename to save your index to (Suggested: <filename>.txt) : ";
                    cin >> outputFile;
                    ofstream output(outputFile.c_str());
                    myTree.printTree(output);
                    output.close();
                    cout << "Saved\n";
                }

                    //Quit
                else
                    break;
            }
        }
        else{
            cout << "Invalid File Name. Restart Program.\n";
            return 2;
        }
    }
    if (choice1 == 'b'){
        if(input.is_open()){
            myBtree.buildTree(input);
            input.close();
            while(1){
                choice = 0;
                cout <<"Options: (1) display index, (2) search, (3) save index, (4) quit\n";
                cin >> choice;

                //Print index
                if(choice == 1)
                    myBtree.printTree(cout);

                    //Search index for a word
                else if(choice == 2)
                    myBtree.contains();

                    //Save index
                else if(choice == 3){
                    string outputFile;
                    cout << "Enter a filename to save your index to (Suggested: <filename>.txt) : ";
                    cin >> outputFile;
                    ofstream output(outputFile.c_str());
                    myBtree.printTree(output);
                    output.close();
                    cout << "Saved\n";
                }

                    //Quit
                else
                    break;
            }
        }
        else{
            cout << "Invalid File Name. Restart Program.\n";
            return 2;
        }
    }
    else if (choice1 == 'c'){
        // Create trees
        if(input.is_open()){
            myTree.buildTree(input);
            input.clear();
            input.seekg(0);
            cout << endl;
            myBtree.buildTree(input);
            input.close();

            // get every word in index and put into a vector, then search all words in both trees.
            vector<string> words = myBtree.every_word();
            cout << "\nSearching entire index, BST..." << endl;
            double bst_totalTime, bst_finishTime, bst_startTime = clock();
            for (int i = 0; i < words.size(); i++){
                myTree.contains(words[i]);
            }
            bst_finishTime = clock();
            cout << "Searching entire index, 2-3 tree..." << endl;
            double btree_totalTime, btree_finishTime, btree_startTime = clock();
            for (int i = 0; i < words.size(); i++){
                myBtree.contains(words[i]);
            }
            btree_finishTime = clock();

            // calculate time taken to search trees
            bst_totalTime = (double) (bst_finishTime - bst_startTime)/CLOCKS_PER_SEC;
            btree_totalTime = (double) (btree_finishTime - btree_startTime)/CLOCKS_PER_SEC;

            // print results
            cout << "\nTimes for searching entire index:" << endl;
            cout << "Total time taken by BST:              " << bst_totalTime << endl;
            cout << "Total time taken by 2-3 Tree:         " << btree_totalTime << endl;
        }
        else{
            cout << "Invalid File Name. Restart Program.\n";
            return 2;
        }
    }

    return 0;
}