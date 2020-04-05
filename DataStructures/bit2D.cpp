int tree[MAXN][MAXM];

int query(int x, int y){
	int res = 0;
	while(x){
		int y0 = y;
		while(y0){
			res += tree[x][y0];
			y0 -=(y0&-y0);
		}
		x -=(x&-x);
	}
	return res;
}

void update(int x, int y, int v){
	while(x < MAXN){
		int y0 = y;
		while(y0 < MAXM){
			tree[x][y0] += v;
			y0 +=(y0&-y0);	
		}
		x +=(x&-x);
	}
}

int readRectangle(int x1,int y1,int x2,int y2){
	int sum=0;
	if(x1>x2)
        swap(x1,x2);
	if(y1>y2)
	    swap(y1,y2);
	sum =query(x2,y2);
	sum-=query(x2,y1 -1);
	sum-=query(x1-1,y2);
	sum+=query(x1-1,y1-1);
	return sum;
}