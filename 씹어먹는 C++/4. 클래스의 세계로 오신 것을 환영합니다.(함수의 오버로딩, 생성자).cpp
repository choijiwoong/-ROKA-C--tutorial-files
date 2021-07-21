/*1. �Լ��� �����ε�(Overloading)
�����ε��� ������ ��: �����ϴ�, �����ϰ� �ɸ��� �ϴ�, �ʹ� ���� �ִ�.
��. �Լ��� �����ϸ� �ִ�..
printf�� C���̺귯���� �� �Ѱ��̰�, scanf�� �ϳ������� C++������ ���� �̸��� ���� �Լ��� ������ �����ص� �ȴ�.
 �� �Լ��� ������ ���ڸ� ���� �����Ѵ�.
 
#include <iostream>

void print(int x) { std::cout<<"int: "<<x<<std::endl;}
void print(char x) { std::cout<<"char: "<<x<<std::endl; }
void print(double x) { std::cout<<"double: "<<x<<std::endl; }

int main(){
	int a=1;
	char b='c';
	double c=3.2f;
	
	print(a);
	print(b);
	print(c);
	
	return 0;
}
��, C++������ �Լ��� �̸��� ������ ���ڰ� �ٸ��� �ٸ� �Լ��� �Ǵ��Ͽ� ������ �߻����� �ʴ´�.
���⼭�� ������ C���� ��� �ڷ��� Ÿ�Կ� ���� �Լ��� �̸��� �ٸ��� ������ ������, C++�� �˾Ƽ�
������ ���ڸ� ������ �Լ��� ã���ֱ⿡ �̸��� ���� �ص� �������(�Լ��� �����ε�)

#include <iostream>

void print(int x) { std::cout << "int : " << x << std::endl; }
void print(double x) { std::cout << "double : " << x << std::endl; }//char�� �޴� �Լ��� �����. 

int main() {
  int a = 1;
  char b = 'c';
  double c = 3.2f;

  print(a);//p.s) printf�� �ƴ϶� print��. 
  print(b);//char�� �޴� �Լ��� ���� ���¿��� ȣ��. ->�ᱣ�� 99�� ��µ�. 
  print(c);//�� line39�� 2�ܰ迡 ���� ����ȯ�� ���� print(int x)ȣ��. 

  return 0;
}
���� ��� ��Ȯ�� ��ġ�ϴ� ���ڸ� ������ �Լ��� ���� ������ '�ڽŰ� �ִ�� ������ �Լ�'�� ã�Ե�
C++���� �Լ��� �����ε� �ϴ� ����
1�ܰ�: �ڽŰ� Ÿ���� ��ȣ���� ��ġ�ϴ� �Լ��� ã�´�.
2�ܰ�: ��Ȯ�� ��ġ�ϴ� Ÿ���� ���� ��� ����ȯ�� ���ؼ� ��ġ�ϴ� �Լ��� ã�ƺ���.
		1. Char, unsigned char, short �� int �� ��ȯ�ȴ�.
		2. Unsigned short �� int �� ũ�⿡ ���� int Ȥ�� unsigned int �� ��ȯ�ȴ�.
		3. Float �� double �� ��ȯ�ȴ�.
		4. Enum �� int �� ��ȯ�ȴ�.
3�ܰ�: �� �� �������� ����ȯ�� ���� ��ġ�ϴ� �Լ��� ã�ƺ���.
		1. ������ ����(numeric) Ÿ���� �ٸ� ���� Ÿ������ ��ȯ�ȴ�. (���� ��� float -> int)
		2. Enum �� ������ ���� Ÿ������ ��ȯ�ȴ� (���� ��� Enum -> double)
		3. 0 �� ������ Ÿ���̳� ���� Ÿ������ ��ȯ�� 0 �� ������ Ÿ���̳� ���� Ÿ������ ��ȯ�ȴ�
		4. �����ʹ� void �����ͷ� ��ȯ�ȴ�.
4�ܰ�: ���� ���ǵ� Ÿ�� ��ȯ���� ��ġ�ϴ� ���� ã�´�.
�����߻��ܰ�: ��ȣ�ϴٶ�� �Ǵ��Ͽ� ���� �߻�. 

#include <iostream>

void print(int x) { std::cout<<"int: "<<x<<std::endl; }
void print(char x) { std::cout<<"double: "<<std::endl; }

int main(){
	int a=1;
	char b='c';
	double c=3.2f;
	
	print(a);
	print(b);
	print(c);//double�� ����ȯ�� int x, char x �� �ΰ����� ���ɼ��� �־� ��ȣ�����߻�. 
	
	return 0;
}
���� ��������(line64)������ 1�ܰ迡�� �ڽŰ� ���� �Լ��� ��� 2�ܰ�� �Ѿ�� 2�ܰ迡�� ������ 
float�̳� double�� �ش�Ǵ� ���� ��� 3�ܰ�� �Ѿ��, 3�ܰ迡�� double�� int�� char.
��, ���� �ܰ� �ȿ��� �� �� �̻��� ������ ��ġ�� �����ϹǷ� ambigous������ ����Ų��.
 �׷��⿡ �����ε� ��Ģ�� �����ϴ� ���� �ſ� �߿��ϴ�. ���� �������� ������ �Լ��� �����ε��Ѵٸ�
�������� �� �� ���� ������ �⿬�� ���� �ȴ�..
*/

