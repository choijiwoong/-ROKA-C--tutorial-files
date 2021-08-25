#include <iostream>
#include <set>
#include <string> 
#include <map> 
#include <unordered_set>
#include <unordered_map>
#include <functional> 

/*1
template <typename T>
void print_set(std::set<T>& s){
	std::cout<<"[ ";
	for(typename std::set<T>::iterator itr=s.begin(); itr!=s.end(); ++itr)//this iterator is BidirectionalIterator. only step by step approach like list in sequence container.
		std::cout<<*itr<<" ";
	std::cout<<" ] "<<std::endl;
} 
int main(){
	std::set<int> s;
	s.insert(10);//no location information! unlike sequence container
	s.insert(50);
	s.insert(20);
	s.insert(40);
	s.insert(30);
	
	//whether element is in set
	std::cout<<"sorted set will be out"<<std::endl;
	print_set(s);
	
	std::cout<<"Is 20 s's element? :: ";
	auto itr=s.find(20);//if exist, return that's iterator. if not, return s.end()
	if(itr!=s.end())
		std::cout<<"Yes"<<std::endl;
	else
		std::cout<<"No"<<std::endl;
	
	std::cout<<"Is 25 s's element? :: ";
	itr=s.find(25);
	if(itr!=s.end())
		std::cout<<"Yes"<<std::endl;
	else
		std::cout<<"No"<<std::endl;
		
	//no overlap of element
	std::cout<<std::endl<<std::endl;
	
	std::set<int> s1;
	s1.insert(10); 
	s1.insert(20);
	s1.insert(30);
	s1.insert(20);//ignore
	s1.insert(10);//ignore if we want to permit overlap, we can use multiset.
	
	print_set(s1);//Like sequence contatiner, set supply range-based for loop.
	
	return 0;
}*/

/*2
template <typename T, typename C>
void print_set(std::set<T, C>& s){
	for(const auto& elem:s)
		std::cout<<elem<<" "<<std::endl;
}
class Todo{
	int priority;//importance. high->emergency
	std::string job_desc;
	
	public:
		Todo(int priority, std::string job_desc): priority(priority), job_desc(job_desc) {}
		
		//bool operator<(const Todo& t) const{//we MUST keep const function that receives const Todo as reference. because set use const iterator in ordering.
		//	if(priority==t.priority)//if we don't handle this condition, compiler will ignore inserting of element that has same priority. 
		//		return job_desc<t.job_desc;//order by dictionary.
		//	return priority>t.priority;//high->emergency
		//}//so when we concrete 'oprator<', we must make other object can be distinguished on 'operator<'. it means one of A<B or B<A must be True.
		
		friend std::ostream& operator<<(std::ostream& o, const Todo& td);
		
		friend struct TodoCmp; 
};
struct TodoCmp{//Todo's operator< was deleted. but we have to compare of Todo objects, so make this class.
	bool operator()(const Todo& t1, const Todo& t2) const{//function object!
		if(t1.priority==t2.priority)
			return t1.job_desc<t2.job_desc;
		return t1.priority>t2.priority;
	
	}
};

std::ostream& operator<<(std::ostream& o, const Todo& td){
	o<<"[ importance: "<<td.priority<<"] "<<td.job_desc;
	return o;
}

int main(){
	std::set<Todo, TodoCmp> todos;//compiler do all comparing by TodoCmp's function object.
	
	todos.insert(Todo(1, "do basketball"));//error occur! set keeps ordered status saving data. compiler do comparing of element for ordering.
	todos.insert(Todo(2, "do math homework"));//but our todo class aren't defined operator<
	todos.insert(Todo(1, "programming project"));
	todos.insert(Todo(3, "meet friend"));
	todos.insert(Todo(2, "watch movie"));
	
	print_set(todos);
	
	std::cout<<"--------------"<<std::endl;
	std::cout<<"if finish homework!"<<std::endl;
	todos.erase(todos.find(Todo(2, "do math homework")));
	print_set(todos);
	
	return 0;
}*/

