#include <iostream>

/*1
struct S{
	void operator()(int a, int b) { std::cout<<"a + b = "<<a+b<<std::endl; }
};

int main(){
	S some_obj;//it's callable! it's not function but it can be called by ()
	some_obj(3, 5);
}*/


#include <functional>
#include <string> 
/*2
int some_func1(const std::string& a){
	std::cout<<"call Func1!"<<a<<std::endl;
	return 0;
}

struct S{//Functor
	void operator()(char c){ std::cout<<"call Func2!"<<c<<std::endl; }
};

int main(){
	std::function<int(const std::string&)> f1=some_func1;
	std::function<void(char)> f2=S();
	std::function<void()> f3=[](){ std::cout<<"call Func3!"<<std::endl; };//lambda function
	//std::function's template argument is <return_type(argument_type)>
	
	f1("hello");
	f2('c');
	f3();
	
	return 0;
}*/

/*3 error case: what's this? 
class A{
	int c;
	
	public:
		A(int c): c(c) {}
		int some_func() {std::cout<<"inner data : "<<c<<std::endl;}
};
int main(){
	A a(5);
	std::function<int()> f1=a.some_func;//error occur! c in dome_func() means this.c variable but if we save member function into std::function, compiler doesn't know what's this.
}*/

/*3 how can we use member function by using std::function
class A{
	int c;
	
	public:
		A(int c):c(c){}//constructor
		int some_func(){
			std::cout<<"nonconst function: "<<++c<<std::endl;
			return c;
		}
		
		int some_const_function() const{
			std::cout<<"const function: "<<c<<std::endl;
			return c;
		}
		
		static void st() {}
};
int main(){
	A a(5);
	//it has to be receive object that is owner of member function we want to input.
	std::function<int(A&)> f1=&A::some_func;//normally pass <return_type(argument type that gets object)> as template argument.
	std::function<int(const A&)> f2=&A::some_const_function;//In C++ rule, every function(without member function)'s name change to function's address.
	//Exceptionally, name of member function doesn't change to function's address automatically.
	//So we have to express function's address explicitly by using & operator.
	
	f1(a);//so we pass that object for execute member function. like python's (self)
	f2(a);
}*/

#include <vector>
#include <algorithm>
/*4 std::function, std::stansform, std::mem_fn
using std::vector;

int main(){
	vector<int> a(1);
	vector<int> b(2);
	vector<int> c(3);
	vector<int> d(4);
	
	vector<vector<int>> container;
	container.push_back(b);
	container.push_back(d);
	container.push_back(a);
	container.push_back(c);
	
	std::function<size_t(const vector<int>&)> sz_func=&vector<int>::size;//function has argument for getting each element, and return type is size_t for working to each element.
	vector<int> size_vec(4);
	
	std::transform(container.begin(), container.end(), size_vec.begin(), sz_func);//not just &vector<int>::size
	//transform is in <algorithm> that save result of execution of function(that is passed by argument) at all elements.
	//transform(first_element, last_element, save_here, work_function_to_each_element)
	//In fact, upper code occurs compile error. because transform's access of work_function_to_each_element is '*d_first++=unary_op(*first);
	//it passes work_function by using vector<int>::size not using real object(each element.size()).
	
	//we can use mem_fn that returns function object.
	//So by using mem_fn, sz_func can be replaced to std::mem_fn(&vector<int>::size).
	//ㄴstd::transform(container.begin(), container.end(), size_vec.begin(), std::mem_fn(&vector<int>::size)
	
	for(auto itr=size_vec.begin(); itr!=size_vec.end(); ++itr)
		std::cout<<"size of vector :: "<<*itr<<std::endl;
}*/

/*5 normal use of std::bind, std::placeholders
void add(int x, int y){
	std::cout<<x<<" + "<<y<<" = "<<x+y<<std::endl;
}
void subtract(int x, int y){
	std::cout<<x<<" - "<<y<<" = "<<x-y<<std::endl;
}
int main(){
	auto add_with_2=std::bind(add, 2, std::placeholders::_1);//bind add function with argument (2, std::placeholders::_1)
	add_with_2(3);//==add(2, 3)
	
	//ignore second argument
	add_with_2(3, 4);//==add(2, 3). third argument is not binded in std::bind. ignore extra argument.
	
	auto subtract_from_2=std::bind(subtract, std::placeholders::_1, 2);//bind subtract function with argument (std::placeholders::_1, 2)
	auto negate=std::bind(subtract, std::placeholders::_2, std::placeholders::_1);//bind subtract function with argument (std::placeholders::_2, std::placeholders::_1)
	
	subtract_from_2(3);//==subtract(3, 2)
	negate(4,2);//==subtract(2,4)
}*/

