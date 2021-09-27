#include <iostream>

/*TMP1. addtion
template <int N>
struct Int{//wrapper
	static const int num=N;//this type is this!
}; 

template <typename T, typename U>
struct add{
	typedef Int<T::num+U::num> result;//access by :: because it's type
};

int main(){
	typedef Int<1> one;
	typedef Int<2> two;
	
	typedef add<one, two>::result three;
	
	std::cout<<"Addtion result: "<<three::num<<std::endl;
}*/

/*TMP2. factorial
template <int N>
struct Factorial{
	static const int result=N*Factorial<N-1>::result;
};

template<>//stop condition as template specialization
struct Factorial<1>{
	static const int result=1;
};

int main(){
	std::cout<<"6! = 1*2*3*4*5*6= "<<Factorial<6>::result<<std::endl;
}*/

//TMP3. GCD
template <int X, int Y>
struct GCD{
	static const int value=GCD<Y, X%Y>::value;
};

template <int X>
struct GCD<X, 0>{
	static const int value=X;
};


template <int N, int D=1>
struct Ratio{
	private:
		const static int _gcd=GCD<N, D>::value;//gcd for reduction
		
	public:
		typedef Ratio<N/_gcd, D/_gcd> type;//calculated ratio type
		static const int num=N/_gcd;//num
									//---
		static const int den=D/_gcd;//den
};

template <class R1, class R2>//add
struct _Ratio_add{
	using type=Ratio<R1::num*R2::den + R2::num*R1::den, R1::den*R2::den>;
};
template <class R1, class R2>
struct Ratio_add: _Ratio_add<R1, R2>::type{};//inheritance! for reducing of process that we type ::type

template <class R1, class R2>//subtract
struct _Ratio_subtract{
	using type=Ratio<R1::num*R2::dem - R2::num*R1::den, R1::den*R2::den>;
};
template <class R1, class R2>
struct Ratio_subtract: _Ratio_subtract<R1, R2>::type{};

template <class R1, class R2>//multiply
struct _Ratio_multiply{
	using type=Ratio<R1::num*R2::num, R1::den*R2::den>;
};
template <class R1, class R2>
struct Ratio_multiply: _Ratio_multiply<R1, R2>::type{};

template <class R1, class R2>//divide
struct _Ratio_divide{
	using type=Ratio<R1::num*R2::den, R1::den*R2::num>;
};
template <class R1, class R2>
struct Ratio_divide: _Ratio_divide<R1, R2>::type{};

int main(){
	using r1=Ratio<2,3>;
	using r2=Ratio<3,2>;
	
	using r3=Ratio_add<r1, r2>;
	std::cout<<"2/3+3/2= "<<r3::num<<" / "<<r3::den<<std::endl;
}

/*
1.	템플릿을 통하여 타입을 인자처럼 사용하는 것으 일반화 프로그래밍(generic programming)이라고 한다.
2.	 
*/
