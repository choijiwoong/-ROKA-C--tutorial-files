/*1. 스타크래프트 만들기 
#include <iostream>
#include <string.h>//마린의 이름 만들기 

class Marine{
	int hp;//marin's hp
	int coord_x, coord_y;//marin's location
	int damage;//attack ability
	bool is_dead;
	char* name;//marine's name
	
	public:
		Marine();//default constructor 
		Marine(int x, int y);//make marin in x,y location
		Marine(int x, int y, const char* marine_name);//make with name 
		~Marine();//2. Destructor
		
		int attack();//return damage
		void be_attacked(int damage_earn);//gain damage
		void move(int x, int y);//new location
		
		void show_status();//show status
};

Marine::Marine(){
	hp=50;
	coord_x=coord_y=0;
	damage=5;
	is_dead=false;
}
Marine::Marine(int x, int y, const char* marine_name){
	name=new char[strlen(marine_name)+1];//make space to enter name **name is made by char's array.->delete[]
	strcpy(name, marine_name);//copy
	//if we aren't use delete to new memory, no auto delete. 
	//when they increase in memory, it occur memory leak that it takes too many memory unnormally.
	coord_x=x;
	coord_y=y;
	hp=50;
	damage=5;
	is_dead=false;
}
Marine::Marine(int x, int y){
	coord_x=x;
	coord_y=y;
	hp=50;
	damage=5;
	is_dead=false;
}
void Marine::move(int x, int y){
	coord_x=x;
	coord_y=y;
}
int Marine::attack() { return damage; }
void Marine::be_attacked(int damage_earn){
	hp-=damage_earn;
	if(hp<=0) is_dead=true;
}
void Marine::show_status(){
	std::cout << " *** Marine : " << name << " ***" << std::endl;
	std::cout<<" Location : ( "<<coord_x<<" , "<<coord_y<<" ) "<<std::endl;
	std::cout<<" HP : "<<hp<<std::endl;
}
Marine::~Marine(){
	std::cout << name << " 의 소멸자 호출 ! " << std::endl;
	if(name!=NULL){
		delete[] name;//name자체가 string이 아닌 char의 배열로써 new됨. 꼭 delete[] 
	}
}
int main(){
	Marine* marines[100];//많은 마린들을 담기 위해 배열로 Marine들을 저장. 
	
	marines[0] = new Marine(2, 3, "Marine 2");//생성자를 자동으로 호출해줌. C++에 맞는 새로운 동적할당 
    marines[1] = new Marine(1, 5, "Marine 1");
	
	marines[0]->show_status();//포인터를 가리키는 배열이기에 메소드 호출 시 .이 아니라 ->을 사용해야한다. 
	marines[1]->show_status();
	
	std::cout <<std::endl<<"마린 1이 마린 2를 공격! "<<std::endl;
	
	marines[0]->be_attacked(marines[1]->attack());
	
	marines[0]->show_status();
	marines[1]->show_status();
	
	delete marines[0];//동적할당 메모리 항상 해제 
	delete marines[1];
	return 0;
}
//
1. C++의 경우 malloc과 다르게 new는 객체를 동적으로 생성 시 자동으로 생성자도 호출해줌.
2. 명확히 delete를 하지 않는 한 자동으로 delete가 되는 경우는 없기에, 저 공간은 영원히 메모리 공간 속에서 둥둥
   떠다니게 됨. 이러한 것들이 쌓이면 비정상적으로 많은 메모리를 점유하는 메모리 누수(Memory Leak)의 문제점이 발생.
3. 그래서 C++에서는 main함수 끝에서 Marine이 delete될 때, 즉 생성했던 객체가 소멸될 때 자동으로 호출되는 함수로써 소멸자(Destructor)을 지원.
    생성자가 클래스 이름과 똑같이 생겼다면, 소멸자는 그 앞에 ~를 붙여서 표시함. ex)~Marine(); 
4. 소멸자는 주로 동적으로 할당받은 메모리를 해제하는 일과, 쓰레드 사이에서 lock된 것을 푸는데 사용한다.
	참고로, 생성자를 정의하지 않고도 default constructor가 있던 것 처럼, default destructor가 있다.
	대신 차피 소멸하는 것이기에 아무 작업도 수행하지 않기에 소멸자가 필요없는 클래스라면 굳이 클래스를
	명시하지 않는다. 
 */
 
 
