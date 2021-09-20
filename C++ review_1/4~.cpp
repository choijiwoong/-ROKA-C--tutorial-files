#include <iostream>

//�ռ� �Լ��� �����ε��� ���� ��� ¤�� �Ѿ�µ�, ������ ���� �Լ� �̱� ������ ���������� �Լ��� �����ε��� ����� �� �ֽ��ϴ�. ���� ���� �ش� Ŭ������ ��ü�� �������� ������� ������ �� �ְ� �ǰ�����.

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
		return 29;//����
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

  	day.SetDate(2012, 1, 31);  // ����
  	day.AddDay(29);
  	day.ShowDate();

  	day.SetDate(2012, 8, 4);
  	day.AddDay(2500);
  	day.ShowDate();
  	
	return 0;
}

/*
1.	C++�����Ϸ��� �Լ� �����ε� ����
	1) �ڽŰ� Ÿ���� ��Ȯ�� ��ġ�ϴ� �Լ��� ã�´�.
	2) ��Ȯ�� ��ġ�ϴ� Ÿ���� ���� ��� �Ʒ��� ���� ����ȯ�� ���Ͽ� ��ġ�ϴ� �Լ��� ã�ƺ���.
		-char, unsigned char, short�� int
		-unsigned short�� int�� ũ�⿡ ���� intȤ�� unsigned int��
		-float�� double��
		-enum�� int��
	3) �Ʒ��� �� �� �������� ����ȯ�� ���Ͽ� ��ġ�ϴ� �Լ��� ã�ƺ���.
		-numeric(������ ����)Ÿ���� �ٸ� ���� Ÿ������ ��ȯ�ȴ�.
		-enum�� ������ ���� Ÿ������ ��ȯ�ȴ�
		-0�� ������ Ÿ���̳� ����Ÿ������ ��ȯ�ȴ�.
		-�����ʹ� void�����ͷ� ��ȯ�ȴ�.
	4) ���� ���ǵ� Ÿ�� ��ȯ���� ��ġ�ϴ� ���� ã�´�
	 �� 4������ ���ؿ� �ش����� ������ ��ȣ�ϴ�(ambigous)��� �Ǵ��Ͽ� ������ �߻���Ų��. 
	���� �ڵ忡���� 3�ܰ���� ���������� double�� char�̳� int�� �� ��ȯ�� �����ϱ⿡ ambiguous������ �߻���Ų��. 

2.	Date day(2011, 3, 1);�� �Ͻ���(implicit) ���, Date day=Date(2012, 3, 1);�� �����(explicit) ������� �����ڸ� ȣ���� ���̴�. 
	Default�����ڸ� Date(){}ó�� �����ص� ������, Date()=default�� ��������� �˷��� ���� �ִ�. 
*/
