/*1. 함수의 오버로딩(Overloading)
오버로드의 사전적 뜻: 과적하다, 과부하가 걸리게 하다, 너무 많이 주다.
즉. 함수에 과부하를 주다..
printf은 C라이브러리에 단 한개이고, scanf도 하나이지만 C++에서는 같은 이름을 가진 함수가 여러개 존재해도 된다.
 그 함수의 구분은 인자를 보고 결정한다.
 
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
즉, C++에서는 함수의 이름이 같더라도 인자가 다르면 다른 함수로 판단하여 오류가 발생하지 않는다.
여기서의 장점은 C언어였을 경우 자료형 타입에 따라 함수의 이름을 다르게 만들어야 했지만, C++은 알아서
적합한 인자를 가지는 함수를 찾아주기에 이름을 같게 해도 상관없다(함수의 오버로딩)

#include <iostream>

void print(int x) { std::cout << "int : " << x << std::endl; }
void print(double x) { std::cout << "double : " << x << std::endl; }//char을 받는 함수가 사라짐. 

int main() {
  int a = 1;
  char b = 'c';
  double c = 3.2f;

  print(a);//p.s) printf가 아니라 print임. 
  print(b);//char을 받는 함수가 없는 상태에서 호출. ->결괏값 99로 출력됨. 
  print(c);//즉 line39는 2단계에 따라서 형변환을 통해 print(int x)호출. 

  return 0;
}
위의 경우 정확히 일치하는 인자를 가지는 함수가 없기 때문에 '자신과 최대로 근접한 함수'를 찾게됨
C++에서 함수를 오버로딩 하는 과정
1단계: 자신과 타임이 정호가히 일치하는 함수를 찾는다.
2단계: 정확히 일치하는 타입이 없는 경우 형변환을 통해서 일치하는 함수를 찾아본다.
		1. Char, unsigned char, short 는 int 로 변환된다.
		2. Unsigned short 는 int 의 크기에 따라 int 혹은 unsigned int 로 변환된다.
		3. Float 은 double 로 변환된다.
		4. Enum 은 int 로 변환된다.
3단계: 좀 더 포괄적인 형변환을 통해 일치하는 함수를 찾아본다.
		1. 임의의 숫자(numeric) 타입은 다른 숫자 타입으로 변환된다. (예를 들어 float -> int)
		2. Enum 도 임의의 숫자 타입으로 변환된다 (예를 들어 Enum -> double)
		3. 0 은 포인터 타입이나 숫자 타입으로 변환된 0 은 포인터 타입이나 숫자 타입으로 변환된다
		4. 포인터는 void 포인터로 변환된다.
4단계: 유저 정의된 타입 변환으로 일치하는 것을 찾는다.
오류발생단계: 모호하다라고 판단하여 오류 발생. 

#include <iostream>

void print(int x) { std::cout<<"int: "<<x<<std::endl; }
void print(char x) { std::cout<<"double: "<<std::endl; }

int main(){
	int a=1;
	char b='c';
	double c=3.2f;
	
	print(a);
	print(b);
	print(c);//double의 형변환이 int x, char x 즉 두가지의 가능성이 있어 모호에러발생. 
	
	return 0;
}
위와 같은상태(line64)에서는 1단계에서 자신과 같은 함수가 없어서 2단계로 넘어가고 2단계에서 여전히 
float이나 double에 해당되는 것이 없어서 3단계로 넘어가고, 3단계에선 double이 int나 char.
즉, 같은 단계 안에서 두 개 이상의 가능한 일치가 존재하므로 ambigous오류를 일으킨다.
 그렇기에 오버로딩 규칙을 숙지하는 것은 매우 중요하다. 추후 여러개의 복잡한 함수를 오버로딩한다면
눈물없이 볼 수 없는 오류의 향연을 보게 된다..
*/

