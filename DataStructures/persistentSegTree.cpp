//Persistent SegTree
//Build  O(n)
//Update O(log n)
//Query  O(log n)
const int MAX = 200010, UPD = 75000 * 3, LOG = 20;
const int MAXS = 4*MAX+UPD*LOG;

struct segTree{
	ll seg[MAXS];
	int L[MAXS], R[MAXS], cnt = 0;
	int n;

	segTree(int n_){
		n = n_;
		build(cnt++, 0, n-1);
	}
	
	ll build(int r, int ss, int se) {
		if (ss == se) return seg[r] = 0;
		L[r] = cnt++, R[r] = cnt++;
		int m = (ss+se)/2;
		return seg[r] = build(L[r], ss, m) + build(R[r], m+1, se);
	}
	
	ll query(int r, int ss, int se, int qs, int qe) {
		if (qe < ss || se < qs) return 0;
		if (qs <= ss && se <= qe) return seg[r];
		int m = (ss+se)/2;
		return query(L[r], ss, m, qs, qe) + query(R[r], m + 1, se, qs, qe);
	}
	
	ll query(int r, int qs, int qe) {
		return query(r, 0, n-1, qs, qe);
	}
	
	void update(int nr, int r, int ss, int se, int pos, ll v) {
		if(ss == se){
			seg[nr] = sum(seg[r], v);
			return;
		}
		int m = (ss+se)/2;
		L[nr] = L[r];
		R[nr] = R[r];
		if(pos <= m)
			update(L[nr] = cnt++, L[r], ss, m, pos, v);
		else
			update(R[nr] = cnt++, R[r], m+1, se, pos, v);
		seg[nr] = seg[L[nr]] + seg[R[nr]];
	}
	
	int update(int r, int pos, ll v){
		int idx = cnt++;
		update(idx, r, 0, n-1, pos, v);
		return idx;
	}
};