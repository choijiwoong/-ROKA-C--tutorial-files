#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <initializer_list>

/*0 compiler decode everything (seems like definition of function) to definition of function
class A{
	public:
		A() { std::cout<<"Call A's constructor"<<std::endl; }
};

int main(){
	A a();//no print! because compiler think it definition of function
}*/

/*0 how about this?
class A{
	public:
		A() { std::cout<<"Call A's Constructor!"<<std::endl; }
};
class B{
	public:
		B(A a){ std::cout<<"Call B's Constructor!"<<std::endl; }
};

int main(){
	B b(A());//no print too! because compiler think it definition of function(that return B and get A() as argument)
}*/

/*1 another way using {} 
class A{
	public:
		A(int x, double y) { std::cout<<"Call A's Constructor!"<<std::endl; }
};
A func(){
	return {1, 2.3};//it's same to A(1, 2.3) compiler guess return type itself
}
int main(){
	//A a(3.5);//Narrow-conversion is possible
	//A b{3.5};//Narrow-conversion is impossible
	
	func();
}*/

/*2 initializer list
class A{
	public:
		A(std::initializer_list<int> l){
			for(auto itr=l.begin(); itr!=l.end(); ++itr)
				std::cout<<*itr<<std::endl;
		}
};
int main(){ A a={1,2,3,4,5}; }//if we use (), initializer_list is not created.
*/

/*2 simple definition of container by using initializer_list
template <typename T>
void print_vec(const std::vector<T>& vec){
	std::cout<<"[";
	for(const auto& e: vec)
		std::cout<<e<<" ";
	std::cout<<"]"<<std::endl;
}

template<typename K, typename V>
void print_map(const std::map<K, V>& m){
	for(const auto& kv: m)
		std::cout<<kv.first<<" : "<<kv.second<<std::endl;
}

int main(){
	std::vector<int> v={1,2,3,4,5};
	print_vec(v);
	
	std::cout<<"------------------------"<<std::endl;
	std::map<std::string, int> m={ {"abc", 1}, {"hi", 3}, {"hello", 5}, {"c++", 2}, {"java", 6} };
	print_map(m);
}*/

/*3 compiler think initializer_list first. 
class A{
	public:
		A(int x, double y) { std::cout<<"Common Constructor! "<<std::endl; }
		A(std::initializer_list<int> lst){ std::cout<<"Constructor using initializer!"<<std::endl; }
};
int main(){
	A a(3, 1.5);//Good
	A b{3, 1.5};//Bad
	//Compiler takes effort for using initializer_list. So although narrowing conversion is occur, it takes initializer constructor not common constructor!
}*/

/*3 example compiler can't convert argument implicitly for calling initializer_list constructor
class A{
	public:
		A(int x, double y){ std::cout<<"common constructor!"<<std::endl; }
		A(std::initializer_list<std::string> lst){ std::cout<<"constructor using initializer_list!"<<std::endl;}
};
int main(){
	A a(3, 1.5);//common
	A b{3, 1.5};//common. because int or double can't convert to std::string implicitly.
	A c{"abc", "def"};//initializer_list
}*/

//4
int main(){
	auto list={1,2,3};//it creates initializer_list(when we auto with {})
	
	//In C++11
	auto a={1};//std::initializer_list<int>
	auto b{1};//std::initializer_list<int>
	auto c={1,2};//std::initializer_list<int>
	auto d{1,2};//std::initializer_list<int>
	
	//In C++17
	auto a_={1};//std::initializer_list<int>
	auto b_{1};//int
	auto c_={1,2};//std::initializer_list<int>
	auto d_{1,2};//compile error
}


