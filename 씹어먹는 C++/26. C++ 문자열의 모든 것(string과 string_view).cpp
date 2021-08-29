#include <iostream>
#include <string>


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

/*2
//if we define new to global funtion, compiler overloads all new operator.
//it we define new as member function of some class, new operators in that class are overloaded.
void* operator new(std::size_t count){
	std::cout<<count<<" bytes allocate "<<std::endl;
	return malloc(count);
}

int main(){
	std::cout<<"make s1 --- "<<std::endl;
	std::string s1="this is a pretty long sentence!!!";//operator new called! we can check memory allocation without change of basic_string. 
	std::cout<<"size of s1 : "<<sizeof(s1)<<std::endl;
	
	std::cout<<"make s2 --- "<<std::endl;
	std::string s2="short sentence";//no memory allocation because of SSO(but my version make allocation,,,)
	std::cout<<"size of s2 : "<<sizeof(s2)<<std::endl;
	
	return 0;
}*/

//3
//std::string operator"" s(const char *str, std::size_t len);
//ㄴstring literal. For use this, we have to use namespace std::string_literals. it can also express int or float,,,etc.

using namespace std::literals;

int main(){
	//string literal
	auto s1="hello"s;//string literal used! 
	std::cout<<"length of s1 : "<<s1.size()<<std::endl;
	
	//all string print
	std::string str=R"(asdfasdf
이 안에는
어떤 것들이 와도
// 이런것도 되고
#define hasldfjalskdfj
\n\n <--- Escape 안해도 됨
)";//normally printed! but the problem is we can't add )" in string. but it can solve by delimiter
	std::cout<<str<<std::endl;
	
	//delimiter
	std::string str1=R"foo(
	)";<--ignored
	)foo";
	std::cout<<str1;//Raw string's grammer: R"/* delimiter */( /* string */ )/* delimiter */"
	//for special char like )" we can use delimiter. first and second delimiter's name must be same. delimiter is like a bracket
	
	return 0;
} 

//4
int main2(){
	//UTF-32 that's some unefficient because of fixed 4bites.
	std::u32string u32_str=U"이건 UTF-32 문자열 입니다";//1234567890 123 4 567
	std::cout<<u32_str.size()<<std::endl;//print 17
	
	//UTF-8 that used well in web
	std::string u8_str=u8"이건 UTF-8 문자열 입니다";//12 345678901 2 3456
	std::cout<<u8_str.size()<<std::endl;//print 32 because of 1~4bites per char. Korean is 3bites, others are 1bites.
	//std::string just think str made by char. so it returnd amount of char in str.size not real length. how many char possible.
	//so std::cout<<u8_str[1]; doesn't print "건"
	
	//so if we search UTF-8 string, we have to do like that.
	std::string stg=u8"이건 UTF-8 문자열 입니다";//1 234567890 1 2 34 5 6
	size_t i=0;
	size_t len=0;
	
	while(i<stg.size()){
		int char_size=0;
		if((stg[i]&0b11111000)==0b11110000)
			char_size=4;
		else if((stg[i]&0b11110000)==0b11100000)
			char_size=3;
		else if((stg[i]&0b11100000)==0b11000000)
			char_size=2;
		else if((stg[i]&0b10000000)==0b00000000)
			char_size=1;
		else{
			std::cout<<"strange string detected!"<<std::endl;
			char_size=1;
		}
		
		std::cout<<stg.substr(i, char_size)<<std::endl;//read currect char by reading curect size(char_size) at start point(i)
		
		i+=char_size;
		len++;
	}
	std::cout<<"real length of string ; "<<len<<std::endl;
	
	//UTF-16 that almost uses 2bites per char.
	std::u16string u16_str=u"이건 UTF-16 문자열 입니다";
	std::cout<<u16_str.size()<<std::endl;//same to real length! so we can make code that seperate Korean like that
	
	//seperate Korean by using UTF-16
	std::u16string u16_string=u"안녕하세용 모두의 코드에 오신 것을 환영합니다";
	std::string jaum[]={"ㄱ", "ㄲ", "ㄴ", "ㄷ", "ㄸ", "ㄹ", "ㅁ",
                        "ㅂ", "ㅃ", "ㅅ", "ㅆ", "ㅇ", "ㅈ", "ㅉ",
                        "ㅊ", "ㅋ", "ㅌ", "ㅍ", "ㅎ"};
	for(char16_t c:u16_str){
		if(!(0xAC00<=c && c<=0xD7A3))//exception. range of Korean in unicode.
			continue;
		
		//Korean starts at AC00 and 0x24C per char.
		int offser=c-0xAc00;
		int jaum_offset=offset/0x24C;
		std::cout<<jaum[jaum_offset];//print ㅇㄶㅅㅇㅁㄷㅇㅋㄷㅇㅇㅅㄱㅇㅎㅇㅎㄴㄷ  seperate completely!
	}
	
	//use 4bites in UTF-16
	std::u16string u16=u"????";
	std::cout<<u16.size()<<std::endl;//print 4
	
	return 0;
} 

