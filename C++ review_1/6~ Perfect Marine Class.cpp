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
1.	�ʱ�ȭ ����Ʈ(initializer list)�� ������ ȣ��� ���ÿ� ��� �������� �ʱ�ȭ�ϱ⿡ ������ ���� �� �����ϴ� ����� ���� ȿ�����̴�. 
	���� ����� ���۷������� ��� ������ ���ÿ� �ʱ�ȭ�� �Ǿ�� �Ѵ�. �� �ʱ�ȭ ����Ʈ�� �̿�����.
2.	����Ÿ���� ���۷����� �ƴ� ��쿡 �ӽ� ������� ��ü�� �Լ��� ����ϴ� ���� ��������. 
3.	�������Լ��� int attack() const;�÷� �����ϸ� �ٸ� ������ ���� �ٲ��� �ʴ� �Լ��� ǥ���Ѵ�. 
4.	static�� 0���� �ڵ� �ʱ�ȭ�ȴ�.
 
1.	C����� ���ڿ� ǥ������� �� ���� ���ڿ�(Null-terstd::minating string)�̶�� �Ѵ�. �̴� ���ڿ� �����̳� ũ�� ���濡 ������. 
2.	capacity�� ������ ���� �Ҵ��Ͽ��ٰ� ������� �ʴ� ������ �ٽ� ����Ҷ�, ���Ҵ��� ��ȿ������ ���̱����� ����Ѵ�. �� �Ҵ��� ȿ������ ���� ���̱� ���� reserve�� ����ϸ� ����ũ�⸦ ���ũ���� 2�������� �����ϰ� �Ҵ��Ѵ�. 
	���ʿ� ũ�Ⱑ capacity�� 2�踦 �Ѵ´ٸ� ���ʿ��� allocation�� ���� ���� �ʿ��� ��ŭ�� �Ҵ��Ѵ� 
3.	���԰� ���� �ǹ̷� assign()�Լ��� ����� �� �ִ�. 
*/
