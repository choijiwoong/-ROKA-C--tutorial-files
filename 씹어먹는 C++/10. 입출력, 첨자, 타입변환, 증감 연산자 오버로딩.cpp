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

  // 이제 이 함수는 Complex 의 private 멤버 변수들에 접근할 수 있습니다.
  friend Complex operator+(const Complex& a, const Complex& b);
};

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
  a = a + a;

  Complex b(1, 2);
  b = a + b;

  b.println();
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
	  


*/
