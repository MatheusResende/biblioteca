//Extended_euclidean

ll extended_euclidean(ll a, ll b, ll &x, ll &y){
	if(b == 0){
		x = 1;
		y = 0;
		return a;
	}
	ll res = extended_euclidean(b, a % b, x, y);
	ll x1 = y, y1 = x - (a / b) * y;
	x = x1; y = y1;
	return res;
}