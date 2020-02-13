
//Hash
ll computeHash(string &s, int p, int m){
	ll res = 0;
	ll p_pow = 1;
	for(auto c: s){
		res = (res + (c - 'a' + 1) * p_pow) % m;
		p_pow *= p;
	}
	return res;
}

ii getHashPair(){
	int p1 = computeHash(s, p, 1e9 + 7);
	int p2 = computeHash(s, p, 1e9 + 9);
	return {p1, p2};
}