/**
 * Author: Luke Videckis
 * Description: bridges
 * adj[u] += {v, i};
 * adj[v] += {u, i};
 * is\_br[edge id] = 1 iff bridge edge
 * br\_id[v] = id, 0<=id<num\_ccs
 * returns {num\_ccs, br\_id, is\_br}
 * Assumes the root node points to itself.
 */
#pragma once

auto bridges(const auto& adj, int m) {
	int n = ssize(adj), num_ccs = 0, q = 0, s = 0;
	vector<int> br_id(n, -1), is_br(m), tin(n), st(n);
	auto dfs = [&](auto&& self, int v, int p) -> int {
		int low = tin[v] = ++q;
		st[s++] = v;
		for (auto [u, e] : adj[v])
			if (e != p && br_id[u] < 0)
				low = min(low, tin[u] ?: self(self, u, e));
		if (tin[v] == low) {
			if (p != -1) is_br[p] = 1;
			while (br_id[v] < 0) br_id[st[--s]] = num_ccs;
			num_ccs++;
		}
		return low;
	};
	for (int i = 0; i < n; i++)
		if (!tin[i]) dfs(dfs, i, -1);
	return tuple{num_ccs, br_id, is_br};
}
