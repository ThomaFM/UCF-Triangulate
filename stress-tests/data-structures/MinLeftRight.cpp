#include "../utilities/template.h"

using T = pair<ll, ll>;
using F = ll;
T idem = {0, 0};
F defLazy = 0;
T op(T left, T right) { return {left.first + right.first, left.second + right.second}; }
T applyLazy(T val, F lazy) { return {val.first + val.second * lazy, val.second}; }
F combLazy(F old, F nw) { return old + nw; }

struct lazy_segtree {
	int N, log, S;
	vector<T> d;
	vector<F> lz;
	lazy_segtree(const vector<T>& v):
		N(sz(v)), log(__lg(2 * N - 1)), S(1 << log), d(2 * S, idem),
		lz(S, defLazy) {
		for (int i = 0; i < N; i++) d[S + i] = v[i];
		for (int i = S - 1; i >= 1; i--) pull(i);
	}
	void apply(int k, F f) {
		d[k] = applyLazy(d[k], f);//len= S>>(31-__builtin_clz(k));
		if (k < S) lz[k] = combLazy(lz[k],f);
	}
	void push(int k) {
		apply(2 * k, lz[k]), apply(2 * k + 1, lz[k]), lz[k] = defLazy;
	}
	void push(int l, int r) {
		int zl = __builtin_ctz(l), zr = __builtin_ctz(r);
		for (int i = log; i > min(zl, zr); i--) {
			if (i > zl) push(l >> i);
			if (i > zr) push((r - 1) >> i);
		}
	}
	void pull(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
	void set(int p, T x) {
		p += S;
		for (int i = log; i >= 1; i--) push(p >> i);
		for (d[p] = x; p /= 2;) pull(p);
	}
	T query(int l, int r) {
		if (l == r) return idem;
		push(l += S, r += S);
		T vl = idem, vr = idem;
		for (; l < r; l /= 2, r /= 2) {
			if (l & 1) vl = op(vl, d[l++]);
			if (r & 1) vr = op(d[--r], vr);
		}
		return op(vl, vr);
	}
	void update(int l, int r, F f) {
		if (l == r) return;
		push(l += S, r += S);
		for (int a = l, b = r; a < b; a /= 2, b /= 2) {
			if (a & 1) apply(a++, f);
			if (b & 1) apply(--b, f);
		}
		int zl = __builtin_ctz(l), zr = __builtin_ctz(r);
		for (int i = min(zl, zr) + 1; i <= log; i++) {
			if (i > zl) pull(l >> i);
			if (i > zr) pull((r - 1) >> i);
		}
	}
#include "../../content/data-structures/MinLeft.h"
#include "../../content/data-structures/MaxRight.h"

};

struct lazy_segtree2 {
	vector<T> vals;
	lazy_segtree2(const vector<T> &vals) : vals(vals) {}
	T query(int l, int r) {
		T res = idem;
		for (int i = l; i < r; ++i) {
			res = op(res, vals[i]);
		}
		return res;
	}
	void set(int p, T x) {
		vals[p] = x;
	}
	void update(int l, int r, F f) {
		for (int i = l; i < r; ++i) {
			vals[i] = applyLazy(vals[i], f);
		}
	}
	int min_left(int r, auto g) {
		assert(g(idem));
		for (int l = 0; l <= r; ++l) {
			if (g(query(l, r))) return l;
		}
		assert(0);
	}
	int max_right(int l, auto g) {
		assert(g(idem));
		for (int r = vals.size(); r >= l; --r) {
			if (g(query(l, r))) return r;
		}
		assert(0);
	}
};

mt19937 rng;

int main() {
	for (int iter = 0; iter < 10000; ++iter) {
		vector<T> initVals(rng() % (iter < 500 ? 100 : 10) + 1);
		for (T &x : initVals) {
			x = {rng() % 10 + 1, rng() % 10 + 1};
		}
		lazy_segtree tree(initVals);
		lazy_segtree2 tree2(initVals);
		for (int qi = 0; qi < 1000; ++qi) {
			int t = rng() % 5;
			if (t == 0) {
				int i = rng() % initVals.size();
				T x = {rng() % 10 + 1, rng() % 10 + 1};
				tree.set(i, x);
				tree2.set(i, x);
			}
			else if (t == 1) {
				int l = rng() % (initVals.size() + 1);
				int r = rng() % (initVals.size() + 1);
				if (l > r) swap(l, r);
				F f = rng() % 10;
				tree.update(l, r, f);
				tree2.update(l, r, f);
			}
			else if (t == 2) {
				int l = rng() % (initVals.size() + 1);
				int r = rng() % (initVals.size() + 1);
				if (l > r) swap(l, r);
				T t1 = tree.query(l, r);
				T t2 = tree2.query(l, r);
				assert(t1 == t2);
			}
			else if (t == 3) {
				int r = rng() % (initVals.size() + 1);
				int v = rng() % 50;
				int l1 = tree.min_left(r, [&](T t) { return t.first <= v; });
				int l2 = tree2.min_left(r, [&](T t) { return t.first <= v; });
				assert(l1 == l2);
			}
			else if (t == 4) {
				int l = rng() % (initVals.size() + 1);
				int v = rng() % 50;
				int r1 = tree.max_right(l, [&](T t) { return t.first <= v; });
				int r2 = tree2.max_right(l, [&](T t) { return t.first <= v; });
				assert(r1 == r2);
			}
		}
	}

	cout<<"Tests passed!"<<endl;
}
