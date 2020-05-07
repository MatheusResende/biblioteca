struct Query{
	int l, r, idx, lc, c;
	ll h;
	bool operator<(const Query &q)const{
		return h < q.h;
	}
};

struct MO_TREE{
	vvi g, p;
	vi depth, in, out, ID, v, vis, cnt;
	int n, logN = 18, dfs_cnt = 0; 

	MO_TREE(vvi &g, vi &v):g(g), v(v), n(g.size()){}
	
	void dfs(int u){
		ID[dfs_cnt] = u;
		in[u] = dfs_cnt++;
		for(auto v: g[u]){
			if(depth[v] == -1){
				p[v][0] = u;	
				depth[v] = depth[u] + 1; 
				dfs(v);
			}
		}
		ID[dfs_cnt] = u;
		out[u] = dfs_cnt++;
	}

	void preprocess(){
		p = vvi(n, vi(logN, -1));
		depth = vi(n, -1);
		in = vi(n);
		out = vi(n);
		ID = vi(2 * n);
		depth[0] = 0;
		dfs(0);
		for(int j = 1; j < logN; j++)
			for(int i = 0; i < n; i++)
				if(p[i][j - 1] != -1)
					p[i][j] = p[p[i][j - 1]][j - 1];
	}

	int lca(int u, int v){
		if(depth[u] < depth[v]) swap(u, v);
		for(int i = logN - 1; i >= 0; i--)
			if(depth[u] - (1 << i) >= depth[v])
				u = p[u][i];
		if(u == v) return u;	
		for(int i = logN - 1; i >= 0; i--){
			if(p[u][i] != p[v][i]){
				u = p[u][i];
				v = p[v][i];
			}
		}	
		return p[u][0];
	}
	
	const int N = (1 << 18);
	
	ll hilbert(int x, int y) {
		ll rx, ry, s, d = 0;
		for (s = N/2; s>0; s /= 2) {
			rx = (x & s) > 0;
			ry = (y & s) > 0;
			d += s * s * ((3 * rx) ^ ry);
			if (ry == 0) {
				if (rx == 1) {
					x = N-1 - x;
					y = N-1 - y;
				}
				swap(x, y);
			}
		}
		return d;
	}

	void change(int idx){
		if(vis[ID[idx]]) cnt[v[ID[idx]]]--;
		else cnt[v[ID[idx]]]++;
		vis[ID[idx]] ^= 1;
	} 
	 
	vi solve(vector<Query> &queries){
		int q = queries.size();
		preprocess();
		vis = vi(n);
		cnt = vi(n + 1);
		for(int i = 0; i < q; i++){
			int &L = queries[i].l, &R = queries[i].r;
			if(in[R] < in[L]) swap(L, R);
			int &LC = queries[i].lc;
			LC = lca(L, R);
			if(LC == L){
				L = in[L];
				R = in[R];
			}
			else{
				L = out[L];
				R = in[R];
			}
			queries[i].h = hilbert(L, R);
		}
		int l = 0, r = -1;
		vi ans(queries.size());
		sort(queries.begin(), queries.end());
		for(auto q: queries){
			while(q.l < l)change(--l);
			while(r < q.r)change(++r);
			while(l < q.l)change(l++);
			while(q.r < r)change(r--);
			if(ID[q.l] != q.lc && ID[q.r] != q.lc) change(in[q.lc]);
			ans[q.idx] = cnt[q.c];
			if(ID[q.l] != q.lc && ID[q.r] != q.lc) change(in[q.lc]);
		}
		return ans;
	}
};