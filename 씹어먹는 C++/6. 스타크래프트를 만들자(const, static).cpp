/*1. 생성자의 초기화 리스트(initializer list)
#include <iostream>

class Marine {
  static int total_marine_num;//static멤버변수 
  const static int i=0;//선언하면서 초기화하 가능한 경우. 
   
  int hp;                // 마린 체력
  int coord_x, coord_y;  // 마린 위치
  //int damage;            // 공격력
  bool is_dead;
  
  const int default_damage;  // 기본 공격력_프로그래머의 실수 방지. 
  
 public:
  Marine();              // 기본 생성자
  Marine(int x, int y);  // x, y 좌표에 마린 생성
  Marine(int x, int y, int default_damage);
  
  //int attack(); 
  int attack() const;// 데미지를 리턴한다. const 함수. 
  //void be_attacked(int damage_earn);  // 입는 데미지
  Marine& be_attacked(int damage_earn);//입는 데미지 
  void move(int x, int y);            // 새로운 위치

  void show_status();  // 상태를 보여준다.
  static void show_total_marine();//class static function
  ~Marine() { total_marine_num--; }
};
int Marine::total_marine_num=0;//static total variable을 0으로 initialize.
//모든 전역 및 static variable은 정의와 동시에 0으로 초기화 되기에 초기화를 따로 안해줘도 되지만,
//class's static variable의 경우 위와 같이 초기화 함. 
void Marine::show_total_marine(){
	//std::cout<<default_damage<<std::endl; 처럼 static함수에서 멤버변수를써버리면 누구의 변수인지 몰라 오류. 
	std::cout<<"전체 마린 수: "<<total_marine_num<<std::endl;
}

//기본 공격력을 실수방지를 위해 const로 썼으니 생성과 동시에 초기화해줘야 함. 초기화 리스트로 생성자 구성. 
Marine::Marine() : hp(50), coord_x(0), coord_y(0), default_damage(5), is_dead(false) {
	total_marine_num++;//constructor call->plus 1 to static variable
}//함수 본체에 아무것도 업따??! 
//생성자 뒤에 :hp(50), 이런 꼴을 초기화리스트(initializer list)라고 부르며, 호출과 동시에 멤버변수 초기화. 
Marine::Marine(int x, int y)//이런꼴로 대입도 가능. 
    : coord_x(x), coord_y(y), hp(50), default_damage(5), is_dead(false) {
	total_marine_num++;//constructor call->plus 1 to static variable
}
Marine::Marine(int x, int y, int default_damage)
	:coord_x(x),
	coord_y(y),
	hp(50),//const int default_damage=(인자로 받은)default_damage;와 같음.  
	default_damage(default_damage),//초기화 리스트를 사용하여 const를 저장하는 것은  
	is_dead(false) {
	total_marine_num++;//constructor call->plus 1 to static variable
}

void Marine::move(int x, int y) {
  coord_x = x;
  coord_y = y;
}
int Marine::attack() const{ return default_damage; }//다를게 없고 걍 선언만 다름 
Marine& Marine::be_attacked(int damage_earn){//참조자로 Marine객체를 반환할 예정. 
	
	hp-=damage_earn;//this->hp-=damage_earn; 값을 this포인터로 접근하여 변경 후 
	if (hp<=0) is_dead=true;//if (this->hp<=0) this->is_dead=true;
	
	return *this;//포인터의 값을 레퍼런스로 리턴. 즉, 객체 자기 자신의 참조자를 리턴. 
}
<각주시작> 
void Marine::be_attacked(int damage_earn) {//위에 함수로 대체 
  hp -= damage_earn;
  if (hp <= 0) is_dead = true;
}<각주끝> 

void Marine::show_status() {
  std::cout << " *** Marine *** " << std::endl;
  std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) "
            << std::endl;
  std::cout << " HP : " << hp << std::endl;
  std::cout << " 현재 총 마린 수 : " << total_marine_num << std::endl;//total print show
}
void create_marine() {
  Marine marine3(10, 10, 4);
  //marine3.show_status();
  Marine::show_total_marine();
}


int main() {
  Marine marine1(2, 3, 5);
  marine1.show_status();

  Marine marine2(3, 5, 10);
  marine2.show_status();
  
  std::cout << std::endl << "마린 1 이 마린 2 를 두 번 공격! " << std::endl;
  marine2.be_attacked(marine1.attack()).be_attacked(marine1.attack());
  //marine이 어택받고 반환하는게 마린2의 참조자이기에 그냥 마린2로 치환해서
  // marine2.be_attacked(marine1.attack())이 먼저 실행되고, 값은 마린2의 값이라
  //marine2.be_attacked(marine1.attack());가 이후에 실행된다고 보면 됨. 즉 마린2가 딜 2번 받음. 
  //만약에 marine의 be_attack()의 반환형을 Marine&이 아닌 Marine으로 한다면 전자 실행 후 임시객체 Marine이
  //호출되고 임시객체를 어택하는 것이 되기에 marine2는 1번의 공격만 받게 됨. 
  
  std::cout<<std::endl; 
  marine1.show_status();
  marine2.show_status();
}

1. 아씨발 타로밀크티 존나 먹고싶다 날 내보내줘~~~
2. 초기화 리스트(initializer list)의 일반적인꼴_ 생성자이름 : var1(arg1), var2(arg2) {} 
   var1은 클래스의 멤버 변수이고, arg는 멤버변수를 초기화시킬 값이다.
    여기서 var1과 arg1의 이름이 같아도 된다. 왜냐면 우선적으로 받음 arg1의 값을 우선으로 지칭하기에. 
   만약 일반적으로 초기화 할때 (함수 본체 안에) coord_x=coord_x;라고 하면 오류가 난다. 모두 인자로 받은
   것으로 취급하기에.
    초기화리스트를 이용하는 이유는 생성과 초기화를 동시에 하기 때문이다. 일반적으로 생성자 함수 본체에
   값을 넣은 경우는 생성을 먼저 하고 그 다음에 대입연산자를 수행하는 것이다. 즉, 초기화리스트는 int a=10;
   과 같고, 생성자 본체를 이용할 경우 int a; a=10;과 같다. 이것을 클래스로써 생각하면, 초기화리스트를 사용하면
   복사생성자가 호출되는데, 후자의 경우 디폴트 생성자가 호출된 다음, 대입이 수행된다는 것이다. 즉 후자의
   작업이 조금 더 많게 된다. ->초기화리스트가 효율적이다. 
    또다른 이유는 레퍼런스나 상수의 경우 '반드시 생성과 동시에 초기화'되어야 하는데, 초기화리스트를 사용하지
   하지않는다면, 오류가 날 것이다. 그리하여 클래스 내부에 레퍼런스 변수나 상수를 넣는다면, 무조건 초기화 리스트를
   사용해야 한다. 
    이처럼 중요한 값을 상수로 처리하는 것은 매우 유용한 일이다. 실수로 default_damage의 값을 변경하여
   오류가 어디서 발견했는지 일일히 찾는 것보다 컴파일 오류가 뜸으로 써 효율적으로 디버깅을 할 수 있다. 
*/

