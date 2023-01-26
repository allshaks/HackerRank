#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <functional>

using namespace std;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

/*
 * Complete the 'almostSorted' function below.
 *
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

void almostSorted(vector<int> arr) {
    bool inc;
    string out_str = "yes\n";
    int dec_count = 0;
    int first, last;
    bool swap = true;
    bool gap = false;

    for (vector<int>::iterator it = arr.begin() + 1; it != arr.end(); ++it) {
        inc = *it > *(it - 1);
        if (!inc) {
            if (gap) {
                cout << "no";
                return;
            }
            dec_count++;
            if (dec_count == 1)
                first = it - arr.begin() - 1;
            else if (dec_count > 2) {
                if (swap)
                    swap = false;
                last = it - arr.begin() - 1;
            }
        }
        else if (dec_count >= 2 && !gap) {
            gap = true;
            last = it - arr.begin() - 1;
        }
    }
    if (swap) {
        if (dec_count == 1)
            last = first + 1;
        int tmp_first = arr[first];
        arr[first] = arr[last];
        arr[last] = tmp_first;
        out_str += "swap ";
    }
    else {
        int f = first, l = last;
        while (l - f > 1) {
            int tmp_f = arr[f];
            arr[f] = arr[l];
            arr[l] = tmp_f;
            f++;
            l--;
        }
        out_str += "reverse ";
    }
    if (arr[first + 1] - arr[first] > 0) {
        if (!first || arr[first] - arr[first - 1] > 0) {
            if (arr[last] - arr[last - 1] > 0) {
                if ((last == (arr.size() - 1)) || arr[last + 1] - arr[last] > 0) {
                    out_str += to_string(first + 1);
                    out_str += " ";
                    out_str += to_string(last + 1);
                    cout << out_str;
                    return;
                }
            }
        }
    }
    cout << "no";
    return;
}

int main()
{
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split(rtrim(arr_temp_temp));

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    almostSorted(arr);

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
