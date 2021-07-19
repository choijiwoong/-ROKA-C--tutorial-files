/*[CONSTRUCTOR]_객체 생성 시 호출되는 함수 
#include <iostream>

using namespace std;

class student{//생성자 . 초기값을 세팅하는 또다른 방법. 기본꼴 class->private, public 
	private:
		char* name;
		int age;
		char* hobby;
	public:
		student(char* _name, int _age, char* _hobby); 
		void ShowInfo();
		void Study();
		void Sleep();
};

student::student(char* _name, int _age, char* _hobby){//하는일은 SetInfo와 동일 
	name=_name;
	age=_age;
	hobby=_hobby;
}
/*
void student::SetInfo(char *_name, int _age, char *_hobby)
{
	name=_name;
	age=_age;
	hobby=_hobby;
}


void student::ShowInfo(){
	cout<<"이름: "<<name<<", 나이: "<<age<<", 취미: "<<hobby<<endl;
}

void student::Study(){
	cout<<"공부!"<<endl;
}

void student::Sleep(){
	cout<<"잠!"<<endl;
}

int main()
{
	student stu("김철수", 16, "컴퓨터 게임");
	
	stu.ShowInfo();
	
	
	while(ture):
		stu.Study();
		stu.Sleep();
		
	return 0;
}
*/

/*[CONSTRUCTOR OVERLOADING]
#include <iostream>

using namespace std;

class ExConstructor{
	public:
		ExConstructor(){
			cout<<"ExConstructor() called!"<<endl;
		}
		
		ExConstructor(int a){
			cout<<"ExConstructor(int a) called!"<<endl;
		}
		
		ExConstructor(int a, int b){
			cout<<"ExConstructor(int a, int b) called!"<<endl;
		}
};

int main()
{
	ExConstructor ec1;
	ExConstructor ec2(10);
	ExConstructor ec3(20, 10);
	
	return 0;
}
*/

/*[COPY CONSTRUCTOR]
#include <iostream>

using namespace std;

class MyClass{
	private:
		int num1;
		int num2;
	public:
		MyClass(int a, int b){
			num1=a;
			num2=b;
		}
		
		void ShowData(){
			cout<<"num1: "<<num1<<", num2: "<<num2<<endl;
		}
};

int main(){
	MyClass mc1(50,40);
	MyClass mc2=mc1;//MyClass(const MyClass& mc)
	
	mc2.ShowData();
	return 0;
}
*/

/*[DESTRUCTOR]_객체 소명시 호출되는 함수 
#include <iostream>

using namespace std;

class ExConstructor{
	public:
		ExConstructor(){
			cout<<"ExConstructor() called!"<<endl;
		}
		
		~ExConstructor(){
			cout<<"~ExConstructor() called!"<<endl;
		}
};

int main()
{
	ExConstructor ec;
	
	return 0;//return 하며 소멸자 호출 _메모리 반환 시에 반환되지 않은 메모리 공간을 반환하기 위해 사용 
}
*/

/*[PROBLEM OF SWALLOW COPY]
#include <iostream>
#include <string.h>

using namespace std;

class MyClass{
	private:
		char *str;
	public:
		MyClass(const char *aStr){
			str=new char[strlen(aStr)+1];
			strcpy(str, aStr);
		}
		~MyClass(){
			delete []str;
			cout<<"~MyClass() called!"<<endl;
		}
		void ShowData(){
			cout<<"str: "<<str<<endl;
		}
}; 

int main(){
	MyClass mc1("MyClass!");
	MyClass mc2=mc1;//같은 char *str의 값도 복사해가서 서로 같은 메모리 사용중 
	
	mc1.ShowData();
	mc2.ShowData();//소멸자가 호출되지 않음.  return 시 이미 mc2의 소멸자가 메모리를 해제했기에 이미 해제된 상태에서 mc1의 소멸자가 호출X 
	
	return 0;
}
*/

//[DEEP COPY]
#include <iostream>
#include <string.h>

using namespace std;

class MyClass{
	private:
		char *str;
	public:
		MyClass(const char *aStr){
			str=new char[strlen(aStr)+1];
			strcpy(str, aStr);
		}
		MyClass(const MyClass& mc){//Q. MyClass*로 하면 오류 
			str=new char[strlen(mc.str)+1];
			strcpy(str, mc.str);
		}
		~MyClass(){
			delete []str;
			cout<<"~MyClass() called!"<<endl;
		}
		void ShowData(){
			cout<<"str: "<<str<<endl;
		}
}; 

int main(){
	MyClass mc1("MyClass!");
	MyClass mc2=mc1;//같은 char *str의 값도 복사해가서 서로 같은 메모리 사용중 
	
	mc1.ShowData();
	mc2.ShowData();//소멸자가 호출되지 않음.  return 시 이미 mc2의 소멸자가 메모리를 해제했기에 이미 해제된 상태에서 mc1의 소멸자가 호출X 
	
	return 0;
} 
