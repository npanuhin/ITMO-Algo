//                             ┌───────────────────────────────────────────┐
//                             │ Copyright (c) 2019-2022 Nikita Paniukhin  │
//                             │      Licensed under the MIT license       │
//                             └───────────────────────────────────────────┘
//
//                                               Hi there!
//        Here you will find a number of data structures and useful tools for olympic programming
//  If you're looking for the code to solve a specific problem, it starts down below, at about line 247


#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,tune=native")
#pragma GCC target("avx2")

// #include <bits/stdc++.h>

// #define _USE_MATH_DEFINES

// #include "getCPUTime.c"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits.h>
#include <cassert>
#include <cstring>
#include <float.h>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <bitset>
#include <math.h>
#include <random>
#include <vector>
#include <cmath>
#include <deque>
#include <queue>
#include <map>
#include <set>

using namespace std;
typedef long long LL;typedef long long ll;typedef unsigned long long uLL;typedef unsigned long long ull;typedef unsigned int uint;typedef unsigned char uchar;typedef long double ld;typedef long double Ld;

// ============= GLOBAL CONST =============

const int MOD = 1e9 + 7;
// const int MOD2 = 1e9 + 7;

// ========================================

#define all(_x) (_x).begin(), (_x).end()
#define rall(_x) (_x).rbegin(), (_x).rend()
#define sortv(_x) sort((_x).begin(), (_x).end())
#define get(_type, _x) _type _x; cin >> (_x);
#define print(_x) cout << (_x) << endl;
#define maxind(_v) (max_element((_v).begin(), (_v).end()) - (_v).begin())
#define minind(_v) (min_element((_v).begin(), (_v).end()) - (_v).begin())
#define print_float fixed << setprecision(20)
#define print_array(_v) for(int _i=0;_i<(_v).size();++_i){cout<<(_v)[_i]<<' ';}cout<<endl;
#define rand_init srand(time(NULL))

template <class T>
T read(){T x;cin>>x;return x;}
template <class T>
vector<T> vector_init(int n){vector<T> x;x.reserve(n);return x;}

template <class T>
long long sum(vector<T> &a){long long x=0;for(int _i=0;_i<a.size();++_i)x+=a[_i];return x;}

bool contains(string &s, char x) {for(size_t i=0;i<s.size();++i){if(s[i]==x){return true;}}return false;}
template <class T>
bool contains(vector<T> &a, T x) {for(size_t i=0;i<a.size();++i){if(a[i]==x){return true;}}return false;}

template<class InputIt, class T>
typename iterator_traits<InputIt>::difference_type
rcount(InputIt first, InputIt last, const T& value){typename iterator_traits<InputIt>::difference_type ret=0;for(;first!=last;++first){if(*first!=value)++ret;}return ret;}

string cut(string &s, int start, int end) {string r;while(max(start,0)<min((int)s.size(),end)){r+=s[start++];}return r;}
template <class T>
vector<T> cut(vector<T> &a, int start, int end) {vector<T> r;while(max(start,0)<min((int)a.size(),end)){r.emplace_back(a[start++]);}return r;}

template <class T1, class T2>
bool equal(vector<T1> &a, vector<T2> &b) {if (a.size() != b.size()) return false;for (size_t i = 0; i < a.size(); ++i) if (a[i] != b[i]) return false;return true;}

template <class T>
T gcd(T a, T b) {while(b){a%=b;swap(a,b);}return a;}

template <class T>
T gcd(T a, T b, T &x, T &y) {if(a == 0){x = 0;y = 1;return b;}int x1, y1;int d = gcd(b%a, a, x1, y1);x = y1 - (b / a) * x1;y = x1;return d;}

template <class T>
T lcm(T a, T b) {return a/gcd(a, b)*b;}

long long binpow(long long a, unsigned int n) {long long r=1;while(n){if(n&1)r*=a;a*=a;n>>=1;}return r;}

