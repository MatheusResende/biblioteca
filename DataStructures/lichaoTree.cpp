//Lichao Tree
//addLine O(log n)
//getY O(log n)
void addLine(int id, int l, int r, ii nl){
	int m = (l + r)/2;
	bool f1 = f(nl, l) < f(line[id], l);
	bool f2 = f(nl, m) < f(line[id], m);
	if(f2) swap(line[id], nl);
	if(l + 1 == r)return;
	if(f1 != f2)addLine(id * 2, l, m, nl);
	else addLine(id * 2 + 1, m, r, nl);
}

ll getY(int id, int l, int r, int x){
	if(l + 1 == r)return f(line[id], x);
	int m = (l + r)/2;
	if(x < m) return min(f(line[id], x), getY(id * 2, l, m, x));
	return min(f(line[id], x), getY(id * 2+1, m, r, x));
}