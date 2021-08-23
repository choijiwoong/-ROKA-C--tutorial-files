#include <iostream>
#include <set>
#include <string> 
#include <map> 

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

//3
templae <typename K, typename V>
void print_map(std::mal<K, V>& m){
	for(auto itr=m.begin(); itr!=m.end(); ++itr)
		std::cout<<itr->first<<" "<<itr->second<<std::endl;
}

int main(){
	
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
1.	 
*/ 

//오늘은 뭔가 꾸리꾸리 하구만,,, 태풍이 와서 그런 것인지,,,다이어트를 해서 그런 것인지,,,돌아오자 선우정아 노래를 들어서 그런 것인지,,,
