//Sparse Table
//Precompute O(nlogn)
//Query O(1)

const int MAX = 1e5+ 10, LOGN = 20;
int st[LOGN][MAX];

void precompute(vi &v){
	int n = v.size();
	for(int i = 0; i < n; i++)
		st[0][i] = v[i];
	for(int j = 1; j < LOGN; j++)
		for(int i = 0; i + (1 << j) <= n; i++)
			st[j][i] = min(st[j-1][i], st[j-1][i + (1<<(j-1))]);
}

int query(int l, int r){
	int j = 31 - __builtin_clz(r-l+1);
	return min(st[j][l], st[j][r-(1<<j)+1]);
}