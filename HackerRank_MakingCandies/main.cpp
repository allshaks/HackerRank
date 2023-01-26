#include <iostream>
#include <fstream>
#include <numeric>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;

typedef unsigned long long ull;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

/*
 * Complete the 'minimumPasses' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. LONG_INTEGER m
 *  2. LONG_INTEGER w
 *  3. LONG_INTEGER p
 *  4. LONG_INTEGER n
 */

ull minimumPasses(ull m, ull w, ull p, ull n) {
    ull c = 0; //candy
    ull passes = 0;

    if (m < w) swap(m, w);

    ull T, T2;
    ull passes_to_gain;
    ull new_passes = 0;
    ull m_buying = 0, w_buying[2] = { 0 };

    while (c < n) {
        m_buying = 0;
        w_buying[0] = 0, w_buying[1] = 0;
        T = trunc((double)c / p);
        T2 = T;
        if (m != w)
            w_buying[0] = (T <= m - w ? T : m - w);

        T2 = T - w_buying[0];
        w_buying[1] = (T2 - (T2 & 1)) / 2;
        m_buying = w_buying[1] + (T2 & 1);

        if (T == 0) {
            if (log10(n - c) < log10(m) + log10(w))
                return passes + 1;
            else
                new_passes = min(ceil(static_cast<double>(p - c) / (m * w)), ceil(static_cast<double>(n - c) / (m * w)));
        }
        else {
            passes_to_gain = ceil(static_cast<double>(p) * (w_buying[0] + 2 * w_buying[1] + (T2 & 1)) / (w_buying[0] * m + w_buying[1] * (2 * m + w_buying[1]) + (T2 & 1) * (m + w_buying[1])));
            if (passes_to_gain > 1 && c + m * w * (passes_to_gain - 1) >= n) {
                new_passes = ceil(static_cast<double>(n - c) / (m * w));
                w_buying[0] = 0;
                w_buying[1] = 0;
                m_buying = 0;
            }
        }

        m += m_buying;
        w += w_buying[0] + w_buying[1];
        passes += new_passes;
        c += new_passes * m * w - (m_buying + w_buying[0] + w_buying[1]) * p;
        new_passes = 0;
    }
    return passes + new_passes;
}

int main()
{
    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    ull m = stol(first_multiple_input[0]);

    ull w = stol(first_multiple_input[1]);

    ull p = stol(first_multiple_input[2]);

    ull n = stol(first_multiple_input[3]);

    ull result = minimumPasses(m, w, p, n);

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