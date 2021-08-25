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
[0.	들어가기에 앞서]
1.	지난번에 배운 시퀀스 컨테이너들(vector, list, deque)은 말 그대로 '원소'자체를 보관하는 컨테이너들이다.
2.	이번엔 다른 종류의 컨테이너인 연관 컨테이너(associative container)를 다룰 것인데, 이는 시퀀스 컨테이너와 다르게 key-value구조를 가진다.
	물론 템플릿 라이브러리이기에 키와 값 모두가 임의의 타입의 객체가 될 수 있다. 
3.	이름(key)를 바탕으로 나이(value)를 얻는것 처럼 키에 대응하는 값을 얻을 수 있는 구조인데, 이러한 자료에서 보통 두 가지의 질문을 할 수 있다. 
	-장효성이 데이터에 존재하는지(특정 키가 연관 컨테이너에 존재하는지 유무)->True
	-만약 존재한다면 이에 대응하는 값이 무엇인지(특정 키에 대응되는 값이 무엇인지 질의)->21
4.	C++에서는 위 두가지 작업을 처리할 수 있게 연관 컨테이너를 제공하는데, 전자의 경우 셋(set)과 멜티셋(muliset)이고, 후자의 경우 맵(map)과 멀티맵(multimap)이다.
	물론 해당하는 키가 맵에 존재하지 않으면 애초에 대응되는 값을 가져올 수 없기 때문에 맵과 멀티맵을 셋처럼 사용할 수 있다. 하지만, 맵은 셋보다 메모리의 사용량이 많기 때문에 키의 존재 유무만 궁금하다면 셋을 사용하는 것이 좋다.
	
[1.	셋(set)]
1.	셋에 원소를 추가하거나 지우는 작업은 O(logN)으로 처리된다. 시퀀스가 O(N)이라는 점을 보면 훨씬 빠르단걸 알 수 있다. 
2.	벡터였다면 처음부터 끝까지 비교해가며 찾기에 vector.find()는 O(N)이다. 하지만 셋은 O(logN)으로 확인할 수 있는데, 셋 내부적으로 원소들이 정렬된 상태를 유지하기에 트리구조로 구성하여 비교적 빠르게 원소의 존재 유무를 확인할 수 있기 때문이다.
	흔히 트리구조는 각 원소들이 트리의 각 노드들에 저장되어 있고,
	-왼쪽에 오는 모든 노드들은 나보다 작다
	-오른쪽에 있는 모든 노드들은 나보다 크다
	의 규칙을 지키고 있다. 이때 원소를 검색하는 횟수는 트리의 높이에 비례하기에 트기의 경우 최대한 모든 노드들을 꽉 채우는 것이 중요하다.
3.	만약 트리가 한쪽으로 아예 치우쳐버려 사실상 시퀀스 컨테이너와 검색 속도가 동일한 트리를 균형잡히지 않은 트리(unbalanced tree)라고 부른다.
	물론, 실제 셋의 구현을 보면 unbalanced tree를 막기 위해 더 많은 규칙들을 도입하여 항상 balanced되게 유지하고 있다. 따라서 셋의 구현 상O(logN)의 검색이 보장된다.
4.	셋의 중요한 특징으로 중복된 원소가 없다는 것이다. 

[2.	여러분이 만든 클래스 객체를 셋에 넣고 싶을 때]
1.	셋 내부에서 두 개의 우너소가 같냐 다르냐를 판별하기 위해서 ==를 이용하지 않는다. 두 원소 A와 B가 셋 내부에서 같다는 의미는 A.operator<(B)와 B.operator<(A)가 둘 다 false라는 뜻이다. 
2.	엄밀히 말하자면 operator<는 다음과 같은 조건들을 만족해야 한다.(A와 B가 다른 객체일 때를 따로 핸들링 한다면)
	-A<A is False
	-A<B!=B<A
	-A<B & B<C than A<C
	-A==B than A<B & B<A are both False
	-A==B & B==C than A==c 
	이 조건들을 만족하는 <연산자는 strict weak ordering을 만족한다고 한다.(상식적으로 operator<를 설계하면 걍 저럼)
	만약, 위 조건 중 하나라도 조건이 맞지 않는다면, set이 제대로 동작하지 않고(컴파일타임에서 오류 X), 런타임상에서 오류가 발생하는데 디버깅이 매우 힘들 것이다.
3.	클래스 자체에 operator<를 두지 않더라도 set을 사용할 수 있다. 예를들어 외부 라이브러리를 사용하는데, 그 라이브러리의 한 클래스의 객체를 셋에 저장하고 싶은데 oeprator<가 정의되어 있지 않을 때이다. 아 경우 따로 객체를 비교할 수 있는 방법을 알려주어야 한다. 
	실제로 set클래스 정의에서 두번째 인자로 Comapare를 받는 것을 알 수 있다.
	template <class Key, class Compare=std::less<key>, class Allocator=std::allocator<Key>>
	class set;
	결과적으로 셋은 원소의 삽입과 삭제를 O(logN), 원소의 탐색도 O(logN)으로 수행하는 자료구조이다.

[3. 맵(map)]
1.	맵은 셋과 거의 똑같은 자료구조로, 셋의 경우 키만 보관했지만, 맵의 경우 키에 대응되는 값까지도 같이 보관한다. 
2.	std::pair object는 그냥 2개의 객체를 맴버로 가지는 객체이다.
	template <class T1, class T2>
	struct std::pair{
		T1 first;
		T2 second;
	} 

