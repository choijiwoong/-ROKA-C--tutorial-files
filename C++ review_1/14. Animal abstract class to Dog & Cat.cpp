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

/*동적 바인딩 
1.	상속시 Based 클래스의 소멸자를 가상함수(virtual)로 만들자 because of memory leak 
2.	모든 함수를 virtual로 만들지 않는 이유는 일반적인 상속관계에서의 호출과 달리, 실제로 어떤 함수를 고를지 가상 함수 테이블을 통해 결정하기 때문에 아주 약간의 오버헤드가 발생하기 때문이다
3.	virtual함수에 =0;을 붙여 순수 가상 함수(pure virtual function)을 만들 수 있다. 이때 이를 인스턴스화 하기 위해선 상속받는 클래스를 만들어 순수 가상 함수들으 오버라이딩 시켜주어야 한다.
	이처럼 순수 가상 함수를 갖고있는, 즉 반드시 상속되어야만 사용할 수 있는 클래스를 추상 클래스(abstrat class)라고 한다. like 설계도
4.	다이아몬드 상속 문제를 해결하려면 가장 상위 클래스를 virtual로 상속받아 상위 클래스의 멤버를 한 번만 포함하도록 하면 된다.
5.	클래스를 설계하는 방법으로 크게 브리지 패턴, 중첩된 일반화 방식, 다중 상속이 있다. 
*/
