#include <iostream>
#include <string.h>//strlen

//perfect String Class

class MyString{
	char* string_content;//data
	int string_length;
	int memory_capacity;
	
	public:
		MyString(char c);//one char
		MyString(const char* str);//char[]
		MyString(const MyString& str);//copy
		~MyString();
		
		int length() const;
		int capacity() const;
		void reserve(int size);
		
		//print
		void print() const;
		void println() const;
		
		//assign
		MyString& assign(const MyString& str);
		MyString& assign(const char* str);
		
		//at
		char at(int i) const;
		
		//insert
		MyString& insert(int loc, const MyString& str);
		MyString& insert(int loc, const char* str);
		MyString& insert(int loc, char c);
		
		//erase
		MyString& erase(int loc, int num);
		
		//find
		int find(int find_from, const MyString& str) const;
		int find(int find_from, const char* str) const;
		int find(int find_from, char c) const;
		
		//compare
		int compare(const MyString& str) const;
};
MyString::MyString(char c){
	string_content=new char[1];//allocate
	string_content[0]=c;//save
	string_length=1;//set
	memory_capacity=1;
}
MyString::MyString(const char* str){
	string_length=strlen(str);//get length
	string_content=new char[string_length];//allocate
	for(int i=0; i<string_length; i++)
		string_content[i]=str[i];//save
	memory_capacity=string_length;//set
}
MyString::MyString(const MyString& str){
	string_length=str.string_length;//get length
	string_content=new char[str.memory_capacity];//allocate to memory_capacity
	for(int i=0; i<string_length; i++)
		string_content[i]=str.string_content[i];
	memory_capacity=str.memory_capacity;
}
MyString::~MyString(){
	if(string_content!=nullptr)
		delete[] string_content;
}

int MyString::length() const{ return string_length; }
int MyString::capacity() const{ return memory_capacity; }
void MyString::reserve(int size){
	if(size<=memory_capacity)//enough memory for reserve
		return;
	MyString temp=*this;//copy for content
	delete[] string_content;//delete content for reallocation
	string_content=new char[size];//reallocation
	for(int i=0; i<temp.string_length; i++)//move content
		string_content[i]=temp.string_content[i];
	memory_capacity=size;//set
	//automatically call temp's destructor
}

void MyString::print() const{
	for(int i=0; i<string_length; i++)
		std::cout<<string_content[i];
}
void MyString::println() const{
	for(int i=0; i<string_length; i++)
		std::cout<<string_content[i];
	std::cout<<std::endl;
}

int main(){
	return 0;
}
