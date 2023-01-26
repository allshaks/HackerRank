#include <iostream>
#include <fstream>
#include <numeric>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <functional>
#include <algorithm>

typedef unsigned long long ull;

using namespace std;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

/*
 * Complete the 'maximumSum' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. LONG_INTEGER_ARRAY a
 *  2. LONG_INTEGER m
 */

long maximumSum(vector<ull> a, long m) {
    int len = a.size();
    long min_dif;

    vector<long> partial_sum_mod_m(len, 0);
    map<long, int> partial_sum_mod_m_map;
    a[0] %= m;
    partial_sum(a.begin(), a.end(), partial_sum_mod_m.begin(), [&](ull x, ull y) {return (x + y % m) % m; });

    for (int i = 0; i < len; i++)
        partial_sum_mod_m_map[partial_sum_mod_m[i]] = i;

    sort(partial_sum_mod_m.begin(), partial_sum_mod_m.end());

    min_dif = m - partial_sum_mod_m[0];
    for (int i = 1; i < len; i++) {
        min_dif = min(min_dif, m - partial_sum_mod_m[i]);
        int index_dif = partial_sum_mod_m_map[partial_sum_mod_m[i]] - partial_sum_mod_m_map[partial_sum_mod_m[i - 1]];
        long dif = partial_sum_mod_m[i] - partial_sum_mod_m[i-1];
        if (index_dif < 0 && dif)
            min_dif = min(min_dif, dif);
    }

    return m - min_dif;
}

int main()
{

    ifstream fin("input.txt");
    ifstream output("expected_output.txt");

    string q_temp;
    //getline(cin, q_temp);
    fin >> q_temp;

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        /*string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int n = stoi(first_multiple_input[0]);

        long m = stol(first_multiple_input[1]);*/

        int n;
        long m;
        fin >> n;
        fin >> m;

        /*string a_temp_temp;
        getline(cin, a_temp_temp);

        vector<string> a_temp = split(rtrim(a_temp_temp));*/

        vector<ull> a(n);
        for (int i = 0; i < n; i++) {
            /*long a_item = stol(a_temp[i]);

            a[i] = a_item;*/
            fin >> a[i];
        }
        int expected;
        output >> expected;
        long result = maximumSum(a, m);

        cout << result << "\n";

        if (result != expected) {
            cout << "La entrada nro " << q_itr << " no coincide con lo esperado." << endl;
            system("pause");
        }
        
    }

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