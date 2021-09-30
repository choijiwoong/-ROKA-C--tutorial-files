#include <iostream>
#include <utility>//move

#include <cstring>
/*MyString class with std::move
class MyString{
	char *string_content;
	int string_length;
	int memory_capacity;
	
	public:
		MyString();//constructor
		MyString(const char *str);//constructor
		MyString(const MyString &str);//copy constructor
		MyString(MyString &&str);//move constructor
		
		//for assign in swap function
		MyString &operator=(const MyString &s);//common assign operator
		MyString& operator=(MyString&& s);//move assign operator
		
		~MyString();//destructor
		
		int length() const;
		void println();
};

MyString::MyString(){
	std::cout<<"constructor is called!"<<std::endl;
	string_length=0;
	memory_capacity=0;
	string_content=NULL;
}
MyString::MyString(const char *str){
	std::cout<<"constructor is called!"<<std::endl;
	string_length=strlen(str);
	memory_capacity=string_length;
	string_content=new char[string_length];
	
	for(int i=0; i!=string_length; i++)
		string_content[i]=str[i];
}
MyString::MyString(const MyString &str){
	std::cout<<"copy constructor is called!"<<std::endl;
	string_length=str.string_length;
	string_content=new char[string_length];
	
	for(int i=0; i!=string_length; i++)
		string_content[i]=str.string_content[i];
}
MyString::MyString(MyString &&str){
	std::cout<<"move constructor is called!"<<std::endl;
	string_length=str.string_length;
	string_content=str.string_content;
	memory_capacity=str.memory_capacity;
	
	str.string_content=nullptr;//for no destruct
	str.string_length=0;
	str.memory_capacity=0;
}
MyString::~MyString(){
	if(string_content)
		delete[] string_content;
}
MyString &MyString::operator=(const MyString &s){//common assign operator
	std::cout<<"copy!"<<std::endl;
	if(s.string_length>memory_capacity){
		delete[] string_content;
		string_content=new char[s.string_length];
		memory_capacity=s.string_length;
	}
	string_length=s.string_length;
	for(int i=0; i!=string_length; i++)
		string_content[i]=s.string_content[i];
	
	return *this;
}
MyString& MyString::operator=(MyString&& s){
	std::cout<<"move!"<<std::endl;
	string_content=s.string_content;
	memory_capacity=s.memory_capacity;
	string_length=s.string_length;
	
	s.string_content=nullptr;
	s.memory_capacity=0;
	s.string_length=0;
	return *this;
}
int MyString::length() const{ return string_length; }
void MyString::println(){
	for(int i=0; i!=string_length; i++)
		std::cout<<string_content[i];
	std::cout<<std::endl;
}

template <typename T>
void my_swap(T &a, T &b){
	T tmp(std::move(a));//std::move is used!
	a=std::move(b);//std::move is not move! move is working in overloading function that gets rvalue
	b=std::move(tmp);
}

int main(){
  MyString str1("abc");
  MyString str2("def");
  std::cout << "Swap 전 -----" << std::endl;
  std::cout << "str1 : ";
  str1.println();
  std::cout << "str2 : ";
  str2.println();

  std::cout << "Swap 후 -----" << std::endl;
  my_swap(str1, str2);
  std::cout << "str1 : ";
  str1.println();
  std::cout << "str2 : ";
  str2.println();
}*/

/*how can we enter A(that is existing) to B's member by move constructor?
class A{
	public:
		A(){std::cout<<"ctor\n";}
		A(const A& a){std::cout<<"copy ctor\n";}
		A(A&& a){std::cout<<"move ctor\n";}
};

class B{
	public:
		B(A&& a): a_(std::move(a)){}
		A a_;
};

int main(){
	A a;
	std::cout<<"create B-- \n";
	B b(std::move(a));
}*/

//Universal reference and perfect move
template <typename T>
void wrapper(T&& u){//universal reference not rvalue reference because it's template type
	g(std::forward<T>(u));//if lvalue, apply std::move specially.
} 

class A{};

void g(A& a){ std::cout<<"lvalue reference is called"<<std::endl;}
void g(const A& a){ std::cout<<"lvalue const reference is called"<<std::endl; }
void g(A&& a){ std::cout<<"rvalue reference is called"<<std::endl; }

int main(){
	A a;
	const A ca;
	
	std::cout<<"original --------"<<std::endl;
	g(a);
	g(ca);
	g(A());
	
	std::cout<<"Wrapper ----"<<std::endl;
	wrapper(a);
	wrapper(ca);
	wrapper(A());
} 

/*
1.	swap함수와 같이 잠시 포인터를 이동할 때, 복사생성이 아닌 이동생성으로 temp에 옮겨놓으면 되는데, 이때 좌측값을 이동생성할 수 있게 바꿔주는 move함수를 사용한다. 
	std::move함수는 인자로 받는 객체를 우측값으로 변환하여 리턴한다. 즉 타입변환만 수행하기에 실제로 rvalue같은 이름의 개념이다.
	 이때, std::move로 변환된 값을 받는 assign oeprator overloading이 따로 필요하다 즉, 일반 operator=는 반환타입이 &이고, rvalue는  &operator=이다.
2.	함수의 인자로 rvalue reference&&를 사용하더라도 실제로 저장된 것은 좌측값이기에 대입연산과같이 작업을 할때 std::move처럼 우측값으로 변환시켜주어야 한다.
3.	wrapper클래스의 인자를 함수에 넣어 호출할 때, 타입이 기존의 데이터와 다르게 캐스팅되는 문제가 있어서 인자별로(const)따로 함수를 만들어주어야 했는데,
	이는 인자의 개수가 늘어날 때마다 제곱꼴로 늘어나기에 비효율적이다. 고로 보편적 레퍼런스(Universal reference)라는 개념이 C++11에서 나타났다.
4.	기존의 우측값 레퍼런스는 우측값만을 인자로 받을 수 있었지만, 템플릿 타입의 우측값 레퍼런스는 보편적 레퍼런스라고 불리우는데,
	이는 우측값과 좌측값 둘 다 받을 수 있다. 이때 레퍼런스 겹침 규칙(reference collapsing rule)에 따라 T의 타입이 추론된다.
	 그런데 값을 받은 후 함수에 다시 인자로 넣을때, 우측값이면 그냥 넣으면 되지만, 좌측값이면 std::move를 통해 다시 우측값임을 명시해야 하는데, 
	이러한 작업 즉, 우측값이면 그냥 넣고, 좌측값이면 std::move로 넣게 해주는것이 std::forward함수이다.
	 
*/
