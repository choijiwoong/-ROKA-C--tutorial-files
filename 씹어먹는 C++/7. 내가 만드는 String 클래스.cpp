//1. ���ڿ� Ŭ������ ������.
#include <iostream>
#include <string.h>//only for strlen. if you make strlen function, it's not needed. 

class MyString{//private�� �����صΰ�, ��� �۾��� ������ �� �ִ� �Լ��� ������ �Ѵ�. _encapsulation
	char* string_content;//pointer that locate string data
	int string_length;//string length_it's not need 'NULL' because we can check the end of string thanks to strign_lengh
	int memory_capacity;//how many memory is used?
	
	public:
		//make by one char
		MyString(char c);
		//make by char array(string)
		MyString(const char* str);
		//copy constructor
		MyString(const MyString& str);
		//destructor
		~MyString();
		//get length
		int length() const;//make it const function_Only read
		//make print
		void print() const;
		//make print with \n
		void println() const;
		
		//function assign_when type is MyString
		MyString& assign(const MyString& str);
		//function assign_when type is char*
		MyString& assign(const char* str);
		
		//function memory_capacity_reserve size of char that will be allocated.
		void reserve(int size);
		//function memory_capacity_return memory_capacity.
		int capacity(); 
		
		//return char in random location
		char at(int i) const;
		
		//string insert function
		MyString& insert(int loc, const MyString& str);//MyString type
		MyString& insert(int loc, const char* str);//char[] type_it will be coded by MyString type function
		MyString& insert(int loc, char c);//char type_too.
		
		//erase function
		MyString& erase(int loc, int num); 
		
		//find function
		int find(int find_from, MyString& str) const;//Like insert func
		int find(int find_from, const char* str) const;
		int find(int find_from, char c) const;
}; 
MyString::MyString(char c){
	string_content=new char[1];
	string_content[0]=c;
	string_length=1;
}
MyString::MyString(const char* str){
	string_length=strlen(str);
	string_content=new char[string_length];
	
	for(int i=0;i!=string_length;i++) string_content[i]=str[i];
}
MyString::MyString(const MyString& str){
	string_length=str.string_length;
	string_content=new char[string_length];
	for(int i=0;i!=string_length;i++) string_content[i]=str.string_content[i];
}
MyString::~MyString() { delete[] string_content; }//In constructor, string_content is set by dinamic allocation,
												  //It must deleted at destructor
