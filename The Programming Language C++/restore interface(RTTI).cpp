#include <iostream>

namespace {//p.710
	class Io_obj{//polymorphism type
		public:
			virtual Io_obj* clone() const=0;
			virtual ~Io_obj(){}
	};
	
	using Pf=Io_obj*(istream&);//function ptr
	map<string, Pf> io_map;//match string to function Pf
	string get_word(istream& is);//read one word
	
	Io_obj* get_obj(istream& is){
		string ptr=get_word(is);
		if(auto f=io_map[str])
			return f(is);//call function
		throw Unknown_class{};
		//structure of io_map! example.
		//io_map["Io_circle"]=&Io_circle::new_circle();
		//io_map["Io_truangle"]=&To_triangle::new_triangle;
	}
	
	
	//
	class Shape: public Io_obj{};
	struct Io_circle: Circle, Io_obj{
		Io_circle(istream&);//initialize by istream
		Io_circle* clone() const{ return new Io_circle{*this}; }//use copy constructor(factory)
		static Io_obj* new_circle(istream& is){ return new Io_circle{is}; }//for io_map
	};
	class Io_triangle: public Triangle, public Io_obj{
		//...
	};
	
	template<typename T>
	struct Io:T, Io_obj{//[1]for prepare io of object easily. like circle, triangle...etc. we can use 'using Io_circle=Io<Circle>' like. 
		//[2]prob) BUT we have to use explicit definition of Io<Circle>::Io(istream&) unfortunately because we have to know detail of Circle. SO we will solve this problem by T val in struct Io.
		public:
			T val;//[3]sol) for get detail of type for Io<T>::Io(istream&). NOW we can use 'using Io_int=Io<int>' like.
			Io(istream&);
			Io* clone() const override{ return new Io{*this}; }
			static Io* new_io(istream& is){ return new Io{is}; }
	};
	
	template<typename T>
	T* get_val<T>(Io_obj* p){//[4] we cannot cast Io_obj<X> to X because we make value as member. so we have to provide handling function of that.
		if(auto pp=dynamic_cast<Io<T>*> (p))
			return &pp->val;//return val of casted Io<T>'s pointer.
		return nullptr;
	}
	
	classs Face: public Shape{
		public:
			Shape* outline;
			array<Shape*> eyes;
			Shape* mouth;
			//...
	};
	
	//
	void user(){
		//...open file, ss set istream of file...
		unique_ptr<Io_obj> p{get_obj(ss)};//read object
		//[5] now no dynamic_cast(auto sp=dynamic_cast<Shape*>(p.get())), use get_val.
		if(auto sp=get_val<Shape>(p.get()){//dynamic_cast for handling many objects.
			sp->draw();
			//...
			
		} else{
			//problem occur. p is not Shape
		}
	}
}


namespace dynamic_dispatch{//p.714
	void do_something(Shape& s1, Shape& s2){//[1] intersect problem!
		if(s1.intersect(s2)){//intersect s1.intersect(s2) & s2.intersect(s1)!!!
			
		}
		//...
	}
	
	//[2] double dispatch
	class Circle;
	class Triangle;
	
	class Shape{
		public:
			virtual bool intersect(const Shape&) const=0;
			virtual bool intersect(const Circle&) const=0;
			virtual bool intersect(const Triangle&) const=0;
	}; 
	
	class Circle: public Shape{
		public:
			bool intersect(const Shape&) const override;
			virtual bool intersect(const Circle&) const override;
			virtual bool intersect(const Triangle&) const override;
	};
	class Triangle: public Shape{
		public:
			bool intersect(const Shape&) const override;
			virtual bool intersect(const Circle&) const override;
			virtual bool intersect(const Triangle&) const override;
	};
	
	//[2-1] decide work per every combination_ we will get hard when expansion of argument.
	bool Circle::intersect(const Shape& s) const { return s.intersect(*this); }
	bool Circle::intersect(const Circle&) const { std::cout<<"intersect(circle, circle)\n"; return true; }
	bool Circle::intersect(const Triangle&) const{ std::cout<<"intersect(triangle, circle)\n"; return true; }
	
	bool Triangle::intersect(const Shape& s) const{ return s.intersect(*this); }
	bool Triangle::intersect(const Circle&) const{ std::cout<<"intersect(circle, triangle)\n"; return true; }
	bool Triangle::intersect(cosnt Triangle&) cosnt { std::cout<<"intersect(triangle, triangle)\n"; return true; }
	
	//
	void test(Triangle& t, Circle& c){
		std::vector<std::pair<Shape*, Shape*>> vs{ {&t,&t}, {&t,&c}, {&c,&t}, {&c,&c} };//test all combination
		for(auto p: vs)
			p.first->intersect(*p.second);
	}
	void user{
		intersect(triangle, triangle);//"intersect(triangle, triangle)"
		intersect(triangle, circle);//...etc
		intersect(circle, triangle);
		intersect(circle, circle);
	}
	
	//[2-2] For solving [2-1]'s priblem, use intersect(Shape*, Shape*) and define all bounding box.
	class Shape{
		public:
			virtual Rectangle box() const=0;//bounding box for each shape.
			//...
	};
	class Circle: public Shape{
		public:
			Rectangle box() const override;//make to Shape
			//...
	};
	class Triangle: public Shape{
		public:
			Rectangle box() const override;
			//...
	};
	
	bool intersect(const Rectangle&, const Rectangle&);
	bool intersect(const Shape& s1, const Shape& s2){
		return intersect(s1.box(), s2.box());//check intersect by box also.
	}
	
	//[2-3] Make search_table
	bool intersect(const Shape& s1, const Shape& s2){
		auto i=index(type_id(s1), type_id(s2));
		return intersect_tbl[i](s1, s2);
	}
}


namespace visitor{//p.716
	class Visitor;
	class Node{
		public:
			virtual void accept(Visitor&)=0;
	};
	class Expr: public Node{
		public:
			void accept(Visitor&) override;
	};
	class Stmt: public Node{
		public:
			void accept(Visitor&) override;
	};
	
	void Expr::accept(Visitor& v){ v.accept(*this); }//[1]call accept by itself
	void Stmt::accpet(Visitor& v){ v.accept(*this); }
	
	class Visitor{//declaration of combination of operations
		public:
			virtual void accept(Expr&)=0;//[2]automatically overloading
			virtual void accept(Stmt&)=0;
	};
	
	struct Do1_visitor: public Visitor{//definition of combination of operations. [3]make visitor per combination.
		void accept(Expr&) override{ std::cout<<"do1 to Expr\n"; }
		void accept(Stmt&) override{ std::cout<<"do1 to Stmt\n"; }
	};
	struct Do2_visitor: public Visitor{
		void accept(Expr&) override{ std::cout<<"do2 to Expr\n"; }
		void accept(Stmt&) override{ std::cout<<"do2 to Stmt\n"; }
	};
	
	Do1_visitor do1;//test
	Do2_visitor do2;
	void test(Expr& e, Stmt& s){
		std::vector<std::pair<Node*, Visitor*>> vn{ {&e,&do1}, {&s,&do1}, {&e,&do2}, {&s,&do2} };
		for(auto p: vn)
			p.first->accept(*p.second);
		//do1 to Expr_e.accept(do1)
		//do1 to Stmt
		//do2 to Expr
		//do2 to Stmt
	}
}
