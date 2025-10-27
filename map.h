#include <string>
#include <vector>
#include <utility>
using std::string, std::vector, std::pair;


class Map {
private:
    vector<vector<pair<string, int> > > frequency_list;
    int hash_fun(string token);

public:
    Map(int word_count);
    Map(int word_count, string token);
    Map(vector<string> token_list);
    void put_token(string token);
    int get_frequency(string token);
};