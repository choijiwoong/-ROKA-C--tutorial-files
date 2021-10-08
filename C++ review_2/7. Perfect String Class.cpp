
/* MYSTRING 
#include <iostream>
#include <string.h>

class MyString{
	char* string_content;
	int string_length;
	int memory_capacity;
	
	public:
		MyString(char c);
		MyString(const char* str);
		MyString(const MyString& str);
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
		char operator[](int i) const;
		
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
		
		friend std::ostream& operator<<(std::ostream& os, MyString& temp);
};
MyString::MyString(char c){
	string_content=new char[1];
	string_content[0]=c;
	string_length=1;
	memory_capacity=1;
}
MyString::MyString(const char* str){
	string_length=strlen(str);
	string_content=new char[string_length];
	for(int i=0; i<string_length; i++)
		string_content[i]=str[i];
	memory_capacity=string_length;
}
MyString::MyString(const MyString& str){
	string_length=str.string_length;
	string_content=new char[str.memory_capacity];
	for(int i=0; i<string_length; i++)
		string_content[i]=str.string_content[i];
	memory_capacity=str.memory_capacity;
}
MyString::~MyString(){
	if(string_content!=nullptr)//if it's already nullptr, we don't have to free memory
		delete[] string_content;
}

int MyString::length() const{ return string_length; }
int MyString::capacity() const{ return memory_capacity; }
void MyString::reserve(int size){
	if(size<=memory_capacity)//Exception already enough memory
		return;
	const MyString temp=*this;
	delete[] string_content;
	string_content=new char[size];
	for(int i=0; i<temp.string_length; i++)
		string_content[i]=temp.string_content[i];
	memory_capacity=size;
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
	if(str.string_length>memory_capacity){
		delete[] string_content;
		string_content=new char[str.string_length];
		for(int i=0; i<str.string_length; i++)
			string_content[i]=str.string_content[i];
		memory_capacity=str.string_length;
		string_length=str.string_length;
		return *this;
	}
	//no need for allocation
	for(int i=0; i<str.string_length; i++)
		string_content[i]=str.string_content[i];
	string_length=str.string_length;
	return *this;
}
MyString& MyString::assign(const char* str){
	MyString temp(str);
	return this->assign(temp);
}
char MyString::operator[](int i) const{
	if(i<0||i>string_length)
		return -1;
	return string_content[i];
}

MyString& MyString::insert(int loc, const MyString& str){
	if( str.string_length==0||(loc<0||loc>string_length) )
		return *this;
	
	const int total_length=string_length+str.string_length;//total string length
	if(total_length>memory_capacity){
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
MyString& MyString::insert(int loc, const char* str){
	MyString temp(str);
	return this->insert(loc, temp);
}
MyString& MyString::insert(int loc, char c){
	MyString temp(c);
	return this->insert(loc, temp);
}

MyString& MyString::erase(int loc, int num){
	if((loc<0||loc>string_length) || (num==0||loc+num>string_length))
		return *this;
	
	for(int i=loc; i<string_length-num; i++)
		string_content[i]=string_content[i+num];
	string_length-=num;
	
	return *this;
}

int MyString::find(int find_from, const MyString& str) const{
	if(str.string_length==0)
		return -1;
	int i, j;
	for(i=find_from; i<=string_length-str.string_length; i++){ 
		for(j=0; j<str.string_length; j++){
			if(string_content[i+j]!=str.string_content[j])
				break;
		}
		if(j==str.string_length)//little unefficient
			return i;	
	}
	return -1;//we have to make special exception by this value
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
	//(*this)-(str) =1(*this�� �ڿ�), 0(����), -1(*this�� �տ�)
	for(int i=0; i<std::min(string_length, str.string_length); i++){
		if(string_content[i]>str.string_content[i])
			return 1;
		else if(string_content[i]<str.string_content[i])
			return -1;
	} 
	//compare by size
	if(string_length==str.string_length)
		return 0;
	else if(string_length>str.string_length)
		return 1;
	else
		return -1; 
}

std::ostream& operator<<(std::ostream& os, MyString& temp){
	for(int i=0; i<temp.string_length; i++)
		os<<temp.string_content[i];
	return os;
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
	std::cout<<"string1[5~7]: "<<string1[5]<<string1[6]<<string1[7]<<std::endl;
	
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
	string3.insert(string3.length()-1, pppp);//error occur! ����� 1 ũ�� �ν�? \n������ 
	std::cout<<"string3 is added name?:  ";
	string3.println();
	
	//skip
	std::cout<<std::endl<<string1<<", "<<string2<<", "<<string1.compare(string2)<<std::endl;
	
	return 0;
}*/

/*example of KMP
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int* table;

//by pattern
int* createTable(char* string, int stringLen){//content & length as argument
	int j;
	table=(int*)malloc(sizeof(int)*(stringLen+1));//allocation
	table[0]=-1;//default value of table
	
	for(int i=1; i<stringLen+1; i++)
		table[i]=0;//initialization
	
	j=0;//���̺� ���� �� 
	for(int k=1; k<stringLen; k++){//���Ϻ��濡 ���� �ε��� ���� 
		while(string[j]!=string[k] && j>0)
			j=table[j];
		
		if(string[j]==string[k])
			table[k+1]=++j;
	}
	
	return table;
}

void KMP(char* string, char* pattern){
	int* table;
	
	int stringLen=strlen(string);
	int patternLen=strlen(pattern);
	int distance=0, idx=0, cnt=0;
	int findFlag=0;
	
	table=createTable(pattern, patternLen);
	while(true){
		idx=0;
		if((idx+distance)+patternLen>stringLen)
			break;
		
		while(string[idx+distance]==pattern[cnt]){
			cnt++;
			idx++;
			
			if(cnt==patternLen){
				printf("finding complete at %d!\n", distance+1);
				findFlag=1;
				break;
			}
		}
		
		distance=distance+(cnt-table[cnt]);
		cnt=0;
	}
	
	if(findFlag==0)
		printf("can't fine that pattern.\n");
}

int main(){
	char* string="ABAABACABAACCABACABACABAACABACABAAC";
	char* pattern="ABACABAAC";
	KMP(string, pattern);
}*/

