#ifndef MAP.H
#define MAP.H

#include "map.h"


Map::Map() {
    frequency_list = new Node*[LIST_LENGTH];
    word_count = 0;
}


Map::Map(string word) {
    frequency_list = new Node*[2000];
    word_count = 0;
    
    put_word(word);
}


Map::Map(string word_list[], int size) {
    frequency_list = new Node*[LIST_LENGTH];
    word_count = 0;
    
    for(int i=0; i<size; ++i) {
        put_word(word_list[i]);
    }
}


Map::Map(vector<string> word_list) {
    frequency_list = new Node*[LIST_LENGTH];
    word_count = 0;

    for(string item : word_list) {
        put_word(item);
    }
}


void Map::append_word(string word, int hash) {
    Node *n, *temp = frequency_list[hash];
    if (!temp) {
        frequency_list[hash] = new Node(word, 1, nullptr);
        return;
    }

    while (temp) {
        n = temp;
        temp = temp->next;
    }

    n->next = new Node(word, 1, nullptr);
    ++word_count;
}


void Map::put_word(string word) {
    unsigned int hash = hash_fun(word);
    Node *n, *temp = frequency_list[hash];
    bool added = false;

    while (temp) {
        n = temp;
        temp = temp->next;

        if (n->word == word) {
            ++n->frequency;
            added = true;
            break;
        }
    }

    if (!added) {
        pair<string, int> temp(word, 1);
        append_word(word, hash);
    }
}


int Map::delete_word(string word) {
    int hash = hash_fun(word);
    Node *n, *temp = frequency_list[hash];

    while (temp) {
        n = temp;

        if (n->word == word) {
            if (n->frequency) return --n->frequency;
            return 0;
        }

        temp = temp->next;
    }
    return -1;
}


int Map::get_frequency(string word) {
    int hash = hash_fun(word);
    Node *n, *temp = frequency_list[hash];

    while (temp) {
        n = temp;

        if (n->word == word) {
            return n->frequency;
        }

        temp = temp->next;
    }

    return 0;
}


void merge_sort(vpsi &list) {
    if (list.empty() || list.size() == 1) return;

    vpsi half_1(vpsi(list.begin(), list.end() + (list.end()-list.begin()) / 2));
    vpsi half_2(vpsi(list.end() + (list.end()-list.begin()) / 2, list.end()));
    merge_sort(half_1);
    merge_sort(half_2);

    int i=0, j=0, ind=0;
    for (i, j, ind; i<half_1.size(), j<half_2.size(); ++ind) {
        if(half_1[i].second < half_2[j].second) {
            list[ind] = half_1[i];
            ++i;
        } else {
            list[ind] = half_2[j];
            ++j;
        }
    }

    if (i == half_1.size()) {
        for (j; j<half_2.size(); ++j) {
            list[ind] = half_2[j];
        }
    } else if (j == half_2.size()) {
        for (i; i<half_1.size(); ++i) {
            list[ind] = half_1[i];
        }
    }
}


vpsi Map::sort_by_frequency() {
    vpsi list;
    list.reserve(word_count);
    for (int i=0; i<LIST_LENGTH; ++i) {
        Node *n, *temp = frequency_list[i];

        while (temp) {
            list.push_back(pair<string, int>(temp->word, temp->frequency));
        }
    }

    merge_sort(list);
    return list;
}


#endif