/*2. Date Ŭ����
#include <iostream>

class Date{
	int year_;
	int month_;//1 to 12
	int day_;//1 to 31
	
	public:
		void SetDate(int year, int month, int date);
		void AddDay(int inc);
		void AddMonth(int inc);
		void AddYear(int inc);
		
		//�ش� ���� �� �� ���� ���Ѵ�.
		int GetCurrentMonthTotalDays(int year, int month);
		void ShowDate(); 
}; 

void Date::SetDate(int year, int month, int day){//���Ͱ��� Date::�� �Լ��̸� �տ� �ٿ��ָ� 
	year_=year;//DateŬ���� ���� ���ǵ� �Լ� ��� �ǹ̸� �ο���. �ֳĸ� 
	month_=month;//Ŭ���� ���� ������ �Լ��� ������ ��� ���Ⱑ ���� �ʱ� �����̴�. 
	day_=day;//�Ѵ��� Ŭ������ ������ ���� �� �ְԲ�,, 
}

int Date::GetCurrentMonthTotalDays(int year, int month){
	static int month_day[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	if (month!=2){
		return month_day[month-1];
	} else if (year%4==0&&year%100!=0){
		return 29;//���� _������ ���ǳ�.. 
	} else{
		return 28;
	}
}

void Date::AddDay(int inc) {
  while (true) {
    // ���� ���� �� �� ��
    int current_month_total_days = GetCurrentMonthTotalDays(year_, month_);

    // ���� �� �ȿ� ���´ٸ�;
    if (day_ + inc <= current_month_total_days) {
      day_ += inc;
      return;
    } else {
      // �����޷� �Ѿ�� �Ѵ�.
      inc -= (current_month_total_days - day_ + 1);
      day_ = 1;
      AddMonth(1);
    }
  }
}


void Date::AddMonth(int inc){
	AddYear((inc+month_-1)/12);
	month_=month_+inc%12;
	month_=(month_==12?12:month_%12);
}

void Date::AddYear(int inc) { year_+=inc;}

void Date::ShowDate(){
	std::cout<<"������ "<<year_<<" �� "<<month_<<" �� "<<day_<<" �� �Դϴ� "<<std::endl;
}

int main(){
  Date day;
  day.SetDate(2011, 3, 1);//���� SetDate()�� ���� �ʾҴٸ� �Ʒ��� ����������� ������ ���� ��µǰ� ��. 
  day.ShowDate();//�̷��� ��츦 C++����� �������� �����ִ� ���� �ִµ�, �ٷ� ������(Constructor)�̴�. 

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
*/

