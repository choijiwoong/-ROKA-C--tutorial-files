#include <iostream>
// 코드의 경우 add, check_div,, result, one 등등 ...) 를 보았을 때 이 식별자가 '값' 인지 '타입' 인지 결정을 해야 합니다. 왜냐하면 예를들어서
/*
bool is_prime(int N){//normal function
	if(N==2) return true;
	if(N==3) return true;
	
	for(int i=2; i<=N/2; i++)
		if(N%i==0) return false;
		
	return true;
}//transfer this to TMP!

template <>//template specialization of 2
struct is_prime<2>{
	static const bool result=true;
};

template<>
struct is_prime<3>{//template specialization of 3
	static const bool result=true;
};

template <int N>//get bool value bu check_div
struct is_prime{
	static const bool result=!check_div<n, 2>::result;
};

template <int N, int d>
struct check_div{
	static const bool result=(N%d==0)||check_div<N, d+1>::result;//recursive structure
};

template <int N>//At this, error occur. template specialization must use template <> but, if then, we can't express <N, N/2> without template <int N>. So make N to type!
struct check_div<N, N/2>{//stop condition
	static const bool result=(N%(N/2)==0);
};*/


template <int N>
struct INT{
	static const int num=N;
};
template <typename a, typename b>
struct add{
	typedef INT<a::num+b::num> result;
};

template <typename a, typename b>
struct divide{
	typedef INT<a::num / b::num> result;
};

using one=INT<1>;
using two=INT<2>;
using three=INT<3>;

template <typename N, typename d>
struct check_div{
	static const bool result=(N::num%d::num==0)||check_div<N, add<d, one>::result>::result;//recursive structure with add<d, one>
};

template <typename N>
struct is_prime{
	static const bool result=!check_div<N, two>::result;//judge by check_div
};

template <>
struct is_prime<two>{//template specialization
	static const bool result=true;
};
template<>
struct is_prime<three>{
	static const bool result=true;
};

temaplate <typename N>
struct check_div<N, divide<N, two>::result>{//error occur! we think result as type ofcoursely. But in compiler aspect, it must decide that this result is type or value.
	static const bool result=(N::num%(N::num/2)==0);
};


/*
[1.	지난 강의 생각해보기 문제(TMP를 사용하여 어떤 수가 소수인지 아닌지를 판별하는 프로그램을 만들어보자)]
1.	 
*/
