#include <iostream>
#include <functional>

//logical error of std::bind
struct S{
	int data;
	S(int data): data(data){ std::cout<<"common constructor is called!"<<std::endl; }//normal con
	S(const S& s){//copy con
		std::cout<<"copy constructor is called!"<<std::endl; 
		data=s.data;
	}
	S(S&& s){//move con
		std::cout<<"move constructor is called!"<<std::endl;
		data=s.data;
	}
};

void do_something(S& s1, const S& s2){ s1.data=s2.data+3; }//function get reference as argument

int main(){
	S s1(1), s2(2);
	
	std::cout<<"Before: "<<s1.data<<std::endl;
	
	auto do_something_with_s1=std::bind(do_something, s1, std::placeholders::_1);//pass s1's copy! not ref. so use it by std::ref
	//Let's use like this!
	//auto do_something_with_s1=std::bind(do_something
	
	do_something_with_s1(s2);
	
	std::cout<<"After:: "<<s1.data<<std::endl;
}


/*
1.	Callable; ()로 호출이 가능한거 를 모두 객체의 형태로 보관할 수 있는 std::function클래스를 사용할 수 있다. 
	std::fuction<int(const std::string&)> f1=some_func1;
2.	멤버변수를 std::function에 저장할 때는, 어떤 객체의 함수인지 모르기에 
	std::function<int(A&)> f1=&A::some_func;로 표현해야 한다. 일반적인 함수들은 알아서 C++ 규칙상 &꼴로 암시적 변환이 일어나지만 function은 안그러기에 명시적으로 표현해주어야 한다. 
3.	std::function이 필요한 예시로 transform에 멤버함수를 사용할 때인데, transform은 멤버함수의 경우 (*first).(*&vector<int>::size)나 first->(*&vector<int>::size)처럼 호출해야 하기에
	그냥 해당 멤버함수를 std::function에 담아 function을 인자로 전달해주면 속이 시원하다.
4.	근데 만들어서 전달하는건 2줄이라 이를 한줄로 줄여 std::mem_fn(&vector<int>::size())로 바꿔치기가 가능하다. 대충 안에 함수를 function으로 바꾸어 리턴~이라는 뜻
	(사실 걍 람다로 전달하면 되지롱 쿠쿠루삥뽕)_ [](const auto& v){ return v.size(); } 
5.	함수 객체 생성 시에 인자를 특정한 것으로 지정해주는 std::bind~ 
	std::ref는 객체를 복사가능한 reference로 바꾸어준다. 
*/
