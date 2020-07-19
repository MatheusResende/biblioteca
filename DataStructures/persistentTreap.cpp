//Persistent Implicit treap
//Expected complexity
//Query, Update, reverse, merge, split: O(log n)

typedef struct node{
    int prior,size,val,lazy,rev;
	ll sum;
    struct node *l,*r;
}node;
typedef node* pnode;

int sz(pnode t){
    return t?t->size:0;
}

void upd_sz(pnode t){
    if(t)t->size=sz(t->l)+1+sz(t->r);
}

void reset(pnode t){
    if(t) t->sum= t->val;
}


void lazy(pnode t){
    if(!t)return;
	if(t->lazy){
		t->val+=t->lazy;
		t->sum+=t->lazy*sz(t);
		if(t->l)t->l->lazy+=t->lazy;
		if(t->r)t->r->lazy+=t->lazy;
		t->lazy=0;
	}
	if(t->rev){
		swap(t->l, t->r);
		if(t->l)t->l->rev^=1;
		if(t->r)t->r->rev^=1;
		t->rev=0;
	}
}

void combine(pnode& t,pnode l,pnode r){
    if(!l || !r)return void(t = l?l:r);
	t->sum = l->sum + r->sum;
}

void operation(pnode t){
    if(!t)return;
    reset(t);
	lazy(t->l);lazy(t->r);
	combine(t,t->l,t);
    combine(t,t,t->r);
}

pnode init(int val){
    pnode ret = (pnode)malloc(sizeof(node));
	ret->prior = rand();ret->size=1;
    ret->sum = ret->val = val;
	ret->l = ret->r = NULL;
	ret->lazy = ret->rev = 0;
    return ret;
}

pnode copyNode(pnode t){
	pnode c = init(t->val);
	c->l = t->l;
	c->r = t->r;
	return c;
}

void split(pnode t,pnode &l,pnode &r,int pos,bool copy = false,int add=0){
    if(!t)return void(l=r=NULL);
    int curr_pos = add + sz(t->l);
	lazy(t);
    if(curr_pos<=pos){
		l = (copy)? copyNode(t): t;
        split(t->r,l->r,r,pos,copy,curr_pos+1);
		upd_sz(l);
		operation(l);
	}
	else{
		r = (copy)? copyNode(t): t;
        split(t->l,l,r->l,pos,copy,add);
		upd_sz(r);
		operation(r);
	}
}

void merge(pnode &t,pnode l,pnode r, bool copy = false){
	lazy(l);lazy(r);
    if(!l || !r) t = (copy)? copyNode(l?l:r): (l?l:r);
    else if(l->prior>r->prior)merge(l->r,l->r,r, copy),t=(copy)? copyNode(l): l;
    else    merge(r->l,l,r->l, copy),t = (copy)? copyNode(r): r;
    upd_sz(t);
    operation(t);
}

ll range_query(pnode t,int l,int r){
    pnode L,mid,R;
    split(t,L,mid,l-1,true);
    split(mid,t,R,r-l,true);
    ll ans = t->sum;
    merge(mid,L,t, true);
    merge(t,mid,R, true);
    return ans;
}

void range_update(pnode &t, pnode s,int l,int r,int val){
    pnode L,mid,R;
    split(s,L,mid,l-1,true);
    split(mid,s,R,r-l,true);
    s->lazy+=val;
    merge(mid,L,s,true);
    merge(t,mid,R,true);
}

void reverse(pnode &t, pnode s, int l, int r){
	pnode L,mid,R;
    split(s,L,mid,l-1,true);
    split(mid,s,R,r-l,true);
    s->rev^=1;
    merge(mid,L,s,true);
    merge(t,mid,R,true);
}