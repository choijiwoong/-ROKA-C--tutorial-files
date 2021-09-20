#include <iostream>

//앞서 함수의 오버로딩에 대해 잠깐 짚고 넘어갔는데, 생성자 역시 함수 이기 때문에 마찬가지로 함수의 오버로딩이 적용될 수 있습니다. 쉽게 말해 해당 클래스의 객체를 여러가지 방식으로 생성할 수 있게 되겠지요.

/*1 order of function overloading
void print(int x){ std::cout<<"int : "<<x<<std::endl; }
void print(char x){ std::cout<<"double : "<<x<<std::endl; } 

int main(){
	int a=1;
	char b='c';
	double c=3.2f;
	
	print(a);
	print(b);
	print(c);//ambiguous error!
	
	return 0;
}*/

//2 Date class
class Date{
	int year_;
	int month_;
	int day_;
	
	public:
		void SetDate(const int& year, const int& month, const int& date);
		void AddDay(int inc);
		void AddMonth(const int& inc);
		void AddYear(const int& inc);
		
		const int& GetCurrentMonthTotalDays(const int& year, const int& month);//calculation tool
		void ShowDate();
		
		Date()=default;//default constructor
		Date(const int& year, const int& month, const int& day){
			year_=year;
			month_=month;
			day_=day;
		}
};
void Date::SetDate(const int& year, const int& month, const int& day){
	year_=year;
	month_=month;
	day_=day;
}
const int& Date::GetCurrentMonthTotalDays(const int& year, const int& month){
	static int month_day[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	
	if(month!=2)
		return month_day[month-1];
	else if(year%4==0 && year%100!=0)
		return 29;//윤년
	else
		return 28; 
}
void Date::AddDay(int inc){
	while(1){
		int current_month_total_days=GetCurrentMonthTotalDays(year_, month_);
		
		if(day_+inc<=current_month_total_days){
			day_+=inc;
			return;
		} else{
			inc-=(current_month_total_days-day_+1);
			day_=1;
			AddMonth(1);
			//continue before execute code in if
		}
	}
}
void Date::AddMonth(const int& inc){
	AddYear((inc+month_-1)/12);
	month_=month_+inc%12;
	month_=(month_==12? 12:month_%12);
}
void Date::AddYear(const int& inc){
	year_+=inc;
}
void Date::ShowDate(){
	std::cout<<"totay is "<<year_<<"."<<month_<<"."<<day_<<std::endl;
}

int main(){
	//Date day();//definition of function day that return value is Date
	Date day;
	day.SetDate(2011,3,1);
	day.ShowDate();
	
	day.AddDay(30);
  	day.ShowDate();

  	day.AddDay(2000);
  	day.ShowDate();

  	day.SetDate(2012, 1, 31);  // 윤년
  	day.AddDay(29);
  	day.ShowDate();

  	day.SetDate(2012, 8, 4);
  	day.AddDay(2500);
  	day.ShowDate();
  	
	return 0;
}

/*
1.	C++컴파일러의 함수 오버로딩 과정
	1) 자신과 타입이 정확히 일치하는 함수를 찾는다.
	2) 정확히 일치하는 타입이 없는 경우 아래와 같은 형변환을 통하여 일치하는 함수를 찾아본다.
		-char, unsigned char, short는 int
		-unsigned short는 int의 크기에 따라 int혹은 unsigned int로
		-float은 double로
		-enum은 int로
	3) 아래의 좀 더 포괄적인 형변환을 통하여 일치하는 함수를 찾아본다.
		-numeric(임의의 숫자)타입은 다른 숫자 타입으로 변환된다.
		-enum도 임의의 숫자 타입으로 변환된다
		-0은 포인터 타입이나 숫자타입으로 변환된다.
		-포인터는 void포인터로 변환된다.
	4) 유저 정의된 타입 변환으로 일치하는 것을 찾는다
	 위 4가지의 기준에 해당하지 않으면 모호하다(ambigous)라고 판단하여 오류를 발생시킨다. 
	위의 코드에서는 3단계까지 내려간다음 double이 char이나 int둘 다 변환이 가능하기에 ambiguous오류를 발생시킨다. 

2.	Date day(2011, 3, 1);은 암시적(implicit) 방법, Date day=Date(2012, 3, 1);은 명시적(explicit) 방법으로 생성자를 호출한 것이다. 
	Default생성자를 Date(){}처럼 선언해도 되지만, Date()=default로 명시적으로 알려줄 수도 있다. 
*/
