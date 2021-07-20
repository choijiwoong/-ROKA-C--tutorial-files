/*1. �޸��� ����
�����Ϸ��� ���� ������� �������� ����Ǵ� ����(stack)���� �ٸ��� ���� ����ڰ� ������ �����ϴ� �κ�����
å���� �ִ�.
C������ malloc�� free�� C++������ ����� �����ϳ�, ��� �������� �����ϴ� ���� new�� delete��.
*/

/*2. new�� delete�� ���
#include <iostream>

int main(){
	int* p=new int;//Ÿ���� ����� �ָ�, �� Ÿ���� ũ�⸸ŭ ������ �Ҵ��Ѵ�. 
	*p=10;//���� ����. 
	
	std::cout<<*p<<std::endl;
	
	delete p;//p�� �Ҵ�� ���� ���� 
	return 0;
} 

���� ���������� �����ϰ� delete�� �Ҵ��� �����ع������� �Ѵٸ� Heap�� �ƴ� ������ �����Ϸ� �Ѵٴ� ���޽���. 
#include <iostream>

int main(){
	int a=5;
	delete &a;
	return 0;
} 
*/

/*3. new�� �迭 �Ҵ��ϱ�. 
#include <iostream>

int main(){
	int arr_size;//�迭�� ũ�⸦ ���� ���� ����.
	 
	std::cout<<"array size: ";
	std::cin>>arr_size;//�� ���� �Է¹���
	 
	int *list=new int[arr_size];//�迭�� ������ ������ []�� �̿��Ͽ� �迭�� ũ�⸦ �־��ش�.
	//�ֳĸ� ���� 2.���� �� Ÿ���� ũ�⸸ŭ ������ �Ҵ��Ѵٰ� �ϴµ�, ���� �Ҵ� �� ����� ��Ȯ��
	//ũ�⸦ �˾ƾ� �ϱ⿡ �ܼ��� new int�� �ϸ� int1���� ���� ��ŭ�� ������ �Ҵ�Ǵ�
	//int[arr_size]�� ���� ��Ȯ�� ��� ũ�⸦ �˷��ش�. 
	//���� �� �״�� new(���ο� ���� �Ҵ�) int[arr_size](�̸�ŭ) 
	
	for (int i=0;i<arr_size;i++){//�Ʒ��� p.s�� ���� ���� �Լ� �ۿ��� i�� ���� �ߴ��� �����Ϸ��� 
		std::cin>>list[i];       //������ ���� ���� ������ �����ϱ� ������ ������ �߻��� ���ɼ��� ����. 
	}
	for (int i=0;i<arr_size;i++){
		std::cout<<i<<"th element of list: "<<list[i]<<std::endl;
	}
	delete[] list;//����Ʈ�� ����. �� new-delete, new[]-delete[]�� ���� �̷�.���̻��? 
	return 0;
} 

+p.s � ������ ����� �� �����Ϸ��� �� ������ ���� ����� ����(scope)���� ã�� �ȴ�.
int a=4;
{
	std::cout<<"�ܺ��� ���� 1"<<a<<std::endl;
	int a=3;
	std::cout<<"������ ����"<<a<<std::endl; 
} 
std::cout<<"�ܺ��� ���� 2"<<a<<std::endl; 
�� ��� 4 3 4 �� ��µ�. �����Ϸ��� ������ ã�� �� ���� ����� ���� ������ ã�´�. ���⼭�� ����: {} 
*/

