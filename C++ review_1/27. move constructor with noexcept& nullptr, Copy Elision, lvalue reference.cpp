#include <iostream>

//compiler doesn't use move constructor without noexcept EXAMPLE MyString class
#include <cstring>
#include <vector>

class MyString{
	char *string_content;
	int string_length;
	int memory_capacity;
	
	public:
		MyString(){//constructor
			std::cout<<"call constructor"<<std::endl;
			string_length=0;
			memory_capacity=0;
			string_content=nullptr;//C++11
		}
		MyString(const char *str){//constructor
			std::cout<<"call cosntructor"<<std::endl;
			string_length=strlen(str);
			memory_capacity=string_length;
			string_content=new char[string_length];
			for(int i=0; i!=string_length; i++)
				string_content[i]=str[i];	
		}
		MyString(const MyString &str){//copy constructor
			std::cout<<"call copy constructor"<<std::endl;
			string_length=str.string_length;
			memory_capacity=str.string_length;
			string_content=new char[string_length];
			for(int i=0; i!=string_length; i++)
				string_content[i]=str.string_content[i];
		}
		MyString(MyString &&str) noexcept{//move constructor
			std::cout<<"call move constructor"<<std::endl;
			string_length=str.string_length;
			string_content=str.string_content;
			memory_capacity=str.memory_capacity;
			
			str.string_content=nullptr;//no free memory!
		}
		~MyString(){//destructor
			if(string_content)//no delete if string_content is nullptr
				delete[] string_content;
		}
};

int main(){
	MyString s("abc");
	std::vector<MyString> vec;
	vec.resize(0);
	
	std::cout<<"first element"<<std::endl;
	vec.push_back(s);
	std::cout<<"second element"<<std::endl;
	vec.push_back(s);
	std::cout<<"third element"<<std::endl;
	vec.push_back(s);
}


/*
1.	Copy Elision_������� A c(A(2))�� ������ �ӽû����� ��ü�� ����ǹǷ� ���縦 �����ϰ� �����ڸ� ȣ���Ѵ�. 
2.	rvalue, lvalue, lvalue reference
3.	�̵� ������  by && like str.string_content=nullptr; 
4.	C++ �����̳ʵ�, �� vector�� �̵������ڰ� �̿�� ��ü�� �ִ´ٸ�, �̵� �����ڸ� noexcept�� ����ؾ� �Ѵ�. �� ������ vector�� allocate�߿� ������ �߻��ϸ�
	�����ϴ��� �Ҹ��Ű�� �ٽ� ������ ��ü�� ����Ű�� ������, �̵������� ��� �̹� �κ������� �̵��Ǿ��� ������ ������ �߻��Ѵ�. 
5.	nullptr
*/ 
