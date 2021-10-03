#include <iostream>
#include <initializer_list>
#include <string>

//unusual convert of {} to (), if argument is not perfectly matched to initializer_list's argument.
class A{
	public:
		A(int x, double y){ std::cout<<"common constructor!"<<std::endl; }
		A(std::initializer_list<std::string> lst){ std::cout<<"initializer_list constructor!"<<std::endl; }
};

int main(){
	A a(3, 1.5);//common
	A b{3, 1.5};//common
	A c{"abc", "def"};//initializer_list
}

/*
1.	함수의 선언과 객체의 생성을 구분하고자 C++에서 균일한 초기화(Uniform initialization)을 도입하였다.
2.	생성자 호출시 {}를 사용하는데, {}는 Narrow-conversion(손실이 있는 변환) 즉, 암시적 타입 변환을 불허하는 것이 차이점이다. 
	+ 해당 객체타입으로 유니폼초기화 사용하여 리턴 시 굳이 타입을 다시 명시하지 않아도 된다. 
	+C의 어레이처럼 initializer_list를 인자로 받는 생성자가 있는 컨테이너에 초기화자 리스트를 사용하여 {}로 데이터를 넣을 수 있다. 
	-map은 pair<key, value>원소들을 초기화자 리스트로 받기에 {{"abc", 1}, {"ji", 3};꼴로 전달해주면 된다.
3.	initializer_list 사용 시 주의할 점은 {}를 이용하여 객체를 생성할 경우 생성자 오버로딩 시에 initializer_list를 사용하는 
	생성자를 최우선으로 고려하기 때문에 의도하지 않은 생성자가 호출될 수 있다. 
	 데이터 손실이 없는 변환을 하는 {}지만, initializer_list의 원소 타입으로 타입 변환 자체가 불가능 할 경우 ()의 생성자타입으로 들어간다.
4.	auto키워드를 사용하면 전부 initializer_list<type>타입으로 추정이 된다. 다만 C++17부터 특정한 규칙에 따라 추정된다. 
	+auto list={"a", "b", "cc"}는 const char*로 추정 
*/ 
