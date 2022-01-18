#include <iostream>

namespace concepts{
	template<typename T>
	constexpr bool Totally_ordered(){
		return Equality_compareable<T>()//== !=
			&&Has_less<T>() && Boolean<Less_result<T>>()
			&&Has_greater<T>() && Boolean<Greater_result<T>>()
			&&Has_less_equal<T>() && Boolean<Less_equal_result<T>>()
			&&Has_greater_equal<T>() && Boolean<Greater_equal_result<T>>();
	}
	template<typename T>
	constexpr bool Equality_comparable(){
		return Has_equal<T>() && Boolean<Equal_result<T>>()
			&& Has_not_equal<T>() && Boolean<Not_equal_result<>>();
	}
}
namespace concepts{
	template<typename T>
	constexpr bool Semiregular(){
		return Destructible<T>()
			&&Default_constructible<T>()
			&&Move_constructible<T>()
			&&Move_assignable<T>()
			&&Copy_constructible<T>()
			&&Copy_assignable<T>();
	}
}
namespace concepts{
	template<typename C>
	ostream& operator<<(ostream& out, String<C>& s){
		static_assert(Streamable<C>(), "String's character not streamable");
		out<<'"';
		for(int i=0; i!=s.size(); ++i)
			cout<<s[i];
		out<<'"';
	}
	template<typename T>
	constexpr bol Steamable(){
		return Input_streamable<T>() && Output_streamable<T>();
	}
}


namespace concept_for_regular{
	template<typename T>
	bool Copy_equality(T x){
		return T{x}==x;
	}
	template<typename T>
	bool Copy_assign_effect(T x, T& y){
		return (y=x, y==x);
	}
	
	template<typename T>
	bool Move_effect(T x, T& y){
		return (x==y?(x==T{std::move(y)}):true)&&can_destroy(y));
	}
	template<typename T>
	bool Move_assign_effect(T x, T& y, T& z){
		return (y==z?(x=std::move(y), x==z):true)&&can_destroy(y);
	}
}


namespace multi_argument_concept{
	template<typename T, typename U>
	constexpr bool Equality_comparable(T, U){
		return Common<T,U>()
			&&Totally_ordered<T>()
			&&Totally_ordered<U>()
			&&Totally_ordered<Common_type<T,U>>()
			&&Has_less<T,U>()&&Boolean<Less_reault<T,U>>()
			&&Has_less<U,T>()&&Boolean<Less_result<U,T>>()
			&&Has_greater<T,U>()&&Boolean<Greater_result<T,U>>()
			&&Has_greater<U,T>()&&Boolean<Greater_result<U,T>>()
			&&Has_less_equal<T,U>()&&Boolean<Less_equal_result<T,U>()
			&&Has_less_equal<U,T>()&&Boolean<Less_equal_result<U,T>()
			&&Has_greater_equal<T,U>()&&Boolean<Greater_equal_result<T,U>()
			&&Has_greater_equal<U,T>()&&Boolean<Greater_equal_result<U,T>();
	}
	
	template<typename Iter, typename Val>
	Iter find(Iter b, Iter e, Val x){
		static_assert(Input_iterator<Iter>(), "find() requires an input iterator");
		static_assert(Equality_comparable<Value_type<Iter>, Val>(), "find()'s iterator and value arguments must match");
		whiel(b!=e){
			if(*b==x){
				return b;
			}
			++b;
		}
		return b;
	}
}


namespace value_concept{
	template<int N>
	constexpr bool Small_size(){
		return N<=8;
	}
}
namespace value_concept{
	constexpr int stack_limit=2048;
	template<typename T, int N>
	constexpr bool Stackable(){
		return Regular<T>() && sizeof(T)*N<=stack_limit;//compare as value
	}
	
	template<typename T, int N>
	struct Buffer{};
	
	template<typename T, int N>
	void fct(){
		static_assert(Stackable<T,N>(), "fct() buffer won't fit on stack");
		Buffer<T,N> buf;
		//...
	}
}
