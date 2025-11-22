#ifndef MAP_H
#define MAP_H

#include "map.h"
#include <iostream>
using std::cout;


Map::Map() {
    frequency_list = new Node*[LIST_LENGTH]();
    word_count = 0;
}
Map::~Map() {
    if (frequency_list) {
        for (int i = 0; i < LIST_LENGTH; ++i) {
            Node* current = frequency_list[i];
            while (current) {
                Node* next = current->next;
                delete current;
                current = next;
            }
        }
        delete[] frequency_list;
        frequency_list = nullptr;
    }
}

Map::Map(string word) {
    frequency_list = new Node*[2000];
    word_count = 0;
    
    put_word(word);
}


Map::Map(string word_list[], int size) {
    frequency_list = new Node*[LIST_LENGTH]();
    word_count = 0;
    
    for(int i=0; i<size; ++i) {
        put_word(word_list[i]);
    }
}


Map::Map(vector<string> word_list) {
    frequency_list = new Node*[LIST_LENGTH]();
    word_count = 0;

    for(string item : word_list) {
        put_word(item);
    }
}


void Map::append_word(string word, int hash) {
    Node *n, *temp = frequency_list[hash];
    if (!temp) {
        frequency_list[hash] = new Node(word, 1, nullptr);
        ++word_count;
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


void Map::merge_sort(vpsi &list) {
    if (list.empty() || list.size() == 1) return;

    vpsi half_1(vpsi(list.begin(), list.begin() + (list.end()-list.begin()) / 2));
    vpsi half_2(vpsi(list.begin() + (list.end()-list.begin()) / 2, list.end()));
    merge_sort(half_1);
    merge_sort(half_2);

    // int i=0, j=0, ind=0;
    // for (i, j, ind; i<half_1.size(), j<half_2.size(); ++ind) {
    //     if(half_1[i].second < half_2[j].second) {
    //         list[ind] = half_1[i];
    //         ++i;
    //     } else {
    //         list[ind] = half_2[j];
    //         ++j;
    //     }
    // }

    // if (i == half_1.size()) {
    //     for (j; j<half_2.size(); ++j) {
    //         list[ind] = half_2[j];
    //     }
    // } else if (j == half_2.size()) {
    //     for (i; i<half_1.size(); ++i) {
    //         list[ind] = half_1[i];
    //     }
 //   }
    int i = 0, j = 0, ind = 0;
    while (i < half_1.size() && j < half_2.size()) {
        if (half_1[i].second < half_2[j].second) {
            list[ind++] = half_1[i++];
        } else {
            list[ind++] = half_2[j++];
        }
    }

    while (i < half_1.size()) list[ind++] = half_1[i++];
    while (j < half_2.size()) list[ind++] = half_2[j++];
}


vpsi Map::sort_by_frequency() {
    vpsi list;
    list.reserve(word_count);
    for (int i=0; i<LIST_LENGTH; ++i) {
        Node *n, *temp = frequency_list[i];

        while (temp) {
            list.push_back(pair<string, int>(temp->word, temp->frequency));
            temp = temp->next;
        }
    }

    merge_sort(list);
    return list;
}


uint32_t Map::rotate_left_32bit(uint32_t hash, const uint32_t &r2) {
    for (int i=0; i<r2; ++i) {
        bool temp = 1<<31 & hash;
        hash = hash << 1;
        hash |= temp;
        // cout << bitset<32>(hash) << "\n";
    }

    return hash;
}
uint32_t Map::hash_fun(string key) {
    // const uint32_t c1 = 0xcc9e2d51,
    //     c2 = 0x1b873593,
    //     r1 = 15,
    //     r2 = 13,
    //     m = 5,
    //     n = 0xe6546b64;

    // uint32_t hash = 0x9747b28c;  // Initial randomly chosen seed

    // // Loop over the string in 4-byte chunks
    // const int nblocks = key.size() / 4;
    // int32_t *blocks = (int32_t *)key.data();
    // for (int i=0; i<nblocks; ++i) {
    //     uint32_t k = blocks[i];

    //     k *= c1;
    //     k = rotate_left_32bit(k, r1);  // Rotate k left by r1 bits
    //     k *= c2;

    //     hash ^= k;
    //     hash = rotate_left_32bit(hash, r2);
    //     hash = hash * m + n;
    // }

    // // Handle remaining bytes
    // const uint8_t *tail = (const uint8_t*)(key.data() + nblocks * 4);
    // uint32_t k1 = 0;

    // switch (key.size() & 3) {
    // case 3: k1 ^= tail[2] << 16;
    // case 2: k1 ^= tail[1] << 8;
    // case 1: k1 ^= tail[0];
    //     k1 *= c1;
    //     k1 = rotate_left_32bit(k1, r1);
    //     k1 *= c2;
    //     hash ^= k1;
    // }

    // // Finalization, ensure bytes are well-mixed
    // hash ^= key.size();
    // hash ^= (hash >> 16);
    // hash *= 0x85ebca6b;
    // hash ^= (hash >> 13);
    // hash *= 0xc2b2ae35;
    // hash ^= (hash >> 16);


    // return hash;
    uint32_t hash = 2166136261u;           // FNV offset basis
    for (unsigned char c : key) {
        hash ^= c;                         // XOR with byte
        hash *= 16777619u;                 // multiply by FNV prime
    }
    return hash % LIST_LENGTH;
}




#endif