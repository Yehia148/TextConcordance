#include <iostream>
#include <fstream>
#include <cctype>
#include "ConcordanceTree.h"
#include "TrieConcordance.h"
#include "WordNetSynonyms.h"

using namespace std;

int tokenizeLine(const string &line, string tokens[], int maxTokens) {
    string current = "";
    int count = 0;

    for (int i = 0; i <= (int) line.size(); i++) {
        char c = (i < (int) line.size()) ? line[i] : ' ';

        if (isalnum((unsigned char) c)) {
            current += c;
        } else {
            if (current != "" && count < maxTokens) {
                tokens[count] = current;
                count++;
                current = "";
            }
        }
    }

    return count;
}

int main() {
    // testing the concordance tree class
    TrieConcordance trie;
    ConcordanceTree avl;

    ifstream inputFile("../test.txt");
    if (!inputFile.is_open()) {
        cout << "File could not be opened" << endl;
        return 1;
    }

    string line;
    int lineNumber = 1;

    while (getline(inputFile, line)) {
        string tokens[200];
        int tokenCount = tokenizeLine(line, tokens, 200);

        for (int i = 0; i < tokenCount; i++) {
            string current = tokens[i];
            string next = (i + 1 < tokenCount) ? tokens[i + 1] : "";

            // insert into avl (word frequency and line number)
            avl.insert(current, lineNumber);

            // insert into trie (word and next-word relationship)
            trie.insert(current, next);
        }

        lineNumber++;
    }

    inputFile.close();

    cout << "\n=== Concordance Successfully Built ===\n" << endl;

    cout << "=== AVL WORD FREQUENCIES (alphabetical) ===" << endl;
    avl.display();
    cout << endl;

    cout << "\n=== WORDNET SYNONYMS ===" << endl;

    // get most frequent word from trie
    string mostFrequentWord = trie.getMostFrequentWord();

    if (mostFrequentWord.empty()) {
        cout << "No words found in trie.\n";
    } else {
        cout << "Most frequent word: " << mostFrequentWord << "\n";

        // call your WordNet helper
        auto synonyms = getSynonyms(mostFrequentWord);

        if (synonyms.empty()) {
            cout << "No synonyms found in WordNet for \"" << mostFrequentWord << "\".\n";
        } else {
            cout << "Synonyms:\n";
            for (const auto &s: synonyms) {
                cout << " - " << s << '\n';
            }
        }
    }

    cout << "=== TRIE CONTEXT EXAMPLES ===" << endl;
    trie.showWordInfo("the");
    trie.showWordInfo("and");
    trie.showWordInfo("apple");

    cout << "\n=== Program complete. ===" << endl;
    return 0;
}
