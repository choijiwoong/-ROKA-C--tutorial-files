#include <iostream>
#include <string>
#include <fstream> 

#include <sstream>//5
/*1
int main(){
	//1
	std::ifstream in("test.txt");//ready for read file.
	std::string s;
	
	if(in.is_open()){//TIC
		in>>s;//content save to s. of coursely, read until space.
		std::cout<<"�Է� ���� ���ڿ� :: "<<s<<std::endl;//print
	} else{
		std::cout<<"������ ã�� �� �����ϴ�!"<<std::endl;
	}
	//2
	in.close();//situation that we have to close ifstream directly. 
	in.open("other.txt");//for use other file with same variable.
	
	if(in.is_open()){
		in>>s;
		std::cout<<"�Է� ���� ���ڿ� :: "<<s<<std::endl;
	} else{
		std::cout<<"������ ã�� �� �����ϴ�!"<<std::endl;
	} 
	//3
	in.close();
	in.open("test.txt", std::ios::binary);//std::ifstream in("test.txt", std::ios::binary);_p.s std::ios::binary is just number.
	//we will receive test.txt to binary type. that means receving binary value directly not string data. 
	int x;//read by binary number
	if(in.is_open()){
		in.read((char*)(&x),4);//read 4 bites content. first argument means buffer.so we send data with int varuable that works as char array has 4 bites.
		std::cout<<std::hex<<x<<std::endl;
	} else{
		std::cout<<"������ ã�� �� �����ϴ�!"<<std::endl;
	}
	
	return 0;
} */

//int main(){
	//2
	/*2-1. all content read
	std::ifstream in ("test.txt");//ready for file read
	std::string s;//variable for save file data
	
	if(in.is_open()){//file is open
		in.seekg(0,std::ios::end);//location designator to end of file
		//move location designator to std::ios::end+0; end of file.
		int size=in.tellg();//read that location==file size because we move location defignator to end of file.
		//save location of location designator. we moved loc-designator to end of file so that's location means file size.
		s.resize(size);//allocate string that size
		//string reallocation with file size.
		in.seekg(0, std::ios::beg);//move location designator to start point of file.
		//loc-desig is now at end of file, so remove to start point by seekg function.
		in.read(&s[0], size);//read file content and save at string
		//all content in in read to &s[0] as much as file size.
		std::cout<<s<<std::endl;//print!
	}else{
		std::cout<<"Can't find file!"<<std::endl;//exception
	}*/
	
	/*2-2. use buffer not string
	std::ifstream in("test.txt");//ready for read file
	char buf[100]; 
	
	if(!in.is_open()){//exception
		std::cout<<"cannot find file!"<<std::endl;
		return 0;
	}
	while(in){
		in.getline(buf,100);//read file before '\n'(default), so it read 100-1 for '\n'.//getline is not safe because of condition for using.
		std::cout<<buf<<std::endl;//print!
	}*/
	
	/*2-3. read by line.
	std::ifstream in ("test.txt");//ready for use
	
	if(!in.is_open()){//exception
		std::cout<<"cannot find file!"<<std::endl;
		return 0;
	}
	
	std::string s;//for efficiency. first exception, last assign.
	while(in){//can read?
		getline(in, s);//getline to string s. get line function is not defined at ifstream, defined at std::string. first argument is istream object, second argument is string object that will be saved input
		//use get line function in std::string is much convenient than getline in ifstream because we don't have to assign buffer's size. it use '\n'or end of file not buffer size. 
		std::cout<<s<<std::endl;//print
	}*/
	
	//3
	/*3-1. normal using guide.
	std::ofstream out ("test.txt", std::ios::app);//ready for write file. W mode! If no file, write file. If exsist file, overwrite file if you don't set special setting.
	//std::ofstream out ("text.txt", std::ios::app); with app option, it will add before exsisting content.
	std::string s;
	if(out.is_open()){//well open?
		out<<"\n plus content!";
	}*/
	
	/*3-2. options
	std::ofstream out("test.txt", std::ios::app);//abc
	std::ofstream out2("test2.txt", std::ios::ate);//abc
	
	out.seekp(3, std::ios::beg);//In app mode, we judge now status of file is empty. so beg+3 is not work because it is empty file.
	out2.seekp(3, std::ios::beg);//In ate mode, stream location designator move 3, but exsisting content is all erased.(ate doesn't save exsisting content!)
	
	out<<"add!";
	out2<<"add!";
	*/
	
	
	//return 0;
//}

/*4
class Human{
	std::string name;
	int age;
	
	public:
		Human(const std::string& name, int age):name(name), age(age){}//Constructor with initializer list
		std::string get_info(){//return type is std::string.
			return "Name :: "+name+" \ Age :: "+"21";//std::to_string(age) function used! but my version is not matched..
		}
		
		friend std::ofstream& operator<<(std::ofstream& o, Human& h);//for std::ofstream operator overloading! 
};

std::ofstream& operator<<(std::ofstream& o, Human& h){
	o<<h.get_info();
	return o;
}

int main(){
	std::ofstream out("test.txt");
	
	Human h("Jimo", 21);
	out<<h<<std::endl;
	
	return 0;
}*/

