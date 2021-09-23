#include <iostream>

//Iterator부터~~~~~~~~~~ 

namespace MyArray{
	class Array;
	class Int;//for friend Int
	
	class Array{
		friend Int;//for use Wrapper class in operator[] overloading part.
		
		const int dim;//dimemsion depth
		int* size;//size[dimension]
		
		struct Address{//Struct(is class that all member is public) in Class! we don't want to open mechanism of Array class.
			int level;//dim-1 points data
			void* next;//points address
		};
		
		Address* top;//Top
		
		public:
			//DEFINITION OF ITERATOR CLASS
			class Iterator{//Iterator
				int* location;//information what element is pointed by iterator. {1,2,3} in arr[1][2][3]
				Array* arr;
				
				friend Int;
				
				public:
					//CONSTRUCTOR OF ITERATOR
					Iterator(Array* arr, int* loc=NULL):arr(arr){
						location=new int[arr->dim];
						for(int i=0; i!=arr->dim; i++)
							location[i]=(loc!=NULL? loc[i]:0);
					}
					//COPY CONSTRUCTOR OF ITERATOR
					Iterator(const Iterator& itr):arr(itr.arr){
						location=new int[arr->dim];
						for(int i=0; i!=arr->dim; i++)
							location[i]=itr.location[i];
					}
					//DESTRUCTOR OF ITERATOR
					~Iterator(){ delete[] location; }
					
					//OPERATOR++ OVERLOADING
					Iterator& operator++(){
						if(location[0]>=arr->size[0])//reference by index out of range
							return (*this);
						
						bool carry=false;//[1][1][3]++ ->[1][2][0] not [1][1][4]
						int i=arr->dim-1;
						do{
							location[i]++;//operator ++
							if(location[i]>=arr->size[i]&&i>=1){//out of size
								location[i]-=arr->size[i];//reset location
								carry=true;//and make carry
								i--;//move i to next dimention
							} else{
								carry=false;
							}
						} while(i>=0&&carry);//i<0&&carry is true==reference by index out of range
						
						return (*this);
					}
					//OPERATOR= OVERLOADING
					Iterator* operator=(const Iterator& itr){
						arr=itr.arr;
						location=new int[itrarr->dim];
						for(int i=0; i!=arr->dim; i++)
							location[i]=itr.location[i];
						
						return (*this);
					}
					Iterator operator++(int){
						Iterator itr(*this);
						++(*this);
						return itr;
					}
					bool operator!=(const Iterator* itr){
						if(itr.arr->dim!=arr->dim)
							return true;
							
						for(int i=0; i!=arr->dim; i++)
							if(itr.location[i]!=location[i])
								return true;
						
						return false;
					}
					Int operator*();//********여기도ㅗㅗㅗㅗㅗㅗㅗㅗㅗㅗㅗㅗㅗㅗㅗㅗㅗㅗㅗㅗㅗㅗㅗㅗ 
					
			};
			//END ITERATOR CLASS
			
			frient Iterator;
			//CONSTRUCTOR OF ARRAY
			Array(int dim, int* array_size):dim(dim){//dim==dimention, array_size==size in each dimention. Let's set!
				size=new int[dim];//array(that saves size) is allocated
				for(int i=0; i<dim; i++)
					size[i]=array_size[i];//save size in each dimention
				
				top=new Address;//make top by address
				top->level=0;//and set level to ZERO
				
				initialize_address(top);//make space for Address and link to top->next
			}
			//COPY CONSTRUCTOR OF ARRAY
			Array(const Array &arr):dim(arr.dim){
				size=new int[dim];//set size
				for(int i=0; i<dim; i++)
					size[i]=arr.size[i];
					
				top=new Address;//set top
				top->level=0;
				
				initialize_address(top);//make space for Address and link to top->next
				copy_address(top, arr.top);//content copy
			}
			
