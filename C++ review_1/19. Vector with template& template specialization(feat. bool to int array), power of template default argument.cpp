#include <iostream>
#include <string>

template <typename T>//=template <class T>
class Vector{
	T* data;
	int capacity;
	int length;
	
	public:
		typedef T value_type;//which type will be saved
		
		Vector(int n=1): data(new T[n]), capacity(n), length(0){}//CONSTRUCTOR
		void push_back(T s){//PUSH_BACK
			if(capacity<=length){
				T* temp=new T[capacity*2];
				for(int i=0; i<length; i++)
					temp[i]=data[i];
				delete[] data;
				data=temp;
				capacity*=2;
			}
			data[length]=s;
			length++;
		}
		T operator[](int i){ return data[i]; }//ACCESS BY []
		void remove(int x){//REMOVE
			for(int i=x+1;i<length;i++)
				data[i-1]=data[i];
			length--;
		}
		int size(){ return length; }//LENGTH
		void swap(int i, int j){//SWAP
			T temp=data[i];
			data[i]=data[j];
			data[j]=temp;
		}
		~Vector(){//DESTRUCTOR
			if(data)
				delete[] data;
		}
}; 

template <>//template specialization
class Vector<bool>{//use int type
	unsigned int* data;//for prevention of problem in shift
	int capacity;//size of created data
	int length;//real bool data
	
	public:
		typedef bool value_type;
		
		Vector(int n=1): data(new unsigned int[n/32+1]), capacity(n/32+1), length(0){//CONSTRUCTOR
			for(int i=0; i<capacity; i++)
				data[i]=0;//initialization to ZERO
		}
		void push_back(bool s){//PUSH_BACK
			if(capacity*32<=length){
				unsigned int* temp=new unsigned int[capacity*2];
				for(int i=0; i<capacity; i++)//it's ok because 32 bool data is save in one int data. so if we move one int data normally, automatically 32 bool data will be moved
					temp[i]=data[i];
				for(int i=capacity; i<2*capacity; i++)//initialization to ZERO
					temp[i]=0;
				
				delete[] data;
				data=temp;
				capacity*=2;
			}
			
			if(s)//if push data is true
				data[length/32]|=(1<<(length%32));//make it to true. or operation is useful because it can protect initial value. ???
			
			length++;
		}
		bool operator[](int i){ return (data[i/32] & (1<<(i%32)))!=0; }//ACCESS BY []
		void remove(int x){//REMOVE
			for(int i=x+1; i<length; i++){
				int prev=i-1;
				int curr=i;
				
				if(data[curr/32]&(1<<(curr%32))){//curr is 1
					data[prev/32]|=(1<<(prev%32));//prev to 1
				} else{//curr is 0
					unsigned int all_ones_except_prev=0xFFFFFFFF;//value that is true except of location(we will delete) to false
					all_ones_except_prev^=(1<<(prev%32));//^ is XOR.  
					data[prev/32]&=all_ones_except_prev;//remove prev by 0
				}
			}
			length--;
		}
		int size(){ return length; }//GET SIZE
		~Vector(){//DESTRUCTOR
			if(data)
				delete[] data;
		}
};

template <typename Cont>//template function
void bubble_sort(Cont& cont){
	for(int i=0; i<cont.size(); i++)
		for(int j=i+1; j<cont.size(); j++)
			if(cont[i]>cont[j])
				cont.swap(i, j);
}

template <typename Cont, typename Comp>
void bubble_sort(Cont& cont, Comp& comp){
	for(int i=0; i<cont.size(); i++)
		for(int j=i+1; j<cont.size(); j++)
			if(!comp(cont[i], cont[j]))//use Functor
				cont.swap(i, j);
}

struct Comp1{//Functor
	bool operator()(int a, int b){ return a>b; }
};
struct Comp2{
	bool operator()(int a, int b){ return a<b; }
};

