#include <iostream>

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

/*6 problem occur that compiler can't handle conditionf class B doesn't have func() member function
template <typename T, typename=decltype(std::declval<T>().func())>//can't handle class doesn't have func(). compile error occur
void test(const T& t){
	std::cout<<"t.func() : "<<t.func()<<std::endl;
}

struct A{//have func()
	int func() const { return 1;}
};
struct B {};//doesn't have func()

int main(){ 
	test(A{}); 
	//test(B{});//error occur because B doesn't have func() as member function.
	//we can force return type of func() by using enable_if
	
	test1(A{});
	test1(B{});
}*/

/*6 enable_if can solve that problem
template <typename T, typename=std::enable_if_t<std::is_integral_v<decltype(std::declval<T>().fun())>>>//is_integral_v can use in C++17..
void test(const T& t){
	std::cout<<"t.func() : "<<t.func()<<std::endl;
}

struct A{ int func() const { return 1; }; };
struct B{ char func() const {return 'a'; };};//not int type. compile error occur because of std::is_integral_v with enable_if_t

int main(){
	test(A{});
	test(B{});
}*/


#include <set>
#include <vector>
/*6 how about check many fuction not only func? Let's suppose print function that prints all elements of container. we have to check definition of begin & end.
template <typename Cont, typename=decltype(std::declval<Cont>().begin()), typename=decltype(std::declval<Cont>().end())>//std::ceclval can check object without calling constructor. decltype is keyword that return real type of argument. if Cont's begin is not exist, then decltype call error, then typename=part's occur error too. it's compile error.
void print(const Cont& container){
	std::cout<<"[";
	for (auto it=container.begin(); it!=container.end(); ++it)
		std::cout<<*it<<" ";
	std::cout<<"]\n";
}

int main(){
	std::vector<int> v={1,2,3,4,5};
	print(v);
	
	std::set<char> s={'a','b','c','u'};
	print(s);
	//well work!
}*/

/*6 Let's see what's happening if begin & end is not defined in class.
template <typename Const, typename=decltype(std::declval<Cont>().begin()), typename=secltype(std::declval<Cont>().end())>
void print(const Cont& container){
	std::cout<<"[ ";
	for (auto it=container.begin(); it!=container.end(); ++it)
		std::cout<<*it<<" ";
	std::cout<<"]\n";
}

struct Bad{
	void begin();
};
//it's really good choice that i choose computer engineering...it's feeled little hard, but it's so interesting and fun soon to me:) such like intelligentic satisfying
//When i feel some confusing, i feel happy everythings of me not only recovering.
int main(){ print(Bad{}); }//error occur! because Bad doesn't have end() so Bad{} cannot be overloaded.
//it's seem like good to us, but one problem is staying. that's too many template argument 'typename='
//In aspect of other people, he can't find easily how many template argument in Print function. correctly, which argument are gotten?
//So for solving this readability problem, meta function that is 'void_t' is added int C++17
*/

/*7 user pass one more argument to template argument by mistake in code that is used void_t
template <typename Cont,
		  typename = std::void_t<decltype(std::declval<Cont>().begin()),//std::void_t is in C++17!
		  						 decltype(std::declval<Cont>().end())>>
void print(const Cont& container){
	std::cout<<"[ ";
	for (auto it=container.begin(); it!=container.end(); ++it)
		std::cout<<*it<<" ";
	std::cout<<"]\n";
}

struct Bad {};

int main(){
	print<Bad, void>(Bad{});//one more template argument not only container. compile error occur! because print is not removed in order of overloading.
	//user pass void 
}*/

//8. review fucking template
template <class _CharT, class _Traits, class _Yp, class _Dp>
typename enable_if<
	is_same<void, typename __void_t<decltype(declval<basic_ostream<_CharT, _Traits>()<<declval<
		typename unique_ptr<_Yp, _Dp>::pointer>()))>::type>::value, 
			basic_ostream<_CharT, _Traits>&>::type operator<<(basic_ostream<_CharT, _Traits>& __os, 
				unique_ptr<_Yp, _Dp> const& __P){
	return __os<<__p.get();
}
//this function is in stdard library of C++ so it muse be made safely
//so it checks type by return type of function not by default argument of template
//Let's see it partly.

