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
	const MyString temp=*this;//copy for content
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
	this->print();
	std::cout<<std::endl;
}

MyString& MyString::assign(const MyString& str){
	if(str.string_length>memory_capacity){//allocation is needed
		delete[] string_content;
		string_content=new char[str.string_length];
		for(int i=0; i<str.string_length; i++)
			string_content[i]=str.string_content[i];
		memory_capacity=str.string_length;
		string_length=str.string_length;
		return *this;
	}
	//no allocation
	for(int i=0; i<str.string_length; i++)
		string_content[i]=str.string_content[i];
	string_length=str.string_length;
	return *this;
}
MyString& MyString::assign(const char* str){
	//MyString temp(str);
	//return this->assign(temp);
	const int str_length=strlen(str);
	if(str_length>memory_capacity){//allocation is needed
		delete[] string_content;
		string_content=new char[str_length];
		for(int i=0; i<str_length; i++)
			string_content[i]=str[i];
		memory_capacity=str_length;
		string_length=str_length;
		return *this;
	}
	//no allocation
	for(int i=0; i<str_length; i++)
		string_content[i]=str[i];
	string_length=str_length;
	return *this;
}

char MyString::at(int i) const{
	if(i<0||i>string_length)
		return -1;
	return string_content[i];
}

MyString& MyString::insert(int loc, const MyString& str){
	if( str.string_length==0||(loc<0||loc>string_length) )//exceptions
		return *this;
	
	const int total_length=string_length+str.string_length;//total string length
	if(total_length>memory_capacity){//allocation is needed
		const MyString temp(*this);//copy
		delete[] string_content;
		//allocation by size
		if(total_length<memory_capacity*2){//small size_enough space
			string_content=new char[total_length*2];
			memory_capacity=total_length*2;
		} else{//big size_fit space
			string_content=new char[total_length];
			memory_capacity=total_length;
		}
		//shift  "asffa" 1, "asf"  "as asf ffa"
		for(int i=0; i<string_length; i++)//move initial data after allocation
			string_content[i]=temp.string_content[i];
		for(int i=total_length-1; i>loc+str.string_length; i--)//shift for space
			string_content[i]=string_content[i-1];
		for(int i=loc; i<loc+str.string_length; i++)//insert
			string_content[i]=str.string_content[i-loc];
		string_length=total_length;
		
		return *this;
	}
	//no allocation
	for(int i=total_length-1; i>loc+str.string_length; i--)//make shift for space
		string_content[i]=string_content[i-1];
	for(int i=loc; i<loc+str.string_length; i++)//insert
		string_content[i]=str.string_content[i-loc];
	string_length=total_length;
		
	return *this;
}
MyString& MyString::insert(int loc, const char* str){//_error occur!
	//MyString temp(str);
	//return this->insert(loc, temp);
	const int str_length=strlen(str);
	if(str_length==0||(loc<0||loc>string_length))//exception
		return *this;
		
	const int total_length=string_length+str_length;//_error1 of this. string_length=str.length
	if(memory_capacity<total_length){//allocation is needed
		const MyString temp(*this);//copy
		delete[] string_content;
		
		if(memory_capacity*2<total_length){//big size
			string_content=new char[total_length];
			memory_capacity=total_length;
		} else{//small size
			string_content=new char[total_length*2];
			memory_capacity=total_length*2;
		}
		
		for(int i=0; i<string_length; i++)//save initial data
			string_content[i]=temp.string_content[i];
		for(int i=total_length-1; i>loc+str_length; i--)//shift
			string_content[i]=string_content[i-1];
		for(int i=loc; i<loc+str_length; i++)//save
			string_content[i]=str[i-loc];
		
		string_length=total_length;//_error3 of this. =str_length
		return *this;
	}
	//no allocation
	for(int i=total_length-1; i>loc+str_length; i--)//_error2 of this. i<loc+str_length
		string_content[i]=string_content[i-1];
	for(int i=loc; i<loc+str_length; i++)
		string_content[i]=str[i-loc];
		
	string_length=total_length;//_error3 of this. =str_length
	return *this;
}
MyString& MyString::insert(int loc, char c){
	if(loc>string_length||loc<0)//exception
		return *this;
		
	if(1+string_length>memory_capacity)//allocation is needed
		this->reserve(1);
		
	for(int i=string_length; i>loc; i--)
		string_content[i]=string_content[i-1];
	string_content[loc]=c;
	string_length++;
	
	return *this;
}

