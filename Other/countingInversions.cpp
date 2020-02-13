//Count Inversions O(nlog n)

ll merge(vi &a, vi &b, int l, int r){
	ll mid = (l + r) / 2, cnt = 0, _l = l, _r = mid + 1, i;
	for(i = l; i <= r; i++) b[i] = a[i];
	for(i = l; i <= r; i++){
		if((_r > r || b[_l] <= b[_r]) && !(_l > mid))
			a[i] = b[_l++];
		else{
			a[i] = b[_r++];
			cnt += mid - _l + 1;
		}
	}
	return cnt;
}

ll count_inversions(vi &a, vi &b, int l, int r){
	if(l == r) return 0;
	int mid = (r + l) / 2;
	return count_inversions(a, b, l, mid) + count_inversions(a, b, mid + 1, r) + merge(a, b, l , r);
}