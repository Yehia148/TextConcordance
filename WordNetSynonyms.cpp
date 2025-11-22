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


// path to wordnet
static const std::string WN_BIN_PATH =
    "C:/Program Files (x86)/WordNet/2.1/bin";

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

    // make WordNet find the dict folder
    _putenv("WNHOME=C:\\Program Files (x86)\\WordNet\\2.1");

    std::vector<std::string> synonyms;

    std::string command =
        "\"" + WN_BIN_PATH + "/wn.exe\" " + word + " -synsn 2>&1";

    std::array<char, 256> buffer{};

    FILE* pipe = POPEN(command.c_str(), "r");
    if (!pipe) {
        return synonyms;
    }

    while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe) != nullptr) {
        std::string line = buffer.data();
        line = trim(line);

        if (line.empty()) continue;


        if (!line.empty() &&
            std::isdigit(static_cast<unsigned char>(line[0])) &&
            line.find("sense") != std::string::npos)
        {
            continue;  // skip sense count lines
        }

        // Skip headers
        if (line.rfind("Synonyms/Hypernyms", 0) == 0) continue;

        // Skip "Sense 1", "Sense 2", ...
        if (line.rfind("Sense ", 0) == 0) continue;

        // Remove leading "=>"
        if (line.rfind("=>", 0) == 0) {
            line = trim(line.substr(2));
        }

        // Remove underscores
        std::replace(line.begin(), line.end(), '_', ' ');

        line = trim(line);

        // Skip the queried word itself
        if (line == word) continue;

        if (!line.empty() &&
            std::find(synonyms.begin(), synonyms.end(), line) == synonyms.end()) {

            synonyms.push_back(line);
        }
    }

    PCLOSE(pipe);
    return synonyms;
}
