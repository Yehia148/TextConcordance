//
// Created by yahia on 10/21/2025.
//

#include "ConcordanceTree.h"
ConcordanceTree::ConcordanceTree() {
root = nullptr; //Constructor creates a root that is null.
}
ConcordanceTree::~ConcordanceTree() {
if (!root) { //destructor uses the deleteall function to clear all of the nodes.
    return;
}
    deleteall(root);

}
void ConcordanceTree::deleteall(Node *start) {
    if (!start) { //the function traverses through the entire tree recursively and deletes the nodes.
        return;
    }
    deleteall(start->left);
    deleteall(start->right);
    delete start;
}
int ConcordanceTree::balance(Node *start) {
if (!start) { //This provides the balance starting from the node.
    return 0; //if the given pointer is null, just return zero, but if it is not then return the difference
              //in height.
}
    else {
        return getheight(start->left) - getheight(start->right);
    }
}
int ConcordanceTree::getheight(Node *start) {
    if (!start) { //This provides the balance starting from the node.
        return 0; //if the given pointer is null, just return zero, but if it is not then return the difference
        //in height.
    }
    else {
        return start->height;
    }
}
Node *ConcordanceTree::leftrotate(Node *start) { //regular right rotation implementation for AVL Tree.
    Node *R = start->right;
    Node *R_L = R->left;
    // Perform rotation
    R->left = start;
    start->right = R_L;
    // Update heights
    start->height = 1 + max(getheight(start->left), getheight(start->right));
    R->height = 1 + max(getheight(R->left), getheight(R->right));
    return R; // Return new root
}
Node *ConcordanceTree::rightrotate(Node *start) { //regular right rotation implementation for AVL Tree.
    Node *L = start->left;
    Node *L_R = L->right;
    // Perform rotation
    L->right = start;
    start->left = L_R;
    // Update heights
    start->height = 1 + max(getheight(start->left), getheight(start->right));
    L->height = 1 + max(getheight(L->left), getheight(L->right));
    return L; // Return new root

}
int ConcordanceTree::max(int first, int second) {
    if (first > second) { //this function returns the greater of two numbers.
        return first;
    }
    else {
        return second;
    }
}

void ConcordanceTree::insert(string& term, int lineNumber) { //Ali (added the int lineNumber)
    //insert an element into the AVL Tree after going through the lowercase function.
    string fixed = lowercase(term);
    if (!fixed.empty()) {
        root = insertion(root, fixed, lineNumber);
    }
}

// void ConcordanceTree::insert(string& term) { //Ali (Overloaded the function)
//     int dummyLine = -1;
//     insert(term, dummyLine);
// }

Node* ConcordanceTree::insertion(Node* node, string& term, int lineNumber) {


    if (node == nullptr) { // create new node for this word
        Node* newNode = new Node(term);
        return newNode;
    }

    if (term < node->text)
        node->left = insertion(node->left, term, lineNumber);
    else if (term > node->text)
        node->right = insertion(node->right, term, lineNumber);
    else {
        // word already exists
        node->frequency++;
        return node;
    }

    // update height
    node->height = 1 + max(getheight(node->left), getheight(node->right));

    // rebalance if needed
    int balancefactor = balance(node);

    // Left Left
    if (balancefactor > 1 && term < node->left->text)
        return rightrotate(node);

    // Right Right
    if (balancefactor < -1 && term > node->right->text)
        return leftrotate(node);

    // Left Right
    if (balancefactor > 1 && term > node->left->text) {
        node->left = leftrotate(node->left);
        return rightrotate(node);
    }

    // Right Left
    if (balancefactor < -1 && term < node->right->text) {
        node->right = rightrotate(node->right);
        return leftrotate(node);
    }

    return node;
}

Node* ConcordanceTree::find(string& term) { //Ali (added a function that searches for a specific word)
    string fixed = lowercase((term));
    Node* current = root;
    while (current != nullptr) {
        if (fixed < current->text)
            current = current->left;
        else if (fixed > current->text)
            current = current->right;
        else
            return current; // found
    }
    return nullptr;
}



void ConcordanceTree::display() {
print(root); //uses the print function to display frequency of each word starting from the root.
}
string ConcordanceTree::lowercase(string &term) {
string lower;
    for (char a: term) { //goes through every letter in the string
        if (isalnum(a)) { //library function that checks if it is alphanumeric
            lower += tolower(a); //makes the letter lowercase
        }
    }
    return lower;
}
void ConcordanceTree::print(Node *start) {
    if (!start) { //goes through the entire tree and prints out the word and the frequency next to it.
        return;   //this is the helper function for getting the frequency starting from the root.
    }
    print(start->left);
    cout << start->text << ": " << start->frequency << endl;
    print(start->right);
}



