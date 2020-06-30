struct longNum{
	vi a;
	const int base = 1000000000;

	int print(){
		printf ("%d", a.empty() ? 0 : a.back());
		for (int i = (int)a.size() - 2; i >= 0; --i)
		printf ("%09d", a[i]);
		printf("\n");
	}
	
	void set(string s){
		for (int i = (int)s.length(); i > 0; i -= 9){
			if (i < 9)
				a.push_back (atoi (s.substr (0, i).c_str()));
			else
				a.push_back (atoi (s.substr (i-9, 9).c_str()));
		}
	}
	
	void operator+=(const longNum &b){
		int carry = 0;
		for (size_t i=0; i<max(a.size(),b.a.size()) || carry; ++i) {
			if (i == a.size())
				a.push_back (0);
			a[i] += carry + (i < b.a.size() ? b.a[i] : 0);
			carry = a[i] >= base;
			if (carry)  a[i] -= base;	
		}
	}
};