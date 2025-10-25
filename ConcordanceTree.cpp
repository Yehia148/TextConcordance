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
    start->height = 1 + max(getheight(T->left), getheight(start->right));
    R->height = 1 + max(getheight(R->left), getheight(R->right));
    return start; // Return new root
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
    return start; // Return new root

}
int ConcordanceTree::max(int first, int second) {
    if (first > second) { //this function returns the greater of two numbers.
        return first;
    }
    else {
        return second;
    }
}

void ConcordanceTree::insert(string&term) {

}
Node *ConcordanceTree::insertion(Node *node, string &term) {

}

void ConcordanceTree::display(string&term) {

}
string ConcordanceTree::lowercase(string &term) {

}
void ConcordanceTree::print(Node *start) {

}



