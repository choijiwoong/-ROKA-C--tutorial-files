//댕글링 레퍼런스(Dangling reference); 아무것도 아닌 것을 가리키는 레퍼런스 
//메모리 할당은 힙(Heap)영역에서 한다. 스택(Stack)영역은 컴파일러에 의해 어느정도의 안정성이 보장된다. 
//객체지향의 탄생이유를 아래의 마이펫 코드에서 찾아보자. 
typedef struct Animal{
	char name[30];
	int age;
	
	int health;
	int food;
	int clean;
}Animal;

typedef struct Fish{
	char name[30];
	int age;
	
	int health;
	int food;
	int clean;
	
	int deep;//just one element are added!_ we have to make another structure because of this element
}Fish;

void create_animal(Animal *animal){//set elements of inputted Animal struct_not real create! just setting default value
	std::cout<<"name of pet ";
	std::cin>>animal->name;
	
	std::cout<<"age of pet ";
	std::cin>>animal->age;
	
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
				list[animal_num]=new Animal;//Actually Animal objects are already made!
				create_animal(list[animal_num]);//create_animal means just setting element of Animal(that is already made); we can make this processes(make structure & setting default value) by using constructor
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
					show_stat(list[play_with]);//we can make this processes by member function of class's member function
				break;
		}
		
		for(int i=0; i!=animal_num;i++)
			one_day_pass(list[i]);
	}
	for(int i=0; i!=animal_num; i++)//we can make this process by destructor
		delete list[i];
}

//3-1 Object에 Variables가 있고, 그 주위를 Methods가 둘러싼 형태; 추상화(abstraction)_객체가 현실 세계에서 존재하는 것들을 나타내기 위함 
//C++에서는 객체를 인스턴스(instance)라고 불리우는데 객체의 변수나 함수들을 인스턴스 변수(instance variable), 인스턴스 메소드(instance method)라고 부른다.  이때 클래스 내의 메소드와 변수를 멤버 함수와 멤버 변수라고 부은다. 

//3-2 인스턴스 변수와 인스턴스 메소드
class Animal{
	private:
		int food;
		int weight;
		
	public:
		void set_animal(int _food, int _weight){
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
	Animal animal;
	animal.set_animal(100, 50);
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
