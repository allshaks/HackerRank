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
 * Complete the 'matrixRotation' function below.
 *
 * The function accepts following parameters:
 *  1. 2D_INTEGER_ARRAY matrix
 *  2. INTEGER r
 */

vector<int> roll(vector<int> v, int r) {
    int s = v.size();
    vector<int> v_rolled = v;
    for (int i = 0; i < s; i++) {
        int j = (i + r) % s;
        v_rolled[j] = v[i];
    }
    return v_rolled;
}

void matrixRotation(vector<vector<int>> matrix, int r) {
    int cols = matrix[0].size();
    int rows = matrix.size();
    int layers = (rows < cols ? rows : cols)/2;
    vector<vector<int>> layer_matrix(layers, vector<int>());
    vector<vector<int>> rotated_matrix(rows, vector<int>(cols,0));

    for (int l = 0; l < layers; l++) {
        for (int i = l; i < rows - l; i++) {
            layer_matrix[l].push_back(matrix[i][l]);
        }
        for (int i = l+1; i < cols - l; i++) {
            layer_matrix[l].push_back(matrix[rows-l-1][i]);
        }
        for (int i = l+1; i < rows - l; i++) {
            layer_matrix[l].push_back(matrix[rows-i-1][cols-l-1]);
        }
        for (int i = l+1; i < cols - l - 1; i++) {
            layer_matrix[l].push_back(matrix[l][cols-i-1]);
        }
        layer_matrix[l] = roll(layer_matrix[l], r);
    }

    for (int l = 0; l < layers; l++) {
        int e = 0;
        for (int i = l; i < rows - l; i++) {
            rotated_matrix[i][l] = layer_matrix[l][e];
            e++;
        }
        for (int i = l + 1; i < cols - l; i++) {
            rotated_matrix[rows - l - 1][i] = layer_matrix[l][e];
            e++;
        }
        for (int i = l + 1; i < rows - l; i++) {
            rotated_matrix[rows - i - 1][cols - l - 1] = layer_matrix[l][e];
            e++;
        }
        for (int i = l + 1; i < cols - l - 1; i++) {
            rotated_matrix[l][cols - i - 1] = layer_matrix[l][e];
            e++;
        }
    }

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            cout << rotated_matrix[row][col];
            if (col != cols - 1)
                cout << " ";
        }
        if (row != rows - 1)
            cout << "\n";
    }

    return;
}

int main()
{
    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int m = stoi(first_multiple_input[0]);

    int n = stoi(first_multiple_input[1]);

    int r = stoi(first_multiple_input[2]);

    vector<vector<int>> matrix(m);

    for (int i = 0; i < m; i++) {
        matrix[i].resize(n);

        string matrix_row_temp_temp;
        getline(cin, matrix_row_temp_temp);

        vector<string> matrix_row_temp = split(rtrim(matrix_row_temp_temp));

        for (int j = 0; j < n; j++) {
            int matrix_row_item = stoi(matrix_row_temp[j]);

            matrix[i][j] = matrix_row_item;
        }
    }

    matrixRotation(matrix, r);

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