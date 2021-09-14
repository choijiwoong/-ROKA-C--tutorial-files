#include <iostream>

//위와 같은 작업들을 하지 않는 이상 constexpr 키워드를 함수에 붙일 수 있게 됩니다. 만일 조건을 만족하지 않는 작업을 함수 내에서 하게 된다면 컴파일 타임 오류가 발생하게 됩니다. 예를 들어서

/*1 use of constexpr
template <int N>
struct A{
	int operator()(){return N;}
};
int main(){
	constexpr int size=3;
	int arr[size];//Good!
	
	constexpr int N=10;
	A<N> a;//Good!
	std::cout<<a()<<std::endl;
	
	constexpr int number=3;
	enum B{x=number, y, z};
	std::cout<<B::x<<std::endl;
}*/

/*2 defference of constexpr & const
int a;
//Do something...
const int b=a;

int a_;
//Do something
constexpr int b_=a_;//error 'int a_ is not const'

const int i=3;//initialization in compile time? or runtime? Ambiguous in perception of compiler.
*/

/*3 It was impossible making compile time const object without constexpr in past.
int factorial(int N){
	int total=1;
	for(int i=1; i<=N; i++)
		total*=i;
		
	return total;
}

template <int N>
struct A{
	int operator()(){return N;}
};

int main(){
	A<factorial(5)> a;//error occur because factorial(5) isn't compile time const. 
}//so we have to use complex template meta programming for solving this problem before like this.
*/

/*3 make compile time const object by using TMP.
template <int N>
struct Factorial{
	static const int value=N*Factorial<N-1>::value;//Like recursive
};

template <>//template specialization for stop condition of Fatorial
struct Factorial<0>{
	static const int value=1;
};

template <int N>
struct A{
	int operator()(){ return N; }
};

int main(){
	A<Factorial<10>::value> a;//it can be used by template argument because it's decided in compile time thanks to template meta programming.
	
	std::cout<<a()<<std::endl;
}*/

/*3 make compile time const object by using constexpr
constexpr int Factorial(int n){//explicitly expression that return type is constexpr!
	int total=1;
	for(int i=1; i<=n; i++)
		total*=i;
	
	return total;
}

template <int N>
struct A{
	int operator()(){ return N; }
};

int main(){
	A<Factorial(10)> a;//so it can be used by template argument because Factorial always returns constexpr object.
	
	std::cout<<a()<<std::endl;
}*/

//3 compile time error occur if we don't keep exception condition of constexpr function



/*
[0. 들어가기에 앞서]
1.	C++11에서 도입된 constexpr키워드를 알아볼 것인데, 이는 객체나 함수 앞에 붙일 수 있는 키워드로, 해당 객체나 함수의 리턴값을 컴파일 타임에 값을 알수 있다 라는 의미를 전달하게 된다.
	컴파일러가 컴파일 타임에 어떠한 식의 값을 결정할 수 없다면 해당 식을 상수식(Constant expression)이라고 하고, 
	그 중에서 값이 정수인 것을 정수 상수식(Integral constant expression)이라고 하는데 이는 많은 쓰임새를 갖는다.
	int arr[size];에서 size나
	
	template <int N>
	struct A{
		int operator()(){return N;}
	};
	A<numver> a;의 number,
	
	enum A{a=number, b, c};의 number
	모두 정수 상수식이어야 한다. 이처럼 C++언어 상 정수상수식은 매우 흔하다. 
	
[1.	constexpr]
1.	Constexpr은 어떠한 식이 상수식이라고 명시해주는 키워드이다. constecpr이 객체정의에 사용된다면 그 객체는 어떠한 상수식에도 사용될 수 있다. 

[2.	constexpr VS const]
1.	const로 정의된 상수들은 굳이 컴파일 타임에 그 값을 알 필요가 없지만, constexpr의 경우 반드시 오른쪽에 다른 상수식이 와야 한다.
	constexpr은 항상 const지만, const는 constexpr이 아니다. 
2.	또한 const객체가 상수식으로 초기화되었다 해도 컴파일러에 따라 이를 런타임에 초기화할지, 컴파일타임에 초기화할지 다를 수 있기에 
	컴파일 타임에 확실히 상수를 사용하고 싶다면 constexpr 키워드를 꼭 사용해야 한다. 

[3.	constexpr 함수]
1.	constexpr로 컴파일 타임 상수를 정의할 수 있다면, 컴파일 타임 상수인 객체들을 만들어내는 함수를 정의할 수 있을까?
2.	constexpr이전에는 컴파일 타임 상수인 객체를 만드는 함수작성이 불가능했다. 
	근데 지금은 걍 함수의 리턴타입이 constexpr이라고 명시해주면 사용가능하다.
3.	C++14부터 몇가지 제약조건이 완화되어 아래의 조건빼고는 모두 constexpr함수 내부에서 수행할 수 있다.
	-goto문 사용
	-예외처리(try 문; C++20부터 가능해짐)
	-리터럴 타입이 아닌 변수의 정의
	-초기화 되지 않는 변수의 정의
	-실행 중간에 constexpr이 아닌 함수를 호출하게 됨
	만약 위와 같은 작업을 하면 컴파일 타임 오류가 발생한다. 
*/ 
