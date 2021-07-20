/*1. 메모리의 관리
컴파일러에 의해 어느정도 안정성이 보장되는 스택(stack)과는 다르게 힙은 사용자가 스스로 제어하는 부분으로
책임이 있다.
C에서의 malloc과 free를 C++에서도 사용이 가능하나, 언어 차원에서 지원하는 것이 new와 delete다.
*/

/*2. new와 delete의 사용
#include <iostream>

int main(){
	int* p=new int;//타입을 명시해 주면, 그 타입의 크기만큼 공간을 할당한다. 
	*p=10;//값의 저장. 
	
	std::cout<<*p<<std::endl;
	
	delete p;//p에 할당된 공간 해제 
	return 0;
} 

만약 지역변수를 무리하게 delete로 할당을 해제해버리려고 한다면 Heap이 아닌 공간을 해제하려 한다는 경고메시지. 
#include <iostream>

int main(){
	int a=5;
	delete &a;
	return 0;
} 
*/

/*3. new로 배열 할당하기. 
#include <iostream>

int main(){
	int arr_size;//배열의 크기를 잡을 변수 정의.
	 
	std::cout<<"array size: ";
	std::cin>>arr_size;//그 값을 입력받음
	 
	int *list=new int[arr_size];//배열을 생성할 때에는 []을 이용하여 배열의 크기를 넣어준다.
	//왜냐면 위에 2.에서 그 타입의 크기만큼 공간을 할당한다고 하는데, 동적 할당 시 사용할 정확한
	//크기를 알아야 하기에 단순히 new int를 하면 int1개의 변수 만큼의 공간이 할당되니
	//int[arr_size]를 통해 정확한 모든 크기를 알려준다. 
	//정말 말 그대로 new(새로운 공간 할당) int[arr_size](이만큼) 
	
	for (int i=0;i<arr_size;i++){//아래의 p.s에 따라 만약 함수 밖에서 i를 정의 했더라도 컴파일러는 
		std::cin>>list[i];       //가가운 범위 내의 변수를 참조하기 때문에 오류가 발생할 가능성이 감소. 
	}
	for (int i=0;i<arr_size;i++){
		std::cout<<i<<"th element of list: "<<list[i]<<std::endl;
	}
	delete[] list;//리스트의 해제. 즉 new-delete, new[]-delete[]가 쌍을 이룸.수미상관? 
	return 0;
} 

+p.s 어떤 변수를 사용할 때 컴파일러는 그 변수를 가장 가까운 범위(scope)부터 찾게 된다.
int a=4;
{
	std::cout<<"외부의 변수 1"<<a<<std::endl;
	int a=3;
	std::cout<<"내부의 변수"<<a<<std::endl; 
} 
std::cout<<"외부의 변수 2"<<a<<std::endl; 
의 경우 4 3 4 가 출력됨. 컴파일러는 변수를 찾을 때 가장 가까운 범위 내에서 찾는다. 여기서의 범위: {} 
*/

