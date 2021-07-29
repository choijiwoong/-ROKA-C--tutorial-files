/*1
#include <iostream>

class A{
	private:
		void private_func(){}
		int private_num;
		
		friend class B;//B는 A의 친구 
		friend void func();//func()는 A의 친구 
}; 

class B{
	public:
		void b(){
			A a;
			//private 함수의 fields지만, 친구이기 때문에 접근이 가능하다. 
			a.private_func();
			a.private_num=2;
		}
};

void func(){
	A a;
	//private 함수의 fields지만, 친구이기 때문에 접근이 가능하다. 
	a.private_func();
	a.private_num=3;
}

int main(){
	return 0;
} */

/*2,3
#include <iostream>
#include <cstring>

class Complex {
 private:
  double real, img;
  double get_number(const char* str, int from, int to) const;

 public:
  Complex(double real, double img) : real(real), img(img) {}
  Complex(const Complex& c) { real = c.real, img = c.img; }
  Complex(const char* str);

  //Complex operator+(const Complex& c) const; //자기 자신을 리턴하지 않으니 외부함수로(아래 friend) 
  Complex& operator=(const Complex& c);

  // 나머지 연산자 함수들은 생략 :)

  void println() {
    std::cout << "( " << real << " , " << img << " ) " << std::endl;
  }
  
  friend std::ostream& operator<<(std::ostream& os, const Complex& c); 
  // 이제 이 함수는 Complex 의 private 멤버 변수들에 접근할 수 있습니다.
  friend Complex operator+(const Complex& a, const Complex& b);
};

std::ostream& operator<<(std::ostream& os, const Complex& c){
	os<<"( "<<c.real<<" , "<<c.img<<" ) ";
	return os;
}
Complex operator+(const Complex& a, const Complex& b) {
  Complex temp(a.real + b.real, a.img + b.img);//a와 b의 private멤버변수에 접근 가능. 
  return temp;
}

Complex::Complex(const char* str) {
  int begin = 0, end = strlen(str);
  img = 0.0;
  real = 0.0;

  int pos_i = -1;
  for (int i = 0; i != end; i++) {
    if (str[i] == 'i') {
      pos_i = i;
      break;
    }
  }

  if (pos_i == -1) {
    real = get_number(str, begin, end - 1);
    return;
  }

  real = get_number(str, begin, pos_i - 1);
  img = get_number(str, pos_i + 1, end - 1);

  if (pos_i >= 1 && str[pos_i - 1] == '-') img *= -1.0;
}
double Complex::get_number(const char* str, int from, int to) const {
  bool minus = false;
  if (from > to) return 0;

  if (str[from] == '-') minus = true;
  if (str[from] == '-' || str[from] == '+') from++;

  double num = 0.0;
  double decimal = 1.0;

  bool integer_part = true;
  for (int i = from; i <= to; i++) {
    if (isdigit(str[i]) && integer_part) {
      num *= 10.0;
      num += (str[i] - '0');
    } else if (str[i] == '.')
      integer_part = false;
    else if (isdigit(str[i]) && !integer_part) {
      decimal /= 10.0;
      num += ((str[i] - '0') * decimal);
    } else
      break;
  }

  if (minus) num *= -1.0;

  return num;
}

Complex& Complex::operator=(const Complex& c) {
  real = c.real;
  img = c.img;
  return *this;
}

int main() {
  Complex a(0, 0);
  a = "-1.1 + i3.923" + a;
  std::cout << "a 의 값은 : " << a << " 이다. " << std::endl;//a 를 그냥 cout로 해도 출력이 되도록. 
}*/

/*4
#include <iostream>
#include <cstring>

class MyString {
  char* string_content;  // 문자열 데이터를 가리키는 포인터
  int string_length;     // 문자열 길이

  int memory_capacity;  // 현재 할당된 용량

 public:
  // 문자 하나로 생성
  MyString(char c);

  // 문자열로 부터 생성
  MyString(const char* str);

  // 복사 생성자
  MyString(const MyString& str);

  ~MyString();

  int length();

  void print() const;
  void println() const;

  char& operator[](const int index);//첨자 연산자 operator. 인수는 인덱스 숫자 int, return type은 'c'처럼 리턴하기에. 
};//so structure is simple because we only have to return string_content[index];

MyString::MyString(char c) {
  string_content = new char[1];
  string_content[0] = c;
  memory_capacity = 1;
  string_length = 1;
}
MyString::MyString(const char* str) {
  string_length = strlen(str);
  memory_capacity = string_length;
  string_content = new char[string_length];

  for (int i = 0; i != string_length; i++) string_content[i] = str[i];
}
MyString::MyString(const MyString& str) {
  string_length = str.string_length;
  string_content = new char[string_length];

  for (int i = 0; i != string_length; i++)
    string_content[i] = str.string_content[i];
}
MyString::~MyString() { delete[] string_content; }
int MyString::length() { return string_length; }
void MyString::print() const {
  for (int i = 0; i != string_length; i++) {
    std::cout << string_content[i];
  }
}
void MyString::println() const {
  for (int i = 0; i != string_length; i++) {
    std::cout << string_content[i];
  }
  std::cout << std::endl;
}

char& MyString::operator[](const int index) { return string_content[index]; }//return char as reference.

int main() {
  MyString str("abcdef");
  str[3] = 'c';

  str.println();
}*/

