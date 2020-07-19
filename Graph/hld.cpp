struct HLD{
	segTree seg;
	vi sz, in, out, nxt, p, h;
	vvi g;
	int n, t = 1;
	
	HLD(vvi g): n(g.size()), in(n), nxt(n), p(n), h(n), seg(n + 1){
		nxt[1] = 1;
		dfs_sz(1, g);
		dfs_hld(1, g);
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

	void update(int a, int b, int v){
		if(h[a] < h[b]) swap(a, b);
		if(nxt[a] == nxt[b]){
			if(in[b] < in[a])swap(a, b);
			if(in[a] != in[b]) seg.update(1, 1, n, in[a]+1, in[b], v);
		}
		else seg.update(1, 1, n, in[nxt[a]], in[a], v), update(p[nxt[a]], b, v);
	}

	int query(int a, int b){
		if(h[a] < h[b]) swap(a, b);
		if(nxt[a] == nxt[b]){
			if(in[b] < in[a])swap(a, b);
			return (in[a] != in[b])? seg.query(1, 1, n, in[a]+1, in[b]): 0;
		}
		return max(seg.query(1, 1, n, in[nxt[a]], in[a]), query(p[nxt[a]], b));
	}
};