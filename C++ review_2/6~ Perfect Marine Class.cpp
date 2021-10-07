#include <iostream>

class Marine{
	static int total_marine_num;//variable in Marine "class" not "object" because of static keyword. 
	const static int i=0;//const static can be initialized in class directly.
	
	int hp;
	int coord_x, coord_y;
	bool is_dead;
	
	const int default_damage;
	
	public:
		Marine();
		Marine(int x, int y);
		Marine(int x, int y, int default_damage);
		Marine(const Marine& mr);
		~Marine(){ total_marine_num--; }
		
		int attack() const;
		Marine& be_attacked(int damage_earn);//update this object by return of reference with *this
		void move(int x, int y);
		void show_status();
		
		static void show_total_marine();//static function in Marine "class" not "object"
};
int Marine::total_marine_num=0;//initialization of static variable
void Marine::show_total_marine(){
	std::cout<<"count of all marines : "<<total_marine_num<<std::endl;
} 

Marine::Marine():hp(50), coord_x(0), coord_y(0), default_damage(5), is_dead(false){ total_marine_num++; }
Marine::Marine(int x, int y):coord_x(x), coord_y(y), hp(50), default_damage(5), is_dead(false){ total_marine_num++; }
Marine::Marine(int x, int y, int default_damage):coord_x(x), coord_y(y), hp(50), default_damage(default_damage), is_dead(false){ total_marine_num++; }
Marine::Marine(const Marine& mr):hp(mr.hp), coord_x(mr.coord_x), coord_y(mr.coord_y), default_damage(mr.default_damage), is_dead(mr.is_dead){ total_marine_num++; }
void Marine::move(int x, int y){ coord_x=x; coord_y=y; }
int Marine::attack() const{return default_damage; }
Marine& Marine::be_attacked(int damage_earn){
	hp-=damage_earn;
	if(hp<=0)
		is_dead=true;
	
	return *this;
}
void Marine::show_status(){
	std::cout<<"***Marine Status***\n";
	std::cout<<"Location: ("<<coord_x<<", "<<coord_y<<") \n";
	std::cout<<"HP: "<<hp<<std::endl;
	std::cout<<"[all number of marine now : "<<total_marine_num<<"]"<<std::endl;
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
/*
1.	리턴타입이 레퍼런스가 아닌 경우에 임시 복사생성 객체에 함수를 사용하는 것을 유의하자.
2.	불필요한 복사를 막기위한 컴파일러의 복사생략(copy slision) 예시 
 	A get_A() {
	    A temp(a);
	    return temp;//not copy temp object when returnnig! just return temp's pointer
	}
*/
