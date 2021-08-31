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
[1.	���� ����(Copy Elision)]
1.	�����Ϸ� ��ü���� ���縦 �����ع����� �۾��� ���� ����(copy elision)�̶�� �Ѵ�.
2.	�Լ� ���ο��� ������ ��ü�� �״�� ������ ������ ������ �� �ִ�.(C++ǥ�ؿ� �ݵ�� �Ѵٵ� �ƴϰ� �Ҽ����ִٰ� ����, ��++17���� Ư������ ���������� ����)
3.	������ ���� MyString Ŭ������ �ٽ� ���캸��. 

[2.	������(lvalue)�� ������(rvalue)]
1.	int a=3; aó�� �ּҰ��� ���� �� �ִ� ���� ������(lvalue), �������� �����̵� �������̵� �� �� �ִ�.
	�ݸ� 3�� �ּҰ��� ���� �� ���� ��ü�� ���� ���̴�. �̰��� ������(rvalue)��� �Ѵ�. �������� �����ʿ��� �����ؾ� �Ѵ�. 
2.	int a; int& l_a=a; int&r_b=3; a�� �������̴�. �׷��⿡ ���۷����� l_a�� ���� �� ������, 3�� �������̱⿡ ���۷����� r_b�� ���� �� ����.
	��ó�� & �ϳ��� �̿��Ͽ� �����ϴ� ���۷����� ������ ���۷���(lvalue reference)��� �Ѵ�. 
3.	�ռ� ������ MyString str3=str1+str2���� operator+�� ���Ǹ� ã�ƺ��� MyString���� �������� �����ϰ��ִµ�(��ü�� �����) ���� �̰��� �������� ���ڷ� �޴� MyString(const MyString &str)�� ȣ���� �� ������?
	&�� ������ ���۷����� �ǹ�������, ���������� const T&Ÿ�Կ� ���ؼ��� �������� ���۷����� ���� �� �ִ�. �� ������ const�� �ӽð�ü�� ���� ������ �� ��, ������ �� ���� �����̴�.

[3.	�׷��ٸ� �̵��� ���?]
1.	�ӽ÷� ������ ��ü�� string_content�� ����Ű�� ���ڿ��� �ּҸ� str3�� string_content�� ���ְ�, �ӽð�ü�ÿ� string_content�� �������� �ʵ���
	�ӽð�ü�� string_content�� nullptr�� �ٲ۵�, �Ҹ��ڿ��� string_content�� nullptr�̸� �������� �ʵ��� �������ָ� �ȴ�.
	 ������, ������ ���� �����ڿ��� ����� �� ���°�, ���ڸ� const MyString&���� �ޱ⿡ ������ �Ұ��ϱ� �����̴�.
	�� px�Ȱ��ٿԳ�...�߰��ٹ� ����ļ� ���ɼ���
	�̿� ���� ����(PX?)�� COSNT mYsTRING&�� �������� ������ ��� ���� �� �ִٴ� ������ ��ԵǾ� ���������� �������� Ư�������� ���� �� �ִ� ������ ���۷���(c++11)�� �̿��ϸ� �ȴ�. 

[4.	������ ���۷���]
1.	�Ϲ������� ������ ���۷����� �Ʒ��� ���� ������� ����� �����ϴ�.
	int a;
	int& l_a=a;
	int& ll_a=3;//impossible  ���� ���� ���۷����� �������� �־�? 
	
	int&& r_b=3;�������� ���۷��� �Ұſ��� && 
	int&& rr_b=a;//impossible. ���� �̰� ���������ݾ� 
	
	***
	const int& a=3;�б⸸ �����ϱ⿡ �������� ���۷�����
	int&& b=3;�������� b�� ���������۷����� �޴µ� �б⵵ ���� ���浵 ����. �� ���۷����ε� �޴°��� �������� �����ϰԲ�.
	
	***
	MyString&& str3=str1+str2;str3�� �Ҹ���� ���� �ӽð�ü�� ����Ŵby move constructor 
	MyString str3=str1+str2;str3�� �ӽð�ü�� ���������by copy constructor 
	�̵������ڰ� ���ʿ��� �����ڸ� �ּ�ȭ��. 
	 
2.	������ ���۷����� ����ִ� Ư¡�� ���۷��� �ϴ� �ӽ� ��ü�� �Ҹ���� �ʵ��� �ٵ�� �ִٴ� ���̴�.
	MyString&& str3=str1+str2;
	str3.println();
	���� str3�� str1+str2�� �����ϴ� �ӽ� ��ü�� ���۷����� �Ǹ鼭 �� �ӽ� ��ü�� �Ҹ���� �ʵ��� �Ѵ�. 

[5.	�̵� ������ �ۼ� �� ������ ��]
1.	MyString�� C++�����̳ʵ�, vector���� �Ϳ� �ִµ��� �̵������ڸ� �ݵ�� noexcept�� ����ؾ� �Ѵ�.
	Vector�� �� ���Ҹ� �߰��� ��, �޸𸮰� �����ϸ� Ʈ�Ⱑ Ŀ�� �� ���� �Ҵ� ��, �� �޸𸮷� �ű�� �ȴ�. 
	���� ��������ϴ� �������� ���ܰ� �߻��Ѵٸ�, ���ο� �޸𸮸� �Ҹ��Ų �� ���ܸ� ���ϸ� �� ���� �޸𸮵� �����ְ�, ���ο�޸𸮵� �������Ǵ� ȿ�����̴�.
	 �ٸ� ������ �̵������ڸ� �̿��Ͽ� �̵������ϴ� �������� ���ܰ� �߻��ϴ� ����̴�. �̵������� ��� �� �޸𸮸� �����ϸ� �̹� �����Ͱ� �̵��� ���������� ������ �߻��� �޸𸮸�
	���Ҹ� ������ �� ����. ��� vector�� ��� �̵������ڿ��� ���ܰ� �߻����� ��, �̸� ����� ó���� �� ���� �̴� �ٸ� �����̳ʵ鵵 �����ϴ�.
	 �׷��⿡ vector�� �̵������ڰ� noexcept(�����������)�� �ƴ� �̻� �̵������ڸ� ������� �ʴ´�.  
*/
