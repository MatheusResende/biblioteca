string reverse_polish(string str){
	map<char, int> mp;
	mp['('] = 0;
	mp['|'] = 1;
	mp['&'] = 2;
	mp['='] = 3;
	mp['>'] = 3;
	mp['<'] = 3;
	mp['+'] = 4;
	mp['-'] = 4;
	mp['*'] = 5;
	mp['/'] = 5;
	mp['^'] = 6;
	string res;
	stack<int> s;
	for(auto c: str){
		if(c == ')'){
			while(s.top() != '('){
				res.push_back(s.top());
				s.pop();
			}
			s.pop();
		}
		else if(c == '('){
			s.push(c);
		}
		else if(mp.count(c)){
			while(!s.empty() && mp[s.top()] >= mp[c]){
				res.push_back(s.top());
				s.pop();
			}
			s.push(c);
		}
		else
			res.push_back(c);
	}
	while(!s.empty()){
		res.push_back(s.top());
		s.pop();
	}
	return res;
}