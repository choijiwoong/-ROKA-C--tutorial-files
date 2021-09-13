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
[0.	들어가기 전에]
1.	C++11에서 추가된 균일한 초기화(Uniform Initialization)에 대해 알아볼 것이다. 
2.	위의 코드는 A를 리턴하는 함수 a()를 정의한 것으로 컴파일러는 생각한다. 
3.	이러한 문제는 ()가 함수의 인자들을 정의하는데도 사용되고, 일반적인 객체의 생성자를 호출하는데에도 사용되기 때문이다.
	고로 C++11에서는 이러한 문제를 해결하기 위해 균일한 초기화(Uniform Initialization)을 도입하였다.
	
[1.	균일한 초기화(Uniform Initialization)
1.	생성자를 호출하기 위해 ()를 사용하는 대신에 {}를 사용하면 끝이다. 
	대신 주의해야하는 점은, {}를 이용한 생성은 일부 암시적 타입 변환들을 불허하고 있다. 그러한 것은 전부 데이터 손실이 있는(Narrowing) 변환이다.
2.	오히려 좋아,,, {}를 사용하여 원하지 않는 타입 캐스팅을 방지하여 오류를 미연에 잡아낼 수 있다.
	또한 {}를 사용하면 함수 리턴시에 굳이 생성하는 객체의 타입을 다시 명시하지 않아도 된다. 
	
[2.	초기화자 리스트(Initializer list)]
1.	C++11에서 배열을 정의할 때 int arr[]={1,2,3,4};했던것과 같이 vector<int> v={1,2,3,4};가 가능해졌다. 
2.	initializer_list를 이용하여 컨테이너들을 간단하게 정의할 수 있다.
 
*/
