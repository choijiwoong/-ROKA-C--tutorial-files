/*1. ��Ÿũ����Ʈ ����� 
#include <iostream>
#include <string.h>//������ �̸� ����� 

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
	std::cout << name << " �� �Ҹ��� ȣ�� ! " << std::endl;
	if(name!=NULL){
		delete[] name;//name��ü�� string�� �ƴ� char�� �迭�ν� new��. �� delete[] 
	}
}
int main(){
	Marine* marines[100];//���� �������� ��� ���� �迭�� Marine���� ����. 
	
	marines[0] = new Marine(2, 3, "Marine 2");//�����ڸ� �ڵ����� ȣ������. C++�� �´� ���ο� �����Ҵ� 
    marines[1] = new Marine(1, 5, "Marine 1");
	
	marines[0]->show_status();//�����͸� ����Ű�� �迭�̱⿡ �޼ҵ� ȣ�� �� .�� �ƴ϶� ->�� ����ؾ��Ѵ�. 
	marines[1]->show_status();
	
	std::cout <<std::endl<<"���� 1�� ���� 2�� ����! "<<std::endl;
	
	marines[0]->be_attacked(marines[1]->attack());
	
	marines[0]->show_status();
	marines[1]->show_status();
	
	delete marines[0];//�����Ҵ� �޸� �׻� ���� 
	delete marines[1];
	return 0;
}
//
1. C++�� ��� malloc�� �ٸ��� new�� ��ü�� �������� ���� �� �ڵ����� �����ڵ� ȣ������.
2. ��Ȯ�� delete�� ���� �ʴ� �� �ڵ����� delete�� �Ǵ� ���� ���⿡, �� ������ ������ �޸� ���� �ӿ��� �յ�
   ���ٴϰ� ��. �̷��� �͵��� ���̸� ������������ ���� �޸𸮸� �����ϴ� �޸� ����(Memory Leak)�� �������� �߻�.
3. �׷��� C++������ main�Լ� ������ Marine�� delete�� ��, �� �����ߴ� ��ü�� �Ҹ�� �� �ڵ����� ȣ��Ǵ� �Լ��ν� �Ҹ���(Destructor)�� ����.
    �����ڰ� Ŭ���� �̸��� �Ȱ��� ����ٸ�, �Ҹ��ڴ� �� �տ� ~�� �ٿ��� ǥ����. ex)~Marine(); 
4. �Ҹ��ڴ� �ַ� �������� �Ҵ���� �޸𸮸� �����ϴ� �ϰ�, ������ ���̿��� lock�� ���� Ǫ�µ� ����Ѵ�.
	�����, �����ڸ� �������� �ʰ� default constructor�� �ִ� �� ó��, default destructor�� �ִ�.
	��� ���� �Ҹ��ϴ� ���̱⿡ �ƹ� �۾��� �������� �ʱ⿡ �Ҹ��ڰ� �ʿ���� Ŭ������� ���� Ŭ������
	������� �ʴ´�. 
 */
 
 
/* 3.�Ҹ��� ȣ�� Ȯ���ϱ�
#include <string.h>
#include <iostream>

class Test {
  char c;

 public:
  Test(char _c) {
    c = _c;
    std::cout << "������ ȣ�� " << c << std::endl;//������ ȣ�� cout 
  }
  ~Test() { std::cout << "�Ҹ��� ȣ�� " << c << std::endl; }//�Ҹ��� ȣ�� cout 
};
void simple_function() { Test b('b'); }//�Լ��� ȣ��Ǹ� TestŬ���� 'b'�� ����. �ٵ� �Լ��� ������
									   //�ٷ� b�� ��ü�� ������Ƿ� b�� �Ҹ��� ȣ��. because b is local object 
int main() {
  Test a('a');//��ü a�� ���� 
  simple_function();//��ü b�� ������ �Ҹ� 
}//��ü a�� �Ҹ� 
line114���� Test��ü 'a'����.
line115���� simple_function()ȣ�� 
�׷��� �ڵ� ���� ��  
������ ȣ�� a 
������ ȣ�� b
�Ҹ��� ȣ�� b_������ü�̱⿡ �Լ��� ������ �Ҹ� 
�Ҹ��� ȣ�� a ������ ��µ�.  _�����Լ��� ������ �Ҹ� 
*/

