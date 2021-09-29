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

/*�ʼ��и�
using namespace std::string_literals;
int main(){
	std::u16string u16_str=u"�ȳ��ϼ��� ���� ���̿���";
	std::string jaum[]={"��", "��", "��", "��", "��", "��", "��",
                        "��", "��", "��", "��", "��", "��", "��",
                        "��", "��", "��", "��", "��"};

	for(char16_t c: u16_str){
		if(!(0xAC00<=c && c<=0xD7A3))//range of Korean in unicode
			continue;
		
		int offset=c-0xAC00;//Korean start ar AC00
		int jaum_offset=offset/0x24C;//�� �ʼ��� 0x24C
		
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
1.	std::string�� std::basic_string�� �ν��Ͻ�ȭ �����̴�. 
	���ø� ���ڷ� CharT, Traits, Allocatior�� �޴µ� �������� �и����� ��������ǰ� ���� �������. 
2.	basic_string�� Traits�� stateless�Ͽ� static function��� �����ȴ�. 
3.	Short String Optimization(SSO)�� ª�� ������ ���ڿ��� �Ҵ���� ��ü�� �����ϴ� ���̴�. C++11 �������� ���ڿ��� �ٲ��� ��μ� ���縦 �ϴ� Copy On Write����� ���Ǿ���.
4.	s���ͷ� �����ڸ� ����ϱ� ���ؼ� using namespace std::string_literals;�� �ʿ��ϴ�. 
	R(Raw String Literal)�� �ȿ� � ���̴� ��ȣ�� ��Ʈ������ �з��Ѵ�. )"���� �̴� foo(~)foo�� �ذᰡ�� 
5.	�޸� �Ƴ����� string�� &�� �޴� �Լ��� ������µ�, char*�� ���ڿ��� ���� �����ε���Ģ������ &�̴��� string��ü�� �����Ǿ���. 
	��� string_view��ü�� �޾� ���� �ɹ��Լ��� �۾�(find, substr)�� ó���� �� �ִµ�, �� ��ü �����ÿ� �޸��Ҵ��� �ȵȴ�. �ٸ� �갡 �����ϴ� ���ڿ��� �����ϴ����� Ȯ���ؾ��Ѵ�. �׷��� ������ Undefined behaivor�߻�
*/
