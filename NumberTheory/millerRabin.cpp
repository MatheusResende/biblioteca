//MillerRabin
//Complexity O(log^3 n)
//If n is 32bit use just the first four values of a
typedef unsigned long long int ull;

ull multiply(ull a, ull b, ull m){
	ull res = 0;
	while(b){
		if(b & 1ULL)
			res = (res + a) % m;
		a = (2 * a) % m;
		b /= 2;
	}
	return res;
}

ull binpower(ull a, ull n, ull mod) {
    ull res = 1;
    a %= mod;
    while (n) {
        if (n & 1)
            res = multiply(res, a, mod);
        a = multiply(a, a, mod);
        n >>= 1;
    }
    return res;
}

//return 1 if n is composite and 0 if it's probably prime
int composite(ull n, ull a, ull d, int sz) {
    ull x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return 0;
    for (int r = 1; r < sz; r++) {
        x = multiply(x, x, n);
        if (x == n - 1)
            return 0;
    }
    return 1;
};

//returns 1 if n is prime, else returns 0.
int MillerRabin(ull n) { 
    if (n < 2)
        return 0;
    int sz = 0;
    ull d = n - 1;
    while ((d & 1) == 0){
        d >>= 1;
        sz++;
    }
    for (ull a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a) return 1;
        if (composite(n, a, d, sz)) return 0;
    }
    return 1;
}