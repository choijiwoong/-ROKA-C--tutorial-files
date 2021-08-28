#include <iostream>
#include <string>

//립니다. 이를 짧은 문자열 최적화(SSO - short string optimization) 이라고 부릅니다.

/*1
//normal structure of basic_string.
template <class CharT, class Traits=std::char_traits<CharT>, class Allocator=std::allocator<CharT>>//send template instantiated version of std::char_traits to Traits.
class basic_string;//CharT=char, std::string. traits saves normal calculation of string. Logic seperation! of saving(basic_string) and calculation(traits). for user custom.
//allocator will be handle soon!

//how can i treat basic_string to modify template argument! treat logically seperations.
#include <cctype>
//all function in char_traits are static function
struct my_char_traits: public std::char_traits<char>{//it must be made with all member function that char_traits produces.
	static int get_real_rank(char c){//inheritance is not needed. just for convenience at this time.
		if(isdigit(c))//if num, decrease many rank 
			return c+256;//low rank == high priority
		return c;
	}
	
	static bool lt(char c1, char c2){//compare string's size.
		return get_real_rank(c1)<get_real_rank(c2);
	}
	
	static int compare(const char* s1, const char* s2, size_t n){//compare char type's size).
		while(n--!=0){
			if(get_real_rank(*s1)<get_real_rank(*s2))
				return -1;
			if(get_real_rank(*s1)>get_real_rank(*s2))
				return 1;
			++s1;//if same, to next char
			++s2;
		}
		return 0;
	}
};//simple change of Traits can produce cutomized basic_string that we can use.

int main(){
	std::basic_string<char, my_char_traits> my_s1="1a";//toss my_char_traits as template argument.
	std::basic_string<char, my_char_traits> my_s2="a1";
	
	std::cout<<"string that has low rank of digit : "<<std::boolalpha<<(my_s1<my_s2)<<std::endl;//changed result thanks to Traits
	//boolalpha(1)==true
	std::string s1="1a";//normal define.
	std::string s2="a1";
	
	std::cout<<"common string : "<<std::boolalpha<<(s1<s2)<<std::endl;//normal result
	
	return 0;	
}*/

//2
//if we define new to global funtion, compiler overloads all new operator.
//it we define new as member function of some class, new operators in that class are overloaded.
void* operator new(std::size_t count){
	std::cout<<count<<" bytes allocate "<<std::endl;
	return malloc(count);
}

int main(){
	std::cout<<"make s1 --- "<<std::endl;
	std::string s1="this is a pretty long sentence!!!";
	std::cout<<"size of s1 : "<<sizeof(s1)<<std::endl;
	
	std::cout<<"make s2 --- "<<std::endl;
	std::string s2="short sentence";
	std::cout<<"size of s2 : "<<sizeof(s2)<<std::endl;
	
	return 0;
}


/*
[1.	basic_string]
1.	std::string은 basic_string의 클래스 템플릿의 인스턴스화 버전이다. 
2.	총 5가지 종류의 인스턴스화 된 문자열들이 있다.
	타입, 정의, 비고 
	-std::string  std::basic_string<char>
	-std::wstring	std::basic_string<wchar_t>	wchar_t의 크기는 시스템마다 다름(고로 확실하게하려고 아래꺼 만듬) 
	-std::u8string	std::basic_string<char8_t>	C++20에 새로 추가. 1bite. UTF-8문자열 보관 가능
	-std::u16string	std::basic_string<char16_t>	2bite. UTF-16문자열 보관 가능. 
	-std::u32string	std::basic_string<char32_t>	4bite. UTF-32문자열 보관 가능.
3.	Traits 활용 예시: 숫자들의 순위가 알파벳보다 낮은 문자열 
	Traits를 전달할 때는 char:traits에서 제공하는 모든 멤버 함수들이 구현된 클래스가 전달되어야 한다!! 
	또한 char_traits에 정의되는 함수들은 모두 static 함수들인데, 간단한 연산을 제공하는 것이기 때문에 데이터가 저장될 필요가 없기 때문이다!(stateless하다고 표현함) 
	 고로 대소비교부분만 바꿔주자! 
	 
[2.	짧은 문자열 최적화(SSO)]
1.	basic_string이 저장하는 문자열의 길이는 천차 만별인데, 수십만 바이트의 거대한 문자열을 할당하는 경우는 드문 대신, 짧은 문자열을 할당하는 것은 굉장히 잦다. 
	길이가 짧은 문자열을 여러번 할당한다면 메모리 할당이 잦아짐으로써, 비효율적이게 된다. 
	 따라서 basic_string은 짧은 길이의 문자열의 경우 따로 문자 데이터를 위해 메모리를 할당하지 않고, 객체 자체에 저장해버린다.
	이를 짧은 문자열 최적화(SSO-Short String Optimization)이라고 한다. 

 
*/