//2. 생성된 총 'Marine' 수 세기(static 변수)
// static 멤버 변수의 사용

/*
1. 일반적으로 총 Marine의 개수를 알아내는데에는 
	1) 배열에 Marine을 보관하고 생선된 마린의 개수를 모두 셈._크기가 자유자재로 변하는 배열 필요.(벡터로 해결가능하긴 함) 
	2) 어떤 변수를 만들어서 Marine이 생성되면 +1, 소멸시에 -1_다른 함수에서 사용 시 인자로 계속 전달해야댐 
	3) 전역변수 생성_코드크기에 비례하여 실수로 인한 오류가능성이 증가. 
2. C++에서는 전역변수 같으면서도 클래스 하나에만 종속되는 변수인 static 멤버 변수를 제공하고 있다.
   p.s C에서는 프로그램 종료시까지 사라지지 않게 하는데 static 사용
   이와 비슷하게, C++에서 클래스의 static 멤버변수의 경우 객체가 사라질 때가 아닌 프로그램이 종료될 때 소멸되며,
   모든 객체들이 하나의 static멤버변수를 사용하게 된다. 
3. Class static variable은 초기화 시 int Marine::total_marine_num=0;과 같이 초기화 한다.
   당연히 클래스 내부에서 static int total_marine_num=0;처럼 초기화는 불가능하다.
   클래스 내부에서 초기화가 위처럼 가능한 꼴은 const static int x=0;이 유일하다.?? what is it.? 
4. 클래스 안에 static 변수처럼 클래스 전체에 딱 1개 있는 static 함수도 있다. 즉, 멤버 함수의 경우, 객체를
   만들어야만 각 멤버함수들을 호출할 수 있지만, static함수는 객체가 없어도 그냥 클래스 자체에서 호출할 수 있다.
   Marine::show_total_marine();과 같이 호출함._어느 객체도 함수를 갖고 있기 때문에. 

3. this. C++에서 언어적 차원으로 객체 자기 자신을 가리키는 포인터. 
   구조체 포인터 변수에서 ->하여 구조체 원소들에 접근했던 것 처럼, 클래스 맴버함수를 this->arg로 접근 가능.

5. const 함수_ C++에서 변수들의 값을 바꾸지 않고 읽기만 하는. 상수같은 멤버함수를 상수함수로써 선언이 가능하다. 
   (기존 함수의 정의) const;로 선언을 하게 됨.
   또한 아래와 같이 함수의 정의 역시 const키워드를 넣어줘야함
   int Marine::attack() const {return default_damage;} 
    이러한 규칙을 통해 attack함수는 '상수 멤버 함수'로 정의된 것이다. 즉 다른프로그래머에게 이 함수는
   다른 변수의 값을 바꾸지 않는 함수이다 라는 것을 알려 줄 수 있다. 
*/