__void_t<decltype((declval<basic_ostream<_CharT, _Traits>&>()<<declval<typename unique_ptr<_Yp, _Dp>::pointer>()))::type//__void_t is same to std::void_t
//it's checking this expression is correct gramatically.
declval<basic_ostream<_CharT, _Traits>&>()<<declval<typename unique_ptr<_Yp, _Dp>::pointer>()
//Can besic_ostream's operator<< print pointer type object of unique_ptr? 
//if it's possible, __void_t will be calculated to void, else if it's impossible, this operator<< will be removed in order of overloading.

//then, return part of this function 
typename enable_if<
	is_same<void, typename __void_t<decltype((declval<basic_ostream<_CharT, _Traits>&>()<<declval<
		typename unique_ptr<_Yp, _Dp>::pointer>()))::type>::value, 
			basic_ostream<_CharT, _Traits>&>::type
//will be instantiated like that.
typename enable_if<is_same<void, void>::value, basic_ostream<_CharT, _Traits>&>::type
//is_same is meta function that is defined in type_traits. if two arguments in is_same is true, value set true, else value set false.
//now, argument's type is same, so it's value set true.

//then, this expression
typename enable_if<true, basic_ostream<_CharT, _Traits>&>::type operator<<(
	basic_ostream<_CharT, _Traits>& __os, unique_ptr<_Yp, _Dp> const& __p){
		return __os<<__p.get();
}
//is changed by enable_if like that
basic_ostream<_CharT, _Traits>& operator<<(basic_ostream<_CharT, _Traits>& __os, unique_ptr<_Yp, _Dp> const& __p){
	return __os<<__p.get();
}

//this code is long, but it's same to examples we learned.
//example's return type is coid, operator<<'s return type is basic_ostream<_CharT, _Traits>&. it's just.


