/*1. �������� �ʱ�ȭ ����Ʈ(initializer list)
#include <iostream>

class Marine {
  static int total_marine_num;//static������� 
  const static int i=0;//�����ϸ鼭 �ʱ�ȭ�� ������ ���. 
   
  int hp;                // ���� ü��
  int coord_x, coord_y;  // ���� ��ġ
  //int damage;            // ���ݷ�
  bool is_dead;
  
  const int default_damage;  // �⺻ ���ݷ�_���α׷����� �Ǽ� ����. 
  
 public:
  Marine();              // �⺻ ������
  Marine(int x, int y);  // x, y ��ǥ�� ���� ����
  Marine(int x, int y, int default_damage);
  
  //int attack(); 
  int attack() const;// �������� �����Ѵ�. const �Լ�. 
  //void be_attacked(int damage_earn);  // �Դ� ������
  Marine& be_attacked(int damage_earn);//�Դ� ������ 
  void move(int x, int y);            // ���ο� ��ġ

  void show_status();  // ���¸� �����ش�.
  static void show_total_marine();//class static function
  ~Marine() { total_marine_num--; }
};
int Marine::total_marine_num=0;//static total variable�� 0���� initialize.
//��� ���� �� static variable�� ���ǿ� ���ÿ� 0���� �ʱ�ȭ �Ǳ⿡ �ʱ�ȭ�� ���� �����൵ ������,
//class's static variable�� ��� ���� ���� �ʱ�ȭ ��. 
void Marine::show_total_marine(){
	//std::cout<<default_damage<<std::endl; ó�� static�Լ����� ���������������� ������ �������� ���� ����. 
	std::cout<<"��ü ���� ��: "<<total_marine_num<<std::endl;
}

//�⺻ ���ݷ��� �Ǽ������� ���� const�� ������ ������ ���ÿ� �ʱ�ȭ����� ��. �ʱ�ȭ ����Ʈ�� ������ ����. 
Marine::Marine() : hp(50), coord_x(0), coord_y(0), default_damage(5), is_dead(false) {
	total_marine_num++;//constructor call->plus 1 to static variable
}//�Լ� ��ü�� �ƹ��͵� ����??! 
//������ �ڿ� :hp(50), �̷� ���� �ʱ�ȭ����Ʈ(initializer list)��� �θ���, ȣ��� ���ÿ� ������� �ʱ�ȭ. 
Marine::Marine(int x, int y)//�̷��÷� ���Ե� ����. 
    : coord_x(x), coord_y(y), hp(50), default_damage(5), is_dead(false) {
	total_marine_num++;//constructor call->plus 1 to static variable
}
Marine::Marine(int x, int y, int default_damage)
	:coord_x(x),
	coord_y(y),
	hp(50),//const int default_damage=(���ڷ� ����)default_damage;�� ����.  
	default_damage(default_damage),//�ʱ�ȭ ����Ʈ�� ����Ͽ� const�� �����ϴ� ����  
	is_dead(false) {
	total_marine_num++;//constructor call->plus 1 to static variable
}

void Marine::move(int x, int y) {
  coord_x = x;
  coord_y = y;
}
int Marine::attack() const{ return default_damage; }//�ٸ��� ���� �� ���� �ٸ� 
Marine& Marine::be_attacked(int damage_earn){//�����ڷ� Marine��ü�� ��ȯ�� ����. 
	
	hp-=damage_earn;//this->hp-=damage_earn; ���� this�����ͷ� �����Ͽ� ���� �� 
	if (hp<=0) is_dead=true;//if (this->hp<=0) this->is_dead=true;
	
	return *this;//�������� ���� ���۷����� ����. ��, ��ü �ڱ� �ڽ��� �����ڸ� ����. 
}
<���ֽ���> 
void Marine::be_attacked(int damage_earn) {//���� �Լ��� ��ü 
  hp -= damage_earn;
  if (hp <= 0) is_dead = true;
}<���ֳ�> 

void Marine::show_status() {
  std::cout << " *** Marine *** " << std::endl;
  std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) "
            << std::endl;
  std::cout << " HP : " << hp << std::endl;
  std::cout << " ���� �� ���� �� : " << total_marine_num << std::endl;//total print show
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
  
  std::cout << std::endl << "���� 1 �� ���� 2 �� �� �� ����! " << std::endl;
  marine2.be_attacked(marine1.attack()).be_attacked(marine1.attack());
  //marine�� ���ùް� ��ȯ�ϴ°� ����2�� �������̱⿡ �׳� ����2�� ġȯ�ؼ�
  // marine2.be_attacked(marine1.attack())�� ���� ����ǰ�, ���� ����2�� ���̶�
  //marine2.be_attacked(marine1.attack());�� ���Ŀ� ����ȴٰ� ���� ��. �� ����2�� �� 2�� ����. 
  //���࿡ marine�� be_attack()�� ��ȯ���� Marine&�� �ƴ� Marine���� �Ѵٸ� ���� ���� �� �ӽð�ü Marine��
  //ȣ��ǰ� �ӽð�ü�� �����ϴ� ���� �Ǳ⿡ marine2�� 1���� ���ݸ� �ް� ��. 
  
  std::cout<<std::endl; 
  marine1.show_status();
  marine2.show_status();
}

1. �ƾ��� Ÿ�ι�ũƼ ���� �԰�ʹ� �� ��������~~~
2. �ʱ�ȭ ����Ʈ(initializer list)�� �Ϲ����β�_ �������̸� : var1(arg1), var2(arg2) {} 
   var1�� Ŭ������ ��� �����̰�, arg�� ��������� �ʱ�ȭ��ų ���̴�.
    ���⼭ var1�� arg1�� �̸��� ���Ƶ� �ȴ�. �ֳĸ� �켱������ ���� arg1�� ���� �켱���� ��Ī�ϱ⿡. 
   ���� �Ϲ������� �ʱ�ȭ �Ҷ� (�Լ� ��ü �ȿ�) coord_x=coord_x;��� �ϸ� ������ ����. ��� ���ڷ� ����
   ������ ����ϱ⿡.
    �ʱ�ȭ����Ʈ�� �̿��ϴ� ������ ������ �ʱ�ȭ�� ���ÿ� �ϱ� �����̴�. �Ϲ������� ������ �Լ� ��ü��
   ���� ���� ���� ������ ���� �ϰ� �� ������ ���Կ����ڸ� �����ϴ� ���̴�. ��, �ʱ�ȭ����Ʈ�� int a=10;
   �� ����, ������ ��ü�� �̿��� ��� int a; a=10;�� ����. �̰��� Ŭ�����ν� �����ϸ�, �ʱ�ȭ����Ʈ�� ����ϸ�
   ��������ڰ� ȣ��Ǵµ�, ������ ��� ����Ʈ �����ڰ� ȣ��� ����, ������ ����ȴٴ� ���̴�. �� ������
   �۾��� ���� �� ���� �ȴ�. ->�ʱ�ȭ����Ʈ�� ȿ�����̴�. 
    �Ǵٸ� ������ ���۷����� ����� ��� '�ݵ�� ������ ���ÿ� �ʱ�ȭ'�Ǿ�� �ϴµ�, �ʱ�ȭ����Ʈ�� �������
   �����ʴ´ٸ�, ������ �� ���̴�. �׸��Ͽ� Ŭ���� ���ο� ���۷��� ������ ����� �ִ´ٸ�, ������ �ʱ�ȭ ����Ʈ��
   ����ؾ� �Ѵ�. 
    ��ó�� �߿��� ���� ����� ó���ϴ� ���� �ſ� ������ ���̴�. �Ǽ��� default_damage�� ���� �����Ͽ�
   ������ ��� �߰��ߴ��� ������ ã�� �ͺ��� ������ ������ ������ �� ȿ�������� ������� �� �� �ִ�. 
*/

