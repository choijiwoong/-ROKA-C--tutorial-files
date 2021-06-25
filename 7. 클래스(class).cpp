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
	cout<<"�̸�: "<<name<<", ����: "<<age<<", ���: "<<hobby<<endl;
}

void student::SetInfo(char *_name, int _age, char *_hobby)
{
	name=_name;
	age=_age;
	hobby=_hobby;
}

void student::Study(){
	cout<<"����!"<<endl;
}

void student::Sleep(){
	cout<<"��!"<<endl;
}

int main()
{
	student stu;
	
	stu.SetInfo("��ö��", 16, "��ǻ�� ����");
	stu.ShowInfo();
	
	while(true){
		stu.Study();
		stu.Sleep();
	}
	
	return 0;
}

//Object , Instance. ö���� �л� Ŭ������ �ν��Ͻ��̴�. ö���� �л� ��ü�̴�. 
