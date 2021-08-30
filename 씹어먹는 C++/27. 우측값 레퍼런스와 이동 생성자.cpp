#include <iostream>

/*1
class A{
	int data_;
	
	public:
		A(int data):data_(data){ std::cout<<"common constructor called!"<<std::endl;}
		A(const A& a):data_(a.data_){ std::cout<<"copy constructor called!"<<std::endl;}
};

int main(){
	A a(1);//normal constructor call
	A b(a);//copy constructor call
	
	A c(A(2));//how about this? print common!
	//In standard, A(2) makes temporary object and call copy constructor in c()
	//compiler say just make c with A(2)! not two process do one process! so skip copy and just makes c to A(2).
	//It's called 'copy elision'
	
	
	return 0;
}*/

/*1
#include <cstring>

class MyString{
	char *string_content;
	int string_length;
	int memory_capacity;
	
	public:
		MyString();
		MyString(const char *str);
		MyString(const MyString &str);
		
		void reserve(int size);
		MyString operator+(const MyString &s);
		~MyString();
		
		int length() const;
		void print();
		void println();
};
MyString::MyString(){
	std::cout<<"call constructor!"<<std::endl;
	string_length=0;
	memory_capacity=0;
	string_content=nullptr;//nullptr is added as keyword at C++11. NULL in C can't show value 0 or pointer address 0. so make nullptr that can show pointer address 0.
}
MyString::MyString(const char *str){
	std::cout<<"call constructor!"<<std::endl;
	string_length=strlen(str);
	memory_capacity=string_length;
	string_content=new char[string_length];
	for(int i=0; i!=string_length; i++)
		string_content[i]=str[i];
}
MyString::MyString(const MyString &str){
	std::cout<<"call copy constructor!"<<std::endl;
	string_length=str.string_length;
	memory_capacity=str.string_length;
	string_content=new char[string_length];
	for(int i=0; i!=string_length; i++)
		string_content[i]=str.string_content[i];
}
MyString::~MyString(){ delete[] string_content;}
void MyString::reserve(int size){
	if(size>memory_capacity){
		char *prev_string_content=string_content;
		
		string_content=new char[size];
		memory_capacity=size;
		
		for(int i=0; i!=string_length; i++)
			string_content[i]=prev_string_content[i];
		if(prev_string_content!=nullptr) delete[] 
			prev_string_content;
	}
}
MyString MyString::operator+(const MyString &s){
	MyString str;
	str.reserve(string_length+s.string_length);
	for(int i=0; i<string_length; i++)
		str.string_content[i]=string_content[i];
	for(int i=0; i<s.string_length; i++)
		str.string_content[string_length+i]=s.string_content[i];
	str.string_length=string_length+s.string_length;
	return str;
}
int MyString::length() const{return string_length;}
void MyString::print(){
	for(int i=0; i!=string_length; i++)
		std::cout<<string_content[i];
}
void MyString::println(){
	for(int i=0; i!=string_length; i++)
		std::cout<<string_content[i];
	std::cout<<std::endl;
}

int main(){
	MyString str1("abc");
	MyString str2("def");
	std::cout<<"-----------------"<<std::endl;
	MyString str3=str1+str2;//print structor! and copy structor! but it's not needed. so we have to copy slision if str1 and str2's size is too big. it's unefficient.
	str3.println();
	
	return 0;
}*/

//2
int& func1(int& a){return a;}
int func(int b){return b;}
int main(){
	int a=3;
	func1(a)=4;//possible
	std::cout<<&func1(a)<<std::endl;
	
	int b=2;
	a=func(b);//end of sentence, no substance. it's be right value. right value can placed right but
	std::cout<<&func(b)<<std::endl;//can't check address of right value
	
	return 0;
} 



/*
[1.	복사 생략(Copy Elision)]
1.	컴파일러 자체에서 복사를 생략해버리는 작업을 복사 생략(copy elision)이라고 한다.
2.	함수 내부에서 생성된 객체를 그대로 리턴할 때에도 수행할 수 있다.(C++표준에 반드시 한다도 아니고 할수도있다고 나옴, ㅊ++17부터 특정경우는 무조건으로 정함)
3.	이전에 만든 MyString 클래스를 다시 살펴보자. 

[2.	좌측값(lvalue)과 우측값(rvalue)]
1.	int a=3; a처럼 주소값을 취할 수 있는 값을 좌측값(lvalue), 좌측값은 왼쪽이든 오른쪽이든 올 수 있다.
	반면 3은 주소값을 취할 수 없는 실체가 없는 값이다. 이것을 우측값(rvalue)라고 한다. 우측값은 오른쪽에만 존재해야 한다. 
2.	int a; int& l_a=a; int&r_b=3; a는 좌측값이다. 그렇기에 레퍼런스인 l_a를 만들 수 있지만, 3은 우측값이기에 레퍼런스인 r_b를 만들 수 없다.
	이처럼 & 하나를 이용하여 정의하는 레퍼런스를 좌측값 레퍼런스(lvalue reference)라고 한다. 
3.	앞선 예제의 MyString str3=str1+str2에서 operator+의 정의를 찾아보면 MyString으로 우측값을 리턴하고있는데(실체가 사라질) 어찌 이것이 좌측값을 인자로 받는 MyString(const MyString &str)을 호출할 수 있을까?
	&가 좌측값 레퍼런스를 의미하지만, 예외적으로 const T&타입에 한해서만 우측값도 레퍼런스로 받을 수 있다. 그 이유는 const는 임시객체의 값을 참조만 할 뿐, 변경할 수 없기 때문이다.

[3.	그렇다면 이동은 어떻게?]
1.	임시로 생성된 객체의 string_content가 가리키는 문자열의 주소를 str3의 string_content로 해주고, 임시객체시에 string_content가 해제되지 않도록
	임시객체의 string_content를 nullptr로 바꾼뒤, 소멸자에서 string_content가 nullptr이면 해제하지 않도록 세팅해주면 된다.
	 하지만, 기존의 복사 생성자에선 사용할 수 없는게, 인자를 const MyString&으로 받기에 수정이 불가하기 때문이다.
	아 px안갔다왔네...야간근무 배고파서 어케서누
	이와 같은 문제(PX?)는 COSNT mYsTRING&이 좌측값과 우측값 모두 받을 수 있다는 점에서 비롯되어 좌측값말고 우측값만 특이적으로 받을 수 있는 우측값 레퍼런스(c++11)를 이용하면 된다. 

[4.	우측값 레퍼런스]
1.	 
 
*/
