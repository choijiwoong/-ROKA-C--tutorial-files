#include <iostream>
#include <typeinfo>
//마찬가지 방법으로 모든 사칙연산들을 구현하자면 아래와 같습니다.
/*0
template <typename T, unsigned int N>//get type, uint by template argument.
class Array{
	T data[N];//database
	
	public:
		Array(T (&arr)[N]){//array constructor. &arr get array, define size as N(unsigned int) and type is T in template argument.
			for(int i=0; i<N; i++)//for all data in array,
				data[i]=arr[i];//copy to data.
		}
		
		T* get_array(){//return data pointer
			return data;
		}
		
		unsigned int size(){//return size
			return N;
		}
		
		void print_all(){
			for(int i=0; i<N-1; i++)
				std::cout<<data[i]<<", ";
			std::cout<<data[N-1]<<std::endl;
		}
};

int main(){
	int arr[3]={1,2,3};
	
	Array<int, 3> arr_w(arr);
	arr_w.print_all();
	
	//is Array<int, 5> is same class? of coursely, different because template instansiate by different template argument. we can check it by #include <typeinfo>
	std::cout<<(typeid(Array<int, 3>)==typeid(Array<int, 5>))<<std::endl; 
}*/

/*0
template <int N>
struct Int{
	static const int num=N;
};

template <typename T, typename U>
struct add{//add part
	typedef Int<T::num+U::num> result;//two type's argument's num + and make new Int object that has typename result.
};

int main(){
	typedef Int<1> one;
	typedef Int<2> two;
	
	typedef add<one, two>::result three;
	
	std::cout<<"Addition result : "<<three::num<<std::endl;//* add work is in compile time. In runtime, just show that result.
}*/

/*1
//factorial calculation in compile time
template <int N>
struct Factorial{
	static const int result=N*Factorial<N-1>::result;//not finish define 'static const int result'! it's stil defining in compile time.
}; 

template<>//like n==1 exception of recursive function
struct Factorial<1>{//n=1 in template. template specialization.
	static const int result=1;
};

int main(){
	std::cout<<"6! = 1*2*3*4*5*5 = "<<Factorial<6>::result<<std::endl;//there are no object that has value'720'! 720 value is just point type 'Factorial<6>'
}*/

int gcd(int a, int b){//normal way
	if(b==0)
		return a;
	return gcd(b, a%b);
} 

template <int X, int Y>//TMP way
struct GCD{
	static const int value=GCD<Y, X%Y>::value;
};
template <int X>
struct GCD<X, 0>{
	static const int value=X;
};
/*previoud Ratio & add
template <int N, int D=1>
struct Ratio{//Ratio means rational number
	typedef Ratio<N, D> type;//point self (like 'this' keyword in class)
	static const int num=N;//numerator of fraction
	static const int den=D;//denominator of fraction
};

template <class R1, class R2>
struct _Ratio_add{//radio add part
	typedef Ratio<R1::num*R2::den + R2::num*R1::den, R1::den*R2::den> type;
};
template <class R1, class R2>
struct Ratio_add:_Ratio_add<R1, R2>::type {};//just make type that is already added. ???
*/
template <int N, int D=1>
struct Ratio{
	private:
		const static int _gcd=GCD<N, D>::value;
		
	public:
		typedef Ratio<N/_gcd, D/_gcd> type;
		static const int num=N/_gcd;
		static const int den=D/_gcd;
};
template <class R1, class R2>
struct _Ratio_add{
	using type=Ratio<R1::num*R2::den+R2::num*R1::den, R1::den*R2::den>;
};

template <class R1, class R2>
struct Ratio_add:_Ratio_add<R1, R2>::type {};//부터 


int main(){
	std::cout<<"gcd (36, 24) :: "<<GCD<26, 24>::value<<std::endl;
	
	using rat=Ratio<2, 3>;//typedef Ratio<2, 3> rat;
	using rat2=Ratio<3, 2>;//typedef Ratio<3, 2> rat2;
	using rat3=Ratio_add<rat, rat2>;//typedef Ratio_add<rat, rat2> rat3;
	std::cout<<rat3::num<<" / "<<rat3::den<<std::endl;//not making Ratio class's object! just compiler makes new types.
	
	return 0;
}