/*3. ������(Constructor)
#include <iostream>

class Date {
  int year_;
  int month_;  // 1 ���� 12 ����.
  int day_;    // 1 ���� 31 ����.

 public:
  void SetDate(int year, int month, int date);
  void AddDay(int inc);
  void AddMonth(int inc);
  void AddYear(int inc);

  // �ش� ���� �� �� ���� ���Ѵ�.
  int GetCurrentMonthTotalDays(int year, int month);

  void ShowDate();

  Date(int year, int month, int day) {//��ü�� ������ �� ������ ���� ���ڿ� �°� ���߾� ȣ���ϸ�, 
    year_ = year;//�����ڸ� ȣ���ϸ� ��ü�� �����ϰ� ��. 
    month_ = month;
    day_ = day;
  }
};

// ����

void Date::AddYear(int inc) { year_ += inc; }

void Date::ShowDate() {
  std::cout << "������ " << year_ << " �� " << month_ << " �� " << day_
            << " �� �Դϴ� " << std::endl;
}
int main() {
  //Date daks;�����߻�. �����ڰ� ������ default�����ڴ� �����.  
  Date day(2011, 3, 1);//�̷��� ���ڸ� �� ���߾� ���־�� ��. 
  day.ShowDate();//��, DateŬ������ day��ü�� ����鼭 ������ Date(int year, int month, int day)�� ȣ���Ѵ� ��� ��.
   
  day.AddYear(10);
  day.ShowDate();

  return 0;
}
�����ڴ� �⺻������ "��ü ���� �� �ڵ����� ȣ��Ǵ� �Լ�"��� �� �� �ִ�. ��, �ڵ����� ȣ��Ǹ鼭 ��ü��
�ʱ�ȭ���ִ� ��Ȱ�� ����Ѵ�. �����ڴ� ��ü�� �ʱ�ȭ �ϴ� ��Ȱ�� �ϱ� ������ ���ϰ��� ����!
�������� ���Ǵ� 'Ŭ�����̸� (����) {}��' �����Ѵ�. 
�����ڸ� ����ϴ� �������
Date day(2011, 3, 1);�� ���� �Ͻ��� ���(implicit)��,
Date day=Date(2012,3,1);�� ���� ����� ���(explicit)�� �ִ�.
�ַ� �Ͻ���������� ����ؼ� ���̵� ����Ѵ�.
*/

/*4. ����Ʈ ������(Default constructor)
ó���� ������ ���Ǹ� ���� ���� �·� Date day;�� �� �������� �����ڴ� ȣ��ȴ�.
��ó�� �ƹ��� �����ڸ� �������� �ʴ´ٸ�, ���ڸ� �ϳ��� ������ �ʴ� �������� ����Ʈ ������(default constructor)�� ȣ��ȴ�.
 �̴� Ŭ�������� ����ڰ� ��� �����ڵ� ��������� �������� �ʾ��� ��쿡 �����Ϸ��� �ڵ����� �߰����ִ� �������̴�.
**���ǻ���**_����ڰ� �ٸ� �����ڸ� �߰��ϴ� ���� �����Ϸ��� �ڵ����� ����Ʈ �����ڸ� �������� �ʴ´�.

// ����Ʈ ������ �����غ���
#include <iostream>

class Date {
  int year_;
  int month_;  // 1 ���� 12 ����.
  int day_;    // 1 ���� 31 ����.

 public:
  void ShowDate();

  Date() {//���ڸ� ���� �ʴ� �����ڸ� ����. 
    year_ = 2012;
    month_ = 7;
    day_ = 12;
  }
};

void Date::ShowDate() {
  std::cout << "������ " << year_ << " �� " << month_ << " �� " << day_
            << " �� �Դϴ� " << std::endl;
}

int main() {
  Date day = Date();//������� ������� ������ ȣ�� 
  Date day2;//�Ͻ����� ������� ������ ȣ��_���ʿ� ���ǵ� �����ڿ� ���ڰ� ����. 
  Date day3();//���ڰ� �ִ� �� ó�� �ϸ�, default�����ڷ� �ʱ�ȭ �ϴ� ���� �ƴ϶�,
  //���ϰ��� Date��, ���ڰ� ���� �Լ� day3�� �����ϰ� �� ������ �ν���. �̴� �Ͻ���ǥ������
  //��ü�� ������ �� �����ؾ��ϴ� ����. 
  //�� ���Ͱ��� day3�� �Լ��� �����ϴ� ������ �˾Ƶ���. ��� default �����ڸ� �Ͻ��� ǥ������ ������
  //Date day2ó�� ��Ȯ�ϰ� ���ڰ� ���ٰ� ��������. 

  day.ShowDate();
  day2.ShowDate();
  day3.ShowDate();
  return 0;
}
*/

