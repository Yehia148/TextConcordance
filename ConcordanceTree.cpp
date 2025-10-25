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

}
int ConcordanceTree::getheight(Node *start) {

}
Node *ConcordanceTree::leftrotate(Node *start) {

}
Node *ConcordanceTree::rightrotate(Node *start) {

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



