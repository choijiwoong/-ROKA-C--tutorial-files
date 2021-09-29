#include <iostream>
#include <string>
#include <cctype>

/*overloading of Traits class in basic_string
struct my_char_traits: public std::char_traits<char>{//std::string's traits template argument is char_traits<char>
	static int get_real_rank(char c){//ranking
		if(isdigit(c))//if number
			return c+256;//add many number to priority
		return c;
	}
	
	static bool It(char c1, char c2){//compare size of strings
		return get_real_rank(c1)<get_real_rank(c2);
	}
	
	static int compare(const char* s1, const char* s2, size_t n){//compare length of string
		while(n--!=0){
			if(get_real_rank(*s1)<get_real_rank(*s2))
				return -1;
			if(get_real_rank(*s1)>get_real_rank(*s2))
				return 1;
			++s1;
			++s2;
		}
		return 0;
	}
};

int main(){
	std::basic_string<char, my_char_traits> my_s1="1a";
	std::basic_string<char, my_char_traits> my_s2="a1";
	
	std::cout<<"low string : "<<std::boolalpha<<(my_s1<my_s2)<<std::endl;
	
	std::string s1="1a";
	std::string s2="a1";
	
	std::cout<<"low string : "<<std::boolalpha<<(s1<s2)<<std::endl;
}*/

/*초성분리
using namespace std::string_literals;
int main(){
	std::u16string u16_str=u"안녕하세요 저는 정이에요";
	std::string jaum[]={"ㄱ", "ㄲ", "ㄴ", "ㄷ", "ㄸ", "ㄹ", "ㅁ",
                        "ㅂ", "ㅃ", "ㅅ", "ㅆ", "ㅇ", "ㅈ", "ㅉ",
                        "ㅊ", "ㅋ", "ㅌ", "ㅍ", "ㅎ"};

	for(char16_t c: u16_str){
		if(!(0xAC00<=c && c<=0xD7A3))//range of Korean in unicode
			continue;
		
		int offset=c-0xAC00;//Korean start ar AC00
		int jaum_offset=offset/0x24C;//한 초성당 0x24C
		
		std::cout<<jaum[jaum_offset];
	}
} */

//string_view
void* operator new(std::size_t count){
	std::cout<<count<<" bytes allocated"<<std::endl;
	return malloc(count);
} 

int main(){
	std::cout<<"string---------"<<std::endl;
	std::string s="somethimes string is very slow";
	std::cout<<"---------------"<<std::endl;
	std::cout<<s.substr(0, 15)<<std::endl<<std::endl;
	
	std::cout<<"string view-----"<<std::endl;
	std::string_view sv=s;//C++17
	std::cout<<"---------------"<<std::endl;
	std::cout<<sv.substr(0, 15)<<std::endl;
}

/*
1.	std::string은 std::basic_string의 인스턴스화 버전이다. 
	템플릿 인자로 CharT, Traits, Allocatior를 받는데 로직들을 분리시켜 사용자정의가 쉽게 만들었다. 
2.	basic_string의 Traits는 stateless하여 static function들로 구성된다. 
3.	Short String Optimization(SSO)는 짧은 길이의 문자열을 할당없이 객체에 저장하는 것이다. C++11 이전에는 문자열이 바뀌어야 비로소 복사를 하는 Copy On Write기법이 사용되었다.
4.	s리터럴 연산자를 사용하기 위해서 using namespace std::string_literals;가 필요하다. 
	R(Raw String Literal)은 안에 어떤 식이던 부호던 스트링으로 분류한다. )"제외 이는 foo(~)foo로 해결가능 
5.	메모리 아끼려고 string을 &로 받는 함수를 만들었는데, char*형 문자열이 들어가면 오버로딩규칙에의해 &이더라도 string객체가 생성되었다. 
	고로 string_view객체로 받아 여러 맴버함수로 작업(find, substr)을 처리할 수 있는데, 이 객체 생성시엔 메모리할당이 안된다. 다만 얘가 참조하는 문자열이 존재하는지는 확인해야한다. 그렇지 않으면 Undefined behaivor발생
*/
