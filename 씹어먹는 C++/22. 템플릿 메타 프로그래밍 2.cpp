#include <iostream>

/*1
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

/*1
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
	static const bool result=(N::num%d::num==0)||check_div<N, typename add<d, one>::result>::result;//recursive structure with add<d, one>
};

template <typename N>//use like is_prime<INT<11>>::result but for convenience, change to use like is_prime<11>::result
struct _is_prime{
	static const bool result=!check_div<N, two>::result;//judge by check_div. 
};

template <>
struct _is_prime<two>{//template specialization
	static const bool result=true;
};
template<>
struct _is_prime<three>{
	static const bool result=true;
};

temaplate <typename N>//depending on N!
struct check_div<N, typename divide<N, two>::result>{//error occur! we think result as type ofcoursely. But in compiler aspect, it must decide that this result is type or value.
	static const bool result=(N::num%(N::num/2)==0);//So, for completely read upper command we show "result must be type" by adding 'typename' keyword 
};//check_div's result is static const bool(value), so it doesn't need typename. 

template <int N>
struct is_prime{
	static const bool result=_is_prime<INT<N>>::result;
};

int main(){
	std::cout<<std::boolalpha;
	std::cout<<"Is 2 prime? :: "<<is_prime<2>::result<<std::endl;//true
	std::cout<<"Is 10 prime? :: "<<is_prime<10>::result<<std::endl;//false
	std::cout<<"Is 11 prime? :: "<<is_prime<11>::result<<std::endl;//true
	std::cout<<"Is 61 prime? :: "<<is_prime<61>::result<<std::endl;//true
}*/

//GCD define
template <int X, int Y>
struct GCD{
	static const int value=GCD<Y, X%Y>::value;
};
template <int X>
struct GCD<X, 0>{//escape
	static const int value=X;
};
//Ratio define
template <int N, int D=1>//N/D structure for expression of denominator and numerator of fraction.
struct Ratio{
	const static int _gcd=GCD<N, D>::value;//tool for abbreviation
	
	public:
		typedef Ratio<N/_gcd, D/_gcd> type;
		static const int num=N/_gcd;
		static const int den=D/_gcd;
};
//calculation part of Ratio
template <class R1, class R2>//add define
struct _Ratio_add{
	using type=Ratio<R1::num*R2::den+R2::num*R1::den, R1::den*R2::den;
};
template <class R1, class R2>//for simplization of add
struct Ratio_add:_Ratio_add<R1, R2>::type{};

template <class R1, class R2>//subtract define
struct _Ratio_subtract{
	using type=Ratio<R1::num*R2::den-R2::num*R1::den. R1::den*R2::den;
};
template <class R1, class R2>//for simplization of subtract
struct Ratio_subtract: _Ratio_subtract<R1, R2>::type {};

template <class R1, class R2>//multiply define
struct _Ratio_multiply{
	using type=Ratio<R1::num*R2::num, R1::den*R2::den>;
};
template <class R1, class R2>//for simplization of multiply
struct Ratio_multiply:_Ratio_multiply<R1, R2>::type {};

template <class R1, class R2>//divide define
struct _Ratio_divide{
	using type=Ratio<R1::num*R2::den, R1::den*R2::num>;
};
template <class R1, class R2>//for simplization of divide
struct Ratio_divide:_Ratio_divide<R1, R2>::type {};

//Dim define
template <typename U, typename V, typename W>//for express unit. get type by argument. so not Dim<1, 1, -2>, Dim<Ratio<1,1>, Ratio<1,1>, Ratio<-2,1>>
struct Dim{//for simplization just 3 element(normal 8 elements are needed)
	using M=U;//Mass(kg)
	using L=V;//Length(meter)
	using T=W;//Time(second)
	
	using type=Dim<M, L, T>;//like point self
};
//calculation part of Dim
template <typename U, typename V>//+ & - calculation
struct add_dim_{//Dim add define
	typedef Dim<typename Ratio_add<typename U::M, typename V::M>::type,//dependent type.
			    typename Ratio_add<typename U::L, typename V::L>::type,
			    typename Ratio_add<typename U::T, typename V::T>::type>
			type;//simplization of add of Dim
};
template <typename U, typename V>
struct subtract_dim_{//Dim subtract define
	typedef Dim<typename Ratio_subtract<typename U::M, typename V::M>::type,
			    typename Ratio_subtract<typename U::L, typename V::L>::type,
			    typename Ratio_subtract<typename U::T, typename V::T>::type>
			type;//simplizatino of subtract of Dim
};

//quantity define for data+unit
template <typename T, typename D>//data, dim
struct quantity{//class that save real data.
	T q;//data is q that has t type.
	using dim_type=D;//dimention information
	
	//for operator overload
	quantity operator+(quantity<T, D> quant) {//input data with quantity<T,D> type in operator+()function define name to quant 
		return quantity<T, D>(q+quant.q);//q and quant's q add operation. return quantity object that has q+quant.q. than constructor get that key and set q+quant.q as new q value.
	}//quantity's data type must be same Dim type for instantiation.
	quantity operator-(quantity<T, D> quant) {	
		return quantity<T, D>(q-quant.q);	
	}//if types are different, compiler make error that can't find operator+ because of no instantiation.
	//if D is different in operator+ & - overloading work, compiler makes error in return part because quantity<T, D1> is different type of quantity<T, D2>. cannot save data regardless of q+quant.t
	
