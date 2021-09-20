#include <iostream>
#include <map>
#include <string>
/*1 function that checks if matched valued of key exist in map 
std::string GetValueFromMap(const std::map<int, std::string>& m, int key){
	auto itr=m.find(key);
	
	if(itr!=m.end())
		return itr->second;
		
	return std::string();//if real matched value is empty string? map cannot distinguish case1(key is not in map), case2(matched value is empty string) 
}

int main(){
	std::map<int, std::string> data={{1, "hi"}, {2, "hello"}, {3, "hiroo"}};
	std::cout<<"matched value to 2 in map: "<<GetValueFromMap(data,2)<<std::endl;
	std::cout<<"matched value to 4 in map: "<<GetValueFromMap(data,4)<<std::endl;
}*/

/*1 first try for solving these problem by pair.
std::pair<std::string, bool> GetValueFromMap(const std::map<int, std::string>& m, int key){//pair object has first, second
		auto itr=m.find(key);
		if(itr!=m.end())
			return std::make_pair(itr->second, true);//pair.first to itr->second, pair.second to true
		
		return std::make_pair(std::string(), false);
	}//pass whether or not it exists in the real map with value
}
int main(){
	std::map<int, std::string> data={{1, "hi"}, {2, "hello"}, {3, "hiroo"}};
	std::cout<<"matched value to 2: "<<GetValueFromMap(data,2).first<<std::endl;
	std::cout<<"Is exist 4 in map? "<<std::boolalpha<<GetValueFromMap(data, 4).second<<std::endl;
	//we have to return empty std::pair if value is not in map..that object's default constructor,,,creating default creating,,, problems!
}*/

#include <utility>
/*1 std::optional
std::optional<std::string> GetValueFromMap(const std::map<int, std::string>* m, int key){
	auto itr=m.find(key);
	if(itr!=m.end())
		return itr->second;//automatically compiler makes it optional object because we allow type we will save to std::optional by template argument 
	return std::nullopt;//empty optional object
}
int main(){
	std::map<int, std::string> data={{1, "hi"}, {2, "hello"}, {3, "hiroo"}};
	std::cout<<"matched value to 2: "<<GetValueFromMap(data, 2).value()<<std::endl;
	std::cout<<"Is 4 in map: "<<std::boolalpha<<GetValueFromMap(data, 4).has_value()<<std::endl;
}*/

/*1 Let's see std::optional<T> doesn't have to get default object in empty state
class A{
	public:
		A(){ std::cout<<"default create"<<std::endl; }
		A(const A& a){ std::cout<<"copy create"<<std::endl; }
};
int main(){
	A a;
	
	std::cout<<"make optional object ----"<<std::endl;
	std::optional<A> maybe_a;
	
	std::cout<<"maybe_a doesn't need to create default because it doesn't contain object A"<<std::endl;
	maybe_a=a;//don't print message "default create"
	//So we can pass mean that save some object or not by std::optional
}*/

/*1 std::optional that has reference
class A{
	public:
		A(){ std::cout<<"default create"<<std::endl; }
		A(const A& a){ std::cout<<"copy create"<<std::endl; }
};
int main(){
	A a;
	std::optional<A&> maybe_a=a;//fucking compile error.
}*/

#include <functional>
/*1 std::optional that has reference by std::reference_wrapper
class A{
	public:
		int data;
};
int main(){
	A a;
	a.data=d;
	
	//maybe_a save a's reference not copy of a
	std::optional<std::reference_wrapper<A>> maybe_a=std::ref(a);
	
	maybe_a->get().data=3;
	
	std::cout<<"a.data : "<<a.data<<std::endl;//value change!
}*/

/*2 simple example of std::variant
std::variant<int, std::string, double> v;//v is int now
v=1;//v is std::string int.
v="abc";//v is std::string now.
v=3.14;//v is double now.*/

/*2 example of return value after searching DB
class A{};
class B{};

?? GetDatFromDB(bool is_a){
	if(is_a)
		return A();
	return B();
} */

/*2 solution that use polumorphism of C++
class Data{};
class A: public Data{};
class B: public Data{};

std::unique_ptr<Data> GetDataFromDB(bool is_a){
	if(is_a)
		return std::make_unique<A>();//make A to Data by unique pointer
	return std::make_unique<B>();
}*/

