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

//2 is_integral in type_traits
class A{};

template <typename T>
void only_integer(const T& t){
	static_assert(std::is_integral<T>::value);
	std::cout<<"T is an integer\n";
}
int main(){
	int n=3;
	only_integer(n);
	
	A a;
	only_integer(a);
}


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
*/