/*
[0.	���⿡ �ռ�]
1.	C++���� Ÿ�� ���� ������ ���� ���ø� ��Ÿ �Լ����� �������ִ� type_traits���̺귯���� �ִ�.

[1.	������ ���ø�]
1.	���� ���� ���������� ���ø� �ڵ带 ������. 
	�� �ڵ�� lib++ ���̺귯������ ������ �ڵ��, unique_ptr�� �ּҰ��� ������ִ� basic_ostream�� operator<<�������� �����κ��̴�.
2.	���� ���� �ڵ带 �츮�� type_traits���̺귯������ ���ø� ��Ÿ �Լ�(template meta function)���� �� ���ظ� �Ѵٸ� �������� �ؼ��� �� �ִ�.

[2.	���ø� ��Ÿ �Լ�]
1.	�Լ��� �ƴ����� �Լ�ó�� �����ϴ� ���ø� Ŭ�������� �ǹ��Ѵ�. �̵��� ��Ÿ �Լ��� ������ ������ �Լ����� �������� ������ �ϴ� �ݸ�,
	��Ÿ�Լ��� Ÿ�Կ� ���� ������ �����Ѵٴ� ���� �ٸ���
2.	� ���� �������� �ƴ����� �Ǻ��ϴ� �Լ� is_negative�� �Ʒ��� ����
	if(is_negative(x)){
		//Do something...
	}
	���ø� ��Ÿ �Լ��� ��� ����ϰ�, � Ÿ���� void���� �ƴ����� �Ǵ��ϴ� �Լ� is_void�� �Ʒ��� ����
	if(is_void<T>::value){
		//Do something
	}
3.	���� �ڵ�� �Űܺ���.
	�߿��� ���� ���ø� ��Ÿ �Լ����� ������ �Լ��� �ƴ϶�� ���̴�. �Լ���� ()�� ���Ͽ� ȣ���� �߰�����, is_void�� ()��ſ� <>�� ����
	�Լ� ���ڰ� �ƴ� ���ø� ���ڸ� �����ϰ� �ִ�. �����ε� is_void�� �Լ��� �ƴ� Ŭ������ �����Ǿ� �ִ�. 
4.	is_void
	���ø� ��Ÿ���α׷��ֿ��� if���� ���ø� Ư��ȭ�� ���ؼ� �����ȴ� �Ͽ���. if_void���� ���캸��. 
5.	C++ǥ�� ���̺귯�� �� �ϳ��� type_traits������ is_voidó�� Ÿ�Ե鿡 ���� �������� ������ ������ �� �ִ� ��Ÿ �Լ����� �����ϰ� �ִ�.
	���� �ϳ� �� ��� is_integral�Լ��� �߰��� ����. 
6.	is_integral
	static_assert�� C++11�� �߰��� Ű�����(�Լ��� �ƴ�) ���ڷ� ���޵� ���� ������ �ƴ����� ������Ÿ�ӿ� Ȯ���Ѵ�. ��, boolŸ���� constexpr�� static_assert�� Ȯ���� �� �ְ� �� �ܿ� ������ ������ �߻��Ѵ�.
	���� ���ߵ� ���� ���̸�, �ش� ���� �����Ϸ��� ���� ���õǰ�, �����̶�� ������ ������ �߻���Ű�� �ȴ�.
	 static_assert�� std::is_integral�� �����Ͽ� T�� �ݵ�� ���� Ÿ������ ���� �� �� �ִ�. 

[3.	is_class]
1.	type_traits�� ���ǵǾ� �ִ� ��Ÿ �Լ��� �߿��� ��̷ο� �Լ��� is_class�� �ִµ� �̴� ���ڷ� ���޵� Ÿ���� Ŭ�������� �ƴ����� Ȯ���ϴ� ��Ÿ�Լ��̴�.
2.	std::integral_constant�� std::integral_constant<T, T v>�� ���ǵǾ� �ִµ�, �׳� v�� static���ڷ� ������ Ŭ�����̴�. ��, ��� ���� static��ü�� ������ �ִ� Ŭ������ ������ִ� ���ø��̴�.
	���� std::integral_constant<bool, false>�� integral_constant<bool, false>::value�� false�� Ŭ�����̴�. 
3.	������ ����� ����Ű�� ������(Pointer to Data member)
	int T::*�� T�� int����� ����Ű�� �����Ͷ�� �ǹ��̴�. 
4.	test�����ε� �ÿ� T�� Ŭ������ �ƴ϶�� int T::*�� �Ұ����� ����������, ������ ������ �ƴ� �ܼ��� �����ε� �ĺ������� ���ܵ��ϴ�.
5.	C++���� ������ ����� ����Ű�� �����Ͱ� ���Ǵ� ���� Ŭ������ ����ü(union)�� �ΰ����̴�. ���� is_union�� �߰������� ����Ͽ� ����ü�� �ƴ��� Ȯ���ؾ��ϴµ�, C++������ Ŭ������ ����ü�� ������ �� �ִ� ����� ���µ�, 

[4.	ġȯ ������ ������ ������ �ƴϴ�(Substitution failure is not an error-SFINAE)]
1.	�Ʊ� ������ ���� �ÿ� �����ε� �ĺ������� ���ܵȴٴ� ������ ���Ծ���. 
2.	���ø� ���ڵ��� ������ Ÿ������ ġȯ�� �� ��, ���������� ���� �ȵǴ� ������ �����ϱ� �����̴�. 
	�׷� ��� ���ǳ�(SFINAE)��Ģ�� �ǰ��Ͽ� ������ ������ �߻���Ű�� �ʰ� �����ε� �ĺ������� �����Ѵ�.
	 �ٸ� �߿��� ����, �Լ� ���� ��ü�� ���������� �ùٸ��� Ȯ���ϴ� ���� �ƴ϶� �ܼ��� �Լ��� ���ڵ�� ���� Ÿ�Ը��� ���������� �ùٸ����� Ȯ���ϱ⿡ �� ���Ǹ� �����Ѵٸ�, 
	���������� �Լ� ���ο� ���������� �ùٸ��� ���� ������ �ִ��� �����ε� �ĺ����� �����ְ� �ȴ�. 
3.	SFINAE�� Ȱ���ϸ� ������ �ʴ� Ÿ�Ե鿡 ���Ͽ� �����ε� �ĺ������� ������ �� �ִ�. 
	type_traits���� �ش� �۾��� �ս��� �� �� �ִ� ��Ÿ �Լ��� �ϳ� �����ϴµ�, enable_if�̴�.
	
[5.	enable_if]
1.	SFINAE�� ���ؼ� ���ǿ� ���� �ʴ� �Լ����� �����ε� �ĺ������� ���� �� �� �ְ� �����ִ� ������ ���ø� ��Ÿ �Լ��̴�. 

[6.	Ư�� ��� �Լ��� �����ϴ� Ÿ�� ���� �޴� �Լ�]
1.	enable_if�� ����� ���� ��Ÿ �Լ��� �� �� �־��� ���� �̷��̷��� ������ �����ϴ� Ÿ���� ���ڷ� �޴� �Լ��� ����� �ʹ� ����.
	���� �̷��̷��� ��� �Լ��� �ִ� Ÿ���� ���ڷ� �޴� �Լ��� ����� �ʹ��̸� ��� �ؾ��ұ�?

[7.	void_t]
1.	definition of void_t is very simple like that

	template <class...>
	using void_t=void;
	
	By using variadic template, we can pass random types to void_t as template argument, anyway void_t is same to void.
	 So if one of void_t's arguments occur error, it will be removed in overloading order by SFINAE.
	so we can develop readability of upper function by using void_t like that.
	
	template <typename Cont, 
			  typename = std::void_t<decltype(std::declval<Cont>().begin()),
			  						 decltype(std::declval<Cont>().end())>>
			  						 
	but this code is not perfect if user pass one more argument to template argument by mistake
	So checking place of Cont's type are passed void. so compiler doesn't use default argument of template argument. so compiler skips type check.
	
	To solve this delema, we have to design well worked-function even if user do mistake.
	So we will seperate type checking part to another place like that.
	
	template <typename Cont>
	std::void_t<decltype(std::declval<Cont>().begin()), decltype(std::declval<Cont>().end())> print(const Cont& container){
		//Do something...
	}
	
	type checking part is moved to return type. return type is also applied SFINAE, so it can make same effect with safety of user's mistake.
	
[8.	������ ���ø� �ٽ� ���캸��]
1.	����� ������ ��������, ���� ��� �������� ������ �������̶��� operator<<�� ����Ÿ���� basic_ostream<_CharT, _Traits>&��� �� ���̴�.

[9.	�������ϸ�]
1.	type_traits�� ���ǵǾ� �ִ� ��Ÿ �Լ����� ������ �ִ���
2.	C++���� ���ø� ���� ġȯ �� ���������� �ùٸ��� ���� �ڵ尡 ������ ���, ������ ������ �߻���Ű�� ���� �ƴ϶� �����ε� �ĺ������� �����Ѵ�.
	�̶�, �����Ϸ��� ��� �ڵ带 ġȯ�ϴ� ���� �ƴ϶� �Լ��� Ÿ��, ���� ���� �κи� Ȯ���ϴµ�, �̷��� ��Ģ�� SFINAE��� �Ѵ�.
3.	enable_if�� ���Ͽ� ���ϴ� Ÿ�Ը� �޴� �Լ��� �ۼ��� �� �ִ�.
4.	void_t�� ���Ͽ� ���ϴ� Ÿ�Ը� �޴� �Լ��� �������ְ� �ۼ��� �� �ִ�. 
	
*/
