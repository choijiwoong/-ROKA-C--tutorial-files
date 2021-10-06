#include <iostream>
#include <map>
#include <string>
#include <utility>


/*use of optional in map
std::optional<std::string> GetValueFromMap(const std::map<int, std::string>& m, int key){
	auto itr=m.find(key);
	if(itr!=m.end())
		return itr->second;
	
	return std::nullopt;//empty optional object
} 

int main(){
	std::map<int, std::string> data={{1,"hi"}, {2, "hello"}, {3, "hiroo"}};
	
	GetValueFromMap(data, 2).has_value(); //check. if it's nullopt, throw exception
	std::cout<<"value of 2: "<<GetValueFromMap(data, 2).value()<<std::endl;
}*/

/*optional doesn't have default object in empty state
class A{
	public:
		A(){std::cout<<"default constructor"<<std::endl;}
		A(const A& a){std::cout<<"copy constructor"<<std::endl;}
};

int main(){
	A a;
	
	std::cout<<"make optional object------"<<std::endl;
	std::optional<A> maybe_a;//empty state!
	std::cout<<"default construct is not need because maybe_a doesn't have A object."<<std::endl;
	maybe_a=a;
}*/

#include <variant>
#include <memory>
/*solution of this situation by using variant object as return
class A{
	public:
		void a(){std::cout<<"I am A"<<std::endl;}
};

class B{
	public:
		void b(){ std::cout<<"I am B"<<std::endl; }
};

std::variant<A, B> GetDataFromDB(bool is_a){
	if(is_a)
		return A();
	return B();
}

int main(){
	auto v=GetDataFromDB(true);
	
	std::cout<<v.index()<<std::endl;//type index
	std::get<A>(v).a();//==std::get<0>(v).a();
}*/

#include <tuple>
//tuple(set with different types) with structured binding 
std::tuple<int, std::string, bool> GetStudent(int id){
	if(id==0)
		return std::make_tuple(30, "john", true);
	else
		return std::make_tuple(28, "mary", false);
}

int main(){
	auto student=GetStudent(1);
	auto [age, name, is_male]=student;//structured binding!
	
	std::cout<<"name: "<<name<<std::endl;
	std::cout<<"age: "<<age<<std::endl;
	std::cout<<"is male?: "<<std::boolalpha<<is_male<<std::endl;
}

/*
1.	map에 주어진 키에 대응되는 값이 있는지 확인하는 함수를 짤때, 단순하게 짜면 대응되는 값이 없다면 std::string();을 리턴하는 방식으로 만들 수 있다.
	하지만, 만약 정말로 대응되는 값이 빈 string이라면 대응되는 값이 없는 것과 대응되는 값이 빈 string인 것을 제대로 구분할 수 없다. 
	고로 우리는 make_pair을 리턴하여 대응되는 값이 있다면 true를 추가로, 없다면 false를 추가로 리턴하여 위의 두가지 경우를 구분할 수 있다.
	 하지만 맵에 키가 존재하지 않을 때 디폴트 객체를 리턴해야 하는데, 객체의 디폴트 생성자가 정의되어 있지 않을 수도 있고, 이러한 생성이 오래걸릴 수도 있다.
	고로 우리는 원하는 값을 보관할 수도, 안할 수도 있는 std::optional객체를 도입한다.
2.	optional의 장점은 동적 할당이 발생하지 않는데, 값을 알고 싶다면 .value()함수를 호출하면 된다.
	만약 가지고있는 객체가 없는 nullopt면 std::bad_optional_access예외를 덩지게 된다. 고로 실제로 값을 가지고 있는지를 확인해야 하는데,
	이는 .has_value()를 사용한다. 
3.	optional과 pair의 가장큰 차이점은 optional은 아무것도 들고 있지 않은 상태에서 디폴트 객체를 가지지 않는다는 것이다.
4.	optional의 단점은 일반적인 방법 std::optional<A&> maybe_a=a;로는 레퍼런스를 포함할 수 없다. 고로 레퍼런스를 optional을 이용하여 사용하고 싶다면
	std::reference_weapper<A>를 사용하여 레퍼런스처럼 동작하는 wrapper객체를 정의하여 사용한다.
	std::optional<std::reference_wrapper<A>> maybe_a=std::ref(a);
	maybe_a->get().data=3; 
	
5.	이러이러한 타입등 중 하나(one-of)를 표현하기 위해 variant객체를 사용할 수 있다.
	std::variant<int, std::string, double> v=1;//v는 int
	variant는 아무것도 정의하지 않으면 가장 첫 번째 인자로 디폴트 생성자가 호출되기에 비어있는 variant객체는 불가능하다.
	 variant는 객체 대입 시에 동적할당이 발생하지 않기에 one-of를 표현하기 가장 적절하다.
6.	DB와 같이 들어온 타입에 따라 리턴타입이 바뀌는 경우 그 전까지 클래스 관계에서 C++의 다형성(polymorphism)을 사용하여 
	리턴타입을 std::unique_ptr<Data>, 리턴을 std::make_unique<A>();와 같이 했어야 하지만 이는 클래스들의 부모 클래스가 공통으로 정외되어야 하고, 표준 클래스의 객체에는 적용할 수 없다는 문제가 있었다.
	 이를 variant로 해결할 수 있다.
7.	variant에 같은 타입을 여러번 써주면 컴파일 오류가 발생하게 된다.
8.	std::monostatr로 variant에 아무것도 없는 상태를 표현할 수 있다. like optional
	std::variant<std::monostate, A, B> v;
	이는 클래스 타입을 넣으려 하는데, 그 클래스에 defualt constructor가 없는 경우에 에러가 발생하는 것을 막아준다. 
	class A {
 	public:
  	A(int i) {}
	};
	
	class B {
 	public:
  	B(int i) {}
	};
	
	std::variant<std::monostate, A, B> v;
9.	std::tuple객체를 리턴하는 함수에 대해 각 항목을 받으려면 auto로 해당 객체를 받아 각 항목을 변수에 저장했어야 하는데,	
	C++17부터 Structured binding이라는 테크닉을 이용하여 보다 쉽게 tuple의 값들을 받을 수 있다. 다만 반드시 모든 원소들을 받아야 한다. 
	structured binding은 tuple외에도 pair이나 구조체의 데이터 필드들을 받는데도 사용할 수 있다. 
*/
