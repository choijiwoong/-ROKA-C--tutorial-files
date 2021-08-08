#include <iostream>
#include <string> 
//므로, 플래그를 초기화해버리지 않는 한 cin 을 이용하여 입력 받을 수 없게 됩니다.
int main(){
	std::string s;//cin can't handle space at one time.
	while (false){
		std::cin>>s;
		std::cout<<"word: "<<s<<std::endl;//input with seperation by space..etc
	}
	
	int t;//type error
	while(false){
		std::cin>>t;
		std::cout<<"입력:: "<<t<<std::endl;//if input is sentence, error.
		if(t==0)
			break;
	}
	
	//int T;
	//while(std::cin>>T){//input at while()
	//	std::cout<<"입력 :: "<<T<<std::endl;//no roof error!! 
	//	if(T==0)
	//		break;
	//}
	
	int y;
  	std::cin >> y;  // 고의적으로 문자를 입력하면 failbit 가 켜진다
  	std::cout << "fail 비트가 켜진 상태이므로, 입력받지 않는다" << std::endl;
  	std::string S;
  	std::cin >> S;
	
	
	
	return 0;
} 

/*
[1.	C++ 입출력 라이브러리]
1.	C++의 모든 입출력 클래스는 ios_base를 기반 클래스로 하게 된다. 이 클래스는 많은 일은 하지 않고, 스트림의 입출력 형식 관련 데이터를 처리한다.ex) 실수형을 출력할 때, 청밀도를 어떻게 할지, 정수형을 출력할지, 10진수로 할지 16진수로 할지 etc..
	 그 다음으로 ios 클래스가 실제로 스트림 버퍼(데이터 임시 저장소)를 초기화 한다. ex)사용자가 1bite씩 읽는다고 했을때 실제로는 한 뭉터기(ex.513bite)를 한번에 읽어 스트림 버퍼에 저장한뒤에 사용자가 요청할 때마다 1bite씩 꺼냄.
	이렇게 스트림버퍼를 사용하는 이유는 하드디스크에서 읽어오는 작업이 매우 느리기에 한번 읽을 때 1bite씩 읽으면 엄청난 딜레이가 발생하기 때문이다. 쓰기도 마찬가지이다.
	ios클래스는 스트림 버퍼 외에도, 현재 입출력 작업의 상태를 처리한다. ex)파일을 읽다가 끝에 도달했는가? eof함수, 현재 입출력을 잘 수행할 수 있는가?good함수.

[2. iostream 클래스]
1.	ios_base와 ios 클래스들이 입출력 작업을 위해 바탕을 깔아주었다면, iostream는 실제로 입력을 수행하는 클래스이다.ex)operator>>는 istream클래스에 정의되어있는 연산자, cin은 istream클래스의 객체 중 하나.
	std::cin>>a;를 할 수 있게끔 모든 기본 타입들에 대한 정의가 operator>>로 되어 있다. 그렇다고 string같이 istream의 멤버 함수로 없는 것을 입력못하는 것은 아니고,
	외부 함수로 연산자 오버로딩을 하여 사용할 수 있다.
	istream& operator>>(istram& in, std::string&s){
		//make
	} 
2.	operator>>의 또다른 특징으로는, 모든 공백문자(띄어쓰기 엔터 탭 등)을 입력시키면 무시해버린다. 고로 cin을 통하여 문장을 입력받는다면, 첫 단어만 입력받고 나머지를 읽을 수 없다. 
	int형 변수에 'c'와 같은 다른 타입을 입력하면 오류가 발생되는데 그 이유에 앞서서, ios 클래스는 스트림의 상태를 관리한다고 앞서서 말했다.
	이때 스트림의 상태를 관리하는 플래스(flag; 비트 1개 같은거)가 4개가 정의되어 있고, 이 4개의 플래그들이 스트림이 현재 어떠한 상태인지에 대하여 정보를 보관한다.
	4개의 클래그는 goodbit, badbit, eofbit, failbit로, 입출력 작업이 가능할 때, 복구 불가한 오류 발생 시, 입력 작업 시 EOF도달시, 복구 가능한 오류 발생시를 나타낸다.
	만약 위의 코드처럼 타입이 달라 문자를 입력할 경우, 그냥 현재 스트림 버퍼에 들어가있는 'c\n'을 제거해버리면 되기에 badbit는 아니고, failbit가 켜지게 된다. 그리고 입력값을 받지 않고 그냥 리턴해버린다.
	여기서의 문제는 그냥 리턴하면서 버퍼에 남아있는 'c\n'이다. 그렇기에 무한반복하며 쓰레기값이 출력되는 것이다. 
3.	std::cin에서 타입오류로 무한루프에 빠질때는 while(std::cin>>t)와 같이 해결할 수 있는데, ios에는 operator void*() const; 함수가 정의되어 있다.
	이는 ios객체를 void*로 변환해 주는데, 이 때, NULL포인터가 아닌 값을 리턴하는 조건이, failbit, badbit가 모드 off일 때이다.(정상수행가능할때)
	근데 's'를 우리가 입력하면 operator>>가 cin의 failbit를 켜게되고, std::cin>>t후 cin이 리턴되는데, 리턴값이 while의 조건식으로 들어가기 때문에 컴파일러는 적절한 타입 변환을 찾게 되고,
	결국, ios객체->void*->bool로 가는 2단 변환을 통해서 while문을 빠져나오게 된다.(NULL은 bool상 false) 
	 물론, 여전히 failbit가 켜져있기에 flag를 초기화 하지 않는 한 cin을 이용하여 입력을 받을 수 없는 건 여전하다. 다만 문제만 해결되었을 뿐.
	  
*/
