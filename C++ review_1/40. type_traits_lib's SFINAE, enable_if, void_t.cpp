#include <iostream>
#include <type_traits>

/*make only_integer that force special type(int) by static_assert keyword
class A{};

template <typename T>
void only_integer(const T& t){
	static_assert(std::is_integral<T>::value);
	std::cout<<"T is an integer \n";
}

int main(){
	int n=3;
	only_integer(n);
	
	A a;
	only_integer(a);
}*/

/*is_class 
namespace detail{
	template <class T>
	char test(int T::*);//check Pointer to Data member regardless of int member is exist(if not exit, it doesn't point anythinig) 
	
	struct two{
		char c[2];
	};
	template <class T>
	two test(...);//return type is two that has char[2]. so it's not 1. finally false.
}
template <class T>
struct is_class: std::integral_constant<bool, sizeof(detail::test<T>(0))==1 && !std::is_union<T>::value> {};
//if sizeof~ is true, it's class. this struct just make class with static value.
*/

/*enable_if pop element to overloading occured by SFINAE
template <typename T, typename U=typename std::enable_if<std::is_integral<T>::value>::type>
void test(const T& t){
	std::cout<<"t : "<<t<<std::endl;
}

int main(){
	test(1);
	test(false);
	test('c');//well compile!
	
	struct A{};
	test(A{});//error! not int type
}*/

/*function that has func() as member function and func() must return int type value; by using enable_if
template <typename T, typename=std::enable_if_t<std::is_integral_v<decltype(std::declval<T>().func())>>>
void test(const T& t){
	std::cout<<"t.func(): "<<t.func()<<std::endl;
}

struct A{
	int func1() const { return 1; }
};
struct B{
	char func() const { return "as"; }
};

int main(){
	test(A{});//error! because of argument type (not return type)
	test(B{});//error! because of return type (not argument type)
}*/

//example code
template <class _CharT, class _Traits, class _Yp, class _Dp>
typename enable_if<//check type by return type
	is_same<void, typename __void_t<decltype(
					(declval<basic_ostream<_CharT, _Traits>&>()<<
					 declval<typename unique_ptr<_Yp, _Dp>::pointer>()))::type>::value
					 , basic_ostream<_CharT, _Traits>&>::type
		operator<<(basic_ostream<_CharT, _Traits>* __os, unique_ptr<_Yp, _Dp> const & __P){//it's just operator overloading function!
	return __os<<__p.get();		
}

//result of upper code if it's all passed
basic_ostream<_CharT, _Traits>& operator<<(basic_ostream<_CharT, _Traits>* __os, unique_ptr<_Yp, _Dp> const& __p){
	return __os<<__p.get();
}

/*
1.	type_traits���� ���� ���ø� ��Ÿ(Ÿ�Կ� ���� ����) �Լ����� �ִ�.(ex. is_void, is_integral) 
2.	static_assert�� C++11 Ű����� ���ڷ� ���޵� ���� ������ �ƴ����� ������Ÿ�ӿ� Ȯ���ϴµ�, �� bool Ÿ���� constexpr�� Ȯ���� �� �ְ� �� �ܿ��� ������ ������ �߻��Ѵ�.
	���ڰ� ���̸� �ش� ���� ���õǰ�, �����̸� ������ ������ �߻���Ų��. �̸� �̿��Ͽ� Ư�� Ÿ�Ը� �޴� �Լ��� �����ϰ� ���� �� �ִ�.
3.	std::integral_constant<T, T v>�� � ���� static ��ü�� ������ �ִ� Ŭ������ ������ִ� ���ø��̴�. 
	������ ����� ����Ű�� ������(Pointer to Data member)������ Ŭ�������� ����� �� �ִ�. 
	 �츮�� detail::test<T>(0)�� ������ ù�� ° �켱������ ������ �� ���Ŀ� ������ ����� �� ���̴�.
	�ٸ� ù��° ���Ŀ� �����ʾ� �����ε� ���������� �з�(not error by SFINAE) �ι�°�� ���� �ȴٸ�, 
	����Ÿ���� two�� �Ǿ� sizeof�� 1�� �Ǿ� false������ �ȴ�. (p.s ����ü�� ������ ����� C++�� ���� �����Ϸ��� ������ ������� is_union�� ����� �ذ��Ѵ�.)
4.	SFINAE(Substitution Failure Is Not An Error)��Ģ�� ���� ġȯ������ �����ε� ���������� �з����� �Ǵµ�, ������ �����Ϸ���
	������ �߻��ϴ� ��� ġȯ�������� �Ǵ��ϴ°� �ƴ� �Լ��� ���ڵ�� ����Ÿ�Ը��� Ȯ���Ͽ� �����ε� ���������� ���õǾ�����,
	���� �������ϴ� ������ �߻��ϴ� ������ �����Ѵ�.
5.	�̸� enable_if�� ����Ͽ� ���ǿ� �����ʴ� �Լ����� �����ε� ���������� ���ܽ�ų �� �ִ�.
	std::enable_if�� ������ ���϶��� type�� ���ǵǰ� �����̸� type ���ǰ� ���� �ʾ� �ִµ� type�� ȣ���� ���̴� ������ �߻���Ų��. 
	 typename�� enable_if�տ� �ٴ� ������ ����Ÿ���̱� �����ε� �����ϴ� �׳� enable_if�� typename�� ���� ����.
6.	enable_if�� ������ �����ϰ� ���ø� Ư��ȭ�� �ؼ� ������ true�� �������� type�� ���ǵǾ� �ְ�, �ƴϸ� �ƹ��͵� ���ǵǾ� ���� �ʴ�.
7.	���� �츮�� Ư���� ����Լ��� �ִ� Ÿ���� ���ڷ� �ް� �ʹٸ� typename=decltype(std::declval<T>().func())�� ���� enable_ifó�� ������ �߻���Ű�� ����� ó���� �� �ִ�.
	 �ٵ� �� ���ư� ���� �Ӹ��� �ƴ� ���ϵǴ� Ÿ�Ը����� Ȯ���ϰ� �ʹٸ� enable_if�� ����� �� �ִ�. 
8.	�츮�� Iterator�� �̿��ϴ� �Լ��� ����ٸ�, template argument�� decltype(std::declval<Cont>().begin()), �� ���� begin()�� end()����Լ��� ���θ� 
	���� Ȯ���ؾ� �Ѵ�. ������ �̴� ���ŷӱ⿡ �̵��� �������� ���ø��� �̿��Ͽ� �ϳ��� ���� ���� Ȯ���ϰ� ���ִ� void_t�Լ��� �ִ�.
	 �׸��� ������ �Ǽ��� template argument�κп� ���� �־� Ÿ��üũ�κ��� ����ȭ�Ǵ� ���� �����ϱ� ���� ����Ÿ�Կ� �ִ� ���� �ٶ����ϴ�.(void print ó�� ����Ÿ���� ������ �� �ִٸ�)
	template <typename Cont>
	std::void_t<decltype(std::declval<Cont>().begin()), 
				decltype(std::declval<Cont>().end()> print(const Cont& containter) //check in return type
*/ 
