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
1.	Copy Elision_복사생략 A c(A(2))는 어차피 임시생성된 객체가 복사되므로 복사를 생략하고 생성자를 호출한다. 
2.	rvalue, lvalue, lvalue reference
3.	이동 생성자  by && like str.string_content=nullptr; 
4.	C++ 컨테이너들, 즉 vector에 이동생성자가 이용된 객체를 넣는다면, 이동 생성자를 noexcept로 명시해야 한다. 그 이유는 vector가 allocate중에 오류가 발생하면
	복사하던걸 소멸시키고 다시 기존의 객체를 가리키면 되지만, 이동생성의 경우 이미 부분적으로 이동되었기 때문에 오류가 발생한다. 
5.	nullptr
*/ 
