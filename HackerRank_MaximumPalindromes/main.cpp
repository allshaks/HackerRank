#include <iostream>
#include <fstream>
#include <chrono>
#include <numeric>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>

typedef unsigned long long int ullint;
const ullint TOP = 1000000007;

using namespace std;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

/*
 * Complete the 'initialize' function below.
 *
 * The function accepts STRING s as parameter.
 */

vector<map<char, int>> char_maps;

int xEuclidAlgorithm(int a, int b, int& s1, int& t1, int s2 = 0, int t2 = 1) {
    if (b == 0)
        return a;

    int q = a / b;
    int s_temp = s1, t_temp = t1;
    s1 = s2;
    t1 = t2;
    s2 = s_temp - q * s2;
    t2 = t_temp - q * t2;

    return xEuclidAlgorithm(b, a % b, s1, t1, s2, t2);
}

//ullint factorial_modulo_N(int n, int N) {
//    if (n == 1 || n == 0)
//        return 1;
//    return (ullint)(factorial_modulo_N(n - 1, N) * (n % N)) % N;
//}

int modular_multip_inv(int a, int N) {
    int x = 1, y = 0;
    if (xEuclidAlgorithm(a, N, x, y) == 1) {
        while (x < 0)
            x += N;
        return x;
    }
    else return -1;
}

ullint product_modulo_N(ullint a_mod_N, ullint b, ullint N) {
    return (ullint)((a_mod_N * (b % N)) % N);
}
ullint division_modulo_N(ullint a_mod_N, ullint b, ullint N) {
    return (ullint)((a_mod_N * (modular_multip_inv(b, N) % N)) % N);
}

//int xEuclidAlgorithm(int a, int b, int& x, int& y) {
//
//    if (b == 0)
//        return a;
//
//    int r = a % b;
//    int q = a / b;
//    int x_next, y_next, gcd = xEuclidAlgorithm(b, r, x_prev, y_prev);
//
//    
//}

void initialize(string s) {
    // This function is called once before all queries.
    map<char, int> char_map;
    for (char c = 'a'; c <= 'z'; c++)
        char_map[c] = 0;
    char_maps.push_back(char_map);
    for (char& c : s) {
        char_map[c]++;
        char_maps.push_back(char_map);
    }
}

/*
 * Complete the 'answerQuery' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER l
 *  2. INTEGER r
 */

int answerQuery(int l, int r) {
    // Return the answer for this query modulo 1000000007.
    map<char,int> pairs_count;
    int total_pairs_count = 0;
    int loners_count = 0;

    ullint answer = 1;

    int length = r - l;

    map<char, int> leftmost_map = char_maps[l - 1], char_map = char_maps[r];
    for_each(char_map.begin(), char_map.end(), [&leftmost_map](pair<const char, int>& x) {x.second -= leftmost_map[x.first]; });

    int count = 0;
    
    for (auto const& c : char_map) {
        count = c.second;
        pairs_count[c.first] = count / 2;

        for (int i = 0; i < count / 2; i++) {
            answer = product_modulo_N(answer, static_cast<ullint>(total_pairs_count + i + 1), TOP);
            answer = division_modulo_N(answer, static_cast<ullint>(i + 1), TOP);
        }

        total_pairs_count += count / 2;
        loners_count += count % 2;
    }

    /*answer *= factorial_modulo_N(total_pairs_count, TOP);

    for (auto const& p : pairs_count) {
        if (p.second) {
            for (int i = 1; i <= p.second; i++)
                answer = division_modulo_N(answer, i, TOP);
        }
        else
            continue;
    }*/

    return (ullint)((static_cast<ullint>(answer) * (loners_count ? loners_count : 1) % TOP) % TOP);
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    ifstream f1("input.txt");
    ofstream f2("output.txt");
    //buff << f1.rdbuf();

    string s;
    f1 >> s;

    //getline(cin, s);

    auto start_init = chrono::high_resolution_clock::now();
    initialize(s);
    auto finish_init = chrono::high_resolution_clock::now();
    auto mus_int_init = chrono::duration_cast<chrono::microseconds>(finish_init - start_init);

    cout << "La inicializacion tomo " << mus_int_init.count() << " microsegundos\n";
    cin.get();

    string q_temp;
    f1 >> q_temp;
    //getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        //string first_multiple_input_temp;
        //f1 >> first_multiple_input_temp;
        //getline(cin, first_multiple_input_temp);

        //vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        //int l = stoi(first_multiple_input[0]);

        //int r = stoi(first_multiple_input[1]);

        int l, r;

        f1 >> l;
        f1 >> r;

        int result = answerQuery(l, r);

        //cout << result << "\n";
        f2 << result << "\n";
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