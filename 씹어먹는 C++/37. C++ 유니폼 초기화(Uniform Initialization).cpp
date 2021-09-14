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

[3.	initializer_list사용 시 주의할 점]
1.	생성자들 중에서 initializer_list를 받는 생성자가 있다면, {}을 사용하여 객체를 생성할 경우, 생성자 오버로딩 시에 해당 함수가 최추선으로 고려된다는 점을 주의해야 한다.
	예로 vector(size_type count);로 원소자리를 reserve하는것이 있는데, vector v{10};으로 할때 그냥 원소 1개짜리 initializer_list라 생각하여 10을 보관하는 벡터를 생성한다. 고로 그냥 ()를 이용하여 
	vector v{10};생성하면 우리가 원하는 생성자를 호출할 수 있다. 
2.	반대로 생각하면 컴파일러가 최선을 다해서 해당 생성자와 매칭시키려고 노력한다는 의미이다. 즉, 데이터 손실이 나더라도 {}는 initializer_list를 받는 생성자를 호출한다. 
	{}는 데이터 손실이 있는 변환을 할 수 없지만, C++컴파일런느 initializer_list를 이용한 생성자를 최대한 고려하기에 타입변환이 된다. 이러한 문제를 막기 위해서는
	아예 initializer_list의 원소타입으로 타입 변환 자체가 불가능하여 ()가 호출되는 경우이다.
	
[4.	initializer_list와 auto]
1.	{}로 생성할 때 타입이 auto면 initializer_list객체가 생성된다. 
2.	C++17부터 {}시 auto의 타입이 아래의 규칙과 같이 추론된다.
	-auto x={arg1, arg2...}에서 arg들이 같은 타입이면 x는 std::initializer_list<T>로 추론
	-auto x{arg1, arg2...}에서 인자가 1개면 인자의 타입으로 추론하고, 여러개면 오류 발생. 
3.	유니폼 초기화와 auto를 같이 사용할 때 또 주의할 점은, 문자열을 다룰 때
	auto list={"a", "b", "cc"};를 하게되면 initializer_list<std::string>이 아닌 initializer_list<const char*>이 된다. 
	 이 문제는 C++14에 추가된 리터럴 연산자로 해결가능한데,
	using namespace std::literals;
	auto list={"a"s, "b"s, "c"s};와 같이 리터럴 연산자로 타입을 명시해주면 된다. 

[5.	마무리하며]
1.	유니폼 포기화({}를 이용한 생성자 호출)로 인자 없는 생성자가 함수의 정의로 컴파일러가 판단하는 오류를 막으며, initializer_list를 만들어 {}로 인자를 전달할 수 있고, 이를 통하여 객체를 생성할 수 있다. 
*/
