struct Edge{
	int v, rev, cap;
	Edge(int v, int cap, int rev): v(v), cap(cap), rev(rev){}
};

struct MaxFlow {
	vector<vector<Edge> > g;
	vector<int> level;
	queue<int> q;
	int n;
	MaxFlow(int n) : g(n), level(n), n(n){}

	void addEdge(int u, int v, int cap){
		Edge e(v, cap, int(g[v].size()));
		Edge r(u, 0, int(g[u].size()));
		g[u].push_back(e);
		g[v].push_back(r);
	}
	
	int buildLevelGraph(int s, int t){
		fill(level.begin(), level.end(), -1);
		queue<int> q;
		level[s] = 0;
		q.push(s);
		while(!q.empty()){
			int u = q.front();
			q.pop();
			for(auto e: g[u]){
				if(level[e.v] == -1 && e.cap){
					level[e.v] = level[u] + 1;
					if(e.v == t) return 1;
					q.push(e.v);
				}
			}
		}
		return 0;	
	}

	int blockingFlow(int s, int t, int f){
		if(s == t || !f) return f;
		int fu = 0;
		for(auto& e: g[s]){
			if(e.cap && level[e.v] == level[s] + 1){
				int mincap = blockingFlow(e.v, t, min(e.cap, f - fu));
				g[e.v][e.rev].cap += mincap;
				e.cap -= mincap;
				fu += mincap;
			}
		}
		if(!fu) level[s] = -1;
		return fu;
	}

	int maxflow(int s, int t){
		int flow = 0;
		while(buildLevelGraph(s, t))
			flow += blockingFlow(s, t, INF);
		return flow;
	}
};