[4.	멀티셋(multiset)과 멀티맵(multimap)]
1.	멀티셋 & 멀티맵은 셋 & 맵과 달리 중복이 허용된다! 

[5.	정렬되지 않은 셋과 맵(unordered_set, unordered_map)]
1.	말 그대로 원소들이 순서대로 정렬되어 들어가지 않는다. 거의 랜덤한 순서로 나온다!
2.	명탐정코난: "여기서 잠깐!" unordered_set에는 한가지 놀라운 점이 있는데, insert, erase, find 모든 작업이 O(1)로 수행된다는 점이다! 그 원리는 unordered_set&map의 구현에 있다(feat. 해시함수).
	unorder(로 줄여 말하겠다)는 삽입과 검색 이전에 해시 함수(Hash function)를 사용하는데, 이는 임의의 크기의 데이터를 고정된 크기(일정 범위의 정수값)의 데이터로 대응시켜주는 함수이다. 
	unorder의 해시함수는 1부터 D(=상자의 수)까지의 값을 반환하고, 그 해시값(해시함수로 계산한 값)을 원소를 저장할 상자의 번호로 삼는다. 해시함수는 구조상 최대한 1부터 D까지 고른 값을 반환하도록 설계되어, 모든 상자를 고루고루 사용할 수 있다.
	해시 함수의 가장 중요한 성질은, 만약 같은 원소를 해시 함수에 전달한다면 같은 해시값을 리턴한다는 점이다. 고로 빠르게 원소를 탐색할 수 있다.
	ex) 사용자"파란공이 unordered_set에 들어있나?"->파란공을 해시함수에 대입하면 1리턴->1번상자를 보니 파란공이 있음->존재! (이때 해시 함수가 해시값 계산을 상수 시간에 처리한다!)
	 다만 다른 원소임에도 불구하고 같은 해시값을 갖는 경우가 있는데 이를 해시 충돌(hash collision)이라고 한다. ex)이 경우 같은 상자에 다른 원소들이 있게 됨.
	즉, input의 해시값을 계산하고, 해당하는 상자에 모든 원소들을 탐색해야 한다.(그렇게 하지 않게 하기 위해 최대한 1부터 N까지 고른 값을 반환하도록 설계)
	고로, 운이 매우 나쁘면 모든 input이 같은 상자에 들어가서 평균적으로 O(1)이지만, 최악의 겨우 O(N)으로 수행될 수 있다. (p.s set과 map은 최악과 평균 모두 O(logN)
	 이 때문에 보통의 경우 안전하게 맵이나 셋을 사용하고, 최적화가 매우 필요할 경우에 해시 함수를 잘 설계해서 unordered_set과 unordered_map을 사용하는 것이 좋다.(p.s 기본 타입들(in, double etc..)과 std::string은 자체적으로 해시 함수가 내장되어 있어 그냥 사용하면 된다.)
3.	처음부터 많은 개수의 상자(곧 메모리)를 사용할 수 없기에, 상자의 개수는 원소가 많아질수록 점진적으로 늘어나는데, 이때마다 해쉬함수를 바꿔야하기에 모든 원소를 처음부터 끝까지 insert해야한다. 이를 rehash라고 하며 O(N)의 시간이 걸린다.
 
[6.	내가 만든 클래스를 'unordered_set/unordered_map'의 원소로 넣고 싶을 때]
1.	셋이나 맵과 달리 직접 '해시 함수'를 만들어야 한다.(고로 셋과 맵 이용하3)
	정렬하지 않기에 operator<가 필요하지 않지만, operator==는 해시 충돌 발생 시에 상자안에 원소들과 비교를 위해서 필요하다.
	다행인 점은 C++에서 기본적인 타입들에 대한 해시 함수들을 제공하고 있어 이를 잘 활용하면 된다.
2.	해시 함수를 직접 제작하는 일은 꽤나 어렵다. 왜냐면 unordered_map이 제대로 된 성능을 발휘하기 위해서는 해시 함수가 입력받은 키를 잘 흝뿌려야 하기 때문이다.
	만약 해시 함수결과가 특정 범위의 값에 집중되어 있다면, 성능이 set, map보다 못할 뿐만 아니라 악의적인 사용자가 허점을 이용하여 프로그램의 성능을 저하시킬 수 있다.
	 고로, 기본 타입에 대한 해시함수를 사용하거나, map이나 set을 사용하는 것이 좋다.
	 
[7.	그렇다면 뭘 써야되?]
	-데이터의 존재 유무만 궁금할 경우->set
	-중복 데이터를 허락할 경우->multiset(insert, erase, find 모두 O(logN), 최악도 O(logN)
	-데이터에 대응되는 데이터를 저장하고 싶을 경우->map
	-중복 키를 허락할 경우->multimap(insert, erase, find 모두 O(logN), 최악도 O(logN)
	-속도가 매우매우 중요해서 최적화를 해야하는 경우->unordered_set, unordered_map(insert, erase, find 모두 O(1), 최악은 O(N) 
*/ 

//오늘은 뭔가 꾸리꾸리 하구만,,, 태풍이 와서 그런 것인지,,,다이어트를 해서 그런 것인지,,,돌아오자 선우정아 노래를 들어서 그런 것인지,,,
