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
		//NUMBOX operator+(NUMBOX &ref){//여기에 숫자넣으면 숫자를 NUMBOX 클래스로 받음.error 
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
	//result=nb1.operator+(nb);//함수 호출 방식으로 +처리 
	
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
		NUMBOX(int num1, int num2):num1(num1),num2(num2){}//생성자 
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
		NUMBOX operator++(){//전위 증가 연산++nb 
			num1+=1;
			num2+=1;
			return *this;//this는 객체의 주소를 나타내고 *this는 객체 자체를 나타냄 
		}
		NUMBOX operator++(int){//int의 뜻은 단지 전위와 후위를 구분하기 위함이지 정수형을 어케 하는게 아님 
			NUMBOX temp(*this);/후위 증가 연선 nb++ 
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
		A() {};//default 생성자
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
	
	a2=a1;//따로 operator=안해도 실행 but 얕은 복사(동일객체) 
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
			cout << "이름: " << name << endl;
			cout << "나이: " << age << endl;
		}
		~Student()
		{
			delete []name;
			cout << "~Student 소멸자 호출!" << endl;
		}
};

int main()
{
	Student st1("김철수", 14);
	Student st2("홍길동", 15);
	
	st2 = st1;//문제 발생. 얕은 복사로 이루어 지기에 st2는 st1의 주소르 가리킴 
	
	st1.ShowInfo();
	st2.ShowInfo();
	
	return 0;//즉 이 과정에서 소멸자가 호출될 때 st1의 주소는 중복으로 delete[]되고, st2는 delete불가. 
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
			cout << "이름: " << name << endl;
			cout << "나이: " << age << endl;
		}
		Student& operator=(Student& ref)
		{
			delete []name;
			name = new char[10];
			strcpy(name, ref.name);
			age = ref.age;
			return *this;//객체 자체를 리턴 
		}
		~Student()
		{
			delete []name;
			cout << "~Student 소멸자 호출!" << endl;
		}
};

int main()
{
	Student st1("김철수", 14);
	Student st2("홍길동", 15);

	st2 = st1;
	
	st1.ShowInfo();
	st2.ShowInfo();
	
	return 0;
}


