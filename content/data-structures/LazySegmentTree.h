/**
 * Author: Atcoder/Modified
 * Date: 2025-10-08
 * License: CC0
 * Description: Segment tree with lazy prop, modify at will.
 *  0-based, inclusive-exclusive.
 * Time: O(\log N).
 * Usage: lazy_segtree<ValType,LazyType> st(arr)
 * Status: stress-tested a bit
 */
#pragma once

template<class T, class F>
struct lazy_segtree {
	int N, log, S;
	T idem = //modify: op(val,idem) = val
	F defLazy = //modify: applyLazy/combLazy(val,defLazy) = val
	vector<T> d;
	vector<F> lz;
	T op(T left, T right) { /*modify*/ }
	T applyLazy(T val, F lazy) { /*modify*/ }
	F combLazy(F old, F nw) { /*modify*/ } 
	lazy_segtree(const vector<T>& v): N(sz(v)), log(__lg(2 * N
			- 1)), S(1 << log), d(2 * S, idem), lz(S, defLazy) {
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
};
