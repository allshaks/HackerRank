#include <iostream>
#include <fstream>
#include <sstream>
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
 * Complete the 'highestValuePalindrome' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. STRING s
 *  2. INTEGER n
 *  3. INTEGER k
 */

string highestValuePalindrome(string s, int n, int k) {

    vector<int> p;

    for (int i = 0; i < n / 2; i++) {
        if (s[i] != s[n - i - 1])
            p.push_back(i);
    }
    if (p.size() > k)
        return "-1";

    bool can_be_odd = 1;
    while (k != p.size()) {
        bool odd = (k - p.size()) % 2;
        if (odd && can_be_odd) {
            for (vector<int>::iterator it = p.begin(); it != p.end(); ++it) {
                if (s[*it] != '9' && s[n - *it - 1] != '9') {
                    s[*it] = '9';
                    s[n - *it - 1] = '9';
                    k-=2;
                    p.erase(it);
                    break;
                }
            }
            can_be_odd = false;
        }
        else {
            can_be_odd = false;
            int extra_pairs = (k - p.size()) / 2;
            if (!extra_pairs)
                break;
            vector<int>::iterator p_it = p.begin();
            for (int i = 0; i < (n + 1) / 2; i++) {
                bool is_pal = false;
                if (!p.empty() &&  i == *p_it) {
                    p_it++;
                    is_pal = true;
                }
                if (s[i] != '9' && s[n - i - 1] != '9') {
                    s[i] = '9';
                    s[n - i - 1] = '9';
                    k -= (1 + (i != (n - 1) / 2));
                    if (is_pal) {
                        p_it--;
                        p_it = p.erase(p_it);
                        can_be_odd = !can_be_odd;
                    }
                    if (!can_be_odd)
                        extra_pairs = (k - p.size()) / 2;;
                    if (!extra_pairs)
                        break;
                }
            }
            if (!can_be_odd)
                break;
        }
    }

    for (vector<int>::iterator it = p.begin(); it != p.end(); ++it) {
        if (s[*it] > s[n - *it - 1])
            s[n - *it - 1] = s[*it];
        else if (s[*it] < s[n - *it - 1])
            s[*it] = s[n - *it - 1];
        k--;
    }

    if (k > 0 && s.size() % 2 && s[n / 2] != '9')
        s[n / 2] = '9';

    return s;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    stringstream buff;
    ifstream f1("input1.txt");
    ifstream f2("input2.txt");
    buff << f1.rdbuf();

    string first_multiple_input_temp;// = buff.str();
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int k = stoi(first_multiple_input[1]);

    buff.str(string());
    buff << f2.rdbuf();
    string s;// = buff.str();
    getline(cin, s);

    string result = highestValuePalindrome(s, n, k);

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