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
1.	�Լ��� ����� ��ü�� ������ �����ϰ��� C++���� ������ �ʱ�ȭ(Uniform initialization)�� �����Ͽ���.
2.	������ ȣ��� {}�� ����ϴµ�, {}�� Narrow-conversion(�ս��� �ִ� ��ȯ) ��, �Ͻ��� Ÿ�� ��ȯ�� �����ϴ� ���� �������̴�. 
	+ �ش� ��üŸ������ �������ʱ�ȭ ����Ͽ� ���� �� ���� Ÿ���� �ٽ� ������� �ʾƵ� �ȴ�. 
	+C�� ���ó�� initializer_list�� ���ڷ� �޴� �����ڰ� �ִ� �����̳ʿ� �ʱ�ȭ�� ����Ʈ�� ����Ͽ� {}�� �����͸� ���� �� �ִ�. 
	-map�� pair<key, value>���ҵ��� �ʱ�ȭ�� ����Ʈ�� �ޱ⿡ {{"abc", 1}, {"ji", 3};�÷� �������ָ� �ȴ�.
3.	initializer_list ��� �� ������ ���� {}�� �̿��Ͽ� ��ü�� ������ ��� ������ �����ε� �ÿ� initializer_list�� ����ϴ� 
	�����ڸ� �ֿ켱���� ����ϱ� ������ �ǵ����� ���� �����ڰ� ȣ��� �� �ִ�. 
	 ������ �ս��� ���� ��ȯ�� �ϴ� {}����, initializer_list�� ���� Ÿ������ Ÿ�� ��ȯ ��ü�� �Ұ��� �� ��� ()�� ������Ÿ������ ����.
4.	autoŰ���带 ����ϸ� ���� initializer_list<type>Ÿ������ ������ �ȴ�. �ٸ� C++17���� Ư���� ��Ģ�� ���� �����ȴ�. 
	+auto list={"a", "b", "cc"}�� const char*�� ���� 
*/ 
