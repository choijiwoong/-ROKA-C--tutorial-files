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
[1.	std::optional(C++17 �̻�-<optional>)]
1.	��� map���� �־��� Ű�� �����ϴ� ���� ���θ� Ȯ���ϴ� �Լ� 
2.	std::pair�� �̿��Ͽ� ���� �ʿ� �����ϴ��� ���θ� ���� �����ϸ� �������� ���� ����°�
	��ü�� ����Ʈ �����ڰ� ���ǵǾ� ���� ���� ���� �ְ�, ��ü�� ����Ʈ �����ϴ°� �ſ� ���� �ɸ� ���� �ִ�.
3.	�̶� std::optional�� ���Եȴ�. 
	���ø� ���ڷ� �����ϰ��� �ϴ� ��ü�� Ÿ���� ����. optional�� ��ü������������ �����Ҵ��� ����. �� ���ʿ��� ������尡 ����. optional��ü�� ��ü�� ���ԵǾ� �ִٰ� ����
	optional��ü�� ������ �ִ� ��ü�� �����Ϸ��� value()�Լ��� ���� �Ǵµ�, �̶� ��ü�� ���ٸ� std::bad_optional_access���ܸ� �����Ƿ� ���� ���� ������ ���� Ȯ���ؾ� �Ѵ�. 
	�̴� has_value�Լ��� �̿��ϸ� �ȴ�. 
	(p.s optional��ü�� bool��ȯ ĳ���ÿ����ڰ� �־ if(GetValueFromMap(data, 4))�� if(GetValueFromMap(data,4).has_value())�� �����ϴ�. ���� .value�� ������(*)�� �����ϴ�. 
	 std::optional<T>�� std::pair<bool, T>�� ���� ū �������� �ƹ��͵� ������� ���� ���¿��� default object�� ���� �ʿ䰡 ���ٴ� ���̴�.
	 Ȯ���غ���.
4.	���۷����� ������ std::optional
	std::optional�� �Ѱ��� �������� �Ϲ����� ������� ���۷����� ������ �� ����	 
	������ �׷��ٰ� �ƿ� �� �� ���°� �ƴѵ�, std::reference_wrapper�� ����Ͽ� ���۷���ó�� �����ϴ� wrapper��ü�� �����ϸ� �ȴ�. 
	 std::reference_wrapper�� ���۷������ƴ� �Ϲ� ��ü�̱⿡ optional�� ������ �� �ְ�, get�� ���� ���۷����ϰ��ִ� ��ü�� ������ �ȴ�. �ٸ� �̸� ����ϱ� ���� std::ref�� ����ؾ� �Ѵ�.
	optional�� �����������ڿ����ε����� *�ε� �˾Ƴ� �� ������, get()�� ���ؼ��� ������ ���ִ�.
	
[2.	std::variant(C++ 17�̻�-<variant>)]
1.	�̴� one-of�� ������ Ŭ�����̴�. ��, ������ Ÿ�ӿ� ������ �������� Ÿ�Ե� �߿� �� ���� Ÿ���� ��ü�� ������ �� �ִ� Ŭ�����̴�.
	����ü(union)�� ����� �� ������, �̴� ���� � Ÿ���� ��ü�� �����ϴ��� �𸣱⿡ ������ ����ϱ⿣ �δ��� ������. 
2.	����ִ� variant�� �Ұ����ϴ�. variant�� optional�� ����ϰ� ���� �� �����Ҵ��� ������ �ȱ⿡ ������ ���� �������� ��ü���� ������ �� �ִ�.
	�ٸ� variant��ü�� ũ��� ������ Ÿ�� �� ���� ū ũ�⸦ ���󰣴�.
	 variant�� �̷��̷��� Ÿ�Ե��� �ϳ�(one-of)�� ǥ���ϱ⿡ �����ϴ�. DB�� �˻��ؼ� ����� �����ִ� �Լ��� �����غ���. 
	������(polymorphism)�� ����ϸ� ����������, �����ϰ��� �ϴ� Ŭ�������� �θ� Ŭ������ ���ܵǾ��־���ϰ�, ǥ�� Ŭ������ ��ü�鿡�� ������ �� ���ٴ� ������ �ִ�.(int, std::string...)
	 �̸� variant�� ����Ͽ� �ذ�����. 
	�ٸ� variant�� �����ϴ� ��ü���� Ÿ������ ���еǱ⿡ ���� Ÿ���� std::variant<std::string, std::string> v;ó�� ���� �����Ͽ����� �߻��Ѵ�.
3.	���� variant�� empty���¸� ǥ���ϰ������ Ÿ�Կ� std::monostate�� ����ϸ� �ȴ�. �̴� std::optional�� ���� ȿ���� �� �� �ִ�. 
	std::variant<std::monostatus, A, B> v;�� ���ų� A�ų� B�ų���. �̴� variant�ȿ� ���ǵ� Ÿ���� default constructor�� ������ ��밡��.

[3.	std::tuple(C++11�̻�-<tuple>)]
1.	���� ���� �ٸ� Ÿ�Ե��� ������ �����ϰ� �ٷ� �� �ְ����ش�. C++���� ���� Ÿ�� ��ü���� �ٷ� �� std::vector�� �迭�� �̿�������, ���� �ٸ� Ÿ���� ��ü���� ������ �ٷ�� ���� ��ġ������.
	struct Collection{
		int a;
		std::string s;
		double d;
	}�� ���� �ؾ��ߴ�. �̴� ���̽��� (1, 'abc', 3.14)�� �ٸ��� �ſ� �����ϴ�.
	 �׷��� �߰��ع������� ���������
2.	tuple���� ���� Ÿ���� ����־ ������� make_tuple�� �̿��Ͽ� �����. ���� ���������� std::get<std::string>�� index�� ������ �ȴ�.(���� std::string���ų� 2���̻��̸� ����) 
3.	Structured binding(C++17�̻�)
	C++17���� structured binding�̶�� ��ũ������ tuple�� �� ���ϰ� �ٷ� �� �ִ�. 
	auto [age, name, is_male]=student; ���̽� ������ �����ε�
	auto(&or && ����) [���ҹ���]=tp;�� �ϸ� �ȴ�. ���� ���縻�� ���۷����� ���ϰ������ auto&�ϸ� �ȴ�.
	 ��� �߿��� ���� ��� ���ҵ��� �ݵ�� �޾ƾ� �Ѵٴ� ���̴�. structured binding�� ����ϸ� �߰��� ���Ҹ� ���� �޴°��� �Ұ����ϴ�.
4.	structured binding�� ���� ���Ǵµ�, tuple���� ������ ������� ���ǵ� ����ü�� ������ �ʵ带 ���� ���� �Ʒ��� ���� ����� �����ϴ�.
	struct Data{
		int i;
		std::string s;
		bool b;
	}
	Data d;
	auto [i, s, b]=d;
	 �ʿ��� ����� �����ѵ�(Ŭ������ �� �Ǵ�) ������ iterator�� first, second�� ǥ���ϴ��� structured binding���� ����ϰ� ��Ÿ�� �� �ִ�. 

[4.	�������ϸ�]
1.	optional�� ���ϴ� �����͸� �����ų� ������ �ʴ� ��ü ������ �����ϴ�.
	variant�� ���� Ÿ�� �� �ϳ��� ������ ��ü ������ �����ϴ�.
	tuple�� ���� ���� ���� �ٸ� Ÿ���� ���� ��ü ������ �����ϴ�. 
*/
