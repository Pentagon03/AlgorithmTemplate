//first:val, second:id
struct heap_set{
	priority_queue<pii> iq,dq;
	void push(pii x){ iq.push(x); }
	void del(pii x){ dq.push(x); }
	void upd(){
		while(!dq.empty()){
			if(!iq.empty()) dq.pop();
			else{
				if(dq.top().first > iq.top().first) dq.pop();
				else if(dq.top().first == iq.top().first) dq.pop(), iq.pop();
				else break;
			}
		}
	}
	bool empty(){upd(); return iq.empty();}
	void pop(){if(!empty()) iq.pop();}
	pii top(){
		if(!empty()) return iq.top();
		return pii(-1,-1);
	}
};
