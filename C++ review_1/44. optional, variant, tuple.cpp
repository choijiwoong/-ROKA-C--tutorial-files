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
1.	map�� �־��� Ű�� �����Ǵ� ���� �ִ��� Ȯ���ϴ� �Լ��� ©��, �ܼ��ϰ� ¥�� �����Ǵ� ���� ���ٸ� std::string();�� �����ϴ� ������� ���� �� �ִ�.
	������, ���� ������ �����Ǵ� ���� �� string�̶�� �����Ǵ� ���� ���� �Ͱ� �����Ǵ� ���� �� string�� ���� ����� ������ �� ����. 
	��� �츮�� make_pair�� �����Ͽ� �����Ǵ� ���� �ִٸ� true�� �߰���, ���ٸ� false�� �߰��� �����Ͽ� ���� �ΰ��� ��츦 ������ �� �ִ�.
	 ������ �ʿ� Ű�� �������� ���� �� ����Ʈ ��ü�� �����ؾ� �ϴµ�, ��ü�� ����Ʈ �����ڰ� ���ǵǾ� ���� ���� ���� �ְ�, �̷��� ������ �����ɸ� ���� �ִ�.
	��� �츮�� ���ϴ� ���� ������ ����, ���� ���� �ִ� std::optional��ü�� �����Ѵ�.
2.	optional�� ������ ���� �Ҵ��� �߻����� �ʴµ�, ���� �˰� �ʹٸ� .value()�Լ��� ȣ���ϸ� �ȴ�.
	���� �������ִ� ��ü�� ���� nullopt�� std::bad_optional_access���ܸ� ������ �ȴ�. ��� ������ ���� ������ �ִ����� Ȯ���ؾ� �ϴµ�,
	�̴� .has_value()�� ����Ѵ�. 
3.	optional�� pair�� ����ū �������� optional�� �ƹ��͵� ��� ���� ���� ���¿��� ����Ʈ ��ü�� ������ �ʴ´ٴ� ���̴�.
4.	optional�� ������ �Ϲ����� ��� std::optional<A&> maybe_a=a;�δ� ���۷����� ������ �� ����. ��� ���۷����� optional�� �̿��Ͽ� ����ϰ� �ʹٸ�
	std::reference_weapper<A>�� ����Ͽ� ���۷���ó�� �����ϴ� wrapper��ü�� �����Ͽ� ����Ѵ�.
	std::optional<std::reference_wrapper<A>> maybe_a=std::ref(a);
	maybe_a->get().data=3; 
	
5.	�̷��̷��� Ÿ�Ե� �� �ϳ�(one-of)�� ǥ���ϱ� ���� variant��ü�� ����� �� �ִ�.
	std::variant<int, std::string, double> v=1;//v�� int
	variant�� �ƹ��͵� �������� ������ ���� ù ��° ���ڷ� ����Ʈ �����ڰ� ȣ��Ǳ⿡ ����ִ� variant��ü�� �Ұ����ϴ�.
	 variant�� ��ü ���� �ÿ� �����Ҵ��� �߻����� �ʱ⿡ one-of�� ǥ���ϱ� ���� �����ϴ�.
6.	DB�� ���� ���� Ÿ�Կ� ���� ����Ÿ���� �ٲ�� ��� �� ������ Ŭ���� ���迡�� C++�� ������(polymorphism)�� ����Ͽ� 
	����Ÿ���� std::unique_ptr<Data>, ������ std::make_unique<A>();�� ���� �߾�� ������ �̴� Ŭ�������� �θ� Ŭ������ �������� ���ܵǾ�� �ϰ�, ǥ�� Ŭ������ ��ü���� ������ �� ���ٴ� ������ �־���.
	 �̸� variant�� �ذ��� �� �ִ�.
7.	variant�� ���� Ÿ���� ������ ���ָ� ������ ������ �߻��ϰ� �ȴ�.
8.	std::monostatr�� variant�� �ƹ��͵� ���� ���¸� ǥ���� �� �ִ�. like optional
	std::variant<std::monostate, A, B> v;
	�̴� Ŭ���� Ÿ���� ������ �ϴµ�, �� Ŭ������ defualt constructor�� ���� ��쿡 ������ �߻��ϴ� ���� �����ش�. 
	class A {
 	public:
  	A(int i) {}
	};
	
	class B {
 	public:
  	B(int i) {}
	};
	
	std::variant<std::monostate, A, B> v;
9.	std::tuple��ü�� �����ϴ� �Լ��� ���� �� �׸��� �������� auto�� �ش� ��ü�� �޾� �� �׸��� ������ �����߾�� �ϴµ�,	
	C++17���� Structured binding�̶�� ��ũ���� �̿��Ͽ� ���� ���� tuple�� ������ ���� �� �ִ�. �ٸ� �ݵ�� ��� ���ҵ��� �޾ƾ� �Ѵ�. 
	structured binding�� tuple�ܿ��� pair�̳� ����ü�� ������ �ʵ���� �޴µ��� ����� �� �ִ�. 
*/
