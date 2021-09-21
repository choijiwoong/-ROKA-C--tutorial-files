#include <iostream>

//1 perfect Marine
class Marine{
	static int total_marine_num;//variable in Marine "class" not "object" because of static keyword. 
	const static int i=0;//const static can be initialized in class directly.
	
	int hp;
	int coord_x, coord_y;
	bool is_dead;
	
	const int default_damage;//protect mistake of programmer by const
	
	public:
		Marine();
		Marine(int x, int y);
		Marine(int x, int y, int default_damage);
		Marine(const Marine& mr);
		~Marine(){ total_marine_num--; }//for static variable for expression of all marines.
		
		int attack() const;//const member function that doesn't change any value.
		Marine& be_attacked(int damage_earn);//return type is reference for protection to copy of temporary object.
		void move(int x, int y);
		void show_status();
		
		static void show_total_marine();//static function in Marine "class" not "object"
};
int Marine::total_marine_num=0;//static variable. we can approach by :: of Marine class
void Marine::show_total_marine(){
	std::cout<<"count of all marines : "<<total_marine_num<<std::endl;
} 

Marine::Marine():hp(50), coord_x(0), coord_y(0), default_damage(5), is_dead(false){ total_marine_num++; }
Marine::Marine(int x, int y):coord_x(x), coord_y(y), hp(50), default_damage(5), is_dead(false){ total_marine_num++; }
Marine::Marine(int x, int y, int default_damage):coord_x(x), coord_y(y), hp(50), default_damage(default_damage), is_dead(false){ total_marine_num++; }
Marine::Marine(const Marine& mr):hp(mr.hp), coord_x(mr.coord_x), coord_y(mr.coord_y), default_damage(mr.default_damage), is_dead(mr.is_dead){ total_marine_num++; }
void Marine::move(int x, int y){ coord_x=x; coord_y=y; }
int Marine::attack() const{return default_damage; }
Marine& Marine::be_attacked(int damage_earn){//retype is reference for reducing needless copy by temporary object(prevention of error too)
	hp-=damage_earn;
	if(hp<=0)
		is_dead=true;
	
	return *this;//return this object
}
void Marine::show_status(){
	std::cout<<"***Marine Status***\n";
	std::cout<<"Location: ("<<coord_x<<", "<<coord_y<<") \n";
	std::cout<<"HP: "<<hp<<std::endl;
	std::cout<<"[all number of marine now : "<<total_marine_num<<"]\n";
}

int main(){
	Marine marine1(2,3,5);
	marine1.show_status();
	
	Marine marine2(marine1);
	marine2.show_status();
	
	std::cout<<std::endl<<"marine1 attack marine2 two times"<<std::endl;
	marine2.be_attacked(marine1.attack()).be_attacked(marine1.attack());
	
	marine1.show_status();
	marine2.show_status();
}

/*_copy elision_ that compiler prevents needless copy 
B(const B& b) : a(b.a) {}
  A get_A() {
    A temp(a);
    return temp;
} */



/*
1.	초기화 리스트(initializer list)는 생성자 호출과 동시에 멤버 변수들을 초기화하기에 기존의 생성 후 대입하는 방법에 비해 효율적이다. 
	또한 상수와 레퍼런스들은 모두 생성과 동시에 초기화가 되어야 한다. 즉 초기화 리스트를 이용하자.
2.	리턴타입이 레퍼런스가 아닌 경우에 임시 복사생성 객체에 함수를 사용하는 것을 유의하자. 
3.	상수멤버함수는 int attack() const;꼴로 정의하며 다른 변수의 값을 바꾸지 않는 함수를 표시한다. 
4.	static은 0으로 자동 초기화된다.
 
1.	C언어의 문자열 표현방식을 널 종료 문자열(Null-terstd::minating string)이라고 한다. 이는 문자열 병합이나 크기 변경에 귀찮다. 
2.	capacity의 도입은 전에 할당하였다가 사용하지 않는 공간을 다시 사용할때, 재할당의 비효율성을 줄이기위해 사용한다. 이 할당의 효율성을 보다 높이기 위해 reserve를 사용하며 가용크기를 사용크기의 2배정도로 낭낭하게 할당한다. 
	애초에 크기가 capacity의 2배를 넘는다면 불필요한 allocation을 막기 위해 필요한 만큼만 할당한다 
3.	대입과 같은 의미로 assign()함수를 사용할 수 있다. 
*/
