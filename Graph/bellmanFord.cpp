struct edge{
	int a, b, w;
};

vi bellmanFord(int s, int n, int m, vector<edge> &e){
	vi d(n, INF);
    d[s] = 0;
    for (int i = 0; i < n - 1; i++){
        bool flag = false;
        for (int j = 0; j < m; j++){
            if (d[e[j].a] < INF){
                if (d[e[j].b] > d[e[j].a] + e[j].w){
                    d[e[j].b] = d[e[j].a] + e[j].w;
                    flag = true;
                }
			}
		}
        if (!flag) break;
    }
    return d;
}