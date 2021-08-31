#include <iostream>
#include <cstring>
#include <utility>//for use move function that makes lvalue to rvalue

//그렇다면 아예 우측값을 레퍼런스로 받을 수 있도록 const A& 와 A& 따로 만들어주는 방법이 있습니다. 아래와 같이 말이지요.

/* 0 1
class MyString {
  char *string_content;
  int string_length;

  int memory_capacity;

 public:
  MyString();
  MyString(const char *str);
  MyString(const MyString &str);
  MyString(MyString &&str);

  MyString &operator=(const MyString &s);//normal =operator
  MyString& operator=(MyString&& s);//move =operator
  ~MyString();

  int length() const;

  void println();
};

MyString::MyString() {
  std::cout << "call constructor!"<< std::endl;
  string_length = 0;
  memory_capacity = 0;
  string_content = NULL;
}

MyString::MyString(const char *str) {
  std::cout << "call constructor!" << std::endl;
  string_length = strlen(str);
  memory_capacity = string_length;
  string_content = new char[string_length];

  for (int i = 0; i != string_length; i++) string_content[i] = str[i];
}
MyString::MyString(const MyString &str) {
  std::cout <<"call copy constructor!" << std::endl;
  string_length = str.string_length;
  string_content = new char[string_length];

  for (int i = 0; i != string_length; i++)
    string_content[i] = str.string_content[i];
}
MyString::MyString(MyString &&str) {
  std::cout << "call move constructor!" << std::endl;
  string_length = str.string_length;
  string_content = str.string_content;
  memory_capacity = str.memory_capacity;

  str.string_content = nullptr;
  str.string_length=0;
  str.memory_capacity=0;
}
MyString::~MyString() {
  if (string_content) delete[] string_content;
}

MyString &MyString::operator=(const MyString &s) {
  std::cout << "copy!" << std::endl;
  if (s.string_length > memory_capacity) {
    delete[] string_content;
    string_content = new char[s.string_length];
    memory_capacity = s.string_length;
  }
  string_length = s.string_length;
  for (int i = 0; i != string_length; i++) {
    string_content[i] = s.string_content[i];
  }

  return *this;
}
MyString& MyString::operator=(MyString&& s){//get rvalue. if we don't define it, compiler work copy operator.
	std::cout<<"move!"<<std::endl;
	string_content=s.string_content;
	memory_capacity=s.memory_capacity;
	string_length=s.string_length;
	
	s.string_content=nullptr;
	s.memory_capacity=0;
	s.string_length=0;
	
	return *this;
}
int MyString::length() const { return string_length; }
void MyString::println() {
  for (int i = 0; i != string_length; i++) std::cout << string_content[i];

  std::cout << std::endl;
}
template <typename T>
void my_swap(T &a, T &b) {
  T tmp(std::move(a));//make tmp(temporary object) to a. it's fast because of move constructor.
  a=std::move(b);//not substitute operation just move operation because we made overloading for move operator=.
  b=std::move(tmp);//not move process worked in this line, it's work in move substitute operator or move constructor. don't be confuse to the mean of std::move.
}//make lvalue to rvalue.

int main() {
  MyString str1("abc");
  MyString str2("def");
  std::cout << "before Swap -----" << std::endl;
  str1.println();
  str2.println();

  std::cout << "after Swap -----" << std::endl;
  my_swap(str1, str2);
  str1.println();
  str2.println();
}*/

/*1
class A{
	public:
		A(){std::cout<<"normal constructor is called"<<std::endl;}
		A(const A& a){std::cout<<"copy constructor is called"<<std::endl;}
		A(A&& a){std::cout<<"move constructor is called"<<std::endl;}
};
int main(){
	A a;//"normal constructor is called"
	std::cout<<"--------"<<std::endl;
	A b(a);//"copy constructor is called"
	//a is lvalue, so it calls copy contructor
	
	std::cout<<"--------"<<std::endl;
	A c(std::move(a));//"move constructor is called"
	//std::move return after changing of object as argument to rvalue. not move just casting to rvalue!
	
	return 0;
}*/

/*2
class A{//normal class
	public:
		A(){std::cout<<"ctor\n";}
		A(const A& a){std::cout<<"copy ctor\n";}
		A(A&& a){std::cout<<"move ctor\n";}
};
class B{//save a class
	public:
		//B(const A& a):a_(a){}//first try
		//B(const A& a):a_(std::move(a)){}//second try
		//B(A&& a):a_(a){}//third try
		B(A&& a):a_(std::move(a)){}//correct answer!
		A a_;
};

int main(){
	//if we want to input A to B making B object?
	A a;
	std::cout<<"create B----\n";
	//B b(?);//first & second try
	B b(std::move(a));//third try
	
	//what can we make B's constructor? make it const A& type first.
	//it calls copy copyconstructor! we don't want it. we want to move A to b's inside!. it's not copy constructor.
	
	//second try
	//how about use std::move for move?
	//call copy constructor not move constructor! The fact (that std::move(a) change a to rvalue) is correct. 
	//but we get a as 'const A&' in B, so std::move(a) get type 'const A&&'. but In A class, it doesn't have A(const A&& ). so compiler get std::move(a) get as const A& a that is copy constructor.
	
	//third try(아...통학 어케하누....자취방 전월세가 재개발때문에 다 올랐는데.....하..... 긱사라도 되면 좋겠는데 직선거리는 짧단마리야 김말이는 떡볶이 국물에 찍어머그란 마리야 아베 마리아~~~~)
	//how about get rvalue in B at all?
	//we input std::move(a) as argument, but it's reset lvalue in B(A&& a). 
	
	//correct answer
	//so we have to rechange like a_(std::move(a));
	
	
	return 0;
}*/

