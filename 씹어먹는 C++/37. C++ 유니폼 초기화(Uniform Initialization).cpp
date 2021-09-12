#include <iostream>

/*0 compiler decode everything (seems like definition of function) to definition of function
class A{
	public:
		A() { std::cout<<"Call A's constructor"<<std::endl; }
};

int main(){
	A a();//no print! because compiler think it definition of function
}*/

/*0 how about this?
class A{
	public:
		A() { std::cout<<"Call A's Constructor!"<<std::endl; }
};
class B{
	public:
		B(A a){ std::cout<<"Call B's Constructor!"<<std::endl; }
};

int main(){
	B b(A());//no print too! because compiler think it definition of function(that return B and get A() as argument)
}*/

/*1 another way using {} 
class A{
	public:
		A(int x, double y) { std::cout<<"Call A's Constructor!"<<std::endl; }
};
A func(){
	return {1, 2.3};//it's same to A(1, 2.3) compiler guess return type itself
}
int main(){
	//A a(3.5);//Narrow-conversion is possible
	//A b{3.5};//Narrow-conversion is impossible
	
	func();
}*/

//2



/*
[0.	���� ����]
1.	C++11���� �߰��� ������ �ʱ�ȭ(Uniform Initialization)�� ���� �˾ƺ� ���̴�. 
2.	���� �ڵ�� A�� �����ϴ� �Լ� a()�� ������ ������ �����Ϸ��� �����Ѵ�. 
3.	�̷��� ������ ()�� �Լ��� ���ڵ��� �����ϴµ��� ���ǰ�, �Ϲ����� ��ü�� �����ڸ� ȣ���ϴµ����� ���Ǳ� �����̴�.
	��� C++11������ �̷��� ������ �ذ��ϱ� ���� ������ �ʱ�ȭ(Uniform Initialization)�� �����Ͽ���.
	
[1.	������ �ʱ�ȭ(Uniform Initialization)
1.	�����ڸ� ȣ���ϱ� ���� ()�� ����ϴ� ��ſ� {}�� ����ϸ� ���̴�. 
	��� �����ؾ��ϴ� ����, {}�� �̿��� ������ �Ϻ� �Ͻ��� Ÿ�� ��ȯ���� �����ϰ� �ִ�. �׷��� ���� ���� ������ �ս��� �ִ�(Narrowing) ��ȯ�̴�.
2.	������ ����,,, {}�� ����Ͽ� ������ �ʴ� Ÿ�� ĳ������ �����Ͽ� ������ �̿��� ��Ƴ� �� �ִ�.
	���� {}�� ����ϸ� �Լ� ���Ͻÿ� ���� �����ϴ� ��ü�� Ÿ���� �ٽ� ������� �ʾƵ� �ȴ�. 
	
[2.	�ʱ�ȭ�� ����Ʈ(Initializer list)]
1.	 
*/