/* 3.소멸자 호출 확인하기
#include <string.h>
#include <iostream>

class Test {
  char c;

 public:
  Test(char _c) {
    c = _c;
    std::cout << "생성자 호출 " << c << std::endl;//생성자 호출 cout 
  }
  ~Test() { std::cout << "소멸자 호출 " << c << std::endl; }//소멸자 호출 cout 
};
void simple_function() { Test b('b'); }//함수가 호출되면 Test클래스 'b'를 만듬. 근데 함수가 끝나며
									   //바로 b의 객체가 사라지므로 b의 소멸자 호출. because b is local object 
int main() {
  Test a('a');//객체 a의 생성 
  simple_function();//객체 b의 생성과 소멸 
}//객체 a의 소멸 
line114에서 Test객체 'a'생성.
line115에서 simple_function()호출 
그래서 코드 실행 시  
생성자 호출 a 
생성자 호출 b
소멸자 호출 b_지역객체이기에 함수가 끝나며 소멸 
소멸자 호출 a 순으로 출력됨.  _메인함수가 끝나며 소멸 
*/

/*4. 복사 생성자(copy constructor)
//포토캐논
#include <iostream>
#include <string.h>

class Photon_Cannon{
	int hp, shield;
	int coord_x, coord_y;
	int damage;
	
	char *name;//name
	
	public:
		Photon_Cannon(int x, int y);
		Photon_Cannon(int x, int y, const char *cannon_name);//if name, make with name
		~Photon_Cannon();//destructor 
		//Photon_Cannon(const Photon_Cannon& pc); _for check limit of default copy constructor->for use default
		Photon_Cannon(const Photon_Cannon& pc);//sol. 
		
		void show_status();
}; 
<각주처리시작> 
//for use default copy constructor
Photon_Cannon::Photon_Cannon(const Photon_Cannon& pc){//standard definition of cpyt constructor
	std::cout<<"복사 생성자 호출 !"<<std::endl;//얘 지우면 Photon_Cannon's default copy constructor structure. 
	hp=pc.hp;
	shield=pc.shield;
	coord_x=pc.coord_x;
	coord_y=pc.coord_y;
	damage=pc.damage; 
}
<각주처리 종료>
Photon_Cannon::Photon_Cannon(const Photon_Cannon &pc){
	std::cout<<"복사 생성자 호출! "<<std::endl;
	hp = pc.hp;
  	shield = pc.shield;
  	coord_x = pc.coord_x;
  	coord_y = pc.coord_y;
  	damage = pc.damage;
	
	name=new char[strlen(pc.name)+1];//복사 생성자에서 name에서 deep copy를 위해 new. 
	strcpy(name,pc.name);//content copy. same code with constructor in name. 복사 과정서 따로 메모리를 생성. 
}
Photon_Cannon::Photon_Cannon(int x, int y) {
  std::cout << "생성자 호출 !" << std::endl;
  hp = shield = 100;
  coord_x = x;
  coord_y = y;
  damage = 20;
}
Photon_Cannon::Photon_Cannon(int x, int y, const char *cannon_name) {//constructor with name
  hp = shield = 100;
  coord_x = x;
  coord_y = y;
  damage = 20;
  
  name=new char[strlen(cannon_name)+1];
  strcpy(name, cannon_name);
}
Photon_Cannon::~Photon_Cannon(){
	if (name) delete[] name;
}
void Photon_Cannon::show_status() {
  std::cout << "Photon Cannon " << std::endl;
  std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) "
            << std::endl;
  std::cout << " HP : " << hp << std::endl;
}
int main() {
  Photon_Cannon pc1(3, 3);
  Photon_Cannon pc2(pc1);
  Photon_Cannon pc3 = pc2;//***C++컴파일러는 이 문장을 Photon_Cannon pc3(pc2);과 똑같이 해석함.
  //이는 아주 특별한 경우로 만약  pc=pc2;를 했다면 단순한 대입연산이겠지만, Photon_Cannon pc3=처럼
  //생성 시에 대입하는 연산을 하면 복사 생성자가 호출되게 됨. 

  pc1.show_status();
  pc2.show_status();
  
  std::cout<<std::endl;
  //for check limit of default copy constructor
  Photon_Cannon pc4(3,3,"Cannon");
  Photon_Cannon pc5=pc4;
  
  pc4.show_status();
  pc5.show_status();
  //원래는 실행하면 runtime error. 근데 해보니 그냥 return 쓰레기값뜨긴하지만 실행은 됨. 여튼 에러. 
}
*/

