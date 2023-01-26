#include <iostream>
#include <sstream>
#include <numeric>
#include <string>
#include <vector>
#include <bitset>
#include <functional>

using namespace std;

string ltrim(const string&);
string rtrim(const string&);

/*
 * Complete the 'extraLongFactorials' function below.
 *
 * The function accepts INTEGER n as parameter.
 */

bool Is0(char c) {
    return (c == '0');
}

vector<int> dec_to_vec (int n) {
    vector<int> numbers;
    while (n > 0) {
       numbers.push_back(n % 10);
       n /= 10;
    }
    return numbers;
}

void extraLongFactorials(int n) {

    vector<int> f;
    f.push_back(1);

    if (n > 100 || n < 0) {
        cout << "El número debe estar entre 0 y 100" << endl;
        return;
    }

    for (int i = 1; i <= n; i++) {
        vector<int> op(f.size()+3,0);
        vector<int> i_digits = dec_to_vec(i);
        for (int j = 0; j < f.size(); j++) {
            if (!f[j]) continue;
            for (int k = 0; k < i_digits.size(); k++) {
                if (!i_digits[k]) continue;
                op[j + k] += f[j]*i_digits[k];
            }
        }
        f = vector<int>(op.size(),0);
        for (vector<int>::iterator it = op.begin(); it != op.end(); ++it) {

            uint8_t digit = (*it) % 10;
            uint8_t carry = (*it - digit) / 10;
            if (it != op.end() - 1)
                *(it + 1) += carry;
            else if (carry != 0) {
                op.push_back(carry);
                f.push_back(0);
            }
            f[it - op.begin()] = digit;
        }
    }
    
    ostringstream oss;

    for (vector<int>::reverse_iterator it = f.rbegin(); it != f.rend(); ++it) {
        oss << *it;
    }

    string f_str = oss.str();

    f_str.erase(0,f_str.find_first_not_of("0"));

    cout << f_str;

    return;
}

int main()
{
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    extraLongFactorials(n);

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