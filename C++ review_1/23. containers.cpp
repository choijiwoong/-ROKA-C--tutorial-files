#include <iostream>
#include <functional>
#include <string>
#include <unordered_set>

//unorsered_set with hash function for Todo class that we made
template <typename K>
void print_unordered_set(const std::unordered_set<K>& m){
	for(const auto& elem: m)//print all elements
		std::cout<<elem<<std::endl;
} 

template <typename K>
void is_exist(std::unordered_set<K>& s, K key){
	auto itr=s.find(key);
	if(itr!=s.end())
		std::cout<<key<<"is exist!"<<std::endl;
	else
		std::cout<<key<<"is not exist!"<<std::endl;
}

class Todo{
	int priority;//high-first
	std::string job_desc;
	
	public:
		Todo(int priority, std::string job_desc): priority(priority), job_desc(job_desc){}//CONSTRUCTOR
		
		bool operator==(const Todo& t)const{//FOR COMPARE IN SAME BOX
		if(priority==t.priority && job_desc==t.job_desc)
			return true;
		}
		
		friend std::ostream& operator<<(std::ostream& o, const Todo& t);
		friend struct std::hash<Todo>;//hash function
};

namespace std{//for add class or function, we have to write namespace explicitly
	template<>
	struct hash<Todo>{
		size_t operator()(const Todo& t) const{
		hash<string> hash_func;
			return t.priority^(hash_func(t.job_desc));//XOR for confusion of two hash value
		}
	};
}

std::ostream& operator<<(std::ostream& o, const Todo& t){
	o<<"[priority: "<<t.priority<<" ] "<<t.job_desc;
	return o;
}

int main(){
	std::unordered_set<Todo> todos;
	
	todos.insert(Todo(1, "Goto Home"));
	todos.insert(Todo(2, "after many times"));
	todos.insert(Todo(3, "when i become _4"));
	todos.insert(Todo(3, "with knowledge of Human"));
	todos.insert(Todo(2, " & My Dream."));
	
	print_unordered_set(todos);
	std::cout<<"----------------------------"<<std::endl;
}

/*
1.	sequence container
	-vector: push_back, pop_back, at (RandomAccessIterator)_지우면 itr초기화 
	-list: insert, erase (BidirectionalIterator)_지워도 not 초기화
	-deque: insert, erase, at, push_back, push_pop 단점: 많은 메모리 
2.	associative container
	-set: find element is exist (BidirectionalIterator)_정렬을 통한 Tree구조이기에 매우 빠른 탐색. unbalanced tree가 되지 않도록 많은 규칙을 도입 
	-map: value by key_default constructor로 없는 원소의 값이 추가되지 않도록 먼저 find를 해주자 
	-multiset: same element ok
	-multimap: one key many value. equal_range를 사용하여 대응되는 값들을 검색 
	-unordered_set, unorderes_map: erase, find, insert FUCKING FAST because of Hash function(해시 충돌을 피해야하기에 설계가 어렵다. 최적화가 극강으로 필요할 때만 사용하자. rehash도 고려해야 한다) 
3.	template 버전의 경우 container iterator을 쓰기 위해 typename을 써주어야 한다. 
	iterator로는 const_iterator, reverse_iterator등이 있다. 웬만하면 접근에서 이터레이터를 사용하자. 
4.	사용자 정의 객체를 set에 넣으려면 정렬되어야하기에 operator<가 오버로딩되어야 하고, const여야 한다. const iterator는 cosnt function만 사용한다. 
	이때, 다른 객체도 구분 될 수 있도록 만들어야 하기에 완전한 <연산자의 기능 즉, strict weak ordering을 만족해야 한다.
	 아니면 Comp Functor를 만들어 같이 템플릿인자로 넣어주어도 된다. 
5.	사용자 정의 객체를 unordered_set이나 unordered_map의 원소로 넣고싶다면  Hash function을 만들고, operator==가 박스안의 원소비교를 위해 필요하다.
	어지간한 type의 hash_function은 C++에서 제공하니 이를 이용하자. 
6.	해시 함수가 제대로 성능을 뽐내려면 입력받은 키를 잘 흝뿌려야 하는데, 이는 꽤 어렵다. 그냥 기성품 쓰자 
*/
