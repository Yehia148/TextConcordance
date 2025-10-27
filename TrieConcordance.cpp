#include "TrieConcordance.h"
#include <cctype>


TrieNode::TrieNode() { //building Trie node structure - provides value to each of the variables and creates an array of 26 children.
    isEndOfWord = false;
    frequency = 0;
    followList = NULL;
    followCount = 0;
    followCapacity = 0;
    for (int i = 0; i < 26; i++) {
        children[i] = NULL;
    } //node takes character, not word.
}


TrieConcordance::TrieConcordance() {
    root = new TrieNode(); //constructor gives the root an empty node.
}

TrieConcordance::~TrieConcordance() { //destructor deletes the nodes to free up memory.
    freeAll(root);
}


string TrieConcordance::normalizeToken(const string& raw) {
    string out;
    for (int i = 0; i < (int)raw.size(); i++) {
        char c = raw[i];
        if (isalpha((unsigned char)c)) { //unsigned char used for safety.
            out += (char)tolower((unsigned char)c);
        }
    }
    return out;
}

int TrieConcordance::charIndex(char c) {
    // assume already lowercase a-z
    return c - 'a';
}

TrieNode* TrieConcordance::insertPath(const string& word) {
    TrieNode* cur = root;
    for (int i = 0; i < (int)word.size(); i++) {
        int idx = charIndex(word[i]);
        if (idx < 0 || idx >= 26) {
            // skip anything weird, but normalizeToken already filtered
            continue;
        }
        if (cur->children[idx] == NULL) {
            cur->children[idx] = new TrieNode();
        }
        cur = cur->children[idx];
    }
    return cur;
}

TrieNode* TrieConcordance::findPath(const string& word) {
    TrieNode* cur = root;
    for (int i = 0; i < (int)word.size(); i++) {
        int idx = charIndex(word[i]);
        if (idx < 0 || idx >= 26) {
            return NULL;
        }
        if (cur->children[idx] == NULL) {
            return NULL;
        }
        cur = cur->children[idx];
    }
    if (cur->isEndOfWord == false) {
        // we only consider it valid if we marked it before
        return NULL;
    }
    return cur;
}

void TrieConcordance::growFollowList(TrieNode* node) {
    if (node->followCapacity == 0) {
        node->followCapacity = 4;
        node->followList = new NextWordEntry[node->followCapacity];
        node->followCount = 0;
    } else if (node->followCount >= node->followCapacity) {
        int newCap = node->followCapacity * 2;
        NextWordEntry* newArr = new NextWordEntry[newCap];
        for (int i = 0; i < node->followCount; i++) {
            newArr[i] = node->followList[i];
        }
        delete[] node->followList;
        node->followList = newArr;
        node->followCapacity = newCap;
    }
}

void TrieConcordance::addFollower(TrieNode* node, const string& nextWord) {
    if (nextWord.size() == 0) {
        return;
    }

    // see if its already in followList
    for (int i = 0; i < node->followCount; i++) {
        if (node->followList[i].word == nextWord) {
            node->followList[i].count++;
            return;
        }
    }

    // otherwise add a new entry
    growFollowList(node);
    node->followList[node->followCount].word = nextWord;
    node->followList[node->followCount].count = 1;
    node->followCount++;
}


void TrieConcordance::insert(const string& currentWordRaw, const string& nextWordRaw) {
    string currentWord = normalizeToken(currentWordRaw);
    if (currentWord.size() == 0) {
        return;
    }

    string nextWord = normalizeToken(nextWordRaw);

    TrieNode* node = insertPath(currentWord);

    // mark end of word
    node->isEndOfWord = true;
    node->frequency++;

    // record n-gram info
    addFollower(node, nextWord);
}



void TrieConcordance::printTopFollowers(TrieNode* node) {
    if (node->followCount == 0) {
        cout << "No common next-word suggestions." << endl;
        return;
    }



    int topIdx[3] = {-1, -1, -1};
    int topCount[3] = {-1, -1, -1};

    for (int i = 0; i < node->followCount; i++) {
        int c = node->followList[i].count;

        // insert into top3 if it's bigger than something
        for (int k = 0; k < 3; k++) {
            if (c > topCount[k]) {
                // shift down
                for (int m = 2; m > k; m--) {
                    topCount[m] = topCount[m-1];
                    topIdx[m] = topIdx[m-1];
                }
                // place here
                topCount[k] = c;
                topIdx[k] = i;
                break;
            }
        }
    }

    cout << "Most common next words:" << endl;
    for (int k = 0; k < 3; k++) {
        if (topIdx[k] != -1) {
            cout << "  \"" << node->followList[topIdx[k]].word
                 << "\"  (x" << node->followList[topIdx[k]].count << ")"
                 << endl;
        }
    }
}

void TrieConcordance::showWordInfo(const string& rawWord) {
    string word = normalizeToken(rawWord);
    if (word.size() == 0) {
        cout << "Invalid word." << endl;
        return;
    }

    TrieNode* node = findPath(word);
    if (node == NULL) {
        cout << "Word \"" << word << "\" not found." << endl;
        return;
    }

    cout << "Word: " << word << endl;
    cout << "Frequency: " << node->frequency << endl;
    printTopFollowers(node);
}


void TrieConcordance::freeAll(TrieNode* node) {
    if (node == NULL) return;

    for (int i = 0; i < 26; i++) {
        if (node->children[i] != NULL) {
            freeAll(node->children[i]);
        }
    }

    if (node->followList != NULL) {
        delete[] node->followList;
    }

    delete node;
}