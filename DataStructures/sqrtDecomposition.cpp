//sqrtDecomposition

struct sqrtDecomposition{
	int n, m;
	vi a; 
	vvi b;
	
	sqrtDecomposition(vi &v){
		a = v;
		n = a.size();
		m = sqrt(n) + 1;
		b = vvi(m);
		for(int i = 0; i < n; i++)
			b[i/m].push_back(a[i]);
		for(int i = 0; i < m; i++)
			sort(b[i].begin(), b[i].end());
	}
	
	int query(int l, int r, int v){
		int bl = l/m, br = r/m, res = 0;
		if(bl == br){
			for(int i = l; i <= r; i++)
				res += (a[i] < v);
		}
		else{
			for(int i = l ; i < (bl + 1) * m; i++)
				res += (a[i] < v);
			for(int i = bl + 1; i < br; i++)
				res += upper_bound(b[i].begin(), b[i].end(), v-1) - b[i].begin(); 
			for(int i = br * m; i <= r; i++)
				res += (a[i] < v);
		}
		return res;
	}
	
	void update(int idx, int v){
		int bc = idx/m;
		(*lower_bound(b[bc].begin(), b[bc].end(), a[idx])) = v;
		a[idx] = v;
		sort(b[bc].begin(), b[bc].end());
	}
};