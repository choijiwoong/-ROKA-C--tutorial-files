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
		std::cout<<"입력 받은 문자열 :: "<<s<<std::endl;//print
	} else{
		std::cout<<"파일을 찾을 수 없습니다!"<<std::endl;
	}
	//2
	in.close();//situation that we have to close ifstream directly. 
	in.open("other.txt");//for use other file with same variable.
	
	if(in.is_open()){
		in>>s;
		std::cout<<"입력 받은 문자열 :: "<<s<<std::endl;
	} else{
		std::cout<<"파일을 찾을 수 없습니다!"<<std::endl;
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
		std::cout<<"파일을 찾을 수 없습니다!"<<std::endl;
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
1.	파일 스트림은 기본적인 istream이나 ostream보다 지원하는 기능이 더 많기에 이를 상속받아서 작성되었으며, 각각을 상속받은 것이 ifstream과 ofstream이다. 또한 이들을 모두 포함하는 라이브러리로 fstream을 사용한다.
2.	기존에 cout나 cin을 할 때는, 이미 표준 입출력에 연동이 되어 있는 상황이었지만, 파일의 경우 어느 파일에 입출력을 해야할지를 지정해야하기에 이를 ifstream객체에 생성자에 연동하고자 한느 파일의 경로를 전달하면 된다.
3.	C와 다르게 fclose가 애당초 ifstream의 소멸자에서 자동적으로 close를 하기에 안해도 된다. 다만 직접 해야하는 경우가 있는데, 한번 연 파일을 종료하고 다른 파일을 담을 때 in.close()를 한 다음 in.open("other.txt")식으로 불러올 경우이다. 즉, 새로운 파일에서 같은 객체가 입력을 받기 위해서는 기존 파일 스트림과의 연결을 종료하고, 새로운 파일과 연결시켜주면 된다. 
	또한 open함수가 있기에 ifstream객체 생성자에서 파일경로를 바로 지정해줄 필요는 없고, 나중에 open으로 원하는 파일을 열어도 된다.
4.	hex에디터로 test.txt의 내용을 살펴보면, 첫 부분이 일치하는 것을 볼 수 있다.(3) 
	참고로 우리가 쓰는 CPU의 경우 리틀 엔디안(높은 주소값에 높은 자리수가)때문에 거꾸로 int변수에 기록된 것을 볼 수 있다. 
	파일을 다르게 받을 때, binary말고도 여러가지 옵션을 같이 사용하려면 or 때려버리면 된다. 
	 하지만 실제로 위의 코드처럼 int를 4바이트 char 배열처럼 사용하는 경우는 거의 없고, 그냥 char 배열에 크기를 지정해서 읽으면 된다.
	 char x[10];
	 in.read(x, 10);
5.	p.s cout에서 사용한 std::hex지난번 강의의 std::cout<<std::hex<<x<<std::endl;의 hex와 비슷한 부류로 16진수로 정수 데이터를 표기해준다.

[2. 파일 전체 읽기]
1.	in.seekg는 C언어에서 fseek과 같은 함수로, 파일 위치 지정자를 이리저리 움직일 수 있다. 두번째 인자는 파일 내 위치를 의미하고, 첫 번째 인자는 그 위치로 부터 얼마나 만큼 떨어져 있느냐를 의미한다.
	in.seekg(0,std::ios::end)의 경우, 파일의 끝에서 0만큼 떨어진, 즉 파일의 끝으로 이동한다는 것이다.
2.	in.tellg는 시작 지점으로 부터의 위치 지정자의 위치를 반환한다. 앞서 위치 지정자를 파일 끝으로 이동시켜 놓았기 때문에 tellg함수는 파일의 크기(바이트 단위)로 반환한다. 그 크기만큼 string s를 재할당해준다. 
3.	getline함수는 파일에서 \n이 나올 때 까지 최대지정한크기-1만큼 읽는다.(for null char)
	이때, 원하는 문자가 나올때 까지 읽는 것으로 설정할 수도 있다.in.getline(buf,100,'.');
4.	ifstream에서는 자기 자신의 bool로 캐스팅 할 수 있는 캐스팅 연산자(operator bool())이 오버로딩 되어있어, while문 조건에 in을 전달하면 bool로 캐스팅 하는 연산자 함수가 호출된다.
	이때, in이 true이려면 다음 입력작업이 성공적이어야만 하고, 현재 스트림에 오류 플래그가 켜져있지 않아야 한다.
	 하지만, getline함수는 개행 문자가 나오기 전에 지정한 버퍼의 크기가 다 차게 된다면 failbit를 키게 되므로 버퍼의 크기를 너무 작게 만든다면 정상적으로데이터를 받을 수 없게 된다. 고로 위의 조건을 잘 확인해야 한다.
	이와 같은 한계점을 극복하기 위해서 std::string에서 getline함수를 제공하고 있다. 
5.	eof는 파일 위치 지시자가 파일의 끝에 도달한 이후에 true를 리턴하기 때문에 while문 조건으로 절대로 in.eof()를 사용하면 안된다. 
	왜냐하면 파일을 끝(eof)이 아닌 직전까지 읽은(알맹이만 다 읽은)상태에서도 eof는 true의 값을 가지기에(실제로 다 읽었지만 eof직전이라 끝나지 않았다고 하는)
	다 안읽었다고 판단하게 된다. 이때 data를 다른곳에 저장해버리게 되면, 남은것은 eof밖에 없기에 아무것도 저장되지 않게 된다. 즉 해당 저장 공간이 초*기*화가 되지 않은 상태로 남아있다는 것이다!!(쓰레기값)
	 즉, in.eof()는 while문 안에서 파일 읽기를 안전하게 보장하지 못한다. 고로 in.eof()가 아닌 in 스트림 객체 자체를 전달하도록 하자. istream객체는 다음읽기가 안전할 때만 true로 캐스팅된다.

[3. 파일에 쓰기]
1.	std::ofstream out("test.txt")의 옵션으로 std::ios::binary와 std::ios::app말고도 4개가 더 있다.
	-ios::ate 자동으로 파일 끝에서 부터 읽기와 쓰기를 실시한다.(즉 파일을 열 때 위치 지정자가 파일 끝을 가리킨다.)
	-ios::trunc 파일 스트림을 열면 기존에 있던 내용들이 모두 지워진다.(default setting)
	-ios::in, std::ios::out 파일에 입력을 할 지 출력을 할 지 지정하며, ifstream과 ofstream객체를 생성할 때 각각은 이미 설정되어 있다. 
	여기서 ios::app과 ios::ate의 차이는 ios::app의 경우, 원본 파일에 접근할 수 없다 즉 내용이 보장된다(파일 지정자가 기존 파일의 끝을 시작점으로 판단). 다만 ios::ate의 경우 위치 지정자를 그 이전으로 옮길 수 있다.(말 그대로 파일을 열 때 위치 지정자가 파일 끝을 가리키는 것이지 끝을 처음으로 판단하는 것이 아님.)

[4.	std::ofstream 연산자 오버로딩 하기]
1.	std연산자 오버로딩 하는 것 익숙히 해두장 cout<<이나 cin>> 과 같은 기본 함수들에서 내가 만든 클래스나 함수들을 사용할 수 있다! 

[5.	문자열 스트림(std::stringstream)]
1.	<sstream>에는 std::istringstream이 정의되어 있는데, 이는 문자열을 한의 스트림이라 생각하게 해주는 가상화 장치이다. 
	즉, 우리는 문자열 "123"이 기록되어 있는 입력 스트림을 생성하였고, 거기서 입력 받는 것과 동일하다고 생각하면 되기에, 마치 파일에서 숫자를 읽어내는 것 처럼 ss>>과 같은 것이 가능한 것이다. 
2.	이를 활용하면 atoi같은 함수 없이 간편하게 문자열에서 숫자로 변환하는 함수를 만들 수 있다. 
3.	마찬가지로 데이터를 출력할 수 잇는 std::ostringstream이 있다. 이는 거구로 숫자에서 문자열로 바꾸는 함수를 제작할 수 있다. 
*/