/*3
template <typename K, typename V>
void print_map_by_iterator(std::map<K, V>& m){//for use iterator of function argument
	for(auto itr=m.begin(); itr!=m.end(); ++itr)
		std::cout<<itr->first<<" "<<itr->second<<std::endl;//itr points std::pair object! so we can approach key by itr->first, and value by itr->second.
}//it can also change by using range-based for loop like that

template <typename K, typename V>
void print_map(std::map<K, V>& m){
	for(const auto& kv:m)//it's convenient than iterator
		std::cout<<kv.first<<" "<<kv.second<<std::endl;//elem returns object. so we can approach by .first and .second
}

template <typename K, typename V>//for prevent error that's occured when we refer value with [] that is not exist in map!
void search_and_print(std::map<K, V>& m, K key){
	auto itr=m.find(key);
	if(itr!=m.end())
		std::cout<<key<<" --> "<<itr->second<<std::endl;
	else//exception
		std::cout<<key<<"is not in map"<<std::endl;
}

int main(){
	std::map<std::string, double> pitcher_list;//2 argument of template argument in map. first argument is key's type, and second argument is value's type.
	
	//map'insert() get pair object as argument.
	pitcher_list.insert(std::pair<std::string, double>("saewoongpark", 2.34));//for add element in map, we must have to input std::pair object.
	pitcher_list.insert(std::pair<std::string, double>("hacker", 2.93));//passing template argument is some annoying, so we can use std::pair() that passes argument automatically.
	pitcher_list.insert(std::pair<std::string, double>("pearband", 2.95));
	//without type definition, std::make_pair can make std::pair object.
	pitcher_list.insert(std::make_pair("ouchancha", 3.04));//make_pair make std::pair object with template arguments that was gottten by ("ouchancha", 3.04)
	pitcher_list.insert(std::make_pair("wonjunjang", 3.05));
	pitcher_list.insert(std::make_pair("hacktor", 3.09));
	//without insert(), we can add element by []
	pitcher_list["nipert"]=3.56;//very convenient!
	pitcher_list["jonghunpark"]=3.76;//like dictionary in python!
	pitcher_list["kelly"]=3.90;//if there is same key, it will be replaced.
	
	print_map(pitcher_list);//print all elements
	std::cout<<std::endl<<"depending rate of saewoongpark :: "<<pitcher_list["saewoongpark"]<<std::endl;
	//than, we approach element that is not in pitcher_list.
	std::cout<<"print element(that is not existing) by [] :: "<<pitcher_list["choijiwoong"]<<std::endl;//not occur error! print 0
	//because when we call pitcher_list[choijiwoong] that is not exist in list, compiler call default constructor of double and add that value by 0. 
	//so it initializes value of 'choijiwoong' to zero.
	//For preventing this problem, refer value after check element is in list by find function.
	
	//solve problem of []!
	search_and_print(pitcher_list, std::string("saewoongpark"));
	search_and_print(pitcher_list, std::string("janghyoseoung"));//if we search "choijiwoong", it exists in list because we call default constructor of double before!
	
	//map don't allow overlapping of element like set! second insert can be ignored!
	pitcher_list.insert(std::pair<std::string, double>("coldbrewcoffee", 100));
	pitcher_list.insert(std::pair<std::string, double>("coldbrewcoffee", 0));//ignore!
	print_map(pitcher_list);
	std::cout<<"score of coldbrewcoffee! :: "<<pitcher_list["coldbrewcoffee"]<<std::endl;
	//so if we want to change element, use []!
	
	return 0;
}*/

/*4
template <typename K>
void print_set(const std::multiset<K>& s){
	for(const auto& elem:s)
		std::cout<<elem<<std::endl;
}

template <typename K, typename V>
void print_map(const std::multimap<K, V>& m){
	for(const auto& kv:m)
		std::cout<<kv.first<<" "<<kv.second<<std::endl;
}

int main(){
	std::multiset<std::string> s;
	s.insert("a");
	s.insert("b");
	s.insert("a");//overlap possible
	s.insert("c");
	s.insert("d");
	s.insert("c");
	print_set(s);
	
	std::multimap<int, std::string> m;
	m.insert(std::make_pair(1, "hello"));
	m.insert(std::make_pair(1, "hi"));
	m.insert(std::make_pair(1, "ahihi"));
	m.insert(std::make_pair(2, "bye"));
	m.insert(std::make_pair(2, "baba"));
	print_map(m);
	std::cout<<std::endl<<std::endl;
	std::cout<<m.find(1)->second<<std::endl;//Unlike common map, we can know many value can match to one key. but because of this, we can't use operator[] in multimap.
	//so multimap doesn't supply operator[]. than what will be returned at m.find(1)->second? In c++ standard, there is no definition of this. It means "hi" or "ahihi" or "hello" all ok in C++.
	//For use like this function, multimap apply this function.
	
	auto range=m.equal_range(1);//get multimap's key as argument, and return iterator of element's start and end as std::pair's first & second.
	for(auto itr=range.first; itr!=range.second; ++itr)//same key value's iterator information in range.first and range.second.
		std::cout<<itr->first<<" : "<<itr->second<<" "<<std::endl;
	
	return 0;
}*/

