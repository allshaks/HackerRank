#include <iostream>
#include <fstream>
#include <sstream>
#include <numeric>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

#include <chrono>

using namespace std;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

/*
 * Complete the 'activityNotifications' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY expenditure
 *  2. INTEGER d
 */

int activityNotifications(vector<int> expenditure, int d) {
    bool odd = d % 2;
    int notifs = 0;

    int avg_time = 0;

    auto start = chrono::high_resolution_clock::now();
    vector<int> buffer(d);

    copy(expenditure.begin(), expenditure.begin() + d, buffer.begin());

    sort(buffer.begin(), buffer.end());

    for (vector<int>::iterator it = expenditure.begin() + d; it != expenditure.end(); ++it) {
        int twicemedian;
        int i = it - expenditure.begin() - d;

        if (odd)
            twicemedian = 2*buffer[d / 2];
        else
            twicemedian = buffer[d / 2] + buffer[d / 2 - 1];

        if (*it >= twicemedian)
            notifs++;

        if (*it == expenditure[i])
            continue;

        if (expenditure[i] > twicemedian / 2)
            buffer.erase(find(buffer.begin() + (int)(d / 2), buffer.end(), expenditure[i]));
        else
            buffer.erase(find(buffer.begin(), buffer.end() - (int)(d / 2), expenditure[i]));

        if (*it > twicemedian / 2)
            buffer.insert(find_if(buffer.begin() + (int)(d / 2), buffer.end(), [it](int e) {return e >= *it; }), *it);
        else
            buffer.insert(find_if(buffer.begin(), buffer.end() - (int)(d / 2), [it](int e) {return e >= *it; }), *it);
    }

    return notifs;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));
    stringstream buff;
    ifstream f1("input1.txt");
    ifstream f2("input2.txt");
    buff << f1.rdbuf();

    string first_multiple_input_temp = buff.str();
    buff.str(string());
    //getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int d = stoi(first_multiple_input[1]);

    buff << f2.rdbuf();
    string expenditure_temp_temp = buff.str();
    //getline(cin, expenditure_temp_temp);

    vector<string> expenditure_temp = split(rtrim(expenditure_temp_temp));

    vector<int> expenditure(n);

    for (int i = 0; i < n; i++) {
        int expenditure_item = stoi(expenditure_temp[i]);

        expenditure[i] = expenditure_item;
    }

    int result = activityNotifications(expenditure, d);

    cout << result << "\n";
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