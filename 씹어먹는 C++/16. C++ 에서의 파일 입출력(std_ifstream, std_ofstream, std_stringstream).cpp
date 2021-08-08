#include <iostream>
#include <string>
#include <fstream> 

int main(){
	//1
	std::ifstream in("test.txt");//ready for read file.
	std::string s;/*
	
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
	} */
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
1.	  
*/