/*5
template <typename K>
void print_unordered_set(const std::unordered_set<K>& m){
	for(const auto& elem:m)
		std::cout<<elem<<std::endl;
}

template <typename K>
void is_exist(std::unordered_set<K>& s, K key){
	auto itr=s.find(key);
	if(itr!=s.end())
		std::cout<<key<<" exist!"<<std::endl;
	else
		std::cout<<key<<" not exist!"<<std::endl;
}

int main(){
	std::unordered_set<std::string> s;
	
	s.insert("hi");
	s.insert("my");
	s.insert("name");
	s.insert("is");
	s.insert("psi");
	s.insert("welcome");
	s.insert("to");
	s.insert("c++");
	
	print_unordered_set(s);//almost randomly print!
	std::cout<<"----------------"<<std::endl;
	is_exist(s, std::string("c++"));
	is_exist(s, std::string("c"));
	
	std::cout<<"----------------"<<std::endl;
	std::cout<<"delete 'hi' "<<std::endl;
	s.erase(s.find("hi"));
	is_exist(s, std::string("hi"));
	
	return 0;
}*/

template <typename K>//uset print
void print_unordered_set(const std::unordered_set<K>& m){
	for(const auto& elem:m)
		std::cout<<elem<<std::endl;
}

template <typename K>//uset is exist
void is_exist(std::unordered_set<K>& s, K key){
	auto itr=s.find(key);
	if(itr!=s.end())
		std::cout<<key<<" exist!"<<std::endl;
	else
		std::cout<<key<<" not exist! "<<std::endl;
}

class Todo{//This will be used in inordered_set
	int priority;//high==emergency
	std::string job_desc;
	
	public:
		Todo(int priority, std::string job_desc): priority(priority), job_desc(job_desc) {}//Constructor
		bool operator==(const Todo& t) const{//for comparing elements in same box(when hash collision). just teach what compiler has to compare in object.
			if(priority==t.priority && job_desc==t.job_desc) 
				return true;
			return false;
		}
		friend std::ostream& operator<<(std::ostream& o, const Todo& t);//print by <<
		friend struct std::hash<Todo>;//for use it in hash
};

//Functor for Todo's hash function
namespace std{//we have to write namespace explicitly when we add new class or function in special namespace.
	template<>
	struct hash<Todo>{
		size_t operator()(const Todo& t) const{
			hash<string> hash_func;//In c++, STL produces hash function about common type like int, std::string, etc.. so we just use it.
			return t.priority^(hash_func(t.job_desc));//priority is int value so just use as hash value, and calculate string's hash value by moving to hash_func object.
		}//(^ is xor) for jammpong~! 
	};
}
std::ostream& operator<<(std::ostream& o, const Todo& t){
	o<<"[priority : "<<t.priority<<" ] "<<t.job_desc;
	return o;
}

int main(){
	std::unordered_set<Todo> todos;
	
	todos.insert(Todo(1, "do basketball"));
	todos.insert(Todo(2, "do math homework"));
	todos.insert(Todo(1, "shot mg50"));
	todos.insert(Todo(3, "break remote control console's W8"));
	todos.insert(Todo(2, "watch movie"));
	print_unordered_set(todos);
	std::cout<<"------------------"<<std::endl;
	
	return 0;
}