/*2 solution with std::variant
class A{
	public:
		void a(){ std::cout<<"I am A"<<std::endl; }
};
class B{
	public:
		void b{ std::cout<<"I am B"<<std::endl; }
};
std::variant<A, B> GetDataFromDB(bool is_a){
	if(is_a)
		return A();
	return B();
}
int main(){
	auto v=GetDataFromDB(true);
	
	//way to extract value in variant
	std::cout<<v.index()<<std::endl;//it let us know what type is used in std::variant<A, B>.
	std::get<A>(v).a();//or std::get<0>(v).a() or std::get<v.index()>(v).a();
}*/

/*2 use variant with monostate for case that default constructor isn't exist.
class A{
	public:
		A(int i){}
};
class B{
	public:
		B(int i){}
};
int main(){
	//std::variant<A, B> v;//compile error! v try to set A as default type, but A doesn't have default constructor
	//So Let's add std::monostate like that
	std::variant<std::monostate, A, B> v;
}*/

#include <tuple> 
/*3 tuple
int main(){
	std::tuple<int, double, std::string> tp;
	tp=std::make_tuple(1, 3.14, "hi");
	
	std::cout<<std::get<0>(tp)<<", "<<std::get<1>(tp)<<", "<<std::get<2>(tp)<<std::endl;
}*/

/*3 little unconvenience.
std::tuple<int, std::string, bool> GetStudent(int id){
	if(id==0)
		return std::make_tuple(30, "James", true);
	else
		return std::make_tuple(28, "Sandy", false);
}
int main(){
	auto student=GetStudent(1);
	
	int age=std::get<0>(student);//little long code.
	std::string name=std::get<1>(student);
	bool is_male=std::get<2>(student);
	
	std::cout<<"name: "<<name<<std::endl;
	std::cout<<"age : "<<age<<std::endl;
	std::cout<<"male? "<<std::boolalpha<<is_male<<std::endl;
}*/

/*3 need of structured binding
std::tuple<int, std::string, bool> GetStudent(int id){
	if(id==0)
		return std::make_tuple(30, "James", true);
	return std::make_tuple(28, "Sandy", false);
}
int main(){
	auto student=GetStudent(1);
	auto [age, name, is_male]=student;
	
	std::cout<<"name: "<<name<<std::endl;
	std::cout<<"age : "<<age<<std::endl;
	std::cout<<"male? "<<std::boolalpha<<is_male<<std::endl;
}*/

//3 structued binding is also used in class like pair, too
int main(){
	std::map<int, std::string> m={{3, "hi"}, {5,"hello"}};
	
	for(auto& [key, val]: m)
		std::cout<<"Key: "<<key<<" value: "<<val<<std::endl;
}



