#include <iostream>
#include <fstream>
#include <numeric>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>

using namespace std;

string ltrim(const string&);
string rtrim(const string&);

/*
 * Complete the 'alternate' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING s as parameter.
 */

int alternate(string s) {
    int count = 0;
    vector<int> pairs[26][26];

    for (const char& c : s) {
        int i = c - 'a';
        for (int j = 0; j < 26; j++) {
            if (i == j) continue;
            auto& pair = pairs[min(i, j)][max(i, j)];
            if (pair.empty() || pair.back() == j)
                pair.push_back(i);
            else if (pair.back() == i)
                pair.push_back(-1);
        }
    }

    for (int i = 0; i < 25; i++) {
        for (int j = i + 1; j < 26; j++) {
            if (!pairs[i][j].empty() && pairs[i][j].back() != -1)
                count = max(count, (int)pairs[i][j].size());
        }
    }

    return (count > 1 ? count : 0);
}

int main()
{
    string l_temp;
    getline(cin, l_temp);

    int l = stoi(ltrim(rtrim(l_temp)));

    string s;
    getline(cin, s);

    int result = alternate(s);

    cout << result << "\n";

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