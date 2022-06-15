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

random_device random_dev;
mt19937 rng(random_dev());
mt19937_64 rng_64(random_dev());

int randint(int start = 0, int end = INT_MAX) {
	// return rand() % (end - start) + start + 1;
	uniform_int_distribution<mt19937::result_type> distrib(start, end); // distribution in range [1, 6]
	return distrib(rng);
}

long long randll(long long start = 0, long long end = LLONG_MAX) {
	// return rand() % (end - start) + start + 1;
	uniform_int_distribution<mt19937_64::result_type> distrib(start, end); // distribution in range [1, 6]
	return distrib(rng_64);
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

class LinkCutTree {
public:
	struct Vertex {
		int left, right, parent;
		bool revert;
		int size;
		int64_t value, result, delta;

		Vertex()
			: left(-1), right(-1), parent(-1), revert()
			, size(1), value(), result(), delta() {}
	};

	vector<Vertex> t;

	bool isRoot(int x) const {
		int p = t[x].parent;
		return p == -1 || (t[p].left != x && t[p].right != x);
	}

	int64_t getValue(int x) const {
		return t[x].value + t[x].delta;
	}

	int64_t getResult(int x) const {
		return t[x].result + t[x].delta * t[x].size;
	}

	void push(int x) {
		if (t[x].revert) {
			if (t[x].left != -1)
				t[t[x].left].revert = !t[t[x].left].revert;
			if (t[x].right != -1)
				t[t[x].right].revert = !t[t[x].right].revert;
			swap(t[x].left, t[x].right);
			t[x].revert = false;
		}
		t[x].value = getValue(x);
		t[x].result = getResult(x);
		if (t[x].left != -1)
			t[t[x].left].delta += t[x].delta;
		if (t[x].right != -1)
			t[t[x].right].delta += t[x].delta;
		t[x].delta = 0;
	}

	void keep(int x) {
		t[x].size = 1;
		t[x].result = getValue(x);
		if (t[x].left != -1) {
			t[x].size += t[t[x].left].size;
			t[x].result += getResult(t[x].left);
		}
		if (t[x].right != -1) {
			t[x].size += t[t[x].right].size;
			t[x].result += getResult(t[x].right);
		}
	}

	void rotate(int x) {
		int p = t[x].parent;
		int g = t[p].parent;
		push(p), push(x);
		if (g != -1) {
			if (t[g].left == p)
				t[g].left = x;
			else if (t[g].right == p)
				t[g].right = x;
		}
		t[x].parent = g;
		if (t[p].left == x) {
			t[p].left = t[x].right;
			if (t[p].left != -1)
				t[t[p].left].parent = p;
			t[x].right = p;
		} else {
			t[p].right = t[x].left;
			if (t[p].right != -1)
				t[t[p].right].parent = p;
			t[x].left = p;
		}
		t[p].parent = x;
		keep(p), keep(x);
	}

	void splay(int x) {
		while (!isRoot(x)) {
			int p = t[x].parent;
			if (!isRoot(p)) {
				int g = t[p].parent;
				bool zigzig = (x == t[p].left) == (p == t[g].left);
				rotate(zigzig ? p : x);
			}
			rotate(x);
		}
		push(x);
	}

	int expose(int x) {
		int c = -1;
		for (int y = x; y != -1; y = t[y].parent) {
			splay(y);
			t[y].right = c;
			keep(y);
			c = y;
		}
		splay(x);
		return c;
	}

	LinkCutTree(int n) : t(n) {}

	void evert(int x) {
		expose(x);
		t[x].revert = !t[x].revert;
	}

	int root(int x) {
		expose(x);
		while (t[x].left != -1) {
			x = t[x].left;
			push(x);
		}
		expose(x);
		return x;
	}

	int parent(int x) {
		expose(x);
		if (t[x].left == -1)
			return -1;
		x = t[x].left;
		push(x);
		while (t[x].right != -1) {
			x = t[x].right;
			push(x);
		}
		return x;
	}

	bool path(int x, int y) {
		if (x == y)
			return true;
		expose(y), expose(x);
		return t[y].parent != -1;
	}

	void link(int x, int y) {
		if (path(x, y))
			return;
		evert(x);
		t[x].parent = y;
	}

	void cut(int x) {
		expose(x);
		if (t[x].left == -1)
			return;
		t[t[x].left].parent = -1;
		t[x].left = -1;
	}

	int lca(int x, int y) {
		if (!path(x, y))
			return -1;
		expose(x);
		return expose(y);
	}

	int depth(int x) {
		expose(x);
		if (t[x].left == -1)
			return 0;
		return t[t[x].left].size;
	}

	int distance(int x, int y) {
		int l = lca(x, y);
		if (l == -1)
			return -1;
		return depth(y) + depth(x) - depth(l) * 2;
	}

	int64_t query(int x, int y) {
		if (!path(x, y))
			return 0;
		evert(x), expose(y);
		return t[y].result;
	}

	void update(int x, int y, int64_t value) {
		if (!path(x, y))
			return;
		evert(x), expose(y);
		t[y].delta += value;
	}
};

signed main() {
	ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

	int n, m, u, v, u_root, v_root;
	cin >> n >> m;

	auto tree = LinkCutTree(n);

	string req_type;
	for (int req = 0; req < m; ++req) {
		cin >> req_type >> u >> v; --u; --v;

		if (req_type == "link") {
			tree.link(u, v);

		} else if (req_type == "cut") {
			tree.evert(v);
			tree.cut(u);

		} else {
			cout << (tree.root(u) == tree.root(v)) << endl;
		}
	}
}