//3
template <typename T>
void wrapper(T u){//error occur 'void wrapper(T& u)'. 
	g(u);
}

class A{};

void g(A& a){std::cout<<"lvalue reference is called"<<std::endl;}
void g(const A& a){std::cout<<"lvalue const reference is called"<<std::endl;}
void g(A&& a){std::cout<<"rvalue reference is called"<<std::endl;}

int main(){
	A a;
	const A ca;
	
	std::cout<<"original version ----------"<<std::endl;
	g(a);//"lvalue reference is called"
	g(ca);//"lvalue const reference is called"
	g(A());//"rvalue reference is called"
	
	std::cout<<"Wrappe version ------------"<<std::endl;
	wrapper(a);//"lvalue reference is called"
	wrapper(ca);//"lvalue reference is called"
	wrapper(A());//"lvalue reference is called"
	//with wrapper, if T is normal type not reference, compiler ignores const. it means compiler guess T as class A. so call g(A& a).
	
	//than, how about work in wrapper that set 'T& u' as argument?
 	//make error that "error: cannot bind non-const lvalue reference of type 'A&' to an rvalue of type 'A'
 	//In g(A()), A() is not const so compiler guess T to class A. than A& can't be rvalue's reference. it makes compile error.
 	
 	//So let's make both of const A& and A&
 	//
	
	return 0;
} 


/*
[0.	들어가기에 앞서]
1.	좌측값을 이동하고 싶다면 어떻게 해야하나? swap함수를 생각해보자.
	template<typename T>
	void my_swap(T &a, T &b){
		T tmp(a);
		a=b;
		b=tmp;
	}무려 복사를 3번이나 하게 된다. 이 T가 만약 MyString이라면? 
	 복사 3번이 아니라 그냥 string_content주소만 바꿔주면 된다는 것을(move constructor) 우린 알고있다.
	다만 위를 my_swap에서 구현하는데에 문제가있는데, my_swap은 MyString에서만 작동되게끔 한거라 일반적인 T에서는 작동하지 않는다.
	물론 이는 
	template<>
	void my_swap(MyString &a, MyString &b)의 템플릿 특수화를 이용하면 된다. 하지만 또다른 문제는 string_content가 private이기에
	MyString내부에 swap함수를 만들어서 접근이 가능하게 해야하는데, 이러면 my_swap함수의 정의의 필요성이 사라진다. 
	 원래의 my_swap을 사용하며 깔끔한 처리는 안될까? 우리는 T tmp(a)에서 복사 생성자 말고 이동생성자로 하길 바란다. 옮기기만 하면 되기 때문이다.
	하지만, a는 좌측값이다(실체가 있다.) 고로 이 상태로는 이동생성자가 오버로딩되지 않는다.
	
[1.	move함수(move semantics)]_좌측값을 우측값으로
1.	C++11부터 <utility>에서 좌측값을 우측값으로 바꿔주는 move함수를 제공한다. 
2.	MyString class에 적용해보자. 

[2.	퀴즈] 

[3.	완벽한 전달(perfect forwarding)]
1.	우측값 레퍼런스를 도입하며 해결할 수 있는 또다른 문제는 wrapper함수에서도 존재한다.
2.	그냥 g(u)를 호출하지 않고 저러한 전달방식을 종종 사용해야한다. 예로 vector는 emplace_back는 객체의 생성자에 전달하고 싶은 인자들을 함수에 전달하면 알아서 생성해서 vector맨 뒤에 추가해주는 함수이다.
	즉, A를 원소로 가지는 벡터의 뒤에 원소르 추가할때 vec.push_back(A(1,2,3))처럼 객체를 생성하여 전달하는 반면(불필요한 이동 or 복사 발생),
	emplace_back함수를 사용하면 vec.emplace_back(1,2,3)를 사용하여 내부에서 A생성자 호출 후 벡터원소로 추가할 수 있다.
	 (근데 사실 push_back도 컴파일러가 알아서 최적화해서 emplaced_back과 동일한 어셈블리를 생성함. 사실 emplace_back은 예상치 못한 생성자가 호출될 수 있어서 push_back이 권장되긴 함 이상 몰래카메라..?)
3.	그렇다면 이러한 의도하지 않은 생성자가 호출될 수도 있다는 점을 고려하여 어떻게 하면 wrapper함수를 잘 정의할 수있을까? 
	

*/
