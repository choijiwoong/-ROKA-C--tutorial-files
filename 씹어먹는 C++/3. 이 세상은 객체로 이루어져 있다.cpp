/*1. 객체란?
기존의 Animal 구조체를 가져오면  
typedef struct Animal {
  char name[30];  // 이름
  int age;        // 나이

  int health;  // 체력
  int food;    // 배부른 정도
  int clean;   // 깨끗한 정도
} Animal;
이고, 이를 필요로 하는 함수들에게 play(list[play_with]);와 같이 구조체를 인수로 전달해 줌.
근데 play가 animal을 하는 것 같은 이 코드는 사실 animal자체가 play를 하는 것임.
즉 이를 고쳐주어 새로 코딩하게 되면,

Animal animal;

// 여러가지 초기화 (생략)

animal.play();   // 즉 내가 (animal 이) Play 를 한다!
animal.sleep();  // 내가 sleep 을 한다! 
이렇게 바굴 수 있음. 이렇다면 play함수는 이미 내 모든 정보를 알 수 있기에 적절한 처리가 가능.
즉. animal은 자신의 상태를 알려주는 변수(variable)과, 자신이 하는 행동들(play, sleep)을 수행하는
함수(method)들로 이루어짐.
 결론적으로 "객체한, 변수들과 참고 자료들로 이루어진 소프트웨어 덩어리이다." 
이때 객체가 현실세계의 존재하는 것을 나타내기위해 추상화(abstraction)이라는 과정을 거치는데,
핸드폰의 경우 전화나 문자를 핸드폰을 하는 것으로, 배터리의 잔량같은 것은 변수로. 
즉. 적절하게 컴퓨터에서 처리할 수 있도록 바꾸는 과정을 의미한다. 
 즉 객체안의 변수들을 함수들이 둘러싸고 있는 구조인데, 이를 인스턴트 변수(instance variable)와
인스턴트 메소드(instance method)라고 부른다. (걍 대충 인스턴트 메소드면 객체안의 함수다.)
 이때, 변수들을 함수들이 둘러싼다는 것은 실제로 보호를 받는 것을 의미함. 인스턴트 변수에
직접 접근하여 값을 바꾸기 보단 함수로 값을 수정하는데, 이처럼 외부에서 직접 인스턴트 변수의 값을
바꿀 수 없고, 항상 인스턴스 메소드를 통하여 간접적으로 조절하는 것을 캠슐화(Encapsulation)이라고 한다.
  이때 캡슐화의 이유, 즉 장점은 "객체가 내부적으로 어떻게 작동하는지 몰라도 사용할 수 있다."이다.
만약 위의 animal에서 animal.increase_food(100);을 하면 내부적으로 weight가 증가하고, happiness가 올라가는
등, 여러 작업이 일어나는데, 캡슐화를 하지 않았다면 객체 내부의 변수들이 어떤 것이 할당되어 있는지를 확인하고
이에따라 각각의 변수들을 조정해줘야 한다. 즉 프로그래머가 food를 100먹는 과정에서 어떤 일들이 일어나는지
알아야만 설정이 가능하다는 것. 만약 이를 캡슐화 했다면 다른 프로그래머가 봤을때 이러한 일들의 과정을 
몰라도 단순히 animal.increase_food(100);을 통해 내부를 몰라도 사용이 가능하다. 
이에 대해 의문을 품는다면 앞으로 키보드를 my_domputer.keyboard_hit('a');메소드의 호출로 사용하기 바람. 
 */
 
/*2. (너와 나의?)클래스 
C++에서의 이러한 객체르 만들 수 있는 장치가 클래스(class)이다. 클래스를 이용하여 만들어진 객체를 인스턴스(instance)라고 부른다.
#include <iostream>

class Animal {//Animal클래스를 통하여 생성될 임의의 객체에 대한 설계도 
 private://이를 접근 시지자 라고 함. 외부에서 멤버들에 대하여 접근을 할 수 있냐 없냐를 지시해주는 것이다.
  int food;//클래스 상에서 지칭할때 맴버 변수(member variable) 
  int weight;//private되는 모든 것은 자기 객체 안에서만 접근할 수 있지, 객체 외부에서는 접근할 수 없게 된다. 
  //즉 main에서 Animal animal;할당 후 animal.food=100;이 불가능하다는 것.
  //별도의 private, public명시를 하지 않는다면 private가 default값임. 즉 private안의 맴버 변수를
  //밖으로 꺼내둬도 정상 작동 함. (알아서 private화) 
   
 public://public의 경우 외부에서 마음껏 이용할 수 있음. 즉 main에서 animal.set_animal(100,50);처럼 사용이 가능하다. 
  void set_animal(int _food, int _weight) {//맴버 함수(member function)이라고 부름. 즉 실재하는게 아니다. 
    food = _food;//객체가 만들어져서 실재하면 인스턴스 변수, 인스턴스 함수! 
    weight = _weight;
  }//만약 voit set_animal()함수를 private로 옮겼다면, 접근이 불가능하다는 오류가 3개정도 등장한다. 
  //위와 비슷하게 만약 멤버변수를 public으로 옮기면 main에서 animal.food=100;처럼 사용이 가능하다. 
  
  void increase_food(int inc) {
    food += inc;
    weight += (inc / 3);
  }
  void view_stat() {
    std::cout << "이 동물의 food   : " << food << std::endl;
    std::cout << "이 동물의 weight : " << weight << std::endl;
  }
};  // 세미콜론 잊지 말자!

int main() {
  Animal animal;//클래스의 생성 struct를 명시하지 않고 일반적인 자료형 처럼 사용. 
  animal.set_animal(100, 50);
  animal.increase_food(30);

  animal.view_stat();
  return 0;
}
*/

//3. 생각 해볼 문제
#include <iostream>

class Date{
	int year_;
	int month_;//1 to 12
	int day_;//1 to 31
	
	public:
		int return_day_by_month(int i){//즁아,,,이거슨 파이썬이 아닌거시여!!!!! 
			if (i==2){
				return 28;
			}
			
			//int *array=new int[7]; 얜 와 안되누  
			int array[7]={1,3,5,7,8,10,12};
			
			for(int m=0;m<7;m++){//알겠어??? :가 아니라 {}라고오오오구마엔 사이다 
				if(array[m]==i){
					//delete[] array;
					return 31;
				}
			}
			
			//delete[] array;
			return 30;
		}
		
		void SetDate(int year, int month, int day){
			year_=year;
			month_=month;
			day_=day;
		}
		
		void AddDay(int inc){
			//초과하는 경우 
			if (return_day_by_month(month_)<day_+inc){
				month_+=1;
				day_=day_+inc-return_day_by_month(month_);
			}
			//일반적인 경우 
			else{
				day_+=inc;
			}
		}
				
		void AddMonth(int inc){
			//초과하는 경우
			if (month_+inc>12){
				year_+=1;
				month_=month_+inc-12;
			}
			else
				month_=month_+inc;
		}
		
		void AddYear(int inc){
			year_+=inc;
		}
		
		void ShowDate(){
			std::cout<<year_<<"년 "<<month_<<"월 "<<day_<<"일 입니다."<<std::endl;
		}
			
};

int main(){
	Date test;
	test.SetDate(2021,7,21);
	test.ShowDate();
	test.AddDay(11);
	test.ShowDate();
	test.AddMonth(6);
	test.AddYear(3);
	test.ShowDate();
}
 
