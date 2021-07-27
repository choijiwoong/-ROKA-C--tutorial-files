/*1
#include <iostream>

class A{
	private:
		void private_func(){}
		int private_num;
		
		friend class B;//B�� A�� ģ�� 
		friend void func();//func()�� A�� ģ�� 
}; 

class B{
	public:
		void b(){
			A a;
			//private �Լ��� fields����, ģ���̱� ������ ������ �����ϴ�. 
			a.private_func();
			a.private_num=2;
		}
};

void func(){
	A a;
	//private �Լ��� fields����, ģ���̱� ������ ������ �����ϴ�. 
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

  //Complex operator+(const Complex& c) const; //�ڱ� �ڽ��� �������� ������ �ܺ��Լ���(�Ʒ� friend) 
  Complex& operator=(const Complex& c);

  // ������ ������ �Լ����� ���� :)

  void println() {
    std::cout << "( " << real << " , " << img << " ) " << std::endl;
  }

  // ���� �� �Լ��� Complex �� private ��� �����鿡 ������ �� �ֽ��ϴ�.
  friend Complex operator+(const Complex& a, const Complex& b);
};

Complex operator+(const Complex& a, const Complex& b) {
  Complex temp(a.real + b.real, a.img + b.img);//a�� b�� private��������� ���� ����. 
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
[1. friend Ű����]
1.	friend��� �����ϰ� �Ǹ�, ��� private��� �Լ���� ��� �����鿡 ���� ���� ������ �ο��ϰ� �ȴ�.
	�ٸ�, ¦����̶� ������ ������ �Ұ��ϰ� �Ϲ����̴�. 
class A {
 	private:
  	int x;

  	friend class B;
};

class B {
 	private:
  	int y;
};
�� ���, A�� B�� private������ y�� ������ �Ұ��ϴ�. ���� ģ���� ����� �Լ����� ������ �����һ�.

[2. ���� ������] 
1.	�ռ� �����ڿ����ε� �� a = a + "-1.1 + i3.923";  // ��� ������,  a = "-1.1 + i3.923" + a;  // ��� �ȵȴٴ� ������ �־���.
	�����Ϸ��� *a.operator@(b); *operator@(a, b);(���⼭ @�� ������ ������) �� ������ �༮���� ó���ϴµ�,
	���ڴ� aŬ������ ����Լ���, ���ڴ� �Ϲ����� �Լ��� �ǹ��Ѵ�. ��� Complex operator+(const Complex& a, const Complex& b) {}
	�÷� �ϸ� �ȴ�. ���  "-1.1 + i3.923" + a;��, �����ε� �Լ��� ���� operator+(Complex("-1.1 + i3.923"), a);�� �ؼ��Ǿ� �� ����ȴ�.
	 ���⼭ �߿��� ����, operator+�Լ��� ����� �۵��Ϸ��� a�� b�� real, img�� �����ؾ��ϴµ� �̴� private����̴�. ��� friend�� ����Ѵ�. 
2.	1�� ���� ����� ���Ѵٸ� ���� ������Ȳ������ ������ �ذ��� �� �ִ�. �ٸ� �߰����� ������ ����µ�,
	a=a+a;�� ���� ��ɾ���� 1�� *a.operator@(b); *operator@(a, b); �� �� �����ϱ� ������ �����
	����ؾ��ϴ��� �𸣰ڴٴ� ��ȣ��� �߻���Ų��. ��� �� �� �ϳ��� �Լ��� ���־� �Ѵ�.
3.	(�߿�)
	��������� �ڱ� �ڽ��� �������� �ʴ� ���� �����ڵ�(+, -, *, /)�� �ܺ��Լ��� �����ϴ� ���� ��Ģ�̸�,
	�ݴ�� �ڱ� �ڽ��� �����ϴ� ���� �����ڵ�(+=, -=)�� ��� ����Լ��� �����ϴ� ���� ��Ģ�̴�.  

[3. ����� ������ �����ε� �ϱ�]
1.	std::cout<<a;��� ��� ���� std::cout�̶�� ��ü�� �ɹ����� operator<<�� ���ǵǾ� �־� a�� ȣ���ϴ� ���̴�.
	�ٸ� int, double, ���ڿ� ��� ����� �Ǵ� ���� �� ���� ���� operator<<�Լ����� �����ε� �Ǿ��ִٴ� ���̴�.
	(p.s �̴� ostream�� ���ǵǾ� �ִ�. +iostream�� ostream�� include��.)
�̵� ���п� �츮�� ���ϰ� ������ Ÿ�Կ� ������� �ս��� ����� ����� �� �ְ� �Ǵ� ��������.
���� �⸴_���� ���� �ϳ����� ���� ������. 
	  


*/
