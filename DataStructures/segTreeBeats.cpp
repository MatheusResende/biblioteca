struct segTreeBeats{
	vector<ll> tree, max_v, smax_v, lazy;
	vi maxcnt;
	
	segTreeBeats(int n): tree(4*n), max_v(4*n), smax_v(4*n), maxcnt(4*n), lazy(4*n){};
		
	void fix(int p, int ss, int se){
		if(max_v[p*2] == max_v[p*2+1]){
			max_v[p] = max_v[p*2];
			maxcnt[p] = maxcnt[p*2] + maxcnt[p*2+1];
			smax_v[p] = max(smax_v[p*2], smax_v[p*2+1]);
		}
		if(max_v[p*2] < max_v[p*2+1]){
			max_v[p] = max_v[p*2+1];
			maxcnt[p] = maxcnt[p*2+1];
			smax_v[p] = max(max_v[p*2], smax_v[p*2+1]);
		}
		if(max_v[p*2] > max_v[p*2+1]){
			max_v[p] = max_v[p*2];
			maxcnt[p] = maxcnt[p*2];
			smax_v[p] = max(max_v[p*2+1], smax_v[p*2]);
		}
		tree[p] = tree[p*2]+tree[p*2+1];
	}
	
	void build(int p, int ss, int se, vi &v){
		if(ss == se){
			max_v[p] = tree[p] = v[ss];
			smax_v[p] = -INF;
			maxcnt[p] = 1;
		}
		else{
			int mid = (ss+se)/2;
			build(p*2, ss, mid, v);
			build(p*2+1, mid+1, se, v);
			fix(p, ss, se);
		}
	}
	
	void setMin(int p, int x){
		if(max_v[p] <= x)return;
		tree[p] -= maxcnt[p] *(ll) (max_v[p]-x);
		max_v[p] = x;
	}
	
	void setSum(int p, int ss, int se, ll x){
		if(x >= tree[p])
		tree[p] += (se - ss + 1) * x;
		max_v[p] += x;
		smax_v[p] += x;
	}
	
	void propagate(int p, int ss, int se){
		setSum(p, ss, se, lazy[p]);
		if(ss != se){
			lazy[2*p] += lazy[p];
			lazy[2*p+1] += lazy[p];
			setMin(2*p, max_v[p]);
			setMin(2*p+1, max_v[p]);
		}
		lazy[p] = 0;
	}
	
	void updateMin(int p, int ss, int se, int us, int ue, int x){
		if(ue < ss || se < us || max_v[p] <= x)return;
		if(us <= ss && se <= ue && smax_v[p] < x){
			setMin(p, x);
			return;
		}
		propagate(p, ss, se);
		int mid = (ss + se)/2;
		updateMin(p*2, ss, mid, us, ue, x);
		updateMin(p*2+1, mid+1, se, us, ue, x);
		fix(p, ss, se);
	}
	
	void add(int p, int ss, int se, int us, int ue, int x){
		if(ue < ss || se < us)return;
		if(us <= ss && se <= ue){
			setSum(p, ss, se, x);
			return;
		}
		propagate(p, ss, se);
		int mid = (ss + se)/2;
		add(p*2, ss, mid, us, ue, x);
		add(p*2+1, mid+1, se, us, ue, x);
		fix(p, ss, se);
	}
	
	ll query(int p, int ss, int se, int us, int ue){
		if(ue < ss || se < us)return 0ll;
		if(us <= ss && se <= ue)
			return tree[p];
		propagate(p, ss, se);
		int mid = (ss + se)/2;
		return query(p*2, ss, mid, us, ue) + query(p*2+1, mid+1, se, us, ue); 
	}
	
	ll queryMax(int p, int ss, int se, int us, int ue){
		if(ue < ss || se < us)return -INF;
		if(us <= ss && se <= ue)
			return max_v[p];
		propagate(p, ss, se);
		int mid = (ss + se)/2;
		return max(queryMax(p*2, ss, mid, us, ue), queryMax(p*2+1, mid+1, se, us, ue)); 
	}
};