#include <iostream>
#include <string>

/*1~3, 4, 5
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

template <typename Cont, typename Comp>
void bubble_sort(Cont& cont, Comp& comp){
	for(int i=0; i<cont.size(); i++)
		for(int j=i+1; j<cont.size(); j++)
			if(!comp(cont[i], cont[j]))//comp is not function but it's  used like function
				cont.swap(i, j);
}

struct Comp1{//comp1 object. Function object_Functor!
	bool operator()(int a, int b){//() operator overloading. it will work as function because of () overloading.
		return a>b;
	}
};
struct Comp2{//conp2 object. Function object_Functor!
	bool operator()(int a, int b){//() operator overloading
		return a<b;
	}//thanks to Functor, we can compare two object in bubble_sort funtion.
};

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
	std::cout<<std::endl;
	
	std::cout<<std::endl<<"오름차순 정렬 이후 ---- "<<std::endl;
	//Comp2 comp2;
	bubble_sort(int_vec);//Vector<int> will be sent to Cont typename in template function. runtime error! it compare by <
	for(int i=0; i<int_vec.size(); i++)
		std::cout<<int_vec[i]<<" ";
	std::cout<<std::endl;
	
	std::cout<<std::endl<<"내림차순 정렬 이후 ---- "<<std::endl;
	Comp1 comp1;
	bubble_sort(int_vec, comp1);//it compare by Comp object
	for(int i=0; i<int_vec.size(); i++)
		std::cout<<int_vec[i]<<" ";
	std::cout<<std::endl<<std::endl;
	//both make template instantiation!
	
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

	std::cout <<std::endl<< "-------- bool vector ---------" << std::endl;
	for (int i = 0; i < bool_vec.size(); i++) {
  		std::cout << bool_vec[i];
	}
	std::cout << std::endl;
}*/

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

/*6
template <typename T, int num=5>//defaul argument! add_num(x) possible!!
T add_num(T t){
	return t+num;
} 

int main(){
	int x=3;
	std::cout<<"x : "<<add_num<int, 5>(x)<<std::endl;//if we just use add_num<int>(x), compiler doesn't know what content will be in num variable.
}*/

/*6
#include <array>

template <typename T>
void print_array(const T& arr){//void print_array(const std::array<int, 5>& arr){
	for(int i=0; i<arr.size(); i++)
		std::cout<<arr[i]<<" ";
	std::cout<<std::endl;
} 

int main(){
	std::array<int, 5> arr={1,2,3,4,5};
	for(int i=0; i<arr.size(); i++)
		std::cout<<arr[i]<" ";
		
    std::array<int, 7> arr2 = {1, 2, 3, 4, 5, 6, 7};
    std::array<int, 3> arr3 = {1, 2, 3};
    std::array<int, 5> arr4 = {1, 2, 3, 4, 5};
    print_array(arr2);
    print_array(arr3);
	print_array(arr4);
	
	std::cout<<std::endl;
}*/

//7
template <typename T>
struct Compare{
	bool operator()(const T& a, const T& b) const { return a<b; }
};

template <typename T, typename Comp=Compare<T> >
T Min(T a, T b){
	Comp comp;
	if(comp(a, b))
		return a;
	return b;
}

