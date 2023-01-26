#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>

using namespace std;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

/*
 * Complete the 'lilysHomework' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

int lilysHomework(vector<int> arr) {

    int swaps[] = {0, 0};
    bool sorted;

    int s = arr.size();

    vector<int> arr_copy = arr;
    vector<int> sorted_arr = arr;
    map<int, vector<int>> arr_key;
    sort(sorted_arr.begin(), sorted_arr.end());
    
    for (vector<int>::iterator it = sorted_arr.begin(); it != sorted_arr.end(); ++it) {
        int i = it - sorted_arr.begin();
        arr_key[*it].push_back(i);
        arr_key[*it].push_back(s - i - 1);
    }

    for (int k = 0; k < 2; k++) {
        arr = arr_copy;
        sorted = false;
        while (!sorted) {
            sorted = true;
            for (int i = 0; i < arr.size(); i++) {
                int j = arr_key[arr[i]][k];
                if (i != j) {
                    int tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                    sorted = false;
                    swaps[k]++;
                }
            }
        }
    }

    return (swaps[0] < swaps[1] ? swaps[0] : swaps[1]);
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

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

    int result = lilysHomework(arr);

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