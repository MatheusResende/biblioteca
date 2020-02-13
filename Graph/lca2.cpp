//lca 
//preprocess O(n)
//query O(log n)

struct LCA{
    vi h, euler, first, seg;
    int n;

    LCA(vvi &g, int root = 0) {
        n = g.size();
        euler = vi(n * 2);
		first = vi(n);
		h = vi(n, -1);
		h[root] = 0;
        dfs(g, root);
        int m = euler.size();
        seg = vi(m * 4);
        build(1, 0, m - 1);
    }

    void dfs(vvi &g, int u) {
        first[u] = euler.size();
        euler.push_back(u);
        for (auto v : g[u]) {
            if (h[v] < 0) {
				h[v] = h[u] + 1;
                dfs(g, v);
                euler.push_back(u);
            }
        }
    }

    void build(int idx, int l, int r) {
        if (l == r) {
            seg[idx] = euler[l];
        } else {
            int mid = (r + l) / 2;
            build(idx * 2, l, mid);
            build(idx * 2 + 1, mid + 1, r);
            l = seg[idx * 2], r = seg[idx * 2 + 1];
            seg[idx] = (h[l] < h[r]) ? l : r;
        }
    }

    int query(int idx, int ss, int se, int qs, int qe) {
        if (ss > qe || se < qs)
            return -1;
        if (qs <= ss && se <= qe)
            return seg[idx];
        int mid = (ss + se) / 2;
        int l = query(idx * 2, ss, mid, qs, qe);
        int r = query(idx * 2 + 1, mid + 1, se, qs, qe);
        if (l == -1) return r;
        if (r == -1) return l;
        return h[l] < h[r] ? l : r;
    }

    int lca(int u, int v) {
        int l = first[u], r = first[v];
        if (l > r) swap(l, r);
        return query(1, 0, euler.size() - 1, l, r);
    }
};