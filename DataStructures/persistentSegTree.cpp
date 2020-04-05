int lastV = 0;

struct Vertex {
    int l, r;
    int value;
	Vertex(): l(0), r(0), value(0){};
    Vertex(int val) : l(0), r(0), value(val) {}
    Vertex(int l, int r, int val) : l(l), r(r), value(val) {}
} nodes[MAX];

int build(int ss, int se) {
    if (ss == se){
        nodes[++lastV] = Vertex(0);
		return lastV;
	}
    int mid = (ss + se) / 2;
	int l = build(ss, mid);
	int r = build(mid + 1, se);
    nodes[++lastV] = Vertex(l, r, nodes[l].value + nodes[r].value);
	return lastV;
}

int query(int x, int ss, int se, int l, int r) {
    if (l > r) return 0;
    if (l == ss && se == r) return nodes[x].value;
    int mid = (ss + se) / 2;
    return query(nodes[x].l, ss, mid, l, min(r, mid))
         + query(nodes[x].r, mid+1, se, max(l, mid+1), r);
}

int update(int x, int ss, int se, int pos, int new_val) {
	if(ss == se){
		nodes[++lastV] = Vertex(new_val);
		return lastV;
	}
	int l = nodes[x].l, r = nodes[x].r;
	int idx = ++lastV, mid = (ss + se) / 2;
	if(pos <= mid) l = update(l, ss, mid, pos, new_val);
	if(pos > mid) r = update(r, mid + 1, se, pos, new_val);
	nodes[idx] = Vertex(l, r, nodes[l].value + nodes[r].value);
	return idx;
}