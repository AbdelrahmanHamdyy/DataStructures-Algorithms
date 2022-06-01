#include <unordered_map> 
#include <algorithm>
#include <utility>
#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
using namespace std;

// Helper function
void preprocess(string& str) {
    // Removing punctuation
    for (int i = 0, len = str.size(); i < len; i++)
    {
        // Check whether parsing character is punctuation or not 
        if (ispunct(str[i]))
        {
            str.erase(i--, 1);
            len = str.size();
        }
    }

    // Converting to lower case
    transform(str.begin(), str.end(), str.begin(), ::tolower);
}

// Helper function
vector<string> readFile() {
    ifstream f("two-cities.txt"); //taking file as inputstream

    string file;

    if (f) {
        ostringstream ss;
        ss << f.rdbuf(); // reading data
        file = ss.str();

        // Removes punctuation and converts to lower case
        preprocess(file);

        // Split into tokens on space
        istringstream iss(file);
        vector<string> tokens{ istream_iterator<string>{iss},
                          istream_iterator<string>{} };

        return tokens;
    }

    vector<string> empty;
    return empty;
}

// TODO: IMPLEMENT THIS FUNCTION
string findSecret(vector<string> tokens) {
    // Hint: you can use std::unordered_map and std::sort
    // unordered_map<string, int>
    unordered_map<string, int> mp;
    string result;
    vector<int> req = { 11, 23, 22, 43, 3, 47 };
    for (string s : tokens)
    {
        mp[s]++;
    }
    vector<pair<int, string>> v;
    for (auto it = mp.begin(); it != mp.end(); it++)
    {
        v.push_back({ it->second, it->first });
    }
    sort(v.begin(), v.end(), greater<>());
    for (int i = 0; i < req.size(); i++)
        result += v[req[i] - 1].second + " ";
    return result;
}

int main() {

    vector<string> tokens = readFile();

    cout << findSecret(tokens) << endl;

    return 0;
}
