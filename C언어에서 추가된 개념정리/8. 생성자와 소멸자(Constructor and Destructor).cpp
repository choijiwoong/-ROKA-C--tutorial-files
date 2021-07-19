/*[CONSTRUCTOR]_��ü ���� �� ȣ��Ǵ� �Լ� 
#include <iostream>

using namespace std;

class student{//������ . �ʱⰪ�� �����ϴ� �Ǵٸ� ���. �⺻�� class->private, public 
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

student::student(char* _name, int _age, char* _hobby){//�ϴ����� SetInfo�� ���� 
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
	cout<<"�̸�: "<<name<<", ����: "<<age<<", ���: "<<hobby<<endl;
}

void student::Study(){
	cout<<"����!"<<endl;
}

void student::Sleep(){
	cout<<"��!"<<endl;
}

int main()
{
	student stu("��ö��", 16, "��ǻ�� ����");
	
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

/*[DESTRUCTOR]_��ü �Ҹ�� ȣ��Ǵ� �Լ� 
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
	
	return 0;//return �ϸ� �Ҹ��� ȣ�� _�޸� ��ȯ �ÿ� ��ȯ���� ���� �޸� ������ ��ȯ�ϱ� ���� ��� 
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
	MyClass mc2=mc1;//���� char *str�� ���� �����ذ��� ���� ���� �޸� ����� 
	
	mc1.ShowData();
	mc2.ShowData();//�Ҹ��ڰ� ȣ����� ����.  return �� �̹� mc2�� �Ҹ��ڰ� �޸𸮸� �����߱⿡ �̹� ������ ���¿��� mc1�� �Ҹ��ڰ� ȣ��X 
	
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
		MyClass(const MyClass& mc){//Q. MyClass*�� �ϸ� ���� 
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
	MyClass mc2=mc1;//���� char *str�� ���� �����ذ��� ���� ���� �޸� ����� 
	
	mc1.ShowData();
	mc2.ShowData();//�Ҹ��ڰ� ȣ����� ����.  return �� �̹� mc2�� �Ҹ��ڰ� �޸𸮸� �����߱⿡ �̹� ������ ���¿��� mc1�� �Ҹ��ڰ� ȣ��X 
	
	return 0;
} 
