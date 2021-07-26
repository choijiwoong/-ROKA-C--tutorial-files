/*
#include <string.h>
#include <iostream>

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

  int compare(MyString& str);
  bool operator==(MyString& str);
};

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
int MyString::compare(MyString& str) {
  // (*this) - (str) 을 수행해서 그 1, 0, -1 로 그 결과를 리턴한다
  // 1 은 (*this) 가 사전식으로 더 뒤에 온다는 의미. 0 은 두 문자열
  // 이 같다는 의미, -1 은 (*this) 사 사전식으러 더 앞에 온다는 의미이다.

  for (int i = 0; i < std::min(string_length, str.string_length); i++) {
    if (string_content[i] > str.string_content[i])
      return 1;

    else if (string_content[i] < str.string_content[i])
      return -1;
  }

  // 여기 까지 했는데 끝나지 않았다면 앞 부분 까지 모두 똑같은 것이 된다.
  // 만일 문자열 길이가 같다면 두 문자열은 아예 같은 문자열이 된다.

  if (string_length == str.string_length) return 0;

  // 참고로 abc 와 abcd 의 크기 비교는 abcd 가 더 뒤에 오게 된다.
  else if (string_length > str.string_length)
    return 1;

  return -1;
}
bool MyString::operator==(MyString& str) {
  return !compare(str);  // str 과 같으면 compare 에서 0 을 리턴한다._compare의 경우 같으면 0을 리턴하기 때문. 
}
int main() {
  MyString str1("a word");
  MyString str2("sentence");
  MyString str3("sentence");

  if (str1 == str2)
    std::cout << "str1 와 str2 같다." << std::endl;
  else
    std::cout << "st1 와 str2 는 다르다." << std::endl;

  if (str2 == str3)
    std::cout << "str2 와 str3 는 같다." << std::endl;
  else
    std::cout << "st2 와 str3 는 다르다" << std::endl;
}*/
#include <string.h>
#include <iostream>

class Complex{
	double real, img;
	double get_number(const char *str, int from, int to) const;//stdlib.h의 atof함수로 대체 가능. 
	
	public:
		Complex(double real, double img): real(real), img(img){}
		Complex(const Complex& c) { real=c.real; img=c.img; }
		Complex(const char* str);
		
		//Complex plus(const Complex& c);
		Complex operator+(const Complex& c) const;
		//Complex minus(const Complex& c);
		Complex operator-(const Complex& c) const;
		//Complex times(const Complex& c);
		Complex operator*(const Complex& c) const;
		//Complex divide(const Complex& c);
		Complex operator/(const Complex& c) const;
		
		//return reference in = operate
		Complex& operator=(const Complex& c); 
		
		//make by using existing function
		Complex& operator+=(const Complex& c);
		Complex& operator-=(const Complex& c);
		Complex& operator*=(const Complex& c);
		Complex& operator/=(const Complex& c);
		
		//develop to use "2+i4"
		Complex operator+(const char* str) const; 
		Complex operator-(const char* str) const;
  		Complex operator*(const char* str) const;
  		Complex operator/(const char* str) const;
		
		void println() { std::cout<<" ( "<<real<<" , "<<img<<" ) "<<std::endl; }
};
Complex Complex::operator+(const Complex& c) const{
	Complex temp(real+c.real, img+c.img);//또한 연산을 진행하고 피연산자의 값이 바뀌면 안되니 그냥 Complex객체를 새로 만들어 리턴. 
	return temp;//if 여기서 temp의 참조자를 리턴해버리면 함수 종료와 동시에 사라짐. 
}
Complex Complex::operator-(const Complex& c) const{
	Complex temp(real-c.real, img-c.img);
	return temp;
}
Complex Complex::operator*(const Complex& c) const{
	Complex temp(real*c.real-img*c.img, real*c.img+ img*c.real);
	return temp;
}
Complex Complex::operator/(const Complex& c) const{
	Complex temp(
		(real*c.real+img*c.img)/(c.real*c.real+c.img*c.img),
		(img*c.real-real*c.img)/(c.real*c.real+c.img*c.img)
	);
	return temp;
}
Complex& Complex::operator=(const Complex& c){
	real=c.real;
	img=c.img;
	return *this;
}
Complex& Complex::operator+=(const Complex& c){
	(*this)=(*this)+c;
	return *this;
}
Complex& Complex::operator-=(const Complex& c){
	(*this)=(*this)-c;
	return *this;
}
Complex& Complex::operator*=(const Complex& c){
	(*this)=(*this)*c;
	return *this;
}
Complex& Complex::operator/=(const Complex& c){
	(*this)=(*this)/c;
	return *this;
}

