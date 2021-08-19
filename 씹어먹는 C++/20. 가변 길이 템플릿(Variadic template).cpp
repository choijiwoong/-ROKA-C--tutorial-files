#include <iostream>
#include <string> 
#include <cstring>

/*1
template <typename T>
void print(T arg){
	std::cout<<arg<<std::endl;
} 

template <typename T, typename... Types>
void print(T arg, Types... args){//...is parameter pack!
	std::cout<<arg<<", ";
	print(args...);//recursive! 
}

int main(){
	print(1, 3.1, "abc");
	print(1,2,3,4,5,6,7);
}*/

/*2
size_t GetStringSize(const char* s){//for compatibility
	return strlen(s);
}
size_t GetStringSize(const std::string& s){
	return s.size();
}
template <typename String, typename... Strings>
size_t GetStringSize(const String& s, Strings... strs){
	return GetStringSize(s)+GetStringSize(strs...);
}

void AppendToString(std::string* concat_str){//for escape
	return;
}
template <typename String, typename... Strings>
void AppendToString(std::string* concat_str, const String& s, Strings... strs){
	concat_str->append(s);
	AppendToString(concat_str, strs...);
}

template <typename String>
std::string StrCat(const String& s){
	return std::string(s);
} 
template <typename String, typename... Strings>
std::string StrCat(const String& s, Strings... strs){
	//return std::string(s)+StrCat(strs...);
	//recursive! but it's same that we call operator+ 5 times. so StrCat's arguments is 5, memory allocation can be 5 times.
	
	size_t total_size=GetStringSize(s, strs...);//calculate all size
	
	std::string concat_str;
	concat_str.reserve(total_size);//reserve space
	
	concat_str=s;
	
	AppendToString(&concat_str, strs...);
	
	return concat_str;

}//so first, we calculate whole string size.

int main(){
	std::cout<<StrCat(std::string("this"), " ", "is", " ", std::string("a"), " ", std::string("sentence"));
}*/

/*3
int sum_all(){ return 0; }//for escape

template <typename... Ints>
int sum_all(int num, Ints... nums){
	return num+sum_all(nums...);
}

template<typename... Ints>//template parameter pack
double average(Ints... nums){//function parameter pack
	return static_cast<double>(sum_all(nums...))/sizeof...(nums);//sizeof... to parameter pack! and nums... and nums are used! nums...each nums and nums are all variable in argument
}

int main(){
	std::cout<<average(1, 4, 2, 3, 10)<<std::endl;
}*/

template <typename... Ints>//Unary Fold
int sum_all(Ints... nums){
	return (...+nums);//Fold format! in C++ 17. It's can be read at compiler return ((((1+4)+2)+3)+10); it call Unary left fold!
} //for understanding, it is return (((((nums[0]+nums[1])+num[2])+...)+nums[last]) 

template <typename Int, typename... Ints>//Binary Fold
Int diff_from(Int start, Ints... nums){
	return (start-...-nums);//Fold format with ... and nums
}

class A{
	public:
		void do_something(int x) const{
			std::cout<<"Do something with "<<x<<std::endl;
		}
}; 
template <typename T, typename... Ints>
void do_many_things(const T& t, Ints... nums){
	(t.do_something(nums), ...);//call do_something functions to each arguments! thanks to , operator in Fold format. it's same every arguments call t.do_something(arg).
}

int main(){
	//by Unary Fold
	std::cout<<sum_all(1, 4, 2, 3, 10)<<std::endl;
	//by Binary Fold
	std::cout<<diff_from(100, 1, 4, 2, 3, 10)<<std::endl;
	//use operator ','
	A a;
	do_many_things(a, 1, 3, 2, 4);
}


