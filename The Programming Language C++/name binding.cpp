#include <iostream>

namespace {
	//example of name binding
	template<typename T>
	int f(T a){
		return g(a);//dependent name
	}
	class Quad{};
	int g(Quad);
	int z=f(Quad{2});//binding f(T a)'s g to g(Quad)
	
	//not good example
	class Quad{};
	template<typename T>
	int ff(T a){
		return gg(Quad{1});//ERROR! gg() is not in valid section, gg(Quad{1}) not depend to T
	}
	int gg(Quad);
	int zz=ff{Quad{2}};
	
	//little bad example. 
	template<typename Container>
	void fct(Container& c){
		Container::value_type v1=c[7];//grammer error. value_type is supposed to non-type name
		typename Container::value_type v2=c[9];//suppose naming by value_type
		
		auto v3=c[11];
		//...
	}
	//good example of upper code
	template<typename T>
	using Value_type=typename T::value_type;
	
	template<typename Container>
	void fct2(Container& c){
		Value_type<Container> v1=c[7];//value_type<container> not container::value_type
		//...
	}
	
	//other example
	class Pool{
		public:
			template<typename T> T* get();
			template<typename T> void release(T*);
			//...
	};
	template<typename Alloc>
	void f(Alloc& all){//some allocator
		int* p1=all.get<int>();
		int* p2=all.template get<int>();
		//...
	}
	void user(Pool* pool){
		f(pool);
		//... 찜질방가고싶당 
	}
}

namespace instantiation_binding{
	void g(int);
	template<typename T>
	void f(T a){
		g(a);//g will be binded in instantization time
	}
	
	void h(int i){
		extern void g(double);//delay instantiate
		f(i);
	}
	//now f<int> instantiate.
	
	
	//recursive
	void g(int);
	template<typename T>
	void f(T a){
		g(a);
		if(a>1)
			h(T(a-1));
	}
	enum Count{one=1, two, three};
	void h(Count i){
		f(i);//for recursive, instantiate f after definition of h.
	}
	//now f<int> instantiate.
	
	
	//
	template<typename T>
	class Container{
		vector<T> v;
		public:
			void sort();
			//...
	};
	//now Container<int> instantiate. 
	void f(){
		Container<int> c;
		c.sort();
	}
}

namespace ambigous{
	void fff(){
		struct S{int a,b;};//S is local name!
		vector<S> vs;//but it use S as explicit argument. AMBIGOUS!
		//...
	}
	
	
	template<typename T>
	void print_sorted(vector<T>& v){//ambigous example
		sort(v.begin(), v.end());
		for(const auto& x: v)
			cout<<x<<'\n';
	}
	void use(vector<string>& vec){
		//...
		print_sorted(vec);
	}
	
	
	template<typename T, typename S>
	void print_sorted(vector<T>& v, S sort, ostream& os){//for removing ambigous. non-efficient! we have to increase template arguments and code is more complex. 
		sort(v.begin(), v.end());//so reducing local name is cool, but we don't have to make standard seperately.
		for(const auto& x:v)
			os<<x<<'\n';
	}
	void fct(vector<string>& vec){
		//...
		using Iter=decltype(vec.begin());
		print_sorted(vec, std::sort<Iter>, std::cout);
	}
}

namespace diff_mean_on_diff_instantiation_time{
	void f(int);
	namespace N{
		class X{};
		char g(X,int);
	}
	template<typename T>
	char ff(T t, double d){
		f(d);//casting to int f(double d)->f(int d) on N
		return g(t,d);//casting to int g(t, double d)->g(t, int d) on N
	}
	auto x1=ff(N::X{}, 1.1);//인자기반적추론? 무튼 g(X, int) call 
	
	namespace N{
		double g(X, double);//추가 
	}
	auto x2=ff(N::X{}, 2.2);//g(X, double) call
	//다른 인스턴스화시점, 다른 의미! 문제 발생! 
}

namespace base_dependent_template{
	void g(int);
	
	struct B{
		void g(char);
		void h(char);
	};
	
	template<typename T>
	class X: public B{
		public:
			void h(int);
			void f(){
				g(2);//T와 상관없기때문에 compile time에 위의 void g(int)로 함. 
				h(2);
			}
			//...
	};
}
namespace base_dependent_template{
	void g(int);
	void g2(int);
	
	struct B{
		using Type=int;
		void g(char);
		void g2(char);
	};
	
	template<typename T>
	class X: public T{
		public:
			typename T::Type m;//for adding namespace of B
			Type m2;//ERROR. not yet
			using T::g2();//using g2() explicitly
			void f(){
				this->g(2);//T::g call
				g(2);//global g call **** 인스턴스 시점이 되어야만 매개변수 T에 쓰인 인자가 필요한 이름을 갖고있는지를 알 수 있다. 즉 using이든 뭐가 없는 g()는 컴파일타임에 결정되어 ::g를 call 
				g2(2);//T::g2 call thanks to using T::g2()
			}
			//...
	};
	void h(X<B> x){
		x.f();
	}
}
namespace solution{
	template<typename T>
	class Matrix_base{
		//...
		int size() const { return sz; }
		
		protected:
			int sz;
			T* elem;
	};
	
	template<typename T, int N>
	class Matrix: public Matrix_base<T>{
		//...
		T* data(){
			return this->elem;//this->limit is necessary in this example for prevent referencing global variables.
		}
	};
} 