/*4. 돌아온 마이펫_C언어 강의에서 switch문을 배우며 간단하게 만든 프로그램 
#include <iostream>

typedef struct Animal{//animal 구조체 제작 및 typedef 사용하여 struct Animal->Animal로 간추림 
	char name[30];//이름
	int age; //나이
	
	int health;//체력
	int food;//배부른 정도
	int clean;//깨끗한 정도 
} Animal;

void create_animal(Animal *animal){
	std::cout<<"동물의 이름? ";
	std::cin>>animal->name;
	
	std::cout<<"동물의 나이? ";
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
	//하루가 지나면
	animal->health-=10;
	animal->food-=30;
	animal->clean-=20; 
}

void show_stat(Animal *animal){
	std::cout<<animal->name<<"의 상태"<<std::endl;
	std::cout<<"체력: "<<animal->health<<std::endl;
	std::cout<<"배부름: "<<animal->food<<std::endl;
	std::cout<<"청결: "<<animal->clean<<std::endl;
}

int main(){
	Animal *list[10];
	int animal_num=0;
	
	for(;;){
		std::cout<<"1. 동물 추가하기"<<std::endl;
		std::cout<<"2. 놀기"<<std::endl;
		std::cout<<"3. 상태 보기"<<std::endl;
		
		int input;
		std::cin>>input;
		
		switch(input){
			int play_with;
			case 1:
				list[animal_num]=new Animal;//Animal을 new로 생성하면  
				create_animal(list[animal_num]);//create_animal함수를 통하여 값을 초기화 
				animal_num++;
				break;
			case 2:
				std::cout<<"누구랑 놀게? : ";
				std::cin>>play_with;
				if(play_with<animal_num) 
					play(list[play_with]);//놀기를 호 출 
				break;
			case 3:
				std::cout<<"누구껄 보게? : ";
				std::cin>>play_with;
				if (play_with<animal_num)
					show_stat(list[play_with]);//상태보기를 호출 
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

위의 코드에서 상당한 낭비 같은 부분: 
1) play를 호출하려면 list[play_with]를 전달해야함
근데 그냥 Animal구조체 자체에 함수를 만들어서 각 구조체 변수가 각각 자신의 함수를 가지게 되는 것은?
그럼 list[play_with]->play()와 같이 변수가져오듯 함수를 호출하여 자신의 데이터를 이용하여 처리하게끔.
*이렇게 한다면 play함수에 인자를 전달할 필요도 없을 뿐 더러 play함수 내에 animal->health로 접근하지 않고
자기 자신의 함수이기때문에 그냥 health로도 접근이 가능하다는것. 
2) line125~126에 new Animal을 통해 생성한 다음에 반드시 create_animal을 호출해야만 값이 초기화 됨.
이는 만약 프로그래머가 실수로 new Animal을 생성한 후 create_animal을 하지 않으면, 초기화 되지 않은
값에 연산을 하는 결과가 발생하게 됨.
즉. new가 새로운 Animal을 할당할 때 자동으로 호출되는 함수가 있다면 자동으로 초기화해서 오류가
생기지 않게 막을 수 있다. 

아니 설명을 기가막히게 하네 이보쇼 당신 뭐하는 양반이요? 갓에 싸인좀 해주시오.

3) 위의 동물 프로그램이 크나큰 인기를 얻어서 확장팩을 개발하려 하는데 Animal이라고 정의했던 것을 세분화하여
Bird, Fish등으로 나누어 처리하려고 함. bird와 fish는 animal과 기본적으로 유사하지만 새는 고도를 나타내는
변수인 int height;가 새로 추가되고, fist는 수심을 나타내는 변수인 int deep;이 추가됨. 그렇다면 코드는
typedef struct Bird {
  char name[30];  // 이름
  int age;        // 나이

  int health;  // 체력
  int food;    // 배부른 정도
  int clean;   // 깨끗한 정도

  // 여기까지는 Animal 과 동일하다.
  int height;  // 나는 고도

} Bird;

typedef struct Fish {
  char name[30];  // 이름
  int age;        // 나이

  int health;  // 체력
  int food;    // 배부른 정도
  int clean;   // 깨끗한 정도

  // 여기까지는 Animal 과 동일하다.
  int deep;  // 현재 깊이

} Fish;
와 같이 됨. 즉 Animal과 거의 똑같지만 조금 다른 것 때문에 구조체를 새로 두개나 만들어야 함.
그냥 Animal과 동일한 부분은 가져다 쓰고 새로 추가된 부분만 추가하면 안되는가? 
만약 위와 같이 관리한다면 더이상 Animal*배열 하나가 아닌 Fish*, Bird*따로 관리해야할 뿐더러
play, show_stat함수도 모두 Animal, Bird, Fish에 따라 각각 새로 작성해야 함.
즉. int height, int deep때문에 코드의 2배를 써야한다는 것. 
C언어라면 이 모든것을 꿋꿋이 함. 객체지향프로그래밍이 도입되는 순간이 바로 여기. 
*/



/*정리
1. new와 delete를 알아보기에 앞서, 동적할당은 스택(stack)에 비해 heap영역을 사용하여 프로그래머가
   직접 제어하므로 책임성이 있다.
2. C언어에서의 malloc과 free함수 역시 c++에서 사용이 가능하나, 언어적인 차원에서 new와 delete를 지원하며
   malloc의 역활은 new로, free는 delete로 사용한다. 
3. int *p=new int;처럼 type *pointer=new type꼴로 사용하며, new 뒤에 명시된 자료형의 크기만큼 메모리가 할당된다.
   값의 사용은 *를 사용하여 *p꼴로 사용하며, 메모리를 해제할 때는 delete p;와 같이 해제한다. 
4. 만약 delete를 이용하여 삭제하는 변수가 new를 사용하여 heap영역에 할당된 변수가 아닌 stack영역에 할당된 지역변수라면,
   heap영역이 아닌 영역의 메모리를 해제하려 한다는 경고메시지가 출력된다.
5. 배열을 new로 할당하려면, int *p=new int[size];처럼 할당하면 된다. 즉 new 뒤에 오는 자료의 크기만큼 할당한다. 
   또한 이의 사용은 애초에 int arrat[size]에서 array는 주소를 가리키고, 값의 사용은 array[0]와 같이 하는데,
   위의 p는 이미 메모리의 주소를 가리키기에 일반 배열과 같이 p[0]식으로 접근하면 된다. 
6. new로 인하여 동적할당 된 메모리의 해제는 일반 delete p;가 아닌 delete[] p;로 한다.
   즉, new-delete, new[]-delete[]가 한 쌍이다.
   
7. 컴파일러는 어떤 변수를 사용할 때 가장 가까운 범위(scope_{}중괄호)에 있는 변수를 사용함.
   이는 for{}문 안에서 정의된 i라는 변수의 이름이 for{}외부의 i변수와 이름이 같을 때, 오류발생을 막아줌.
8. 구조체의 형성시 반드시 호출되어야 하는 함수에게 구조체를 넘길 때 인자로 구조체가 들어간다는 점, 
   반드시 호출되어야 하는 함수를 실수로 호출하지 않았을때의 오류발생가능성, 
   비슷한 구조체의 정의를 매번 새롭게 해야하고, 이 관리를 다른 구조체기에 하나의 리스트로 못한다는 점, 
   구조체에 적용시킬 함수의 인자전달에 animal->health와 같은 방법으로 귀찮게 전달한다는 점의
   C의 단점이 객체지향프로그래밍을 접목한 C++에서 해결이 되기 시작함. 
*/ 