/*
[0.	들어가기에 앞서]
1.	이전 강의처럼 템플릿을 통하여 타입이 마치 인자 인것 처럼 사용하는 것을 일반화 프로그래밍(generic programming)혹은 그냥 제너릭 프로그래밍이라고 부른다.
2.	템플릿 인자로는 타입 뿐만 아니라 특정한 조건을 만족하는 값들도 올 수 있는데, 이전에 std::array가 어떻게 구현되었는지를 대충 만들어보자. 
3.	위 코드처럼 배열을 감싸는 wrapper 클래스를 만들어서 마치 배열처럼 사용한다면, 배열을 사용하며 발생하는 많은 문제들을 많이 해결할 수 있게 된다.
	예를들어, 일반 배열의 경우 배열 범위가 넘어가도 알 수 없지만, 위 Array클래스는 index 범위가 넘어갈때를 따로 알려줄 수 있기 때문이다.
4.	다시말해, 덧셈이 수행되는 시기는 컴파일타임이고, 런타임 시에는 단순히 그 결과를 보여준다.

[1.	템플릿 메타 프로그래밍(Template Meta Programming-TMP)]
1.	템플릿 이전에, 기존에 알고있던 타입은 어떠한 값을 가지지 않았지만, 바로 위 예제들을 통해서 템플릿을 사용하여 타입에 어떠한 값을 부여하고, 그 값으로 연산을 할 수 있다는 것을 보았다.
	또한, 타입은 반드시 컴파일 타임에 확정되어야 하므로, 컴파일 타임에 모든 연산들이 끝나게 되는데 
	 이렇게 타입을 가지고 컴파일 타임에 생성되는 코드로 프로그래밍을 하는 것을 메타 프로그래밍(meta programming)이라고 하고, 
	C++의 경우 템플릿을 가지고 이러한 작업을 하기 때문에 템플릿 메타 프로그래밍, 줄여서 TMP라고 부른다.
2.	템플릿으로는 for문을 쓸 수 없기에 재귀적 구조를 사용한다. 하지만 반대로, for문으로 구현할 수 있는 모든 코드는 똑같이 템플릿 메타 프로그래밍을 이용하여 구현할 수 있고, 
	if문 역시 위의 템플릿 특수화를 통해 TMP로 구현할 수 있다. 
	
[2. TMP를 왜 쓰는가?]
1.	사실 모든 C++코드는 템플릿 메타 프로그래밍 코드로 변환할 수 있다. 이는 컴파일 타임에 모든 연산이 끝나기 때문에 컴파일 시간은 엄청 늘어나겠지만, 프로그램 실행 속도를 향상 시킬 수 있다는 장점이 있다.
	 단, 템플릿 메타 프로그래밍은 매우 복잡하기에 프로그램 전체를 구현하는 일은 없다. 또한, 컴파일 타임에 연산하는 것이기에 디버깅이 불가능하고, C++컴파일러 특성 상 템플릿 오류 시에 엄청난 길이의 오류를 내뿜기에 TMP로 작성된 코드의 버그를 찾는 것이 매우 힘들다.
2.	그렇기에 TMP를 이용하는 경우는 꽤나 제한적이지만, Boost 라이브러리를 포함한 많은 C++라이브러리 들이 TMP를 이용하여 구현되었고, 이를 통하여 컴파일 타임에 여러 오류들을 잡아낼 수도 있고(단위나 콩화 일치 여부 등등),  
	속도가 매우 중요한 프로그램의 경우 TMP를 통하여 런타임 속도도 향상시킬 수 있다. 
3.	C++11부터 typedef 대신에 using이라는 키워드를 사용할 수 있다.
	typedef Ratio_add<rat, rat2> rat3; == using rat2=Ratio_add<rat, rat2>;
4.	특히 함수 포인터의 경우 typedef void (*func)(int, int);처럼 사용해야 했지만, using으로는 using func=void (*)(int int);처럼 직관적으로 나타낼 수 있다. 
*/
