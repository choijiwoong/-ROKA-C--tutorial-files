#include <iostream>
#include <string>

//solution of input error
int main(){
	int t;
	while(1){
		//std::cin.setf(std::ios_base::hex, std::ios_base::basefield);//change format of istream to hex. //VALUE!
		std::cin>>std::hex>>t;//manipulator that changes io format by manipulating io stream. FUNCTION! like bool alpha, std::endl
		std::cout<<"input "<<t<<std::endl;//input normally
		if(std::cin.fail()){//if failbit is on
			std::cout<<"type right"<<std::endl;
			std::cin.clear();//clear flags
			std::cin.ignore(100, '\n');//ignore until '\n'
		}
		if(t==1) break;
	}
} 

//streambuf
int main(){
	std::string s;
	std::cin>>s;//hello world! but cin get one word by space or \n. So only hello is inputted to S, and ' world!' stay in input buffer.
	//manipulate streambuf! 
	char peek=std::cin.rdbuf()->snextc();//readbuffer's location pointer move one space(' |world!'), and spy next char without moving(' |world!')
	if(std::cin.fail()) std::cout<<"Failed";
	std::cout<<"first char of second word: "<<peek<<std::endl;
	std::cin>>s;
	std::cout<<"read! : "<<s<<std::endl;
} 

/*
1.	ios_base(스트림 입출력 형식), ios(스트림 버퍼 초기화&입출력 작업 상태), istream&ostream(실제 입출력), ifstream. ofstream, iostream, fstream
2.	cin은 띄어쓰기나 공백문자를 분리해서 입력받는다. 
3.	ios에서 goodbit, badbit, eofbit, failbit을 사용하는데, 예로 cin에 잘못된 값을 켰을 시 failbit만 키고 버퍼를 냅둬 무한 오류에 빠진다. flag를 이용하여 예외조건을 처리할 수 있다. 
4.	std::ios_base를 이용하여 입출력 형식변경이 가능한데, 이는 조작자(manipulator)_함수로도 가능하다.
5.	std::streambuf로 일반적인 문자열을 스트림처럼 사용이 가능하다. 
6.	streambuf클래스는 버퍼의 시작부분_시작포인터와, 읽을 문자_스트림 위치 지정자와, 끝 부분_끝 포인터가 있다. 이때 입력버퍼를 get area, 출력 버퍼를 put area라고 표현한다. 
7.	streambuf의 존재 목적은 다중 바이트 문자들에 대해 사용자가 입출력 처리를 이용하기 용이하게 하는데에 목적이 있다. 
*/