/*5. ��������� ����Ʈ ������ ����ϱ�.
C++11 �������δ� default�����ڸ� ����ϰ� ���� ��, �׳� �����ڸ� �������� �ʴ� ��� �ۿ� �����µ�,
�׷��� �ڵ带 �д� ����ڰ� �� �����ڰ� �����ڸ� �ؾ ���Ǹ� ���� ������, ����Ʈ �����ڸ� ����ϰ�
�; �ǵ� �� �������� �ް����ϱ� ������. �׷��� C++ 11���� ����Ʈ �����ڸ� ��������� ����� �� �ְԵ�.
class Date{
	public:
	Date()=default;//����Ʈ �����ڸ� �����ض�. 
};
�� Date�� ���ڰ� ���� ������ �޾��� ���ھ��� �����ڸ� �����ϴµ�, �� �����ڸ� default�� �����Ѵ�. 
*/

/*6. ������ �����ε�
#include <iostream>

class Date {
  int year_;
  int month_;  // 1 ���� 12 ����.
  int day_;    // 1 ���� 31 ����.

 public:
  void ShowDate();

  Date() {//������ ���� �Լ��⿡ �����ε��� ����. 
    std::cout << "�⺻ ������ ȣ��!" << std::endl;
    year_ = 2012;
    month_ = 7;
    day_ = 12;
  }

  Date(int year, int month, int day) {//���ڰ� �ٸ��� �ٸ� �Լ��� ����ϴ� �Լ� �����ε�. 
    std::cout << "���� 3 ���� ������ ȣ��!" << std::endl;
    year_ = year;
    month_ = month;
    day_ = day;
  }
  Date(int year){
  year_=year;
  month_=0;
  day_=0;
  }
};

void Date::ShowDate() {
  std::cout << "������ " << year_ << " �� " << month_ << " �� " << day_
            << " �� �Դϴ� " << std::endl;
}
int main() {
  Date day = Date();
  Date day2(2012, 10, 31);

  day.ShowDate();
  day2.ShowDate();

  return 0;
}
*/

//7. �����غ���. 
#include <iostream>

class Point {//Ŭ���� Point���� 
  int x, y;//���� x���� y���� ��Ÿ���� �ɹ����� x, y ����. 

 public:
  Point(int pos_x, int pos_y){//������ ����. 
  	x=pos_x;
  	y=pos_y;
  }
  
  void View(){//��ǥ ��� �Լ� 
  	std::cout<<"x: "<<x<<", y: "<<y<<std::endl;
  }
};

class Geometry {//������ ������ Ŭ���� Geometry����. 
 public:
  Geometry() {//������. Geometry��ü�� �����ϸ� �����ִ� ���� ������ 0���� �ʱ�ȭ�Ѵ�. 
    num_points = 0;
  }

  void AddPoint(const Point &point) {//Point�ڷ����� const�� ������point�� �����´�. 
    point_array[num_points ++] = new Point(point.x, point.y);
  }

  // ��� ���� ���� �Ÿ��� ����ϴ� �Լ� �Դϴ�.
  void PrintDistance();

  // ��� ������ �մ� ������ ���� ������ ���� ������ִ� �Լ� �Դϴ�.
  // ���������� ������ �� ���� �մ� ������ �������� f(x,y) = ax+by+c = 0
  // �̶�� �� �� ������ �ٸ� �� �� (x1, y1) �� (x2, y2) �� f(x,y)=0 �� ��������
  // ���� �ٸ� �κп� ���� ������ f(x1, y1) * f(x2, y2) <= 0 �̸� �˴ϴ�.
  void PrintNumMeets();

private:
  // �� 100 ���� �����ϴ� �迭.
  Point* point_array[100];//���� ������ ���� Point�ڷ����� �����͸� �迭 100ĭ���� ����. 
  int num_points;//���� ������ ���� ����. 
};

int main(){
	return 0;
} 




