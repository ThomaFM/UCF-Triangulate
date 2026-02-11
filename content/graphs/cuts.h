/**
 * Author: Luke Videckis
 * Description: articulation points and block-vertex tree
 * self edges not allowed
 * adj[u] += {v, i};
 * adj[v] += {u, i};
 * is\_cut[v] = 1 iff cut node
 * bcc\_id[edge id] = id, 0<=id<num\_bccs
 * returns {num\_bccs, bcc\_id, is\_cut}
 * Assumes the root node points to itself.
 * Time: $O(n+m)$
 * Memory: $O(n+m)$
 */
#pragma once

auto cuts(const auto& adj, int m) {
	int n = ssize(adj), num_bccs = 0, q = 0, s = 0;
	vector<int> bcc_id(m, -1), is_cut(n), tin(n), st(m);
	auto dfs = [&](auto&& self, int v, int p) -> int {
		int low = tin[v] = ++q;
		for (auto [u, e] : adj[v]) {
			assert(v != u);
			if (e == p) continue;
			if (tin[u] < tin[v]) st[s++] = e;
			int lu = -1;
			low = min(low, tin[u] ?: (lu = self(self, u, e)));
			if (lu >= tin[v]) {
				is_cut[v] = p >= 0 || tin[v] + 1 < tin[u];
				while (bcc_id[e] < 0) bcc_id[st[--s]] = num_bccs;
				num_bccs++;
			}
		}
		return low;
	};
	for (int i = 0; i < n; i++)
		if (!tin[i]) dfs(dfs, i, -1);
	return tuple{num_bccs, bcc_id, is_cut};
}