/*
[0. 들어가기에 앞서]
1.	템플릿을 잘 사용하면 써야되는 코드의 양을 비약적으로 줄이 수 있는데, 그 연장선으로써 템플릿을 사용하여 임의의 개수의 인자를 받는 방법에 대하여 알아보자. 

[1. 가변 길이 템플릿(variadic template)]
1.	파이썬의 경우 print(1, 3.1, "abc")와 같이 print함수의 인자로 전달되는 모든것을 출력할 수 있다. C++템플릿을 이용하여 이를 C++에서도 구현할 수 있다.
2.	typename...뒤에 ...으로 오는 것을 파라미터 팩(parameter pack)이라고 한다. 템플릿 파라미터 팩의 경우, 0개 이상의 템플릿 인자들을 나타낸다.
	마찬가지로 함수에 인자로 ...로 오는 것을 함수 파라미터 팩이라고 부르며, 템플릿 파라미터 팩과 함수 파라미터 팩의 차이점은
	템플릿의 경우 타입 앞에 ...이 오고, 함수의 경우 타입 뒤에 ...가 온다는 점이다. 
3.	우선, 첫번째 인자가 arg로 std문을 이용하여 출력되고, 나머지가 재귀식으로 print를 호출하는 방식이 반복된다. 그러다 마지막에 인자가 하나 남으면 컴파일러는 void print(T arg, Types... args)가 아닌 void print(T arg)를 선택하게 되는데,
	이는 C++ 규칙 상, 파라미터 팩이 없는 함수의 우선순위가 높기 때문이다. 덕분에 print(T arg)함수가 로출되어 endl이 출력되며 줄바꿈이 되었다.
4.	여기서 재미있는 점은, 두 print함수의 위치를 바꾸면 컴파일 오류가 발생한다. 
	이유는 C++컴파일러는 함수를 컴파일 시에, 자신의 앞에 정의되어 있는 함수들 밖에 보지 못하기 때문인데, 이는 컴파일상에서 void print(T arg, Types...args)함수를 읽을 때 아래의 void print(T arg)함수의
	존재를 모른다는 것이다. 이는 void print(T arg, Types... args)함수에서 마지막 print("abc")의 오버로딩을 찾을 때 다시 파라미터 팩이 있는 자기자신을 찾게 되는데, 그 함수 안에서 다시 print()가 호출이 된다. 이때 print함수가 어디있는지를 더는 찾지 못하기에 오류를 나타내게 된다. 
5.	따라서 템플릿 함수를 사용할 때에는 그 순서에 유의하여 사용해야 한다.
 
[2.	임의의 개수의 문자열을 합치는 함수]
1.	std::string에서 문자열을 합치기 위해서는 concat=s1+s2+s3와 같이 했는데, 위는 사실 concat=s1.operator+(s2).operator+(s3)와 같은 말이다.
	문제는 s2를 더할 때 메모리 할당이 발생하고, s3를 더할 때 메모리 할당이 또 한번 발생하기에 시간적으로 비효율적이다. (메모리 할당/해제는 매우 느린 작업 중에 하나이다.)
2.	그래서 합쳐진 문자열의 크기는 미리 알 수 있으니까 한번에 필요한 만큼 메모리를 할당하는 것이 중요하기에 
	std::string concat;
	concat.reserve(s1.size()+s2.size()+s3.size());
	concat.append(s1);
	concat.append(s2);
	concat.append(s2);
	으로 해결할 수 있다. 혹은
	std::string concat=StrCat(s1, "abc", s2, s3);을 통해 깔뜸하게 불필요한 메모리 할당 없이 해결할 수 있다.
3.	하지만 여기에서 발생하는 한게점은 StrCat함수가 임의의 개수의 인자를 받아야 한다는 것인데, 여기서 가변 길이 템플릿이 사용된다. 

[3.	sizeof...]
1.	sizeof 연산자는 인자의 크기를 리턴하지만, 파라미터 팩에 sizeof...을 사용할 경우, 전체 인자의 개수를 리턴하게 된다. 

[4.	Fold Expression]
1.	위에서 살펴본 가변 길이 템플릿은 매우 편리하지만, 재귀 함수 형태로 구성해야되기 때문에, 반드시 재귀 호출 종료를 위한 함수를 따로 만들어야 한다는 것이 단점이다.
	이는 코드의 복잡도를 쓸데없이 늘리게 된다.
2.	하지만 C++17에 새로 도입된 Fold 형식을 사용한다면 이를 훨씬 쉽고 간단하게 표현할 수 있다. 
3.	return (...+nums)이 바로 Fold 형식으로, 위의 코드의 형태는 단항 좌측 Fold(Unary left fold)이라고 부른다. C++17에서 지원하는 Fold의 방식으로는
	(E op ...)     단항 우측 Fold     (E1 op(...op(En-1 op En))) 
	(... op E)     단항 좌측 Fold     (((E1 op E2) op ...) op EN)
	(E op ... op I)이항 우측 Fold     (E1 op (... op (En-1 op (En op I))))
	(I op ... op E)이항 좌측 Fold     ((((I op E1) op E2) op ...) op EN 
	여기서 op은 대부분의 이항 연산자들(+, -, <, <<, ->, ,, etc...)이 포함된다. 
4.	중요한 점은 Fold식을 쓸 때 꼭 ()로 감싸줘야 한다. return (...+nums)를 return ...+nums;로 하면 오류!! 애초에 위의 표에 () 자체도 Fold 식에 포함되어 있음 
5.	한가지 더 재미있는 점은 ,연산자를 사용하면 각각의 인자들에 대해 원하는 식을 실행할 수 있다. 
*/
