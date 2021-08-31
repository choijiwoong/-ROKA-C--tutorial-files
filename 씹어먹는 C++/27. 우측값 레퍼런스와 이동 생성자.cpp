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

//1 4
#include <cstring>
#include <vector>

class MyString{
	char *string_content;
	int string_length;
	int memory_capacity;
	
	public:
		MyString();
		MyString(const char *str);
		MyString(const MyString &str);
		MyString(MyString &&str) noexcept;//move constructor. make compiler use move constructor by telling it's safe for using.
		
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
//get rvalue as argument.
MyString::MyString(MyString &&str) noexcept{//for define reference of rvalue, we have to use two &. so it get rvalue as argument that's MyString type.
	std::cout<<"call move constructor!"<<std::endl;//str is rvalue.
	string_length=str.string_length;
	string_content=str.string_content;//just copy address unlike normal copy constructor.
	memory_capacity=str.memory_capacity;
	
	str.string_content=nullptr;//no delete[] when deleting of tempoary object.
	//because we set string_content to str.string_content. so when str's destructor called, make it exist by setting str.string_content to nullptr. no delete real address, delete fake address.
}
MyString::~MyString(){ 
	if(string_content)//if string_content is nullptr, no delete.
		delete[] string_content;
}
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
	//4 for show using of move constructor efficiently. 
	MyString str1("abc");
	MyString str2("def");
	std::cout<<"-----------------"<<std::endl;//My conpiler doesn't print "call copy constructor!", it just do copy elision smartly. 
	MyString str3=str1+str2;//print constructor! and copy constructor! but it's not needed. so we have to copy slision if str1 and str2's size is too big. it's unefficient.
	str3.println();//and now, constructor called and move constructor called.
	
	//5
	MyString s("abc");
	std::vector<MyString> vec;
	vec.resize(0);
	
	std::cout<<"add first element ---"<<std::endl;
	vec.push_back(s);
	std::cout<<"add second element ---"<<std::endl;
	vec.push_back(s);
	std::cout<<"add third element ---"<<std::endl;
	vec.push_back(s);
	//it doesn't use move constructor!! it uses copy constructor wtf!
	//Let's add noexcept keyword at move constructor. it use move constructor successfully!
	
	return 0;
}

/*2
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
} */



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
1.	일반적으로 오측값 레퍼런스는 아래와 같은 방식으로 사용이 가능하다.
	int a;
	int& l_a=a;
	int& ll_a=3;//impossible  뭐야 감히 레퍼런스에 우측값을 넣어? 
	
	int&& r_b=3;우측값을 레퍼런스 할거에요 && 
	int&& rr_b=a;//impossible. 뭐야 이건 좌측값이잖아 
	
	***
	const int& a=3;읽기만 가능하기에 우측값을 레퍼런스로
	int&& b=3;우측값을 b에 우측값레퍼런스로 받는데 읽기도 가능 변경도 가능. 즉 레퍼런스인데 받는것이 우측값이 가능하게끔.
	
	***
	MyString&& str3=str1+str2;str3이 소멸되지 않은 임시객체를 가리킴by move constructor 
	MyString str3=str1+str2;str3이 임시객체를 복사생성함by copy constructor 
	이동생성자가 불필요한 생성자를 최소화함. 
	 
2.	우측값 레퍼런스의 재미있는 특징은 레퍼런스 하는 임시 객체가 소멸되지 않도록 붙들고 있다는 점이다.
	MyString&& str3=str1+str2;
	str3.println();
	에서 str3이 str1+str2가 리턴하는 임시 객체의 레퍼런스가 되면서 그 임시 객체가 소멸되지 않도록 한다. 

[5.	이동 생성자 작성 시 주의할 점]
1.	MyString을 C++컨테이너들, vector같은 것에 넣는데에 이동생성자를 반드시 noexcept로 명시해야 한다.
	Vector는 새 원소를 추가할 때, 메모리가 부족하면 트기가 커진 새 공간 할당 후, 새 메모리로 옮기게 된다. 
	만약 복사생성하는 과정에서 예외가 발생한다면, 새로운 메모리를 소멸시킨 후 예외를 전하면 그 전에 메모리도 남아있고, 새로운메모리도 해젝가되니 효율적이다.
	 다만 문제는 이동생성자를 이용하여 이동생성하는 과정에서 예외가 발생하는 경우이다. 이동생성의 경우 새 메모리를 해제하면 이미 데이터가 이동된 상태인지라 오류가 발생한 메모리를
	섯불리 해제할 수 없다. 고로 vector의 경우 이동생성자에서 예외가 발생했을 때, 이를 제대로 처리할 수 없고 이는 다른 컨테이너들도 동일하다.
	 그렇기에 vector는 이동생성자가 noexcept(예외절대없음)이 아닌 이상 이동생성자를 사용하지 않는다.  
*/
