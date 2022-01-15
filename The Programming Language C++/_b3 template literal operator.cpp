#include <iostream>

constexpr int ipow(int x, int n){ return n>0? x*ipow(n, n-1):1; }

template<char...> struct helper;//un use

template<char c>
struct helper<c>{//stop condition
	static_assert('0'<=c&&c<'3', "not a ternary digit");
	static constexpr int value(){ return c-'0'; }
};

template<char c, char... tail>
struct helper<c, tail...>{
	static_assert('0'<=c&&c<'3', "not a ternary digit");
	static constexpr int value(){ return (c-'0')*ipow(3, sizeof...(tail))+helper<tail...>::value(); }//recursive
};

template<char... chars>
constexpr int operator"" _b3(){ return helper<chars...>::value(); }

int main(){
	std::cout<<1012_b3<<'\n';//OK
	std::cout<<123_b3<<'\n';//static assertion failed
	
	return 0;
}
