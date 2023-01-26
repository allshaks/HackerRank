#include <iostream>
#include <cmath>
#include <numeric>
#include <string>
#include <vector>
#include <functional>

using namespace std;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

/*
 * Complete the 'queensAttack' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER k
 *  3. INTEGER r_q
 *  4. INTEGER c_q
 *  5. 2D_INTEGER_ARRAY obstacles
 */

int queensAttack(int n, int k, int r_q, int c_q, vector<vector<int>> obstacles) {
    int pd_q = r_q - c_q;
    int nd_q = r_q + c_q;

    int l = c_q - 1,
        b = r_q - 1,
        r = n - c_q,
        t = n - r_q,
        bl = (b < l ? b : l),
        br = (b < r ? b : r),
        tr = (t < r ? t : r),
        tl = (t < l ? t : l);

    for (vector<vector<int>>::iterator obs = obstacles.begin(); obs != obstacles.end(); ++obs) {
        int r_o = (*obs)[0];
        int c_o = (*obs)[1];
        int pd_o = r_o - c_o;
        int nd_o = r_o + c_o;

        int r_dif = r_o - r_q;
        int c_dif = c_o - c_q;
        int pd_dif = pd_o - pd_q;
        int nd_dif = nd_o - nd_q;

        if (r_dif == 0) {
            if (c_dif > 0 && c_dif <= r)
                r = c_dif - 1;
            else if (c_dif < 0 && c_dif >= -l)
                l = - c_dif - 1;
        }
        else if (c_dif == 0) {
            if (r_dif > 0 && r_dif <= t)
                t = r_dif - 1;
            else if (r_dif < 0 && r_dif >= -b)
                b = -r_dif - 1;
        }
        else if (pd_dif == 0) {
            if (nd_dif > 0 && (int)(nd_dif/2) <= tr)
                tr = (int)(nd_dif / 2) - 1;
            else if (nd_dif < 0 && (int)(nd_dif / 2) >= -bl)
                bl = -(int)(nd_dif / 2) - 1;
        }
        else if (nd_dif == 0) {
            if (pd_dif > 0 && (int)(pd_dif / 2) <= tl)
                tl = (int)(pd_dif / 2) - 1;
            else if (pd_dif < 0 && (int)(pd_dif / 2) >= -br)
                br = -(int)(pd_dif / 2) - 1;
        }
    }

    return r+l+t+b+br+bl+tr+tl;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int k = stoi(first_multiple_input[1]);

    string second_multiple_input_temp;
    getline(cin, second_multiple_input_temp);

    vector<string> second_multiple_input = split(rtrim(second_multiple_input_temp));

    int r_q = stoi(second_multiple_input[0]);

    int c_q = stoi(second_multiple_input[1]);

    vector<vector<int>> obstacles(k);

    for (int i = 0; i < k; i++) {
        obstacles[i].resize(2);

        string obstacles_row_temp_temp;
        getline(cin, obstacles_row_temp_temp);

        vector<string> obstacles_row_temp = split(rtrim(obstacles_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int obstacles_row_item = stoi(obstacles_row_temp[j]);

            obstacles[i][j] = obstacles_row_item;
        }
    }

    int result = queensAttack(n, k, r_q, c_q, obstacles);

    //fout << result << "\n";

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