/*4. 레퍼런스를 리턴하는 함수 
#include <iostream>

class A{
	int x;//member variable 'x' 
	
	public:
		A(int c): x(c) {}//constructor. int와 생성하면, 초기화리스트를 이용하여 x를 c로 초기화
		
		int& access_x() { return x; }//object's x to return by reference
		int get_x() { return x; } //just return int x
		void show_x() { std::cout << x <<std::endl; }//x show
};

int main(){
	A a(5);//define and initialize a
	a.show_x();
	
	int& c=a.access_x();//a의 x를 ref로 c에 저장 
	c=4;//a의 x를 ref로 받은 후 변경이기에  
	a.show_x();//a의 값이 변경 
	
	int d=a.access_x();//a의 x를 ref로 반환한 것을 ref 가 아닌 int로 받음->***값의 복사가 이루어짐.***
	d=3;//d값 변경 
	a.show_x();//a값 변경안됨. 
	
	//아래는 오류_error C2440: 'initializing' : cannot convert from 'int' to 'int &'
	//int& e=a.get_x();//a의 x값을 참고자로 받음 (오류) 문장이 끝나면 a.get_x()값을 가진 임시int가 사라짐.근데 그걸 ref로 받음 
	//e=3;//즉 위의 경우 어찌어찌 ref가 받았다고 해도 값이 존재하지 않는 ref이기에 접근 시 오류. 
	//a.show_x();//좀 더 자세히 말하면 int&은 좌측값의 ref고, a.get_x()는 우측값이기에 안된다.(추후 설명) 
	
	int f=a.get_x();//a의 값을 int f에 저장 
	f=1;//f 변경 
	a.show_x() //당연히 a 그대로 
	
	//a.get_x()=3;당연히 오류. 
	
	return 0;
}
*/

//6. 생각해보기_복사생성이 몇번 표시되는지? 
#include <iostream>

class A{
	int x;
	
	public:
		A(int c):x(c) {}//initializer list
		A(const A& a){
			x=a.x;//대입 복사. 
			std::cout<<"복사 생성"<<std::endl;
		}
}; 

class B{
	A a;
	
	public:
		B(int c):a(c) {}//initializer list
		B(const B& b): a(b.a) {}//B's copy constructor
		A get_a(){//반환형이 A이고, get_a()로 호출. 
			A temp(a);//A클래스를 가지는 객체 temp를 생성하는데, a가 인수임. 
			return temp;//temp객체를 리턴함. 
		}
};

int main() {
  B b(10);

  std::cout << "---------" << std::endl;
  A a1 = b.get_A();
}