/*5
#include <iostream>

class Int{
	int data;//some other data
	
	public:
		Int(int data): data(data) {}//constructor with initializer list(Int x=3)
		Int(const Int& i): data(i.data) {}//constructor overloading for using like real int type.(int a= x+4)

	operator int() { return data; }//this class can be int() type. when has type int(), it return data value.
};	//no return type. for distinguish 'type conversion operator' and 'normal function'.

int main() {
  Int x = 3;//thanks to default assignment operator
  int a = x + 4;//int() for operate and assignment

  x = a * 2 + x + 4;
  std::cout << x << std::endl;
}*/

#include <iostream>

class Test {
  int x;

 public:
  Test(int x) : x(x) {}
  Test(const Test& t) : x(t.x) {}

  Test& operator++() {
    x++;
    std::cout << "전위 증감 연산자" << std::endl;
    return *this;
  }

  // 전위 증감과 후위 증감에 차이를 두기 위해 후위 증감의 경우 인자로 int 를
  // 받지만 실제로는 아무것도 전달되지 않는다.
  Test operator++(int) {
    Test temp(*this);
    x++;
    std::cout << "후위 증감 연산자" << std::endl;
    return temp;
  }

  int get_x() const {
    return x;
  }
};

void func(const Test& t) {
  std::cout << "x : " << t.get_x() << std::endl;
}

int main() {
  Test t(3);

  func(++t); // 4
  func(t++); // 4 가 출력됨
  std::cout << "x : " << t.get_x() << std::endl;
}