/*
[0.	���� ����]
1.	C++11���� �߰��� ������ �ʱ�ȭ(Uniform Initialization)�� ���� �˾ƺ� ���̴�. 
2.	���� �ڵ�� A�� �����ϴ� �Լ� a()�� ������ ������ �����Ϸ��� �����Ѵ�. 
3.	�̷��� ������ ()�� �Լ��� ���ڵ��� �����ϴµ��� ���ǰ�, �Ϲ����� ��ü�� �����ڸ� ȣ���ϴµ����� ���Ǳ� �����̴�.
	��� C++11������ �̷��� ������ �ذ��ϱ� ���� ������ �ʱ�ȭ(Uniform Initialization)�� �����Ͽ���.
	
[1.	������ �ʱ�ȭ(Uniform Initialization)
1.	�����ڸ� ȣ���ϱ� ���� ()�� ����ϴ� ��ſ� {}�� ����ϸ� ���̴�. 
	��� �����ؾ��ϴ� ����, {}�� �̿��� ������ �Ϻ� �Ͻ��� Ÿ�� ��ȯ���� �����ϰ� �ִ�. �׷��� ���� ���� ������ �ս��� �ִ�(Narrowing) ��ȯ�̴�.
2.	������ ����,,, {}�� ����Ͽ� ������ �ʴ� Ÿ�� ĳ������ �����Ͽ� ������ �̿��� ��Ƴ� �� �ִ�.
	���� {}�� ����ϸ� �Լ� ���Ͻÿ� ���� �����ϴ� ��ü�� Ÿ���� �ٽ� ������� �ʾƵ� �ȴ�. 
	
[2.	�ʱ�ȭ�� ����Ʈ(Initializer list)]
1.	C++11���� �迭�� ������ �� int arr[]={1,2,3,4};�ߴ��Ͱ� ���� vector<int> v={1,2,3,4};�� ����������. 
2.	initializer_list�� �̿��Ͽ� �����̳ʵ��� �����ϰ� ������ �� �ִ�.

[3.	initializer_list��� �� ������ ��]
1.	�����ڵ� �߿��� initializer_list�� �޴� �����ڰ� �ִٸ�, {}�� ����Ͽ� ��ü�� ������ ���, ������ �����ε� �ÿ� �ش� �Լ��� ���߼����� ����ȴٴ� ���� �����ؾ� �Ѵ�.
	���� vector(size_type count);�� �����ڸ��� reserve�ϴ°��� �ִµ�, vector v{10};���� �Ҷ� �׳� ���� 1��¥�� initializer_list�� �����Ͽ� 10�� �����ϴ� ���͸� �����Ѵ�. ��� �׳� ()�� �̿��Ͽ� 
	vector v{10};�����ϸ� �츮�� ���ϴ� �����ڸ� ȣ���� �� �ִ�. 
2.	�ݴ�� �����ϸ� �����Ϸ��� �ּ��� ���ؼ� �ش� �����ڿ� ��Ī��Ű���� ����Ѵٴ� �ǹ��̴�. ��, ������ �ս��� ������ {}�� initializer_list�� �޴� �����ڸ� ȣ���Ѵ�. 
	{}�� ������ �ս��� �ִ� ��ȯ�� �� �� ������, C++�����Ϸ��� initializer_list�� �̿��� �����ڸ� �ִ��� ����ϱ⿡ Ÿ�Ժ�ȯ�� �ȴ�. �̷��� ������ ���� ���ؼ���
	�ƿ� initializer_list�� ����Ÿ������ Ÿ�� ��ȯ ��ü�� �Ұ����Ͽ� ()�� ȣ��Ǵ� ����̴�.
	
[4.	initializer_list�� auto]
1.	{}�� ������ �� Ÿ���� auto�� initializer_list��ü�� �����ȴ�. 
2.	C++17���� {}�� auto�� Ÿ���� �Ʒ��� ��Ģ�� ���� �߷еȴ�.
	-auto x={arg1, arg2...}���� arg���� ���� Ÿ���̸� x�� std::initializer_list<T>�� �߷�
	-auto x{arg1, arg2...}���� ���ڰ� 1���� ������ Ÿ������ �߷��ϰ�, �������� ���� �߻�. 
3.	������ �ʱ�ȭ�� auto�� ���� ����� �� �� ������ ����, ���ڿ��� �ٷ� ��
	auto list={"a", "b", "cc"};�� �ϰԵǸ� initializer_list<std::string>�� �ƴ� initializer_list<const char*>�� �ȴ�. 
	 �� ������ C++14�� �߰��� ���ͷ� �����ڷ� �ذᰡ���ѵ�,
	using namespace std::literals;
	auto list={"a"s, "b"s, "c"s};�� ���� ���ͷ� �����ڷ� Ÿ���� ������ָ� �ȴ�. 

[5.	�������ϸ�]
1.	������ ����ȭ({}�� �̿��� ������ ȣ��)�� ���� ���� �����ڰ� �Լ��� ���Ƿ� �����Ϸ��� �Ǵ��ϴ� ������ ������, initializer_list�� ����� {}�� ���ڸ� ������ �� �ְ�, �̸� ���Ͽ� ��ü�� ������ �� �ִ�. 
*/
