#include <iostream>

namespace MyArray{//define namespace "MyArray". All class is in namespace'MyArray'. it will make no problem when we define Array class in other library!
	//main concentrating point is that two class is in using in same file. it means that ordering of define is very important. 
	class Array;//tell to compiler Array is in code.
	class Int;//without these define, we can't use friend because compiler do not know exsist of class 'Int'
	
	class Array{
		friend Int;//Int can access to Array's member
		
		const int dim;//how deep tensor
		int* size;//size[0]*size[1]*...*size[dim-1] size array. for size save.ex)Array[1][2][5]
		
		struct Address{
			int level;
			void* next;//In last level(dim-1 level), it locate data array(real data), and the others locate next Address array
		};
		
		Address* top;//top's Address define. for dim=0 that is root address of all process.
		
		public:
			class Iterator{//for reference of Array[2][5][7] without for(for(for(for(...))) by using iterator.
				int* location;//{2,5,7};
				Array* arr;
				
				friend Int;
				
				public:
					Iterator(Array* arr, int* loc=NULL):arr(arr){//constructor ex)Array[4][5]->int loc={4,6}
						location=new int[arr->dim];//allocate space tensor num. ex)2
						for(int i=0;i!=arr->dim;i++)						  //ex)1~2
							location[i]=(loc!=NULL ? loc[i]:0);//location[i]=loc[i] with exception of empty to set zero.
					}
					Iterator(const Iterator& itr):arr(itr.arr){//copy constructor with initializer list.
						location=new int[arr->dim];//allocation_make space.
						for(int i=0;i!=arr->dim;i++) location[i]=itr.location[i];//just copy
					}
					~Iterator() { delete[] location; }//destructor for delete storage.
					Iterator& operator++(){//to make next element(for prefix operator)
						if(location[0]>=arr->size[0]) return (*this);//exception for finish access. Normally, last element+1 of array means first element's address. but this method can't distinguish whether it is finish or not to compiler. so we choose other method if we reach last element of array, set virtual index that is not exsist in array._array[1][2]'s index will set [2,0] in Iterator class for express finish of calculate.
						
						bool carry=false;//In array[2][4], array[0][3]'s next is array[1][0]. it will be expressed by bool carry.
						int i=arr->dim-1;//max index of location.
						do{//???
							location[i]++;//normal way for access next element. last index ++. main action of ++. anyway, we have to add +1 for operator++
							
							if(location[i]>=arr->size[i]&&i>=1){//when over size. when it need carry.
								location[i]-=arr->size[i];//set zero
								carry=true;//carry on
								i--;//access point -- and later, +1 to location[i] in first part of do-while function. 
							}else//we need no carry!
							carry=false;
						} while(i>=0&&carry);//escape condition => if i to -(finish) and no carry.
						return (*this);//set
					}
					Iterator& operator=(const Iterator& itr){//assign operator
						arr=itr.arr;
						location=new int[itr.arr->dim];
						for(int i=0;i!=arr->dim;i++) location[i]=itr.location[i];
						
						return (*this);
					}
					Iterator operator++(int){//(for postfix operator)
						Iterator itr(*this);//for calculate ++ work, it must be real Iterator object.
						++(*this);//++work
						return itr;//return
					}
					bool operator!=(const Iterator& itr){//rather same or not
						if(itr.arr->dim!=arr->dim) return true;//different size pre execute. for delete trash calculattion.
						for(int i=0;i!=arr->dim;i++){
							if(itr.location[i]!=location[i])//different
								return true;
						}
						
						return false;//pass.
					}
					Int operator*();//???
			};
			