int main(){
	int a=3, b=4;
	//std::cout<<"min : "<<Min<int, Compare<int>>(a, b);//complex! use defualt template argument!
	std::cout << "Min " << a << " , " << b << " :: " << Min(a, b) << std::endl;//work by default template argument!

    std::string s1 = "abc", s2 = "def";
    std::cout << "Min " << s1 << " , " << s2 << " :: " << Min(s1, s2)<< std::endl;//automatically work!
}


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
3.	bubble_sort함수에는 한가지 부족한 점이 있는데, 바로 역순 정렬이다. 이에 대한 해결책으로는 크게 3가지 정도가 있는데,
	-bubble_sort2를 만들어서 부등호의 방향을 반대로 바꿔준다.
	-operator>를 오버로딩해서 원하는 방식으로 만들어준다.
	-cont[i]와 cont[j]의 비교를 >로 하지 말고 특정 함수에 넣어서 전달한다.
	첫번째 방법과 같은 경우 C언어를 배우는 단계에서나 적합한 방법이다.
	두번째 방법은 우리가 만든 객체를 사욯할 때 적용가능한 방법이다. bool operator<(const customClass& c{} 하지만 위처럼 기본적으로 operator를 오버로딩할 수 없는 상황이라면(ex. int나 string은 이미 내부적으로 operator<가 정의되어 있기에 오버로딩이 불가능하다.)

[5.	함수 객체(Function Object-Funtor)의 도입] 
1.	함수는 아니지만 함수인 척을 하는 객체를 함수 객체(Function Object, Functor)이라고 한다.
2.	C++ 표준 라이브러리의 sort함수 역시, 비교 클래스를 받지 않는
	template <class RandonIt>
	void sort(RandomIt first, RandomIt last);와
	
	template <class RandomIt, class Compare>
	void sort(RandomIt first, RanfomIt last, Compare comp);
	처럼 비교클래스를 받는 위 버전으로 구성되어 있다. 
3.	C의 경우, 클래스를 받는다는 것 자체가 불가능하기에 대신에, 비교작업을 수행하는 함수의 포인터를 받아서 처리가 가능하다.
	물론, Functor을 사용하는 것이 여러모로 편리하다.
	클래스 내부 state를 지정하여 비교 자체가 복잡한 경우에도 사용자가 원하는 방식으로 만들어낼 수 있을 뿐만아니라, 
	함수 포인터로 함술르 받아서 처리한다면 컴파일러가 최적화를 할 수 없지만, Functor를 넘기게 되면 컴파일러가 operator()자체를 인라인화 시켜서 매우 빠르게 작업수행이 가능하다. _대충 C의 매크로함수 같은 

[6.	타입이 아닌 템플릿 인자(non-type template arguments)]
1.	템플릿 인자로 타입이 아닌 값을 전달할 수도 있는데, 아래와 같이 제한적이다.
	-정수 타입들(bool, char, int, long 등등). float과 double은 제외된다.
	-포인터 타입
	-enum 타입(열거형) 
	-std::nullptr_t(널 포인터) 
2.	이렇게 타입이 아니라 템플릿 인자를 활용하는 예시로는 컴파일 타임 간에 값들이 정해져야 하는 것들의 경우다.
	예를 들어 C에서 함수에 배열을 전달할 때 배열의 크기에 대한 정보를 잃어버리게 되는데, 이를 템플릿 인자로서 배열의 크기를 명시한다면(배열의 크기는 컴파일 타임간에 정해지게되니) 완벽하게 문제를 해결할 수 있다.
3.	C++11부터 이런 기능을 가진 배열을 std::array를 통해 사용할 수 있다. 이때 C처럼 배열을 정의할 때 {}를 이용하는데,
	이 {}는 유니폼 초기화(uniform initialization)이라 불리는 C++11에서 추가된 개념인데, 우선 std::array의 생성자를 호출하는 또 하나의 방법이라고 생각하면 된다.
	 한 가지 재미있는 점은, arr은 동적으로 크기가 런타임에서 할당되는 것이 아니라, 일반적인 배열처럼 컴파일 시에 int 5개를 가지는 메모리를 가지고 스택에 할당된다.
	또한 이 배열을 함수에 전달하기 위해서는 그냥 std::array를 받는 함수가 아니라 std::array<int, 5>자체가 하나의 타입이기 때문에 void print_array(const std;:array<int, 5>& arr){}이런 식으로 받아야 한다. 
	하지만 넘모 귀찮쥬? 그래서 템플릿을 사용해버립니다. 
[7. 디폴트 템플릿 인자]
1.	함수에 디폴트 인자를 지정할 수 있던 것 처럼, 템플릿도 디폴트 인자를 지정할 수 있다. 
2.	타입도 마찬가지로 디폴트 지정이 가능하다. 
*/
