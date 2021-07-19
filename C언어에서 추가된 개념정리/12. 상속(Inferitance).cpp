/*[INFERITANCE]
#include <iostream>
#include <cstring>

using namespace std;

class Human{//부모 클래스(상위, 기초, 슈퍼) 
	private:
		int age;
		char name[10];
		char hobby[20];
	public:
		Human(int _age, char* _name, char* _hobby): age(_age){//human class로 _age가 넘어오면 그 값으로 age 초기화 
			strcpy(name, _name);//위의 방법을 Member Initializer라고 함 
			strcpy(hobby, _hobby);
		}
		void getup(){
			cout<<"기상!"<<endl;
		}
		void sleep(){
			cout<<"취침!"<<endl;
		}
		void eat(){
			cout<<"식사!"<<endl;
		}
		void study(){
			cout<<"공부!"<<endl;
		}
		void showInfo(){
			cout<<"이름: "<<name<<endl;
			cout<<"나이: "<<age<<endl;
			cout<<"취미: "<<hobby<<endl;
		}
};

class Student : public Human{//자식 클래스(하위, 유조, 서브) 
	private:
		char school[30];
	public:
		Student(int _age, char* _name, char *_hobby, char* _school): Human(_age, _name, _hobby){
			strcpy(school, _school);//위에 멤버 이니셜라이저->휴먼에 입력값 넣고 나온걸로 초기화 
		}
		void schoolInfo(){
		cout<<"소속 학교: "<<school<<endl;
		}
};

int main()
{
	Student stu(18, "김철수", "프로그래밍", "자바고등학교");
	
	stu.schoolInfo();
	stu.getup();
	stu.eat();
	stu.study();
	stu.sleep();
	
	return 0;
}
*/

/*[MEMBER INITIALIZER]
#include <iostream>

using namespace std;

class memInit{
	private:
		int num1, num2;
	public:
		memInit(int _num1, int _num2): num1(_num1), num2(_num2){}
		void ShowInfo(){//memInit함수에서 넘 받고 그걸로 private변수 초기화 *******
			cout<<"num1: "<<num1<<", num2: "<<num2<<endl;
		}
}; 

int main()
{
	memInit mi(50, 70);
	
	mi.ShowInfo();
	return 0;
}
*/

/*[PRIVATE INHERITANCE]
#include <iostream>

using namespace std;

class Parent{
	private:
		int num1;
	public:
		int num2;
	protected:
		int num3;
};

class Base: private Parent{};//상속을 private 로 하면 public, protected도 다 privatize. 
int main(){
	Base base;
	
	cout<<base.num1<<endl;//error
	cout<<base.num2<<endl;//error
	cout<<base.num3<<endl;//error
	
	return 0;
}
*/

/*[PROTECTED INHERITANCE]
#include <iostream>

using namespace std;

class Parent{
	private:
		int num1;
	public:
		int num2;
	protected:
		int num3;
}; 

class Base:protected Parent {};//늘 그렇듯이 protected보다 접근 범위가 넓은 것들은 protectize. 
int main()//protected는 외부접근X, 파생 클래스 내에서 접근 가능 
{//private<protected<public 
	Base base;
	
	cout<<base.num1<<endl;//error
	cout<<base.num2<<endl;//error
	cout<<base.num3<<endl;//error**************
	
	return 0;
}
*/

//[PUBLIC INHERITANCE]
#include <iostream>

using namespace std;

class Parent{
	private:
		int num1;
	public:
		int num2;
	protected:
		int num3;
};

class Base : public Parent{};
int main(){
	Base base;
	
	cout<<base.num1<endl;//error
	cout<<base.num2<<endl;//ok
	cout<<base.num3<endl;//error
	
	return 0;
}
