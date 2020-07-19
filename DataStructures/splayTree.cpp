//Implicit Splay Tree
struct node{
	int val, sum, lazy, rev, size;
	struct node *l, *r, *p;	
};
typedef node* pnode;

pnode init(int v){
	pnode t = new node(); 
	t->l = t->r = t->p = NULL;
	t->val = t->sum = v;
	t->size = 1;
	t->lazy = t->rev = 0;
	return t;
}

int sz(pnode t){
    return t?t->size:0;
}

void upd_sz(pnode t){
	if(t) t->size = sz(t->l) + sz(t->r) + 1;
}

void reset(pnode t){
	if(t)t->sum = t->val;
}

void combine(pnode &t, pnode l, pnode r){
	if(!l || !r) return void(t = l? l:r);
	t->sum = l->sum + r->sum;
}

void lazy(pnode t){
	if(!t) return;
	if(t->lazy){
		t->val += t->lazy;
		t->sum += t->lazy * sz(t);
		if(t->l)t->l->lazy += t->lazy;
		if(t->r)t->r->lazy += t->lazy;
		t->lazy = 0;
	}
	if(t->rev){
		swap(t->l, t->r);
		if(t->l)t->l->rev ^= 1;
		if(t->r)t->r->rev ^= 1;
		t->rev = 0;
	}
}

void operation(pnode t){
    if(!t)return;
    reset(t);
    lazy(t->l);lazy(t->r);
    combine(t,t->l,t);
    combine(t,t,t->r);
	upd_sz(t);
}

void rotateLeft(pnode t){
	pnode p = t->p;
	p->r = t->l;
	if(t->l) t->l->p = p;
	t->p = p->p;
	if(p->p && p == p->p->l)p->p->l = t;
	if(p->p && p == p->p->r)p->p->r = t;
	p->p = t;
	t->l = p;
	operation(p);
	operation(t);
}

void rotateRight(pnode t){
	pnode p = t->p;
	p->l = t->r;
	if(t->r)t->r->p = p;
	t->p = p->p;
	if(p->p && p == p->p->l)p->p->l = t;
	if(p->p && p == p->p->r)p->p->r = t;
	p->p = t;
	t->r = p;
	operation(p);
	operation(t);
}

void splay(pnode t){
	if(!t)return;
	while(t->p){
		if(!t->p->p){
			if(t->p->l == t)rotateRight(t);
			else rotateLeft(t);
		}
		else{
			int type = 0;
			if(t->p->l == t) type++;
			if(t->p->p->l == t->p) type+=2;
			if(type == 0){
				rotateLeft(t->p);
				rotateLeft(t);
			}
			if(type == 1){
				rotateRight(t);
				rotateLeft(t);
			}
			if(type == 2){
				rotateLeft(t);
				rotateRight(t);
			}
			if(type == 3){
				rotateRight(t->p);
				rotateRight(t);
			}
		}
	}
}

void find(pnode &p, pnode t, int pos){
	if(pos == sz(t->l)){ 
		p = t, splay(p);
	}
	else if(pos < sz(t->l)) find(p, t->l, pos);
	else find(p, t->r, pos - sz(t->l) - 1);
}

void merge(pnode &t, pnode a, pnode b){
	lazy(a);lazy(b);
	if(!a || !b) t = (a)? a: b;
	else{
		find(t, a,sz(a)-1);
		t->r = b;
		if(b)b->p = t;
	}
	operation(t);
}

void split(pnode t, pnode &a, pnode &b, int v){
	lazy(t);
	if(!t) return void(a = b = NULL);
	if(v < 0){
		a = NULL;
		b = t;
		return;
	}
	find(a, t, v);
	b = a->r;
	a->r = NULL;
	if(b)b->p = NULL;
	operation(a);
	operation(b);
}

int range_query(pnode t,int l,int r){
    pnode L,mid,R;
    split(t,L,mid,l-1);
    split(mid,t,R,r-l);
    int ans = t->sum;
    merge(mid,L,t);
    merge(t,mid,R);
    return ans;
}

void range_update(pnode t,int l,int r,int val){
    pnode L,mid,R;
    split(t,L,mid,l-1);
    split(mid,t,R,r-l);
    t->lazy+=val;
    merge(mid,L,t);
    merge(t,mid,R);
}

void reverse(pnode t, int l, int r){
	pnode L,mid,R;
	split(t,L,mid,l-1);
	split(mid,t,R,r-l);
	t->rev^=1;
	merge(mid,L,t);
    merge(t,mid,R);
}