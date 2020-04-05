void divideConquer(int l, int r, int optl, int optr){
	if(l > r) return;
	int mid = (l + r)/ 2;
	ii best = {INF, -1};
	for(int k = optl, k <= min(mid, optr); k++)
		best = min(best, {old_dp[k] + C(k, mid), k});
	dp[mid] = best.f;
	int opt = best.s;
	divideConquer(l, mid - 1, optl, opt);
	divideConquer(mid + 1, r, opt, optr);
}