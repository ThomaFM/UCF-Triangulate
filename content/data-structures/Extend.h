/**
 * Author: Andy Phan
 * Date: 2026-02-06
 * License: CC0
 * Source: Andy Phan/Atcoder
 * Description: Extends a range starting at p towards the left/right
 * as much as possible while maintaining g(query(l, r)). Note query is [)
 * Add to LazySegmentTree structure
 * Time: $O(\log N)$.
 */
int extend(int p, bool left, auto g) {
  if (p == N * !left) return p;
  assert(g(idem)); p += S;
  for (int i = log; i >= 1; i--) push((p - left) >> i);
  T sm = idem;
  do {
    if (left) { p--; while (p > 1 && (p % 2)) p /= 2; }
    else while (p % 2 == 0) p /= 2;
    if (!g(left ? op(d[p], sm) : op(sm, d[p]))) {
      while (p < S) {
        push(p); 
        p = 2 * p + left;
        if (left) { if (g(op(d[p], sm))) sm = op(d[p--], sm); }
        else { if (g(op(sm, d[p]))) sm = op(sm, d[p++]); }
      }
      return p + left - S;
    }
    sm = left ? op(d[p], sm) : op(sm, d[p++]);
  } while ((p & -p) != p);
  return N * !left;
}
