#ifndef TRIE_CONCORDANCE_H
#define TRIE_CONCORDANCE_H

#include <iostream>
using namespace std;


struct NextWordEntry {
    string word;
    int count;
};

struct TrieNode {
    TrieNode* children[26];
    bool isEndOfWord;
    int frequency;

    // dynamic array that tracks words that come after
    NextWordEntry* followList;
    int followCount;
    int followCapacity;

    TrieNode();
};

class TrieConcordance {
public:
    TrieConcordance();
    ~TrieConcordance();


    void insert(const string& currentWord, const string& nextWord);
    void showWordInfo(const string& rawWord);
    string getMostFrequentWord();
private:
    TrieNode* root;

    // helper: turns "Apple" into "apple"
    string normalizeToken(const string& raw);

    // helper: map 'a'..'z' to 0..25, assume input already normalized
    int charIndex(char c);


    TrieNode* insertPath(const string& word);


    TrieNode* findPath(const string& word);


    void addFollower(TrieNode* node, const string& nextWord);


    void growFollowList(TrieNode* node);

    void freeAll(TrieNode* node);


    void printTopFollowers(TrieNode* node);

    void findMostFrequent(TrieNode* node,
                          string& current,
                          string& bestWord,
                          int& bestFreq);
};

#endif // TRIE_CONCORDANCE_H