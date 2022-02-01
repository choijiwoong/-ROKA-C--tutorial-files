#include <iostream>
#include <type_traits>

namespace type_predicate{
	using namespace std;
	//1. type property predicate function provides access check by case_inheritance(unliike type property predicate function)
	class X{
		public:
			static void inside();
		private:
			X& operator=(const X&);
			~X();
	};
	void X::inside(){
		cout<<"inside =: "<<is_copy_assignable<X>::value<<'\n';//type property predicate
		cout<<"inside ~: "<<is_destructible<X>::value<<'\n';
	}
	void outside(){
		cout<<"outside =: "<<is_copy_assignable<X>::value<<'\n';
		cout<<"outside ~: "<<is_destructible<X>::value<<'\n';
	}
	
	//2. type_property_question
	template<typename T>
	void f(T a){
		static_assert<Is_array<T>(), "f(): not an array");
		constexpr int dn{Extent<T,2>()};//extent!
	}
	
	//3. type relation
	template<typename T>
	void draw(T t){
		static_asert(Is_same<Shape*, T>() || Is_base_of<Shape, Remove_pointer<T>>(), "");
		t->draw();
	}
}

namespace type_generator{
	//1. const & volatile
	template<typename K, typename V>
	class My_map{
		pair<typename add_const<K>::type, V> default_node;
		//...
	};
	//or we can use using
	template<typename T>
	using Add_const=typename add_const<T>::type;//use like pair<Add_const<K>,V> default_node;
	
	
	//2. reference
	template<typename T>
	void f(T&& v){
		Remove_reference<T> x=v;//copy
		T y=v;//copy or reference(by argument)
		++y;
		
		vector<Remove_reference<T>> vec1;//ok
		vector<T> vec2;//if T is reference, error occur.
		//...
	}
	void user(){
		int val=7;
		f(val);
		f(7);
	}
	
	
	//3. array
	int a[10][20];
	Remove_extent<decltype(a)> a20;//array[20]
	Remove_all_extents<decltype(a)> i;//int
	cout<<Extent<decltype(a20)>()<<' '<<Extent<decltype(i)>()<<'\n';//20 0
	
	
	//4. pointer
	template<typename T>
	void f2(T&& x){
		Add_pointer<T> p=new Remove_reference<T>();
		T* p2=new T();//if T is reference, not work
		//...
	}
	
	
	//5. align
	template<size_t N, size_t A>
	struct aligned_storage{
		using type=struct{ alignas(A) unsigned char data[N]; };//(aligned by A) N char.
	};
	
	
	//6. etc convert: common_type
	template<typename... T> struct common_type;
	
	template<typename T>
	struct common_type<T>{//self
		using type=T;
	};
	
	template<typename T, typename U>
	struct common_type<T,U>{//two
		using type=decltype(true?declval<T>():declval<U());
	};
	
	template<typename T, typename U, typename... V>
	struct common_type<T, U, V...>{//variadic
		using type=typename common_type<typename common_type<T,U>::type, V...>::type;
	};
	
	//use
	template<typename.. T>
	using Common_type=typename common_type<T...>::type;
	Common_type<int, double> x1;//double
	Common_type<int, string> x2;//error
	Common_type<void*, double*, Shape*> x5;//void*
	
	
	//7. etc convert: result of
	int ff(int){ return 2; }
	typedef bool (*PF)(int);
	struct Fct{
		double operator()(string);
		string operator()(int, int);
	};
	auto fx=[](char ch){ return tolower(ch, locale()); };
	
	Result_of<decltype(&&ff)()> r1=7;//int
	Result_of<PF(int)> r2=true;//bool
	Result_of<Fct(string)> r3=9.9;//double 동일한 사랑이 비멤버 함수에는 적용되지 않는다. 함수 포인터에 대해선 오버로딩 불가.. 
	Result_of<Fct(int, int)> r4="Hero";//string 동일한 사랑이 비멤버 함수에는 적용되지 않는다. 
	Result_of<decltype(fx)(char)> r5='a';//char
	//application of result_of
	template<typename F, typename A>
	auto temp(F f, A a)->Result_of<F(A)>{ return f(a); }
	
	
	//8. etc convert: declval()
	template<typename T, size_t N>
	void array<T,N>::swap(array& a) noexcept(noexcept(swap(declval<T&>(), declval<T&>()))){//원소가 swap가능한지 ck만 하고 실제 사용X(p.s noexcept function, noexcept in ())
		for(int i=0; i<a.size(); ++i)
			swap((*this)[i], a[i]);
	}
}

namespace small_utils{
	//1. move()
	template<typename T>
	Remove_referencee<T>&& move(T&& t) noexcept{
		return static_cast<Remove_reference<T>&&>(t);
	}
	
	//2. forward()
	template<typename T>
	T&& forward(Remove_reference<T>& t) noexcept{//lvalue argument
		return static_cast<T&&>(t);
	}
	template<typename T>
	T&& forward(Remove_rference<T>&& t) noexcept{//rvalue argument
		static_assert(!Is_lvalue_reference<T>, "forward of lvalue");
		return static_cast<T&&>(t);
	}
	//use
	int i=7;
	forward(i);//first version
	forward(7);//second version
	
	//3. type_info's compare & hashing
	unordered_map<type_index, type_info*> types;
	//...
	types[type_index{something}]=&typeid(something);
}

int main(){
	//1
	type_predicate::X::inside();//print 0(false) because destructor & copy assign is private
	type_predicate::outside();
	
	return 0;
}