			//ADDRESS TOOLS
			//COPY_ADDRESS (FOR COPY CONSTRUCTOR OF ARRAY)
			void copy_address(Address *dst, Address *src){//copy function that is consisted to recursive vecause of accessing to each Address.
				if(dst->level==dim-1){//In last level
					for(int i=0; i<size[dst->level]; i++)
						static_cast<int *>(dst->next)[i]=static_cast<int *>(src->next)[i];//cast to int *
					return;
				}
				//Normal level
				for(int i=0; i!=size[dst->level]; i++){//to each element in that dimention
					Address *new_dst=static_cast<Address *>(dst->next)+i;//make object of next
					Address *new_src=static_cast<Address *>(src->next)+i;
					copy_address(new_dst, new_src);//pass these to copy_address again.
				}
			}
			//INITIALIZE_ADDRESS
			void initialize_address(Address *current){//it's consisted of recursive. *up to down*
				if(!current) return;//current is empty
				
				if(current->level==dim-1){//stop condition_last dimention.
					current->next=new int[size[current->level]];//set next to int_array for real data not Address.
					return;
				}
				
				current->next=new Address[size[current->level]];//set next to Address
				for(int i=0; i!=size[current->level]; i++){//set each Address's next for next process.
					(static_cast<Address *>(current->next)+i)->level=current->level+1;//set each next->level to current->level+1 (access to next Address's address by +i because it's 'new Address* array' that is saving sequencely. In other word, it points element of i in address array that's start address is current->next)
					initialize_address(static_cast<Address *>(current->next)+i);//recursive call to each element we made.
				}
			}
			//DELETE_ADDRESS
			void delete_address(Address *current){//it's consisted of recursive. *down to up*
				if(!current) return;//current is empty.
				for(int i=0; current->level<dim-1&&i<size[current->level]; i++)//recursive call first for *down to up*
					delete_address(static_cast<Address *>(current->next)+i);//pass current->next of all element to this function.
				
				if(current->level==dim-1)//extra delete for last layer
					delete[] static_cast<int *>(current->next);//delete real data's point
				
				delete[] static_cast<Address *>(current->next);//in Addres layer
			}
			
			
			//OPERATOR[] OVERLOADING
			Int operator[](cosnt int index);//after definition of Array & Int class. because we will use real information of Int.
			//DESTRUCTOR OF ARRAY
			~Array(){
				delete_address(top);
				delete[] size;
			}
			
			//?????????부터ㅓㅓ터ㅓㅓㅓㅓㅓㅓㅓㅓㅓㅓㅓㅓㅓㅓㅓㅓㅓㅓㅓㅓㅓㅓㅓㅓㅓㅓㅓ 
			Iterator begin(){
				int* arr=new int[dim];
				
			}
		};//END ARRAY CLASS
			
		//DEFINITION OF INT CLASS(WRAPPER CLASS)
		class Int{//For operator[] overloading, for express Array array[3][4][6]'s index with not only int, but also level. 
			void* data;//size value in each dimention
			int level;//signed int
			Array* array;//for get current->level
			
			public:
				//CONSTRUCTOR OF INT
				Int(int index, int _level=0, void *_data=NULL, Array *_array=NULL):level(_level), data(_data), array(_array){//(default argument is started at end of arguments for compiler)
					if(_level<1 || index>=array->size[_level-1]){//exception of user's mistake(-1 because [] is started at 0)
						data=NULL;
						return;
					}
					
					if(level==array->dim){//in real data
						data=static_cast<void *>(static_cast<int *>(static_cast<Array::Address *>(data)->next)+index);//data->next to Address* (for access to next element that is in Address* array) & set it to void* for keep data's type. & use Array::Address for prevention of using frient keyword.
					} else{//in Address layer
						data=static_cast<void *>(static_cast<Array::Address *>(static_cast<Array::Address *>(data)->next)+index);//data->next to Address* (for access to next element that is in Address* array) & set it to Address* & set it to void* for keep data's type.(it can become any type)
					}
				}
				//COPY CONSTRUCTOR OF INT
				Int(cosnt Int& i):data(i.data), level(i.level), array(o.array){}
				//TYPE CONVERT OVERLOADING FOR WRAPPER OF INT
				operator int(){
					if(data)//if data is exist
						return *static_cast<int *>(data);//cast
					
					return 0;//if data is empty
				}
				//OPERATOR= OVERLOADING
				Int& operator=(const int& a){
					if(data)
						*static_cast<int *>(data)=a;//???????????
					return this;
				}
				Int operator[](const int index){
					if(!data)//data is empty
						return 0;
				}
		};
		//END INT CLASS
		
		//Array's []OVERLOADING BY INT
		Int Array::operator[](const int index){
			if(!data) //if data is empty
				return 0;
					
			return Int(index, 1, static_cast<void *>(top), this);
		}
			
			
			
	};
} 

/*
1.	내부적으로 어떻게 작동하는지 공개하고 싶지 않다면 클래스 안에 클래스를 생성하면 된다. 
2.	C++에서 구조체는 모든 멤버변수와 함수가 default로 public인 것이라고 생각하면 된다.
3.	임의의 차원이므로 for을 몇개쓸지를 결정할 수 없으니 재귀를 사용한다. 
4.	반복자는 여러 N중 for문을 막기 위해서 사용했다. iterator의 정의와 목적은 단순하다. ++시 다음 원소의 포인터를 가리키면 된다. 
*/
