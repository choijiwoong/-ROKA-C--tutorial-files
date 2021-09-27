#include <iostream>
#include <string>
#include <cstring>

/*1. CONCAT BY VARIADIC TEMPLATE
//FOR RESERVE
size_t GetStringSize(const char* s){ return strlen(s); }//stop condition by type. stop condition have to be placed upper of main function, because compiler read sequencely. it can't find stop condition
size_t GetStringSize(const std::string& s){ return s.size(); }

template <typename String, typename... Strings>//get size for reserve(... is template parameter pack)
size_t GetStringSize(const String& s, Strings... strs){//(... is function parameter pack)
	return GetStringSize(s)+GetStringSize(strs...);
}

//APPEND TO STRING
void AppendToString(std::string* concat_str){ return; }//stop condition. only remaining concat_str

template <typename String, typename... Strings>//appending
void AppendToString(std::string* concat_str, const String& s, Strings... strs){
	concat_str->append(s);
	AppendToString(concat_str, strs...);
}

//STRCAT
template <typename String, typename... Strings>//template parameter pack
std::string StrCat(const String& s, Strings... strs){//function parameter pack
	size_t total_size=GetStringSize(s, strs...);
	
	std::string concat_str;
	concat_str.reserve(total_size);
	
	concat_str=s;
	AppendToString(&concat_str, strs...);//???
	
	return concat_str;
}

int main(){
	std::cout<<StrCat(std::string("this"), " ", "is", " ", std::string("a"), " ", std::string("sentence"));
}*/

/*2.FOLD EXPRESSION CONCEPT 
template <typename... Ints>
int sum_all(Ints... nums){
	return (...+nums);
}

int main(){
	std::cout<<sum_all(1,4,2,54,10)<<std::endl;
}*/

/*3. FOLD EXPRESSION APPLICATATION 1
template <typename Int, typename... Ints>
Int diff_from(Int start, Ints... nums){
	return (start-...-nums);
}

int main(){
	std::cout<<diff_from(100, 1, 4, 2, 3, 10)<<std::endl;
}*/

/*4. FOLD EXPRESSION APPLICATION 2
class A{
	public:
		void do_something(int x) const{ std::cout<<"Do something with"<<x<<std::endl; }
};

template <typename T, typename... Ints>
void do_many_things(const T& t, Ints... nums){
	(t.do_somethings(nums), ...);
}

int main(){
	A a;
	do_many_things(a, 1, 3, 2, 4);
}*/


/*
1.	가변 길이 템플릿은 파이썬의 print와 같이 임의개수의 인자를 받는 것을 말한다. 
2.	sizeof...(nums)처럼 파라미터 팩에 sizeof를 쓰면 개수를 리턴한다. 크기가 아니다 
3. 	가변 길이 템플릿에 호출종료를 위한 베이스 캐이스 없게 작동시킬 수 있는 Fold형식이 도입되었다.(C++17) 무조건 괄호로 감싸주자. 
*/


//practice
//1. CONCAT BY VARIADIC TEMPLATE
//2. FOLD EXPRESSION CONCEPT 
//3. FOLD EXPRESSION APPLICATATION 1
//4. FOLD EXPRESSION APPLICATION 2


//GetSizeString part
size_t GetSizeString(const char* s){ return strlen(s); }
size_t GetSizeString(const std::string& s){ return s.size(); }

template <typename String, typename... Strings>
size_t GetSizeString(const String& string, Strings... strings){
	return GetSizeString(string)+GetSizeString(strings...);
}

//AppendString part
void AppendString(std::string* concat){
	return;
}

template<typename String, typename... Strings>
void AppendString(std::string* concat, const String& string, Strings... strings){
	concat->append(string);
	AppendString(concat, strings...);
}

//StrCat part
template <typename... Strings>
std::string StrCat(Strings... strings){
	size_t total_size=GetSizeString(strings...);
	
	std::string concat_str;
	concat_str.reserve(total_size);
	
	AppendString(&concat_str, strings...);
	
	return concat_str;
}

//main function
int main(){
	std::cout<<StrCat(std::string("Hello!"), " ", "my", " ", std::string("name is"), " ", "ChoiJiWoong!")<<std::endl;
}
