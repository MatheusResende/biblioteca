const int S = 800;//Block size

struct Query{
	int l, int r, int idx;
	bool operator<(Query q)const{
		return ii(l / S, r) < ii(q.l / S, q.r);
	}
 };
 
 vi MO(vector<Query> queries){
	int l = 0, r = -1;
	vi ans(queries.size());
	sort(queries.begin, queries.end());
	for(auto q: queries){
		while(q.l < l)add(--l);
		while(r < q.r)add(++r);
		while(l < q.l)remove(l++);
		while(q.r < r)remove(r--);
		ans[q.idx] = getAns();
	}
	return ans;
 }