/*
1. T(const T& a);이 복사 생성자의 표준적인 정의이다. 
   이는 다른 T의 객체 a를 상수 레퍼런스로 받는다는 뜻. 즉 복사생성자 내부에서 a의 데이터를 변경불가하고,
   오직 새롭게 초기화되는 인스턴스 변수들에게 복사만 할 수 있게 된다.
   p.s 어지간하면 함수 내부에서 받은 인자의 값을 변환시키는 일이 없다면 const를 붙이는 습관을 기르자.(실수방지)
2. Photon_Cannon pc3=pc2;처럼 생성시에 대입하는 연산 시 복사 생성자를 호출하게 됨. 대입 연산이 아님. 
3.	Photon_Cannon pc3 = pc2; 와  

	Photon_Cannon pc3;
	pc3 = pc2;는 엄연히 다른 문장임.
	선자는 복사 생성자가 1번 호출되는 것이고, 후자는 생성자가 1번 호출되고, pc3=pc2;라는 명령이 실행되는 것.
	이 차이는 복사 생성자나 생성자에 단순히 값을 넣는 작업 말고 다른 작업을 추가했을 시 
	ex) 생성할때 cout생성되었습니다!or 복사할때 객체를 담는 배열에 +1한다던가
	코드가 꼬일 수 있음. 생성할 때 하는 작업과 복사할 때 하는 작업이 다른데, 선자와 후자를 혼용하면,
	논리오류의 향연이 펼쳐질 것.
4. C++컴파일러에서 또 또 또근수? default copy constructor을 지원해주고 있음. 위의 코드에서 복사생성자를 지우고
	컴파일하면 이전과 정확히 동일한 결과가 나타남. 
	이전에 default constructor or destructor는 아무 기능이 없던 반면에, default copy constructor는
	실제로 복사를 해준다.(대응되는 원소들을 1대1복사.)
	즉. 간단한 클래스의 경우 복사생성자를 생성하지 않고도 default copy constructor을 이용하여 쉽게 copy할 수 있음. 
5.	*Limit of default copy constructor*
	default copy constructor는 솔직한 1대1 대응 복사를 해줌. 즉 copy constructor에서 name을
	hp=pc.hp;하듯 name=pc.name;으로 처리함. 
	ex)
		Photon_Cannon::Photon_Cannon(const Photon_Cannon& pc) {
  		hp = pc.hp;
  		shield = pc.shield;
  		coord_x = pc.coord_x;
  		coord_y = pc.coord_y;
  		damage = pc.damage;
  		name = pc.name;
		}
    이러면 name은 char의 array니까 name자체의 값은 주소를 갖게 되고, 
	pc4의 name주소를 그대로 pc5의 name주소에 대입한 꼴이 된다.
	즉, pc4와 pc5는 pc4의 name 주소하나를 가리키고 있는 것임. 즉, 동적할당받은 pc4의 메모리를 pc5의 메모리
	역시 같이 가리키게 되는 것. 
	 같은 메모리를 두개의 포인터가 가리키는 것은 단순히 실행에서는 별 문제가 되지 않는다. 
	다만 소멸자에서 큰 문제가 발생하게 된다.
	  main()함수가 종료되기 직전에 생성되었던 객체들은 파괴되면서 소멸자를 호출하게 되는데, 만약 pc4가
	먼저 파괴되었다고 가정해보자. 그럼 pc4의 내용을 모두 파괴함과 동시에 name에 할당되었던 메모리 역시 
	delete하게 된다. 그런데 그 뒤 pc5의 name이 이미 앞에서 해제된 메모리를 가리키고 있다는 것. 
	그렇다면 pc5의 소멸자가 호출되며 name은 이미 해제된 메모리의 주솟값을(NULL이 아니다)가리키고 있기 때문에
	if문을 통하여 delete연산이 수행되게 되고, 그렇다면 이미 해제된 메모리에 접근하여 다시 해제하려 하고 있기에
	런타임 에러가 발생하게 된다.(일단 해제된 메모리에 접근하려 한다는 것 자체가 이미 오류다.) 
	 이러한 문제를 해결하기 위하여 복사 생성자에 name을 그대로 복사하는 것이아니라, 따로 다른 메모리에
	동적할당(new)하여 그 내용만 복사하면 된다. 
	 이처럼 메모리를 새로 할당하여 내용을 복사하는 것을 깊은 복사(deep copy), 아까처럼 단순히 대입만 해주는
	것을 얕은 복사(shallow copy)라고 부른다.
	 즉, 컴파일러의 default copy constructor는 단순한 대입의 얕은복사밖에 할 수 없기에 위처럼 깊은 복사가
	필요할 경우, 사용자가 직접 복사 생성자를 만들어야 한다. 
6.	C++에서는 std::string이라는 훌륭한 문자열 클래스를 제공하기 때문에, C처럼 null종료로 char 배열을 다루는 것을 비추한다. 
*/

//6. 생각해보기
#include <iostream>

class string{
	char *str;
	int len;
	
	public:
		string(char c, int n);//문자 c가 n개 있는 문자열로 정의
		string(const char *s);
		string(const string &s);
		~string();
		
		void add_string(const string &s);//str뒤에 s를 붙인다.
		void copy_string(const string &s);//str에 s를 복사한다.
		int strlen();//문자열 길이 리턴 
}; 

int main(){
	
	return 0;
}
