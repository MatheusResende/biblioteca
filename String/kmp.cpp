//KMP string matching O(n + m)

vi preprocess(string &S){
	vi p(S.size());
	int i = 0, j = 0;
	while(i < S.size()){
		while(j > 0 && S[i] != S[j]) j = p[j - 1];
		if(S[i] == S[j] && i != j) j++;
		p[i++] = j;
	}
	return p;
}

void kmp(string P, string T){
	vi p = preprocess(P);
	int i = 0, j = 0;
	while(i < T.size()){
		while(j > 0 && T[i] != P[j]) j = p[j - 1];
		if(T[i] == P[j]) j++;
		if(j == P.size()){
			printf("P found at index %d\n", i - j + 1);
			j = p[j - 1];
		}
		i++;
	}
}