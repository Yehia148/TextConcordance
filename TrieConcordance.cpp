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
} //ensures the word is alphabetical

int TrieConcordance::charIndex(char c) {
    // assume already lowercase a-z
    return c - 'a';
} //we subtract in order to get the correct indexing for the letter in children[]

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
} //goes through the trie to each character of the word. Adds nodes where needed for the word and returns the node corresponding to the last letter.

TrieNode* TrieConcordance::findPath(const string& word) { //returns the node for a word if it exists.
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

void TrieConcordance::growFollowList(TrieNode* node) { //when the number of words reaches the capacity, double side of capacity.
    if (node->followCapacity == 0) { //the follow list stores the words that directly follow a given word in input text
        node->followCapacity = 4; //if the word in the follow list already exists, increment its count.
                                    //else, grow the list and insert it. Helps track bigrams.
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
    /**
     * Processes a pair of words into the trie.
     */
    string currentWord = normalizeToken(currentWordRaw);
    if (currentWord.size() == 0) {
        return;
    } //normalize current and next words, traverse currentword in the trie, mark as end of valid word, increment appearance in frequency, record the word coming after it.

    string nextWord = normalizeToken(nextWordRaw);

    TrieNode* node = insertPath(currentWord);

    // mark end of word
    node->isEndOfWord = true;
    node->frequency++;

    // record n-gram info
    addFollower(node, nextWord);
}



void TrieConcordance::printTopFollowers(TrieNode* node) { //prints the three most frequent next words in descending order.
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
    /**
     * Displays the frequency of a word within word
     * pairs if the word is found in the trie.
     * If the word is not found, an error is printed.
     */
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


void TrieConcordance::freeAll(TrieNode* node) { //deletes all nodes and follower list from memory recursively.
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

void TrieConcordance::findMostFrequent(TrieNode* node,
                                       string& current,
                                       string& bestWord,
                                       int& bestFreq) {
    if (!node) return;

    // If this node marks the end of a word, check its frequency
    if (node->isEndOfWord && node->frequency > bestFreq) {
        bestFreq = node->frequency;
        bestWord = current;
    }

    // Traverse children 'a'..'z'
    for (int i = 0; i < 26; i++) {
        if (node->children[i] != nullptr) {
            current.push_back('a' + i);                     // go down
            findMostFrequent(node->children[i], current,    // recurse
                             bestWord, bestFreq);
            current.pop_back();                             // backtrack
        }
    }
}

string TrieConcordance::getMostFrequentWord() {
    /**
     * Returns the most frequent word in the trie's stored phrases.
     */
    string bestWord;
    int bestFreq = 0;
    string current;

    findMostFrequent(root, current, bestWord, bestFreq);
    return bestWord;   // will be "" if trie is empty
}

bool TrieConcordance::getBestCompletion(const string& prefix, string& outWord) {
    /**
     * Extracts the most frequent word containing the given prefix.
     * If none are found (the prefix does not exist) the function returns false.
     */
    string norm = normalizeToken(prefix);
    if (norm.empty()) return false;

    TrieNode* node = findPath(norm);
    if (!node) return false;

    string bestWord;
    int bestFreq = 0;
    string current = norm;

    findMostFrequent(node, current, bestWord, bestFreq);
    if (bestFreq == 0) return false;

    outWord = bestWord;
    return true;
}

bool TrieConcordance::getNextWordSuggestion(const string& prevWord,
                                            const string& nextPrefix,
                                            string& outWord) {
    /**
     * Extracts the most frequent successor of the given word-prefix combination.
     * If none are found (the combination does not exist) the function returns false.
     */
    string prev = normalizeToken(prevWord);
    if (prev.empty()) return false;

    TrieNode* node = findPath(prev);
    if (!node || node->followCount == 0) return false;

    string normPrefix = normalizeToken(nextPrefix);
    int bestCount = 0;
    string best;

    for (int i = 0; i < node->followCount; i++) {
        const string& w = node->followList[i].word;
        if (!normPrefix.empty()) {
            if (w.size() < normPrefix.size() ||
                w.compare(0, normPrefix.size(), normPrefix) != 0) {
                continue;
                }
        }
        int c = node->followList[i].count;
        if (c > bestCount) {
            bestCount = c;
            best = w;
        }
    }

    if (bestCount == 0 || best.empty()) return false;

    outWord = best;
    return true;
}