//5
//when we get function argument as const string&
void operator new(std::size_t count){
	std::cout<<count<<" bytes allocated "<<std::endl;
	return malloc(count);
}
//return true if "very" exist in string
//bool contains_very(const std::string& str){
//	return str.find("very")!=std::string::npos;//if not find, return npos value.
//}

//string view!
bool contains_very(std::string_view str){//just only read work! so if data is erased, than compiler occurs undefined behavior.
	return str.find("very")!=std::string_view::npos;
}//So it's very bery blueberry important status of data.

//if data disappear in string_view?
std::string_view return_sv(){
	std::string s="this is a string";
	std::string_view sv=s;
	return sv;//original data erase!
}

int main3(){
	std::cout<<std::boolalphs<<contains_very("C++ string is very easy to use")<<std::endl;
	//ㄴimplicitly create std::string object. memory allocation!
	std::cout<<contains_very("C++ string is not easy to use")<<std::endl;
	
	//than, how about use const char* as function argument? two problems occur.
	//1. we have to get const char* address by using c_str that changes string to char
	//2. In convertion to const char*, we lost length information. so if we need length information, we have to calculate everytime we use.
	//so we have to make two function with argument 'const string&' and 'const char*' by using overloading.
	//but this problem solved in C++17 thanks to string_view!
	
	//string_view; not own, just read
	std::cout<<std::boolalphs<<contains_very("c++ string is very easy to use")<<std::endl;//print true with no allocation!
	//ㄴno need memory allocation! 
	std::cout<<contains_very("c++ string is not easy to use")<<std::endl;//print false with no allocation!
	
	std::string str="some long long long long long long string";
	std::cout<<"----------------------"<<std::endl;
	std::cout<<contains_very(str)<<std::endl;//print false with no allocation!
	
	//benefit of string_view. fast calculation of substr because it create new string_view not string.
	std::cout<<"string -----"<<std::endl;
	std::string s="sometimes string is very slow";
	//ㄴnew allocation occcur! 
	std::cout<<"--------------------"<<std::endl;
	std::cout<<s.substr(0, 20)<<std::endl<<std::endl;//normal string work of substr 
	//ㄴnew allocation occcur! 
	
	std::cout<<"string_view -----"<<std::endl;
	std::string_view sw=s;
	//ㄴno allocation! 
	std::cout<<"--------------------"<<std::endl;
	std::cout<<sv.substr(0, 20)<<std::endl;
	//ㄴno allocation too! thanks to string_view
	
	//what's happen if original data disappeared?
	std::string sv=return_sv();//get erased data's string_view!
	std::cout<<sv<<std::endl;//strange print "a string"(it also can srash program). Undefined behavior!
	
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
2.	new operator를 오버로딩하면 모든 new연산자들이 위 함수를 사용하게 되고, 클래스 내부에 멤버함수로 new를 오버로딩하면 객체를 new로 생성할 때 그 함수가 호출된다.
3.	라이브버리마다 메모리할당을 하기시작하는 길이는 다르지만, 주류 C++라이브러리(gcc의 libstdc++, clang의 libc++)들은 SSO를 사용한다. 또한 C++11이전에 basic_string에 Copy On Write기법이 사용되었는데, 복사된 문자열이 바뀔때가 되서야 복사를 수행하는 방식이다.

[3.	문자열 리터럴 정의하기]
1.	C에서와 마찬가지로, C++에서 auto str="hello"를 하면 string이 아닌 const char*로 정의된다. 즛 string문자열을 만드려면 string str="hello"처럼 명시를 해줘야 했다.
2.	고로 이 문제를 해결하기 위해 auto str="hello"s 를 사용하는데, ""뒤에 s를 붙여주면 auto가 string으로 추론된다. using namespace std::literals; 필수! 
3.	문자열 리터럴 말고도 정수나 부동소수점등도 리터럴사용법이 있다. 또한 ""말고도 문자열 리터럴을 정의할 수 있는데 예로 std::wstring wstr=L"hello";처럼 L을 붙이면 wchar_t 배열을 만들어준다.
4.	C++11의 유용한 기능으로 Raw string literal이라는 것도 있다. 

[4.	C++에서 한글 다루기]
1.	전세계 모든 문자들을 컴퓨터로 표현할 수 있도록 유니코드(Unicode)사용. 유니코드에는 문자가 대략 14만개 있기에 최소 int를 사용해야 한다.
	하지만, 영어는 값의 범위가 0~127사이이므로 1바이트 문자만 사용해도 전부 표현할 수 있다. 고로 모든 문자를 4바이트씩 지정해서 사용하는 것은 비효율적이기에 등장한 것이
	인코딩(Encoding)방식이다. 
	-UTF-8: 문자를 최소 1부터 최대 4바이트로 표현(즉, 문자마다 길이가 다르다.)
	-UTF-16: 문자를 2or 4바이트로 표현한다.
	-UTF-32: 문자를 4바이트로 표현한다.
2.	std::string은 인코딩과 관련없이 그냥 char의 나열로 보기에 str.size()시 문자열의 실제 길이가 아닌 char이 몇개 있는지를 알려준다. 
	물론 UTF-8문자열에 basic_string의 연산을 사용할 수 있다. (size()제외. 그건 위에 코드처럼 다룸) 
3.	UTF-16은 대부분 2바이트로 인코딩되고, 이모지나 이집트상형문자같은거만 4바이트로 인코딩 됨. 초중종성도 분리 가능.
4.	C++은 Go언어처럼 인코딩된 문자열을 언어단에서 간단히 처리할 수 없다. 가장 편한 것은 모든 문자열을 UTF-32로 바꾸는 것이지만, 이는 많은 메모리를 요구한다.
	다행히 UTF8-CPP라는 인코딩된 문자열을 쉽게 다룰 수 있는 라이브러리가 존재한다.(표준 아님) _https://github.com/nemtrif/utfcpp

[5.	string_view]
1.	어떤 함수에 문자열을 전달할 때, 읽기만 하면 const std::string& 이나 const char*로 받게 된다. 하지만 각각 문제점이 있다. 
2.	const char*을 인자로 받았을 때도 마찬가지로 시작주소값만 복사하기에 allocation이 not occur하고, const char*은 어쩔 수 없지만
	string의 경우 length정보를 이미 갖기에 효율적이다. 
	 so string_view's functions are operations that don't modify original string. 대표적으로 find와 부분 문자열을 얻는 substr이 있는데, string의 경우 부분 문자열을 새로 생성하기에 O(n)이지만, string_view의 substr의 경우 또다른 view를 생성하므로 O(1)로 매우 빠르게 생성된다.
	  
*/
