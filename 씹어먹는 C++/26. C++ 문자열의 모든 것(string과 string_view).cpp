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
//��string literal. For use this, we have to use namespace std::string_literals. it can also express int or float,,,etc.

using namespace std::literals;

int main(){
	//string literal
	auto s1="hello"s;//string literal used! 
	std::cout<<"length of s1 : "<<s1.size()<<std::endl;
	
	//all string print
	std::string str=R"(asdfasdf
�� �ȿ���
� �͵��� �͵�
// �̷��͵� �ǰ�
#define hasldfjalskdfj
\n\n <--- Escape ���ص� ��
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
	std::u32string u32_str=U"�̰� UTF-32 ���ڿ� �Դϴ�";//1234567890 123 4 567
	std::cout<<u32_str.size()<<std::endl;//print 17
	
	//UTF-8 that used well in web
	std::string u8_str=u8"�̰� UTF-8 ���ڿ� �Դϴ�";//12 345678901 2 3456
	std::cout<<u8_str.size()<<std::endl;//print 32 because of 1~4bites per char. Korean is 3bites, others are 1bites.
	//std::string just think str made by char. so it returnd amount of char in str.size not real length. how many char possible.
	//so std::cout<<u8_str[1]; doesn't print "��"
	
	//so if we search UTF-8 string, we have to do like that.
	std::string stg=u8"�̰� UTF-8 ���ڿ� �Դϴ�";//1 234567890 1 2 34 5 6
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
	std::u16string u16_str=u"�̰� UTF-16 ���ڿ� �Դϴ�";
	std::cout<<u16_str.size()<<std::endl;//same to real length! so we can make code that seperate Korean like that
	
	//seperate Korean by using UTF-16
	std::u16string u16_string=u"�ȳ��ϼ��� ����� �ڵ忡 ���� ���� ȯ���մϴ�";
	std::string jaum[]={"��", "��", "��", "��", "��", "��", "��",
                        "��", "��", "��", "��", "��", "��", "��",
                        "��", "��", "��", "��", "��"};
	for(char16_t c:u16_str){
		if(!(0xAC00<=c && c<=0xD7A3))//exception. range of Korean in unicode.
			continue;
		
		//Korean starts at AC00 and 0x24C per char.
		int offser=c-0xAc00;
		int jaum_offset=offset/0x24C;
		std::cout<<jaum[jaum_offset];//print ��������������������������������������  seperate completely!
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
	//��implicitly create std::string object. memory allocation!
	std::cout<<contains_very("C++ string is not easy to use")<<std::endl;
	
	//than, how about use const char* as function argument? two problems occur.
	//1. we have to get const char* address by using c_str that changes string to char
	//2. In convertion to const char*, we lost length information. so if we need length information, we have to calculate everytime we use.
	//so we have to make two function with argument 'const string&' and 'const char*' by using overloading.
	//but this problem solved in C++17 thanks to string_view!
	
	//string_view; not own, just read
	std::cout<<std::boolalphs<<contains_very("c++ string is very easy to use")<<std::endl;//print true with no allocation!
	//��no need memory allocation! 
	std::cout<<contains_very("c++ string is not easy to use")<<std::endl;//print false with no allocation!
	
	std::string str="some long long long long long long string";
	std::cout<<"----------------------"<<std::endl;
	std::cout<<contains_very(str)<<std::endl;//print false with no allocation!
	
	//benefit of string_view. fast calculation of substr because it create new string_view not string.
	std::cout<<"string -----"<<std::endl;
	std::string s="sometimes string is very slow";
	//��new allocation occcur! 
	std::cout<<"--------------------"<<std::endl;
	std::cout<<s.substr(0, 20)<<std::endl<<std::endl;//normal string work of substr 
	//��new allocation occcur! 
	
	std::cout<<"string_view -----"<<std::endl;
	std::string_view sw=s;
	//��no allocation! 
	std::cout<<"--------------------"<<std::endl;
	std::cout<<sv.substr(0, 20)<<std::endl;
	//��no allocation too! thanks to string_view
	
	//what's happen if original data disappeared?
	std::string sv=return_sv();//get erased data's string_view!
	std::cout<<sv<<std::endl;//strange print "a string"(it also can srash program). Undefined behavior!
	
	return 0;
}



/*
[1.	basic_string]
1.	std::string�� basic_string�� Ŭ���� ���ø��� �ν��Ͻ�ȭ �����̴�. 
2.	�� 5���� ������ �ν��Ͻ�ȭ �� ���ڿ����� �ִ�.
	Ÿ��, ����, ��� 
	-std::string  std::basic_string<char>
	-std::wstring	std::basic_string<wchar_t>	wchar_t�� ũ��� �ý��۸��� �ٸ�(��� Ȯ���ϰ��Ϸ��� �Ʒ��� ����) 
	-std::u8string	std::basic_string<char8_t>	C++20�� ���� �߰�. 1bite. UTF-8���ڿ� ���� ����
	-std::u16string	std::basic_string<char16_t>	2bite. UTF-16���ڿ� ���� ����. 
	-std::u32string	std::basic_string<char32_t>	4bite. UTF-32���ڿ� ���� ����.
3.	Traits Ȱ�� ����: ���ڵ��� ������ ���ĺ����� ���� ���ڿ� 
	Traits�� ������ ���� char:traits���� �����ϴ� ��� ��� �Լ����� ������ Ŭ������ ���޵Ǿ�� �Ѵ�!! 
	���� char_traits�� ���ǵǴ� �Լ����� ��� static �Լ����ε�, ������ ������ �����ϴ� ���̱� ������ �����Ͱ� ����� �ʿ䰡 ���� �����̴�!(stateless�ϴٰ� ǥ����) 
	 ��� ��Һ񱳺κи� �ٲ�����! 
	 
[2.	ª�� ���ڿ� ����ȭ(SSO)]
1.	basic_string�� �����ϴ� ���ڿ��� ���̴� õ�� �����ε�, ���ʸ� ����Ʈ�� �Ŵ��� ���ڿ��� �Ҵ��ϴ� ���� �幮 ���, ª�� ���ڿ��� �Ҵ��ϴ� ���� ������ ���. 
	���̰� ª�� ���ڿ��� ������ �Ҵ��Ѵٸ� �޸� �Ҵ��� ��������ν�, ��ȿ�����̰� �ȴ�. 
	 ���� basic_string�� ª�� ������ ���ڿ��� ��� ���� ���� �����͸� ���� �޸𸮸� �Ҵ����� �ʰ�, ��ü ��ü�� �����ع�����.
	�̸� ª�� ���ڿ� ����ȭ(SSO-Short String Optimization)�̶�� �Ѵ�. 
2.	new operator�� �����ε��ϸ� ��� new�����ڵ��� �� �Լ��� ����ϰ� �ǰ�, Ŭ���� ���ο� ����Լ��� new�� �����ε��ϸ� ��ü�� new�� ������ �� �� �Լ��� ȣ��ȴ�.
3.	���̺�������� �޸��Ҵ��� �ϱ�����ϴ� ���̴� �ٸ�����, �ַ� C++���̺귯��(gcc�� libstdc++, clang�� libc++)���� SSO�� ����Ѵ�. ���� C++11������ basic_string�� Copy On Write����� ���Ǿ��µ�, ����� ���ڿ��� �ٲ𶧰� �Ǽ��� ���縦 �����ϴ� ����̴�.

[3.	���ڿ� ���ͷ� �����ϱ�]
1.	C������ ����������, C++���� auto str="hello"�� �ϸ� string�� �ƴ� const char*�� ���ǵȴ�. �� string���ڿ��� ������� string str="hello"ó�� ��ø� ����� �ߴ�.
2.	��� �� ������ �ذ��ϱ� ���� auto str="hello"s �� ����ϴµ�, ""�ڿ� s�� �ٿ��ָ� auto�� string���� �߷еȴ�. using namespace std::literals; �ʼ�! 
3.	���ڿ� ���ͷ� ���� ������ �ε��Ҽ���� ���ͷ������� �ִ�. ���� ""���� ���ڿ� ���ͷ��� ������ �� �ִµ� ���� std::wstring wstr=L"hello";ó�� L�� ���̸� wchar_t �迭�� ������ش�.
4.	C++11�� ������ ������� Raw string literal�̶�� �͵� �ִ�. 

[4.	C++���� �ѱ� �ٷ��]
1.	������ ��� ���ڵ��� ��ǻ�ͷ� ǥ���� �� �ֵ��� �����ڵ�(Unicode)���. �����ڵ忡�� ���ڰ� �뷫 14���� �ֱ⿡ �ּ� int�� ����ؾ� �Ѵ�.
	������, ����� ���� ������ 0~127�����̹Ƿ� 1����Ʈ ���ڸ� ����ص� ���� ǥ���� �� �ִ�. ��� ��� ���ڸ� 4����Ʈ�� �����ؼ� ����ϴ� ���� ��ȿ�����̱⿡ ������ ����
	���ڵ�(Encoding)����̴�. 
	-UTF-8: ���ڸ� �ּ� 1���� �ִ� 4����Ʈ�� ǥ��(��, ���ڸ��� ���̰� �ٸ���.)
	-UTF-16: ���ڸ� 2or 4����Ʈ�� ǥ���Ѵ�.
	-UTF-32: ���ڸ� 4����Ʈ�� ǥ���Ѵ�.
2.	std::string�� ���ڵ��� ���þ��� �׳� char�� ������ ���⿡ str.size()�� ���ڿ��� ���� ���̰� �ƴ� char�� � �ִ����� �˷��ش�. 
	���� UTF-8���ڿ��� basic_string�� ������ ����� �� �ִ�. (size()����. �װ� ���� �ڵ�ó�� �ٷ�) 
3.	UTF-16�� ��κ� 2����Ʈ�� ���ڵ��ǰ�, �̸����� ����Ʈ�������ڰ����Ÿ� 4����Ʈ�� ���ڵ� ��. ���������� �и� ����.
4.	C++�� Go���ó�� ���ڵ��� ���ڿ��� ���ܿ��� ������ ó���� �� ����. ���� ���� ���� ��� ���ڿ��� UTF-32�� �ٲٴ� ��������, �̴� ���� �޸𸮸� �䱸�Ѵ�.
	������ UTF8-CPP��� ���ڵ��� ���ڿ��� ���� �ٷ� �� �ִ� ���̺귯���� �����Ѵ�.(ǥ�� �ƴ�) _https://github.com/nemtrif/utfcpp

[5.	string_view]
1.	� �Լ��� ���ڿ��� ������ ��, �б⸸ �ϸ� const std::string& �̳� const char*�� �ް� �ȴ�. ������ ���� �������� �ִ�. 
2.	const char*�� ���ڷ� �޾��� ���� ���������� �����ּҰ��� �����ϱ⿡ allocation�� not occur�ϰ�, const char*�� ��¿ �� ������
	string�� ��� length������ �̹� ���⿡ ȿ�����̴�. 
	 so string_view's functions are operations that don't modify original string. ��ǥ������ find�� �κ� ���ڿ��� ��� substr�� �ִµ�, string�� ��� �κ� ���ڿ��� ���� �����ϱ⿡ O(n)������, string_view�� substr�� ��� �Ǵٸ� view�� �����ϹǷ� O(1)�� �ſ� ������ �����ȴ�.
	  
*/
