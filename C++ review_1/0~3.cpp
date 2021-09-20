//0-1. header1.h와 같은 namespace이름을 사용하면 하나로 보아 header1.h의 header1 이름공간의 함수 사용 가능 
#include <iostream>
#include "header1.h"
#include "header2.h"

namespace header1{//
	int func(){
		foo();//
		header2::foo();
	}
}

//0-2. namespace의 이름을 안지어주면 static처럼 해당 파일안에서만 접근이 가능하다.
namespace{
	int OnlyInThisFile(){}
	int only_in_this_file=0;
} 
int main(){
	OnlyInThisFile();
	only_in_this_file=3;
}

//0-3. 가독성을 위해 변수 이름 짓는 방법을 혼용하지 말자.
int number_of_people;
int NumberOfPeople;
int NumberOf_People;//no

//1-1 C의 포인터는 당당히 자리를 차지하는 반면, 레퍼런스는 메모리 상에서 존재하지 않을 수도 있다. 그냥 컴파일러가 ref자리를 치환시키면 되기에. 
//1-2 cin이 레퍼런스로 user_input을받기에 C처럼 &을 사용하지 않아도 된다.
//1-3 댕글링 레퍼런스(Dangling reference)를 막기위해 함수 레퍼런스 리턴에서 지역변수 리턴을 조심하자. 아니면 인자로 ref로 받으면 됨. 

//2-1 메모리 할당은 힙(Heap)영역에서 한다. 스택(Stack)영역은 컴파일러에 의해 어느정도의 안정성이 보장된다. 
//2-2 스택 영영을 delete로 해제하려하면 경고메시지가 출력된다.
//2-3 마이펫 프로그램에 Fish가 추가됨으로써 구조체를 하나 더 만들어야 한다면? 에서 객체지향 도래 
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

//3-1 객체가 현실 세계에서 존재하는 것들을 나타내기 위하여 추상화(abstraction)의 과정이 필요하다. Object에 Variables가 있고, 그 주위를 Methods가 둘러싼 형태. 
//	  이러한 객체의 변수나 함수들을 인스턴스 변수(instance variable), 인스턴스 메소드(instance method)라고 부른다. 

//3-2 인스턴스 변수와 인스턴스 메소드
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

//3-3 Data 클래스를 디자인해보자
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
