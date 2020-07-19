//Matrix Exponentiation
typedef vector<vector<ll>> matrix;

matrix matrix_mul(matrix a, matrix b){
	int n = a.size(), m = b[0].size(), p = b.size();
	matrix c(n, vector<ll>(m, 0));
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			for(int k = 0; k < p; k++)
				c[i][j] = (c[i][j]+a[i][k] * b[k][j]) % MOD;	
			//c[i][j] %= MOD;
		}
	}
	return c;
}

matrix matrix_exp(matrix m, ll exp){
	int d = m.size();
	matrix res = matrix(d, vector<ll>(d, 0));
	for(int i = 0; i < d; i++) res[i][i] = 1;
	while(exp){
		if(exp & 1LL)
			res = matrix_mul(m, res);
		m = matrix_mul(m, m);
		exp >>= 1LL;
	}
	return res;
}