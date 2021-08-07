#include <iostream>

/*1
class Parent{
	public:
		Parent(){ std::cout<<"Parent ������ ȣ��"<<std::endl; }
		virtual ~Parent(){ std::cout<<"Parent �Ҹ��� ȣ��"<<std::endl; }//set virtual! for prevent memory leak.
};
class Child:public Parent{
	public:
		Child():Parent(){ std::cout<<"Child ������ ȣ��"<<std::endl; }
		~Child(){ std::cout<<"Child �Ҹ��� ȣ��"<<std::endl; }
};

int main(){
	std::cout<<"--����� Child ������� ��--"<<std::endl;
	{Child c;}
	std::cout<<"--Parent �����ͷ� Child �������� ��--"<<std::endl;
	{
		Parent *p=new Child();//so make it's destructor to virtual.
		delete p;//only call destructor of Parent! Child destructor isn't called. it calls memory leak. then normally call every destructor.
	 } 
} */

/*2
class A{
	public:
		virtual void show(){
		std::cout<<"Parent!"<<std::endl;
		}
};
class B:public A{
	public:
		void show() override{//if show() in B, not to find in A; override.
			std::cout<<"Child!"<<std::endl;
		}
};
void test(A& a){//A type. it's no matter because of virtual keyword of A class.
	a.show();
}
int main(){
	A a;
	B b;
	test(a);
	test(b);
	
	return 0;
}*/

/*3
class Parent{//example
	public:
		virtual void func1();
		virtual void func2();
};
class Child:public Parent{
	public:
		virtual void func1();
		void func3();
};

int main(){
	Parent* p=Parent();
	p->func1();
	//compiler: 
	//1. p is pointer locates Parent, so let's search func1() in Parent class!
	//2. wait. func1() is virtual function! then not execute func1() directly, let's call Parent::func1() in Parent's virtual function table!
	
	parent* c=Child();
	c->func1();
	//compiler:
	//1. p is pointer locates Parent, so let's search func1() in Parent class!
	//2. wait. func1() is virtual function! then not execute func1() directly, let's call Child::func1() in Child's virtual function table! because it locates Chile object!
	
	return 0;
} */

/*4
class Animal{
	public:
		Animal() {}
		virtual ~Animal(){}
		virtual void speak()=0;//it means this function must be overrided; pure virtual function. it can't be called because it's no body. 
};//So, Animal instance can't be make because we don't have to a.speak(). At all, developer of C++ prohibit of this creation of Animal instance. 
//for show structure of skeleton class. and tell to coder "it can't be made normal environment, so make it yourself!"
class Dog:public Animal{
	public:
		Don():Animal(){}
		void speak() override{//must override! 
			std::cout<<"�п�"<<std::endl;
		}
};
class Cat:public Animal{
	public:
		Cat():Animal(){}
		void speak() override {//must override!
			std::cout<<"�߿˾߿�"<<std::endl;
		}
};

int main(){
	Animal* dog=new Dog();//make Animal's pointer instance!!! Animal is abstract class!!  
	Animal* cat=new Cat();
	
	dog->speak();//normally operate because of overriding of Animal's speak() to Dog's speak()
	cat->speak();
}*/

/*5
class A{
	public:
		int a;
		A() { std::cout << "A ������ ȣ��" << std::endl; }
}; 

class B{
	public:
		int b;
		B() { std::cout << "B ������ ȣ��" << std::endl; }
};

class C: public B, public A{//it can be expressed by map : class C->class A & class B it just means C has content of A and B.
	public:
		int c;
		C() : A(), B() { std::cout << "C ������ ȣ��" << std::endl; }
};
int main() { 
	C c;//which constructor will be operated in A & B? when c called. just by order of inheritance
	c.a = 3;//it can work thanks to multiple inheritance!
	c.b = 2;
	c.c = 4;
}*/

/*6
class Human {
 public:
  // ...
};
class HandsomeHuman : public virtual Human {
  // ...
};
class SmartHuman : public virtual Human {
  // ...
};
class Me : public HandsomeHuman, public SmartHuman {
  // ...
};*/