/*4. ���ƿ� ������_C��� ���ǿ��� switch���� ���� �����ϰ� ���� ���α׷� 
#include <iostream>

typedef struct Animal{//animal ����ü ���� �� typedef ����Ͽ� struct Animal->Animal�� ���߸� 
	char name[30];//�̸�
	int age; //����
	
	int health;//ü��
	int food;//��θ� ����
	int clean;//������ ���� 
} Animal;

void create_animal(Animal *animal){
	std::cout<<"������ �̸�? ";
	std::cin>>animal->name;
	
	std::cout<<"������ ����? ";
	;std::cin>>animal->age;
	
	animal->health=100;
	animal->food=100;
	animal->clean=100;
}

void play(Animal *animal){
	animal->health+=10;
	animal->food-=20;
	animal->clean-=30;
}

void one_day_pass(Animal *animal){
	//�Ϸ簡 ������
	animal->health-=10;
	animal->food-=30;
	animal->clean-=20; 
}

void show_stat(Animal *animal){
	std::cout<<animal->name<<"�� ����"<<std::endl;
	std::cout<<"ü��: "<<animal->health<<std::endl;
	std::cout<<"��θ�: "<<animal->food<<std::endl;
	std::cout<<"û��: "<<animal->clean<<std::endl;
}

int main(){
	Animal *list[10];
	int animal_num=0;
	
	for(;;){
		std::cout<<"1. ���� �߰��ϱ�"<<std::endl;
		std::cout<<"2. ���"<<std::endl;
		std::cout<<"3. ���� ����"<<std::endl;
		
		int input;
		std::cin>>input;
		
		switch(input){
			int play_with;
			case 1:
				list[animal_num]=new Animal;//Animal�� new�� �����ϸ�  
				create_animal(list[animal_num]);//create_animal�Լ��� ���Ͽ� ���� �ʱ�ȭ 
				animal_num++;
				break;
			case 2:
				std::cout<<"������ ���? : ";
				std::cin>>play_with;
				if(play_with<animal_num) 
					play(list[play_with]);//��⸦ ȣ �� 
				break;
			case 3:
				std::cout<<"������ ����? : ";
				std::cin>>play_with;
				if (play_with<animal_num)
					show_stat(list[play_with]);//���º��⸦ ȣ�� 
				break;
		}
		
		for (int i=0;i!=animal_num;i++){
			one_day_pass(list[i]);
		}
	}
	for(int i=0;i!=animal_num;i++){
		delete list[i];
	}
}

���� �ڵ忡�� ����� ���� ���� �κ�: 
1) play�� ȣ���Ϸ��� list[play_with]�� �����ؾ���
�ٵ� �׳� Animal����ü ��ü�� �Լ��� ���� �� ����ü ������ ���� �ڽ��� �Լ��� ������ �Ǵ� ����?
�׷� list[play_with]->play()�� ���� ������������ �Լ��� ȣ���Ͽ� �ڽ��� �����͸� �̿��Ͽ� ó���ϰԲ�.
*�̷��� �Ѵٸ� play�Լ��� ���ڸ� ������ �ʿ䵵 ���� �� ���� play�Լ� ���� animal->health�� �������� �ʰ�
�ڱ� �ڽ��� �Լ��̱⶧���� �׳� health�ε� ������ �����ϴٴ°�. 
2) line125~126�� new Animal�� ���� ������ ������ �ݵ�� create_animal�� ȣ���ؾ߸� ���� �ʱ�ȭ ��.
�̴� ���� ���α׷��Ӱ� �Ǽ��� new Animal�� ������ �� create_animal�� ���� ������, �ʱ�ȭ ���� ����
���� ������ �ϴ� ����� �߻��ϰ� ��.
��. new�� ���ο� Animal�� �Ҵ��� �� �ڵ����� ȣ��Ǵ� �Լ��� �ִٸ� �ڵ����� �ʱ�ȭ�ؼ� ������
������ �ʰ� ���� �� �ִ�. 

�ƴ� ������ �Ⱑ������ �ϳ� �̺��� ��� ���ϴ� ����̿�? ���� ������ ���ֽÿ�.

3) ���� ���� ���α׷��� ũ��ū �α⸦ �� Ȯ������ �����Ϸ� �ϴµ� Animal�̶�� �����ߴ� ���� ����ȭ�Ͽ�
Bird, Fish������ ������ ó���Ϸ��� ��. bird�� fish�� animal�� �⺻������ ���������� ���� ���� ��Ÿ����
������ int height;�� ���� �߰��ǰ�, fist�� ������ ��Ÿ���� ������ int deep;�� �߰���. �׷��ٸ� �ڵ��
typedef struct Bird {
  char name[30];  // �̸�
  int age;        // ����

  int health;  // ü��
  int food;    // ��θ� ����
  int clean;   // ������ ����

  // ��������� Animal �� �����ϴ�.
  int height;  // ���� ��

} Bird;

typedef struct Fish {
  char name[30];  // �̸�
  int age;        // ����

  int health;  // ü��
  int food;    // ��θ� ����
  int clean;   // ������ ����

  // ��������� Animal �� �����ϴ�.
  int deep;  // ���� ����

} Fish;
�� ���� ��. �� Animal�� ���� �Ȱ����� ���� �ٸ� �� ������ ����ü�� ���� �ΰ��� ������ ��.
�׳� Animal�� ������ �κ��� ������ ���� ���� �߰��� �κи� �߰��ϸ� �ȵǴ°�? 
���� ���� ���� �����Ѵٸ� ���̻� Animal*�迭 �ϳ��� �ƴ� Fish*, Bird*���� �����ؾ��� �Ӵ���
play, show_stat�Լ��� ��� Animal, Bird, Fish�� ���� ���� ���� �ۼ��ؾ� ��.
��. int height, int deep������ �ڵ��� 2�踦 ����Ѵٴ� ��. 
C����� �� ������ ����� ��. ��ü�������α׷����� ���ԵǴ� ������ �ٷ� ����. 
*/



