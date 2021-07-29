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

  //Complex operator+(const Complex& c) const; //�ڱ� �ڽ��� �������� ������ �ܺ��Լ���(�Ʒ� friend) 
  Complex& operator=(const Complex& c);

  // ������ ������ �Լ����� ���� :)

  void println() {
    std::cout << "( " << real << " , " << img << " ) " << std::endl;
  }
  
  friend std::ostream& operator<<(std::ostream& os, const Complex& c); 
  // ���� �� �Լ��� Complex �� private ��� �����鿡 ������ �� �ֽ��ϴ�.
  friend Complex operator+(const Complex& a, const Complex& b);
};

std::ostream& operator<<(std::ostream& os, const Complex& c){
	os<<"( "<<c.real<<" , "<<c.img<<" ) ";
	return os;
}
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
  std::cout << "a �� ���� : " << a << " �̴�. " << std::endl;//a �� �׳� cout�� �ص� ����� �ǵ���. 
}*/

/*4
#include <iostream>
#include <cstring>

class MyString {
  char* string_content;  // ���ڿ� �����͸� ����Ű�� ������
  int string_length;     // ���ڿ� ����

  int memory_capacity;  // ���� �Ҵ�� �뷮

 public:
  // ���� �ϳ��� ����
  MyString(char c);

  // ���ڿ��� ���� ����
  MyString(const char* str);

  // ���� ������
  MyString(const MyString& str);

  ~MyString();

  int length();

  void print() const;
  void println() const;

  char& operator[](const int index);//÷�� ������ operator. �μ��� �ε��� ���� int, return type�� 'c'ó�� �����ϱ⿡. 
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
    std::cout << "���� ���� ������" << std::endl;
    return *this;
  }

  // ���� ������ ���� ������ ���̸� �α� ���� ���� ������ ��� ���ڷ� int ��
  // ������ �����δ� �ƹ��͵� ���޵��� �ʴ´�.
  Test operator++(int) {
    Test temp(*this);
    x++;
    std::cout << "���� ���� ������" << std::endl;
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
  func(t++); // 4 �� ��µ�
  std::cout << "x : " << t.get_x() << std::endl;
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
***2���Ҹ��� 
2.	���� ComplexŬ�������� ostreamŬ������ ������ operator<<�� ����� �� �ִٸ�? Complex c; std::cout<<c; ->Complex c; c.println();
	�翬��, ostreamŬ������ operator<<�ɹ� �Լ��� �߰��ϴ� ���� ǥ�� ��������� ������ �����ؾ��ϱ⿡ �Ұ����ϴ�. ���
	ostreamŬ������ Complex��ü�� �����ε��ϴ� operator<<������ �Լ��� �߰��� �� �ִ�. �� ostream��ü�� Complex��ü �ΰ��� ���ڷ� �޴� ���� operator<<�Լ��� �����ϸ� �ȴ�.

[4. ÷�� ������ operator[]] (�迭�� ���Ҹ� ������ �� []�ȿ� �ִ� ���� ÷��(subscript)��� �θ�) 
1.	MyStringŬ�������� []�� �̿��Ͽ� str[10]�� ���� 10��° ���ڿ� ��Ȯ�ϰ� ������ �� �ְ� �غ���. 

ļ �������� �� �� �� �ٽ� ��̰� �ٴ� ��
[5. int Wrapper Ŭ����-Ÿ�� ��ȯ ������]_Wrap: ���δ�, �����ϴ�_���𰡸� �����ϴ� Ŭ����. 
1.	Int�� ���� int�� ���� ������� ��� ������ �Լ����� ����� �ָ� ������, ������ �����ε��ϱ⿡�� ���� �����̴�.
	������, �ܼ��� int�� �������� �ϴ��ϰ� ��Ȯ�� �Ȱ��� ������ ���� �̹� �����ϴ� ����� �ٽ� ���餷 �ʿ�� ����.
	�̶�, Ÿ�� ��ȯ �����ڸ� ����Ͽ� WrapperŬ������ ��ü�� ���� 'int�� ����'�� �����Ϸ��� ������ �� �ְ� �����.
	�� Ŭ������ ��ü�� int�� ������ ��ȯ�Ͽ� +���� ������ �����ϰ� �ϴ� ���̴�. 
2.	operator (��ȯ�ϰ����ϴ�Ÿ��) () �̶�, c++���� ��ȯ �����ڸ� �����ϱ� ���Ͽ� �Լ��� ����Ÿ���� ���� �ʴ´�. 
	 �� Wrapper�� Ŭ������ ������ ��ȯ �����ڷ� operator int�� ã�� int�� ��ȯ�Ͽ� ó���� �� ����(return data) ��
	default ���� �����ڰ� �˾Ƽ� ó���ϰ� �Ѵ�. 
	
[6.	����/���� ���� ������]
1.	������ �����ε� �� �� a++�� ++a�� ���� operator++�ε� �̸� ��� �����ϳ�? 
	 �ƿ� ���� ������ ���ѹ���. operator++()_++x, operator--();_--x.(���� ���� ������), operator++(int x)_x++, operator--(int x)_x--(���� ���� ������)
	���⼭ int�� �ƹ� �ǹ̰� ���� �ܼ��� ������ ������ �����ϱ� ���� ����Ѵ�.(p.s ++�ϸ� ���ڷ� ���� ���� ����ϴ� ���� ���⿡operator++(int)�� �ص� ����.) 
2.	���⼭ ������ ���� �������������� ���, ���� �ٲ� �ڽ��� �����ؾ� �ϰ�, ���� ������ ��� ���� �ٲ�� ������ ��ü�� �����ؾ� �Ѵ�.
	����������
	A& operator++(){
		//A++
		return *this;
	}
	����������.
	A operator++(int){/������ ���޵Ǵ� �μ��� ����) 
		A temp(A);//for ���� ���� ���. 
		//A++
		return temp;//because of ������ ���� ++�� ����Ǳ� ������ ++�� ����� �� �ְ� Ŭ������ ������ �����Ѵ�. temp++;������. 
	} 
3.	���� ���� ���� ������ ��� �߰������� ��������ڸ� ȣ���ϱ� ������ ���� ���� ���꺸�� �� ������!

[7. ������ �����ϱ�]
1.	�� ���� ������ ��ü ���̿����� ���� �����ڴ� ��� �Լ��� �ƴ� �ܺ� �Լ��� �����ε� �ϴ� ���� �����ϴ�.(ex. Complex�� operator+(const complex&, const Complex&) const
2.	�� ���� ��ü ������ ���� ������ ������ �� ��ü�� ���� �ٲ�ٴ��� �������� �ʴ� ���� �����ڴ� ��� �Լ��� �����ε� �ϴ� ���� �����ϴ�.(ex. operator+=�� operator+=(const Complex&)�� ����.
3.	���� �����ڴ� ��� �Լ��� �����ε� �ϴ� ���� �����ϴ�(ex. operator++)
4.	�Ϻ� �����ڵ��� �ݵ�� ��� �Լ��θ� �����ε� �ؾ� �մϴ�. ([](÷��), ->(��� ����), =(���� ������), ()�Լ�ȣ�⿬����) 

[8. �����غ���]
1.	N���� �迭�� �����ϴ� Ŭ������ ������. 
*/