//5 Be careful point at function that get reference as argument. use std::ref()
struct S{
	int data;
	S(int data):data(data){ std::cout<<"call common constructor!"<<std::endl;}
	S(const S& s){
		std::cout<<"call copy constructor!"<<std::endl;
		data=s.data;
	}
	S(S&& s){
		std::cout<<"call move constructor!"<<std::endl;
		data=s.data;
	}
};
void do_something(S& s1, const S& s2){
	s1.data=s2.data+3;
}

int main(){
	S s1(1), s2(2);
	std::cout<<"Before :: "<<s1.data<<std::endl;
	
	//auto do_something_with_s1=std::bind(do_something, s1, std::placeholders::_1);//pass s1's copy as argument
	//do_something_with_s1(s2);
	//logical error! pass s1's copy not real s1!!!
	
	//Let's pass s1's reference not copy!
	auto do_something_with_s1=std::bind(do_something, std::ref(s1), std::placeholders::_1);
	do_something_with_s1(s2);
	
	std::cout<<"After :: "<<s1.data<<std::endl;
}


/*
[1.	Callable]
1.	보통 이름 그대로 호출가능한 모든 것을 의미한다. 하지만 C++에서는 ()를 붙여 호출할 수 있는 모든 것은 Callable이라고 정의한다.

[2.	std::function]
1.	C++에서는 callable들을 객체의 형태로 보관할 수 있는 std::function클래스를 제공한다. 
2.	std::function은 C++의 모든 callable을 마음대로 보관하고 이용할 수 있는 객체이다. 이를 만약 함수 포인터로 구현한다면 Functor을 성공적으로 처리할 수 없었을 것이다.

[3.	멤버 함수를 가지는 std::function]
1.	std::function은 일반적인 callable을 쉽게 보관할 수 있지만, 멤버 함수만을 저장한다면 맴버 함수 속 this가 어떤 객체인지 알 수없기에 this가 무엇인지 알 수 없는 문제가 발생한다.
2.	사실 멤버 함수들은 구현 상 자신을 호출한 객체를 인자로 암묵적으로 받고 있다. 예로 파이썬에선 멤버 함수들이 모두 def func(self)와 같이 정의되는 이치와 같다.

[4.	멤버 함수들을 함수 객체로-mem_fn]
1.	transform을 사용하여 work_function을 전달할 때, 각 개체의 멤버함수에 접근하는 것이 아닌, 실체가 없는(해당 객체의 주소정보가 없는) 객체 정의부의 멤버함수에 대입하기에 컴파일 오류가 발생한다.
	즉, unary_op(*first1)이 &vector<int>::size(*first);가 되는데, 멤버함수의 경우엔 (*first).(*&vector<int>::size) 혹은 first->(*&vector<int>::size)로 호출해야하기 때문이다.(C++의 규칙)
2.	매번 위처럼 function객체를 따로 만들어서 전달하는 것이 귀찮기에 function객체를 리턴해버리는 함수를 추가하였다. 
	std::mem_fn(&vector<int>::size)
3.	mem_fn은 람다함수로도 동일한 작업을 할 수있기에 자주 쓰이지는 않는다.
	mem_fn(&vector<int>::size) 대신에 [](const auto& v) { return v.size()}역시 동일한 작업을 하기 때문이다.
	다만 코드 길이가 mem_fn이 깔끔해서 사용한다.
	
[5.	std::bind]
1.	함수 객체 생성 시에 인자를 특정한 것으로 지정할 수도 있다. 
2.	std::bind(function, argument1, argument2, ...)
	auto Ang_Pang=std::bind(subtract, std::placeholders::_2, 3);//==subtract(second_argument, 3)
3.	std::placeholders는 _1부터 _29까지 정의되어 있다.(libstdc++경우. 라이브러리마다 다르긴 하다.) 
4.	단 레퍼런스를 인자로 받는 함수의 경우 조심해야한다. bind함수로 인자가 복사되어 전달되기 때문에 이를 해결하기 위해서는 s1의 레퍼런스를 전달해줘야 한다. 
	전달받은 인자를 복사 가능한 레퍼런스로 변환해주는 std::ref()함수를 이용하여 bind함수 안으로 s1의 레퍼런스가 잘 전달될 수 있게 하자. 
*/

//오늘의 명언; 정확히는 어제의 명언 : "난 너처럼 군생활을 즐기면서 하는애는 처음봤어. 볼 때마다 항상 웃고있어."_4강승민 
