//Continuous ternarySearch
double ternarySearch(double l, double r){
	while(r-l > EPS){
		double m1 = l + (r-l)/3;
		double m2 = r - (r-l)/3;
		if(f(m1) > f(m2)) l = m1;
		else r = m2;
	}
	return f(l);
}