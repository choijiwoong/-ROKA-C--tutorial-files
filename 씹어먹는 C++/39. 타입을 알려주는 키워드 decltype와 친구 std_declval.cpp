#include <iostream> 

/*1 using of decltype
struct A{
	double d;
};

int main(){
	int a=3;
	decltype(a) b=2;//int
	
	int& r_a=a;
	decltype(r_a) r_b=b;//int&
	
	int&& x=3;
	decltype(x) y=2;//int&&
	
	A* aa;
	decltype(aa->d) dd=0.1;//double
}*/

/*2-2 lvalue
int i;
i;//i's address is real address value of i
int&& x=i;//impossible! not movable. cannot compile
//most objects have name are lvalue because it can get address of that object.

//2 lvalue exception of referencing member variable or function that is enum or not static.
class A{
	int f();//not static member function
	static int g();//static member function
}
	
A a;
a.f;//not lvalue. it's prvalue
a.g;//lvalue
	
//2 type category & value category
void f(int&& a){//a's type category is rvalue reference, but a's value category is lvalue because it has name.
	a;
}
f(3);


//2 it can compile too
void f(int&& a) { std::cout<<&a; }
int main() { f(3); } 
*/

/*2-3 prvalue
int f() {return 10; }
f();//we can't access it's address, but it can be put at rvalue reference. so it's prvalue

const int& r=42;
int&& rr=42;
int& rrr=2;//impossible! normal lvalue refercence
*/

/*2-4 xvalue
//definition of std::move()
template <class T>
constexpr typename std::remove_reference<T>::type&& move(T&& t) noexcept;
//move's return type is rvalue reference. so it(calls move) can use like lvalue, like prvalue

//then how about decltype?
int a, b;
decltype(a+b) c;//a+b is prvalue so it guess int. ==int c;

int a_;
decltype((a_)) b_;//(a_) can do &(a_) and not movable, so it's lvalue.
//so b's type is guessed to int& not int.???
*/


/*3 necessity of decltype
int i=4;
auto j=i;//int j=i;

int i=4;
decltype(i) j=i;//int j=1;
//it's same result but actually, auto doesn't express correct type.

//3 difference of auto & decltype_it preserve type perfectly 
const int i=4;
auto j=i;//int j=i;
decltype(i) k=i;//const int k=i;

int arr[10];
auto arr2=arr;//int* arr2=arr;
decltype(arr) arr3;//int arr3[10]; much correct!

template <typename T, typename U>
void add(T t, U u, ? result){//what type will be placed? what we have to do? 
	*result=t+u;
}
//we can use decltype like this
template <typename T, typename U>
void add(T t, U u, decltype(t+u)* result){//just use pointer. it's doesn't get any importance.
	*result=t*u;
}

//how about just make function that returns added value? more shortly like this
template <typename T, typename U>
decltype(t+u) add(T t, U u){//compile error! when compiler watch decltype(t+u), say "what's the funcking this?" because decltype(t+u) is front of definition t & u.
	return t+u;
}
//so we have to write return value of function behind of definition of arguments. like this

template <typename T, typename U>
auto add(T t, U u)->decltype(t+u){//just put auto on return value's place, and assign real return type behind of ->.
	return t+u;
}
//it's like grammer of lambda function
*/

/*4 introduce background before making std::declval
struct A{
	int f() { return 0; }
}; 
decltype(A().f()) ret_val;//int ret_val;
//expressiong in decltype() is not runnig in runtime, it just exist form as expression.
//so in upper code, object A is not created and not called function f actually. it's just expression.
//but also, it can catch wrong expression in decltype() like this

struct B{
	B(int x) {}
	int f() { return 0; }
};
int main(){
	decltype(B().f()) ret_val2;//Error! B() is wrong gramatically.
}
//so we have to code correct code that satisfys rule of B's constructor regardless of we don't make object B actually.


template <typename T>
decltype(T().f()) call_f_and_return(T& t){//call member function f by receiving object T (that is random type)
	return t.f();
}
//we can use it if we suppose every objects that will use this function defines member function f.
//but the problem is every type T cannot define default constructor T().

template <typename T>
decltype(T().f()) call_f_and_return(T& t){
	return t.f();
}
struct A{
	int f(){return 0;}
};
struct B{
	B(int x){}
	int f(){return 0;}
};
int main(){
	A a;
	B b(1);
	
	call_f_and_return(a);//Good. default constructor is called!
	call_f_and_return(b);//Bad. it doesn't have default constructor only have constructor with argument
}
//so making constructor directly can make problem when received type's constructor are not same form.
//This problem can be solved by std::declval.
*/