/*
[1.	virtual �Ҹ���] 
1.	Child�Ҹ��ڰ� ȣ��� ��, Child�� �̹� Parent�� ��ӹ޴´ٴ� ���� �˰� �ֱ� ������, Child �Ҹ��ڰ� '�˾Ƽ�' Parent �Ҹ��ڸ� ȣ�����ش�.
	�ݸ鿡, Parent �Ҹ��ڸ� ���� ȣ���ϰ� �Ǹ�, Parent�� Child�� �ִ��� ������ �𸣱� ������, child�Ҹ��ڸ� ȣ������ �� ����.(Parent *p=new Child()) 
	 �̿� ���� ������, ��ӵ� ������ �ִ� Base Class���� �Ҹ��ڸ� �ݵ�� virtual�� ������ ���߿� ������ �߻��ϴ� ���� ���� �� �ִ�.
	  
[2.	���۷����� �ȴ�]_�������ڸ��� 
1.	������ �� ����

[3.	���� �Լ��� ���� ����]
1.	�׳� ��� �Լ����� virtual�� ���������� �ȵǴ°�? ->��� �Լ����� ���� �Լ��� �������ν�, ������ ���� ���ε��� ����� �����ϰ� �� �Ͽ� ������ JAVA�� ��� �Լ����� default�� virtual�Լ��� ����ȴ�.
	������, virtual�� ����ϰ� �Ǹ� �ణ�� �������(overhead)�� �����Ѵ�._�ð��� �� �ɸ�. �̴� ����ȭ�� �ſ� �߿��� �о߿��� ������ �ʿ䰡 �ֱ� ������, �ٸ� ������� �ٸ��� C++������ ��� �Լ��� default�� virtual�� ���� �ʴ´�. 
2.	C++�� Ŭ������ �����Լ��� �ϳ��� ������ ��� ��ȭ��ȣ�ο� ���� ���� �Լ� ���̺�(virtual function table; vtable)�� ����� �ȴ�. 
	�̴� �Լ��� �̸��� ������ � �Լ��� �����Ǵ����� ���̺�� �����ϰ� �ִ�. 
	 Child�� func3()���� �� ���� �Լ����� Ư���� �ܰ踦 ��ġ�� �ʰ�, func3()�� ȣ���ϸ� ���� ����ȴ�.
	������, �����Լ��� ȣ���Ͽ��� ����, �����Լ����̺��� �� �ܰ� �� ���ļ�, ������ � �Լ��� ���� �����ϰ� �ȴ�.

[4.	���� ���� �Լ�(pure virtual function)�� �߻� Ŭ����(abstract class)]
1.	���� �Լ��� =0;�� �ٿ��� �ݵ�� �������̵� �ǵ��� ���� �Լ��� ������ ���� �Լ�, ���� ���� �Լ�(pure virtual function)�̶�� �Ѵ�. 
2.	���� ���� �Լ��� �ּ� �� �� �̻� �����ϰ� �ִ� Ŭ������ ��ü�� ������ �� ������, �ν��Ͻ�ȭ ��Ű�� ���ؼ��� �� Ŭ������ ��ӹ޴� Ŭ������ ���� ��� ���� ���� �Լ��� �������̵� �ؾ� �Ѵ�.
3.	��ó�� ���� ���� �Լ��� �ּ� �Ѱ� �����ϰ� �ִ� ��, �ݵ�� ��� �Ǿ�� �ϴ� Ŭ������ ������ �߻� Ŭ����(Abstract class)��� �θ���.
4.	����� private �ȿ� ���� ���� �Լ��� �����ص� �ȴ�. �Ȱ��� �������̵�� ������ ���� �ڽ� Ŭ�������� ȣ���� �� �� ���̴�.. 
5.	��� ������, ��ӹ޾Ƽ� ����ϴ� ������� "�� ����� �Ϲ����� ��Ȳ���� �����ϱ� ����� �ʰ� ���� Ư��ȭ �Ǵ� Ŭ������ ���߾ ���� ���"�ϰ� �ϴ� ���̴�.
	���� ��� Animal�� speak�ϴ� ���� ������, �����鸶�� �Ҹ��� �ٸ��⿡ ���� �����Լ��� �������ν�, Animal���� speak�Ѵٴ� �ǹ� ���ް�, �˾Ƽ� �����ϸ� �ȴ�.
6.	�߻�Ŭ������ �Ǵٸ� Ư¡��, ��ü ������ �ȵ�����, �߻� Ŭ������ ����Ű�� �����ʹ� �������� ���� �� �ִٴ� ���̴�. virtual and override!

[5. ���� ���(multiple inheritance)]
1.	C++������ �� Ŭ������ �ٸ� ���� ���� Ŭ�������� ��� �޴� ���� ����ϴµ�, �̸� ���� ���(multiple inheritnace)��� �θ���. 
2.	��� ������ ���� ������ ȣ��. 

[6. ���� ��� �� ������ ��]
1.	�� ���� Ŭ�������� �̸��� ���� ��� ������ �ִµ�, �� �� Ŭ������ ���� ����Ͽ� �ش� ��� ������ �����ϸ�, �翬�� ��� Ŭ������ ��� ������ �����ؾ��ϴ��� ������ �� ���ٴ� ������ �߻���Ų��. �̴� �ڸ��ϰ� �Լ��� ���������̴�. 
2.	�� �Ѱ��� �����ؾ��� ����, (������) ���̾Ƹ�� ���(dreadful_diamond of derivation)�̶�� �θ��� ���� ��� �����̴�. 
	���̽� Ŭ������ Human�� �ְ�, �̸� ��ӹ޴� HandsomeHuman, SmartHumanŬ������ �ִ�. �׸��� HandsomeHuman�� SmartHuman�� ���� ��ӹ޴� Me��� Ŭ������ �ִ�.
	��, ����� �Ǵ� �� ���� Ŭ������ ������ ���̽� Ŭ������ �����ϰ� �ִ� ���´� ���̾Ƹ�� ����̶�� �θ���.
	�� ���, �� Handsome, SmartHuman���� �����Ÿ� �� �غ��� �ᱹ Me���� Human�� ��� ������ �ߺ��Ǵ� ������ �߻��Ѵ�.??? . 
	 �̸� �ذ��ϱ� ���ؼ�, Human�� Smart, Handsome�� virtual�� ��ӹ����� �ȴ�. ��� �����Ϸ��� ������ Human�� �� ���� �����ϵ��� �����ϴ� ���̴�.
	�����, ���� ���� ���� ��� �ÿ�, Me�� �����ڿ��� HandsomeHuman�� SmartHuman�� �����ڿ� ���Ҿ� Human�� ������ ���� ȣ�����־�� �Ѵ�.???
[7.	���� ����� ���� ����ؾ� �ұ�?]
1.	Vehicle�� LandVehicle�� �����ϰ� �ִٸ�, Vehicle�� ��� �Լ��� ȣ������ ��, LandVehicle�� ��� �Լ��� �������̵�Ǽ� ȣ��Ǳ⸦ �ٶ�°�?
2.	Vehicle�� GasPoweredVehicle�� �����ϰ� �ִٸ�, Vehicle�� ��� �Լ��� ȣ������ ��, GasPoweredVehicle�� ��� �Լ��� �������̵�Ǽ� ȣ��Ǳ⸦ �ٶ�°�?
3.	1,2�� ��� ����� ����� ���´ٸ�, ���߻���� ����ϴ� ���� ������, ��� �� ����ؾ��Ѵ�. ȯ���� N���̰�, ���¿��� ������ M����� �غ��ٸ�
	ũ�� 3���� ������� Ŭ������ ������ �� �� �ִ�. �ٷ� �긮�� ����(bridge pattern), ��ø�� �Ϲ�ȭ ���(nested generalization), ���� ����̴�.
	 �긮�� ������ ���, ���¿��� ȯ�� �� �Ѱ��� ī�װ��� �ƿ� ��� �����ͷ� ����� ���̴�. �� Vehicle�� �Ļ�Ŭ������ ȯ��Ŭ�������� �ְ�, Engine*�� ���� ��������� � ������ ����� ������ ����Ű�� �����ϴ� ����̴�.
	�� ���, ȯ���� �߰��ȴ� �ϴ��� Ŭ������ 1���� �� ����� �ȴ�. �� N+M�� Ŭ������ �����ϸ�ȴ�. 
	however, N+M���� �������� �����ϹǷ� NxM�� ���� ��� ��Ȳ�� ���� ������ ��� �ʿ��ϴٸ� ����ϱ⿡ ����������. 
	���� ������ ����ε� ȯ���� ������ ���� ���� �͵� ������ ���������� ���ʿ� ������ �� ���� ��ü�� �����Ǵ� ������ �߻��Ѵ�. ��, ������ Ÿ�ӿ����� �ƴ�, ��Ÿ�ӿ��� ������ Ȯ���ϴ� ���̴�.  
	�Դٰ�, �ϳ��� Ŭ������ �Ѵٸ�, ���� �ϳ��� ī�װ��� ���̽� Ŭ������ ���� �� ���ٴ� ������ �ִ�. 
	 ������ �Ϲ�ȭ�� ���, �Ѱ��� ������ ���� �Ļ�Ŭ������ �����ϰ�, �� �ڿ� ��� �Ļ� Ŭ������ ���� �ٸ� ī�װ��� �Ļ�Ŭ������ ����� ���̴�. ��� NxM���� ������ ��� ����������. 
	however, ���¿� �ϳ��� �߰��Ǹ� �ִ� N���� �Ļ� Ŭ������ �� ������ �Ѵ�. ���� �긴�� ���ϰ� ���� 2��° ī������ ����Ű�� ��� Ŭ������ ���� �� ����.
	��, �ι�° ī�װ����� ���������� ���Ǵ� �ڵ尡 �ִٸ�, �Ź� ���� �ۼ������ �Ѵ�.
	 �ټ� ����� ���,  �긮�� ������ Engine*��������� �������, �Ļ� Ŭ�������� NxM�� ����� �ȴ�. ��, GasPoweredLandVehicle�� ���, GasPoweredEngin�� LandBehicle�� ���� Ŭ������ ��ӹ޴� ���̴�.
	��, ������ ��� �����ϸ鼭�� �긮�� ������ ������ ���� �ȵǴ� ����(���ּ��ε� ������ �����)�� �Ÿ� �� �ִ�.(���ʿ� ������ü�� �������ν�)
	however, �긮�� ���� ó�� �� ī�װ��� �ش��Ѵ� �Ļ� Ŭ�������� ����� �ȴ�.
	
	���� ���� 3���� ����߿��� ���������� ����� ����� ���⿡, ��Ȳ�� �°� �ּ��� ����� ��� ����ؾ� �Ѵ�. ���� ����� ���� ���� �ƴ϶� ��Ȳ�� ���� �޶����ٴ� ���� �������! 
*/
