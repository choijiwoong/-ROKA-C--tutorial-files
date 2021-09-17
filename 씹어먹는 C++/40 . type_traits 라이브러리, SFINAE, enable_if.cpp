#include <iostream>

//enable_if 는 SFINAE 를 통해서 조건에 맞지 않는 함수들을 오버로딩 후보군에서 쉽게 뺄 수 있게 도와주는 간단한 템플릿 메타 함수 입니다. enable_if 는 다음과 같이 정의되어 있습니다.

/*1 In libc++, basic_ostream's operator<<
template <class _CharT, class _Traits, class _yp, class _dp>
typename enable_if<is_same<void, typename __void_t<decltype((declval<basic_ostream<_CharT, _Traits>&>()<<declval<typename unique_ptr<_Yp, _Dp>::pointer>()))>::type>::value, basic_ostream<_CharT, _Traits>&>::type operator<<(basic_ostream<_CharT, _Traits>& __os, unique_ptr<_Yp, _Dp> const& __p){ 
	return __os<<__p.get();
}*/

#include <type_traits>
/*2 std::is_void in type_traits
template <typename T>//template meta function
void tell_type(){
	if(std::is_void<T>::value)
		std::cout<<"T is void!\n";
	else
		std::cout<<"T isn't void. \n";
}
int main(){
	tell_type<int>();//not void
	tell_type<void>();//void
}*/

/*2 is_void template meta function structure like std::is_void
template <typename T>
struct is_void{
	static constexpr bool value=false;
};
template <>//template specialization like if
struct is_void<void>{
	static constexpr bool value=true;
};
template <typename T>//template meta function
void tell_type(){
	if(is_void<T>::value)
		std::cout<<"T is void!\n";
	else
		std::cout<<"T isn't void.\n";
}
int main(){
	tell_type<int>();//not void
	tell_type<void>();//void
}*/

/*2 is_integral in type_traits
class A{};

template <typename T>
void only_integer(const T& t){
	static_assert(std::is_integral<T>::value);//It's keyword that makes compile error if expression int argument is false and ignores that expression if it's true
	std::cout<<"T is an integer\n";
}
int main(){
	//we have to force integeral by using static_assert and std::is_integral
	//static_assert check that's value in compile time
	int n=3;
	only_integer(n);
	
	A a;
	only_integer(a);//error occur! static assertion failed!
	//so if static_assert's value is false by std::is_integral, compiler makes compile error because of static_assert
	//we can make function that gets epecial type only easily by using meta functino of type_traits and static_assert
}*/

/*3 The way of judging class of is_class
namespace detail{
	template <class T>
	char test(int T::*);//it means pointer that points T class's member that's type is int. it's work only in class.
	
	struct two{
		char c[2];
	};
	template <class T>
	two test(...);
}

template <class T>
struct is_class : std::integral_constant<bool, sizeof(detail::test<T>(0))==1 && !std::is_union<T>::value> {};
//1. In detail::test<T>(0), compiler must decide which function will be overloaded.
//if it's class, first is more concrete so compiler choose it.
//if it isn't class, first's (int T::*) grammer is impossible, so second will be overloaded.(but not occur compile error. just except order of overloading)
//then, second's return type is two(struct) so result of sizeof is 2.
//finally, is_class's value set false.
//2. std::is_union<T>::value
//In C++, int T::* can be used only in class & union. so detail::test<T>(0)==1 is true in union, we can check is it union by is_union in  additionally.
//In C++, we can't distinguish class and union. so is_union is made depending on compiler directly.
//Anyway, it's true if T is class.
*/


/*3 int T::* ; it's pointer that points T's int member. 
class A{
	public:
		int n;
		A(int n):n(n){}
};
int main(){
	int A::*p_n=&A::n;//p_n means pointer that can point A's int member. it doesn't point real object's int member.
	
	A a(3);
	std::cout<<"a.n : "<<a.n<<std::endl;
	std::cout<<"a.*p_n : "<<a.*p_n<<std::endl;//if we do backreference, we can use it like referencing A's n like this.
	//but this grammer can be used only to class.
}*/


/*4 wrong grammger is used when we use template
template <typename T>
void test(typename T::x a){//B::x a? gramatically right?(B doesn't have any type 'y') just remove in overloading candidate
	std::cout<<"T::x \n";
}
template <typename T>
void test(typename T::y b){//A::y? but compiler doesn't occur compile error.
	std::cout<<"T::y \n";
}

struct A{
	using x=int;
};
struct B{
	using y=int;
};

int main(){
	test<A>(33);//T::x
	test<B>(22);//T::y
}*/

