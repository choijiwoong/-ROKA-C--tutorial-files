/*[INFERITANCE]
#include <iostream>
#include <cstring>

using namespace std;

class Human{//�θ� Ŭ����(����, ����, ����) 
	private:
		int age;
		char name[10];
		char hobby[20];
	public:
		Human(int _age, char* _name, char* _hobby): age(_age){//human class�� _age�� �Ѿ���� �� ������ age �ʱ�ȭ 
			strcpy(name, _name);//���� ����� Member Initializer��� �� 
			strcpy(hobby, _hobby);
		}
		void getup(){
			cout<<"���!"<<endl;
		}
		void sleep(){
			cout<<"��ħ!"<<endl;
		}
		void eat(){
			cout<<"�Ļ�!"<<endl;
		}
		void study(){
			cout<<"����!"<<endl;
		}
		void showInfo(){
			cout<<"�̸�: "<<name<<endl;
			cout<<"����: "<<age<<endl;
			cout<<"���: "<<hobby<<endl;
		}
};

class Student : public Human{//�ڽ� Ŭ����(����, ����, ����) 
	private:
		char school[30];
	public:
		Student(int _age, char* _name, char *_hobby, char* _school): Human(_age, _name, _hobby){
			strcpy(school, _school);//���� ��� �̴ϼȶ�����->�޸տ� �Է°� �ְ� ���°ɷ� �ʱ�ȭ 
		}
		void schoolInfo(){
		cout<<"�Ҽ� �б�: "<<school<<endl;
		}
};

int main()
{
	Student stu(18, "��ö��", "���α׷���", "�ڹٰ���б�");
	
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
		void ShowInfo(){//memInit�Լ����� �� �ް� �װɷ� private���� �ʱ�ȭ *******
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

class Base: private Parent{};//����� private �� �ϸ� public, protected�� �� privatize. 
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

class Base:protected Parent {};//�� �׷����� protected���� ���� ������ ���� �͵��� protectize. 
int main()//protected�� �ܺ�����X, �Ļ� Ŭ���� ������ ���� ���� 
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
