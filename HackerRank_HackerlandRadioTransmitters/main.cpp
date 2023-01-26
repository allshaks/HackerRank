#include <iostream>
#include <fstream>
#include <numeric>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <chrono>

using namespace std;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

/*
 * Complete the 'hackerlandRadioTransmitters' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY x
 *  2. INTEGER k
 */

int hackerlandRadioTransmitters(vector<int> x, int k) {
    int antennas = 0;
    bool reset;

    sort(x.begin(), x.end());

    int first = x.front();

    while (true) {
        reset = false;
        for (auto ptr_house = x.begin(); ptr_house != x.end(); ++ptr_house) {
            int dist1 = *ptr_house - first;

            if (dist1 > k) {
                int antenna = *(ptr_house - 1);
                for (auto ptr_antenna_outofreach = ptr_house; ptr_antenna_outofreach != x.end(); ++ptr_antenna_outofreach) {
                    int dist2 = *ptr_antenna_outofreach - antenna;
                    if (dist2 > k) {
                        antennas++;
                        first = *ptr_antenna_outofreach;
                        x.assign(ptr_antenna_outofreach, x.end());
                        reset = true;
                        break;
                    }
                }
                if (reset) break;
                else return ++antennas;
            }
            if (reset) break;
        }
        if (!reset)
            return ++antennas;
    }
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));
    ifstream fin("input.txt");

    string first_multiple_input_temp;
    
   /* getline(cin, first_multiple_input_temp);
    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));
    int n = stoi(first_multiple_input[0]);
    int k = stoi(first_multiple_input[1]);*/

    int n, k;
    fin >> n;
    fin >> k;

    string x_temp_temp;

    /*getline(cin, x_temp_temp);
    vector<string> x_temp = split(rtrim(x_temp_temp));*/

    vector<int> x(n);

    for (int i = 0; i < n; i++) {
        /*int x_item = stoi(x_temp[i]);

        x[i] = x_item;*/
        fin >> x[i];
    }

    int result = hackerlandRadioTransmitters(x, k);

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