/*2. Date 클래스
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
		
		//해당 월의 총 일 수를 구한다.
		int GetCurrentMonthTotalDays(int year, int month);
		void ShowDate(); 
}; 

void Date::SetDate(int year, int month, int day){//위와같이 Date::를 함수이름 앞에 붙여주면 
	year_=year;//Date클래스 내에 정의된 함수 라는 의미를 부여함. 왜냐면 
	month_=month;//클래스 내에 복잡한 함수를 정의할 경우 보기가 좋지 않기 때문이다. 
	day_=day;//한눈에 클래스의 구조가 보일 수 있게끔,, 
}

int Date::GetCurrentMonthTotalDays(int year, int month){
	static int month_day[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	if (month!=2){
		return month_day[month-1];
	} else if (year%4==0&&year%100!=0){
		return 29;//윤년 _윤년고려 ㅈ되네.. 
	} else{
		return 28;
	}
}

void Date::AddDay(int inc) {
  while (true) {
    // 현재 달의 총 일 수
    int current_month_total_days = GetCurrentMonthTotalDays(year_, month_);

    // 같은 달 안에 들어온다면;
    if (day_ + inc <= current_month_total_days) {
      day_ += inc;
      return;
    } else {
      // 다음달로 넘어가야 한다.
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
	std::cout<<"오늘은 "<<year_<<" 년 "<<month_<<" 월 "<<day_<<" 일 입니다 "<<std::endl;
}

int main(){
  Date day;
  day.SetDate(2011, 3, 1);//만약 SetDate()를 하지 않았다면 아래의 연산과정에서 쓰레기 값이 출력되게 됨. 
  day.ShowDate();//이러한 경우를 C++언어적 차원에서 도와주는 것이 있는데, 바로 생성자(Constructor)이다. 

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
*/

/*3. 생성자(Constructor)
#include <iostream>

class Date {
  int year_;
  int month_;  // 1 부터 12 까지.
  int day_;    // 1 부터 31 까지.

 public:
  void SetDate(int year, int month, int date);
  void AddDay(int inc);
  void AddMonth(int inc);
  void AddYear(int inc);

  // 해당 월의 총 일 수를 구한다.
  int GetCurrentMonthTotalDays(int year, int month);

  void ShowDate();

  Date(int year, int month, int day) {//객체를 생성할 때 다음과 같이 인자에 맞게 마추어 호출하면, 
    year_ = year;//생성자를 호출하며 객체를 생성하게 됨. 
    month_ = month;
    day_ = day;
  }
};

// 생략

void Date::AddYear(int inc) { year_ += inc; }

void Date::ShowDate() {
  std::cout << "오늘은 " << year_ << " 년 " << month_ << " 월 " << day_
            << " 일 입니다 " << std::endl;
}
int main() {
  //Date daks;에러발생. 생성자가 있으면 default생성자는 사라짐.  
  Date day(2011, 3, 1);//이렇게 인자를 잘 맞추어 써주어야 함. 
  day.ShowDate();//즉, Date클래스의 day객체를 만들면서 생성자 Date(int year, int month, int day)를 호출한다 라는 뜻.
   
  day.AddYear(10);
  day.ShowDate();

  return 0;
}
생성자는 기본적으로 "객체 생성 시 자동으로 호출되는 함수"라고 볼 수 있다. 즉, 자동으로 호출되면서 객체를
초기화해주는 역활을 담당한다. 생성자는 객체를 초기화 하는 역활을 하기 때문에 리턴값이 없다!
생성자의 정의는 '클래스이름 (인자) {}로' 정의한다. 
생성자를 사용하는 방법으로
Date day(2011, 3, 1);과 같은 암시적 방법(implicit)과,
Date day=Date(2012,3,1);과 같은 명시적 방법(explicit)이 있다.
주로 암시적방법으로 축약해서 많이들 사용한다.
*/

