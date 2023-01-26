#include <iostream>
#include <fstream>
#include <numeric>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <bitset>

typedef unsigned long long ull;

using namespace std;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

/*
 * Complete the 'gridlandMetro' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER m
 *  3. INTEGER k
 *  4. 2D_INTEGER_ARRAY track
 */

ull gridlandMetro(int n, int m, int k, vector<vector<int>> track) {
    ull lamps = static_cast<ull>(m) * n;
    map<int, vector<pair<int, int>>> tracks;

    for (const auto& t : track) {
        bool overlap_left = false, overlap_right = false, contained = false;
        int r = t[0] - 1, c1 = t[1] - 1, c2 = t[2]- 1;

        if (tracks.find(r) == tracks.end())
            tracks[r] = vector<pair<int, int>>();

        auto left_side = tracks[r].begin();
        auto right_side = tracks[r].begin();

        for (auto ptr_track = tracks[r].begin(); ptr_track != tracks[r].end(); ++ptr_track) {
            if (ptr_track->second < c1) {
                left_side = ptr_track + 1;
                right_side = ptr_track + 1;
            }
            else if (ptr_track->first <= c1 && c1 <= ptr_track->second && ptr_track->second < c2) {
                left_side = ptr_track;
                right_side = ptr_track + 1;
                overlap_left = true;
            }
            else if (c1 <= ptr_track->first && ptr_track->second <= c2) {
                if (!overlap_left) {
                    left_side = ptr_track;
                    overlap_left = true;
                }
                right_side = ptr_track + 1;
            }
            else if (ptr_track->first <= c2 && c2 <= ptr_track->second && c1 < ptr_track->first) {
                right_side = ptr_track + 1;
                overlap_right = true;
            }
            else if (c2 < ptr_track->first)
                break;
            else if (ptr_track->first <= c1 && c2 <= ptr_track->second) {
                contained = true;
                break;
            }
        }

        if (contained) continue;

        int leftmost_c = overlap_left ? min(c1,left_side->first) : c1;
        int rightmost_c = overlap_right ? (right_side - 1)->second : c2;

        if (overlap_left || overlap_right) right_side = tracks[r].erase(left_side, right_side);
        tracks[r].insert(right_side, make_pair(leftmost_c, rightmost_c));
    }

    for (const auto& row : tracks) {
        for (const auto& t : row.second)
            lamps -= (static_cast<ull>(t.second) - t.first + 1);
    }

    return lamps;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    ifstream fin("input.txt");

    /*string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);
    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));
    int n = stoi(first_multiple_input[0]);
    int m = stoi(first_multiple_input[1]);
    int k = stoi(first_multiple_input[2]);*/

    int n, m, k;
    fin >> n;
    fin >> m;
    fin >> k;

    vector<vector<int>> track(k);

    for (int i = 0; i < k; i++) {
        track[i].resize(3);

        /*string track_row_temp_temp;
        getline(cin, track_row_temp_temp);

        vector<string> track_row_temp = split(rtrim(track_row_temp_temp));*/

        for (int j = 0; j < 3; j++) {
            /*int track_row_item = stoi(track_row_temp[j]);
            track[i][j] = track_row_item;*/

            fin >> track[i][j];
        }
    }

    ull result = gridlandMetro(n, m, k, track);

    cout << result << "\n";

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

vector<string> split(const string& str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}