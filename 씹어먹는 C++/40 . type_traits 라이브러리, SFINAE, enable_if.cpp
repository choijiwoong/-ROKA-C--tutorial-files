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
*/
