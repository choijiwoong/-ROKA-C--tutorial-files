#include <iostream>
#include <string> 

/*1,2
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
	
	//int y;
  	//std::cin >> y;  //if we type char deliberately, then failbit will be turned on.
  	//std::cout << "fail 비트가 켜진 상태이므로, 입력받지 않는다" << std::endl;
  	//std::string S;
  	//std::cin >> S;//no input. return.
	
	int T;//solution
	while(true){
		std::cin>>T;
		std::cout<<"입력 :: "<<T<<std::endl;
		if(std::cin.fail()){//if fail function(not fail flag!!) is on(fail func is defined at ios class that will return when failbit is true or badbit is true)
			std::cout<<"제대로 입력해주세요"<<std::endl;
			std::cin.clear();//initialization of flags(clear function is defined in ios class too, if no argument, it initialize flag to goodbit. it means deleting of fail status)
			std::cin.ignore(100,'\n');//ignore before \n(ignore function is defined at istream class. buffer ignore until read '\n' in maximum 100 length.
		}//so if we input char that has length over 100, ignore function will be called until deleting buffer's char.
		if(T==1)
			break;
	}
	
	return 0;
}*/

/*3
int main(){	
	int t;
	while(false){//basefield saves what notation we use. so initialization of basefield by locate 2nd argument. and set hex.
		std::cin.setf(std::ios_base::hex, std::ios_base::basefield);//setf function can change setting of stream by argument's <format flag>.
		std::cin>>t;//ex) 0xFF
		std::cout<<"입력 :: "<<t<<std::endl;//ex) 255
		if(std::cin.fail()){
			std::cout<<"제대로 입력해주세요"<<std::endl;
			std::cin.clear();
		}
		if(t==0) 
			break;
	}
	while(true){//other way
		std::cin>>std::hex>>t;//hex change the way of getting num at cin. it calls <Manipulator>(hex is function but this std::hex is different of std::ios_base::hex explicitly.)
		std::cout<<"입력 :: "<<t<<std::endl;
		if(std::cin.fail()){
			std::cout<<"제대로 입력해주세요"<<std::endl;
			std::cin.clear();
			std::cin.ignore(100,'\n');
		}
		if(t==0)
			break;
	}
	
	return 0;
}*/

