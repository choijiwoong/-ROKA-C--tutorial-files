#include <iostream>

class Animal{//abstract class
	public:
		Animal(){}
		virtual ~Animal(){}//Destructor as virtual
		virtual void speak()=0;//pure virtual function.
};

class Dog: public Animal{
	public:
		Dog(): Animal(){}
		void speak() override{ std::cout<<"hak"<<std::endl; }//overriding
};
class Cat: public Animal{
	public:
		Cat(): Animal(){}
		void speak() override{ std::cout<<"kah"<<std::endl; }//overriding
};

int main(){
	Animal* dog=new Dog();
	Animal* cat=new Cat();
	
	dog->speak();
	cat->speak();
}

/*���� ���ε� 
1.	��ӽ� Based Ŭ������ �Ҹ��ڸ� �����Լ�(virtual)�� ������ because of memory leak 
2.	��� �Լ��� virtual�� ������ �ʴ� ������ �Ϲ����� ��Ӱ��迡���� ȣ��� �޸�, ������ � �Լ��� ���� ���� �Լ� ���̺��� ���� �����ϱ� ������ ���� �ణ�� ������尡 �߻��ϱ� �����̴�
3.	virtual�Լ��� =0;�� �ٿ� ���� ���� �Լ�(pure virtual function)�� ���� �� �ִ�. �̶� �̸� �ν��Ͻ�ȭ �ϱ� ���ؼ� ��ӹ޴� Ŭ������ ����� ���� ���� �Լ����� �������̵� �����־�� �Ѵ�.
	��ó�� ���� ���� �Լ��� �����ִ�, �� �ݵ�� ��ӵǾ�߸� ����� �� �ִ� Ŭ������ �߻� Ŭ����(abstrat class)��� �Ѵ�. like ���赵
4.	���̾Ƹ�� ��� ������ �ذ��Ϸ��� ���� ���� Ŭ������ virtual�� ��ӹ޾� ���� Ŭ������ ����� �� ���� �����ϵ��� �ϸ� �ȴ�.
5.	Ŭ������ �����ϴ� ������� ũ�� �긮�� ����, ��ø�� �Ϲ�ȭ ���, ���� ����� �ִ�. 
*/
