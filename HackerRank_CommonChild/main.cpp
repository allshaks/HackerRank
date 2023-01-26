#include <iostream>
#include <fstream>
#include <numeric>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>

using namespace std;

//int commonChild(string s1, string s2) {
//    int len1 = s1.length(), len2 = s2.length();
//    int max_len = max(len1, len2);
//    vector<int> options;
//    for (int i = 1; i <= max_len; i++) {
//        for (int j = 1; j <= i; j++) {
//            if (i <= len1 && j <= len2 && s1[len1 - i] == s2[len2 - j])
//                options.push_back(commonChild(s1.substr(0, len1 - i), s2.substr(0, len2 - j)) + 1);
//            if (i <= len2 && j <= len1 && i != j && s1[len1 - j] == s2[len2 - i])
//                options.push_back(commonChild(s1.substr(0, len1 - j), s2.substr(0, len2 - i)) + 1);
//        }
//        if (!options.empty()) break;
//    }
//    if (options.empty())
//        return 0;
//    else
//        return *max_element(options.begin(), options.end());
//}

//int commonChild(string s1, string s2) {
//    vector<int> instances[26];
//    int len = s1.length();
//    cout << len << endl;
//    int longest = 0;
//
//    vector<vector<pair<int, int>>> depth_corners(1, { make_pair(-1,-1) });
//
//    for (int i = 0; i < len; i++)
//        instances[s1[i] - 'A'].push_back(i);
//
//    for (int i = 0; i < len; i++) {
//        char c = s2[i];
//
//        for (auto ptr_inst = instances[c - 'A'].begin(); ptr_inst != instances[c - 'A'].end(); ++ptr_inst) {
//            for (auto ptr_depth = depth_corners.rbegin(); ptr_depth != depth_corners.rend(); ++ptr_depth) {
//                /*int max_possible_len_dif = len - (ptr_depth - depth_corners.rbegin()) - max(i, *ptr_inst);
//                if (max_possible_len_dif <= 0)
//                    break;*/
//                bool found = false;
//                for (auto& corner : *ptr_depth) {
//                    if (i > corner.first && *ptr_inst > corner.second) {
//                        found = true;
//                        if (ptr_depth == depth_corners.rbegin()) depth_corners.push_back({ make_pair(i, *ptr_inst) });
//                        else (ptr_depth - 1)->push_back(make_pair(i, *ptr_inst));
//                        break;
//                    }
//                }
//                if (found) break;
//            }
//        }
//        if (!(i % 100)) {
//            cout << i << endl;
//            cout << depth_corners.size() - 1 << endl;
//        }
//    }
//    return depth_corners.size() - 1;
//}


// Para hacerlo miré la página de Wikipedia de Longest Common Subsequence.
int commonChild(string s1, string s2) {
    int len = s1.length();
    vector<vector<int>> depth(len + 1, vector<int>(len + 1, 0));

    for (int i = 1; i <= len;  i++) {
        for (int j = 1; j <= len; j++) {
            if (s1[i - 1] == s2[j - 1]) depth[i][j] = depth[i - 1][j - 1] + 1;
            else depth[i][j] = max(depth[i - 1][j], depth[i][j - 1]);
        }
    }
    return depth[len][len];
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    ifstream fin("input.txt");

    string s1;
    //fin >> s1;
    getline(cin, s1);

    string s2;
    //fin >> s2;
    getline(cin, s2);

    int result = commonChild(s1, s2);

    cout << result << "\n";

    //fout.close();

    return 0;
}
