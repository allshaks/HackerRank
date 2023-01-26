#include <iostream>
#include <fstream>
#include <numeric>
#include <string>
#include <vector>
#include <set>
#include <functional>
#include <algorithm>

using namespace std;

/*
 * Complete the 'superReducedString' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

string superReducedString(string s) {
    auto it_c = s.begin();
    while (it_c != s.end() && it_c + 1 != s.end()) {
        if (*it_c == *(it_c + 1)) {
            it_c = s.erase(it_c, it_c + 2);
            if (it_c != s.begin())
                it_c--;
        }
        else it_c++;
    }
    if (s.empty())
        return "Empty String";
    else return s;
}

int main()
{
    string s;
    getline(cin, s);

    string result = superReducedString(s);

    cout << result << "\n";

    return 0;
}