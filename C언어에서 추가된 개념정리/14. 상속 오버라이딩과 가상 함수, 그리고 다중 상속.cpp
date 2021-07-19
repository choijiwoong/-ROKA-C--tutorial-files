#include <iostream>

using namespace std;

/*[INHERITANCE OVERRIDING]
class A{
	public:
		void over() {
			cout << "A 클래스의 over 함수 호출!" << endl;
		}
};

class B: public A{
	public:
		void over(){
			cout<<"B 클래스의 over 함수 호출!"<<endl;
		}
};

int main()
{
	B b;
	b.over();//부모의 멤버 함수와 원형이 완전히 같아야 함 
	//오버라이딩 시 부모의 클래스 함수가 모두 가려짐. 
	
	//근데 그렇다고 또 부모함수의 클래스 함수를 못 호출하는 것은 아님.
	b.A::over();
	 
	return 0;
}//오버로딩은 이름같은함수 다르게 쓰는거 오버라이드는 가려지는거
*/ 

/*[VIRTUAL FUNCTION]
class Parent {
	public:
		//void func() { cout << "부모 클래스의 func 함수 호출!" << endl; }
		virtual void func() { cout << "부모 클래스의 func 함수 호출!" << endl; } 
};

class Child : public Parent {
	public:
		//void func() { cout << "자식 클래스의 func 함수 호출!" << endl; }
		virtual void func() { cout << "자식 클래스의 func 함수 호출!" << endl; }
};//virtual 함수를 사용하면 컴파일러가 포인터변수의 자료형을 고려하는 것이 아닌 실제 가리키는 것을 담음 

int main()
{
	Parent P, *pP;
	Child C;
	
	pP=&P;
	pP->func();
	pP=&C;//여기에서 자식함수의 주소를 담는 듯 하지만, 포인터변수의 자료형을 컴파일러가 고려하기 때문에
	//부모함수로 인식함. 
	pP->func();//자식함수가 아닌 부모 호출! 
	
	return 0;
}
*/

/*[PURE VIRTUAL FUNCTION] 
class Parent{
	public:
		virtual void func()=0;
};

class Child: public Parent{
	public:
		virtual void func(){ cout << "자식 클래스의 func 함수 호출"<<endl;}//순수 가상함수는 자식클래스에서 반드시 재정의. 
};//오버라이딩 

int main()
{
	//Parent P; //error! 순수가상함수는 몸체가 없어 정의 불가.  
	Parent *P;//포인터는 가능 
	
	P=new Child;
	P->func();
	
	return 0;
}
*/

//[MULTIPLE INHERITANCE]
class ParentOne {
 	public:
		void funcone() { cout << "ParentOne 클래스에서 funcone() 호출!" << endl; }
};

class ParentTwo {
	public:
		void functwo() { cout << "ParentTwo 클래스에서 functwo() 호출!" << endl; }
};

class Child : public ParentOne, public ParentTwo {
	public:
	void func() { funcone(); functwo(); }
};

int main()
{
	Child child;
	child.func();
	
	return 0;
}

//다중상속은 여러 문제. 두 클래스에서 같은 이름의 함수가 있다면 어느 함수를 호출할 지 모르는 문제발생.
// 다이아몬드상속을 사용하여 abcd 중 d-b-a, d-c-a여서 같은 이름의 함수를 호출하는 this를 다르게 하는 해결책 
//근데 걍 사용 자제 
