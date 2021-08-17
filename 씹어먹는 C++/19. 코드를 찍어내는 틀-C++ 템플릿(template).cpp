#include <iostream>
#include <string>
//그런데 위 bubble_sort 함수에서는 한 가지 부족한 점이 있습니다. 만약에, 정렬 순서를 역순으로 하고
//1~3, 4
template <typename T>
class Vector{
	T* data;
	int capacity;
	int length;
	
	public:
		typedef T value_type;//which type will be saved
		
		Vector(int n=1): data(new T[n]), capacity(n), length(0) {}//constructor
		void push_back(T s){//push
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
		T operator[](int i) {	return data[i];}//random access by using [] operator
		void remove(int x){//remove data that is in random location
			for(int i=x+1;i<length;i++)
				data[i-1]=data[i];
			length--;
		}
		int size(){return length;}//get vector's size
		void swap(int i, int j){//change location with i and j
			T temp=data[i];
			data[i]=data[j];
			data[j]=temp;
		}
		~Vector(){//destructor
			if(data)
				delete[] data;
		}
}; 

//template specialization part
template <>//no exsist other typename work just specializing of bool argument. must exist template<> code! 
class Vector<bool>{//when Vector class used with bool argument.
	unsigned int* data;//for prevent problem when we use shift operate using int.
	int capacity;//data array's size
	int length;//real bool's size. 1 capacity->32 bools.
	
	public:
		typedef bool value_type;//which type will be saved
		
