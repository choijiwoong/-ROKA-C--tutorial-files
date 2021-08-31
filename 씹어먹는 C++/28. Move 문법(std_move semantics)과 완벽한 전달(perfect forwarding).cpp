#include <iostream>
#include <cstring>
#include <utility>//for use move function that makes lvalue to rvalue

//�׷��ٸ� �ƿ� �������� ���۷����� ���� �� �ֵ��� const A& �� A& ���� ������ִ� ����� �ֽ��ϴ�. �Ʒ��� ���� ��������.

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
	
	//third try(��...���� �����ϴ�....����� �������� �簳�߶����� �� �ö��µ�.....��..... ���� �Ǹ� ���ڴµ� �����Ÿ��� ª�ܸ����� �踻�̴� ������ ������ ���ӱ׶� ������ �ƺ� ������~~~~)
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
[0.	���⿡ �ռ�]
1.	�������� �̵��ϰ� �ʹٸ� ��� �ؾ��ϳ�? swap�Լ��� �����غ���.
	template<typename T>
	void my_swap(T &a, T &b){
		T tmp(a);
		a=b;
		b=tmp;
	}���� ���縦 3���̳� �ϰ� �ȴ�. �� T�� ���� MyString�̶��? 
	 ���� 3���� �ƴ϶� �׳� string_content�ּҸ� �ٲ��ָ� �ȴٴ� ����(move constructor) �츰 �˰��ִ�.
	�ٸ� ���� my_swap���� �����ϴµ��� �������ִµ�, my_swap�� MyString������ �۵��ǰԲ� �ѰŶ� �Ϲ����� T������ �۵����� �ʴ´�.
	���� �̴� 
	template<>
	void my_swap(MyString &a, MyString &b)�� ���ø� Ư��ȭ�� �̿��ϸ� �ȴ�. ������ �Ǵٸ� ������ string_content�� private�̱⿡
	MyString���ο� swap�Լ��� ���� ������ �����ϰ� �ؾ��ϴµ�, �̷��� my_swap�Լ��� ������ �ʿ伺�� �������. 
	 ������ my_swap�� ����ϸ� ����� ó���� �ȵɱ�? �츮�� T tmp(a)���� ���� ������ ���� �̵������ڷ� �ϱ� �ٶ���. �ű�⸸ �ϸ� �Ǳ� �����̴�.
	������, a�� �������̴�(��ü�� �ִ�.) ��� �� ���·δ� �̵������ڰ� �����ε����� �ʴ´�.
	
[1.	move�Լ�(move semantics)]_�������� ����������
1.	C++11���� <utility>���� �������� ���������� �ٲ��ִ� move�Լ��� �����Ѵ�. 
2.	MyString class�� �����غ���. 

[2.	����] 

[3.	�Ϻ��� ����(perfect forwarding)]
1.	������ ���۷����� �����ϸ� �ذ��� �� �ִ� �Ǵٸ� ������ wrapper�Լ������� �����Ѵ�.
2.	�׳� g(u)�� ȣ������ �ʰ� ������ ���޹���� ���� ����ؾ��Ѵ�. ���� vector�� emplace_back�� ��ü�� �����ڿ� �����ϰ� ���� ���ڵ��� �Լ��� �����ϸ� �˾Ƽ� �����ؼ� vector�� �ڿ� �߰����ִ� �Լ��̴�.
	��, A�� ���ҷ� ������ ������ �ڿ� ���Ҹ� �߰��Ҷ� vec.push_back(A(1,2,3))ó�� ��ü�� �����Ͽ� �����ϴ� �ݸ�(���ʿ��� �̵� or ���� �߻�),
	emplace_back�Լ��� ����ϸ� vec.emplace_back(1,2,3)�� ����Ͽ� ���ο��� A������ ȣ�� �� ���Ϳ��ҷ� �߰��� �� �ִ�.
	 (�ٵ� ��� push_back�� �����Ϸ��� �˾Ƽ� ����ȭ�ؼ� emplaced_back�� ������ ������� ������. ��� emplace_back�� ����ġ ���� �����ڰ� ȣ��� �� �־ push_back�� ����Ǳ� �� �̻� ����ī�޶�..?)
3.	�׷��ٸ� �̷��� �ǵ����� ���� �����ڰ� ȣ��� ���� �ִٴ� ���� ����Ͽ� ��� �ϸ� wrapper�Լ��� �� ������ ��������? 
	

*/
