#include <iostream>
#include <string>
#include <map>
#include <vector>

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

//2 simple definition of container by using initializer_list
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
		std::cout<<"kv.first"<<" : "<<kv.second<<std::endl;
}

int main(){
	std::vector<int> v={1,2,3,4,5};
	print_vec(v);
	
	std::cout<<"------------------------"<<std::endl;
	std::map<std::string, int> m={ {"abc", 1}, {"hi", 3}, {"hello", 5}, {"c++", 2}, {"java", 6} };
	print_map(m);
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
 
*/
