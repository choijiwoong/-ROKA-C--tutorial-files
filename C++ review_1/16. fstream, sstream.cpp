#include <iostream>
#include <fstream>

//ifstream 
int main(){
	std::ifstream in("test.txt");//we don't need to close without reopen
	std::string s;
	
	if(in.is_open()){//if(in) is possible that means no flag
		in.seekg(0, std::ios::end);//move location pointer to end of file. first argument is location in file.
		int size=in.tellg();//read location for resizing
		
		s.resize(size);//allocate
		in.seekg(0, std::ios::beg);//move loation pointer to start of file
		
		in.read(&s[0], size);//storage, read_size
		//in getline(&s[0], 100);//read file by line
		
		std::cout<<s<<std::endl;
	} else{
		std::cout<<"cannot find file"<<std::endl;
	}
	
	return 0;
} 

//ofstream
#include <string>

class Human{
	std::string name;
	int age;
	
	public:
		Human(const std::string& name, int age): name(name), age(age){}
		std::string get_info(){ return "Name :: "+name+" / Age :: "+std::to_string(age); }
		
		friend std::ofstream& operator<<(std::ofstream& o, Human& h);//ofstream overloading
};

std::ofstream& operator<<(std::ofstrea& o, Human& h){//same to ostream
	o<<h.get_info();
	return o;
}

int main(){
	std::ofstream out("test.txt");
	
	Human h("psi", 60);
	out<<h<<std::endl;//same to ostream
	
	return 0;
}

//std::stringstream
#include <sstream>//string stream

double to_number(std::string s){
	std::istringsteam ss(s);//like input stream initializing to s
	double x;
	
	ss->x;//input
	return x;
} 

std::string to_str(int x){
	std::ostringstream ss;//like output stream
	ss<<x;//input x to ss
	
	return ss.str();
}

int main(){
	std::cout<<"convert:: 1+2= "<<to_number("1")+to_number("2")<<std::endl;
	std::cout<<"convert:: 1+2= "<<to_str(1+2)<<std::endl;
}

/*
1.	fstream은 기본적인 istream&ostream보다 지원하는 기능이 많기에 상속받아 작성되었으며, 각각을 상속받은 것이 ifstream과 ostream이며 이들을 모두 포함하는 fstream라이브러리를 사용한다.
2.	file의 while조건으로 in.eof()는 파일 읽기가 안전하다 라는 보장을 하지 않는다.
3.	sstream의 std:istringstream은 문자열을 하나의 스트림처럼 생각하게 해주는 가상화 장치이다. 이를 사용하여 간단하게 atoi, to_str을 구현할 수 있다. 입출력 과정을 이용한 형변환 개념. 
*/ 