/*4. 디폴트 생성자(Default constructor)
처음에 생성자 정의를 하지 않은 태로 Date day;를 할 때에서도 생성자는 호출된다.
이처럼 아무런 생성자를 정의하지 않는다면, 인자를 하나도 가지지 않는 생성자인 디폴트 생성자(default constructor)가 호출된다.
 이는 클래스에서 사용자가 어떠한 생성자도 명시적으로 정의하지 않았을 경우에 컴파일러가 자동으로 추가해주는 생성자이다.
**주의사항**_사용자가 다른 생성자를 추가하는 순간 컴파일러는 자동으로 디폴트 생성자를 삽입하지 않는다.

// 디폴트 생성자 정의해보기
#include <iostream>

class Date {
  int year_;
  int month_;  // 1 부터 12 까지.
  int day_;    // 1 부터 31 까지.

 public:
  void ShowDate();

  Date() {//인자를 갖지 않는 생성자를 정의. 
    year_ = 2012;
    month_ = 7;
    day_ = 12;
  }
};

void Date::ShowDate() {
  std::cout << "오늘은 " << year_ << " 년 " << month_ << " 월 " << day_
            << " 일 입니다 " << std::endl;
}

int main() {
  Date day = Date();//명시적인 방법으로 생성자 호출 
  Date day2;//암시적인 방법으로 생성자 호출_애초에 정의된 생성자에 인자가 없음. 
  Date day3();//인자가 있는 것 처럼 하면, default생성자로 초기화 하는 것이 아니라,
  //리턴값이 Date고, 인자가 없는 함수 day3을 정의하게 된 것으로 인식함. 이는 암시적표현으로
  //객체를 선언할 때 주의해야하는 사항. 
  //즉 위와같이 day3은 함수를 정의하는 것으로 알아들음. 고로 default 생성자를 암시적 표현으로 쓸때는
  //Date day2처럼 명확하게 인자가 없다고 보여주자. 

  day.ShowDate();
  day2.ShowDate();
  day3.ShowDate();
  return 0;
}
*/

/*5. 명시적으로 디폴트 생성자 사용하기.
C++11 이전으로는 default생성자를 사용하고 싶을 땐, 그냥 생성자를 정의하지 않는 방법 밖에 없었는데,
그러자 코드를 읽는 사용자가 이 개발자가 생성자를 잊어서 정의를 안한 것인지, 디폴트 생성자를 사용하고
싶어서 의도 한 것인지를 햇갈려하기 시작함. 그래서 C++ 11부터 디폴트 생성자를 명시적으로 사용할 수 있게됨.
class Date{
	public:
	Date()=default;//디폴트 생성자를 정의해라. 
};
즉 Date에 인자가 없이 들어오면 받아줄 인자없는 생성자를 정의하는데, 이 생성자를 default로 정의한다. 
*/

/*6. 생성자 오버로딩
#include <iostream>

class Date {
  int year_;
  int month_;  // 1 부터 12 까지.
  int day_;    // 1 부터 31 까지.

 public:
  void ShowDate();

  Date() {//생성자 역시 함수기에 오버로딩이 가능. 
    std::cout << "기본 생성자 호출!" << std::endl;
    year_ = 2012;
    month_ = 7;
    day_ = 12;
  }

  Date(int year, int month, int day) {//인자가 다르면 다른 함수로 취급하는 함수 오버로딩. 
    std::cout << "인자 3 개인 생성자 호출!" << std::endl;
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
  std::cout << "오늘은 " << year_ << " 년 " << month_ << " 월 " << day_
            << " 일 입니다 " << std::endl;
}
int main() {
  Date day = Date();
  Date day2(2012, 10, 31);

  day.ShowDate();
  day2.ShowDate();

  return 0;
}
*/

//7. 생각해보기. 
#include <iostream>

class Point {//클래스 Point정의 
  int x, y;//점의 x값과 y값을 나타내는 맴버변수 x, y 정의. 

 public:
  Point(int pos_x, int pos_y){//생성자 정의. 
  	x=pos_x;
  	y=pos_y;
  }
  
  void View(){//좌표 뷰어 함수 
  	std::cout<<"x: "<<x<<", y: "<<y<<std::endl;
  }
};

class Geometry {//점들을 연산할 클래스 Geometry정의. 
 public:
  Geometry() {//생성자. Geometry객체를 생성하면 갖고있는 점의 개수를 0으로 초기화한다. 
    num_points = 0;
  }

  void AddPoint(const Point &point) {//Point자료형을 const로 참조자point로 가져온다. 
    point_array[num_points ++] = new Point(point.x, point.y);
  }

  // 모든 점들 간의 거리를 출력하는 함수 입니다.
  void PrintDistance();