MyString& MyString::erase(int loc, int num){
	if((loc<0||loc>string_length) || (num==0||loc+num>string_length))//exception
		return *this;
	
	for(int i=loc; i<string_length-num; i++)
		string_content[i]=string_content[i+num];
	string_length-=num;
	
	return *this;
}

int MyString::find(int find_from, const MyString& str) const{//여서부터 찬스 
	if(str.string_length==0)//exception
		return -1;
	int i, j;
	for(i=find_from; i<=string_length-str.string_length; i++){//first char as standard 
		for(j=0; j<str.string_length; j++){
			if(string_content[i+j]!=str.string_content[j])//if different, check next fisrt char
				break;
			}//if same, loop keep going.
		if(j==str.string_length)//finally, same all stirng, return first index of start point
			return i;	
	}
	return -1;
}
int MyString::find(int find_from, const char* str)const{
	const MyString temp(str);
	return find(find_from, temp);
}
int MyString::find(int find_from, char c) const {
	const MyString temp(c);
	return find(find_from, temp);
}

int MyString::compare(const MyString& str) const{
	//(*this)-(str) =1(*this가 뒤에), 0(같음), -1(*this가 앞에)
	for(int i=0; i<std::min(string_length, str.string_length); i++){
		if(string_content[i]>str.string_content[i])
			return 1;
		else if(string_content[i]<str.string_content[i])
			return -1;
	} 
	//앞부분까지 똑같다면 아래 코드 수행
	if(string_length==str.string_length)
		return 0;
		
	else if(string_length>str.string_length)
		return 1;
	return -1; 
}


int main(){
	//check constructor
	MyString string1("hello Mr.Been");
	MyString string3('c');
	MyString string2(string3);
	
	//check print function
	string1.println();
	string2.print();
	string3.println();
	
	//check reserve
	std::cout<<std::endl<<"<reserve part>"<<std::endl;
	string1.reserve(20);
	std::cout<<"string1's length: "<<string1.length()<<" string1's capacity after reserve(20): "<<string1.capacity()<<std::endl;	
	
	//check assign
	std::cout<<std::endl<<"<assign part>"<<std::endl;
	string2.assign(string3);
	string3.assign("assign is sign");
	std::cout<<"string3 after assign: ";
	string3.println();
	std::cout<<"string2 after assign: ";
	string2.println();
	std::cout<<std::endl;
	
	//check at
	std::cout<<std::endl<<"<at part>"<<std::endl;
	std::cout<<"string1[5~7]: "<<string1.at(5)<<string1.at(6)<<string1.at(7)<<std::endl;
	
	//check insert
	std::cout<<std::endl<<"<insert part>"<<std::endl;
	string1.insert(string1.length(),'!');
	std::cout<<"string1 is added '!'?:  ";
	string1.println();
	
	char mess[6]=" jimo";
	string1.insert(string1.length(), mess);//error occur! solved!
	std::cout<<"string1 is added name?:  ";
	string1.println();
	
	MyString pppp(mess);
	string3.insert(string3.length()-1, pppp);//error occur! 사이즈를 1 크게 인식? \n때문에 
	std::cout<<"string3 is added name?:  ";
	string3.println();
	
	//skip
	std::cout<<string1.compare(string2)<<std::endl;
	
	return 0;
}

//여러 검색 알고리즘(KMP, Boyer-Moore)을 사용할 수 있다. 알고리즘에 따라 미리 계산된 체이블이 필요할 수 있는데, 이는 class로 처리할 수 있다.
 
