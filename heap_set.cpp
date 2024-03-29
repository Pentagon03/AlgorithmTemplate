//max set, first:val, second:id
struct Data{
	int val, id;
	Data(int a=-1,int b=-1){val=a;id=b;}
	bool operator<(const Data x) const{
		return val<x.val; //change this to > for min set
	}
	bool operator==(const Data x) const{
		return val==x.val;
	}
};
const Data FAIL = Data();
struct heap_set{
	priority_queue<Data> iq,dq;
	void add(Data x){ iq.push(x); }
	void del(Data x){ dq.push(x); }
	void upd(){
		while(!dq.empty()){
			if(iq.empty()) dq.pop();
			else{
				if(iq.top()<dq.top()) dq.pop();
				else if(iq.top()==dq.top()) dq.pop(), iq.pop();
				else break;
			}
		}
	}
	bool empty(){upd(); return iq.empty();}
	void pop(){if(!empty()) iq.pop();}
	const Data top(){
		if(!empty()) return iq.top();
		return FAIL;
	}
};
