#include <iostream>

namespace Predicate{
	template<typename T>
	void do_something(){
		Conditional<(is_pod<T>()), On_heap<T>, Scoped<T>> x;//ERROR! is_pod<T> is type!
		//...
	}
	
	template<typename T>
	constexpr bool Is_pod(){
		return std::is_pod<T>::value;//COOL! return bool type
	}
}

namespace Trait{
	//example of traits
	template<typename Iterator>
	struct iterator_traits{
		using difference_type=typename Iterator::difference_type;
		using value_type=typename Iterator::value_type;
		using pointer=typename Iterator::pointer;
		using reference=typename Iterator::reference;
		using iterator_category=typename Iterator::iterator_category;
	};
	
	//structure of Conditional
	template<bool C, typename T, typename F>
	struct conditional{
		using type=T;
	};
	template<typename T, typename F>
	struct conditional<false, T,F>{//specialization of false
		using type=F;
	};
	template<bool B, typename T, typename F>
	using Conditional=typename std::conditional<B,T,F>::type;//using! more easily use
	//user!
	Conditional<(Is_polymorphic<T>()),X,Y> z;
}

namespace Select{
	template<unsigned N, typename... Cases>//no instantiation!
	struct select;
	
	template<unsigned N, typename T, typename... Cases>
	struct select<N,T,Cases...>: select<N-1, Cases...>{};
	
	template<typename T, typename... Cases>
	struct select<0,T,Cases...>{//stop condition
		using type=T;
	};
	
	template<unsigned N, typename... Cases>
	using Select=typename select<N, Cases...>::type;
}

namespace loop{
	//ver1
	template<int N>
	constexpr int fac(){
		return N*fac<N-1>();
	}
	template<>
	constexpr int fac<1>(){//stop condition by specialization
		return 1;
	}
	constexpr int x5=fac<5>();
	
	//ver2 more general
	constexpr int fac(int i){
		return (i<2)?1:i*fac(i-1);
	}
	constexpr int x6=fac(6);
	
	//recursive by using class
	template<int N>
	struct Fac{
		static const int value=N*Fac<N-1>::value;
	};
	template<>
	struct Fac<1>{
		static const int value=1;
	};
	constexpr int x7=Fac<7>::value;
}

namespace Enable_if_example{
	void f(Smart_pointer<double> p, Smart_pointer<complex<double>> q){
		auto d0=*p;//OK
		auto c0=*q;//OK
		auto d1=q->real();//OK
		auto d2=p->real();//ERROR_not class
	}
	
	//inner structure of enable_if
	template<bool B, typename T=void>
	struct std::enable_if{
		typedef T type;
	};
	template<typename T>
	struct std::enable_if<false, T>{};
	
	template<bool B, typename T=void>
	using Enable_if=typename std::enable_if<B,T>::type;
	
	//additional example
	struct substitution_failure{};//fail
	template<typename T>
	struct substitution_succeeded: std::true_type{};//true. std::true_type::value==true
	template<>
	struct substitution_succeded<substitution_failure>: std::false_type{};//false. std::false_type::value==false
	
	
	template<typename T>
	struct has_f: substitution_succeeded<typename get_f_result<T>::type>{};//if f(x) doesn't compile?
	
	template<typename T>
	struct get_f_result{
		private:
			template<typename X>
				static auto check(X const& x)->decltype(f(x));//만약 여기서 실패하면 SFINAE에 의해 무시되고
			static substitution_failure check(...);//이게 정의. 
		public:
			using type=decltype(check(std::declval<T>()));//만약 성공이라면 보다 타입인자가 정확한 f(x)를 반환하는 check가, 실패하면 substitution을 반환하느 check가 return 된다. 
	};
}

namespace tuple_structure{
	//Tuple<double, int, char> x{1.1, 42, 'a'}; cout<<get<1>(x);처럼 사용하는 것이 목표. sizeof(T0)==8, sizeof(T1)==4, sizeof(T2)==4 thanks to empty-base optimization
	
	template<typename T1=Nil, typename T2=Nil, typename T3=Nil, typename T4=Nil>//Nil is default template argument
	struct Tuple: Tuple<T2, T3, T4>{//basic structure
		T1 x;
		using Base=Tuple<T2,T3,T4>;
		Base* base(){ return static_cast<Base*>(this); }
		const Base* base() const{ return static_cast<const Base*>(this); }
		Tuple(const T1& t1, const T2& t2, const T3& t3, const T4& t4): Base{t2, t3, t4}, x{t1}{}
	}; 
	
	//specialization
	template<>
	struct Tuple<>{ Tuple(){} };//0-tuple
	
	template<typename T1>
	struct Tuple<T1>: Tuple<>{//1-tuple
		T1 x;
		using Base=Tuple<>();
		Base* base(){ return static_cast<Base*>(this); }
		const Base* base() const{ return static_cast<const Base*>(this); }
		Tuple(const T1& t1): Base{}, x{t1}{}
	};
	
	template<typename T1, typename T2>
	struct Tuple<T1, T2>: Tuple<T2>{//2-tuple
		T1 x;
		using Base=Tuple<T2>;
		Base* base(){ return static_cast<Base*>(this); }
		const Base* base() const{ return static_cast<const Base*>(this); }
		Tuple(const T1& t1, const T2& t2): Base{t2}, x{t1}{}
	};
	
	template<typename T1, typename T2, typename T3>
	struct Tuple<T1, T2, T3>: Tuple<T2, T3>{//3-tuple
		T1 x;
		using Base=Tuple<T2,T3>;
		Base* base(){ return static_cast<Base*>(this); }
		const Base* base() const{ return static_cast<const Base*>(this); }
		Tuple(const T1& t1, const T2& t2, const T3& t3): Base{t2, T3}, x{t1}{}
	};
	
	
	//getNth function for approach to Tuple(feat. const)
	template<typename Ret, int N>
	struct getNth{
		template<typename T>
		static Ret& get(T& t){
			return getNth<Ret, N-1>::get(*Tuple.base());
		}
		template<typename T>
		static const Ret& get(const T& t){
			return getNth<Ret, N-1>::get(*t.base());
		}
	};
	template<typename Ret>
	struct getNth<Ret, 0>{
		template<typename T> static Ret& get(T& t){ return t.x; }//return element by recursive structure
		template<typename T> static const Ret& get(const T& t){ return t.x; }//const also
	};
	template<int N, typename T1, typename T2, typename T3, typename T4>
	Select<N,T1,T2,T3,T4>& get(const Tuple<T1,T2,T3,T4>& t){//get function by using getNth
		return getNth<Select<N,T1,T2,T3,T4>,N>::get(t);
	}
	template<int N, typename T1, typename T2, typename T3, typename T4>
	const Select<N, T1, T2, T3, T4>& get(const Tuple<T1,T2,T3,T4>& t){
		return getNth<Select<N,T1,T2,T3,T4>,N>::get(t);
	}
} 
