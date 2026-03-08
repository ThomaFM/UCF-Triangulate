/**
 * Author: Luke Videckis
 * Date: 2026-03-08
 * Description: Segtree walks for use in SegmentTree.h
 * g(query(l,r)) must be montonic. See inline comment
 * Remember query is [)
 * Time: $O(\log(N))$
 * Status: Tested
 */
#pragma once
// LARGEST x in [l,r] s.t. g(query(l,x)) is true
int max_right(int l, int r, const auto& g) {
	for (T x = unit; l < r;) {
		int u = l + n, v = __lg(min(u & -u, r - l));
		if (T y = f(x, s[u >> v]); g(y)) l += 1 << v, x = y;
		else r = l + (1 << v) - 1;
	} return l;
}
// SMALLEST x in [l,r] s.t. g(query(x,r)) is true
int min_left(int l, int r, const auto& g) {
	for (T x = unit; l < r;) {
		int u = r + n, v = __lg(min(u & -u, r - l));
		if (T y = f(s[(u - 1) >> v], x); g(y))
		r -= 1 << v, x = y;
		else l = r - (1 << v) + 1;
	} return r;
}