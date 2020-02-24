//Hash

const ll m1 = 1e9 + 7, m2 = 1e9 + 9;
vector<ll> v1, v2;

void precompute(ll p, int MAX_SZ){
	v1 = vector<ll>(MAX_SZ);
	v2 = vector<ll>(MAX_SZ);
	ll p1 = 1, p2 = 1;
	for(int i = 0; i < MAX_SZ; i++){
		v1[i] = p1;
		v2[i] = p2;
		p1 = (p1 * p) % m1;
		p2 = (p2 * p) % m2;
	}
}

struct Hash{
	vector<ii> h;
	
	Hash(string &s){
		if(!s.size()) return;
		h = vector<ii>(s.size());
		pair<ll, ll> c_hash = {0, 0};
		h[0] = c_hash;
		for(int i = 0; i < s.size(); i++){
			c_hash.f = (c_hash.f + (s[i] - 'a' + 1) * v1[i]) % m1;
			c_hash.s = (c_hash.s + (s[i] - 'a' + 1) * v2[i]) % m2;
			h[i] = c_hash;
		}
	}

	ii getHash(int l, int r){
		if(!h.size()) return {0, 0};
		ll r1 = h[r].f, r2 = h[r].s;
		if(l){
			r1 = (r1 - h[l - 1].f + m1) % m1;
			r2 = (r2 - h[l - 1].s + m2) % m2;
			int p = v1.size() - l - 1;
			r1 = (r1 * v1[p]) % m1;
			r2 = (r2 * v2[p]) % m2;
		}
		else{
			r1 = (r1 * v1.back()) % m1;
			r2 = (r2 * v2.back()) % m2;
		}
		return {r1, r2};
	}
};

precompute(1e8 + 7, SIZE);