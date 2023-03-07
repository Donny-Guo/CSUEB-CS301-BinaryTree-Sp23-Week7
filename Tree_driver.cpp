//
// Created by Dongping Guo on 3/5/23.
//
#include <iostream>
#include <fstream>
#include <string>
#include "TreeT.h"

using namespace std;

void PrintTree(ofstream& outfile, TreeT<int> &tree);

int main(){
    ifstream infile;
    ofstream outfile;
    string inFileName;
    string outFileName;
    string testLabel;
    string command;

    int item;
    TreeT<int> tree;

    cout << "Enter the name of the input command file and press enter." << endl;
    cin >> inFileName;
    infile.open(inFileName.c_str());

    cout << "Enter the name of the output file and press enter." << endl;
    cin >> outFileName;
    outfile.open(outFileName.c_str());

    cout << "Enter the name of the test run; press enter" << endl;
    cin >> testLabel;
    outfile << testLabel << endl;

    if (infile.fail()){
        cout << "Cannot open the input file.";
        exit(2);
    }

    infile >> command;

    while (command != "Quit"){
        if (command == "Add") {
            infile >> item;
            tree.Add(item);
            outfile << item << " has been added to the tree" << endl;
        }
        else if (command == "Remove"){
            infile >> item;
            tree.Remove(item);
            outfile << item << " has been removed from the tree" << endl;
        }
        else if (command == "Contains") {
            infile >> item;
            if (tree.Contains(item)) {
                cout << item << " found in list." << endl;
                outfile << item << " found in list." << endl;
            }
            else {
                cout << item << " not in list." << endl;
                outfile << item << " not in list." << endl;
            }
        }
        else if (command == "GetLength"){
            outfile << "There are " << tree.Size() << " nodes in the tree." << endl;
        }
        else if (command == "PrintTree"){
            PrintTree(outfile, tree);
        }
        else if (command == "MakeEmpty"){
            tree.MakeEmpty();
        }
        infile >> command;
    }

    infile.close();
    outfile.close();
    return 0;
}

void PrintTree(ofstream& outfile, TreeT<int> &tree) {
    if (tree.Size() == 0){
        outfile << "Tree is empty" << endl;
        return;
    }
    tree.ResetIterator(IN_ORDER);
    for (int i = 0; i < tree.Size(); i++){
        outfile << tree.GetNextItem() << ", ";
    }
    outfile << endl;

}
