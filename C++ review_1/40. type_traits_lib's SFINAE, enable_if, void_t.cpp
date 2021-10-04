#include <iostream>
#include <type_traits>

/*make only_integer that force special type(int) by static_assert keyword
class A{};

template <typename T>
void only_integer(const T& t){
	static_assert(std::is_integral<T>::value);
	std::cout<<"T is an integer \n";
}

int main(){
	int n=3;
	only_integer(n);
	
	A a;
	only_integer(a);
}*/

/*is_class 
namespace detail{
	template <class T>
	char test(int T::*);//check Pointer to Data member regardless of int member is exist(if not exit, it doesn't point anythinig) 
	
	struct two{
		char c[2];
	};
	template <class T>
	two test(...);//return type is two that has char[2]. so it's not 1. finally false.
}
template <class T>
struct is_class: std::integral_constant<bool, sizeof(detail::test<T>(0))==1 && !std::is_union<T>::value> {};
//if sizeof~ is true, it's class. this struct just make class with static value.
*/

/*enable_if pop element to overloading occured by SFINAE
template <typename T, typename U=typename std::enable_if<std::is_integral<T>::value>::type>
void test(const T& t){
	std::cout<<"t : "<<t<<std::endl;
}

int main(){
	test(1);
	test(false);
	test('c');//well compile!
	
	struct A{};
	test(A{});//error! not int type
}*/

/*function that has func() as member function and func() must return int type value; by using enable_if
template <typename T, typename=std::enable_if_t<std::is_integral_v<decltype(std::declval<T>().func())>>>
void test(const T& t){
	std::cout<<"t.func(): "<<t.func()<<std::endl;
}

struct A{
	int func1() const { return 1; }
};
struct B{
	char func() const { return "as"; }
};

int main(){
	test(A{});//error! because of argument type (not return type)
	test(B{});//error! because of return type (not argument type)
}*/

//example code
template <class _CharT, class _Traits, class _Yp, class _Dp>
typename enable_if<//check type by return type
	is_same<void, typename __void_t<decltype(
					(declval<basic_ostream<_CharT, _Traits>&>()<<
					 declval<typename unique_ptr<_Yp, _Dp>::pointer>()))::type>::value
					 , basic_ostream<_CharT, _Traits>&>::type
		operator<<(basic_ostream<_CharT, _Traits>* __os, unique_ptr<_Yp, _Dp> const & __P){//it's just operator overloading function!
	return __os<<__p.get();		
}

//result of upper code if it's all passed
basic_ostream<_CharT, _Traits>& operator<<(basic_ostream<_CharT, _Traits>* __os, unique_ptr<_Yp, _Dp> const& __p){
	return __os<<__p.get();
}

/*
1.	type_traits에는 같은 템플릿 메타(타입에 대한 연산) 함수들이 있다.(ex. is_void, is_integral) 
2.	static_assert는 C++11 키워드로 인자로 전달된 식이 참인지 아닌지를 컴파일타임에 확인하는데, 즉 bool 타입의 constexpr만 확인할 수 있고 그 외에는 컴파일 오류가 발생한다.
	인자가 참이면 해당 식은 무시되고, 거짓이면 컴파일 오류를 발생시킨다. 이를 이용하여 특정 타입만 받는 함수를 간단하게 만들 수 있다.
3.	std::integral_constant<T, T v>는 어떤 값을 static 객체로 가지고 있는 클래스를 만들어주는 템플릿이다. 
	데이터 멤버를 가리키는 포인터(Pointer to Data member)문법은 클래스에만 사용할 수 있다. 
	 우리가 detail::test<T>(0)을 했을때 첫번 째 우선순위인 곳으로 가 형식에 맞으니 통과가 될 것이다.
	다만 첫번째 형식에 맞지않아 오버로딩 순위군에서 밀려(not error by SFINAE) 두번째로 가게 된다면, 
	리턴타입은 two가 되어 sizeof가 1이 되어 false연산이 된다. (p.s 공용체를 구별할 방법이 C++엔 없어 컴파일러에 의존한 방식으로 is_union을 사용해 해결한다.)
4.	SFINAE(Substitution Failure Is Not An Error)규칙에 따라 치환오류는 오버로딩 순위군에서 밀려나게 되는데, 문제는 컴파일러가
	실제로 발생하는 모든 치환오류들을 판단하는게 아닌 함수의 인자들과 리턴타입만을 확인하여 오버로딩 순위군으로 선택되었지만,
	막상 컴파일하니 오류가 발생하는 문제가 발행한다.
5.	이를 enable_if을 사용하여 조건에 맞지않는 함수들을 오버로딩 순위군에서 제외시킬 수 있다.
	std::enable_if에 조건이 참일때만 type이 정의되고 거짓이면 type 정의가 되지 않아 있는데 type을 호출한 것이니 오류를 발생시킨다. 
	 typename이 enable_if앞에 붙는 이유는 의존타입이기 때문인데 복잡하니 그냥 enable_if와 typename을 같이 쓰자.
6.	enable_if의 구조는 간단하게 템플릿 특수화를 해서 조건이 true인 버전에는 type이 정의되어 있고, 아니면 아무것도 정의되어 있지 않다.
7.	만약 우리가 특정한 멤버함수가 있는 타입을 인자로 받고 싶다면 typename=decltype(std::declval<T>().func())와 같이 enable_if처럼 오류를 발생시키게 만들어 처리할 수 있다.
	 근데 더 나아가 인자 뿐만이 아닌 리턴되는 타입마저도 확인하고 싶다면 enable_if를 사용할 수 있다. 
8.	우리가 Iterator를 이용하는 함수를 만든다면, template argument에 decltype(std::declval<Cont>().begin()), 과 같이 begin()과 end()멤버함수의 여부를 
	따로 확인해야 한다. 하지만 이는 번거롭기에 이들을 가변길이 템플릿을 이용하여 하나로 조금 묶어 확인하게 해주는 void_t함수가 있다.
	 그리고 유저가 실수로 template argument부분에 무얼 넣어 타입체크부분이 무력화되는 것을 방지하기 위해 리턴타입에 넣는 것이 바람직하다.(void print 처럼 리턴타입을 지정할 수 있다면)
	template <typename Cont>
	std::void_t<decltype(std::declval<Cont>().begin()), 
				decltype(std::declval<Cont>().end()> print(const Cont& containter) //check in return type
*/ 
