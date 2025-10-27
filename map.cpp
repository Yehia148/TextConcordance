#ifndef MAP.H
#define MAP.H

#include "map.h"


Map::Map(int word_count) {
    frequency_list.assign(word_count, {});
}


Map::Map(int word_count, string token) {
    frequency_list.assign(word_count, {});
    put_token(token);
}


Map::Map(vector<string> token_list) {
    frequency_list.assign(token_list.size(), {});
    for(string token : token_list) {
        put_token(token);
    }
}


void Map::put_token(string token) {
    unsigned int hash = hash_fun(token);
    if (frequency_list[hash].empty()) {
        pair<string, int> temp(token, 1);
        frequency_list[hash].push_back(temp);
    } else {
        for (int i=0; i<frequency_list[hash].size(); ++i) {
            pair<string, int>* p = &frequency_list[hash][i];
            bool added = false;
            if (p->first == token) {
                ++p->second;
                added = true;
                break;
            }
            if (!added) {
                pair<string, int> temp(token, 1);
                frequency_list[hash].push_back(temp);
            }
        }
    }
}


int Map::get_frequency(string token) {
    int hash = hash_fun(token);

    if (frequency_list[hash].empty()) {
        return 0;
    } else {
        for (auto p : frequency_list[hash]) {
            if (p.first == token) return p.second;
        }
    }

    return 0;
}


#endif