/*4. ���� ������(copy constructor)
//����ĳ��
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
<����ó������> 
//for use default copy constructor
Photon_Cannon::Photon_Cannon(const Photon_Cannon& pc){//standard definition of cpyt constructor
	std::cout<<"���� ������ ȣ�� !"<<std::endl;//�� ����� Photon_Cannon's default copy constructor structure. 
	hp=pc.hp;
	shield=pc.shield;
	coord_x=pc.coord_x;
	coord_y=pc.coord_y;
	damage=pc.damage; 
}
<����ó�� ����>
Photon_Cannon::Photon_Cannon(const Photon_Cannon &pc){
	std::cout<<"���� ������ ȣ��! "<<std::endl;
	hp = pc.hp;
  	shield = pc.shield;
  	coord_x = pc.coord_x;
  	coord_y = pc.coord_y;
  	damage = pc.damage;
	
	name=new char[strlen(pc.name)+1];//���� �����ڿ��� name���� deep copy�� ���� new. 
	strcpy(name,pc.name);//content copy. same code with constructor in name. ���� ������ ���� �޸𸮸� ����. 
}
Photon_Cannon::Photon_Cannon(int x, int y) {
  std::cout << "������ ȣ�� !" << std::endl;
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
  Photon_Cannon pc3 = pc2;//***C++�����Ϸ��� �� ������ Photon_Cannon pc3(pc2);�� �Ȱ��� �ؼ���.
  //�̴� ���� Ư���� ���� ����  pc=pc2;�� �ߴٸ� �ܼ��� ���Կ����̰�����, Photon_Cannon pc3=ó��
  //���� �ÿ� �����ϴ� ������ �ϸ� ���� �����ڰ� ȣ��ǰ� ��. 

  pc1.show_status();
  pc2.show_status();
  
  std::cout<<std::endl;
  //for check limit of default copy constructor
  Photon_Cannon pc4(3,3,"Cannon");
  Photon_Cannon pc5=pc4;
  
  pc4.show_status();
  pc5.show_status();
  //������ �����ϸ� runtime error. �ٵ� �غ��� �׳� return �����Ⱚ�߱������� ������ ��. ��ư ����. 
}
*/

