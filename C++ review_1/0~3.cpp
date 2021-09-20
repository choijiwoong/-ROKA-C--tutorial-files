//0-1. header1.h�� ���� namespace�̸��� ����ϸ� �ϳ��� ���� header1.h�� header1 �̸������� �Լ� ��� ���� 
#include <iostream>
#include "header1.h"
#include "header2.h"

namespace header1{//
	int func(){
		foo();//
		header2::foo();
	}
}

//0-2. namespace�� �̸��� �������ָ� staticó�� �ش� ���Ͼȿ����� ������ �����ϴ�.
namespace{
	int OnlyInThisFile(){}
	int only_in_this_file=0;
} 
int main(){
	OnlyInThisFile();
	only_in_this_file=3;
}

//0-3. �������� ���� ���� �̸� ���� ����� ȥ������ ����.
int number_of_people;
int NumberOfPeople;
int NumberOf_People;//no

//1-1 C�� �����ʹ� ����� �ڸ��� �����ϴ� �ݸ�, ���۷����� �޸� �󿡼� �������� ���� ���� �ִ�. �׳� �����Ϸ��� ref�ڸ��� ġȯ��Ű�� �Ǳ⿡. 
//1-2 cin�� ���۷����� user_input���ޱ⿡ Có�� &�� ������� �ʾƵ� �ȴ�.
//1-3 ��۸� ���۷���(Dangling reference)�� �������� �Լ� ���۷��� ���Ͽ��� �������� ������ ��������. �ƴϸ� ���ڷ� ref�� ������ ��. 

//2-1 �޸� �Ҵ��� ��(Heap)�������� �Ѵ�. ����(Stack)������ �����Ϸ��� ���� ��������� �������� ����ȴ�. 
//2-2 ���� ������ delete�� �����Ϸ��ϸ� ���޽����� ��µȴ�.
//2-3 ������ ���α׷��� Fish�� �߰������ν� ����ü�� �ϳ� �� ������ �Ѵٸ�? ���� ��ü���� ���� 
typedef struct Animal{//Structure
	char name[30];
	int age;
	
	int health;
	int food;
	int clean;
}Animal;
//how about fish?
typedef struct Fish{
	char name[30];
	int age;
	
	int health;
	int food;
	int clean;
	
	int deep;//added
}Fish;

void create_animal(Animal *animal){
	std::cout<<"name of pet ";
	std::cin>>animal->name;
	
	std::cout<<"age of pet ";
	std::cin>>animal->age;
	
	animal->health=100;
	animal->food=100;
	animal->clean=100;
}

void play(Animal *animal){//Encapsulation
	animal->health+=10;
	animal->food-=20;
	animal->clean-=30;
}
void one_day_pass(Animal *animal){
	animal->health-=10;
	animal->food-=30;
	animal->clean-=20;
}
void show_stat(Animal *animal){
	std::cout<<"status of "<<animal->name<<std::endl;
	std::cout<<"health "<<animal->health<<std::endl;
	std::cout<<"food "<<animal->food<<std::endl;
	std::cout<<"clean "<<animal->clean<<std::endl;
}

int main(){
	Animal *list[10];
	int animal_num=0;
	
	for(;;){
		std::cout<<"1. add animal"<<std::endl;
		std::cout<<"2. play"<<std::endl;
		std::cout<<"3. status"<<std::endl;

	
		int input;
		std::cin>>input;
	
		switch(input){
			int play_with;
			case 1:
				list[animal_num]=new Animal;
				create_animal(list[animal_num]);
				animal_num++;
				break;
		
			case 2:
				std::cout<<"play with ";
				std::cin>>play_with;
				if(play_with<animal_num)
					play(list[play_with]);
				break;
		
			case 3:
				std::cout<<"status of ";
				std::cin>>play_with;
				if(play_with<animal_num)
					show_stat(list[play_with]);
				break;
		}
		
		for(int i=0; i!=animal_num;i++)
			one_day_pass(list[i]);
	}
	for(int i=0; i!=animal_num; i++)
		delete list[i];
}

//3-1 ��ü�� ���� ���迡�� �����ϴ� �͵��� ��Ÿ���� ���Ͽ� �߻�ȭ(abstraction)�� ������ �ʿ��ϴ�. Object�� Variables�� �ְ�, �� ������ Methods�� �ѷ��� ����. 
//	  �̷��� ��ü�� ������ �Լ����� �ν��Ͻ� ����(instance variable), �ν��Ͻ� �޼ҵ�(instance method)��� �θ���. 

//3-2 �ν��Ͻ� ������ �ν��Ͻ� �޼ҵ�
class Animal{
	private:
		int food;//member variable
		int weight;
		
	public:
		void set_animal(int _food, int _weight){//member function
			food=_food;
			weight=_weight;
		}
		void increse_food(int inc){
			food+=inc;
			weight+=(inc/3);
		}
		void view_stat(){
			std::cout<<"food of this animal"<<food<<std::endl;
			std::cout<<"weight of this animal"<<weight<<std::endl;
		}
}; 

int main(){
	Animal animal;//make instance Animal
	animal.set_animal(100, 50);//use instance function
	animal.increase_food(30);
	animal.view_stat();
	return 0;
}

//3-3 Data Ŭ������ �������غ���
class Date{
	int year_;
	int month_;
	int date_;
	
	public:
		void SetData(int year, int month, int date);
		void AddDay(int inc);
		void AddMonth(int inc);
		void AddYear(int inc);
		void ShowDate();
}; 
