//geometry
typedef ll coord_t;
//typedef double coord_t;

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
	static pt rotate90degrees(const pt p){return pt(-p.y, p.x);}
};

struct seg{
	pt p, q;
	int id;
	seg(){}
	seg(pt p, pt q): p(p), q(q){}
	seg(pt p, pt q, int id): p(p), q(q), id(id){}
	double get_y(double x) const {
        if (abs(p.x - q.x) < EPS)
            return p.y;
        return p.y +(q.y - p.y) * (x-p.x) / (q.x - p.x);
    }
};

bool operator<(const seg& a, const seg& b){
    double x = max(min(a.p.x, a.q.x), min(b.p.x, b.q.x));
    return a.get_y(x) < b.get_y(x) - EPS;
}

double SegpointDist(seg s, pt c){
	if(s.p == s.q) return sqrt(pt::sqrdist(s.p,c));
	if(pt::dot(s.p, s.q, c) < EPS)return sqrt(pt::sqrdist(s.p,c));
	if(pt::dot(s.q, s.p, c) < EPS)return sqrt(pt::sqrdist(s.q,c));
	return pt::cross(s.p, s.q, c) / sqrt(pt::sqrdist(s.p,s.q));
}

bool onSegment(pt p, seg s){
	return (SegpointDist(s, p) < EPS);
}

bool intersect1d(coord_t l1, coord_t r1, coord_t l2, coord_t r2) {
    if (l1 > r1) swap(l1, r1);
    if (l2 > r2) swap(l2, r2);
    return max(l1, l2) <= min(r1, r2) + EPS;
}

int sgn(double x) {
    return abs(x) < EPS ? 0 : x > 0 ? +1 : -1;
}

bool intersects(const seg& a, const seg& b){
    return intersect1d(a.p.x, a.q.x, b.p.x, b.q.x) &&
           intersect1d(a.p.y, a.q.y, b.p.y, b.q.y) &&
           sgn(pt::cross(a.p, a.q, b.p)) * sgn(pt::cross(a.p, a.q, b.q)) <= 0 &&
           sgn(pt::cross(b.p, b.q, a.p)) * sgn(pt::cross(b.p, b.q, a.q)) <= 0;
}

pt findIntersection(seg a, seg b){
	double a1 = a.q.y - a.p.y , b1 = a.p.x - a.q.x, c1 =  a1 * a.p.x + b1 * a.p.y;
	double a2 = b.q.y - b.p.y , b2 = b.p.x - b.q.x, c2 =  a2 * b.p.x + b2 * b.p.y;
	double det = a1 * b2 - a2 * b1;
	return pt( (b2 * c1 - b1 * c2) / det, (a1 * c2 - a2 * c1) / det);
}

//Determine if a point is inside a convex polygon
//O(log(n))
//v is a convexHull with v[0] having the smallest x
//Do not addimits colinear points on convex hull
bool isInside(vector<pt> &v, pt p){
	int n = v.size();
	if(SegpointDist(seg(v[0], v[n - 1]), p) < EPS) return true;
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

//Given a set of segments search for two segments which intersects
//O(n log n)
ii findIntersection(vector<seg> v){
	int n = v.size();
	vector<tuple<int, int, int>> event(2 * n);
	for(int i = 0; i < n; i++){
		v[i].id = i;
		event[2*i]   = {min(v[i].p.x, v[i].q.x), 0, i};
		event[2*i+1] = {max(v[i].p.x, v[i].q.x), 1, i};
	}
	sort(event.begin(), event.end());
	
	set<seg> s;
	vector<set<seg>::iterator> where(n);
	auto prev = [&](set<seg>::iterator it){
		return it == s.begin() ? s.end() : --it;
	};
	auto next = [&](set<seg>::iterator it){
		return ++it;
	};
	for(auto e: event){
		int t = get<1>(e);
		int id = get<2>(e);
		if(t){
			set<seg>::iterator nxt = next(where[id]), prv = prev(where[id]);
			if(nxt != s.end() && prv != s.end() && intersects(*nxt, *prv))return {nxt->id, prv->id};
			s.erase(v[id]);
		}
		else{
			set<seg>::iterator nxt = s.lower_bound(v[id]), prv = prev(nxt);
			if(nxt != s.end() && intersects(*nxt, v[id])) return {nxt->id, id};
			if(prv != s.end() && intersects(*prv, v[id])) return {prv->id, id};
			where[id] = s.insert(nxt, v[id]);
		}
	}
	return {-1, -1};
}
