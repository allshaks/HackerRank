#include <iostream>
#include <fstream>
#include <numeric>
#include <string>
#include <vector>
#include <queue>
#include <bitset>
#include <functional>

using namespace std;

string ltrim(const string&);
string rtrim(const string&);

string dict = "abcdefghijklmnopqrstuvwxyz";

/*
 * Complete the 'biggerIsGreater' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING w as parameter.
 */

string quicksort(string s) {
    if (s.size() <= 1)
        return s;
    char pivot = s.back();
    char high_tmp;
    string::iterator high = s.begin();
    queue<string::iterator> highest;
    for (string::iterator low = s.begin(); low != (s.end() - 1); ++low) {
        if (*high < pivot) {
            high++;
        }
        else if (*low > pivot) {
            if (high != low)
                highest.push(low);
            continue;
        }
        else {
            high_tmp = *high;
            *high = *low;
            *low = high_tmp;

            if (highest.empty())
                high = low;
            else {
                highest.push(low);
                high = highest.front();
                highest.pop();
            }
        }
    }

    high_tmp = *high;
    *high = pivot;
    *(s.end()-1) = high_tmp;
    
    if (high != s.begin())
        s.replace(s.begin(), high, quicksort(string(s.begin(), high)));
    if (high != s.end())
        s.replace(high + 1, s.end(), quicksort(string(high + 1, s.end())));

    return s;
}

string biggerIsGreater(string w) {

    int8_t swap_index_1;
    int8_t swap_index_2;

    for (string::reverse_iterator rit = w.rbegin(); rit != w.rend(); ++rit) {
        char curchar = *rit;
        string dict_bigger = dict.substr(curchar-'a'+1, string::npos);
        string s(w.rbegin(),rit);
        swap_index_1 = s.find_first_of(dict_bigger);
        
        if (swap_index_1 != string::npos) {
            swap_index_2 = w.rend() - 1 - rit;
            swap_index_1 = w.size() - 1 - swap_index_1;
            *rit = w[swap_index_1];
            w[swap_index_1] = curchar;
            break;
        }
    }

    if (swap_index_1 == string::npos)
        return "no answer";
    
    w.replace(swap_index_2 + 1, string::npos, quicksort(w.substr(swap_index_2 + 1, string::npos)));
    return w;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string T_temp;
    getline(cin, T_temp);

    int T = stoi(ltrim(rtrim(T_temp)));

    for (int T_itr = 0; T_itr < T; T_itr++) {
        string w;
        getline(cin, w);

        string result = biggerIsGreater(w);
        cout << result << "\n";
        //fout << result << "\n";
    }

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