	//operator overload of * & / is mush hard than overload of + & - because it can calculate regardless of Dim! just new Dim data occur.(ex. for acceleration just do meter/(second*second)
	//so * and / can work ragardless of Dim!
	template <typename D2>//for * operation of quantity
	quantity<T, typename add_dim_<D, D1>::type> operator*(quantity<T, D2> quant){//* operation with quantity<T, D2> as quant object
		return quantity<T, typename add_dim_<D, D2>::type(q*quant.q);//(both type is same to T! if not error)add dim and set data to q*quant.q by using Constructor
	}//and return type copy to infront of operator* keyword as return type.
	template <typename D2>//for / operation of quantity
	quantity<T, typename subtract_dim_<D, D2>::type> operator/(quantity<T, D2> quant){//algorithm is same to operator*
		return quantity<T, typename subtract_dim_<D, D2>::type>(q/quant.q);
	}
	//for exception scalar input like '3*kg' that is no demention normally.
	quantity<T, D> operator*(T scalar){	return quantity<T,D>(q*scalar);}
	quantity<T, D> operator/(T scalar){	return quantity<T,D>(q/scalar);}
	}
	
	//constructor
	quantity(T q):q(q){}
};

int main(){
	using one=Ratio<1, 1>;
	using zero=Ratio<0, 1>;
	
	quantity<double, Dim<one, xero, xero>> kg(1);//data: double 1, dim_type Mass(kg)
	quantity<double, Dim<zero, one, zero>> meter(1);
	quantity<double, Dim<zero, zero, one>> second(1);
	
	//good
	kg+kg;
	
	//bad
	kg+meter;
	//error occur
	//no opertor "+" matches these operands
	//binary '+': no operator founs which takes a right-hand operand of type
	//'quantity<double, Dim<zero, one, zero>>' (or there is no acceptable conversion)
	
	F=kg*meter/(second*second); //what type will be get F? F's dim is <Ratio<1, 1>, Ratio<1, 1>, Ratio<-2,1>>.
	//So, F get 'quantity<double, Dim<one, one, Ratio<-1,1>>> F=kg*meter/(second*second);
	//it's so annoying when we define variables. and compiler already know what type pop of F.
	//So actually, we don't have to write that dirty type. so make compiler smart to think that type by self.
}


/*
[1.	지난 강의 생각해보기 문제(TMP를 사용하여 어떤 수가 소수인지 아닌지를 판별하는 프로그램을 만들어보자)]
1.	컴파일러의 구조상 어떠한 식별자(변수 이름이든 함수 이름이든 코드 상의 이름들)을 보았을 깨 이 식별자가 '값'인지 '타입'인지를 결정해야 한다.
	예를들어 클래스에 대해 func함수가 특수화 한다면, T::t* p;가 클래스의 t와 p를 곱하는 것으로 해석이 되지만,
	어떤 함수가 클래스에대해 특수화 한다면 T::t* p;는 포인터 p를 선언하는 것이 되기 때문이다.
	고로 이 두상황을 컴파일러가 명확하게 구분하게하기 위해 T::t가 타입인지 값인지를 명확하게 알려줘야만 한다.
	 위의 result역시 '타입'인지 '값'인지를 구분해야하는데, 만약
	template <>
	struct divide<int a, int b>{
		const static int result=a+b;
	};
	이런 템플릿이 정의돼있고 만약 N과 two가 그냥 int값이라면 result는 static const int타입의 '값'이 된다.
	 이처럼 템플릿 인자에 따라 어떠한 타입이 달라질 수 있는 것을 의존 타입(dependent type)이라고 부은다.
	위의 경우 result는 N에 의존하기 때문에 의존타입이다. 
	 무조건 타입이라고 지정하는 방법은 앞에 typename키워드를 붙여주면 된다. 값의 경우는 컴파일러는 어떤 식별자를 봤을 때 default로 값이라고 생각하기에 그냥 안붙여주면 된다. 
2.	참고로 컴파일러에 따라서 재귀적으로 몇 번 사용 가능한지 깊이가 정해져있기 때문에, 꽤 큰 수를 넣는다면 컴파일 오류가 발생할 수도 있다. 
3.	본격적으로 지난 강좌에서 Ratio클래스를 왜 굳이 TMP로 만들었는지 알아가보자. TMP의 진짜 파웡

[2.	단위(Unit) 라이브러리]
1.	C++ 코드를 작성하는 이유 중 하나로 인공위성의 궤도를 계산한다던지, 입자의 운동을 계산한다던지 등에 필요한 여러 수치 계산이 있다.  
	이러한 물리적 수치 계산에 필요한 것이 kg, m, s같은 단위인데, 이러한 것들을 계산하는 프로그램들의 경우, double이나 float변수에 들어가는 값에는 '단위'가 붙어서 들어갈 것이다.
	float v;//속도  m/s
	float a;//가속도 m/s^2
	std::cout<<v+a;
	의 경우, v+a는 분명히 불가능한 연산이지만, C++컴파일러 입장에서는 그냥 두 개의 float변수를 더한 것이기에 문제없이 컴파일 된다.
2.	이러한 실수를 막기 위해서 1차원적인 생각은 클래스를 만들어서 단위도 같이 저장하는 것이다. operator등으로 연산자들을 오버로딩하고, 연산자가 다를때를 적절히 처리하면 된다.
	하지만, 만약 틀린 단위를 연산라는 코드가 매우 드물게 나타난다면, 즉 런타임에서 그 문제를 발견하지 못한 채 넘어갈 수 있다는 문제가 있다.
	 고로, 아예 단위가 다르면 컴파일시에 오류를 발생시켜버리는 것이 이상적이다. 

[3. 타입을 알아서 추측해라! '-auto' 키워드]
1.	 
*/
