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
  std::cout << "Swap �� -----" << std::endl;
  std::cout << "str1 : ";
  str1.println();
  std::cout << "str2 : ";
  str2.println();

  std::cout << "Swap �� -----" << std::endl;
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
1.	swap�Լ��� ���� ��� �����͸� �̵��� ��, ��������� �ƴ� �̵��������� temp�� �Űܳ����� �Ǵµ�, �̶� �������� �̵������� �� �ְ� �ٲ��ִ� move�Լ��� ����Ѵ�. 
	std::move�Լ��� ���ڷ� �޴� ��ü�� ���������� ��ȯ�Ͽ� �����Ѵ�. �� Ÿ�Ժ�ȯ�� �����ϱ⿡ ������ rvalue���� �̸��� �����̴�.
	 �̶�, std::move�� ��ȯ�� ���� �޴� assign oeprator overloading�� ���� �ʿ��ϴ� ��, �Ϲ� operator=�� ��ȯŸ���� &�̰�, rvalue��  &operator=�̴�.
2.	�Լ��� ���ڷ� rvalue reference&&�� ����ϴ��� ������ ����� ���� �������̱⿡ ���Կ�������� �۾��� �Ҷ� std::moveó�� ���������� ��ȯ�����־�� �Ѵ�.
3.	wrapperŬ������ ���ڸ� �Լ��� �־� ȣ���� ��, Ÿ���� ������ �����Ϳ� �ٸ��� ĳ���õǴ� ������ �־ ���ں���(const)���� �Լ��� ������־�� �ߴµ�,
	�̴� ������ ������ �þ ������ �����÷� �þ�⿡ ��ȿ�����̴�. ��� ������ ���۷���(Universal reference)��� ������ C++11���� ��Ÿ����.
4.	������ ������ ���۷����� ���������� ���ڷ� ���� �� �־�����, ���ø� Ÿ���� ������ ���۷����� ������ ���۷������ �Ҹ���µ�,
	�̴� �������� ������ �� �� ���� �� �ִ�. �̶� ���۷��� ��ħ ��Ģ(reference collapsing rule)�� ���� T�� Ÿ���� �߷еȴ�.
	 �׷��� ���� ���� �� �Լ��� �ٽ� ���ڷ� ������, �������̸� �׳� ������ ������, �������̸� std::move�� ���� �ٽ� ���������� ����ؾ� �ϴµ�, 
	�̷��� �۾� ��, �������̸� �׳� �ְ�, �������̸� std::move�� �ְ� ���ִ°��� std::forward�Լ��̴�.
	 
*/
