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
1.	fstream�� �⺻���� istream&ostream���� �����ϴ� ����� ���⿡ ��ӹ޾� �ۼ��Ǿ�����, ������ ��ӹ��� ���� ifstream�� ostream�̸� �̵��� ��� �����ϴ� fstream���̺귯���� ����Ѵ�.
2.	file�� while�������� in.eof()�� ���� �бⰡ �����ϴ� ��� ������ ���� �ʴ´�.
3.	sstream�� std:istringstream�� ���ڿ��� �ϳ��� ��Ʈ��ó�� �����ϰ� ���ִ� ����ȭ ��ġ�̴�. �̸� ����Ͽ� �����ϰ� atoi, to_str�� ������ �� �ִ�. ����� ������ �̿��� ����ȯ ����. 
*/ 