/*����
1. �Լ��� �����ε�(overloading)�̶� ���� �̸��� �Լ����� ���ڰ� �ٸ��� �ٸ� �Լ��� �Ǵ��Ͽ� �ڷ������� ���� �۾��� ó���ϴ� �Լ��� �̸��� ���� ������ �� �ִ� ���̴�.
	[C++���� �Լ��� �����ε� �ϴ� ����]
	1�ܰ�: �ڽŰ� Ÿ���� ��Ȯ�� ��ġ�ϴ� �Լ��� ã�´�.
	2�ܰ�: ��Ȯ�� ��ġ�ϴ� Ÿ���� ���� ��� ����ȯ�� ���ؼ� ��ġ�ϴ� �Լ��� ã�ƺ���.
		1. Char, unsigned char, short �� int �� ��ȯ�ȴ�.
		2. Unsigned short �� int �� ũ�⿡ ���� int Ȥ�� unsigned int �� ��ȯ�ȴ�.
		3. Float �� double �� ��ȯ�ȴ�.
		4. Enum �� int �� ��ȯ�ȴ�.
	3�ܰ�: �� �� �������� ����ȯ�� ���� ��ġ�ϴ� �Լ��� ã�ƺ���.
		1. ������ ����(numeric) Ÿ���� �ٸ� ���� Ÿ������ ��ȯ�ȴ�. (���� ��� float -> int)
		2. Enum �� ������ ���� Ÿ������ ��ȯ�ȴ� (���� ��� Enum -> double)
		3. 0 �� ������ Ÿ���̳� ���� Ÿ������ ��ȯ�� 0 �� ������ Ÿ���̳� ���� Ÿ������ ��ȯ�ȴ�
		4. �����ʹ� void �����ͷ� ��ȯ�ȴ�.
	4�ܰ�: ���� ���ǵ� Ÿ�� ��ȯ���� ��ġ�ϴ� ���� ã�´�.
	1~4�ܰԿ��� �ذ���� ������, ��ȣ�ϴٶ�� �Ǵ��Ͽ� ���� �߻�. 
	*�����ε� ��Ģ�� ��Ȯ�� �������� �ʰ� ����ϸ�, ���� �Լ��� �����ε����� ���� ambigous error�� �߱��Ѵ�.
2. Ŭ���� ���� ������ �Լ��� ������ ��, ���ü��� ����Ű�� ���� Ŭ���� �ۿ� ��ü���� �Լ��� ������ �ۼ��Ѵ�. 
	class Date{
	void show(int year, int month, int day);
	}
	
	void Date::show(int year, int month, int dat){
	�˸���~~�Լ��� ����! 
	}
3. ������(Constructor)�� ��ü ���� �� �ڵ����� ȣ��Ǵ� �Լ��̸�, public:�ȿ� Ŭ�����̸�(����{} �÷� �����Ѵ�. 
   �����ڸ� ȣ���ϴ� �������, ����� ���(explicit)_Date day=Date(2012,3,1)�� �Ͻ��� ���(implicit)_Date day(2011, 3, 1);�� �ִ�.
4. ����Ʈ ������(Default constructor)�� Ŭ�������� ����ڰ� ��� �����ڵ� ��������� �������� �ʾ��� ��쿡 �����Ϸ��� �ڵ����� �߰����ִ� �������̴�.
   �����Ϸ��� ������ִ� ����Ʈ �����ڴ� �ƹ��͵� ��������, ������ �����ڿ��� ���ڸ� ���� ����Ʈ �����ڸ� ������ ������ �� �ִ�. 
   ����ڰ� �����ڸ� ������ִ� ���� �����Ϸ��� ����Ʈ �����ڸ� ������ ��������� �ʴ´�.
   ����Ʈ �����ڸ� ����� ��, ���ǻ����� �ִµ�, main()�ּ� ���� �� Date day=Date()�� Date day2�� ����ؾ���, Date day3();�̶�� ����ع����� ��ȯ���� Date�� �Լ� day3�� �����̶�� �����ع����� ����. 
   ��, ����Ʈ �����ڸ� ����� ��, ��Ȯ�ϰ� ���ڰ� ���ٰ� Date day2ó�� ����ؾ��� ���� �ִ� ��ó�� Date day2()�� ������� ����. 
5. ����Ʈ �����ڸ� �Ϻη� ����ߴٰ� �ڵ�� �����ֱ� ���Ͽ� ��������� default�����ڸ� ������ �� �ִµ�, ������ ���� �ڸ���(public:) Date()=default;�� ǥ���Ѵ�. 
6. ������ ���� �Լ��̱� ������ �μ��� �ٸ��� �ٸ� �Լ��� ����ϴ� ������ �����ε�(overloading)�� �����ϴ�. 
*/ 
