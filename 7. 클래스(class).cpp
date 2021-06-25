//c is struct, then c++ is class. it's just for confusion of C lang. not different except for private, public

#include <iostream>

using namespace std;

class student{
	private:
		char * name;
		int age;
		char * hobby;
	public:
		void ShowInfo();
		void SetInfo(char * _name, int _age, char* _hobby);
		void Study();
		void Sleep();
};

void student::ShowInfo(){
	cout<<"이름: "<<name<<", 나이: "<<age<<", 취미: "<<hobby<<endl;
}

void student::SetInfo(char *_name, int _age, char *_hobby)
{
	name=_name;
	age=_age;
	hobby=_hobby;
}

void student::Study(){
	cout<<"공부!"<<endl;
}

void student::Sleep(){
	cout<<"잠!"<<endl;
}

int main()
{
	student stu;
	
	stu.SetInfo("김철수", 16, "컴퓨터 게임");
	stu.ShowInfo();
	
	while(true){
		stu.Study();
		stu.Sleep();
	}
	
	return 0;
}

//Object , Instance. 철수는 학생 클래스의 인스턴스이다. 철수는 학생 개체이다. 
