/**
 * Author: Andy Phan
 * Date: 2026-02-06
 * License: CC0
 * Source: Andy Phan/Atcoder
 * Description: Minimum l such that g(query(l, r)). Note query is [)
 * Add to LazySegmentTree structure
 * Time: $O(\log N)$.
 */
int min_left(int r, auto g) {
    if (r == 0) return 0;
    assert(g(idem)); r += S;
    for (int i = log; i >= 1; i--) push((r - 1) >> i);
    T sm = idem;
    do {
        r--;
        while (r > 1 && (r % 2)) r /= 2;
        if (!g(op(d[r], sm))) {
            while (r < S) {
                push(r); 
                r = 2 * r + 1; 
                if (g(op(d[r], sm))) {
                    sm = op(d[r], sm);
                    r--; 
                }
            }
            return r + 1 - S;
        }
        sm = op(d[r], sm);
    } while ((r & -r) != r);
    return 0;
}
