/* [IN C LANGUAGE]
#include <stdio.h>

struct student {
	int id;
	char *name;
	float percentage;
}; // 구조체 뒤에 세미콜론이 와야함

int main() {
	struct student s={1, "김철수", 90.5};
	printf("아이디: %d \n", s.id);
	printf("이름: %s \n", s.name);
	printf("백분율: %f \n", s.percentage);
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
}; // 구조체 뒤에 세미콜론이 와야함

int main() {
	student s={1, "김철수", 90.5};
	cout << "아이디: " << s.id << endl;
	cout << "이름: " << s.name << endl;
	cout << "백분율: " << s.percentage << endl;
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
	void Show() {//Void 함수를 따로 빼어서 void Show()로 구조체 내에 선언할 수 도 있음. 
		cout << "아이디: " << id << endl;
		cout<< "이름: " << name << endl;
		cout << "백분율: " << percentage << endl;
	}//세미콜론 없음 
}; // 구조체 뒤에 세미콜론이 와야함
int main() {
	student s={1, "김철수", 90.5};
	s.Show();
	return 0;
}
*/
//[PRIVATE, PUBLIC]
#include <iostream>

using namespace std;

struct student {
	private://직접 접근이 불가하고 내부 접근만 가능함. 
		int id;
		char *name;
		float percentage;
	public:
		void Show();
		void SetInfo(int _id, char * _name, float _percentage);
}; // 구조체 뒤에 세미콜론이 와야함
void student::Show() {//student::Show()식으로 접근 
	cout << "아이디: " << id << endl;
	cout << "이름: " << name << endl;
	cout << "백분율: " << percentage << endl;
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
	s.SetInfo(1, "김철수", 90.5);
	s.Show();
	return 0;
}
