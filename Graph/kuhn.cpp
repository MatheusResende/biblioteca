//fast kuhn bipartite matching
//Expected runtime O(sqrt(V) * E)
int n, m;
vi vis, matchA, matchB;
vvi g;

int dfs(int u){
	for(auto v: g[u]){
		if(vis[v]) continue;
		vis[v] = 1;
		if(matchB[v] == -1 || dfs(matchB[v])){
			matchA[u] = v;
			matchB[v] = u;
			return 1;
		}
	}
	return 0;
}

int bpm(){
	int aux = 1, res = 0;
	matchA = vi(n, -1);
	matchB = vi(m, -1);
	while(aux){
		vis = vi(m, 0);
		aux = 0;
		for(int i = 0; i < n; i++){
			if(matchA[i] == -1 && dfs(i)){
				res++;
				aux = 1;
			}
		}
	}
	return res;
}