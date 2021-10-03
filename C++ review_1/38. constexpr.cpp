#include <iostream>

/*make compile time function by constexpr not TMP
constexpr int Factorial(int n){
	int total=1;
	for(int i=1; i<=n; i++)
		total*=i;
	return total;
}

template <int N>
struct A{//template argument return class
	int operator()(){ return N; }
};

int main(){
	A<Factorial(10)> a;
	std::cout<<a()<<std::endl;
}*/

//coding by template argument case without compile error by using if constexpr
template <typename T>
void  show_value(T t){
	if constexpr(std::is_pointer<T>::value)
		std::cout<<"pointer: "<<*t<<std::endl;
	else
		std::cout<<"not pointer: "<<t<<std::endl;
}

int main(){
	int x=3;
	show_value(x);
	
	int* p=&x;
	show_value(p);
}


/*
1.	constexpr;컴파일 타임 상수. 값을 컴파일 타임에 알 수 있다, 즉 상수식이라고 명시해주는 키워드이다. (like array's size)
2.	const는 값을 지정해 주면 바꿀수 없는 것은 당연하지만, 컴파일 타임에 굳이 그 값을 알 필요가 없다. 값은 컴파일타임이나 런타임에 초기화된다. 
	반면에 constexpr은 반드시 오른쪽에 다른 상수식이 와야 한다. 고로int a;  constexpr int b=a;는 컴파일 오류를 발생시킨다. 
3.	TMP를 사용하여 컴파일 타임 함수나 상수를 만들었던 반면, 
	조건이 맞는다면 constexpr을 사용하여 함수의 리턴값을 컴파일 타임 상수constexpr로 만들 수 있다.(ex. 함수 내부에서 constexpr이 아닌 함수 호출) 
4.	웬말하면 함수에 constexpr을 붙이는게 좋은데, 컴파일 타임 상수를 생성할 수 없다면 일반 함수처럼 작동하기 때문이다. 
5.	constexpr객체의 constexpr멤버 함수만이 constexpr을 준다!(constexpr로 받을 수 있다)
	<type_traits>에서 여러 템플릿 함수들을 제공하는데, 그 중에 std::is_pointer<T>::value라고 포인터인지 아닌지를 확인하는 함수가 있다.
	우린 이를 if로 처리함으로써 포인터일때와 포인터가 아닐 때를 구분하여 코딩할 수 있는데, 문제는 TMP다 보니 template argument에 따라
	컴파일 자체가 불가능한 오류코드가 인스턴스화될 수도 있다. 
	 그럴때 if constexpr문을 사용하여 처리하면, 해당하는 부분 즉 if constexpr과 else중에서 참인 부분만 컴파일되고 나머지 부분은 아예 무시되어 컴파일 오류가 발생하지 않는다.
	  
*/
