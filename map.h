#include <string>
#include <vector>
#include <utility>
// #include "spacy/spacy.h"
using std::string, std::vector, std::pair;


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
    int hash_fun(string token);
    vector<pair<string, int> > sort_by_frequency();
    void append_word(string word, int hash);
    void merge_sort(vector<pair<string, int> > list);

public:
    Map();
    Map(string word);
    Map(string word_list[], int word_count);
    Map(vector<string> word_list);
    void put_word(string word);
    int delete_word(string word);
    int get_frequency(string word);
};