		Vector(int n=1): data(new unsigned int[n/32+1]), capacity(n/32+1), length(0){//constructor. int is 4 byte so int is 32bit. so int can save 32 bool data.
			for(int i=0; i<capacity; i++)
				data[i]=0;//initializing
		}
		void push_back(bool s){//push
			if(capacity*32<=length){
				unsigned int* temp=new unsigned int[capacity*2];
				for(int i=0; i<capacity; i++)
					temp[i]=data[i];//data save
				for(int i=capacity; i<2*capacity;i++)
					temp[i]=0;//initializing
					
				delete[] data;
				data=temp;
				capacity*=2;
			}
			if(s)
				data[length/32]|=(1<<(length%32));//if true is added, change that bit to true. some bit or 1 is absolutely 1. with protection of around bit's value.
			
			length++;
		}
		bool operator[](int i){ return (data[i/32]&(1<<(i%32)))!=0; }//access for random location...???
		void remove(int x){//remove element in random location
			for(int i=x+1; i<length; i++){//not just overcopy because just reading of left or right element is complex.
				int prev=i-1;
				int curr=i;
				
				if(data[curr/32]&(1<<(curr%32)))//if curr's bit is 1, make prev to 1
					data[prev/32]|=(1<(prev%32));
				else{//else, make prev to 0
					unsigned int all_ones_except_prev=0xFFFFFFF;
					all_ones_except_prev^=(1<<(prev%32));
					data[prev/32]&=all_ones_except_prev;
				}
			}
			length--;
		}
		int size(){return length;}//get vector's size
		~Vector(){
			if(data)
				delete[] data;
		}
}; 

template <typename Cont>//function template!
void bubble_sort(Cont& cont){//use reference
	for(int i=0; i<cont.size(); i++)//if Cont doesn't have these function like .size() then, compiler split errors
		for(int j=i+1; j<cont.size(); j++)
			if(cont[i]>cont[j])
				cont.swap(i, j);
}

int main(){
	Vector<int> int_vec;
	int_vec.push_back(3);
	int_vec.push_back(1);
	int_vec.push_back(2);
	int_vec.push_back(8);
	int_vec.push_back(5);
	int_vec.push_back(3);
	
	std::cout<<"정렬 이전 ---- "<<std::endl;
	for(int i=0; i<int_vec.size(); i++)
		std::cout<<int_vec[i]<<" ";
	
	std::cout<<std::endl<<"정렬 이후 ---- "<<std::endl;
	bubble_sort(int_vec);//Vector<int> will be sent to Cont typename in template function. runtime error!
	for(int i=0; i<int_vec.size(); i++)
		std::cout<<int_vec[i]<<" ";
	std::cout<<std::endl;
	
	Vector<std::string> str_vec;
	str_vec.push_back("hello");
	str_vec.push_back("world");
	std::cout<<"-------std::string vector------"<<std::endl;
	std::cout<<"first element : "<<str_vec[0]<<std::endl;
	std::cout<<"second element : "<<str_vec[1]<<std::endl;
	
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

	std::cout << "-------- bool vector ---------" << std::endl;
	for (int i = 0; i < bool_vec.size(); i++) {
  		std::cout << bool_vec[i];
	}
	std::cout << std::endl;
}

/*4
template <typename T>
T max(T& a, T& b){
	return a>b?a:b;
}//no convert to code before instantiation while compiling!

int main(){
	int a=1, b=2;
	std::cout<<"Max ("<<a<<", "<<b<<") ? : "<<max(a,b)<<std::endl;//class template instantiation! convert code to int! (we can also use <int> but compiler do instantiation with a, b type sutomatically)
	
	std::string s="hello", t="world";
	std::cout<<"Max ("<<s<<", "<<t<<") ? : "<<max(s,t)<<std::endl;
}*/

/*
[0.	들어가기에 앞서]
1.	벡터(vector)는 가변 길이 배열로, 사용자가 배열처럼 사용하는데 크기를 마음대로 줄이고 늘일 수 있는 편리한 자료형이다.
2.	스택(stack)의 경우, 나중에 들어간 것이 먼저 나온다(LIFO-last in first out)형태의 자료형으로 pop과 push를 통하여 여러가지 작업들을 할 수 있다.
3.	대신, 문제점은 데이터 타입이 바뀔 때마다 다른 벡터를 만들어주어야 한다는 점이다. 지금까지는 string데이터만 처리하도록 하였다. 
	물론, 데이터타입이 다른 벡터를 만드는 것은 쉬운 일이다. 그냥 코드의 type부분만 바꿔주면 되기 때문이다. 마치 어떠한 틀에 타입을 집어넣으면 원하는 코득가 딱딱 튀어나오는 틀 같이.

[1.	C++ 템플릿(template)]
1.	위와같은 작업을 C++에서는 template이라는 이름으로 지원하고 있다. 이전까지는 인자로 특정한 '값' 혹은 '객체'를 전달해왔지만, '타입'그 자체를 전달한 적은 없었다.
2.	정의방법 template <typename T> 이는 아래에 정의되는 클래스에 대해 템플릿을 정의하고, 템플릿 인자로 T를 받게 되며, T는 반드시 어떠한 타입의 이름임을 명시하고 있다.
3.	위의 경우, 템플릿 문장 아래 오는 것이 class Vector이므로 이 Vector클래스에 대한 템플릿임을 명시하는데, 만약에 밑에 오는 것이 함수일 경우 함수에 대한 템플릿이 된다.
4.	가끔 template <class T>라고도 표시하는데, template <typename T>와 동일한 표현이다. 그렇기에 표시를 class T라고 해서 T자리에 클래스가 와야 하는 것은 아니다.
	(p.s 위 둘은 정확히 같은 의미를 나타내지만, 되도록 typename T를 사용하는 것을 권장한다. C++을 처음 만든 Bjarne Stroustrup은 처음에 template의 인자로 새로운 키워드를 만들고 싶지 않아 class라는 이름을 사용하였다. 
	하지만 시간이 흘러 C++위원회에서 이로인한 혼동을 막기 위해_'class T자리엔 무조건 class!' typename이라는 이름을 사용하기 시작했고, 이전 코드와의 호환을 위해서 class T도 그대로 남겨두었다.) 
5.	이렇게 정의한 템플릿에 인자에 값을 전달하기 위해서는 Vector<int> int_vec;과 같이 <>안에 전달하려는 것을 명시해주면 된다.  
7.	컴파일러는 Vector<int> int_vec;이라는 코드를 보고 Vector의 T를 int로 치환하여 새로운 코드를 작성하게 된다. 
8.	위와 같이 클래스 템플릿에 인자를 전달하여 실제 코드를 생성하는 것을 클래스 템플릿 인스턴스화(class template instantiation)이라고 한다.
	즉, 템플릿이 인스턴스화 되지 않고, 덩그러니 있다면 컴파일 시에 아무런 코드로 변환되지 않는다. 템플릿은 반드시 인스턴스화되어야만 비로소 컴파일러가 실제 코드를 생성하게 된다. 
9.	예외적으로, 일부 타입에 대해선느 다른 방식으로 처리해야 하는 경우가 있는데, 바로 bool데이터를 보관하는 벡터를 생각해볼 때이다.
	Vector<bool> bool_vec; 이용상에는 문제가 없지만, C++에서 기본적으로 사용하는 처리 단위가 1byte라는 점을 고려해야 한다.
	즉, bool데이터형은 1bit만으로 충분히 저장할 수 있지만 8bit를 사용하여 1개 bool값을 저장한다는 것은 엄청난 메모리 낭비가아닐수 없다. 따라서 Vector<bool>에 대해서는 특별히 따로 처리해주어야 한다.

[3. 템플릿 특수화(template specializationi)] 
1.	이와 같이 일부 경우에 대하여 따로 처리하는 것을 템플릿 특수화라고 한다. 
2.	만약 template <typename A, typename B, typename C>에서 A가 int고, C가 double일때를 따로 처리하고 싶다면 template <typename B> class test<int, B, double>{}처럼 처리할 수 있다.
 	만약 B조차도 특수화 하고 싶다면, template<> class test<int, int, couble>{}; 처럼 전달하는 쳄플릿 인자가 없더라도 특수화하고싶다면 template,.라도 남겨줘야 한다. 
3.	그렇다면 bool벡터의 경우, template<> class Vector<bool>{}와 같이 따로 처리해주면 된다. 여기서 int배열을 이용할 것인데, int의 경우 32bit이므로, 1개의 int는 32개의 bool데이터를 저장할 수 있고, 따라서 N번째 bool데이터는 N/32번째 int안에 저장되게 된다.
4.	어려워서 패숭

[4.	함수 템플릿(Function template)]
1.	만약 함수 템플릿에서 사용한 함수를 전달한 인자가 갖고있지 않을 경우에 오류를 뿜어낸다. 이는 런타임 시 발생하는데, 텀파일러가 type이 argument로 들어올 때 코드를 완성하여 사용하기 때문이다.
2.	이렇게 컴파일 시에 모든템플릿 들이 인스턴스화된다는 사실을 가지고 템플릿 메타프로그래밍(template metaprogramming)이라고 하는 방식으로 코들르 짤 수 있다.
 
*/
