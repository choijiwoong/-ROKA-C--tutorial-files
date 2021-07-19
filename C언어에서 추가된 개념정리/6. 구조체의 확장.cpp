/* [IN C LANGUAGE]
#include <stdio.h>

struct student {
	int id;
	char *name;
	float percentage;
}; // ����ü �ڿ� �����ݷ��� �;���

int main() {
	struct student s={1, "��ö��", 90.5};
	printf("���̵�: %d \n", s.id);
	printf("�̸�: %s \n", s.name);
	printf("�����: %f \n", s.percentage);
	return 0;
}//typedef
*/

/* [STRUCT OMITTED IN C++ LANGUAGE]
#include <iostream>

using namespace std;

struct student {
	int id;
	char *name;
	float percentage;
}; // ����ü �ڿ� �����ݷ��� �;���

int main() {
	student s={1, "��ö��", 90.5};
	cout << "���̵�: " << s.id << endl;
	cout << "�̸�: " << s.name << endl;
	cout << "�����: " << s.percentage << endl;
	return 0;
}
*/

/* [FUNC INT STRUCT]
#include <iostream>

using namespace std;

struct student {
	int id;
	char *name;
	float percentage;
	void Show() {//Void �Լ��� ���� ��� void Show()�� ����ü ���� ������ �� �� ����. 
		cout << "���̵�: " << id << endl;
		cout<< "�̸�: " << name << endl;
		cout << "�����: " << percentage << endl;
	}//�����ݷ� ���� 
}; // ����ü �ڿ� �����ݷ��� �;���
int main() {
	student s={1, "��ö��", 90.5};
	s.Show();
	return 0;
}
*/
//[PRIVATE, PUBLIC]
#include <iostream>

using namespace std;

struct student {
	private://���� ������ �Ұ��ϰ� ���� ���ٸ� ������. 
		int id;
		char *name;
		float percentage;
	public:
		void Show();
		void SetInfo(int _id, char * _name, float _percentage);
}; // ����ü �ڿ� �����ݷ��� �;���
void student::Show() {//student::Show()������ ���� 
	cout << "���̵�: " << id << endl;
	cout << "�̸�: " << name << endl;
	cout << "�����: " << percentage << endl;
}

void student::SetInfo(int _id, char * _name, float _percentage)
{
	id = _id;
	name = _name;
	percentage = _percentage;
}

int main() {
	student s;
	//s.id = 1;
	s.SetInfo(1, "��ö��", 90.5);
	s.Show();
	return 0;
}