/*
[1. friend 키워드]
1.	friend라고 선언하게 되면, 모든 private멤버 함수들과 멤버 변수들에 대한 접근 권한을 부여하게 된다.
	다만, 짝사랑이라 역으로 접근은 불가하고 일방적이다. 
class A {
 	private:
  	int x;

  	friend class B;
};

class B {
 	private:
  	int y;
};
의 경우, A는 B의 private변수인 y에 접근이 불가하다. 오직 친구로 선언된 함수에서 접근이 가능할뿐.

[2. 이항 연산자] 
1.	앞서 연산자오버로딩 시 a = a + "-1.1 + i3.923";  // ①는 되지만,  a = "-1.1 + i3.923" + a;  // ②는 안된다는 문제가 있었다.
	컴파일러는 *a.operator@(b); *operator@(a, b);(여기서 @는 임의의 연산자) 중 가능한 녀석으로 처리하는데,
	선자는 a클래스의 멤버함수로, 후자는 일반적인 함수를 의미한다. 고로 Complex operator+(const Complex& a, const Complex& b) {}
	꼴로 하면 된다. 고로  "-1.1 + i3.923" + a;는, 오버로딩 함수로 인해 operator+(Complex("-1.1 + i3.923"), a);로 해석되어 잘 실행된다.
	 여기서 중요한 점은, operator+함수가 제대로 작동하려면 a와 b의 real, img에 접근해야하는데 이는 private멤버이다. 고로 friend를 사용한다. 
2.	1과 같은 방법을 취한다면 위의 문제상황에서의 문제를 해결할 수 있다. 다만 추가적인 문제가 생기는데,
	a=a+a;와 같은 명령어에서는 1의 *a.operator@(b); *operator@(a, b); 둘 다 가능하기 때문에 어떤것을
	사용해야하는지 모르겠다는 모호경고를 발생시킨다. 고로 둘 중 하나의 함수를 없애야 한다.
3.	(중요)
	통상적으로 자기 자신을 리턴하지 않는 이항 연산자들(+, -, *, /)은 외부함수로 선언하는 것이 원칙이며,
	반대로 자기 자신을 리턴하는 이항 연산자들(+=, -=)은 모두 멤버함수로 선언하는 것이 원칙이다.  

[3. 입출력 연산자 오버로딩 하기]
1.	std::cout<<a;라는 경우 역시 std::cout이라는 객체에 맴버변수 operator<<가 정의되어 있어 a를 호출하는 것이다.
	다만 int, double, 문자열 모두 출력이 되는 것은 그 많은 수의 operator<<함수들이 오버로딩 되어있다는 뜻이다.
	(p.s 이는 ostream에 정의되어 있다. +iostream이 ostream을 include함.)
이들 덕분에 우리가 편하게 인자의 타입에 관계없이 손쉽게 출력을 사용할 수 있게 되는 것이지요.
부터 기릿_장전 존나 하나보니 손이 아프네. 
***2뭔소리고 
2.	만약 Complex클래스에서 ostream클래스의 연산자 operator<<를 사용할 수 있다면? Complex c; std::cout<<c; ->Complex c; c.println();
	당연히, ostream클래스에 operator<<맴버 함수를 추가하는 것을 표준 헤더파일의 내용을 수정해야하기에 불가능하다. 대신
	ostream클래스에 Complex객체를 오버로딩하는 operator<<연산자 함수를 추가할 수 있다. 즉 ostream객체와 Complex객체 두개를 인자로 받는 전역 operator<<함수를 정의하면 된다.

[4. 첨자 연산자 operator[]] (배열의 원소를 지정할 때 []안에 넣는 수를 첨자(subscript)라고 부름) 
1.	MyString클래스에서 []를 이용하여 str[10]과 같이 10번째 문자에 정확하게 접근할 수 있게 해보자. 

캬 지루해질 때 쯤 또 다시 재미가 붙는 고만
[5. int Wrapper 클래스-타입 변환 연산자]_Wrap: 감싸다, 포장하다_무언가를 포장하는 클래스. 
1.	Int를 실제 int와 같이 만드려면 모든 연산자 함수들을 만들어 주면 되지만, 일일히 오버로딩하기에는 많은 숫자이다.
	하지만, 단순히 int형 변수끼리 하는일과 정확히 똑같기 때문에 굳이 이미 제공하는 기능을 다시 만들ㅇ 필요는 없다.
	이때, 타입 변환 연산자를 사용하여 Wrapper클래스의 객체를 마지 'int형 변수'로 컴파일러가 생각할 수 있게 만든다.
	즉 클래스의 객체를 int형 변수로 변환하여 +등의 연산을 수행하게 하는 것이다. 
2.	operator (변환하고자하는타입) () 이때, c++에서 변환 연산자를 정의하기 위하여 함수의 리턴타입은 적지 않는다. 
	 즉 Wrapper의 클래스를 적절한 변환 연산자로 operator int를 찾아 int로 변환하여 처리한 후 대입(return data) 시
	default 대입 연산자가 알아서 처리하게 한다. 
	
[6.	전위/후의 증감 연산자]
1.	연산자 오버로딩 할 때 a++과 ++a는 같이 operator++인데 이를 어떻게 구분하나? 
	 아예 따로 구분을 시켜버림. operator++()_++x, operator--();_--x.(전위 증감 연산자), operator++(int x)_x++, operator--(int x)_x--(후위 증감 연산자)
	여기서 int는 아무 의미가 없고 단순히 전위와 후위를 구분하기 위해 사용한다.(p.s ++하며 인자로 들어가는 값을 사용하는 경우는 없기에operator++(int)로 해도 무방.) 
2.	여기서 주의할 점은 전위증감연산의 경우, 값이 바뀐 자신을 리턴해야 하고, 후의 증감의 경우 값이 바뀌기 이전의 객체를 리턴해야 한다.
	전위연산자
	A& operator++(){
		//A++
		return *this;
	}
	후위연산자.
	A operator++(int){/실제로 전달되는 인수는 없음) 
		A temp(A);//for 이전 상태 기록. 
		//A++
		return temp;//because of 리턴한 다음 ++이 실행되기 때문에 ++이 실행될 수 있게 클래스를 온전히 리턴한다. temp++;가능케. 
	} 
3.	따라서 후위 증감 연산의 경우 추가적으로 복사생성자를 호출하기 때문에 전위 증감 연산보다 더 느리다!

[7. 쓰니의 정리하기]
1.	두 개의 동등한 객체 사이에서의 이항 연산자는 멤버 함수가 아닌 외부 함수로 오버로딩 하는 것이 좋습니다.(ex. Complex의 operator+(const complex&, const Complex&) const
2.	주 개의 객체 사이의 이항 연산자 이지만 한 객체만 값이 바뀐다던지 동등하지 않는 이항 연산자는 멤버 함수로 오버로딩 하는 것이 좋습니다.(ex. operator+=는 operator+=(const Complex&)가 낫다.
3.	단항 연산자는 멤버 함수로 오버로딩 하는 것이 좋습니다(ex. operator++)
4.	일부 연산자들은 반드시 멤버 함수로만 오버로딩 해야 합니다. ([](첨자), ->(멤버 접근), =(대입 연산자), ()함수호출연산자) 

[8. 생각해보기]
1.	N차원 배열을 제공하는 클래스를 만들어보자. 
*/