bool isPrime(long long num) {
    if (num == 2) return true;
    if (num <= 1 || num % 2 == 0) return false;
    int upperLimit = (int)( sqrt((double)num) + 1 );
    for (int divisor = 3; divisor <= upperLimit; divisor += 2) {
        if (num % divisor == 0) return false;
    }
    return true;
}

template <class T>
vector<long long> prefSumm(vector<T> a) {
    vector<long long> pref_summ(a.size());
    pref_summ[0] = (long long)a[0];
    for (size_t i = 1; i < a.size(); ++i)
        pref_summ[i] = pref_summ[i - 1] + (long long)a[i];
    return pref_summ;
}

template <class T>
vector<int> prefixFunction(vector<T> a) {
    int n = (int)a.length();
    vector<int> prefix_function(n);
    for (int i = 1; i < n; ++i) {
        int j = prefix_function[i - 1];
        while (j > 0 && a[i] != a[j])
            j = prefix_function[j - 1];
        if (a[i] == a[j]) ++j;
        prefix_function[i] = j;
    }
    return prefix_function;
}

//============================ RANDOM ============================

int randint(int start = 0, int end = INT_MAX) {
    // return rand() % (end - start) + start + 1;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distrib(start, end); // distribution in range [1, 6]
    return distrib(rng);
}

long long randll(long long start = 0, long long end = LLONG_MAX) {
    // return rand() % (end - start) + start + 1;
    std::random_device dev;
    std::mt19937_64 rng(dev());
    std::uniform_int_distribution<std::mt19937_64::result_type> distrib(start, end); // distribution in range [1, 6]
    return distrib(rng);
}

//============================ MATRIX ============================

template <class T>
vector<T> matrix_to_array(vector<vector<T>> &matrix) {
    int n = matrix.size(), m = matrix[0].size();
    vector<T> res(n * m);
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j) res[i * n + j] = matrix[i][j];
    return res;
}

template <class T>
vector<vector<T>> array_to_matrix(vector<T> &matrix, pair<int, int> matrix_size) {
    vector<T> tmp_v_T(matrix_size.second);
    vector<vector<T>> res(matrix_size.first, tmp_v_T);
    for (size_t i = 0; i < matrix_size.first; ++i) for (size_t j = 0; j < matrix_size.second; ++j) res[i][j] = matrix[i * matrix_size.first + j];
    return res;
}

template <class T>
void matrix_print(vector<T> &matrix, pair<int, int> matrix_size) {
    for (size_t i = 0; i < matrix_size.first; ++i) {
        for (size_t j = 0; j < matrix_size.second; ++j) cout << matrix[i * matrix_size.first + j] << ' ';
        cout << endl;
    }
}

template <class T>
void matrix_print(vector<vector<T>> &matrix) {for(int i=0;i<matrix.size();++i){print_array(matrix[i])}}

template <class T1, class T2>
vector<vector<long long>> matrix_multiply(vector<vector<T1>> &matrix1, vector<vector<T2>> &matrix2) {
    int m = matrix1.size(), k = matrix1[0].size(), n = matrix2[0].size();

    vector<long long> tmp_v_ll(n, 0);
    vector<vector<long long>> res(m, tmp_v_ll);

    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            for (size_t t = 0; t < k; ++t) {
                res[i][j] += matrix1[i][t] * matrix2[t][j];
                res[i][j] %= MOD;
            }
        }
    }
    return res;
}

template <class T1, class T2>
vector<long long> matrix_multiply(vector<T1> &matrix1, pair<int, int> matrix1_size, vector<T2> &matrix2, pair<int, int> matrix2_size) {
    int m = matrix1_size.first, k = matrix1_size.second, n = matrix2_size.second;

    vector<long long> res(m * n, 0);

    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            for (size_t t = 0; t < k; ++t) {
                res[i * n + j] += matrix1[i * k + t] * matrix2[t * n + j];
                res[i * n + j] %= MOD;
            }
        }
    }
    return res;
}

