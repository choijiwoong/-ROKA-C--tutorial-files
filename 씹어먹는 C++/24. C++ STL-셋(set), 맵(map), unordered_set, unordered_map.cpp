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
1.	 
*/ 

//������ ���� �ٸ��ٸ� �ϱ���,,, ��ǳ�� �ͼ� �׷� ������,,,���̾�Ʈ�� �ؼ� �׷� ������,,,���ƿ��� �������� �뷡�� �� �׷� ������,,,
