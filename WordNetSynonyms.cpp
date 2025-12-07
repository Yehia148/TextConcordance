//
// Created by Ali on 11/19/2025.
//

#include "WordNetSynonyms.h"
#include <string>
#include <vector>
#include <array>
#include <memory>
#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>


#ifdef _WIN32
    #define POPEN  _popen
    #define PCLOSE _pclose
#else
    #define POPEN  popen
    #define PCLOSE pclose
#endif

// trim the whitespace
static std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

std::vector<std::string> getSynonyms(const std::string& word) {
    /**
     * Fetches synonym data from WordNet and parses it
     * for readability, then returns it as a vector.
     */

    std::vector<std::string> synonyms;
    if (word.empty()) return synonyms;

    std::string urlWord = word;
    for (char &c : urlWord) {
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    std::replace(urlWord.begin(), urlWord.end(), ' ', '+');

    std::string command =
        "curl -s \"http://api.datamuse.com/words?rel_syn=" + urlWord + "\" 2>&1";

    std::array<char, 256> buffer{};
    FILE* pipe = POPEN(command.c_str(), "r");
    if (!pipe) {
        return synonyms;
    }

    std::string json;
    // calling wordnet API
    while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe) != nullptr) {
        json += buffer.data();
    }

    PCLOSE(pipe);

    std::size_t pos = 0;
    while (true) {
        pos = json.find("\"word\"", pos);
        if (pos == std::string::npos) break;

        std::size_t colon = json.find(':', pos);
        if (colon == std::string::npos) break;

        std::size_t q1 = json.find('"', colon + 1);
        if (q1 == std::string::npos) break;

        std::size_t q2 = json.find('"', q1 + 1);
        if (q2 == std::string::npos) break;

        std::string w = json.substr(q1 + 1, q2 - q1 - 1);
        w = trim(w);

        if (!w.empty() &&
            w != word &&
            std::find(synonyms.begin(), synonyms.end(), w) == synonyms.end()) {

            synonyms.push_back(w);
        }

        pos = q2 + 1;
    }

    return synonyms;
}