int MyString::length() const{ return string_length; }//string_length must be setup correct value when it controll
void MyString::print() const{
	for (int i=0;i!=string_length;i++){
		std::cout<<string_content[i];
	}
}
void MyString::println() const{
	for (int i=0;i!=string_length;i++){
		std::cout<<string_content[i];
	}
	std::cout<<std::endl;
}
MyString& MyString::assign(const MyString& str){//Q. why return type is reference?
	//if (str.string_length>string_length){//then it need to reallocation
	if(str.string_length>memory_capacity){
		delete[] string_content;
		string_content=new char[str.string_length];
		memory_capacity=str.string_length;//after reallocation, reset memory capacity.
	}//In case else, it's not needed to reallocation because empty space is not used thanks to string_length.
	for(int i=0;i!=str.string_length;i++){//save string
		string_content[i]=str.string_content[i];
	}
	string_length=str.string_length;//reset string_length to correct length
	
	return *this;//return this object. (this is pointer that locate now object, * makes it's value)
}
MyString& MyString::assign(const char* str){
	int str_length=strlen(str);//save str's length to str_length**not string_length**
	//if(str_length>string_length){//for more efficient in case else.
	if(str_length>memory_capacity){
		delete[] string_content;//delete allocation location(string_content)
		string_content=new char[str_length];//do reallocation
		memory_capacity=str_length;//set memory_capccity after reallocation.
	}
	for(int i=0;i!=str_length;i++){
		string_content[i]=str[i];
	}
	string_length=str_length;
	
	return *this;
}
int MyString::capacity() { return memory_capacity; }
void MyString::reserve(int size){//just expand memory
	if(size>memory_capacity){//whether memory need expand. so if it's not need, then nothing.
		char *prev_string_content=string_content;//new pointer(for data backup) set string_content's pointer
		string_content=new char[size];//renew allocate string_content to reserveed size.
		memory_capacity=size;//set memory_capacity to reserved size.
		for(int i=0;i!=string_length;i++)//reloading backup data at prev_string_content.
			string_content[i]=prev_string_content[i];//load
		delete[] prev_string_content;//delete prev_string_content that worked as backup buffer.
	}
}
char MyString::at(int i) const{
	if (i>=string_length||i<0)//error case in C
		return NULL;//return Null.
	else
		return string_content[i];
}
MyString& MyString::insert(int loc, const char* str){//use insert function
	MyString temp(str);//change to MyString object
	return insert(loc, temp);
}
MyString& MyString::insert(int loc, char c){
	MyString temp(c);
	return insert(loc, temp);
}
MyString& MyString::insert(int loc, const MyString& str){
	//except out range case
	if(loc<0||loc>string_length) return *this;
	//In case, over capacity.
	if(string_length+str.string_length>memory_capacity){
		if(memory_capacity*2>string_length+str.string_length)//less thean memory*2==small char. capacity x2 for prevent repeat insert
			memory_capacity*=2;
		else//new memory allocation
			memory_capacity=string_length+str.string_length;
		
		char* prev_string_content=string_content;//backup
		string_content=new char[memory_capacity];//allocation_as capacity
		
		//copy content before insert part
		int i;
		for(i=0;i<loc;i++){
			string_content[i]=prev_string_content[i];
		}
		//add insert string
		for(int j=0;j!=str.string_length;j++){
			string_content[i+j]=str.string_content[j];
		}
		//copy last part
		for(;i<string_length;i++){
			string_content[str.string_length+i]=prev_string_content[i];
		}
		
		delete[] prev_string_content;
		
		string_length=string_length+str.string_length;
		return *this;
	} 
	//else case(not need new allocation)_for efficiency, push left parts first.
	for(int i=string_length-1;i>=loc;i--)//push to back without delete thanks to enough capacity.
		string_content[i+str.string_length]=str.string_content[i];
	//insert string
	for(int i=0;i<str.string_length;i++)
		string_content[i+loc]=str.string_content[i];
		
	string_length=string_length+str.string_length;
	return *this;
}
MyString& MyString::erase(int loc, int num){//not need think about capacity.
	if(num<0||loc<0||loc>string_length) return *this;
	//erase means just pulling back string to front
	for(int i=loc+num;i<string_length;i++){
		string_content[i-num]=string_content[i];
	}
	string_length-=num;
	return *this;
}
int MyString::find(int find_from, MyString& str) const{
	int i, j;
	if(str.string_length==0) return -1;
	
}


int main() {
  MyString str1("hello world!");
  MyString str2(str1);

  str1.println();
  str2.println();
  
  //occur not efficient problem in case assign. because we use strign_length.
  MyString str3("very very very long string");//ex) 1000bites allocate
  
  str3.reserve(30);
  std::cout<<"Capacity : "<<str3.capacity()<<std::endl;//print 30
  std::cout<<"String length : "<<str3.length()<<std::endl;//print 26
  str3.println();
  
  str3.assign("short string");//reset string_length without delete memory.(memory size is still 1000bite!)
  str3.assign("very long string");//because computer don't know 1000bites is already allocate, it reallocate memory to store very long string.
  //sol. how many memory is allocated? -> Plus variable 'memory_capacity'.
  
  std::cout<<"str3's char in 3place:   "<<str3.at(3)<<std::endl;
  
  MyString str4("<some string inserted between>");
  str3.insert(5,str4);
  str3.println();
  
  std::cout<<"Capacity : "<<str3.capacity()<<std::endl;//enough capacity
  std::cout<<"String length : "<<str3.length()<<std::endl;
  
  str3.erase(1,2);
  str3.println();
  std::cout<<"Capacity : "<<str3.capacity()<<std::endl;//enough capacity
  std::cout<<"String length : "<<str3.length()<<std::endl;
  
  return 0;
}

