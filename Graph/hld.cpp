struct HLD{
	segTree seg;
	vi sz, in, out, nxt, p, h;
	vvi g;
	int n, t = 1;
	
	HLD(vvi g){
		n = g.size();
		sz = vi(n), in = vi(n), nxt = vi(n), p = vi(n), h = vi(n);
		nxt[1] = 1;
		dfs_sz(1, g);
		dfs_hld(1, g);
		seg = segTree(n + 1);
	}
	
	void dfs_sz(int u, vvi &g) {
		sz[u] = 1;
		for(auto &v: g[u]) {
			if(sz[v]) continue;
			p[v] = u;
			dfs_sz(v, g);
			sz[u] += sz[v];
			if(sz[v] > sz[g[u][0]] || g[u][0] == p[u])
				swap(v, g[u][0]);
		}
	}

	void dfs_hld(int u, vvi &g) {
		in[u] = t++;
		for(auto v: g[u]){
			if(u != p[v]) continue;
			nxt[v] = (v == g[u][0] ? nxt[u] : v);
			h[v] = h[u] + (v != g[u][0]);
			dfs_hld(v, g);
		}
	}

	int query_Update(int a, int b, bool isquery, int v = 0){
		if(isquery) return seg.query(1, 1, n, a, b);
		seg.update(1, 1, n, a, b, v);
		return 0;
	}

	int query(int a, int b, bool isQuery = true, int v = 0){
		int res = 0;
		if(h[a] < h[b])
			swap(a, b);
		while(h[a] > h[b]){
			res = max(res, query_Update(in[nxt[a]], in[a], isQuery, v));
			a = p[nxt[a]];
		}
		while(nxt[a] != nxt[b]){
			res = max(res, query_Update(in[nxt[a]], in[a], isQuery, v));
			a = p[nxt[a]];
			res = max(res, query_Update(in[nxt[b]], in[b], isQuery, v));
			b = p[nxt[b]];
		}
		if(in[a] != in[b]){//Query and update on edge
			if(in[b] < in[a]) swap(a, b);
			res = max(res, query_Update(in[a] + 1, in[b], isQuery, v));
		}
		return res;
	}
	
	void update(int a, int b, int v){
		query(a, b, false, v);
	}
};