/*����
1. new�� delete�� �˾ƺ��⿡ �ռ�, �����Ҵ��� ����(stack)�� ���� heap������ ����Ͽ� ���α׷��Ӱ�
   ���� �����ϹǷ� å�Ӽ��� �ִ�.
2. C������ malloc�� free�Լ� ���� c++���� ����� �����ϳ�, ������� �������� new�� delete�� �����ϸ�
   malloc�� ��Ȱ�� new��, free�� delete�� ����Ѵ�. 
3. int *p=new int;ó�� type *pointer=new type�÷� ����ϸ�, new �ڿ� ��õ� �ڷ����� ũ�⸸ŭ �޸𸮰� �Ҵ�ȴ�.
   ���� ����� *�� ����Ͽ� *p�÷� ����ϸ�, �޸𸮸� ������ ���� delete p;�� ���� �����Ѵ�. 
4. ���� delete�� �̿��Ͽ� �����ϴ� ������ new�� ����Ͽ� heap������ �Ҵ�� ������ �ƴ� stack������ �Ҵ�� �����������,
   heap������ �ƴ� ������ �޸𸮸� �����Ϸ� �Ѵٴ� ���޽����� ��µȴ�.
5. �迭�� new�� �Ҵ��Ϸ���, int *p=new int[size];ó�� �Ҵ��ϸ� �ȴ�. �� new �ڿ� ���� �ڷ��� ũ�⸸ŭ �Ҵ��Ѵ�. 
   ���� ���� ����� ���ʿ� int arrat[size]���� array�� �ּҸ� ����Ű��, ���� ����� array[0]�� ���� �ϴµ�,
   ���� p�� �̹� �޸��� �ּҸ� ����Ű�⿡ �Ϲ� �迭�� ���� p[0]������ �����ϸ� �ȴ�. 
6. new�� ���Ͽ� �����Ҵ� �� �޸��� ������ �Ϲ� delete p;�� �ƴ� delete[] p;�� �Ѵ�.
   ��, new-delete, new[]-delete[]�� �� ���̴�.
   
7. �����Ϸ��� � ������ ����� �� ���� ����� ����(scope_{}�߰�ȣ)�� �ִ� ������ �����.
   �̴� for{}�� �ȿ��� ���ǵ� i��� ������ �̸��� for{}�ܺ��� i������ �̸��� ���� ��, �����߻��� ������.
8. ����ü�� ������ �ݵ�� ȣ��Ǿ�� �ϴ� �Լ����� ����ü�� �ѱ� �� ���ڷ� ����ü�� ���ٴ� ��, 
   �ݵ�� ȣ��Ǿ�� �ϴ� �Լ��� �Ǽ��� ȣ������ �ʾ������� �����߻����ɼ�, 
   ����� ����ü�� ���Ǹ� �Ź� ���Ӱ� �ؾ��ϰ�, �� ������ �ٸ� ����ü�⿡ �ϳ��� ����Ʈ�� ���Ѵٴ� ��, 
   ����ü�� �����ų �Լ��� �������޿� animal->health�� ���� ������� ������ �����Ѵٴ� ����
   C�� ������ ��ü�������α׷����� ������ C++���� �ذ��� �Ǳ� ������. 
*/ 