double to_number(std::string s){
	std::istringstream ss(s);
	double x;
	
	ss>>x;
	return x;
} 

string to_string(double d){
	std::ostringstream ss;//string as output stream!
	ss<<d;//print d to ss that is output stream
	
	return ss.str();//make str!
}

int main(){
	std::istringstream ss("123");//string as input stream!
	int x;
	ss>>x;//like this!
	
	std::cout<<"input data :: "<<x<<std::endl;
	
	std::cout<<"convert:: 1+2="<<to_number("1")+to_number("2")<<std::endl;//thanks to string as input stream, 1 is input and double type x is returned, so it work. 
	
	return 0;
} 


/*
[1. fstream]
1.	���� ��Ʈ���� �⺻���� istream�̳� ostream���� �����ϴ� ����� �� ���⿡ �̸� ��ӹ޾Ƽ� �ۼ��Ǿ�����, ������ ��ӹ��� ���� ifstream�� ofstream�̴�. ���� �̵��� ��� �����ϴ� ���̺귯���� fstream�� ����Ѵ�.
2.	������ cout�� cin�� �� ����, �̹� ǥ�� ����¿� ������ �Ǿ� �ִ� ��Ȳ�̾�����, ������ ��� ��� ���Ͽ� ������� �ؾ������� �����ؾ��ϱ⿡ �̸� ifstream��ü�� �����ڿ� �����ϰ��� �Ѵ� ������ ��θ� �����ϸ� �ȴ�.
3.	C�� �ٸ��� fclose�� �ִ��� ifstream�� �Ҹ��ڿ��� �ڵ������� close�� �ϱ⿡ ���ص� �ȴ�. �ٸ� ���� �ؾ��ϴ� ��찡 �ִµ�, �ѹ� �� ������ �����ϰ� �ٸ� ������ ���� �� in.close()�� �� ���� in.open("other.txt")������ �ҷ��� ����̴�. ��, ���ο� ���Ͽ��� ���� ��ü�� �Է��� �ޱ� ���ؼ��� ���� ���� ��Ʈ������ ������ �����ϰ�, ���ο� ���ϰ� ��������ָ� �ȴ�. 
	���� open�Լ��� �ֱ⿡ ifstream��ü �����ڿ��� ���ϰ�θ� �ٷ� �������� �ʿ�� ����, ���߿� open���� ���ϴ� ������ ��� �ȴ�.
4.	hex�����ͷ� test.txt�� ������ ���캸��, ù �κ��� ��ġ�ϴ� ���� �� �� �ִ�.(3) 
	����� �츮�� ���� CPU�� ��� ��Ʋ �����(���� �ּҰ��� ���� �ڸ�����)������ �Ųٷ� int������ ��ϵ� ���� �� �� �ִ�. 
	������ �ٸ��� ���� ��, binary���� �������� �ɼ��� ���� ����Ϸ��� or ���������� �ȴ�. 
	 ������ ������ ���� �ڵ�ó�� int�� 4����Ʈ char �迭ó�� ����ϴ� ���� ���� ����, �׳� char �迭�� ũ�⸦ �����ؼ� ������ �ȴ�.
	 char x[10];
	 in.read(x, 10);
5.	p.s cout���� ����� std::hex������ ������ std::cout<<std::hex<<x<<std::endl;�� hex�� ����� �η��� 16������ ���� �����͸� ǥ�����ش�.

[2. ���� ��ü �б�]
1.	in.seekg�� C���� fseek�� ���� �Լ���, ���� ��ġ �����ڸ� �̸����� ������ �� �ִ�. �ι�° ���ڴ� ���� �� ��ġ�� �ǹ��ϰ�, ù ��° ���ڴ� �� ��ġ�� ���� �󸶳� ��ŭ ������ �ִ��ĸ� �ǹ��Ѵ�.
	in.seekg(0,std::ios::end)�� ���, ������ ������ 0��ŭ ������, �� ������ ������ �̵��Ѵٴ� ���̴�.
2.	in.tellg�� ���� �������� ������ ��ġ �������� ��ġ�� ��ȯ�Ѵ�. �ռ� ��ġ �����ڸ� ���� ������ �̵����� ���ұ� ������ tellg�Լ��� ������ ũ��(����Ʈ ����)�� ��ȯ�Ѵ�. �� ũ�⸸ŭ string s�� ���Ҵ����ش�. 
3.	getline�Լ��� ���Ͽ��� \n�� ���� �� ���� �ִ�������ũ��-1��ŭ �д´�.(for null char)
	�̶�, ���ϴ� ���ڰ� ���ö� ���� �д� ������ ������ ���� �ִ�.in.getline(buf,100,'.');
4.	ifstream������ �ڱ� �ڽ��� bool�� ĳ���� �� �� �ִ� ĳ���� ������(operator bool())�� �����ε� �Ǿ��־�, while�� ���ǿ� in�� �����ϸ� bool�� ĳ���� �ϴ� ������ �Լ��� ȣ��ȴ�.
	�̶�, in�� true�̷��� ���� �Է��۾��� �������̾�߸� �ϰ�, ���� ��Ʈ���� ���� �÷��װ� �������� �ʾƾ� �Ѵ�.
	 ������, getline�Լ��� ���� ���ڰ� ������ ���� ������ ������ ũ�Ⱑ �� ���� �ȴٸ� failbit�� Ű�� �ǹǷ� ������ ũ�⸦ �ʹ� �۰� ����ٸ� ���������ε����͸� ���� �� ���� �ȴ�. ��� ���� ������ �� Ȯ���ؾ� �Ѵ�.
	�̿� ���� �Ѱ����� �غ��ϱ� ���ؼ� std::string���� getline�Լ��� �����ϰ� �ִ�. 
5.	eof�� ���� ��ġ �����ڰ� ������ ���� ������ ���Ŀ� true�� �����ϱ� ������ while�� �������� ����� in.eof()�� ����ϸ� �ȵȴ�. 
	�ֳ��ϸ� ������ ��(eof)�� �ƴ� �������� ����(�˸��̸� �� ����)���¿����� eof�� true�� ���� �����⿡(������ �� �о����� eof�����̶� ������ �ʾҴٰ� �ϴ�)
	�� ���о��ٰ� �Ǵ��ϰ� �ȴ�. �̶� data�� �ٸ����� �����ع����� �Ǹ�, �������� eof�ۿ� ���⿡ �ƹ��͵� ������� �ʰ� �ȴ�. �� �ش� ���� ������ ��*��*ȭ�� ���� ���� ���·� �����ִٴ� ���̴�!!(�����Ⱚ)
	 ��, in.eof()�� while�� �ȿ��� ���� �б⸦ �����ϰ� �������� ���Ѵ�. ��� in.eof()�� �ƴ� in ��Ʈ�� ��ü ��ü�� �����ϵ��� ����. istream��ü�� �����бⰡ ������ ���� true�� ĳ���õȴ�.

[3. ���Ͽ� ����]
1.	std::ofstream out("test.txt")�� �ɼ����� std::ios::binary�� std::ios::app���� 4���� �� �ִ�.
	-ios::ate �ڵ����� ���� ������ ���� �б�� ���⸦ �ǽ��Ѵ�.(�� ������ �� �� ��ġ �����ڰ� ���� ���� ����Ų��.)
	-ios::trunc ���� ��Ʈ���� ���� ������ �ִ� ������� ��� ��������.(default setting)
	-ios::in, std::ios::out ���Ͽ� �Է��� �� �� ����� �� �� �����ϸ�, ifstream�� ofstream��ü�� ������ �� ������ �̹� �����Ǿ� �ִ�. 
	���⼭ ios::app�� ios::ate�� ���̴� ios::app�� ���, ���� ���Ͽ� ������ �� ���� �� ������ ����ȴ�(���� �����ڰ� ���� ������ ���� ���������� �Ǵ�). �ٸ� ios::ate�� ��� ��ġ �����ڸ� �� �������� �ű� �� �ִ�.(�� �״�� ������ �� �� ��ġ �����ڰ� ���� ���� ����Ű�� ������ ���� ó������ �Ǵ��ϴ� ���� �ƴ�.)

[4.	std::ofstream ������ �����ε� �ϱ�]
1.	std������ �����ε� �ϴ� �� �ͼ��� �ص��� cout<<�̳� cin>> �� ���� �⺻ �Լ��鿡�� ���� ���� Ŭ������ �Լ����� ����� �� �ִ�! 

[5.	���ڿ� ��Ʈ��(std::stringstream)]
1.	<sstream>���� std::istringstream�� ���ǵǾ� �ִµ�, �̴� ���ڿ��� ���� ��Ʈ���̶� �����ϰ� ���ִ� ����ȭ ��ġ�̴�. 
	��, �츮�� ���ڿ� "123"�� ��ϵǾ� �ִ� �Է� ��Ʈ���� �����Ͽ���, �ű⼭ �Է� �޴� �Ͱ� �����ϴٰ� �����ϸ� �Ǳ⿡, ��ġ ���Ͽ��� ���ڸ� �о�� �� ó�� ss>>�� ���� ���� ������ ���̴�. 
2.	�̸� Ȱ���ϸ� atoi���� �Լ� ���� �����ϰ� ���ڿ����� ���ڷ� ��ȯ�ϴ� �Լ��� ���� �� �ִ�. 
3.	���������� �����͸� ����� �� �մ� std::ostringstream�� �ִ�. �̴� �ű��� ���ڿ��� ���ڿ��� �ٲٴ� �Լ��� ������ �� �ִ�. 
*/
