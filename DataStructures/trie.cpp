struct node{
	int cnt = 0;
	bool isLeaf = false; 
	node *next[26];
	node(){memset(next, 0, sizeof(next));}
};

void addWord(string s, node *cur){
	for(auto c: s){
		if(cur->next[c-'a'] == NULL)
			cur->next[c-'a'] = new node();
		cur->cnt++;
		cur = cur->next[c-'a'];
	}
	cur->cnt++;
	cur->isLeaf = true;
}