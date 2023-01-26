#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

/*
 * Complete the 'surfaceArea' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts 2D_INTEGER_ARRAY A as parameter.
 */

int surfaceArea(vector<vector<int>> A) {
    int result = 0;
    result += 2*A.size()*A[0].size();

    result += 2*A.front().front() + A.front().back();
    result += accumulate(A.back().begin(), A.back().end(), 0);
    for (vector<int>::iterator col = A.front().begin() + 1; col != A.front().end(); ++col)
        result += (*col + abs((*col) - *(col - 1)));

    for (vector<vector<int>>::iterator row = A.begin() + 1; row != A.end(); ++row) {
        result += row->front() + row->back();
        result += abs(row->front() - (row - 1)->front());
        for (vector<int>::iterator col = row->begin() + 1; col != row->end(); ++col) {
            int index = abs(col - row->begin());
            result += abs(*col - *(col - 1));
            result += abs(*col - (*(row - 1))[index]);
        }
    }

    return result;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int H = stoi(first_multiple_input[0]);

    int W = stoi(first_multiple_input[1]);

    vector<vector<int>> A(H);

    for (int i = 0; i < H; i++) {
        A[i].resize(W);

        string A_row_temp_temp;
        getline(cin, A_row_temp_temp);

        vector<string> A_row_temp = split(rtrim(A_row_temp_temp));

        for (int j = 0; j < W; j++) {
            int A_row_item = stoi(A_row_temp[j]);

            A[i][j] = A_row_item;
        }
    }

    int result = surfaceArea(A);

    cout << result << endl;

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