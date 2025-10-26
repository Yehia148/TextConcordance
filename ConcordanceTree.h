//
// Created by yahia on 10/21/2025.
//

#ifndef UNTITLED1_CONCORDANCETREE_H
#define UNTITLED1_CONCORDANCETREE_H
#include <iostream>
using namespace std;
struct Node {
    string text;
    Node* left;
    Node* right;
    int height;
    int frequency;



    Node(string&word) : text(word), left(NULL), right(NULL), height(1), frequency(1) {}
};
class ConcordanceTree {
    public:
    ConcordanceTree();
    ~ConcordanceTree();
    void display();
    void insert(string& term, int lineNumber);  // Ali
    void insert(string& term);
    Node* find(const string& term);



    private:
    Node* root;
    void print(Node*start);
    int getheight(Node*start);
    int balance(Node*start);
    Node*rightrotate(Node*start);
    Node*leftrotate(Node*start);
    string lowercase(string&term);
    Node* insertion(Node* node, string& term, int lineNumber); //Ali
    void deleteall(Node*start);
    int max(int first, int second);
};

#endif //UNTITLED1_CONCORDANCETREE_H