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
1.	�����ڿ� ���������� ��ü�� ����� �����ϴ� ���� �ƴ϶� ����� Ÿ������ ���� �� ���, �����Ϸ��� �Ͻ��� ��ȯ(implicit conversion)�� �Ͽ�
	��ü�� �����ϴµ�, �̶� ����ڰ� ������ �ʴ� �Ͻ��� ��ȯ�� �߻��� �� �ֱ⿡ �׸� ���� ���ؼ� explicitŰ���带 ����Ѵ�. (������ �߻���Ŵ) 
2.	������ mutable�� �����ϸ�, const�Լ� ������ mutableŰ���庯���� ���� ������ �����ϴ�. ����� �� ��������, DB���� GetUserInfo�� const�Լ��� �ѵ� ĳ�� update�� ����Ѵ�.
3.	������ �����ε� �� ��Ģ������ ��� ���۷����� �����ϸ� �ȵǴ°�, b+c+b�� ���� �Ŀ��� �̹� c�� ������ b�� 2���������� �� ������ �߻��Ѵ�.
	���� �����ڴ� ��������� �ڱ� �ڽ��� ���۷����� �����Ѵ�. ������ default assignment operator�� �̹� �ֱ⿡ ���� �ȸ��� �ȴ�(�����Ҵ��� �ٷ�°� �ƴϸ�)
	+=�� ���� �����ڵ��� +�� �ٸ��� ��ü ������ ���¸� �����ϱ⿡ const�� ���� �ʴ´�. 
4.	friend�� ���ǵ� Ŭ������ �Լ����� ���� Ŭ������ private�� ���ǵ� �Լ��� ������ ������ �����ϴ�. friend void func(); func�� A�� ģ��!
5.	����� ������ �����ε� 
6.	MyStringŬ������ char& MyString::operator[](const int index){return string_content[index];}�� ���� at���� ����� �����ϴ�. 
*/
