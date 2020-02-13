//LCA 
//preprocess O(nlog n)
//query O(log n)
vvi g, p;
vi depth;
int n, logN; 

void dfs(int u){
	for(auto v: g[u]){
		if(depth[v] == -1){
			p[v][0] = u;	
			depth[v] = depth[u] + 1; 
			dfs(v);
		}
	}
}

void preprocess(int r){
	p = vvi(n, vi(logN, -1));
	depth = vi(n, -1);
	depth[r] = 0;
	dfs(r);
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