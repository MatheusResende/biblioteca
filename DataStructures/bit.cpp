//BIT
struct BIT{
	int n;
	vi tree;

	BIT(int sz){
		n = sz + 1;
		tree = vi(n);
	}

	void update(int x,int v){
		while(x<=n){
			tree[x]+=v;	
			x+=(x&-x);
		}
	}

	int read(int x){
		int v=0;
		while(x>0){
			v+=tree[x];
			x-=(x&-x);	
		}
		return v;
	}
};

void updateRange(BIT &bit1, BIT &bit2, int l, int r, int v){
	bit1.update(l, v);
	bit1.update(r + 1, -v);
	bit2.update(l, (l - 1) * v);
	bit2.update(r + 1, -r * v);
}

int read(BIT &bit1, BIT &bit2, int x){
	return bit1.read(x) * x - bit2.read(x);
}