/*
[0.	���⿡ �ռ�]
1.	�������� ��� ������ �����̳ʵ�(vector, list, deque)�� �� �״�� '����'��ü�� �����ϴ� �����̳ʵ��̴�.
2.	�̹��� �ٸ� ������ �����̳��� ���� �����̳�(associative container)�� �ٷ� ���ε�, �̴� ������ �����̳ʿ� �ٸ��� key-value������ ������.
	���� ���ø� ���̺귯���̱⿡ Ű�� �� ��ΰ� ������ Ÿ���� ��ü�� �� �� �ִ�. 
3.	�̸�(key)�� �������� ����(value)�� ��°� ó�� Ű�� �����ϴ� ���� ���� �� �ִ� �����ε�, �̷��� �ڷῡ�� ���� �� ������ ������ �� �� �ִ�. 
	-��ȿ���� �����Ϳ� �����ϴ���(Ư�� Ű�� ���� �����̳ʿ� �����ϴ��� ����)->True
	-���� �����Ѵٸ� �̿� �����ϴ� ���� ��������(Ư�� Ű�� �����Ǵ� ���� �������� ����)->21
4.	C++������ �� �ΰ��� �۾��� ó���� �� �ְ� ���� �����̳ʸ� �����ϴµ�, ������ ��� ��(set)�� ��Ƽ��(muliset)�̰�, ������ ��� ��(map)�� ��Ƽ��(multimap)�̴�.
	���� �ش��ϴ� Ű�� �ʿ� �������� ������ ���ʿ� �����Ǵ� ���� ������ �� ���� ������ �ʰ� ��Ƽ���� ��ó�� ����� �� �ִ�. ������, ���� �º��� �޸��� ��뷮�� ���� ������ Ű�� ���� ������ �ñ��ϴٸ� ���� ����ϴ� ���� ����.
	
[1.	��(set)]
1.	�¿� ���Ҹ� �߰��ϰų� ����� �۾��� O(logN)���� ó���ȴ�. �������� O(N)�̶�� ���� ���� �ξ� �����ܰ� �� �� �ִ�. 
2.	���Ϳ��ٸ� ó������ ������ ���ذ��� ã�⿡ vector.find()�� O(N)�̴�. ������ ���� O(logN)���� Ȯ���� �� �ִµ�, �� ���������� ���ҵ��� ���ĵ� ���¸� �����ϱ⿡ Ʈ�������� �����Ͽ� ���� ������ ������ ���� ������ Ȯ���� �� �ֱ� �����̴�.
	���� Ʈ�������� �� ���ҵ��� Ʈ���� �� ���鿡 ����Ǿ� �ְ�,
	-���ʿ� ���� ��� ������ ������ �۴�
	-�����ʿ� �ִ� ��� ������ ������ ũ��
	�� ��Ģ�� ��Ű�� �ִ�. �̶� ���Ҹ� �˻��ϴ� Ƚ���� Ʈ���� ���̿� ����ϱ⿡ Ʈ���� ��� �ִ��� ��� ������ �� ä��� ���� �߿��ϴ�.
3.	���� Ʈ���� �������� �ƿ� ġ���Ĺ��� ��ǻ� ������ �����̳ʿ� �˻� �ӵ��� ������ Ʈ���� ���������� ���� Ʈ��(unbalanced tree)��� �θ���.
	����, ���� ���� ������ ���� unbalanced tree�� ���� ���� �� ���� ��Ģ���� �����Ͽ� �׻� balanced�ǰ� �����ϰ� �ִ�. ���� ���� ���� ��O(logN)�� �˻��� ����ȴ�.
4.	���� �߿��� Ư¡���� �ߺ��� ���Ұ� ���ٴ� ���̴�. 

[2.	�������� ���� Ŭ���� ��ü�� �¿� �ְ� ���� ��]
1.	�� ���ο��� �� ���� ��ʼҰ� ���� �ٸ��ĸ� �Ǻ��ϱ� ���ؼ� ==�� �̿����� �ʴ´�. �� ���� A�� B�� �� ���ο��� ���ٴ� �ǹ̴� A.operator<(B)�� B.operator<(A)�� �� �� false��� ���̴�. 
2.	������ �����ڸ� operator<�� ������ ���� ���ǵ��� �����ؾ� �Ѵ�.(A�� B�� �ٸ� ��ü�� ���� ���� �ڵ鸵 �Ѵٸ�)
	-A<A is False
	-A<B!=B<A
	-A<B & B<C than A<C
	-A==B than A<B & B<A are both False
	-A==B & B==C than A==c 
	�� ���ǵ��� �����ϴ� <�����ڴ� strict weak ordering�� �����Ѵٰ� �Ѵ�.(��������� operator<�� �����ϸ� �� ����)
	����, �� ���� �� �ϳ��� ������ ���� �ʴ´ٸ�, set�� ����� �������� �ʰ�(������Ÿ�ӿ��� ���� X), ��Ÿ�ӻ󿡼� ������ �߻��ϴµ� ������� �ſ� ���� ���̴�.
3.	Ŭ���� ��ü�� operator<�� ���� �ʴ��� set�� ����� �� �ִ�. ������� �ܺ� ���̺귯���� ����ϴµ�, �� ���̺귯���� �� Ŭ������ ��ü�� �¿� �����ϰ� ������ oeprator<�� ���ǵǾ� ���� ���� ���̴�. �� ��� ���� ��ü�� ���� �� �ִ� ����� �˷��־�� �Ѵ�. 
	������ setŬ���� ���ǿ��� �ι�° ���ڷ� Comapare�� �޴� ���� �� �� �ִ�.
	template <class Key, class Compare=std::less<key>, class Allocator=std::allocator<Key>>
	class set;
	��������� ���� ������ ���԰� ������ O(logN), ������ Ž���� O(logN)���� �����ϴ� �ڷᱸ���̴�.

[3. ��(map)]
1.	���� �°� ���� �Ȱ��� �ڷᱸ����, ���� ��� Ű�� ����������, ���� ��� Ű�� �����Ǵ� �������� ���� �����Ѵ�. 
2.	std::pair object�� �׳� 2���� ��ü�� �ɹ��� ������ ��ü�̴�.
	template <class T1, class T2>
	struct std::pair{
		T1 first;
		T2 second;
	} 

[4.	��Ƽ��(multiset)�� ��Ƽ��(multimap)]
1.	��Ƽ�� & ��Ƽ���� �� & �ʰ� �޸� �ߺ��� ���ȴ�! 

[5.	���ĵ��� ���� �°� ��(unordered_set, unordered_map)]
1.	�� �״�� ���ҵ��� ������� ���ĵǾ� ���� �ʴ´�. ���� ������ ������ ���´�!
2.	��Ž���ڳ�: "���⼭ ���!" unordered_set���� �Ѱ��� ���� ���� �ִµ�, insert, erase, find ��� �۾��� O(1)�� ����ȴٴ� ���̴�! �� ������ unordered_set&map�� ������ �ִ�(feat. �ؽ��Լ�).
	unorder(�� �ٿ� ���ϰڴ�)�� ���԰� �˻� ������ �ؽ� �Լ�(Hash function)�� ����ϴµ�, �̴� ������ ũ���� �����͸� ������ ũ��(���� ������ ������)�� �����ͷ� ���������ִ� �Լ��̴�. 
	unorder�� �ؽ��Լ��� 1���� D(=������ ��)������ ���� ��ȯ�ϰ�, �� �ؽð�(�ؽ��Լ��� ����� ��)�� ���Ҹ� ������ ������ ��ȣ�� ��´�. �ؽ��Լ��� ������ �ִ��� 1���� D���� �� ���� ��ȯ�ϵ��� ����Ǿ�, ��� ���ڸ� ����� ����� �� �ִ�.
	�ؽ� �Լ��� ���� �߿��� ������, ���� ���� ���Ҹ� �ؽ� �Լ��� �����Ѵٸ� ���� �ؽð��� �����Ѵٴ� ���̴�. ��� ������ ���Ҹ� Ž���� �� �ִ�.
	ex) �����"�Ķ����� unordered_set�� ����ֳ�?"->�Ķ����� �ؽ��Լ��� �����ϸ� 1����->1�����ڸ� ���� �Ķ����� ����->����! (�̶� �ؽ� �Լ��� �ؽð� ����� ��� �ð��� ó���Ѵ�!)
	 �ٸ� �ٸ� �����ӿ��� �ұ��ϰ� ���� �ؽð��� ���� ��찡 �ִµ� �̸� �ؽ� �浹(hash collision)�̶�� �Ѵ�. ex)�� ��� ���� ���ڿ� �ٸ� ���ҵ��� �ְ� ��.
	��, input�� �ؽð��� ����ϰ�, �ش��ϴ� ���ڿ� ��� ���ҵ��� Ž���ؾ� �Ѵ�.(�׷��� ���� �ʰ� �ϱ� ���� �ִ��� 1���� N���� �� ���� ��ȯ�ϵ��� ����)
	���, ���� �ſ� ���ڸ� ��� input�� ���� ���ڿ� ���� ��������� O(1)������, �־��� �ܿ� O(N)���� ����� �� �ִ�. (p.s set�� map�� �־ǰ� ��� ��� O(logN)
	 �� ������ ������ ��� �����ϰ� ���̳� ���� ����ϰ�, ����ȭ�� �ſ� �ʿ��� ��쿡 �ؽ� �Լ��� �� �����ؼ� unordered_set�� unordered_map�� ����ϴ� ���� ����.(p.s �⺻ Ÿ�Ե�(in, double etc..)�� std::string�� ��ü������ �ؽ� �Լ��� ����Ǿ� �־� �׳� ����ϸ� �ȴ�.)
3.	ó������ ���� ������ ����(�� �޸�)�� ����� �� ���⿡, ������ ������ ���Ұ� ���������� ���������� �þ�µ�, �̶����� �ؽ��Լ��� �ٲ���ϱ⿡ ��� ���Ҹ� ó������ ������ insert�ؾ��Ѵ�. �̸� rehash��� �ϸ� O(N)�� �ð��� �ɸ���.
 
[6.	���� ���� Ŭ������ 'unordered_set/unordered_map'�� ���ҷ� �ְ� ���� ��]
1.	���̳� �ʰ� �޸� ���� '�ؽ� �Լ�'�� ������ �Ѵ�.(��� �°� �� �̿���3)
	�������� �ʱ⿡ operator<�� �ʿ����� ������, operator==�� �ؽ� �浹 �߻� �ÿ� ���ھȿ� ���ҵ�� �񱳸� ���ؼ� �ʿ��ϴ�.
	������ ���� C++���� �⺻���� Ÿ�Ե鿡 ���� �ؽ� �Լ����� �����ϰ� �־� �̸� �� Ȱ���ϸ� �ȴ�.
2.	�ؽ� �Լ��� ���� �����ϴ� ���� �ϳ� ��ƴ�. �ֳĸ� unordered_map�� ����� �� ������ �����ϱ� ���ؼ��� �ؽ� �Լ��� �Է¹��� Ű�� �� �y�ѷ��� �ϱ� �����̴�.
	���� �ؽ� �Լ������ Ư�� ������ ���� ���ߵǾ� �ִٸ�, ������ set, map���� ���� �Ӹ� �ƴ϶� �������� ����ڰ� ������ �̿��Ͽ� ���α׷��� ������ ���Ͻ�ų �� �ִ�.
	 ���, �⺻ Ÿ�Կ� ���� �ؽ��Լ��� ����ϰų�, map�̳� set�� ����ϴ� ���� ����.
	 
[7.	�׷��ٸ� �� ��ߵ�?]
	-�������� ���� ������ �ñ��� ���->set
	-�ߺ� �����͸� ����� ���->multiset(insert, erase, find ��� O(logN), �־ǵ� O(logN)
	-�����Ϳ� �����Ǵ� �����͸� �����ϰ� ���� ���->map
	-�ߺ� Ű�� ����� ���->multimap(insert, erase, find ��� O(logN), �־ǵ� O(logN)
	-�ӵ��� �ſ�ſ� �߿��ؼ� ����ȭ�� �ؾ��ϴ� ���->unordered_set, unordered_map(insert, erase, find ��� O(1), �־��� O(N) 
*/ 

//������ ���� �ٸ��ٸ� �ϱ���,,, ��ǳ�� �ͼ� �׷� ������,,,���̾�Ʈ�� �ؼ� �׷� ������,,,���ƿ��� �������� �뷡�� �� �׷� ������,,,
