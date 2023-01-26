#include <iostream>
#include <fstream>
#include <numeric>
#include <string>
#include <vector>
#include <set>
#include <functional>
#include <algorithm>

using namespace std;

string ltrim(const string&);
string rtrim(const string&);

/*
 * Complete the 'weightedUniformStrings' function below.
 *
 * The function is expected to return a STRING_ARRAY.
 * The function accepts following parameters:
 *  1. STRING s
 *  2. INTEGER_ARRAY queries
 */

vector<string> weightedUniformStrings(string s, vector<int> queries) {
    set<int> U;
    char prev = '0';
    int count = 0;
    vector<string> ret;

    for (const char& c : s) {
        count = (c == prev ? count : 0) + (c - 'a' + 1);
        prev = c;
        U.insert(count);
    }

    for (const int& q : queries) {
        if (U.find(q) != U.end()) ret.push_back("Yes");
        else ret.push_back("No");
    }

    return ret;
}

int main()
{
    string s;
    getline(cin, s);

    string queries_count_temp;
    getline(cin, queries_count_temp);

    int queries_count = stoi(ltrim(rtrim(queries_count_temp)));

    vector<int> queries(queries_count);

    for (int i = 0; i < queries_count; i++) {
        string queries_item_temp;
        getline(cin, queries_item_temp);

        int queries_item = stoi(ltrim(rtrim(queries_item_temp)));

        queries[i] = queries_item;
    }

    vector<string> result = weightedUniformStrings(s, queries);

    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i];

        if (i != result.size() - 1) {
            cout << "\n";
        }
    }

    cout << "\n";

    return 0;
}

string ltrim(const string& str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string& str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}
