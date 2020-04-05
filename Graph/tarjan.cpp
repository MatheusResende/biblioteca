struct tarjan{
	vvi g;
	vi components, vis, dfs_low;
	stack<int> st;
	int dfs_cnt = 0, SCC_cnt = 0, n;  

	tarjan(vvi g): g(g){
		n = g.size();
		components = vi(n);
		vis = vi(n);
		dfs_low = vi(n);
	}
	
	void dfs(int u){
		int dfs_num = dfs_low[u] = dfs_cnt++;
		vis[u] = 1;
		st.push(u);
		for(auto v: g[u]){
			if(!vis[v])
				dfs(v);
			dfs_low[u] = min(dfs_low[u], dfs_low[v]);	
		}
		if(dfs_low[u] == dfs_num){
			while(1){
				int v = st.top();
				st.pop();
				dfs_low[v] = INF;
				components[v] = SCC_cnt;
				if(v == u) break;
			}
			SCC_cnt++;
		}
	}
	
	vi solve(){
		for(int i = 0; i < n; i++)
			if(!vis[i])
				dfs(i);
		return components;
	}
};