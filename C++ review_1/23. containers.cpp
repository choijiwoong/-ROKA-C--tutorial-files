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
	-vector: push_back, pop_back, at (RandomAccessIterator)_����� itr�ʱ�ȭ 
	-list: insert, erase (BidirectionalIterator)_������ not �ʱ�ȭ
	-deque: insert, erase, at, push_back, push_pop ����: ���� �޸� 
2.	associative container
	-set: find element is exist (BidirectionalIterator)_������ ���� Tree�����̱⿡ �ſ� ���� Ž��. unbalanced tree�� ���� �ʵ��� ���� ��Ģ�� ���� 
	-map: value by key_default constructor�� ���� ������ ���� �߰����� �ʵ��� ���� find�� ������ 
	-multiset: same element ok
	-multimap: one key many value. equal_range�� ����Ͽ� �����Ǵ� ������ �˻� 
	-unordered_set, unorderes_map: erase, find, insert FUCKING FAST because of Hash function(�ؽ� �浹�� ���ؾ��ϱ⿡ ���谡 ��ƴ�. ����ȭ�� �ذ����� �ʿ��� ���� �������. rehash�� ����ؾ� �Ѵ�) 
3.	template ������ ��� container iterator�� ���� ���� typename�� ���־�� �Ѵ�. 
	iterator�δ� const_iterator, reverse_iterator���� �ִ�. �����ϸ� ���ٿ��� ���ͷ����͸� �������. 
4.	����� ���� ��ü�� set�� �������� ���ĵǾ���ϱ⿡ operator<�� �����ε��Ǿ�� �ϰ�, const���� �Ѵ�. const iterator�� cosnt function�� ����Ѵ�. 
	�̶�, �ٸ� ��ü�� ���� �� �� �ֵ��� ������ �ϱ⿡ ������ <�������� ��� ��, strict weak ordering�� �����ؾ� �Ѵ�.
	 �ƴϸ� Comp Functor�� ����� ���� ���ø����ڷ� �־��־ �ȴ�. 
5.	����� ���� ��ü�� unordered_set�̳� unordered_map�� ���ҷ� �ְ�ʹٸ�  Hash function�� �����, operator==�� �ڽ����� ���Һ񱳸� ���� �ʿ��ϴ�.
	�������� type�� hash_function�� C++���� �����ϴ� �̸� �̿�����. 
6.	�ؽ� �Լ��� ����� ������ �˳����� �Է¹��� Ű�� �� �y�ѷ��� �ϴµ�, �̴� �� ��ƴ�. �׳� �⼺ǰ ���� 
*/
