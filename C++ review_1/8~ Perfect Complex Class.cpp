#include <iostream>
#include <cstring>

class Complex{
	private:
		double real, img;
		double get_number(const char* str, int from, int to) const;//tool
		
	public:
		Complex(double real, double img): real(real), img(img){}
		Complex(const Complex& c) { real=c.real, img=c.img; }
		Complex(const char* str);
		
		Complex& operator+=(const Complex& c);//function that returns self to member function
		Complex& operator-=(const Complex& c);
		Complex& operator*=(const Complex& c);
		Complex& operator/=(const Complex& c);
		
		Complex& operator=(const Complex& c);
		
		friend std::ostream& operator<<(std::ostream& os, const Complex& c);
		friend Complex operator+(const Complex& a, const Complex& b);//function that raturns new object to outside function
		friend Complex operator-(const Complex& a, const Complex& b);
		friend Complex operator*(const Complex& a, const Complex& b);
		friend Complex operator/(const Complex& a, const Complex& b);
};
Complex::Complex(const char* str){
	int begin=0, end=strlen(str);
	img=0.0;
	real=0.0;
	
	int pos_i=-1;//get i's position
	for(int i=0; i!=end; i++)
		if(str[i]=='i'){
			pos_i=i;
			break;
		}
	
	if(pos_i==-1){//no img num
		real=get_number(str,begin, end-1);
		return;
	}
	
	//img num is exist
	real=get_number(str, begin, pos_i-1);
	img=get_number(str, pos_i+1, end-1);
	if(pos_i>=1 && str[pos_i-1]=='-')//if negative
		img*=-1.0;
}
double Complex::get_number(const char* str, int from, int to) const{//-3.45
	if(from>to)//exception
		return 0;
	
	bool minus=false;
	if(str[from]=='-')//check -, +
		minus=true;
	if(str[from]=='-' || str[from]=='+')//next
		from++;
		
	double num=0.0;
	double decimal=1.0;
	
	bool integer_part=true;
	for(int i=from; i<=to; i++){
		if(isdigit(str[i])&&integer_part){//integer part
			num*=10.0;
			num+=(str[i]-'0');
		} else if(str[i]=='.'){//dot part
			integer_part=false;
		} else if(isdigit(str[i])&&!integer_part){//decimal part
			decimal/=10.0;
			num+=((str[i]-'0')*decimal);//+ to num
		} else{//integer end
			break;
		}
	}
	
	if(minus)
		num*=-1.0;
	
	return num;
}

Complex& Complex::operator+=(const Complex& c){
	(*this)=*this+c;
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
//assign
Complex& Complex::operator=(const Complex& c){
	real=c.real;
	img=c.img;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Complex& c){
	os<<"( "<<c.real<<", "<<c.img<<" ) ";
	return os;
}

Complex operator+(const Complex& a, const Complex& b){
	Complex temp(a.real+b.real, a.img+b.img);
	return temp;
}
Complex operator-(const Complex& a, const Complex& b){
	Complex temp(a.real-b.real, a.img-b.img);
	return temp;
}
Complex operator*(const Complex& a, const Complex& b){
	Complex temp(a.real*b.real-a.img*b.img, a.real*b.img+a.img*b.real);
	return temp;
}
Complex operator/(const Complex& a, const Complex& b){
	Complex temp((a.real*b.real+a.img*b.img)/(b.real*b.real+b.img*b.img), (b.real*a.img-a.real*b.img)/(b.real*b.real+b.img*b.img));
	return temp;
}

int main(){
	Complex a(0, 0);
	a="-1.1+i3.923"+a;
	std::cout<<"value of a is : "<<a<<std::endl;
}


/*
1.	생성자에 직접적으로 객체를 만들어 전달하는 것이 아니라 비슷한 타입으로 전달 할 경우, 컴파일러가 암시적 변환(implicit conversion)을 하여
	객체를 조정하는데, 이때 사용자가 원하지 않는 암시적 변환이 발생할 수 있기에 그를 막기 위해서 explicit키워드를 사용한다. (오류를 발생시킴) 
2.	변수를 mutable로 선언하면, const함수 내에서 mutable키워드변수에 한해 수정이 가능하다. 사용은 잘 안하지만, DB에서 GetUserInfo를 const함수로 한뒤 캐쉬 update시 사용한다.
3.	연산자 오버로딩 시 사칙연산의 경우 레퍼런스를 리턴하면 안되는게, b+c+b와 같은 식에서 이미 c가 더해진 b를 2번더해지는 논리 오류가 발생한다.
	대입 연산자는 통상적으로 자기 자신을 레퍼런스로 전달한다. 하지만 default assignment operator가 이미 있기에 굳이 안만들어도 된다(동적할당을 다루는게 아니면)
	+=과 같은 연산자들은 +과 다르게 객체 내부의 상태를 변경하기에 const로 하지 않는다. 
4.	friend로 정의된 클래스나 함수들은 원래 클래스의 private로 정의된 함수나 변수에 접근이 가능하다. friend void func(); func는 A의 친구!
5.	입출력 연산자 오버로딩 
6.	MyString클래스에 char& MyString::operator[](const int index){return string_content[index];}와 같이 at말고도 사용이 가능하다. 
*/
