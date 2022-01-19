#include <iostream>

namespace polymorphism_with_template_and_virtual{
	//template version
	template<typename X>
	class Ct{
		X mem;
		public:
			X f();
			int g();
			void h(X);
	};
	
	template<>//explicit specialization
	class Ct<A>{
		A* mem;
		public:
			A f();
			int g();
			void h(A);
			void k(int);
	};
	
	Ct<A> cta;//specialization for A
	Ct<B> ctb;//specialization for B
	
	//virtual version
	class X{};
	class Cx{
		X mem;
		public:
			virtual X& f();
			virtual int g();
			virtual void h(X&);
	};
	
	class DA: public Cx{
		public:
			X& f();
			int g();
			void h(X&);
	};
	class DB: public Cx{
		DB* p;
		public:
			X& f();
			int g();
			void h(X&);
			void k(int);
	};
	Cx& cxa{*new DA};//interface for DA
	Cx& cxb{*new DB};//intetface for DB
}


namespace Red_Black_Tree{
	//try 1 to solve_사용자가 Node_base의 연산과 결과트리구조를 알아야한다는 단점. 
	template<typename N>
	struct Node_base{
		N* left_child;
		N* right_child;
		Node_base();
		
		void add_left(N* p){
			if(left_child==nullptr)
				left_child=p;
			else{}
				//...
		}
		//...
	};
	//try 1 end
	
	//try 2 Cool
	template<typename N>
	struct Node_base{
		static_assert(Totally_ordered<X>(), "Node_base: N must have a <");
		N* left_child;
		N* right_child;
		Balancing_info bal;
		
		Node_base();
		void insert(N& n){
			if(n<left_child){
				//...
			} else{
				//...
			}
		}
		//...
	};
	
	template<typename Val, typename Balance>
	struct Search_node: public Node_base<Search_node<Val, Balance>, Balance>{
		Val val;
		Search_node(Val v): val(v){}
	};
	
	template<typename N, typename Balance>
	struct Node_base: Balance{
		N* left_child;
		N* right_child;
		
		Node_base();
		void insert(N& n){
			if(this->compare(n, left_child)){
				//...
			} else{
				//...
			}
		}
		//...
	};
	
	//try 2 end
	
	template<typename Val>
	struct Node: Node_base<Node<Val>>{//pass derived class to based class as template argument
		Val v;
		Node(Val vv);
		//...
	};
	
	
	using My_node=Node<double>;
	void user(const vector<double>& v){
		My_node root;
		int i=0;
		
		for(auto x: v){
			auto p=new My_node{x};
			if(i++%2)//choose insert point
				root.add_left(p);
			else
				root.add_right(p);
		}
	}
}
