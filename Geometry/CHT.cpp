struct ConvexHullTrick{
	//To get min change only the lambdaFunction on getMax
	//Assumes decreasing m to consider increasing take dot > 0
	//Beware with overflow on dot and cross.
	vector<pt> normal, hull;  
	
	//y = mx + n
	void addLine(coord_t m, coord_t n){
		pt p(m, n);
		while(!normal.empty() && pt::dot(normal.back(), p - hull.back()) < 0 ){
			normal.pop_back();
			hull.pop_back();
		}
		if(!hull.empty()) normal.push_back(pt::rotate90degrees(p - hull.back()));
		hull.push_back(p);
	}
	
	coord_t getMax(coord_t x){
		pt pq(x, 1);
		auto it = lower_bound(normal.begin(), normal.end(), pq, [](pt a, pt b){return pt::cross(a, b) < EPS;});
		return pt::dot(pq, hull[it - normal.begin()]);
	}
};
