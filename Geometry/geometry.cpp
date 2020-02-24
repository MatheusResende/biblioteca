//geometry
//typedef ll coord_t;
typedef double coord_t;

struct pt{
	coord_t x, y;
	pt(){}
	pt(coord_t x, coord_t y): x(x), y(y){}
	pt operator+(const pt &p)const{return pt(x + p.x, y + p.y);}
	pt operator-(const pt &p)const{return pt(x - p.x, y - p.y);}
	pt operator*(coord_t a)const{return pt(a * x, a * y);}
	bool operator==(const pt &p)const{return ((*this) - p).sqrlen() < EPS;}
	bool operator<(const pt &p)const{
		if(x < p.x - EPS) return true;
		if(abs(x - p.x) > EPS) return false;
		return y + EPS < p.y;
	}
	pt rotate(const double a)const{
		double s = sin(a), c = cos(a);
		return pt(x * c - y * s, x * s + y * c);
	}
	coord_t sqrlen(){return pt::dot(*this, *this);}
	static coord_t sqrdist(const pt &p1, const pt &p2){return pt(p1 - p2).sqrlen();}
	static coord_t dot(const pt &v1, const pt &v2){return v1.x * v2.x + v1.y * v2.y;}
	static coord_t dot(const pt &p1, const pt &p2, const pt &p3){return dot(p2-p1, p3-p1);}
	static coord_t cross(const pt &v1, const pt &v2){return v1.x * v2.y - v1.y * v2.x;}
	static coord_t cross(const pt &p1, const pt &p2, const pt &p3){return cross(p2-p1, p3-p1);}
};

typedef pair<pt, pt> seg;

double sqrSegpointDist(seg s, pt c){
	if(s.first == s.second) return pt::sqrdist(s.first,c);
	if(pt::dot(s.first, s.second, c) <= EPS)return pt::sqrdist(s.first,c);
	if(pt::dot(s.second, s.first, c) <= EPS)return pt::sqrdist(s.second,c);
	return (pt::cross(s.first, s.second, c) * pt::cross(s.first, s.second, c)) * 1.0 / pt::sqrdist(s.first,s.second);
}

//Determine if a point is inside a convex polygon
//O(log(n))
//v is a convexHull with v[0] having the smallest x
//Do not addimits colinear points on convex hull
bool isInside(vector<pt> &v, pt p){
	int n = v.size();
	if(sqrSegpointDist(seg(v[0], v[n - 1]), p) < EPS) return true;
	if(pt::cross(v[0], v[n - 1], p) > -EPS || pt::cross(v[0], v[1], p) < -EPS)return false;
	int l = 1, r = n - 2;
	while(l < r){
		int mid = (r + l + 1)/2;
		if(pt::cross(v[0], v[mid], p) > -EPS) l = mid;
		else r = mid - 1;
	}
	if(pt::cross(v[0], v[l], p) > -EPS && pt::cross(v[l], v[l + 1], p) > -EPS && pt::cross(v[l + 1], v[0], p) > -EPS)
		return true;
	return false;
}

//ConvexHull
//Return the vertices on the convexHull in counter-clockwise order  
//O(nlog n)
vector<pt> convexHull(vector<pt> &vet){
	int n = vet.size(), k = 0;
	vector<pt> H(2 * n);
	sort(vet.begin(), vet.end());
	for(int i = 0; i < n; i++){
		while (k >= 2 && pt::cross(H[k - 2], H[k - 1], vet[i]) < EPS) k--;
		H[k++] = vet[i];
	}
	for (int i = n - 2,t = k + 1; i >= 0; i--) {
		while (k >= t && pt::cross(H[k - 2], H[k - 1], vet[i]) < EPS) k--;
		H[k++] = vet[i];
	}
	H.resize(k-1);
	return H;
}

//polygon area
//O(n)
double area(vector<pt> &h){
	double res = h.back().x * h[0].y - h[0].x * h.back().y;
	for(int i = 1; i < h.size(); i++)
		res += h[i-1].x * h[i].y - h[i].x * h[i-1].y;
	return abs(res)/2;
}