/*
#include <string.h>
#include <iostream>

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
  // (*this) - (str) �� �����ؼ� �� 1, 0, -1 �� �� ����� �����Ѵ�
  // 1 �� (*this) �� ���������� �� �ڿ� �´ٴ� �ǹ�. 0 �� �� ���ڿ�
  // �� ���ٴ� �ǹ�, -1 �� (*this) �� ���������� �� �տ� �´ٴ� �ǹ��̴�.

  for (int i = 0; i < std::min(string_length, str.string_length); i++) {
    if (string_content[i] > str.string_content[i])
      return 1;

    else if (string_content[i] < str.string_content[i])
      return -1;
  }

  // ���� ���� �ߴµ� ������ �ʾҴٸ� �� �κ� ���� ��� �Ȱ��� ���� �ȴ�.
  // ���� ���ڿ� ���̰� ���ٸ� �� ���ڿ��� �ƿ� ���� ���ڿ��� �ȴ�.

  if (string_length == str.string_length) return 0;

  // ����� abc �� abcd �� ũ�� �񱳴� abcd �� �� �ڿ� ���� �ȴ�.
  else if (string_length > str.string_length)
    return 1;

  return -1;
}
bool MyString::operator==(MyString& str) {
  return !compare(str);  // str �� ������ compare ���� 0 �� �����Ѵ�._compare�� ��� ������ 0�� �����ϱ� ����. 
}
int main() {
  MyString str1("a word");
  MyString str2("sentence");
  MyString str3("sentence");

  if (str1 == str2)
    std::cout << "str1 �� str2 ����." << std::endl;
  else
    std::cout << "st1 �� str2 �� �ٸ���." << std::endl;

  if (str2 == str3)
    std::cout << "str2 �� str3 �� ����." << std::endl;
  else
    std::cout << "st2 �� str3 �� �ٸ���" << std::endl;
}*/
#include <string.h>
#include <iostream>

