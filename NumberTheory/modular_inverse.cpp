//Modular_inverse

ll modular_inverse(ll a, ll m){
	ll x, y;
	if(extended_euclidean(a, m, x, y) > 1) return -1;
	return (x % m + m) % m;
}