Complex Complex::operator+(const char* str) const{//이건 너무 복잡하니 그냥 str을 complex로 만드는 생성자를 추가하고 연산자 오버로딩시키자. 
	//find real part and img part. "부호 실수부 부호 i 허수부" 맨앞 부호 생략시 +가정.
	int begin=0, end=strlen(str);
	double str_img=0.0, str_real=0.0;
	
	//find i for set standard
	int pos_i=-1;
	for(int i=0; i!=end; i++){
		if(str[i]=='i'){
			pos_i=i;
			break;
		}
	}
	//if no i, then this num is only real num
	if(pos_i==-1){
		str_real=get_number(str, begin, end-1);
		
		Complex temp(str_real, str_img);
		return (*this)+temp;
	}
	//if yes i
	str_real=get_number(str,begin,pos_i-1);
	str_img=get_number(str,pos_i+1,end-1);
	
	if(pos_i>=1&&str[pos_i-1]=='-') str_img*=-1.0;//is 허수부 -면 * -
	//실수부 - 구분? 
	
	Complex temp(str_real, str_img);
	return (*this) +temp; 
}
double Complex::get_number(const char *str, int from, int to) const{
	bool minus=false;
	if(from>to) return 0;//exception
	if(str[from]=='-') minus=true;//-면 true 
	if(str[from]=='-'||str[from]=='+') from++;//위에서 +도 구분 가능하게 햇으니 ++
	
	double num=0.0;
	double decimal=1.0;
	
	bool integer_part=true;
	for(int i=from;i<=to;i++){
		if(isdigit(str[i])&&integer_part){
			num*=10.0;
			num+=(str[i]-'0');//char이 int나 double로 변환되면 ASCII코드로 변환되는데 문자'0'의 ASCII를 뺴면 본인의 숫자가 나옴. 
		} else if(str[i]=='.') integer_part=false;
		else if(isdigit(str[i])&&!integer_part){
			decimal/=10.0;
			num+=((str[i]-'0')*decimal);
		} else break;//그 외 이상한 문자. 
	} 
	if(minus) num*=-1.0;
	return num;
}
Complex::Complex(const char* str) {
  // 입력 받은 문자열을 분석하여 real 부분과 img 부분을 찾아야 한다.
  // 문자열의 꼴은 다음과 같습니다 "[부호](실수부)(부호)i(허수부)"
  // 이 때 맨 앞의 부호는 생략 가능합니다. (생략시 + 라 가정)

  int begin = 0, end = strlen(str);
  img = 0.0;
  real = 0.0;

  // 먼저 가장 기준이 되는 'i' 의 위치를 찾는다.
  int pos_i = -1;
  for (int i = 0; i != end; i++) {
    if (str[i] == 'i') {
      pos_i = i;
      break;
    }
  }

  // 만일 'i' 가 없다면 이 수는 실수 뿐이다.
  if (pos_i == -1) {
    real = get_number(str, begin, end - 1);
    return;
  }

  // 만일 'i' 가 있다면,  실수부와 허수부를 나누어서 처리하면 된다.
  real = get_number(str, begin, pos_i - 1);
  img = get_number(str, pos_i + 1, end - 1);

  if (pos_i >= 1 && str[pos_i - 1] == '-') img *= -1.0;
}
Complex Complex::operator-(const char* str) const {
  Complex temp(str);
  return (*this) - temp;
}
Complex Complex::operator*(const char* str) const {
  Complex temp(str);
  return (*this) * temp;
}
Complex Complex::operator/(const char* str) const {
  Complex temp(str);
  return (*this) / temp;
}

int main() {
  Complex a(0, 0);
  a = a + "-1.1 + i3.923";//->a=a.operator+("-1.1+i3.923");->a=a.operator+(Complex("-1.1+i3.923"));
  a.println();//a="-1.1+i3.923"+a;시 오류!!operator+는 a.operator+로 변형이 가능해야하지만 이는 불가.->이에대한건 다음 강의! 
  a = a - "1.2 -i1.823";
  a.println();
  a = a * "2.3+i22";
  a.println();
  a = a / "-12+i55";
  a.println();
}

