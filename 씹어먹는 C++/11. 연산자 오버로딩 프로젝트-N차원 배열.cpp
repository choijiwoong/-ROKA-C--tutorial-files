#include <iostream>
//연한 사실이지만, 디폴트 인자들은 함수의맨 마지막 인자 부터 '연속적으로'만 사용할 수 있습니다. 왜냐하면 만일 우리가 디폴트 인자를
class Array;
class Int;

class Array{
	friend Int;
	
	const int dim;//tensor size. how deep? level.
	int* size; //size[0]*size[1]*...*size[dim-1] array.(array[3][2][3]'s 323 save this array. size information.
	
	struct Address{//private struct. class in class. struct is class all element is public.
		int level;//how deep
		void* next;//next array(low tensor) address by type. pointer for access next element by +1 to next.
	};
	Address* top;//start point
	
	public:
		Array(int dim, int* array_size);
		Array(const Array &arr);
		~Array();
		
		void initialize_address(Address *current);//recursive function that's same 'deep first search'.
		void delete_address(Address *current);
		void copy_address(Address *dst, Address*src);
		
		Int operator[](const int index);
};
Array::Array(const Array &arr):dim(arr.dim){//copy constructure.
	size=new int[dim];
	for(int i=0;i<dim;i++) size[i]=arr.size[i];
	
	top=new Address;//same process regardless of copy constructure. top is same. always.
	top->level=0;//top set
	
	initialize_address(top);//make spaces processs till here.
	
	copy_address(top, arr.top);//content copy
}
Array::Array(int dim, int* array_size):dim(dim){//Constructor of Array class with initializer list.
			size=new int[dim];//allocate size to dim.
			for(int i=0;i<dim;i++) size[i]=array_size[i];//size saves how many tensors we make.
			
			top=new Address;//top set
			top->level=0;
			
			initialize_address(top);//initialize start.
		}
void Array::initialize_address(Address *current){//argument type is pointer of Address structure. up to down.
	if(!current) return;//exception empty
	if(current->level==dim-1){//stop condition. rule2 in recursive function.
		current->next=new int[size[current->level]];//current's next is allocated by Address structure 
		return;//current->next is pointer.
	}
	current->next=new Address[size[current->level]];//size is member array that has user's input how many tensor we make.
	for(int i=0;i!=size[current->level];i++){//added element(same dim, different poket) to pass same process.
		(static_cast<Address *>(current->next)+i)->level=current->level+1;//current->next to Address(casting) and 
		//new allocated address for Address can be accessed by +1 at initial memory location, and set level.
		initialize_address(static_cast<Address *>(current->next)+i);//current->next is allocated by list as Address.
	}//so +1 means next element of current->next. same dim, different element. amount of its is in size[]
}
void Array::delete_address(Address *current){
	if(!current) return;//exception empty
	for (int i=0; current->level<dim-1&&i<size[current->level];i++){//all
		delete_address(static_cast<Address *>(current->next)+1);//Recursive function. 
	}
	if(current->level==dim-1){//is current is last level
		delete[] static_cast<int *>(current->next);//int data is in last level. current->next has Address type. so we have to cast to int*
	}
	delete[] static_cast<Address *>(current->next);//until last level, Address deallocation.
}
void Array::copy_address(Address *dst, Address *src){
	if(dst->level==dim-1){
		for(int i=0;i<size[dst->level];i++)
			static_cast<int *>(dst->next)[i]=static_cast<int *>(src->next)[i];//if we not use [i] and use just pointer, delete error.
		return;
	}
	for(int i=0;i!=size[dst->level];i++){//for all element in same level.
		Address *new_dst=static_cast<Address *>(dst->next)+1;//next's default set is void. so we has to cast to specific type before use.
		Address *new_src=static_cast<Address *>(src->next)+1;//next location save
		copy_address(new_dst, new_src);//and recursive. for all data copy, use new Address.
	}
}
Array::~Array(){//main process is work in Address, so we have to delete just left variables.
	delete_address(top);//delete top that is root memory.
	delete[] size;//delete size that is allocated list in member variable.
}
Int Array::operator[](const int index){//???
	return Int(index, 1, static_cast<void *>(top), this);
}

class Int{
		void* data;//content is same. for data
		
		int level;//for level
		Array* array;//Array object
		
		public:
			Int(int index, int _level=0, void *_data=NULL, Array *_array=NULL);//Wrapper
			Int operator[](const int index);
			operator int();
};

Int::Int(int index, int _level=0, void *_data=NULL, Array *_array=NULL)
		:level(_level), data(_data), array(_array){//def default argument(it can use sequencly when its group at back)
	if(_level<1||index>=array->size[_level-1]){//exception(top level, over index)
		data=NULL;
		return;
	}
	if(level==array->dim){//Int's level==array's dim
		data=static_cast<void *>(//save our int tupe to data
		static_cast<int *>  (static_cast<Array::Address *>(data)->next)  +index);
	} else{//or save address to data
		data=static_cast<void *>(//?????
		static_cast<Array::Address *>  (static_cast<Array::Address *>(data)->next)  +index);
	}
};
Int Int::operator[](const int index){
	if(!data) return 0;
	return Int(index, level+1, data, array);
}
Int::operator int(){
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
[3. operator[] 문제]
1.	N차원 배열의 각각의 각각의 원소에 접근할 수 있을까? []를 취하는 연산자는 있어도 N개의 []들을 취하는 연산자는 없다.
	 arr[1][2][3]; 에서 arr[1]을 처리하고, 객체 T를 리턴하고 (T)[2]가 처리되는 방식으로 해결해보자. 
2.	새로운 객체가 필요하다. arr[1][2]에서 arr[1]을 일반 Array로 처리한다면 arr[1]=2;같은 모순이 생기기 때문이다.
	또한, 1차원에서는 int를, 고차원이면  다른것을 리턴하게 해야하는데, 이는 오버로딩 원칙 상 한가지 인자엔 한가지 리턴만이 가능하다.
	 이때, int처럼 작동하지만 int가 아닌 클래스. int의 Wrapper개념이 사용된다. 
	대략
	class Int{
		void* data;
		
		int level;
		Array* array;
	};

*/
