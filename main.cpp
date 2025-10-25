#include <iostream>
#include <fstream>
#include "ConcordanceTree.h"

using namespace std;
int main() { //testing the concordance tree class
ConcordanceTree tree;
    ifstream inputFile("../test.txt");
    if (!inputFile.is_open()) {
        cout << "File could not be opened" << endl;
        return 1;
    }
    cout << "From the test.txt file: " << endl;
    string words;
    while (inputFile >> words) {
        tree.insert(words);
    }
    inputFile.close();
    cout << "Displaying tree contents here:" << endl;
    tree.display();
    return 0;
}