struct Edge{
	int v, rev, cap;
	double cost;
	Edge(int v, int cap, double cost, int rev): v(v), cap(cap), cost(cost), rev(rev){}
};

struct minCostMaxFlow {
	vector<vector<Edge> > g;
	vector<int> parent;
	vector<double> dist;
	queue<int> q;
	int n;
	minCostMaxFlow(int n) : g(n), parent(n), dist(n), n(n){}

	void addEdge(int u, int v, int cap, double cost){
		Edge e(v, cap, cost, int(g[v].size()));
		Edge r(u, 0, -cost, int(g[u].size()));
		g[u].push_back(e);
		g[v].push_back(r);
	}
	
	int buildLevelGraph(int s, int t){
		fill(parent.begin(), parent.end(), -1);
		fill(dist.begin(), dist.end(), INF);
		queue<int> q;
		vector<int> inqueue(n, 0); 
		dist[s] = 0;
		q.push(s); 
		while(!q.empty()){
			int u = q.front();
			q.pop();
			inqueue[u] = 0;
			for(auto e: g[u]){
				if(e.v != s && e.cap && dist[u] + e.cost  < dist[e.v]){
					parent[e.v] = u; 
					dist[e.v] = dist[u] + e.cost;
					if(!inqueue[e.v]){
						inqueue[e.v] = 1;
						q.push(e.v);
					}
				}
			}
		}
		return (abs(dist[t] - INF) < EPS)? 0: 1;	
	}

	int blockingFlow(int s, int t, int f, double &cost){
		if(s == t || !f) return f;
		int fu = 0;
		for(auto& e: g[s]){
			if(e.cap && parent[e.v] == s){
				int mincap = blockingFlow(e.v, t, min(e.cap, f - fu), cost);
				g[e.v][e.rev].cap += mincap;
				e.cap -= mincap;
				fu += mincap;
				cost += mincap * e.cost;
			}
		}
		if(!fu) parent[s] = -1;
		return fu;
	}

	double minCost(int s, int t){
		int flow = 0;
		double cost = 0;
		while(buildLevelGraph(s, t))
			flow += blockingFlow(s, t, INF, cost);
		return cost;
	}
};