  // 모든 점들을 잇는 직선들 간의 교점의 수를 출력해주는 함수 입니다.
  // 참고적으로 임의의 두 점을 잇는 직선의 방정식을 f(x,y) = ax+by+c = 0
  // 이라고 할 때 임의의 다른 두 점 (x1, y1) 과 (x2, y2) 가 f(x,y)=0 을 기준으로
  // 서로 다른 부분에 있을 조건은 f(x1, y1) * f(x2, y2) <= 0 이면 됩니다.
  void PrintNumMeets();

private:
  // 점 100 개를 보관하는 배열.
  Point* point_array[100];//점의 정보를 담을 Point자료형의 포인터를 배열 100칸으로 선언. 
  int num_points;//점의 개수를 담을 변수. 
};

int main(){
	return 0;
} 




/*정리
1. 함수의 오버로딩(overloading)이란 같은 이름의 함수더라도 인자가 다르면 다른 함수로 판단하여 자료형별로 같은 작업을 처리하는 함수의 이름을 같게 설정할 수 있는 것이다.
	[C++에서 함수를 오버로딩 하는 과정]
	1단계: 자신과 타임이 정확히 일치하는 함수를 찾는다.
	2단계: 정확히 일치하는 타입이 없는 경우 형변환을 통해서 일치하는 함수를 찾아본다.
		1. Char, unsigned char, short 는 int 로 변환된다.
		2. Unsigned short 는 int 의 크기에 따라 int 혹은 unsigned int 로 변환된다.
		3. Float 은 double 로 변환된다.
		4. Enum 은 int 로 변환된다.
	3단계: 좀 더 포괄적인 형변환을 통해 일치하는 함수를 찾아본다.
		1. 임의의 숫자(numeric) 타입은 다른 숫자 타입으로 변환된다. (예를 들어 float -> int)
		2. Enum 도 임의의 숫자 타입으로 변환된다 (예를 들어 Enum -> double)
		3. 0 은 포인터 타입이나 숫자 타입으로 변환된 0 은 포인터 타입이나 숫자 타입으로 변환된다
		4. 포인터는 void 포인터로 변환된다.
	4단계: 유저 정의된 타입 변환으로 일치하는 것을 찾는다.
	1~4단게에서 해결되지 않으면, 모호하다라고 판단하여 오류 발생. 
	*오버로딩 규칙을 정확히 숙지하지 않고 사용하면, 여러 함수의 오버로딩에서 많은 ambigous error를 야기한다.
2. 클래스 내에 복잡한 함수를 정의할 때, 가시성을 향상시키기 위해 클래스 밖에 구체적인 함수의 몸통을 작성한다. 
	class Date{
	void show(int year, int month, int day);
	}
	
	void Date::show(int year, int month, int dat){
	알맹이~~함수의 몸통! 
	}
3. 생성자(Constructor)는 객체 생성 시 자동으로 호출되는 함수이며, public:안에 클래스이름(인자{} 꼴로 정의한다. 
   생성자를 호출하는 방법으로, 명시적 방법(explicit)_Date day=Date(2012,3,1)과 암시적 방법(implicit)_Date day(2011, 3, 1);이 있다.
4. 디폴트 생성자(Default constructor)는 클래스에서 사용자가 어떠한 생성자도 명시적으로 정의하지 않았을 경우에 컴파일러가 자동으로 추가해주는 생성자이다.
   컴파일러가 만들어주는 디폴트 생성자는 아무것도 안하지만, 기존의 생성자에서 인자를 빼어 디폴트 생성자를 별도로 정의할 수 있다. 
   사용자가 생성자를 만들어주는 순간 컴파일러는 디폴트 생성자를 별도로 만들어주지 않는다.
   디폴트 생성자를 사용할 때, 주의사항이 있는데, main()애서 선언 시 Date day=Date()나 Date day2로 사용해야지, Date day3();이라고 사용해버리면 반환형이 Date인 함수 day3의 선언이라고 생각해버리니 주의. 
   즉, 디폴트 생성자를 사용할 때, 명확하게 인자가 없다고 Date day2처럼 사용해야지 괜히 있는 것처럼 Date day2()로 사용하지 말자. 
5. 디폴트 생성자를 일부러 사용했다고 코드상에 보여주기 위하여 명시적으로 default생성자를 정의할 수 있는데, 생성자 정의 자리에(public:) Date()=default;로 표현한다. 
6. 생성자 역시 함수이기 때문에 인수가 다르면 다른 함수로 취급하는 생성자 오버로딩(overloading)이 가능하다. 
*/ 
