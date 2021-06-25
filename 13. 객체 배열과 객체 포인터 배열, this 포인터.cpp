#include <iostream>
#include <cstring>

using namespace std;

/*[OBJECT ARRAY]
class Student{
	private:
		char name[10];
		int age;
		int studentID;
	public:
		Student() {cout<<"생성자 호출!"<<endl;}
//Student(char * _name, int _age, int _studentID) : age(_age), studentID(_studentID) { strcpy(name, _name); }
		void SetInfo(char * _name, int _age, int _studentID){
			strcpy(name, _name);
			age=_age;
			studentID=_studentID;
		}
		void GetInfo()
		{
			cout << "이름: " << name << endl;
			cout << "나이: " << age << endl;
			cout << "학번: " << studentID << endl;
		}
		~Student() {cout << "소멸자 호출"<<endl;}
};

int main(){
	Student student[5];
	char name[10];
	int age, studentID;
	
	for(int i=0; i<5;i++){
		cin >> name>>age >>studentID;
		student[i].SetInfo(name, age, studentID);
	}
	for(int i=0;i<5;i++)
		student[i].GetInfo();
}
*/

/*[OBJECT POINTER ARRAY]
class Student
{
	private:
	char name[10];
	int age;
	int studentID;
	public:
	Student(char * _name, int _age, int _studentID) : age(_age), studentID(_studentID) { strcpy(name, _name); }
	void GetInfo()
	{
		cout << "이름: " << name << endl;
		cout << "나이: " << age << endl;
		cout << "학번: " << studentID << endl;
	}
};

int main()
{
	Student * student[3];
	char name[10];
	int age, studentID;
	for(int i=0; i<3; i++) {
		cin >> name >> age >> studentID;
		student[i] = new Student(name, age, studentID);//동적 할당 
	}
	for(int i=0; i<3; i++)
	student[i]->GetInfo();//***
	delete student[0];
	delete student[1];
	delete student[2];
	
	return 0; 
}
*/

//[THIS POINTER]//자기 참조 포인터
class MyClass{
	private:
		int num1, num2;
	public:
		MyClass(int num1, int num2){
			this->num1=num1;//use of this pointer
			this->num2=num2;//근데 걍 이럴거면 변수 이름을 바꿔랏 
		}
		void GetInfo(){
			cout<<"num1: "<<num1<<endl;
			cout<<"num2: "<<num2<<endl;
		}
}; 

int main(){
	MyClass mc(10, 20);
	
	mc.GetInfo();
	return 0;
}