//2. ������ �� 'Marine' �� ����(static ����)
// static ��� ������ ���

/*
1. �Ϲ������� �� Marine�� ������ �˾Ƴ��µ����� 
	1) �迭�� Marine�� �����ϰ� ������ ������ ������ ��� ��._ũ�Ⱑ ��������� ���ϴ� �迭 �ʿ�.(���ͷ� �ذᰡ���ϱ� ��) 
	2) � ������ ���� Marine�� �����Ǹ� +1, �Ҹ�ÿ� -1_�ٸ� �Լ����� ��� �� ���ڷ� ��� �����ؾߴ� 
	3) �������� ����_�ڵ�ũ�⿡ ����Ͽ� �Ǽ��� ���� �������ɼ��� ����. 
2. C++������ �������� �����鼭�� Ŭ���� �ϳ����� ���ӵǴ� ������ static ��� ������ �����ϰ� �ִ�.
   p.s C������ ���α׷� ����ñ��� ������� �ʰ� �ϴµ� static ���
   �̿� ����ϰ�, C++���� Ŭ������ static ��������� ��� ��ü�� ����� ���� �ƴ� ���α׷��� ����� �� �Ҹ�Ǹ�,
   ��� ��ü���� �ϳ��� static��������� ����ϰ� �ȴ�. 
3. Class static variable�� �ʱ�ȭ �� int Marine::total_marine_num=0;�� ���� �ʱ�ȭ �Ѵ�.
   �翬�� Ŭ���� ���ο��� static int total_marine_num=0;ó�� �ʱ�ȭ�� �Ұ����ϴ�.
   Ŭ���� ���ο��� �ʱ�ȭ�� ��ó�� ������ ���� const static int x=0;�� �����ϴ�.?? what is it.? 
4. Ŭ���� �ȿ� static ����ó�� Ŭ���� ��ü�� �� 1�� �ִ� static �Լ��� �ִ�. ��, ��� �Լ��� ���, ��ü��
   �����߸� �� ����Լ����� ȣ���� �� ������, static�Լ��� ��ü�� ��� �׳� Ŭ���� ��ü���� ȣ���� �� �ִ�.
   Marine::show_total_marine();�� ���� ȣ����._��� ��ü�� �Լ��� ���� �ֱ� ������. 

3. this. C++���� ����� �������� ��ü �ڱ� �ڽ��� ����Ű�� ������. 
   ����ü ������ �������� ->�Ͽ� ����ü ���ҵ鿡 �����ߴ� �� ó��, Ŭ���� �ɹ��Լ��� this->arg�� ���� ����.

5. const �Լ�_ C++���� �������� ���� �ٲ��� �ʰ� �б⸸ �ϴ�. ������� ����Լ��� ����Լ��ν� ������ �����ϴ�. 
   (���� �Լ��� ����) const;�� ������ �ϰ� ��.
   ���� �Ʒ��� ���� �Լ��� ���� ���� constŰ���带 �־������
   int Marine::attack() const {return default_damage;} 
    �̷��� ��Ģ�� ���� attack�Լ��� '��� ��� �Լ�'�� ���ǵ� ���̴�. �� �ٸ����α׷��ӿ��� �� �Լ���
   �ٸ� ������ ���� �ٲ��� �ʴ� �Լ��̴� ��� ���� �˷� �� �� �ִ�. 
*/