/*
[1. 연산자의 오버로딩]
1.	C++에서는 ::(범위지정), .(멤버 지정), .*(멤버 포인터로 멤버 지정)을 제외한 모든 연산자를 사용자 정의할 수 있다. 
2.	위처럼 기본 연산자들을 직접 사용자가 정의하는 것을 연산자를 오버로딩(overloadin)한다고 부릅니다.
[2. MyString의 '=='연산자 오버로딩]
1.	연산자 오보로딩을 사용하기 위해서는, (리턴 타입) operator(연산자) (연산자가 받는 인자)꼴로 작성해야 한다.
	즉, 만약 우리가 ==을 오버로딩 하고 싶다면 bool을 리턴값으로, 인자로는 비교하는 것 하나만 받게 된다.
	예를 들어 bool operator==(MyString& str);에서는 str==str2라는 명령을 str.operator==(str2)가 내부적으로 실행된다.
[3. 복소수(Complex number)클래스 만들기]_이미 std::complex로 정의되어 있지만 교육용으로 만들어보쟝고 
1.	z=a+bi
2.	Complex&가 아니라 Complex가 반환형인 이유는 만약 Complex a=b+c+b;의 경우, b+c를 한 결과를 b에 저장하고
	+b를 진행하게 되는데, 그럼 연산과정에서 b의 결과가 런타임중에 바뀌어버리니 실질적으로 b+c+(b+c)의 값이 나온다.
	 또한 피연산자의 값이 연산을 한다고해서 바뀌면 안되기때문에, 참조자가 아닌 새로운 객체를 만들어 리턴한다.
3.	또한 const키워드를 붙인 이유로는 연산자 오버로딩 시 함수 내부에서는 읽기만 수행되고 피연산자들의 수정을 일어나지 않기에
	const키워드를 붙여주는 것이 바람직하기 때문이다.(실수방지. 매번 const확인하는 것은 중요!) 
[4. 대입 연산자 함수]
1.	대입 연산자는 위의 일반 연산자 오버로딩과 다르게, 자기 자신을 가리키는 레페런스를 리턴시켜야 한다.
	a=b=c;코드에서 b=c가 b를 리턴해야 a=b;가 수행될 수 있기 때문이다.
	또한 불필요한 복사를 방지하기 위함의 이유도 있고, c+b는 결괏값을 담을 장소가 필요하지만, c=b에선 b를 담을 장소 c가 이미 존재하기 때문이다.
2.	사실 operator=를 만들지 않더라도, 위의 소스를 컴파일하면 잘 작동하낟. 이는 컴파일러 차원에서 
	디폴트 대입 연산자(default assignment operator)를 지원하기 때문이다.(복사생성자도 디폴트가 있던것 처럼)
	 마찬가지로 얕은 복사를 수행한다. 고로 클래스 내부적으로 메모리를 동적으로 할당하는 경우, 대입 연산자 함수를 꼭 만들어주어야 한다.
	<중간점검> 
	Some_Class a = b;  // ①는 복사 생성자 호출
	Some_Class a;  // ②는 생성자 호출다음 대입 연산자 호출 
	a = b;
3.	연산자 오버로딩을 사용하면, 모든 연산자들에 대해 개별적인 정의가 필요하다.
	즉, operator+와 operator=를 정의했다고 a+=b를 자동으로 a=a+b로 바꿔주지 않는다. 
	마찬가지로 ++을 +=1로 바꿔주지 않는다.
[5. 문자열로 'Complex'수와 덧셈하기]_y=z+"3+i2";_문자열 모종의 약속. (부호) (실수부) (부호) i (허수부) 
[6. 생각해보기]
1.	String class에서 구현해보기. 
	1) if(str1.compare(str2) == 0) 하지 말고 if(str1 == str2) 하면 어떨까?
	2)str1.insert(str1.length(), str2) 하지 말고 str1 = str1 + str2; 하면 어떨까?
	3)str1[10] = 'c'; 와 같은 것도 할 수 있을까? 
2.	get_number 함수를 cstdlib 의 atof 함수를 이용해서 좀 더 간단하게 나타내보기. 
*/