int main(){
	std::string s;
	std::cin>>s;//content: hello world\n
	
	//move once placeholder, and peek next char.(not move) status of stram location holder after cin>>s is hello^world\n. Then, snextc() make stream location holder move once and return w. then!!! no touch stream location holder, reread, print world\n not orld\n!
	char peek=std::cin.rdbuf()->snextc();//cin.rdbuf() return pointer that point stremabuf object that cin object work. then, cin object is istream object, so streambuf object only has get area.
	if(std::cin.fail()) std::cout<<"Failed";
	std::cout<<"두 번째 단어 맨 앞 글자: "<<peek<<std::endl;
	std::cin>>s;
	std::cout<<"다시 읽으면 : "<<s<<std::endl;
	
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

[3.	형식 플래그(format 'flag')와 조작자(Manipulator)]
1.	ios_base 클래스에서, 스트임의 입출력 형식을 바꿀 수 있다고 했다. 입력 시 지금까지는 10진수로 처리되었지만, 16진수로 처리할 수도 있게 할 수 있다. 
2.	setf function's version has two. 하나는 인자 1개만 받아 인자로 준 형식 플래그를 적용하는 것이고, 인자를 2개 취하는 것은 두 번째 인자(위에선 basefield)의 내용을 초기화 하고, 첫 번째 인자(hex)를 적용하는 방식이다.
3.	물론, 16진법을 처리하는 함수를 그냥 만들어도 된다. 문자열로 입력받아 처리해도 되지만, 0x를 문자열 앞에 붙일지 안붙일지(16진수에오나타냄), a123일지 A123일지 여러 경우가 있기에
	그냥 IO라이브러리에서 지원하는 방식을 사용하는 것이 좋다.
	 첫 번째로 std::cin::setf(format flag, initialization)방식으로 format flag 형식 플래그를 사용하여 설정하거나, std::cin>>std::hex>>t;와 같이 Manipulator 조작자를 사용하여 설정할 수 있다.
	이때 std::hex는 function이고, format flag's hex는 단지 상수 '값'으로, 이름만 같을 뿐 다른 것이다.(std::ios_base::hex) 
	 형식 플래그 hex that is manipulator는 ios_base object를 reference로 받고, 다시 그 객체를 리턴하게 정의되어 있다.
	std::ios_base& hex(std::ios_base& str); 
	그렇다면 역시 operator>>중 위 함술르 인자로 가지는 경우도 있다.
	istream& operator>>(ios_base& (*pf)(ios_base&));
	그냥 operator>>에서 조작자를 받는다면 단순히 pf(*this)를 호출하는 것이다. 그리고 호출된 hex함수가 단순히
	str.setf(std::ios_base::hex, std::ios_base::basefield)를 수행하게 된다. 
	 즉, setf를 직접 사용하지 않고도, manipulator를 사용하여 간단하게 입력 형식을 바꿀 수 있다. 또한 조작자의 종류 또한 hex말고도 다양한데, true와 false를 1과 0이 아닌 문자열로 처리하는 boolalpha도 있고,
	출력 형식으로 왼쪽 혹은 오른쪽으로 정렬 시키는 left와 right조작자 등 여러가지가 있다.(std::endl도 조작자의 하나인데, 출력을 관장하는 ostream에 정의되어있는 조작자로, 한줄 개행문자를 출력하는 것 말고도, 사실 버퍼를 모두 내보내는(flush)역활도 수행한다!
	이러한 flush역활은 일반적으로 버퍼를 이용하여 어느정도 문자가 쌓인다음 내보내는 방식과 다르게 정해진 시간엥 딱딱 맞춰서 화면에 출력해야해서 바로바로 내보내야하는 경우에 사용된다.
	flush는 버퍼에 데이터가 얼마나 쌓여있든지 간에 바로 출력을 해주는 함수이다. 따라서 다시 본론으로 돌아가자면 std::endl 조작자는 스트림에 '\n'을 출력하는 것과 더불어 flush를 수행해준다.

[4.	스트림 버퍼에 대해] 
1.	모든 입출력 객체들은 이에 대응되는 스트림 객체를 가진다. 즉 C++의 입출력 라이브러리에 대응되는 스트림 버퍼 클래스인 streambuf클래스(말 그대로 문자들이 순차적으로 쭈르륵 들어오는 것)가 존재한다. 
	이는 우리가 화면에 입력하는 문자도 모두 스트림을 통하여 프로그램에 전달된다는 것이고, 하드디스크에서 파일을 읽느 것, 다른컴퓨터와 TCP/IP통신역시 모두 스트림을 통해 이루어진다는 것을 의미한다.
	또한 C++에서는 std::stringstream을 통하여 평범한 문자열을 마치 스트림인것 처럼 사용할 수 있게도 해준다.
	 여튼 다시 본론으로, streambuf는 스트림에 대한 가장 기본적인 제어를 담당한다. 
	streambuf클래스는 스트림의 상태를 나타내기 위해서 세 개의 포인터를 정의하고 있는데, 버퍼의 시작 부분을 가리키는 시작 포인터, 다음으로 읽을 문자를 가리키고 있는 포인터(스트림 위치 지정자), 버퍼의 끝을 가리키는 끝 포인터가 있다.
	또한 streamvuf클래스는 입력 버퍼와 출력 버퍼를 구분하기 위해 get area와 put area로 구분하여 부르는데, 이에 따라 각각을 가리키는 포인터도 g와 p를 붙여서 표현하게 된다. 
2.	of coursely, streambuf는 snextc함수 말고도 다양한 함수들이 정의되어 있다. 다 기억할 필요는 없지만, 단지 C++ 입출력 라이브러리는 스트림 버퍼마저도 추상화하여 클래스로 만들었다는 것은 알고 있으면 좋다.
	또한, C++에서 streambuf를 도입한 이유는 1bite문자 뿐이 아니라 wchar_t, 즉 다중 바이트 문자들(ex. UTF-8)에 대한 처리도 용이하게 하기 위함이다.
	즉, 다중 바이트 문자의 경우, 사용자가 문자 한 개를 요구해도 스크림에서틑 1바이트만 읽을 수 있게되지만 2바이트, 심지어 4바이트까지 필요한 경우가 있다. 그리하여 이러한 것들을 
	스트림 버퍼 객체 자체에서 수행하도록 하여 사용자가 입출력 처리를 이용하는데 유용하게 하였다. 
*/
