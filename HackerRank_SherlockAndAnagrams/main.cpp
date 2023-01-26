#include <iostream>
#include <fstream>
#include <numeric>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

string ltrim(const string&);
string rtrim(const string&);

/*
 * Complete the 'sherlockAndAnagrams' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING s as parameter.
 */

int sherlockAndAnagrams(string s) {
    int count = 0;
    int s_size = s.size();
    vector<vector<vector<int>>> substr_map;
    substr_map = vector<vector<vector<int>>>(s_size - 1, vector<vector<int>>());

    for (int i = 0; i < s_size - 1; i++) {
        for (int j = 0; j < s_size - i; j++) {
            vector<vector<int>> prev_substr_map = substr_map[i];
            substr_map[i].push_back(vector<int>(26, 0));
            string ss = s.substr(j, i + 1);
            for (char& c : ss)
                substr_map[i][j][c - 'a']++;
            for (auto& sub : prev_substr_map) {
                if (equal(sub.begin(), sub.end(), substr_map[i][j].begin()))
                    count++;
            }
        }
    }

    return count;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string s;
        getline(cin, s);

        int result = sherlockAndAnagrams(s);

        cout << result << "\n";
    }

    //fout.close();

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