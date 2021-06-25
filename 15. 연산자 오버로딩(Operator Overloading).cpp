#include <iostream>
#include <cstring>
\
using namespace std;

/*[OPERATOR OVERLOADING]
class NUMBOX
{
	private:
		int num1, num2;
	public:
		NUMBOX(int num1, int num2) : num1(num1), num2(num2) { }
		void ShowNumber(){
			cout << "num1: " << num1 << ", num2: " << num2 << endl;
		}
		//NUMBOX operator+(NUMBOX &ref){//���⿡ ���ڳ����� ���ڸ� NUMBOX Ŭ������ ����.error 
		//	return NUMBOX(num1+ref.num1, num2+ref.num2);
		//}
		NUMBOX operator+(int num){
			return NUMBOX(num1+num, num2+num);
		}
};

int main()
{
	NUMBOX nb1(10, 20);
	NUMBOX nb2(5, 2);
	//NUMBOX result = nb1 + nb2;
	//result=nb1.operator+(nb);//�Լ� ȣ�� ������� +ó�� 
	
	nb1.ShowNumber();
	nb2.ShowNumber();
	//result.ShowNumber();
	
	nb1=nb1+5;
	nb1.ShowNumber();
	
	return 0;
}
*/

/*[GLOBAL FUNCTION OVERLOADING]
class NUMBOX{
	private:
		int num1, num2;
	public:
		NUMBOX(int num1, int num2):num1(num1),num2(num2){}//������ 
		void ShowNumber(){
			cout<<"num1: "<<num1<<", num2: "<<num2<<endl;
		}
		NUMBOX operator+(int num){
			return NUMBOX(num1+num, num2+num);
		}
		friend NUMBOX operator+(int num, NUMBOX ref);
};

NUMBOX operator+(int num, NUMBOX ref){
	ref.num1+=num;
	ref.num2+=num;
	
	return ref;
}

int main(){
	NUMBOX nb1(10,20);
	NUMBOX result=10+nb1+40;
	
	nb1.ShowNumber();
	result.ShowNumber();
	
	return 0;
}
*/

/*[UNARY OPERATOR OVERLOADING]
class NUMBOX{
	private:
		int num1, num2;
	public:
		NUMBOX() {}
		NUMBOX(int num1, int num2): num1(num1), num2(num2) {}
		void ShowNumber(){
			cout<<"num1: "<<num1<<", num2: "<<num2<<endl;
		}
		NUMBOX operator++(){//���� ���� ����++nb 
			num1+=1;
			num2+=1;
			return *this;//this�� ��ü�� �ּҸ� ��Ÿ���� *this�� ��ü ��ü�� ��Ÿ�� 
		}
		NUMBOX operator++(int){//int�� ���� ���� ������ ������ �����ϱ� �������� �������� ���� �ϴ°� �ƴ� 
			NUMBOX temp(*this);/���� ���� ���� nb++ 
			num1+=1;
			num2+=1;
			return temp;
		}
};

int main(){
	NUMBOX nb1(10,20);
	NUMBOX nb2;
	
	nb2=nb1++;
	nb2.ShowNumber();
	nb1.ShowNumber();
	
	nb2=++nb1;
	nb2.ShowNumber();
	nb1.ShowNumber();
	
	return 0;
}
*/

/*[SUBSTITUTE OPERATOR OVERLOADING]
class A{
	private:
		int num1, num2;
	public:
		A() {};//default ������
		A(int num1, int num2): num1(num1), num2(num2){}
		void ShowData() {cout<<num1<<", "<<num2<<endl;}
};

class B{
	private:
		int num1, num2;
	public:
		B() {}
		B(int num1, int num2): num1(num1), num2(num2) {}
		void ShowData() {cout<<num1<<", "<<num2<<endl;}
};

int main(){
	A a1(10, 50);
	A a2;
	B b1(10, 20);
	B b2;
	
	a2=a1;//���� operator=���ص� ���� but ���� ����(���ϰ�ü) 
	b2=b1;
	
	a2.ShowData();
	b2.ShowData();
	
	return 0;
}
*/

/*[PROBLEM OCCUR]
class Student
{
	private:
		char * name;
		int age;
	public:
		Student(char * name, int age) : age(age)
		{
			this->name = new char[10];
			strcpy(this->name, name);
		}
		void ShowInfo() {
			cout << "�̸�: " << name << endl;
			cout << "����: " << age << endl;
		}
		~Student()
		{
			delete []name;
			cout << "~Student �Ҹ��� ȣ��!" << endl;
		}
};

int main()
{
	Student st1("��ö��", 14);
	Student st2("ȫ�浿", 15);
	
	st2 = st1;//���� �߻�. ���� ����� �̷�� ���⿡ st2�� st1�� �ּҸ� ����Ŵ 
	
	st1.ShowInfo();
	st2.ShowInfo();
	
	return 0;//�� �� �������� �Ҹ��ڰ� ȣ��� �� st1�� �ּҴ� �ߺ����� delete[]�ǰ�, st2�� delete�Ұ�. 
}
*/

//[SOLUTION]
class Student
{
	private:
		char *name;
		int age;
	public:
		Student(char *name, int age) : age(age)
		{
			this->name = new char[10];
			strcpy(this->name, name);
		}
		void ShowInfo() {
			cout << "�̸�: " << name << endl;
			cout << "����: " << age << endl;
		}
		Student& operator=(Student& ref)
		{
			delete []name;
			name = new char[10];
			strcpy(name, ref.name);
			age = ref.age;
			return *this;//��ü ��ü�� ���� 
		}
		~Student()
		{
			delete []name;
			cout << "~Student �Ҹ��� ȣ��!" << endl;
		}
};

int main()
{
	Student st1("��ö��", 14);
	Student st2("ȫ�浿", 15);

	st2 = st1;
	
	st1.ShowInfo();
	st2.ShowInfo();
	
	return 0;
}