template <class T1, class T2>
vector<vector<long long>> matrix_binpow(vector<vector<T1>> &matrix, T2 power) {
    if (power == 0) {  // return identity matrix
        vector<long long> tmp_v_ll(matrix[0].size(), 0);
        vector<vector<long long>> res(matrix.size(), tmp_v_ll);
        for (size_t i = 0; i != matrix.size(); ++i) res[i][i] = 1;
        return res;
    }

    if (power % 2 == 1) {
        vector<vector<long long>> res = matrix_binpow(matrix, power - 1);
        return matrix_multiply(res, matrix);
    }

    vector<vector<long long>> res = matrix_binpow(matrix, power / 2);
    return matrix_multiply(res, res);
}

template <class T1, class T2>
vector<long long> matrix_binpow(vector<T1> &matrix, int matrix_size, T2 power) {
    if (power == 0) {  // return identity matrix
        vector<long long> res(matrix_size * matrix_size, 0);
        for (size_t i = 0; i != matrix_size; ++i) res[i * (matrix_size + 1)] = 1;
        return res;
    }

    if (power % 2 == 1) {
        vector<long long> res = matrix_binpow(matrix, matrix_size, power - 1);
        return matrix_multiply(res, make_pair(matrix_size, matrix_size), matrix, make_pair(matrix_size, matrix_size));
    }

    vector<long long> res = matrix_binpow(matrix, matrix_size, power / 2);
    return matrix_multiply(res, make_pair(matrix_size, matrix_size), res, make_pair(matrix_size, matrix_size));
}


// ==============================================================================================================

// Usage:
// [r]count(all(vector), value)
// equal(vector1, vector2)
// cut(string/vector, int start, int end)
// contains(string/vector, value)

// Tweakable defines:
// #define int long long
#define endl '\n'

void build(vector<vector<int>> &graph, vector<int> &depth, vector<vector<int>> &dp, int steps, int v = 0, int p = 0) {
    if (p != v) depth[v] = depth[p] + 1;

    dp[v][0] = p;
    for (int i = 1; i <= steps; ++i) dp[v][i] = dp[dp[v][i - 1]][i - 1];

    for (int next : graph[v]) {
        if (next != p) build(graph, depth, dp, steps, next, v);
    }
}

int lca(vector<int> &depth, vector<vector<int>> &dp, int steps, int u, int v) {
    if (depth[v] > depth[u]) swap(v, u);

    for (int i = steps; i >= 0; --i) {
        if (depth[dp[u][i]] >= depth[v]) u = dp[u][i];
    }

    if (v == u) return v;

    for (int i = steps; i >= 0; --i) {
        if (dp[v][i] != dp[u][i]) {
            v = dp[v][i];
            u = dp[u][i];
        }
    }

    return dp[v][0];
}

int count(vector<vector<int>> &graph, vector<vector<int>> &dp, vector<int> &a, vector<int> &b, int &res, int v = 0) {
    int r = a[v], tmp;
    for (int next : graph[v]) {
        if (next != dp[v][0]) {
            tmp = count(graph, dp, a, b, res, next);
            if (tmp == 0) ++res;
            r += tmp;
        }
    }
    return r - 2 * b[v];
}

signed main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

    int n, m, u, v;
    cin >> n;

    vector<vector<int>> graph(n);
    for (int i = 0; i < n - 1; ++i) {
        cin >> u >> v; --u; --v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<int> depth(n);
    vector<vector<int>> dp(n);
    int steps = 0;
    while ((1 << steps) <= n) ++steps;
    for (int i = 0; i < n; ++i) dp[i].resize(steps + 1);

    build(graph, depth, dp, steps);

    cin >> m;
    vector<int> a(n), b(n);
    for (int i = 0; i < m; ++i) {
        cin >> u >> v; --u; --v;
        ++a[u]; ++a[v];
        ++b[lca(depth, dp, steps, u, v)];
    }
    int res = 0;
    count(graph, dp, a, b, res, 0);
    cout << res << endl;
}
