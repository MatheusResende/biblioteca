//minQueue

struct minQueue{
	int l, r;
	deque<ii> d;
	minQueue(){ l = 1; r = 0;}
	void push(int v){
		while(!d.empty() && d.back().first >= v)
			d.pop_back();
		d.push_back({v, ++r});
	}
	
	void pop(){
		if(!d.empty() && d.front().second == l++)
			d.pop_front();
	}
	
	int getMin(){
		return d.front().first;
	}
};