//4 std::declval version of upper code.
#include <utility>
template <typename T>
decltype(std::declval<T>().f()) call_f_and_return(T& t){//std::declval<T> can make effect like T() even if T's constructor is not defined.
	return t.f();
}
struct A{
	int f() {return 0;}
};
struct B{
	B(int x){}
	int f() {return 0;}
};
int main(){
	A a;
	B b(1);
	
	call_f_and_return(a);//Good
	call_f_and_return(b);//Good
}
//so it can prevent error because of differency of constructors of template argument T.

//but declval must be used in type operation, if we use it runtime, error occur.
struct B{
	B(int x){}
	int f() {return 0;}
};
int main(){B b =std::declval<B>();}//error occur. object saving by std::declval.

//compiler can guess return type of funtion at C++14
template <typename T>
auto call_f_and_return(T& t){
	return t.f();
}

/*
[0.	들어가기에 앞서 배경지식]
1.	C++에서는 값 카테고리를 따질 때 크게 두가지 질문을 한다.
	-정체를 알 수 있는가?_다른 식과 같은 것인지 구분이 가능한가?
	-이동시킬 수 있는가?_이동생성자, 이동대입생성자 사용이 가능한가? 

[1.	decltype]
1.	C++11에 추가된 키워드로, decltype라는 이름의 함수처럼 사용된다. like decltype(타입을 알고자 하는 식)
2.	decltype는 함수와는 달리, 타입을 알고자 하는 식의 타입으로 치환되어 컴파일된다.
	위의 코드와 같이 decltype에 전달된 식이 괋로 둘러쌓이지 않은 식별자 표현식(id-expression)이라면 해당 식의 타입을 얻을 수 있다.
3.	식별자 표현식이란, 변수의 이름, 함수의 이름, enum 이름, 클래스 멤버 변수 등 어떠한 연산을 하지 않고 단순히 객체 하나만을 가리키는 식이다. 
4.	만약 decltype에 식별자 표현식이 아닌 식이 전달된다면, 해당 식의 값의 종류(value category)에 따라 달라진다.
	-xvalue라면 decltype는 T&&
	-lvalue라면 decltype는 T&
	-prvalue라면 decltype는 T

[2.	Value Category]
1.	C++에서는 5가지의 값 카테고리가 존재하는데, lvalue(좌측값), rvalue(우측값), prvalue(순수 우측값), xvalue(소멸하는 값), glvalue(일반화된 좌측값)이다.
	xvalue는 glvalue와 value의 교집합이고, glvalue-rvalue가 lvalue, rvalue-glvalue가 prvalue이다.
2.	lvalue
	-변수, 함수의 이름, 어떤 타입의 데이터 멤버(std::endl, std::cin)등등
	-좌측값 레퍼런스를 리턴하는 함수의 호출식(std::cout<<1, ++it)등등
	-a=b, a+=b, a*=b같은 복합 대입 연산자 식들
	-++a, --a같은 전위 증감 연산자 식들
	-a.m, p->m과 같이 멤버를 참조할 때(m이 enum이거나 static이 아닌 멤버 함수의 경우 제외)
	-a[n]과 같은 배열 참조 식들
	-문자열 리터럴 "hi"
	이러한 lvalue들은 모두 lvalue들은 주소값 연산자(&)를 통해 해당 식의 주소값을 알아낼 수 있다.(&++i, &std::endl) 또한 lvalue들은 좌측값 레퍼런스를 초기화하는데에 사용할 수 있다.
3.	prvalue
	-문자열 리터럴을 제외한 모든 리터럴들(42, true, nullptr)등등
	-레퍼런스가 아닌 것을 리턴하는 함수의 호출식(str.substr(1, 2), str1+str2)등등
	-후위 증감 연산자 식(a++, a--)
	-(default not overloaded)산술 연산자, 논리 연산자 식들(a+b, a&&b, a<b)등등
	-주소값 연산자 식 &a
	-a.p, o->m과 같이 멤버를 참조할 때(m이 enum이거나 nonstatic일 경우만)
	-this
	-enum 값
	-람다식 [](){return 0;};등등 
	prvalue들을 정체를 알 수 없기에 주소값을 취할 수 없기에 &a++나 &42등은 오류이다. 또한 prvalue는 식의 좌측에 올 수 없다.
	대신 prvalue는 우측값 레퍼런스와 상수 좌측값 레퍼런스를 초기화하는데 사용할 수 있다. 
4.	xvalue
	만약 값 카테고리가 lvalue와 prvalue 두개로만 구분된다면, 좌측값으로 분류되는 식을 이동시킬 방법이 사라지는 문제가 발생한다.
	고로 우리는 좌측값 처럼 정체가 있지만 이동도 시킬 수 있는 것을 생각해야하는데 대표적으로 std::move(x)가 있다. 
	즉, move를 호출한 식은 lvalue처럼 좌측값 레퍼런스를 초기화하는데 사용할 수 있고, prvalue처럼 우츠값 레퍼런스에 붙이거나 이동 생성자에 전달하여 이동시킬 수 있는 모두 가능한 만능인 것이다.
	 허나, 우린 decltype에 대해 알고있다. 값 카테고리를 고려해서 생각해보면, 괄호의 유무로 추론 타입이 바뀔 수 있다.
	근데 잘 모르겠음 핳
	 
[3.	decltype의 쓰임새]
1.	auto키워드는 엄밀히 말하면 정확한 타입을 표현하지않기에 타입을 그대로 보존하는 decltype을 사용한다.
2.	템플릿 함수에서 어떤 객체의 타입이 템플릿 인자들에 의해 결정되는 경우가 있더. 
3.	auto add(T t, U u)->decltype(t+u){처럼 리턴값자리에 auto로 쓰고 ->뒤에 실제 함수의 리턴 타입을 지정해주어도 된다.
	리턴타입이 템플릿 인자에 의해 결정될 경우에 이러한 방식으로 해결한다. 
	
[4.	std::declval]
1.	declval은 decltype과 달리 키워드가 아니라 <utilty>에 정의된 함수로 decltype과 같이 C++11에 추가된 std::declval함수이다.
2.	기존의 decltype의 괄호()안에 들어가는 것은 실제로 런타임에 실행되는 것이 아닌 단순한 식의 형태이지만, 우리는 생성자 규칙등을 만족시켜야 사용이 가능했다.
	고로 decltype()안에 생성자를 직접 호출해버리면, 규칙에 맞지않아(사용자 지정 constructor로 default constructor가 없다거나)로 오류가 발생할 수 있다.
3.	std::declval에 타입 T를 전달하면, T의 생성자를 직접 호출하지 않고도 T가 생성된 객체를 나타낼 수 있다. 즉, 생성자가 존재하지 않더라도 마치 T()와 같은 효과를 내어 생성자의 형태가 달라 발생하는 오류를 막을 수 있다. 
4.	C++14부터 알아서 컴파일러가 함수의 리턴타입을 유추해주는 기능이 추가되어 걍 auto로 사실 사용이 가능하지롱 쿠쿠루삥빵뽕
5.	declval의 필요성이 auto로 인해 없어지는듯하지만, 뒤에 type_traits라이브러리를 다루면 유용한 TMP기법들을 사용할 수 있다. 
*/