/*example of BoyerMooreSearch
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int Max(int a, int b){
	if(a>b)
		return a;
	return b;
} 

int BoyerMooreSearch(char* txt, char* pat){
	int lengTxt=strlen(txt);
	int lengPat=strlen(pat);
	int badchar[256]={-1,};
	for(int i=0; i<lengPat; i++)
		badchar[(int)pat[i]]=i;
		
	int s=0, j;
	while(s<lengTxt-lengPat){
		j=lengPat-1;
		while(j>=0 && txt[s+j]==pat[j])
			j--;
		
		if(j<0){
			printf("searched at %d\n", s);
			s+=(s<lengTxt-lengPat)? lengPat-badchar[(int)txt[s+lengPat]]: 1;
		} else{
			s+=Max(1, j-badchar[(int)txt[s+j]]);
		}
	}
}

int main(){
	char txt[]="GCTTCTGCTACCTTTTGCGCGCGCGCGGAA";
	char pat[]="CCTTTTGC";
	
	BoyerMooreSearch(txt, pat);
}*/

//example of Rabin-Karp Search
#include <stdio.h>
#include <string.h>

void check(char* parent, char* pattern, int start){
	int found=1;
	int patternSize=strlen(pattern);
	for(int i=0; i<patternSize; i++){
		if(parent[start+i]!=pattern[i]){
			found=0;
			break;
		}
	}
	if(found){
		printf("searched at %d\n",start+1);
	}
}

void rabinKarp(char* parent, char* pattern){
	int parentSize=strlen(parent);
	int patternSize=strlen(pattern);
	int parentHash=0;
	int patternHash=0;
	int power=1;
	
	for(int i=0; i<parentSize-patternSize; i++){
		if(i==0){
			for(int j=0; j<patternSize; j++){
				parentHash=parentHash+parent[patternSize-1-j]*power;
				patternHash=patternHash+pattern[patternSize-1-j]*power;
				if(j<patternSize-1)
					power=power*2;
			}
		} else{
			parentHash=2*(parentHash-parent[i-1]*power)+parent[patternSize-1+i];
		}
		
		if(parentHash==patternHash)
			check(parent, pattern, i);
	}
}

int main(){
	char parent[]="acabacdabac";
	char pattern[]="abacdab";
	
	rabinKarp(parent, pattern);
}

//���� �˻� �˰���(KMP, Boyer-Moore)�� ����� �� �ִ�. �˰��� ���� �̸� ���� ü�̺��� �ʿ��� �� �ִµ�, �̴� class�� ó���� �� �ִ�.
/*
1.	�������� �˰���(Brute Force)
	�ϳ��ϳ�
2.	KMP �˰���(Knuth Morris Partt Algorithm)
	�켱 ���� ���κο� ���̺ΰ� ���� �� �� ���κ� Ȥ�� ���̺θ� ����Ų��.
	 ã������ ������ �Ϻΰ� �������� ���ڿ��� ��ġ���� �ʴ´ٸ�, ����ġ�� �κ��� ������ ���������� ���Ͽ��� �ִ� ������ ��踦 ã�´�. ��, ���� �κб��� �߿��� �ݺ��Ǵ� ������ ã�� ���̴�. 
	�� ��, ã������ ������ ���̺��� ���� ���ڿ����� �̵���Ų��. �� �����κб��� �߿� �ݺ��Ǵ� ������ �ִٸ� �� 2��° ������ ���������� ��� Ž���� �����Ѵ�. 
	 ���� ��谡 ���ų� ����ġ�Ѵٸ�, ó������ ����ġ�� �κк��� Ž���� �����Ѵ�. 
	�̴� ��ĭ�� �з������� Breute force���� ȿ�����̴�. �ֳ��ϸ� �ִ������ ��踦 ã���� ���� ĭ�� �н��� ���� �ƴ϶� ������ Ȯ���� ��������,
	��ã�´ٰ� �ϴ��� Ʋ���κк��� ã�⿡ ȿ�����̴�.
	
	 �ٸ� �Ź� ������ ������ ��踦 ã�� ���� KMP�˰����� ȿ������ ����߸��⿡ �̵���ų �� ������ �� �ִ� �̵���� ���̺��� �ʿ��ϴ�.
	��ġ�ϴ� ������ ���̿��� �ִ� ���ʺ� ���� �̵��Ÿ��� ���Ѵ�. 
3.	���̾�-���� �˰���(Boyer-Moore algorithm)
	�޺κп��� ����ġ�� �Ͼ Ȯ���� ���ٴ� ������ �̿��Ͽ� ������ ������ �񱳸� �����Ѵ�. 
	 skip���̺��� ����� ���ں��� �� ĭ �̵��� �������� ���� ������ �����Ѵ�. 
	��������� KMP���� ���̾� �� ������ ����. 
4.	���-ī�� �˰���(Rabin-Karp Algorithm)
	ã�� ���ڿ��� �ƽ�Ű�ڵ尪�� 2^�ڸ����� ������ ��Ÿ����(�ؽ���), �ؽ����� ������ ��츦 �߰��� ���� �����Ѵ�. 
*/ 
