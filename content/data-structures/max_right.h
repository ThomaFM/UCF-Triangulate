/**
 * Author: Thomas Meeks
 * Date: 2026-O2-6
 * License: CC0
 * Source: Andy Phan/Atcoder
 * Description: Maximum r such that g(query(l, r)). Note query is [)
 * Usage: LazySegTree.max_right(l, [&](ll v)->bool { return v<x; });
 * would return the first index such that v>=x in a max LazySegtree.
 * Time: O(\log N).
 */

int max_right(int l, auto g) {
    if (l == N) return N;
    assert(g(idem)); l += S;
    for (int i = log; i >= 1; i--) push(l >> i);
    T sm = idem;
    do {
        while (l % 2 == 0) l /= 2;
        if (!g(op(sm, d[l]))) {
            while (l < S) {
                push(l); 
                l = 2 * l; 
                if (g(op(sm, d[l]))) {
                    sm = op(sm, d[l]);
                    l++; 
                }
            }
            return l - S;
        }
        sm = op(sm, d[l]);
        l++;
    } while ((l & -l) != l);
    return N;
}