class Complex{
	double real, img;
	double get_number(const char *str, int from, int to) const;//stdlib.h�� atof�Լ��� ��ü ����. 
	
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
	Complex temp(real+c.real, img+c.img);//���� ������ �����ϰ� �ǿ������� ���� �ٲ�� �ȵǴ� �׳� Complex��ü�� ���� ����� ����. 
	return temp;//if ���⼭ temp�� �����ڸ� �����ع����� �Լ� ����� ���ÿ� �����. 
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

Complex Complex::operator+(const char* str) const{//�̰� �ʹ� �����ϴ� �׳� str�� complex�� ����� �����ڸ� �߰��ϰ� ������ �����ε���Ű��. 
	//find real part and img part. "��ȣ �Ǽ��� ��ȣ i �����" �Ǿ� ��ȣ ������ +����.
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
	
	if(pos_i>=1&&str[pos_i-1]=='-') str_img*=-1.0;//is ����� -�� * -
	//�Ǽ��� - ����? 
	
	Complex temp(str_real, str_img);
	return (*this) +temp; 
}
double Complex::get_number(const char *str, int from, int to) const{
	bool minus=false;
	if(from>to) return 0;//exception
	if(str[from]=='-') minus=true;//-�� true 
	if(str[from]=='-'||str[from]=='+') from++;//������ +�� ���� �����ϰ� ������ ++
	
	double num=0.0;
	double decimal=1.0;
	
	bool integer_part=true;
	for(int i=from;i<=to;i++){
		if(isdigit(str[i])&&integer_part){
			num*=10.0;
			num+=(str[i]-'0');//char�� int�� double�� ��ȯ�Ǹ� ASCII�ڵ�� ��ȯ�Ǵµ� ����'0'�� ASCII�� ���� ������ ���ڰ� ����. 
		} else if(str[i]=='.') integer_part=false;
		else if(isdigit(str[i])&&!integer_part){
			decimal/=10.0;
			num+=((str[i]-'0')*decimal);
		} else break;//�� �� �̻��� ����. 
	} 
	if(minus) num*=-1.0;
	return num;
}
Complex::Complex(const char* str) {
  // �Է� ���� ���ڿ��� �м��Ͽ� real �κа� img �κ��� ã�ƾ� �Ѵ�.
  // ���ڿ��� ���� ������ �����ϴ� "[��ȣ](�Ǽ���)(��ȣ)i(�����)"
  // �� �� �� ���� ��ȣ�� ���� �����մϴ�. (������ + �� ����)

  int begin = 0, end = strlen(str);
  img = 0.0;
  real = 0.0;

  // ���� ���� ������ �Ǵ� 'i' �� ��ġ�� ã�´�.
  int pos_i = -1;
  for (int i = 0; i != end; i++) {
    if (str[i] == 'i') {
      pos_i = i;
      break;
    }
  }

  // ���� 'i' �� ���ٸ� �� ���� �Ǽ� ���̴�.
  if (pos_i == -1) {
    real = get_number(str, begin, end - 1);
    return;
  }

  // ���� 'i' �� �ִٸ�,  �Ǽ��ο� ����θ� ����� ó���ϸ� �ȴ�.
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
  a.println();//a="-1.1+i3.923"+a;�� ����!!operator+�� a.operator+�� ������ �����ؾ������� �̴� �Ұ�.->�̿����Ѱ� ���� ����! 
  a = a - "1.2 -i1.823";
  a.println();
  a = a * "2.3+i22";
  a.println();
  a = a / "-12+i55";
  a.println();
}

/*
[1. �������� �����ε�]
1.	C++������ ::(��������), .(��� ����), .*(��� �����ͷ� ��� ����)�� ������ ��� �����ڸ� ����� ������ �� �ִ�. 
2.	��ó�� �⺻ �����ڵ��� ���� ����ڰ� �����ϴ� ���� �����ڸ� �����ε�(overloadin)�Ѵٰ� �θ��ϴ�.
[2. MyString�� '=='������ �����ε�]
1.	������ �����ε��� ����ϱ� ���ؼ���, (���� Ÿ��) operator(������) (�����ڰ� �޴� ����)�÷� �ۼ��ؾ� �Ѵ�.
	��, ���� �츮�� ==�� �����ε� �ϰ� �ʹٸ� bool�� ���ϰ�����, ���ڷδ� ���ϴ� �� �ϳ��� �ް� �ȴ�.
	���� ��� bool operator==(MyString& str);������ str==str2��� ����� str.operator==(str2)�� ���������� ����ȴ�.
[3. ���Ҽ�(Complex number)Ŭ���� �����]_�̹� std::complex�� ���ǵǾ� ������ ���������� �������� 
1.	z=a+bi
2.	Complex&�� �ƴ϶� Complex�� ��ȯ���� ������ ���� Complex a=b+c+b;�� ���, b+c�� �� ����� b�� �����ϰ�
	+b�� �����ϰ� �Ǵµ�, �׷� ����������� b�� ����� ��Ÿ���߿� �ٲ������� ���������� b+c+(b+c)�� ���� ���´�.
	 ���� �ǿ������� ���� ������ �Ѵٰ��ؼ� �ٲ�� �ȵǱ⶧����, �����ڰ� �ƴ� ���ο� ��ü�� ����� �����Ѵ�.
3.	���� constŰ���带 ���� �����δ� ������ �����ε� �� �Լ� ���ο����� �б⸸ ����ǰ� �ǿ����ڵ��� ������ �Ͼ�� �ʱ⿡
	constŰ���带 �ٿ��ִ� ���� �ٶ����ϱ� �����̴�.(�Ǽ�����. �Ź� constȮ���ϴ� ���� �߿�!) 
[4. ���� ������ �Լ�]
1.	���� �����ڴ� ���� �Ϲ� ������ �����ε��� �ٸ���, �ڱ� �ڽ��� ����Ű�� ���䷱���� ���Ͻ��Ѿ� �Ѵ�.
	a=b=c;�ڵ忡�� b=c�� b�� �����ؾ� a=b;�� ����� �� �ֱ� �����̴�.
	���� ���ʿ��� ���縦 �����ϱ� ������ ������ �ְ�, c+b�� �ᱣ���� ���� ��Ұ� �ʿ�������, c=b���� b�� ���� ��� c�� �̹� �����ϱ� �����̴�.
2.	��� operator=�� ������ �ʴ���, ���� �ҽ��� �������ϸ� �� �۵��ϳ�. �̴� �����Ϸ� �������� 
	����Ʈ ���� ������(default assignment operator)�� �����ϱ� �����̴�.(��������ڵ� ����Ʈ�� �ִ��� ó��)
	 ���������� ���� ���縦 �����Ѵ�. ��� Ŭ���� ���������� �޸𸮸� �������� �Ҵ��ϴ� ���, ���� ������ �Լ��� �� ������־�� �Ѵ�.
	<�߰�����> 
	Some_Class a = b;  // ��� ���� ������ ȣ��
	Some_Class a;  // ��� ������ ȣ����� ���� ������ ȣ�� 
	a = b;
3.	������ �����ε��� ����ϸ�, ��� �����ڵ鿡 ���� �������� ���ǰ� �ʿ��ϴ�.
	��, operator+�� operator=�� �����ߴٰ� a+=b�� �ڵ����� a=a+b�� �ٲ����� �ʴ´�. 
	���������� ++�� +=1�� �ٲ����� �ʴ´�.
[5. ���ڿ��� 'Complex'���� �����ϱ�]_y=z+"3+i2";_���ڿ� ������ ���. (��ȣ) (�Ǽ���) (��ȣ) i (�����) 
[6. �����غ���]
1.	String class���� �����غ���. 
	1) if(str1.compare(str2) == 0) ���� ���� if(str1 == str2) �ϸ� ���?
	2)str1.insert(str1.length(), str2) ���� ���� str1 = str1 + str2; �ϸ� ���?
	3)str1[10] = 'c'; �� ���� �͵� �� �� ������? 
2.	get_number �Լ��� cstdlib �� atof �Լ��� �̿��ؼ� �� �� �����ϰ� ��Ÿ������. 
*/