/*
[1. ���ڿ� Ŭ������ ������]
1. ���� C���� ���ڿ��� ��Ÿ���� ���Ͽ� �� ���� ���ڿ�(Null-terstd::minatinf string)�� ������ �����Ͽ�
   ���ڿ� ���� NULL���ڸ� �ٿ� ���ڿ��� ��Ÿ���� ����� ����ߴ�.
   ������, �̴� ���ڿ��� ũ�⸦ �ٲٰų�, ���ڿ��� ��ġ�µ� �� ���ŷο��� �־���.
     �̷��� ������ �ذ��ϱ� ����, C++������ ����� �������� ǥ�� ���̺귯���� stringŬ������ �����ϰ� �ִ�. #include <string> 
	(p.s C++�� string����� ����.) 
2.  ���ڿ� Ŭ������ ����µ��� �ʿ��� ����Լ��� �켱, ���ڿ��� ����� ������ ����Ű�� �����Ϳ�, ���̰� �ִ�.
    ���ڿ��� �ƴ� �����͸� �����ϴ� ������ ũ���� ������ �����̰�, ���̸� �����ϴ� ������ �Ź� �����ϸ� ��ȿ�����̱� �����̴�.

[2. assign �Լ�]_�����ϴ�. ��� ������ =�� ������ ��Ȱ�� �Ѵ�. ex) str.assign("abc");�� str�� ���� ���ڰ� �������� "abc"�Ҵ�. 
1.  �޸� �Ҵ��� ȿ�������� �ϱ� ���� memory_capacity������ �߰� �����Ͽ���.
	�̷� ����, �Ҵ��� ���ڿ��� �̸� �����صδ� reserve�Լ�, ���� ���ڿ��� �Ҵ�� �޸��� ũ�⸦ ��Ÿ����
	capacity�Լ� �� ���� �Լ����� �߰��� �� �ְ� �Ǿ���. 
2.	������ ��ġ�� ���ڸ� �����ϴ� �Լ��� C���� []�� �����Ǿ��� ����, ������ ������ ����� ��ġ�� ����
	���ڸ� �䱸�ص� ó���� �� �ۿ� ��������(������ ��), C++������ �̷��� ������ �ذ��� �� �ִ�.  
[3. ���ڿ� �����ϱ�(insert)]
1.	�̹� �������� �Լ��� �̿��Ͽ� insert������ �� �� ������, ����ϰ� ���ȴٴ� ���� ����Ͽ� ���� ��������. 
2.	�ַ� insert�� ����ϴ� ����, ���� ũ���� ���ڿ����� ���� ����ִ� ����̴�. �׷��ٸ� ���� capacity �Ѱ迡 ����
	���ڿ� Ŭ������ ���� a�� ��� �߰��Ѵٸ�?
	while(sone_condition){
		str.insert(some_location,'a');
	}
	�Ź� �޸�ň �����ϰ� 1ū �޸𸮸� �Ҵ��ϰ�,,,,�ϴ� ��ȿ���� �ݺ��� �߻��Ѵ�.
	�� ¥���ϰ� insert�ϴ� ��ɿ����� �� ũ�� �޸𸮸� �̸� reserver�ϴ� �۾��� �ʿ��ϴ�.
	 'insert �۾������� ���� �Ҵ�/������ ���ϱ� ���� �̸� �޸𸮸� �Ҵ��س���'�� '�޸𸮸� �Ҵ��� ����, ���� �ڿ��� �������� �ʴ´�.'
	 �� ��� ������Ű�� ����, ����ũ���� �� �� ������ �Ҵ��� ������ �ȴ�. _capacity control
[4. erase �Լ�]<->insert 
[5. find �Լ�]
1.	���ڿ��� ũ�Ⱑ ũ�ٸ� ��û ���� �ɸ� �� �ִ� �Լ��̴�. 
2.	���ڿ��� �˻��ϴ� �˰����� ������, � ��Ȳ�� ���� ���� ������ �����ϴ� �˰����� ����. 
*/ 
