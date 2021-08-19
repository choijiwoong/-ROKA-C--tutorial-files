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
[0. ���⿡ �ռ�]
1.	���ø��� �� ����ϸ� ��ߵǴ� �ڵ��� ���� ��������� ���� �� �ִµ�, �� ���弱���ν� ���ø��� ����Ͽ� ������ ������ ���ڸ� �޴� ����� ���Ͽ� �˾ƺ���. 

[1. ���� ���� ���ø�(variadic template)]
1.	���̽��� ��� print(1, 3.1, "abc")�� ���� print�Լ��� ���ڷ� ���޵Ǵ� ������ ����� �� �ִ�. C++���ø��� �̿��Ͽ� �̸� C++������ ������ �� �ִ�.
2.	typename...�ڿ� ...���� ���� ���� �Ķ���� ��(parameter pack)�̶�� �Ѵ�. ���ø� �Ķ���� ���� ���, 0�� �̻��� ���ø� ���ڵ��� ��Ÿ����.
	���������� �Լ��� ���ڷ� ...�� ���� ���� �Լ� �Ķ���� ���̶�� �θ���, ���ø� �Ķ���� �Ѱ� �Լ� �Ķ���� ���� ��������
	���ø��� ��� Ÿ�� �տ� ...�� ����, �Լ��� ��� Ÿ�� �ڿ� ...�� �´ٴ� ���̴�. 
3.	�켱, ù��° ���ڰ� arg�� std���� �̿��Ͽ� ��µǰ�, �������� ��ͽ����� print�� ȣ���ϴ� ����� �ݺ��ȴ�. �׷��� �������� ���ڰ� �ϳ� ������ �����Ϸ��� void print(T arg, Types... args)�� �ƴ� void print(T arg)�� �����ϰ� �Ǵµ�,
	�̴� C++ ��Ģ ��, �Ķ���� ���� ���� �Լ��� �켱������ ���� �����̴�. ���п� print(T arg)�Լ��� ����Ǿ� endl�� ��µǸ� �ٹٲ��� �Ǿ���.
4.	���⼭ ����ִ� ����, �� print�Լ��� ��ġ�� �ٲٸ� ������ ������ �߻��Ѵ�. 
	������ C++�����Ϸ��� �Լ��� ������ �ÿ�, �ڽ��� �տ� ���ǵǾ� �ִ� �Լ��� �ۿ� ���� ���ϱ� �����ε�, �̴� �����ϻ󿡼� void print(T arg, Types...args)�Լ��� ���� �� �Ʒ��� void print(T arg)�Լ���
	���縦 �𸥴ٴ� ���̴�. �̴� void print(T arg, Types... args)�Լ����� ������ print("abc")�� �����ε��� ã�� �� �ٽ� �Ķ���� ���� �ִ� �ڱ��ڽ��� ã�� �Ǵµ�, �� �Լ� �ȿ��� �ٽ� print()�� ȣ���� �ȴ�. �̶� print�Լ��� ����ִ����� ���� ã�� ���ϱ⿡ ������ ��Ÿ���� �ȴ�. 
5.	���� ���ø� �Լ��� ����� ������ �� ������ �����Ͽ� ����ؾ� �Ѵ�.
 
[2.	������ ������ ���ڿ��� ��ġ�� �Լ�]
1.	std::string���� ���ڿ��� ��ġ�� ���ؼ��� concat=s1+s2+s3�� ���� �ߴµ�, ���� ��� concat=s1.operator+(s2).operator+(s3)�� ���� ���̴�.
	������ s2�� ���� �� �޸� �Ҵ��� �߻��ϰ�, s3�� ���� �� �޸� �Ҵ��� �� �ѹ� �߻��ϱ⿡ �ð������� ��ȿ�����̴�. (�޸� �Ҵ�/������ �ſ� ���� �۾� �߿� �ϳ��̴�.)
2.	�׷��� ������ ���ڿ��� ũ��� �̸� �� �� �����ϱ� �ѹ��� �ʿ��� ��ŭ �޸𸮸� �Ҵ��ϴ� ���� �߿��ϱ⿡ 
	std::string concat;
	concat.reserve(s1.size()+s2.size()+s3.size());
	concat.append(s1);
	concat.append(s2);
	concat.append(s2);
	���� �ذ��� �� �ִ�. Ȥ��
	std::string concat=StrCat(s1, "abc", s2, s3);�� ���� ����ϰ� ���ʿ��� �޸� �Ҵ� ���� �ذ��� �� �ִ�.
3.	������ ���⿡�� �߻��ϴ� �Ѱ����� StrCat�Լ��� ������ ������ ���ڸ� �޾ƾ� �Ѵٴ� ���ε�, ���⼭ ���� ���� ���ø��� ���ȴ�. 

[3.	sizeof...]
1.	sizeof �����ڴ� ������ ũ�⸦ ����������, �Ķ���� �ѿ� sizeof...�� ����� ���, ��ü ������ ������ �����ϰ� �ȴ�. 

[4.	Fold Expression]
1.	������ ���캻 ���� ���� ���ø��� �ſ� ��������, ��� �Լ� ���·� �����ؾߵǱ� ������, �ݵ�� ��� ȣ�� ���Ḧ ���� �Լ��� ���� ������ �Ѵٴ� ���� �����̴�.
	�̴� �ڵ��� ���⵵�� �������� �ø��� �ȴ�.
2.	������ C++17�� ���� ���Ե� Fold ������ ����Ѵٸ� �̸� �ξ� ���� �����ϰ� ǥ���� �� �ִ�. 
3.	return (...+nums)�� �ٷ� Fold ��������, ���� �ڵ��� ���´� ���� ���� Fold(Unary left fold)�̶�� �θ���. C++17���� �����ϴ� Fold�� ������δ�
	(E op ...)     ���� ���� Fold     (E1 op(...op(En-1 op En))) 
	(... op E)     ���� ���� Fold     (((E1 op E2) op ...) op EN)
	(E op ... op I)���� ���� Fold     (E1 op (... op (En-1 op (En op I))))
	(I op ... op E)���� ���� Fold     ((((I op E1) op E2) op ...) op EN 
	���⼭ op�� ��κ��� ���� �����ڵ�(+, -, <, <<, ->, ,, etc...)�� ���Եȴ�. 
4.	�߿��� ���� Fold���� �� �� �� ()�� ������� �Ѵ�. return (...+nums)�� return ...+nums;�� �ϸ� ����!! ���ʿ� ���� ǥ�� () ��ü�� Fold �Ŀ� ���ԵǾ� ���� 
5.	�Ѱ��� �� ����ִ� ���� ,�����ڸ� ����ϸ� ������ ���ڵ鿡 ���� ���ϴ� ���� ������ �� �ִ�. 
*/
