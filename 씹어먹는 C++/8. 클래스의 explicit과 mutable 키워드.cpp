//explicit_암시적 변환 비활성화. 사용금지령 이건 암시적 변환 때 사용하지 마! 
/*#include <iostream>

class MyString {
  char* string_content;  // 문자열 데이터를 가리키는 포인터
  int string_length;     // 문자열 길이

  int memory_capacity;

 public:
  // capacity 만큼 미리 할당함.
  explicit MyString(int capacity);//암시적 변환 비활성화!!!! 

  // 문자열로 부터 생성
  MyString(const char* str);

  // 복사 생성자
  MyString(const MyString& str);

  ~MyString();

  int length() const;
};

MyString::MyString(int capacity) {//미리 크기를 할당받는 새로운 생성자 추가. 
  string_content = new char[capacity];
  string_length = 0;
  memory_capacity = capacity;
  std::cout << "Capacity : " << capacity << std::endl;
}

MyString::MyString(const char* str) {
  string_length = 0;
  while (str[string_length++]) {
  }

  string_content = new char[string_length];
  memory_capacity = string_length;

  for (int i = 0; i != string_length; i++) string_content[i] = str[i];
}
MyString::MyString(const MyString& str) {
  string_length = str.string_length;
  string_content = new char[string_length];

  for (int i = 0; i != string_length; i++)
    string_content[i] = str.string_content[i];
}
MyString::~MyString() { delete[] string_content; }
int MyString::length() const { return string_length; }

void DoSomethingWithString(MyString s) {
  // Do something...
}

int main() {
  DoSomethingWithString(3);  // ????
  
  MyString s = "abc";  // MyString s("abc") well work 
  MyString s3 = 5;      // MyString s(5) occur error
  //대입시 복사생성자가 호출되는데, 이같은 경우에도 알아서 적당한 생성자를 컴파일러가 골라주는데, explicit이 있기에 오류가 발생. 
}*/

/*
[1. explicit]_명시적 
1.	void DoSomethingWithString(MyString s) { Do something... } 위처럼 MyString을 인자로 받는 함수에서
	DoSomethingWithString("abc") 이처럼 명시적으로ex. MyString("abc")표현하지 않은 경우에도 
	C++컴파일러는 "abc"를 어떻게 MyString으로 바꿀 수 있는지를 생각합니다. 다행히, 생성자중에
	MyString(const char* str);이 있기에 알아서 DoSomethingWithString(MyString("abc"))로 변환되어 컴파일된다.
	이와 같은 변환을 암시적 변환(implicit conversion)이라고 부릅니다.
	 하지만  DoSomethingWithString(3)이러한 실수를 했을 경우엔, MyString(int capacity);때문에 위 함수는
	암시적 변환을 통해  DoSomethingWithString(MyString(3))으로 의도치않게 변환되어 컴파일된다. 
	 이러한 의도하지 않은 암시적 변환을 방지하기 위해 암시적 변환을 할 수 없게 만드는 것이 explicit키워드이다.

[2. mutable]_변이 가능한 
1.	const 함수 내부에서는 멤버 변수들의 값을 바꾸는 것이 불가능했지만, 멤버 변수를 mutable로 선언한다면
	const함수 내에서도 이들의 값을 바꿀 수 있다. 
2.	mutable을 쓸바에 차라리 const()를 떼버리면 되지 않느냐?
	const 함수의 의미는 '이 함수는 객체 내부의 상태에 영향을 주지 않습니다.' ex) 읽기작업 수행 함수.
	class Server {
  	// .... (생략) ....

 	 // 이 함수는 데이터베이스에서 user_id 에 해당하는 유저 정보를 읽어서 반환한다.
  	User GetUserInfo(const int user_id) const {
  	  // 1. 데이터베이스에 user_id 를 검색
  	  Data user_data = Database.find(user_id);
	
  	  // 2. 리턴된 정보로 User 객체 생성
  	  return User(user_data);
 	 }
	}; 
	위 서버는 그냥 DB에서 유저를 조회해서, 그 유저의 정보를 리턴하는 함수이다. 당연히 업데이트나 수정작업이
	없기 때문에 const함수로 선언되어 있다.
	 하지만 대게 한번 요청된 정보는 계속해서 요청될 확률이 높기에 캐쉬에 저장되고, 캐쉬 크기는 한정적이기에
	오래된 캐쉬부터 지우게 된다.
	 class Server {
 	 // .... (생략) ....

 	 mutable Cache cache; // 캐쉬! Mutable!!!!!!!

 	 // 이 함수는 데이터베이스에서 user_id 에 해당하는 유저 정보를 읽어서 반환한다.
  	User GetUserInfo(const int user_id) const {
  	  // 1. 캐쉬에서 user_id 를 검색
  	  Data user_data = cache.find(user_id);

 	   // 2. 하지만 캐쉬에 데이터가 없다면 데이터베이스에 요청
 	   if (!user_data) {
  	    user_data = Database.find(user_id);

  	    // 그 후 캐쉬에 user_data 등록
  	    cache.update(user_id, user_data); // <-- 불가능
  	  }

   	 // 3. 리턴된 정보로 User 객체 생성
  	  return User(user_data);
 	 }
	};
	근데 GetUserInfo가 const함수라는 점이 문제로 발생한다.
	cache로 update하는 과정에서,  cache의 내부 data를 바꿔야 하기에 수행할 수 없다.
	또한 당연히 update함수는 const함수가 아닐 것이다.
	 여기서 딜레마가 발생하는데, 그렇다고 GetUserInfo함수의 const를 떼자니 이건 사용자 입장에서
	당연히 const로 정의되어야 하는 함수이기 때문이다. 그래서 이러한 경우, Cache를 mutable로 선언해버리면
	딜레마가 해결된다. 
*/
//mutable
#include <iostream>

class A {
  //int data_;
  mutable int data_;

 public:
  A(int data) : data_(data) {}
  void DoSomething(int x) const {
    data_ = x;  // 불가능!
  }

  void PrintData() const { std::cout << "data: " << data_ << std::endl; }
};

int main() {
  A a(10);
  a.DoSomething(3);
  a.PrintData();
}
