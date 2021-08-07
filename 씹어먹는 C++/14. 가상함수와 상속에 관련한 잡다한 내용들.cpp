#include <iostream>

/*1
class Parent{
	public:
		Parent(){ std::cout<<"Parent 생성자 호출"<<std::endl; }
		virtual ~Parent(){ std::cout<<"Parent 소멸자 호출"<<std::endl; }//set virtual! for prevent memory leak.
};
class Child:public Parent{
	public:
		Child():Parent(){ std::cout<<"Child 생성자 호출"<<std::endl; }
		~Child(){ std::cout<<"Child 소멸자 호출"<<std::endl; }
};

int main(){
	std::cout<<"--평범한 Child 만들었을 때--"<<std::endl;
	{Child c;}
	std::cout<<"--Parent 포인터로 Child 가리켰을 때--"<<std::endl;
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
			std::cout<<"왈왈"<<std::endl;
		}
};
class Cat:public Animal{
	public:
		Cat():Animal(){}
		void speak() override {//must override!
			std::cout<<"야옹야옹"<<std::endl;
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
		A() { std::cout << "A 생성자 호출" << std::endl; }
}; 

class B{
	public:
		int b;
		B() { std::cout << "B 생성자 호출" << std::endl; }
};

class C: public B, public A{//it can be expressed by map : class C->class A & class B it just means C has content of A and B.
	public:
		int c;
		C() : A(), B() { std::cout << "C 생성자 호출" << std::endl; }
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
[1.	virtual 소멸자] 
1.	Child소멸자가 호출될 때, Child는 이미 Parent를 상속받는다는 것을 알고 있기 때문에, Child 소멸자가 '알아서' Parent 소멸자를 호출해준다.
	반면에, Parent 소멸자를 먼저 호출하게 되면, Parent는 Child가 있는지 없는지 모르기 때문에, child소멸자를 호출해줄 수 없다.(Parent *p=new Child()) 
	 이와 같은 이유로, 상속될 여지가 있는 Base Class들은 소멸자를 반드시 virtual로 만들어야 나중에 문제가 발생하는 것을 막을 수 있다.
	  
[2.	레퍼런스도 된다]_포인터자리에 
1.	제목이 곧 내용

[3.	가상 함수의 구현 원리]
1.	그냥 모든 함수들을 virtual로 만들어버리면 안되는가? ->모든 함수들을 가상 함수로 만듬으로써, 언제나 동적 바인딩이 제대로 동작하게 끔 하여 실제로 JAVA는 모든 함수들이 default로 virtual함수로 선언된다.
	하지만, virtual을 사용하게 되면 약간의 오버헤드(overhead)가 존재한다._시간이 더 걸림. 이는 최적화가 매우 중요한 분야에서 감안할 필요가 있기 때문에, 다른 언어들과는 다르게 C++에서는 멤버 함수가 default로 virtual이 되지 않는다. 
2.	C++는 클래스에 가상함수가 하나라도 존재할 경우 전화번호부와 같은 가상 함수 테이블(virtual function table; vtable)을 만들게 된다. 
	이는 함수의 이름과 실제로 어떤 함수가 대응되는지를 테이블로 저장하고 있다. 
	 Child의 func3()같은 비 가상 함수들은 특별한 단계를 거치지 않고, func3()을 호출하면 직접 실행된다.
	하지만, 가상함수를 호출하였을 때는, 가상함수테이블을 한 단계 더 걸쳐서, 실제로 어떤 함수를 고를지 결정하게 된다.

[4.	순수 가상 함수(pure virtual function)와 추상 클래스(abstract class)]
1.	가상 함수에 =0;을 붙여서 반드시 오버라이딩 되도록 만든 함수를 완전한 가상 함수, 순수 가상 함수(pure virtual function)이라고 한다. 
2.	순수 가상 함수를 최소 한 개 이상 포함하고 있는 클래스는 객체를 생성할 수 없으며, 인스턴스화 시키기 위해서는 이 클래스를 상속받는 클래스를 만들어서 모든 순수 가상 함수를 오버라이딩 해야 한다.
3.	이처럼 순수 가상 함수를 최소 한개 포함하고 있는 즉, 반드시 상속 되어야 하는 클래스를 가리켜 추상 클래스(Abstract class)라고 부른다.
4.	참고로 private 안에 순수 가상 함수를 정의해도 된다. 똑같이 오버라이드는 되지만 단지 자식 클래스에서 호출을 못 할 뿐이다.. 
5.	사용 이유는, 상속받아서 사용하는 사람에게 "이 기능은 일반적인 상황으로 정의하기 힘드니 너가 직접 특수화 되는 클래스에 맞추어서 만들어서 써라"하고 하는 것이다.
	위의 경우 Animal이 speak하는 것은 맞지만, 동물들마다 소리가 다르기에 순수 가상함수로 만듬으로써, Animal들은 speak한다는 의미 전달과, 알아서 구현하면 된다.
6.	추상클래스의 또다른 특징은, 객체 생성은 안되지만, 추상 클래스를 가리키는 포인터는 문제없이 만들 수 있다는 것이다. virtual and override!

[5. 다중 상속(multiple inheritance)]
1.	C++에서는 한 클래스가 다른 여러 개의 클래스들을 상속 받는 것을 허용하는데, 이를 다중 상속(multiple inheritnace)라고 부른다. 
2.	상속 순서에 따라 생성자 호출. 

[6. 다중 상속 시 주의할 점]
1.	두 개의 클래스에서 이름이 같은 멤버 변수가 있는데, 이 두 클래스를 다중 상속하여 해당 멤버 변수에 접근하면, 당연히 어느 클래스의 멤버 변수에 접근해야하는지 구분할 수 없다는 오류를 발생시킨다. 이는 자명하게 함수도 마찬가지이다. 
2.	또 한가지 주의해야할 점은, (공포의) 다이아몬드 상속(dreadful_diamond of derivation)이라고 부르는 다중 상속 형태이다. 
	베이스 클래스로 Human이 있고, 이를 상속받는 HandsomeHuman, SmartHuman클래스가 있다. 그리고 HandsomeHuman과 SmartHuman을 다중 상속받는 Me라는 클래스가 있다.
	즉, 상속이 되는 두 개의 클래스가 공통의 베이스 클래스를 포함하고 있는 형태는 다이아몬드 상속이라고 부른다.
	이 경우, 뭐 Handsome, SmartHuman에서 뭔짓거릴 다 해봐도 결국 Me에서 Human의 모든 내용이 중복되는 문제가 발생한다.??? . 
	 이를 해결하기 위해선, Human을 Smart, Handsome이 virtual로 상속받으면 된다. 고로 컴파일러가 언제가 Human을 한 번만 포함하도록 지정하는 것이다.
	참고로, 위와 같은 가상 상속 시에, Me의 생성자에서 HandsomeHuman과 SmartHuman의 생성자와 더불어 Human의 생성자 또한 호출해주어야 한다.???
[7.	다중 상속은 언제 사용해야 할까?]
1.	Vehicle가 LandVehicle를 참조하고 있다면, Vehicle의 멤버 함수를 호출했을 때, LandVehicle의 멤버 함수가 오버라이드되서 호출되기를 바라는가?
2.	Vehicle가 GasPoweredVehicle를 참조하고 있다면, Vehicle의 멤버 함수를 호출했을 때, GasPoweredVehicle의 멤버 함수가 오버라이드되서 호출되기를 바라는가?
3.	1,2가 모두 예라는 대답이 나온다면, 다중상속을 사용하는 것이 좋지만, 몇가지 더 고려해야한다. 환경이 N개이고, 동력원의 종류가 M개라고 해본다면
	크게 3가지 방법으로 클래스를 디자인 할 수 있다. 바로 브리지 패턴(bridge pattern), 중첩된 일반화 방식(nested generalization), 다중 상속이다.
	 브리지 패턴의 경우, 동력원과 환경 중 한가지 카테고리를 아예 멤버 포인터로 만드는 것이다. 즉 Vehicle의 파생클래스로 환경클래스들이 있고, Engine*과 같은 멤버변수로 어떤 엔진을 사용할 것인지 가리키게 설정하는 방식이다.
	이 경우, 환경이 추가된다 하더라도 클래스를 1개만 더 만들며 된다. 즉 N+M의 클래스만 생성하면된다. 
	however, N+M개의 가지수만 제어하므로 NxM과 같이 모든 상황에 대한 섬세한 제어가 필요하다면 사용하기에 불편해진다. 
	또한 엔진이 페달인데 환경이 우주인 경우와 같은 것도 생성이 가능해지는 애초에 생성할 수 없는 객체가 생성되는 오류가 발생한다. 즉, 컴파일 타임에서가 아닌, 런타임에서 오류를 확인하는 것이다.  
	게다가, 하나만 클래스로 한다면, 남은 하나의 카테고리의 베이스 클래스를 만들 수 없다는 단점이 있다. 
	 중접된 일반화의 경우, 한가지 계층을 먼저 파생클래스로 생성하고, 그 뒤에 모든 파생 클래스에 대해 다른 카테고리의 파생클래스를 만드는 것이다. 고로 NxM개의 섬세한 제어가 가능해진다. 
	however, 동력원 하나가 추가되면 최대 N개의 파생 클래스를 더 만들어야 한다. 또한 브릿지 패턴과 같이 2번째 카데고리를 가리키는 기반 클래스를 만들 수 없다.
	즉, 두번째 카테고리에서 공통적으로 사용되는 코드가 있다면, 매번 새로 작성해줘야 한다.
	 다숭 상속의 경우,  브리지 패턴의 Engine*멤버변수가 사라지고, 파생 클래스들을 NxM개 만들게 된다. 즉, GasPoweredLandVehicle의 경우, GasPoweredEngin과 LandBehicle두 개의 클래스를 상속받는 것이다.
	즉, 섬세한 제어가 가능하면서도 브리지 패턴의 단점인 말도 안되는 조합(우주선인데 동력이 페달인)을 거를 수 있다.(애초에 정의자체를 안함으로써)
	however, 브리지 패턴 처럼 각 카테고리에 해당한느 파생 클래스들을 만들게 된다.
	
	따라서 위의 3가지 방식중에서 절대적으로 우월한 방식은 없기에, 상황에 맞게 최선의 방식을 골라서 사용해야 한다. 다중 상속은 만능 툴이 아니라 상황에 따라 달라진다는 것을 명심하자! 
*/
