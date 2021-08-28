#include <iostream>
#include <string>

//���ϴ�. �̸� ª�� ���ڿ� ����ȭ(SSO - short string optimization) �̶�� �θ��ϴ�.

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

 
*/