			Array(int dim, int* array_size):dim(dim){//Constructor with initializer list for dim.
				size=new int[dim];//allocation for save input data to Array object's size(member variable).
				for(int i=0;i<dim;i++)
					size[i]=array_size[i];//save array_size to object's size array.ex)array={1, 4, 5}; it means array[1][4][5]
					
				top=new Address;//initialize top. allocation.
				top->level=0;//and set value to 0
				
				initialize_address(top);//pass top for process work to make space(array) that has size of array_size.
			}
			Array(const Array& arr): dim(arr.dim){//copy constructor(same process with constructor)
				size=new int[dim];
				for(int i=0;i<dim;i++)
					size[i]=arr.size[i];
				
				top=new Address;
				top->level=0;
				
				initialize_address(top);
				copy_address(top, arr.top);//copy work.
			}
			void copy_address(Address* dst, Address* src){//recursive.
				if(dst->level==dim-1){//escape condition
					for(int i=0;i<size[dst->level];i++)//(modify ++i to i++)
						static_cast<int*>(dst->next)[i]=static_cast<int*>(src->next)[i];//last level copy with type <int*>
					return;//and return
				}//if not last level(Address)
				for(int i=0;i!=size[dst->level];i++){//for all tensor
					Address* new_dst=static_cast<Address*>(dst->next)+i;//for all element of same level
					Address* new_src=static_cast<Address*>(src->next)+i;
					copy_address(new_dst, new_src);//recursive.
				}
			}
			void initialize_address(Address* current){//recursive.
				if(!current) return;//exception of empty
				if(current->level==dim-1){//escape condition check
					current->next=new int[size[current->level]];//get size data to Array.size[current->level] and allocation.
					return;//last level's next means real space for saving data. so make allocation.
				}
				current->next=new Address[size[current->level]];//without last level, it's next means next Address location. so make allocation that has Array.size[current->level]. allocation type is Address. not Address*.
				//same allocation but different objext's next. *current next is allocated by Address "array".
				for(int i=0;i!=size[current->level];i++){//for all element(that is Address) of current->next(that is Address array)_process to next step.
					(static_cast<Address*>(current->next)+i)->level=current->level+1;//element's level set to current->level+1 that means next level. cast for access next by ->. cast is for making Adress* because current->next's is allocated to Address. not Address*
					initialize_address(static_cast<Address*>(current->next)+i);//recursive. cast for make same to argument form that is Address* current. and cast it needed for distinguish of last level(int*) and the others level(Address*). prevent error.
				}
			}
			void delete_address(Address* current){//recursive. depth-first search.
				if(!current) return;//exception to empty.
				for(int i=0;current->level<dim-1&&i<size[current->level];i++){//work condition(recursive)
					delete_address(static_cast<Address*>(current->next)+i);//recursive.
				}
				if(current->level==dim-1){//last level
					delete[] static_cast<int*>(current->next);//cast current->next to int* and delete[] allocated space.
				}//if not last level, it means next Address*
				delete[] static_cast<Address*>(current->next);//delete[] Address*
			}//It's use work condition rather than escape condition. when work condition is back of this code, it call error because before work(recursive), it's already delete alloccation space so we can't access memory for delete.
			Int operator[](const int index);//seperate with member function for actually using of Int class. other member function is not needed Int's information access for modifying. So this function is main of using int class, we must define Int class infront of this function(operator[]). so for ordering, it is seperated with Array class for actual using.
 			~Array(){//destructor for delete of Array object
				delete_address(top);
				delete[] size;
			}
			Iterator begin(){//Iterator initialize
				int* arr=new int[dim];//new arr for allocation
				for(int i=0;i!=dim;i++)
					arr[i]=0;//copy
					
				Iterator temp(this, arr);//copy
				delete[] arr;//deallocation
				
				return temp;//return
			}
			Iterator end(){//last shape is {x,0,0} x is already over normal value for expression of finish
				int* arr=new int[dim];//new arr for allocation
				arr[0]=size[0];//copy over value
				for(int i=1;i<dim;i++)
					arr[i]=0;//left value set 0
					
				Iterator temp(this, arr);//coopy
				delete[] arr;//deallocation
				
				return temp;//return
			}
	};
	//still namespace
	class Int{//int's Wrapper class. for access like int ex)arr[1][2]=3;
		void* data;//for locating address when last level, we can just use it for int* array.
		
		int level;//will distinguish last level or the others
		Array* array;
		
		public:
			Int(int index, int _level=0, void* _data=NULL, Array* _array=NULL):level(_level), data(_data), array(_array){//constructor with initializer list. index is user's input ex)index=3 in [3] at array[7]. access location
					if(_level<1||index>=array->size[_level-1]){//exception wroong input(over size index, no root location that is just address)
						data=NULL;
						return;
					}
					if(level==array->dim){//last level
						data=static_cast<void*>((static_cast<int*>(static_cast<Array::Address*>(data)->next)+index));//Address* for use index. and cast int*(for + index? no.) and void* ???
				} else{//not last level
					data=static_cast<void*>(static_cast<Array::Address*>(static_cast<Array::Address*>(data)->next)+index);//Address* for use index. and cast Address* and void*_similar process.
				}
	};
	
	Int(const Int& i):data(i.data), level(i.level), array(i.array){}//copy constructor with initializer list.
	
	operator int(){//Type conversion operator for wrapper class
		if(data) return *static_cast<int*>(data);//when Int call as wrapper, int's address value is in Int.data so just converse void* to int*
		return 0;
	}
	Int& operator=(const int& a){//when Int(int b) with operator =, converse data to int* and calculate. 
		if(data) *static_cast<int*>(data)=a;//if data is exist.
		return *this;
	}
	Int operator[](const int index){//when Int used with [] like 'Int array[3]=2'
		if(!data) return 0;//exception of empty
		return Int(index, level+1,data,array);
	}
};
Int Array::operator[](const int index){//Array's operator[] work
	return Int(index, 1, static_cast<void*>(top), this);
}//Array[5][3]-> Int(5,1,~,this)[3]->Int(3,2,~,array)->(when array->dim==level)data save.->(wrapper) return <int*>(data)_maybe?
Int Array::Iterator::operator*(){//pointer operator
	Int start=arr->operator[](location[0]);//use Int object fully.
	for(int i=1;i<=arr->dim-1;i++)
		start=start.operator[](location[i]);//save all location data of Iterator to start object
	return start;
}

}//namespace MyArray

int main() {
  int size[] = {2, 3, 4};
  MyArray::Array arr(3, size);

  MyArray::Array::Iterator itr = arr.begin();
  for (int i = 0; itr != arr.end(); itr++, i++) (*itr) = i;
  for (itr = arr.begin(); itr != arr.end(); itr++)
    std::cout << *itr << std::endl;

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 4; k++) {
        arr[i][j][k] = (i + 1) * (j + 1) * (k + 1) + arr[i][j][k];
      }
    }
  }
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 4; k++) {
        std::cout << i << " " << j << " " << k << " " << arr[i][j][k]
                  << std::endl;
      }
    }
  }
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
