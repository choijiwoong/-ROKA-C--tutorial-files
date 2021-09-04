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
	//��std::transform(container.begin(), container.end(), size_vec.begin(), std::mem_fn(&vector<int>::size)
	
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
1.	���� �̸� �״�� ȣ�Ⱑ���� ��� ���� �ǹ��Ѵ�. ������ C++������ ()�� �ٿ� ȣ���� �� �ִ� ��� ���� Callable�̶�� �����Ѵ�.

[2.	std::function]
1.	C++������ callable���� ��ü�� ���·� ������ �� �ִ� std::functionŬ������ �����Ѵ�. 
2.	std::function�� C++�� ��� callable�� ������� �����ϰ� �̿��� �� �ִ� ��ü�̴�. �̸� ���� �Լ� �����ͷ� �����Ѵٸ� Functor�� ���������� ó���� �� ������ ���̴�.

[3.	��� �Լ��� ������ std::function]
1.	std::function�� �Ϲ����� callable�� ���� ������ �� ������, ��� �Լ����� �����Ѵٸ� �ɹ� �Լ� �� this�� � ��ü���� �� �����⿡ this�� �������� �� �� ���� ������ �߻��Ѵ�.
2.	��� ��� �Լ����� ���� �� �ڽ��� ȣ���� ��ü�� ���ڷ� �Ϲ������� �ް� �ִ�. ���� ���̽㿡�� ��� �Լ����� ��� def func(self)�� ���� ���ǵǴ� ��ġ�� ����.

[4.	��� �Լ����� �Լ� ��ü��-mem_fn]
1.	transform�� ����Ͽ� work_function�� ������ ��, �� ��ü�� ����Լ��� �����ϴ� ���� �ƴ�, ��ü�� ����(�ش� ��ü�� �ּ������� ����) ��ü ���Ǻ��� ����Լ��� �����ϱ⿡ ������ ������ �߻��Ѵ�.
	��, unary_op(*first1)�� &vector<int>::size(*first);�� �Ǵµ�, ����Լ��� ��쿣 (*first).(*&vector<int>::size) Ȥ�� first->(*&vector<int>::size)�� ȣ���ؾ��ϱ� �����̴�.(C++�� ��Ģ)
2.	�Ź� ��ó�� function��ü�� ���� ���� �����ϴ� ���� �����⿡ function��ü�� �����ع����� �Լ��� �߰��Ͽ���. 
	std::mem_fn(&vector<int>::size)
3.	mem_fn�� �����Լ��ε� ������ �۾��� �� ���ֱ⿡ ���� �������� �ʴ´�.
	mem_fn(&vector<int>::size) ��ſ� [](const auto& v) { return v.size()}���� ������ �۾��� �ϱ� �����̴�.
	�ٸ� �ڵ� ���̰� mem_fn�� ����ؼ� ����Ѵ�.
	
[5.	std::bind]
1.	�Լ� ��ü ���� �ÿ� ���ڸ� Ư���� ������ ������ ���� �ִ�. 
2.	std::bind(function, argument1, argument2, ...)
	auto Ang_Pang=std::bind(subtract, std::placeholders::_2, 3);//==subtract(second_argument, 3)
3.	std::placeholders�� _1���� _29���� ���ǵǾ� �ִ�.(libstdc++���. ���̺귯������ �ٸ��� �ϴ�.) 
4.	�� ���۷����� ���ڷ� �޴� �Լ��� ��� �����ؾ��Ѵ�. bind�Լ��� ���ڰ� ����Ǿ� ���޵Ǳ� ������ �̸� �ذ��ϱ� ���ؼ��� s1�� ���۷����� ��������� �Ѵ�. 
	���޹��� ���ڸ� ���� ������ ���۷����� ��ȯ���ִ� std::ref()�Լ��� �̿��Ͽ� bind�Լ� ������ s1�� ���۷����� �� ���޵� �� �ְ� ����. 
*/

//������ ���; ��Ȯ���� ������ ��� : "�� ��ó�� ����Ȱ�� ���鼭 �ϴ¾ִ� ó���þ�. �� ������ �׻� �����־�."_4���¹� 
