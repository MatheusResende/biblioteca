// Knuth's dp optimization
// dp[i][j] = min(dp[i][k-1] + dp[k+1][j]) + C(i, j)
// necessary condition: C(i, j - 1) <= C(i, j) <= C(i + 1, j)
// complexity: O(m^2)

void knuth(){
	for(int i = 0; i <= m; i++){
		opt[i][i] = i;
		dp[i][i] = 0;
	}
	for(int i = 1; i <= m; i++){
		for(int j = 0; i + j <= m; j++){
			int l = j, r = i + j;
			dp[l][r] = INF; 
			for(int k = opt[l][r - 1]; k <= opt[l + 1][r]; k++){
				int res = 0;
				if(k > l) res += dp[l][k - 1];
				if(k < r) res += dp[k][r];
				if(res < dp[l][r]){
					dp[l][r] = res;
					opt[l][r] = k;
				}
			}
			dp[l][r] += C(l, r);
		}
	}
}