/*
[1.	std::optional(C++17 이상-<optional>)]
1.	어떠한 map에서 주어진 키에 대응하는 값의 여부를 확인하는 함수 
2.	std::pair을 이용하여 실제 맵에 존재하는지 여부를 같이 전달하면 문제점이 새로 생기는게
	객체의 디폴트 생성자가 정의되어 있지 않을 수도 있고, 객체를 디폴트 생성하는게 매우 오래 걸릴 수도 있다.
3.	이때 std::optional이 도입된다. 
	템플릿 인자로 보관하고자 하는 객체의 타입을 쓰자. optional은 객체보관과정에서 동적할당이 없다. 즉 불필요한 오버헤드가 없다. optional자체에 객체가 포함되어 있다고 보자
	optional객체가 가지고 있는 객체에 접근하려면 value()함수를 쓰면 되는데, 이때 객체가 없다며 std::bad_optional_access예외를 던지므로 실제 값의 유무를 먼저 확인해야 한다. 
	이는 has_value함수를 이용하면 된다. 
	(p.s optional자체에 bool변환 캐스팅연산자가 있어서 if(GetValueFromMap(data, 4))나 if(GetValueFromMap(data,4).has_value())가 동일하다. 또한 .value와 역참조(*)도 동일하다. 
	 std::optional<T>가 std::pair<bool, T>의 가장 큰 차이점은 아무것도 들고있지 않은 상태에서 default object를 가질 필요가 없다는 것이다.
	 확인해보자.
4.	레퍼런스를 가지는 std::optional
	std::optional의 한가지 단점으로 일반적인 방법으로 레퍼런스를 포함할 수 없다	 
	하지만 그렇다고 아예 할 수 없는건 아닌데, std::reference_wrapper를 사용하여 레퍼런스처럼 동작하는 wrapper객체를 정의하면 된다. 
	 std::reference_wrapper는 레퍼런스가아닌 일반 객체이기에 optional에 전달할 수 있고, get을 통해 레퍼런스하고있는 객체를 얻어오게 된다. 다만 이를 사용하기 위해 std::ref를 사용해야 한다.
	optional에 역참조연산자오버로딩덕에 *로도 알아낼 수 있지만, get()을 통해서도 가져올 수있다.
	
[2.	std::variant(C++ 17이상-<variant>)]
1.	이는 one-of를 구현한 클래스이다. 즉, 컴파일 타임에 정해진 여러가지 타입들 중에 한 가지 타입의 객체를 보관할 수 있는 클래스이다.
	공용체(union)을 사용할 수 있지만, 이는 현재 어떤 타입의 객체를 보관하는지 모르기에 실제로 사용하기엔 부담이 따른다. 
2.	비어있는 variant는 불가능하다. variant는 optional과 비슷하게 대입 시 동적할당이 생기지 안기에 굉장히 작은 오버헤드로 객체들을 보관할 수 있다.
	다만 variant객체의 크기는 가능한 타입 중 가장 큰 크기를 따라간다.
	 variant는 이러이러한 타입들중 하나(one-of)를 표현하기에 적합하다. DB에 검색해서 결과를 돌려주는 함수를 생각해보자. 
	다형성(polymorphism)을 사용하면 가능하지만, 리턴하고자 하는 클래스들의 부모 클래스가 정외되어있어야하고, 표준 클래스의 객체들에는 적용할 수 없다는 문제가 있다.(int, std::string...)
	 이를 variant를 사용하여 해결하자. 
	다만 variant가 보관하는 객체들은 타입으로 구분되기에 같은 타입을 std::variant<std::string, std::string> v;처럼 쓰면 컴파일오류가 발생한다.
3.	굳이 variant에 empty상태를 표현하고싶으면 타입에 std::monostate를 사용하면 된다. 이는 std::optional과 같은 효과를 낼 수 있다. 
	std::variant<std::monostatus, A, B> v;는 없거나 A거나 B거나임. 이는 variant안에 정의된 타입중 default constructor가 없을때 사용가능.

[3.	std::tuple(C++11이상-<tuple>)]
1.	여러 서로 다른 타입들의 묶음을 간단하게 다룰 수 있게해준다. C++에서 같은 타입 객체들을 다룰 땐 std::vector나 배열을 이용했지만, 서로 다른 타입의 객체들을 여러개 다루는 것을 골치아프다.
	struct Collection{
		int a;
		std::string s;
		double d;
	}와 같이 해야했다. 이는 파이썬의 (1, 'abc', 3.14)와 다르게 매우 불편하다.
	 그래서 추가해버렸지롱 쿠쿠루쿠쿠
2.	tuple에는 같은 타입이 들어있어도 상관없고 make_tuple을 이용하여 만든다. 또한 원소접근은 std::get<std::string>나 index를 넣으면 된다.(만약 std::string없거나 2개이상이면 예외) 
3.	Structured binding(C++17이상)
	C++17에는 structured binding이라는 테크닉으로 tuple을 더 편리하게 다룰 수 있다. 
	auto [age, name, is_male]=student; 파이썬 감성의 문법인데
	auto(&or && 가능) [원소받이]=tp;로 하면 된다. 만약 복사말고 레퍼런스를 취하고싶으면 auto&하면 된다.
	 대신 중요한 점은 모든 원소들을 반드시 받아야 한다는 것이다. structured binding을 사용하면 중간의 원소를 빼고 받는것을 불가능하다.
4.	structured binding은 자주 사용되는데, tuple말고도 데이터 멤버들이 정의된 구조체의 데이터 필드를 받을 때도 아래와 같이 사용이 가능하다.
	struct Data{
		int i;
		std::string s;
		bool b;
	}
	Data d;
	auto [i, s, b]=d;
	 맵에도 사용이 가능한데(클래스는 다 되니) 기존에 iterator의 first, second로 표시하던걸 structured binding으로 깔끔하게 나타낼 수 있다. 

[4.	마무리하며]
1.	optional로 원하는 데이터를 가지거나 가지지 않는 객체 생성이 가능하다.
	variant로 여러 타입 중 하나를 가지는 객체 생성이 가능하다.
	tuple을 통해 여러 서로 다른 타입의 모임 객체 생성이 가능하다. 
*/
