//segTree
#define left(x) (x << 1)
#define right(x) ((x << 1) + 1)

class segTree{
	vector<int> tree, lazy;
	public:
		segTree(int n, vector<int> v){
			tree.assign(n * 4, 0); 
			lazy.assign(n * 4, 0);
			build(1, 1, v.size(), v);
		}	
		
		void build(int idx, int ss, int se, vector<int>& v){
			if(ss == se){
				tree[idx] = v[ss - 1];
				return;
			}
			int mid = (ss + se) / 2;
			build(left(idx), ss, mid, v);
			build(right(idx), mid + 1, se, v);
			tree[idx] = tree[left(idx)] + tree[right(idx)];
		}
		
		void update(int idx, int ss, int se, int us, int ue, int v){
			propagate(idx, ss, se);
			if(ss > ue || se < us) return;
			if(us <= ss && se <= ue){
				if(ss != se){
					lazy[left(idx)] += v;
					lazy[right(idx)] += v;
				}
				tree[idx] += v * (se - ss + 1);
			}
			else{
				int mid = (ss + se) / 2;
				update(left(idx), ss, mid, us, ue, v);
				update(right(idx), mid + 1, se, us, ue, v);
				tree[idx] = tree[left(idx)] + tree[right(idx)];
			}
		}
		
		int query(int idx, int ss, int se, int qs, int qe){
			propagate(idx, ss, se);
			if(ss > qe || se < qs) return 0;
			if(qs <= ss && se <= qe)
				return tree[idx]; 
			int mid = (ss + se) / 2;
			return query(left(idx), ss, mid, qs, qe) + query(right(idx), mid + 1, se, qs, qe);
		}
		
		void propagate(int idx, int ss, int se){
			if(lazy[idx]){
				tree[idx] += (se - ss + 1) * lazy[idx];
				if(ss != se){
					lazy[left(idx)] += lazy[idx];
					lazy[right(idx)] += lazy[idx];
				}
				lazy[idx] = 0;
			}			
		}
};