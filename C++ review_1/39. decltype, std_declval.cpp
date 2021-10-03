#include <iostream>

/*common code without decltype keyword
template <typename T, typename U>
void add(T t, U u, (???type) result){
	*result=t+u;
} 

//solution by decltype
template <typename T, typename U>
void add(T t, U u, decltype(t+u)* result){
	*result=t+u;
}

//how about just return added value without result variable?
template <typename T, typename U>
decltype(t+u) add(T t, U u){//compile error! compiler doesn't know what's t and u
	return t+u;
}

//solution by C++14's rule
template <typename T, typename U>
auto add(T t, U u)->decltype(t+u){//explicit auto as return type. like lambda
	return t+u;
}*/

#include <utility>
//need of std::declval not only decltype
template <typename T>
decltype(std::declval<T>().f()) call_f_and_return(T& t){
	return t.f();
}
struct A{
	int f(){ return 0;}
};
struct B{
	B(int x){}
	int f(){ return 0; }
};

int main(){
	A a;
	B b(1);
	
	call_f_and_return(a);
	call_f_and_return(b);
}

/*
1.	decltype키워드로 타입을 알고자 하는 식의 타입으로 치환되게 된다. 괄호로 둘러쌓이지 않은 식별자 표현식(id-expression);
	어떠한 연산을 하지 않고 단순히 객체 하나만을 가리키는 식이면 다 가능하다.
2.	decltype에 식별자 표현식이 아닌 식을 전달하면 값의 종류(value category)에 따라 달라진다. 
	xvalue면 T&&, lvalue면 T&, prvalue면 T가 된다.
3.	C++의 모든 식(expression)은 타입과 값 카테고리 이 두가지 정보가 항상 따라다닌다.
	값 카테고리를 구분하는 기준은 정체를 알 수 있는가(주소값을 취할 수 있는지)와 이동가능한가(T&& x=i 가능?)이다.
	 xvalue는 정체O이동O, lvalue는 정체O이동X, prvalue는 정체X이동O이다. 이때 이동O는 rvalue, 정체O는 glvalue라고도 한다.
4.	decltype은 괄호에 유무로 인해 값 카테고리가 바뀌어 추론되는 타입이 다를 수 있다. 
	int a; decltype((a)) b;에서 b는 int&로 추론된다. 정체O이동X이기에 lvalue로 추론되기 때문이다.
5.	decltype은 auto와 다르게 정확한 타입을 얻을 수 있다. 즉, 배열의 경우 auto는 포인터로 변환하지만 decltype은 배열 타입 그대로를 전달한다.
6.	C++14부터 일단 함수의 리턴형을 auto로 써두고 함수 인자정의부 뒤에 ->로 실제 리턴 타입을 지정해주는 것이 가능하다.
7.	decltype에 class의 default constructor을 호출하여 함수를 수행하는 decltype(A().f()) ret_val;을 한다고 해도 컴파일 타임에 식의 형태로만 존재할 뿐
	런타임 시에 실행되는 것이 아니다. 
8.	decltype의 문제는 template에서 객체의 함수를 호출할 경우, 해당 템플릿 인자로 들어온 (객체의)타입에 해당 함수를 갖고있지 않다면 오류가 발생한다는 것이다.
	이를 std::declval로 해결이 가능하다. 
	declval은 T의 생성자를 직접 호출하지 않더라도 T가 생성된 객체를 나타낼 수 있다. 이는 생성자의 형태가 모두 달라서 발생하는 오류를 해결해준다.
	 물론 dtd::declval은 런타임에 사용하면 오류가 발생한다.
	사용법은 decltype(std::decltype<T>())을 하면 생성자 직접호출없이 객체표현이 가능하니 멤버함수나 변수들을 .으로 나타내서 decltype 타입을 알아낼 수 있다. 
9.	p.s로 C++14부터는 함수의 리턴타입을 컴파일러가 알아서 유추해주니 그냥 함수 리턴타입을 auto로 통용하여 사용해도 된다. 
 
*/