/*4. ���۷����� �����ϴ� �Լ� 
#include <iostream>

class A{
	int x;//member variable 'x' 
	
	public:
		A(int c): x(c) {}//constructor. int�� �����ϸ�, �ʱ�ȭ����Ʈ�� �̿��Ͽ� x�� c�� �ʱ�ȭ
		
		int& access_x() { return x; }//object's x to return by reference
		int get_x() { return x; } //just return int x
		void show_x() { std::cout << x <<std::endl; }//x show
};

int main(){
	A a(5);//define and initialize a
	a.show_x();
	
	int& c=a.access_x();//a�� x�� ref�� c�� ���� 
	c=4;//a�� x�� ref�� ���� �� �����̱⿡  
	a.show_x();//a�� ���� ���� 
	
	int d=a.access_x();//a�� x�� ref�� ��ȯ�� ���� ref �� �ƴ� int�� ����->***���� ���簡 �̷����.***
	d=3;//d�� ���� 
	a.show_x();//a�� ����ȵ�. 
	
	//�Ʒ��� ����_error C2440: 'initializing' : cannot convert from 'int' to 'int &'
	//int& e=a.get_x();//a�� x���� �����ڷ� ���� (����) ������ ������ a.get_x()���� ���� �ӽ�int�� �����.�ٵ� �װ� ref�� ���� 
	//e=3;//�� ���� ��� ������� ref�� �޾Ҵٰ� �ص� ���� �������� �ʴ� ref�̱⿡ ���� �� ����. 
	//a.show_x();//�� �� �ڼ��� ���ϸ� int&�� �������� ref��, a.get_x()�� �������̱⿡ �ȵȴ�.(���� ����) 
	
	int f=a.get_x();//a�� ���� int f�� ���� 
	f=1;//f ���� 
	a.show_x() //�翬�� a �״�� 
	
	//a.get_x()=3;�翬�� ����. 
	
	return 0;
}
*/

//6. �����غ���_��������� ��� ǥ�õǴ���? 
#include <iostream>

class A{
	int x;
	
	public:
		A(int c):x(c) {}//initializer list
		A(const A& a){
			x=a.x;//���� ����. 
			std::cout<<"���� ����"<<std::endl;
		}
}; 

class B{
	A a;
	
	public:
		B(int c):a(c) {}//initializer list
		B(const B& b): a(b.a) {}//B's copy constructor
		A get_a(){//��ȯ���� A�̰�, get_a()�� ȣ��. 
			A temp(a);//AŬ������ ������ ��ü temp�� �����ϴµ�, a�� �μ���. 
			return temp;//temp��ü�� ������. 
		}
};

int main() {
  B b(10);

  std::cout << "---------" << std::endl;
  A a1 = b.get_A();
}
