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
 * Complete the 'absolutePermutation' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER k
 */

vector<int> absolutePermutation(int n, int k) {
    vector<int> result;
    for (int i = 1; i <= n; i++)
        result.push_back(i);
    if (k == 0)
        return result;
    if (n % 2 != 0 || n % k != 0 || ((int)(n/k) % 2 != 0))
        return { -1 };

    int blocks = (n / k) / 2;
    
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < blocks; j++) {
            int tmp = result[i + j * 2 * k];
            result[i + j * 2 * k] = result[i + k + j * 2 * k];
            result[i + k + j * 2 * k] = tmp;
        }
    }
    return result;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int n = stoi(first_multiple_input[0]);

        int k = stoi(first_multiple_input[1]);

        vector<int> result = absolutePermutation(n, k);

        for (size_t i = 0; i < result.size(); i++) {
            //fout << result[i];
            cout << result[i];

            if (i != result.size() - 1) {
                cout << " ";
                //fout << " ";
            }
        }

        cout << "\n";
        //fout << "\n";
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