int main(){
	Vector<int> int_vec;
	int_vec.push_back(3);
	int_vec.push_back(2);
	
	bubble_sort(int_vec);
	std::cout<<"[normal sort]"<<std::endl;
	std::cout<<"-------- int vector --------"<<std::endl;
	std::cout<<"first element: "<<int_vec[0]<<std::endl;
	std::cout<<"second element: "<<int_vec[1]<<std::endl<<std::endl;
	
	Comp1 comp1;
	bubble_sort(int_vec, comp1);
	std::cout<<"[comp1 sort]"<<std::endl;
	std::cout<<"-------- int vector --------"<<std::endl;
	std::cout<<"first element: "<<int_vec[0]<<std::endl;
	std::cout<<"second element: "<<int_vec[1]<<std::endl<<std::endl;
	
	Vector<std::string> str_vec;
	str_vec.push_back("hello");
	str_vec.push_back("world");
	std::cout<<"-------- std::string vector --------"<<std::endl;
	std::cout<<"first element: "<<str_vec[0]<<std::endl;
	std::cout<<"second element: "<<str_vec[1]<<std::endl<<std::endl;
	
	Vector<bool> bool_vec;
	bool_vec.push_back(true);
	bool_vec.push_back(true);
	bool_vec.push_back(false);
	bool_vec.push_back(false);
	bool_vec.push_back(false);
	bool_vec.push_back(true);
	bool_vec.push_back(false);
	bool_vec.push_back(true);
	bool_vec.push_back(false);
	bool_vec.push_back(true);
	bool_vec.push_back(false);
	bool_vec.push_back(true);
	bool_vec.push_back(false);
	bool_vec.push_back(true);
	bool_vec.push_back(false);
	bool_vec.push_back(true);
	bool_vec.push_back(false);
	bool_vec.push_back(true);
	bool_vec.push_back(false);
	
	std::cout<<"-------- bool vector --------"<<std::endl;
	for(int i=0; i<bool_vec.size(); i++)
		std::cout<<bool_vec[i];
	std::cout<<std::endl;
}

//power of template default argument
template <typename T>
struct Compare{//FUNCTOR FOR COMPARE
	bool operator()(const T& a, const T& b) const{ return a<b; }
};

template <typename T, typename Comp=Compare<T>>
T Min(T a, T b){
	Comp comp;
	if(comp(a, b))
		return a;
	return b;
}

int main(){
	int a=3, b=5;
	std::cout<<"Min "<<a<<", "<<b<<" :: "<<Min(a, b)<<std::endl;//we don't have to Compare<int> comp1; Min<comp1>(a,b);
	
	std::string s1="abc", s2="def";
	std::cout<<"Min "<<s1<<", "<<s2<<" :: "<<Min(s1, s2)<<std::endl;
}

/*
1.	template <class T>와 template <typename T>는 동일하다. 다만 class T는 이전 버전의 호환을 위해 존재한다. 
2.	클래스 템플릿에 인자를 전달해서 실제 코드를 생성하는 것; 클래스 템플릿 인스턴스화(class template instantiation)
3.	비트 연산시 0을 or하거나 1을 and하면 기존의 값을 보존하며 값을 가져올 수 있다. 
4.	Functor는 객체지만 함수인 척 하는 함수를 말한다. 이를 함수 객체(function object)라고 한다. Functor없이 C처럼 함수 포인터를 넘기는 것보다 Functor를 컴파일러가 inline화 할 수 있기에 작업이 더 빨라진다. 
5.	템플릿 인자를 일반 인자처럼 <int num>사용할 수도 있다. 다만 타입이 제한적이다. 주로 컴파일타임에 값이 정해져야 하는 배열의 크기 등을 템플릿 인자로 명시한다. 이 또한 default값을 세팅할 수 있다. 
6.	템플릿을 사용한다는 것은 컴파일 타임에 인스턴스화 된다는 것이고 이는 즉, 스택영역에 할당됨을 의미한다. 
7.	템플릿에 디폴트 인자를 사용할 수 있다는 것은, Comp와 같은 Functor를 기본으로 세팅함으로써 불필요한 인자전송을 없애줄 수 있다. 
*/
