//                             ┌───────────────────────────────────────────┐
//                             │ Copyright (c) 2019-2022 Nikita Paniukhin  │
//                             │      Licensed under the MIT license       │
//                             └───────────────────────────────────────────┘
//
//                                               Hi there!
//        Here you will find a number of data structures and useful tools for olympic programming
//  If you're looking for the code to solve a specific problem, it starts down below, at about line 246


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

template <class T>
T _read(){T x;cin>>x;return x;}

#define all(_x) (_x).begin(), (_x).end()
#define rall(_x) (_x).rbegin(), (_x).rend()
#define sortv(_x) sort((_x).begin(), (_x).end())
#define get(_type, _x) _type _x; cin >> (_x);
#define print(_x) cout << (_x) << endl;
#define read(_type) _read <_type> ()
#define maxind(_v) (max_element((_v).begin(), (_v).end()) - (_v).begin())
#define minind(_v) (min_element((_v).begin(), (_v).end()) - (_v).begin())
#define print_float fixed << setprecision(20)
#define print_array(_v) for(int _i=0;_i<(_v).size();++_i){cout<<(_v)[_i]<<' ';}cout<<endl;
#define rand_init srand(time(NULL))

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
// #define endl '\n'


struct Node {
    int x, y;
    Node *l, *r;

    Node(int x) {
        this->x = x;
        y = rand() * rand();
        l = r = nullptr;
    }
};

void split(Node *t, Node *&l, Node *&r, int x) {
    if (t == nullptr) {
        l = r = nullptr;
        return;
    }

    if (t->x < x) {
        split(t->r, t->r, r, x);
        l = t;
    } else {
        split(t->l, l, t->l, x);
        r = t;
    }
}

void insert(Node *&t, Node *v) {
    if (t == nullptr) {
        t = v;
        return;
    }

    if (t->y > v->y) {
        insert(v->x < t->x ? t->l : t->r, v);
        return;
    }

    split(t, v->l, v->r, v->x);
    t = v;
}

void merge(Node *&t, Node *l, Node *r) {
    if (l == nullptr || r == nullptr) {
        t = (r == nullptr ? l : r);
        return;
    }

    if (l->y > r->y) {
        merge(l->r, l->r, r);
        t = l;
    } else {
        merge(r->l, l, r->l);
        t = r;
    }
}

void remove(Node *&t, int x) {
    if (t == nullptr) return;

    if (x < t->x) {
        remove(t->l, x);
    } else if (x > t->x) {
        remove(t->r, x);
    } else {
        merge(t, t->l, t->r);
    }
}

bool exists(Node *&t, int x) {
    if (t == nullptr) return false;

    if (x == t->x) return true;

    return exists(x < t->x ? t->l : t->r, x);
}


Node* prev(Node *&t, int x) {
    Node *cur = t, *succ = nullptr;

    while (cur != nullptr) {
        if (cur->x < x) {
            succ = cur;
            cur = cur->r;
        } else {
            cur = cur->l;
        }
    }

    return succ;
}

Node* next(Node *&t, int x) {
    Node *cur = t, *succ = nullptr;

    while (cur != nullptr) {
        if (cur->x > x) {
            succ = cur;
            cur = cur->l;
        } else {
            cur = cur->r;
        }
    }
    return succ;
}

signed main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

    Node *v, *t = nullptr;
    
    string operation;
    int x;
    while (cin >> operation >> x) {
        if (operation == "insert") {
            v = new Node(x);
            if (!exists(t, x)) insert(t, v);

        } else if (operation == "exists") {
            cout << (exists(t, x) ? "true" : "false") << endl;

        } else if (operation == "delete") {
            if (exists(t, x)) remove(t, x);

        } else if (operation == "next") {
            v = next(t, x);
            if (v == nullptr) {
                cout << "none" << endl;
            } else {
                cout << v->x << endl;
            }

        } else if (operation == "prev") {
            v = prev(t, x);
            if (v == nullptr) {
                cout << "none" << endl;
            } else {
                cout << v->x << endl;
            }
        }
    }
}
