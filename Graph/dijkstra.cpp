vi dijkstra(int s, vvii &g){
	int n = g.size();
	vi d(n, INF);
	d[s] = 0;
	priority_queue<ii> q;
	q.push(ii(0, s));
	while(!q.empty()){
		int dist = -q.top().first;
		int u = q.top().second;
		q.pop();
		if(dist > d[u])continue;
		for(auto p: g[u])
			if(d[u] + p.s < d[p.f]){
				d[p.f] = d[u] + p.s;
				q.push(ii(-d[p.f], p.f));
			}
	}
	return d;
}