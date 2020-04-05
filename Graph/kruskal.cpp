struct edge{
    ll a,b,w;
    bool operator<(edge e)const{
        return w < e.w;
    }
};

int uf[MAX], sz[MAX];

int find(int x){
    if(uf[x]<0)
        return x;
    return uf[x]=find(uf[x]);
}

void merge(int x, int y){
	x = find(x);
	y = find(y);
	if(sz[x] > sz[y]) swap(x, y);
	uf[x] = y;
	sz[y] += sz[x];
}

ll kruskal(int n, vector<edge> &edges){
	fill(uf, uf + n, -1);
	fill(sz, sz + n, 1);
	sort(edges.begin(), edges.end());
	ll res = 0;
	for(auto e: edges){
		int ga = find(e.a);
		int gb = find(e.b);
		if(ga != gb){
			merge(ga, gb);
			res += e.w;
		}
	}
	return res;
}