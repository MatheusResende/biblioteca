//Implicit SegmentTree

struct node{
	node *left = NULL, *right = NULL;
	int lazy = 0, v = 0;
};

struct SegTree{
	
	node* create_root(){
		return new node();
	}
	
	void propagate(node *root, int ss, int se){
		if(root->lazy){
			root->v = se - ss + 1 - root->v;
			if(ss != se){
				if(!root->left) root->left = new node();
				if(!root->right) root->right = new node();
				root->left->lazy ^= 1;
				root->right->lazy ^= 1;
			}
			root->lazy = 0;
		}
	}
	
	void update(node * root, int ss, int se, int us, int ue){
		propagate(root, ss, se);
		if(ue < ss || se < us) return;
		if(us <= ss && se <= ue){
			root->v = se - ss + 1 - root->v;
			if(ss != se){
				if(!root->left) root->left = new node();
				if(!root->right) root->right = new node();
				root->left->lazy ^= 1;
				root->right->lazy ^= 1;
			}
		}
		else{
			if(!root->left) root->left = new node();
			if(!root->right) root->right = new node();
			int mid = (ss + se)/2;
			update(root->left, ss, mid, us, ue);
			update(root->right, mid+1, se, us, ue);
			root->v = root->left->v + root->right->v;  
		}
	}
	
	int query(node *root, int ss, int se, int qs, int qe){
		propagate(root, ss, se);
		if(qe < ss || se < qs) return 0;
		if(qs <= ss && se <= qe) return root->v;
		if(!root->left) root->left = new node();
		if(!root->right) root->right = new node();
		int mid = (ss + se)/2;
		return query(root->left, ss, mid, qs, qe) + query(root->right, mid+1, se, qs, qe);
	}
}; 