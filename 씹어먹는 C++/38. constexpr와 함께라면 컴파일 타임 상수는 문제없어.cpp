#include <iostream>
#include <type_traits>//6

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

/*3 compile time error occur if we don't keep exception condition of constexpr function
int not_constexpr(int x){ return x++; }
constexpr int Factorial(int n){
	int total=1;
	for(int i=1; i<=n; i++)
		total*=i;
	
	not_constexpr(total);//error occur "call to non_constexpr function"
	return total;
}*/

/*3 constexpr with normal argument not compile time const variable
constexpr int Factorial(int n){
	int total=1;
	for(int i=1; i<=n; i++)
		total*=i;
	return total;
}//error my compiler,,only
int main(){
	int num;
	std::cin>>num;//num is not compile time const!
	std::cout<<Factorial(num)<<std::endl;//constexpr int function can get compile time const successfully.
}*/

/*5 using of constexpr as template argument with constexpr Constructor, function
class Vector{
	public:
		constexpr Vector(int x, int y) :x_(x), y_(y){}//it gets two int as argument that is literal. It's correct using
		
		constexpr int x() const{return x_;}//accessing member variable is set to constexpr. then, these function like x() & y() can be used in constexpr function.
		constexpr int y() const{return y_;}
	
	private:
		int x_;
		int y_;
};

constexpr Vector AddVec(const Vector& v1, const Vector& v2){
	return {v1.x()+v2.x(), v1.y()+ v2.y()};
}

template <int N>//work in compile time
struct A{
	int operator()(){return N;}
};

int main(){
	constexpr Vector v1{1,2};//constexpr Vector object
	constexpr Vector v2{2,3};
	
	//v1.x() can be used by template argument because v1 is constexpr, v1's x() is constexpr function.
	A<v1.x()> a;
	std::cout<<a()<<std::endl;//Good!
	
	//AddVec(v1, v2).x() can be used by template argument because AddVec function is constexpr and it return Vector object that's .x() is constexpr.
	A<AddVec(v1, v2).x()> b;
	std::cout<<b()<<std::endl;//Good
}*/

/*6 function changing by argument's type by using template
template <typename T>
void show_value(T t){
	std::cout<<"it's not pointer : "<<t<<std::endl;
}

template <typename T>
void show_value(T* t){
	std::cout<<"it's pointer : "<<*t<<std::endl;
}

int main(){
	int x=3;
	show_value(x);
	
	int* p=&x;
	show_value(p);
}*/


/*6 function changing by argument's type by using std::is_pointer in type_traits
template <typename T>
void show_value(T t){
	if(std::is_pointer<T>::value)
		std::cout<<"It's pointer"<<*t<<std::endl;//Error occur in template instantiation, because if T is int, this code uses *t to int, so compile error is occur.
	else
		std::cout<<"It's not pointer"<<t<<std::endl;
}

int main(){
	int x=3;
	show_value(x);
	
	int* p=&x;
	show_value(p);
}*/

//6 solution by using if constexpr
template <typename T>
void show_value(T t){
	if constexpr (std::is_pointer<T>::value)//error occur in my compiler...only
		std::cout<"It's pointer"<<*t<<std::endl;//can be ignore!
	else
		std::cout<<"It's not pointer"<<t<<std::endl;//can be ignore!
} 
int main(){
	int x=3;
	show_value(x);
	
	int* p=&x;
	show_value(p);
}




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
4.	constexpr이라고 컴파일 타임 상수들만 인자로 받을 수 있는 것은 아니고 일반 함수처럼 동작할 수도 있다. 
	고로 constexpr을 함수에 붙일 수 있다면 붙여주는 것이 좋은게, constexpr처럼 동작을 못하면 일반 함수처럼 동작할 것이고, 컴파일 타임 상수를 생성할 수 있다면 보다 간단히 이용할 수 있기 때문이다.
	
[4.	리터럴 타입?]
1.	constexpr은 함수 내부에서 불가능한 작업으로 리터럴(Literal)타입이 아닌 변수의 정의라고 하였는데, C++에서는 리터럴을
	-void형
	-스탈라 타입(char, int, bool, long, float, double) 등
	-레퍼런스 타입
	-아래 조건을 만족하는 타입
		ㄴ디폴트 소멸자를 가지고 다음 중 하나를 만족하는 타입
			-람다 함수
			-Arggregate타입(사용자 정의 생성자, 소멸자가 없으며 모든 데이터 멤버들이 public) pair과 같은 애들 
			-constepxr생성자를 가지며 복사 및 이동 생성자가 없음 
2.	위의 애들을 리터럴 타입이라고 의미하며, 해당 객체들만이 constexpr로 선언되던지 constexpr함수 내부에서 사용될 수 있다. 

[5.	constexpr 생성자]
1.	constexpr생성자의 경우 constexpr함수에 적용되는 제약조건들이 모두 적용되며, constexpr생성자의 인자들은 반드시 리터럴 타입이어야만 하고, 해당 클래스는 다른 클래스를 가상 상속 받을 수 없다.
2.	constepxr객체의 constexpr멤버 함수만이 constexpr을 준다.

[6.	if constexpr]
1.	타입에 따라 형태가 달라지는 함수를 짜보자. like get_value function인데 인자가 포인터면 *을 리턴하고 아니면 원래의 인자를 리턴.
	이러한 함수를 template를 이용하여 만들 순있지만, show_value함수가 정확히 어떠한 형태의 T를 요구하는지 한 눈에 파악하기 힘들고,
	같은 함수를 위처럼 두 번 써야한다는 문제가 있다.
2.	이러한 문제를 해결하기 위해 C++표준 라이브러리의 <type_traits>에서는 여러가지 템플릿 함수들을 제공하는데, 이들 중 해당 타입이 포인터인지 아닌지 확인하는 함수를 이용하여 구성해보도록 하자.
	type_traits의 std::is_pointer는 전달한 인자 T가 포인터라면 value가 True가 되고, 아니면 false가 되는 템플릿 메타 함수이다.  
	하지만 타입에 따라 템플릿 인스턴스화 과정에서 코드 자체가 컴파일 될 수 없는 오류가 발생하게 된다.
3.	이러한 문제를 해결하기 위해 if constexpr을 도입할 수 있다. 
*/ 
