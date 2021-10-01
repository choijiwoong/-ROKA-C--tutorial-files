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
1.	Callable; ()�� ȣ���� �����Ѱ� �� ��� ��ü�� ���·� ������ �� �ִ� std::functionŬ������ ����� �� �ִ�. 
	std::fuction<int(const std::string&)> f1=some_func1;
2.	��������� std::function�� ������ ����, � ��ü�� �Լ����� �𸣱⿡ 
	std::function<int(A&)> f1=&A::some_func;�� ǥ���ؾ� �Ѵ�. �Ϲ����� �Լ����� �˾Ƽ� C++ ��Ģ�� &�÷� �Ͻ��� ��ȯ�� �Ͼ���� function�� �ȱ׷��⿡ ��������� ǥ�����־�� �Ѵ�. 
3.	std::function�� �ʿ��� ���÷� transform�� ����Լ��� ����� ���ε�, transform�� ����Լ��� ��� (*first).(*&vector<int>::size)�� first->(*&vector<int>::size)ó�� ȣ���ؾ� �ϱ⿡
	�׳� �ش� ����Լ��� std::function�� ��� function�� ���ڷ� �������ָ� ���� �ÿ��ϴ�.
4.	�ٵ� ���� �����ϴ°� 2���̶� �̸� ���ٷ� �ٿ� std::mem_fn(&vector<int>::size())�� �ٲ�ġ�Ⱑ �����ϴ�. ���� �ȿ� �Լ��� function���� �ٲپ� ����~�̶�� ��
	(��� �� ���ٷ� �����ϸ� ������ �������)_ [](const auto& v){ return v.size(); } 
5.	�Լ� ��ü ���� �ÿ� ���ڸ� Ư���� ������ �������ִ� std::bind~ 
	std::ref�� ��ü�� ���簡���� reference�� �ٲپ��ش�. 
*/