/*
1. T(const T& a);�� ���� �������� ǥ������ �����̴�. 
   �̴� �ٸ� T�� ��ü a�� ��� ���۷����� �޴´ٴ� ��. �� ��������� ���ο��� a�� �����͸� ����Ұ��ϰ�,
   ���� ���Ӱ� �ʱ�ȭ�Ǵ� �ν��Ͻ� �����鿡�� ���縸 �� �� �ְ� �ȴ�.
   p.s �������ϸ� �Լ� ���ο��� ���� ������ ���� ��ȯ��Ű�� ���� ���ٸ� const�� ���̴� ������ �⸣��.(�Ǽ�����)
2. Photon_Cannon pc3=pc2;ó�� �����ÿ� �����ϴ� ���� �� ���� �����ڸ� ȣ���ϰ� ��. ���� ������ �ƴ�. 
3.	Photon_Cannon pc3 = pc2; ��  

	Photon_Cannon pc3;
	pc3 = pc2;�� ������ �ٸ� ������.
	���ڴ� ���� �����ڰ� 1�� ȣ��Ǵ� ���̰�, ���ڴ� �����ڰ� 1�� ȣ��ǰ�, pc3=pc2;��� ����� ����Ǵ� ��.
	�� ���̴� ���� �����ڳ� �����ڿ� �ܼ��� ���� �ִ� �۾� ���� �ٸ� �۾��� �߰����� �� 
	ex) �����Ҷ� cout�����Ǿ����ϴ�!or �����Ҷ� ��ü�� ��� �迭�� +1�Ѵٴ���
	�ڵ尡 ���� �� ����. ������ �� �ϴ� �۾��� ������ �� �ϴ� �۾��� �ٸ���, ���ڿ� ���ڸ� ȥ���ϸ�,
	�������� �⿬�� ������ ��.
4. C++�����Ϸ����� �� �� �Ǳټ�? default copy constructor�� �������ְ� ����. ���� �ڵ忡�� ��������ڸ� �����
	�������ϸ� ������ ��Ȯ�� ������ ����� ��Ÿ��. 
	������ default constructor or destructor�� �ƹ� ����� ���� �ݸ鿡, default copy constructor��
	������ ���縦 ���ش�.(�����Ǵ� ���ҵ��� 1��1����.)
	��. ������ Ŭ������ ��� ��������ڸ� �������� �ʰ� default copy constructor�� �̿��Ͽ� ���� copy�� �� ����. 
5.	*Limit of default copy constructor*
	default copy constructor�� ������ 1��1 ���� ���縦 ����. �� copy constructor���� name��
	hp=pc.hp;�ϵ� name=pc.name;���� ó����. 
	ex)
		Photon_Cannon::Photon_Cannon(const Photon_Cannon& pc) {
  		hp = pc.hp;
  		shield = pc.shield;
  		coord_x = pc.coord_x;
  		coord_y = pc.coord_y;
  		damage = pc.damage;
  		name = pc.name;
		}
    �̷��� name�� char�� array�ϱ� name��ü�� ���� �ּҸ� ���� �ǰ�, 
	pc4�� name�ּҸ� �״�� pc5�� name�ּҿ� ������ ���� �ȴ�.
	��, pc4�� pc5�� pc4�� name �ּ��ϳ��� ����Ű�� �ִ� ����. ��, �����Ҵ���� pc4�� �޸𸮸� pc5�� �޸�
	���� ���� ����Ű�� �Ǵ� ��. 
	 ���� �޸𸮸� �ΰ��� �����Ͱ� ����Ű�� ���� �ܼ��� ���࿡���� �� ������ ���� �ʴ´�. 
	�ٸ� �Ҹ��ڿ��� ū ������ �߻��ϰ� �ȴ�.
	  main()�Լ��� ����Ǳ� ������ �����Ǿ��� ��ü���� �ı��Ǹ鼭 �Ҹ��ڸ� ȣ���ϰ� �Ǵµ�, ���� pc4��
	���� �ı��Ǿ��ٰ� �����غ���. �׷� pc4�� ������ ��� �ı��԰� ���ÿ� name�� �Ҵ�Ǿ��� �޸� ���� 
	delete�ϰ� �ȴ�. �׷��� �� �� pc5�� name�� �̹� �տ��� ������ �޸𸮸� ����Ű�� �ִٴ� ��. 
	�׷��ٸ� pc5�� �Ҹ��ڰ� ȣ��Ǹ� name�� �̹� ������ �޸��� �ּڰ���(NULL�� �ƴϴ�)����Ű�� �ֱ� ������
	if���� ���Ͽ� delete������ ����ǰ� �ǰ�, �׷��ٸ� �̹� ������ �޸𸮿� �����Ͽ� �ٽ� �����Ϸ� �ϰ� �ֱ⿡
	��Ÿ�� ������ �߻��ϰ� �ȴ�.(�ϴ� ������ �޸𸮿� �����Ϸ� �Ѵٴ� �� ��ü�� �̹� ������.) 
	 �̷��� ������ �ذ��ϱ� ���Ͽ� ���� �����ڿ� name�� �״�� �����ϴ� ���̾ƴ϶�, ���� �ٸ� �޸𸮿�
	�����Ҵ�(new)�Ͽ� �� ���븸 �����ϸ� �ȴ�. 
	 ��ó�� �޸𸮸� ���� �Ҵ��Ͽ� ������ �����ϴ� ���� ���� ����(deep copy), �Ʊ�ó�� �ܼ��� ���Ը� ���ִ�
	���� ���� ����(shallow copy)��� �θ���.
	 ��, �����Ϸ��� default copy constructor�� �ܼ��� ������ ��������ۿ� �� �� ���⿡ ��ó�� ���� ���簡
	�ʿ��� ���, ����ڰ� ���� ���� �����ڸ� ������ �Ѵ�. 
6.	C++������ std::string�̶�� �Ǹ��� ���ڿ� Ŭ������ �����ϱ� ������, Có�� null����� char �迭�� �ٷ�� ���� �����Ѵ�. 
*/

//6. �����غ���
#include <iostream>

class string{
	char *str;
	int len;
	
	public:
		string(char c, int n);//���� c�� n�� �ִ� ���ڿ��� ����
		string(const char *s);
		string(const string &s);
		~string();
		
		void add_string(const string &s);//str�ڿ� s�� ���δ�.
		void copy_string(const string &s);//str�� s�� �����Ѵ�.
		int strlen();//���ڿ� ���� ���� 
}; 

int main(){
	
	return 0;
}