/*4 Uncorrect grammar can stay in body of function, because SPINAE in template checks only argument & return type, so 
template <typename T>
void test(typename T::x a){//T has x
	typename T::y b;//T doesn't have y
}
template <typename T>
void test(typename T::y b){
	std::cout<<"T::y \n";
}

struct A{
	using x=int;
};

int main(){ test<A>(11); }
*/

/*5 enable_if
template <bool B, class T=void>//pass condition to B. if B is calculated to true, enable_if::value's type becomes T, else if B is false, enable_if doesn't have value.
struct enable_if;
//we can use enable_if like it
std::enable_if<std::is_integral<T>::value>::type;//we pass std::integral<T>::value to B.
*/

/*5 we can use enable_if like this
template <typename T, typename=typename std::enable_if<std::is_integral<T>::value>::type>//typename= part is passing default argument to template. we dont need to write like typename U= ,because we need only that expression.
void test(const T& t){//additional typename of std::enable_if is needed because std::enable_if<>::type is depending type.
	std::cout<<"t : "<<t<<std::endl;
}
//it's same function more simple
template <typename T, typename=std::enable_if_t<std::is_integral_v<T>>>
void test2(const T& t){
	std::cout<<"t : "<<t<<std::endl;
}

struct A{};

int main(){
	test(1);//int
	test(false);//bool
	test('c');//char
	
	test(A{});//compile error 'no type named 'type'
}
//it's defined like it
template <bool B, class T=void>
using enable_if_t=typename enable_if<B, T>::type;//C++14

template <class T>
inline constexpr bool is_integral_v=is_integral<T>::value;//C++17
*/

/*5 structure of enable_if
template <bool B, class T=void>//if B is false, ignore order of overloading because std::enable_if<B>::value is not correct grammer.
struct enable_if{};

template <class T>
struct enable_if<true, T>{//templae specialization to true
	typedef T type;//if B is true, define type. so only std::enable_if<B>::value stay to order of overloading
};*/

/*5. another example of enable_if
template <typename T>
class vector{
	public:
		vector(size_t num, const T& element){
			std::cout<<"make"<<element<<"amount of "<<num<<std::endl;
		}
		
		template <typename Iterator>
		vector(Iterator start, Iterator end){
			std::cout<<"Call constructor by iterator"<<std::endl;
		}
};

int main(){
	vector<int> v(10, 3);//we want to make 10 vector has 3, but iterator constructor is called. because num's type is size_t.
	//size_t means signed int and v's 10 is unsigned int. compiler can cast it to signed int if more good function to overloading is not existed.
	//but Iterator's constructor is perfectly matched. so mismatch is occured.
}

//So we have to force Iterator is real Iterator not only name.
//If is_iterator(meta function) exist, we can write like this
template <typename Iterator, typename=std::enable_if_T<is_iterator<Iterator>::value>>
vector(Iterator start, Iterator end){
	std::cout<<"Call constructor by using Iterator"<<std::endl;
}
//if we use std::enable_if_t like it, problem can be solved.
*/

//6
template <typename T, typename=decltype(std::declval<T>().func())>
void test(const T& t){
	std::cout<<"t.func() : "<<t.func()<<std::endl;
}

struct A{
	int func() const { return 1;}
};

int main(){ test(A{}); }



