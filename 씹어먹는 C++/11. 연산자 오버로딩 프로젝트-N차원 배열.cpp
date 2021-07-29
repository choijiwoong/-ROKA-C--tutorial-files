#include <iostream>

class Array{
	const int dim;//tensor size. how deep? level.
	int* size; //size[0]*size[1]*...*size[dim-1] array.(array[3][2][3]'s 323 save this array. size information.
	
	struct Address{//private struct. class in class. struct is class all element is public.
		int level;//how deep
		void* next;//next array(low tensor) address by type.
	};
	Address* top;//start point
	
	public:
		Array(int dim, int* array_size):dim(dim){//Constructor with initializer list.
			size=new int[dim];//allocate size to dim.
			for(int i=0;i<dim;i++) size[i]=array_size[i];//size saves how many tensors we make.
		}
};

void initialize_address(Address *current){//argument type is pointer of Address structure.
	if(!current) return;//exception empty
	if(current->level==dim-1){//stop condition. rule2 in recursive function.
		current->next=new int[size[current->level]];
		return;
	}
	//부터 시작. 따라서 이 생각을 정리하면 다음과 같은 코드를 짤 수 있습니다. 검색 ㄱㄱ 
}

int main(){
	return 0;
} 

/*
[1.	C++스타일의 캐스팅]
1.	기존의 C언어에서는 2가지의 캐스팅 방법 즉, 컴파일러가 알아서하는 암시적(implicit)캐스팅과, 우리가 직접 지정하는 명시적(explicit)캐스팅이 있었지요.
	ex)암시적캐스팅: int+double->double+double, 명시적캐스팅: void*->int* or double*, ptr=(something *)other_ptr; int_variable=(int)flocat_variable;
	 이는 말도 안되는 캐스팅에 대하여 컴파일러가 오류를 발생시키지 않기에 실수에 취약하며, 코드의 가독성이 떨어집니다.(function((int)variable);
2.	C++에서는 4가지의 캐스팅을 제공하고 있다.
	1) static_cast: 일반적인 타입 변환 
	2) const_cast: 객체의 상수성(const)를 없애는 타입 변환. 즉 const int -> int
	3) dynamic_cast: 파생 클래스 사이에서의 다운 캐스팅(to be continue...)
	4) reinterpret_cast: 위험을 감수하고 서로 관련이 없는 포인터들 사이의 캐스팅
	 이러한 캐스팅을 사용하는 방법은 (원하는 캐스팅 종류)<바꾸려는 타입>(무엇을 바꿀것인가?)이다.
	즉, static_cast로 float타입의 float_variable변수를 int타입의 변수로 타입 변환하기 위해서는
	static_cast<int>(float_variable);이라고 하면 된다. 이는 C의 (int)(float_variable)과 같다. 
[2. N차원 배열 만들기]
1.	N차원의 배열을 구현하는 방법은 크게 2가지 인데, 첫번째로 array[x1][x2]...[xn]을 원한다면, x1*x2*...*xn의 크기의 일차원 배열을 할당한 후, 정확한 위치를 찾아주면 된다.
	두번째로, 더블 포인터를 정의한 뒤에, int* 타입의 x1 크기의 1 차원 배열을 할당하고, 이 int* 배열의 각 원소에 대해서 또 x2 크기의 1 차원 배열을 모두 할당한 것
	int** arr;
	arr = new int*[x1];
	for (int i = 0; i < x1; i++) arr[i] = new int[x2];
	 다만 두번째 방식의 문제점은 첫번째 방식의 경우 정확히 x1*x2만큼의 메모리만 잡아먹지만, 두번째는 포인터의 자체 크기때문에
	x1*x2+x1+1만큼의 메모리를 잡아먹는다.
	 대신 첫번째 방식의 경우 전체 원소수가 int의 크기를 넘어간다면 큰수의 정수 lib를 사용해야 하지만,
	두번째 방식은 한차원의 수가 int를 넘어가지 않는 이상, 메모리가 매우매우큰 배열도 생성할 수 있다는 것이다.  
	 n차원이라고 arr***...*을 할 수 없으니 연결리스트유사 개념을 가져와보자.
	struct Address{
		int level;
		void* next;
	} 
2.	N차원을 생성하는 데에 주로 for문을 사용하지만, 몇중 for문이 될지 모르기에 재귀 함수를 사용하도록 한다.
	-함수체서 처리하는 것, 즉 현재 단계에서 다음 단계로 넘어가는 과정은 무엇인가?_next에 다음 레벨의 Adress배열을 지정해주고, 처리. 
	-재귀 호출이 종료되는 조건은 무엇인가?_Address배열의 레벨이 dim-1일 때. 
	
*/
