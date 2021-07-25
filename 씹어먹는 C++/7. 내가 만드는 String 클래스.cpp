//1. 문자열 클래스를 만들자.
#include <iostream>
#include <string.h>//only for strlen. if you make strlen function, it's not needed. 

class MyString{//private로 설정해두고, 모든 작업을 수행할 수 있는 함수를 만들어야 한다. _encapsulation
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
[1. 문자열 클래스를 만들자]
1. 기존 C언어는 문자열을 나타내기 위하여 널 종료 문자열(Null-terstd::minatinf string)의 개념을 도입하여
   문자열 끝에 NULL문자를 붙여 문자열을 나타내는 방식을 사용했다.
   하지만, 이는 문자열의 크기를 바꾸거나, 문자열을 합치는데 등 번거로움이 있었다.
     이러한 문제를 해결하기 위해, C++에서는 언어적 차원에서 표준 라이브러리로 string클래스를 지원하고 있다. #include <string> 
	(p.s C++는 string사용을 권장.) 
2.  문자열 클래스를 만드는데에 필요한 멤버함수는 우선, 문자열이 저장된 공간을 가리키는 포인터와, 길이가 있다.
    문자열이 아닌 포인터를 저장하는 이유는 크기의 변경을 위함이고, 길이를 저장하는 이유는 매번 연산하면 비효율적이기 때문이다.

[2. assign 함수]_지정하다. 라는 뜻으로 =과 동일한 역활을 한다. ex) str.assign("abc");는 str의 기존 문자가 지워지고 "abc"할당. 
1.  메모리 할당을 효율적으로 하기 위해 memory_capacity변수를 추가 도입하였다.
	이로 인해, 할당할 문자열을 미리 예약해두는 reserve함수, 현재 문자열의 할당된 메모리의 크기를 나타내는
	capacity함수 등 여러 함수들을 추가할 수 있게 되었다. 
2.	임의의 위치의 문자를 리턴하는 함수로 C언어에서 []로 구현되었을 때는, 구조상 범위를 벗어나는 위치에 대한
	문자를 요구해도 처리할 수 밖에 없었지만(쓰레기 값), C++에서는 이러한 문제를 해결할 수 있다.  
[3. 문자열 삽입하기(insert)]
1.	이미 만들어놓은 함수를 이용하여 insert구현을 할 수 있지만, 빈번하게 사용된다는 점을 고려하여 따로 만들어두자. 
2.	주로 insert를 사용하는 경우는, 작은 크기의 문자열들을 자주 집어넣는 경우이다. 그렇다면 만약 capacity 한계에 달한
	문자열 클래스에 문자 a를 계속 추가한다면?
	while(sone_condition){
		str.insert(some_location,'a');
	}
	매번 메모리흫 해제하고 1큰 메모리를 할당하고,,,,하는 비효율의 반복이 발생한다.
	즉 짜잘하게 insert하는 명령에서는 통 크게 메모리를 미리 reserver하는 작업이 필요하다.
	 'insert 작업에서의 잦은 할당/해제를 피하기 위해 미리 메모리를 할당해놓기'와 '메모리를 할당해 놓되, 많은 자원을 낭비하지 않는다.'
	 를 모두 만족시키기 위해, 현재크기의 두 배 정도를 할당해 놓으면 된다. _capacity control
[4. erase 함수]<->insert 
[5. find 함수]
1.	문자열의 크기가 크다면 엄청 오래 걸릴 수 있는 함수이다. 
2.	문자열을 검색하는 알고리즘은 많지만, 어떤 상황에 대해 좋은 성능을 발휘하는 알고리즘은 없다. 
*/ 