/*
[0.	들어가기에 앞서]
1.	C++에서 타입 관련 연산을 취한 템플릿 메타 함수들을 제공해주는 type_traits라이브러리가 있다.

[1.	공포의 템플릿]
1.	위와 같은 혐오스러운 템플릿 코드를 봐보자. 
	위 코드는 lib++ 라이브러리에서 가져온 코드로, unique_ptr의 주소값을 출력해주는 basic_ostream의 operator<<연산자의 구현부분이다.
2.	위와 같은 코드를 우리가 type_traits라이브러리들의 템플릿 메타 함수(template meta function)들을 잘 이해만 한다면 무리없이 해석할 수 있다.

[2.	템플릿 메타 함수]
1.	함수는 아니지만 함수처럼 동작하는 템플릿 클래스들을 의미한다. 이들이 메타 함수인 이유는 보통의 함수들은 값에대한 연산을 하는 반면,
	메타함수는 타입에 대해 연산을 수행한다는 점이 다르다
2.	어떤 수가 음수인지 아닌지를 판별하는 함수 is_negative는 아래와 같다
	if(is_negative(x)){
		//Do something...
	}
	템플릿 메타 함수의 경우 비슷하게, 어떤 타입이 void인지 아닌지를 판단하는 함수 is_void는 아래와 같다
	if(is_void<T>::value){
		//Do something
	}
3.	실제 코드로 옮겨보자.
	중요한 것은 템플릿 메타 함수들은 실제론 함수가 아니라는 점이다. 함수라면 ()을 통하여 호출을 했겠지만, is_void는 ()대신에 <>를 통해
	함수 인자가 아닌 템플릿 인자를 전달하고 있다. 실제로도 is_void는 함수가 아닌 클래스로 구현되어 있다. 
4.	is_void
	템플릿 메타프로그래밍에서 if문은 템플릿 특수화를 통해서 구현된다 하였다. if_void문을 살펴보자. 
5.	C++표준 라이브러리 중 하나인 type_traits에서는 is_void처럼 타입들에 대해 여러가지 연산을 수행할 수 있는 메타 함수들을 제공하고 있다.
	예를 하나 더 들어 is_integral함수를 추가로 보자. 
6.	is_integral
	static_assert는 C++11에 추가된 키워드로(함수가 아님) 인자로 전달된 식이 참인지 아닌지를 컴파일타임에 확인한다. 즉, bool타입의 constexpr만 static_assert로 확인할 수 있고 그 외에 컴파일 오류가 발생한다.
	만약 전잘딘 식이 참이면, 해당 식은 컴파일러에 의해 무시되고, 거짓이라면 컴파일 오류를 발생시키게 된다.
	 static_assert와 std::is_integral을 조합하여 T가 반드시 정수 타입임을 강제 할 수 있다. 

[3.	is_class]
1.	type_traits에 정의되어 있는 메타 함수들 중에서 흥미로운 함수로 is_class가 있는데 이는 인자로 전달된 타입이 클래스인지 아닌지를 확인하는 메타함수이다.
2.	std::integral_constant는 std::integral_constant<T, T v>로 정의되어 있는데, 그냥 v를 static인자로 가지는 클래스이다. 즉, 어떠한 값을 static객체로 가지고 있는 클래스를 만들어주는 템플릿이다.
	예로 std::integral_constant<bool, false>는 integral_constant<bool, false>::value가 false인 클래스이다. 
3.	데이터 멤버를 가리키는 포인터(Pointer to Data member)
	int T::*는 T의 int멤버를 가리키는 포인터라는 의미이다. 
4.	test오버로딩 시에 T가 클래스가 아니라면 int T::*는 불가능한 문법이지만, 컴파일 오류가 아닌 단순히 오버로딩 후보군에서 제외도니다.
5.	C++에서 데이터 멤버를 가리키는 포인터가 허용되는 것은 클래스와 공용체(union)딱 두가지이다. 따라서 is_union을 추가적으로 사용하여 공용체가 아님을 확인해야하는데, C++에서는 클래스와 공용체를 구별할 수 있는 방법이 없는데, 

[4.	치환 오류는 컴파일 오류가 아니다(Substitution failure is not an error-SFINAE)]
1.	아까 컴파일 오류 시에 오버로딩 후보군에서 제외된다는 개념이 나왔었음. 
2.	템플릿 인자들을 유추한 타입으로 치환을 할 때, 문법적으로 말이 안되는 경우들이 존재하기 마련이다. 
	그럴 경우 스피내(SFINAE)법칙에 의거하여 컴파일 오류를 발생시키지 않고 오버로딩 후보군에서 제외한다.
	 다만 중요한 점은, 함수 내용 전체가 문법적으로 올바른지 확인하는 것이 아니라 단순히 함수의 인자들과 리턴 타입만이 문법적으로 올바른지를 확인하기에 이 조건만 충족한다면, 
	마찬가지로 함수 내부에 문법적으로 올바르지 않은 내용이 있더라도 오버로딩 후보군에 남아있게 된다. 
3.	SFINAE를 활용하면 원하지 않는 타입들에 대하여 오버로딩 후보군에서 제외할 수 있다. 
	type_traits에선 해당 작업을 손쉽게 할 수 있는 메타 함수를 하나 제공하는데, enable_if이다.
	
[5.	enable_if]
1.	SFINAE를 통해서 조건에 맞지 않는 함수들을 오버로딩 후보군에서 쉽게 뺄 수 있게 도와주는 간단한 템플릿 메타 함수이다. 

[6.	특정 멤버 함수가 존재하는 타입 만을 받는 함수]
1.	enable_if를 비롯한 여러 메타 함수로 할 수 있었던 것은 이러이러한 조건을 만족하는 타입을 인자로 받는 함수를 만들고 싶다 였다.
	만약 이러이러한 멤버 함수가 있는 타입을 인자로 받는 함수를 만들고 싶다이면 어떻게 해야할까?
	 
	 
*/
