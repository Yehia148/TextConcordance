/**
 * The map module implements a Map class using linked lists as buckets.
 * Keys are word strings and values are the number of times a word
 * appears throughout the user's text.
 */

#pragma once
#include <string>
#include <vector>
#include <utility>
#include <stdint.h>
// #include "spacy/spacy.h"
using std::string, std::vector, std::pair;

typedef vector<pair<string, int> > vpsi;


class Node {
public:
    string word;
    int frequency;
    Node* next;
    Node(string word, int frequency, Node* next): word(word), frequency(frequency), next(next) {}
};


class Map {
private:
    Node** frequency_list;
    const int LIST_LENGTH = 2503;
    int word_count;
    uint32_t rotate_left_32bit(uint32_t hash, const uint32_t &r2);
    uint32_t hash_fun(string key);

    void append_word(string word, int hash);
    void merge_sort(vpsi &list);

public:
    Map();
    ~Map();
    Map(string word);
    Map(string word_list[], int word_count);
    Map(vector<string> word_list);
    void put_word(string word);
    int delete_word(string word);
    int get_frequency(string word);
    vpsi sort_by_frequency();
};
