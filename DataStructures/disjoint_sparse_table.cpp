//Disjoint Sparse Table
//build O(n log n)
//query O(1)
//works for any associative function

#define MAXN 1000010
#define MAXPOWN (1 << 20)
#define LOGN 21

struct sparseTable{
	int n, h;
	int table[LOGN][MAXPOWN];
	vi v;
	
	sparseTable(vi v1){
		v = v1;
		h = 32 - __builtin_clz(v1.size());
		n = (1 << h);
		v.resize(n);
		build(0, 0, n);
	}
	
	void build(int level, int l, int r){
		int m = (l+r)/2;
	  
		table[level][m] = v[m];
		for(int i = m-1; i>=l; i--)
			table[level][i] = table[level][i+1] + v[i];
		
		table[level][m+1] = v[m+1];
		for(int i = m+2; i<r; i++)
			table[level][i] = table[level][i-1] + v[i];
		
		if(l + 1 != r){
			build(level+1, l, m);
			build(level+1, m, r);
		}
	}

	int query(int x, int y){
		if(x == y) return v[x];
		int k2 = 31 - __builtin_clz(x^y);
		int lev = h - 1 - k2;
		int ans = table[lev][x];
		if(y % (1<<k2))
			ans += table[lev][y];
		return ans;
	}
};