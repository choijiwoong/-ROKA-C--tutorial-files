#include <iostream>
#include <algorithm>
#include <vector> 
#include <functional>
#include <string>

/*1
//for print Vector!
template <typename Iter>//get Iter type as template argument
void print(Iter begin, Iter end){//get Iterator's begin and end as argument
	while(begin!=end){//if content exist
		std::cout<<*begin<<" ";//print that's value by *operator
		begin++;//and pass to next content
	}
	std::cout<<std::endl;
}
//compare functor 1
struct int_compare{//Functor for comparing.
	bool operator()(const int& a, const int& b) const{
		return a>b;
	}
};//but already many common types get operator< or >! so make it by template with expanding.
//compare functor 2
template <typename T>
struct greater_comp{//make new version of compare funtor! BUT it's already in functionla header!!! that's 'greater<int>()'!
	bool operator()(const T& a, const T& b) const{
		return a>b;
	}
};
//compare functor 3 is in std::greater<>()!!

//for stable_sort
struct User{//for show difference of stable_sort and common sort
	std::string name;
	int age;
	
	User(std::string name, int age):name(name), age(age){}
	bool operator<(const User& u) const {//comparing is only depending on User.age regardless of name.
		return age<u.age;
	}
};
std::ostream& operator<<(std::ostream& o, const User& u){
	o<<u.name<<" , "<<u.age;
	return o;
}

int main(){
	//<1. normal sort>
	std::vector<int> vec;
	vec.push_back(5);
	vec.push_back(3);
	vec.push_back(1);
	vec.push_back(6);
	vec.push_back(4);
	vec.push_back(7);
	vec.push_back(2);
	
	std::cout<<"before sort ----"<<std::endl;
	print(vec.begin(), vec.end());//push functor! for comparing.
	std::sort(vec.begin(), vec.end(), std::greater<int>());//get Iterator. This iterator has to satisfy RandomAccessIterator type, so deque and vector only can use sort_function.
	//ex_list is BidirectionalIterator. so sort(l.begin(), l.end()); makes error.
	std::cout<<"after sort ----"<<std::endl;
	print(vec.begin(), vec.end());
	
	std::cout<<std::endl;
	//<2. partial_sort>
	std::vector<int> vec_;
	vec_.push_back(5);
	vec_.push_back(3);
	vec_.push_back(1);
	vec_.push_back(6);
	vec_.push_back(4);
	vec_.push_back(7);
	vec_.push_back(2);
	
	std::cout<<"before sort ----"<<std::endl;
	print(vec_.begin(), vec_.end());
	std::partial_sort(vec_.begin(), vec_.begin()+3, vec_.end());//sort [start, middle) in all elements at [start, end)
	//partial_sort's complexity is O(NlogM) (all size is N, part's size is M)
	std::cout<<"after sort ----"<<std::endl;
	print(vec_.begin(), vec_.end());//left element locate randomly!
	//when we don't need sort all elements, it will be used. like we want to know only highest 10%'s grade.
	
	std::cout<<std::endl;
	//<3. stable_sort>
	std::vector<User> vec3;
	for(int i=0; i<100; i++){//make test data
		std::string name="";
		name.push_back('a'+i/26);
		name.push_back('a'+i%26);//name is like "aa, ab, ac..." already sorted data
		vec3.push_back(User(name, static_cast<int>(rand()%10)));//age is random value.
	}
	
	std::vector<User> vec4=vec3;
	
	std::cout<<"before sort ----"<<std::endl;
	print(vec3.begin(), vec3.end());
	
	std::sort(vec3.begin(), vec3.end());
	std::cout<<"after sort ----"<<std::endl;
	print(vec3.begin(), vec3.end());
	
	std::cout<<"stable_sort case ---"<<std::endl;
	std::stable_sort(vec4.begin(), vec4.end());
	print(vec4.begin(), vec4.end());
	
	return 0;
}*/

/*2
template<typename Iter>
void print(Iter begin, Iter end){
	while(begin!=end){
		std::cout<<"["<<*begin<<"] ";
		begin++;
	}
	std::cout<<std::endl;
}

//for remove_if function's description
struct is_odd{//functor for pass eleminate condition.
	bool operator()(const int& i){
		return i%2==1;
	}
};
//for show pass real function not functor
bool odd(const int& i){
	return i%2==1;
}

//for add condition of remove_if
struct Is_odd{
	int* num_delete;
	
	Is_odd(int* num_delete):num_delete(num_delete){}//constructor with initialize list
	bool operator()(const int& i){
		if(*num_delete>=2)//already delete two elements
			return false;
		if(i%2==1){//erase element
			(*num_delete)++;
			return true;
		}
		return false;
	}
	
};

int main(){
	//<1. remove function>
	std::vector<int> vec;
	vec.push_back(5);
	vec.push_back(3);
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	
	std::cout<<"initial vec's status ------"<<std::endl;
	print(vec.begin(), vec.end());
	
	std::cout<<"eleminate element that's value is 3 in vector ---"<<std::endl;
	vec.erase(std::remove(vec.begin(), vec.end(), 3), vec.end());//erase function has two model that is 'Iterator erase(Iterator pos)', and 'Iterator erase(Iterator first, Iterator last)'
	//first model is just erase element that's in pos, second model is erase all elements in first~last.
	//In content, remove do shift work that finds element 3. than vector that doesn't has 3. but It's not actually delete. just shift.
	//So, by using erase function, we can actually delete value 3. 3 remains in last space. so erase that space to vec.end()
	print(vec.begin(), vec.end());
	//p.s remove function's iterator type is ForwardIterator. so we can use it not only vector, but also list, set, map...etc!
	
	std::cout<<std::endl;
	//<2. remove_if function>
	std::vector<int> vec2;
	vec2.push_back(5);
	vec2.push_back(3);
	vec2.push_back(1);
	vec2.push_back(2);
	vec2.push_back(3);
	vec2.push_back(4);
	
	std::cout<<"initial vec's status ------"<<std::endl;
	print(vec2.begin(), vec2.end());
	
	std::cout<<"eleminate odd element in vector ---"<<std::endl;
	vec2.erase(std::remove_if(vec2.begin(), vec2.end(), is_odd()), vec2.end());//pass functor as delete condition.
	//of coursely, we can pass ral function like it
	vec2.erase(std::remove_if(vec2.begin(), vec2.end(), odd),  vec2.end());
	print(vec2.begin(), vec2.end());
	
	std::cout<<std::endl;
	//<3. add condition to remove_if>
	std::vector<int> vec3;
	vec3.push_back(5);
	vec3.push_back(3);
	vec3.push_back(1);
	vec3.push_back(2);
	vec3.push_back(3);
	vec3.push_back(4);
	
	std::cout<<"initial vec's status ------"<<std::endl;
	print(vec3.begin(), vec3.end());
	
	std::cout<<"eleminate 2 element in front of odd element in vector ---"<<std::endl;
	int num_delete=0;//for prevent (logical...?) error
	vec3.erase(std::remove_if(vec3.begin(), vec3.end(), Is_odd(&num_delete)), vec3.end());
	
	//vec3.erase(std::remove_if(vec3.begin(), vec3.end(), bool is_odd(int i){return i%2==1;}), vec3.end());
	//very good way! but it doesn't allow in C++ �� TT but it's solution is made in C++ 11!
	
	print(vec3.begin(), vec3.end());//error! 3 odd elements are deleted! not 2!
	//In standard of C++, functor in remove_if will not change inner status. it means, using num_delete is impossible in principle.
	//because in remove_if, functor can be copied any times by code.
	
	return 0;
}*/

/*3
class SomeClass{
	std::vector<int> vec;
	int num_erased;
	
	public:
		SomeClass(){
			vec.push_back(5);
			vec.push_back(3);
			vec.push_back(1);
			vec.push_back(2);
			vec.push_back(3);
			vec.push_back(4);
			
			num_erased=1;
			
			vec.erase(std::remove_if(vec.begin(), vec.end(),
				[this](int i){//use this pointer not &num_erased! it's impossible because member variable doesn't has address before instantiation.
					if(this->num_erased>=2)
						return false;
					else if(i%2==1){
						this->num_erased++;
						return true;
					}
					return false;
				}),
				vec.end()
			);
		}
		
}; 

template <typename Iter>
void print(Iter begin, Iter end){
	while(begin!=end){
		std::cout<<"["<<*begin<<"] ";
		begin++;
	}
	std::cout<<std::endl;
}

int main(){
	std::vector<int> vec;
	vec.push_back(5);
	vec.push_back(3);
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	
	std::cout<<"initial vec's status"<<std::endl;
	print(vec.begin(), vec.end());
	
	std::cout<<"eleminate odd element in vector ---"<<std::endl;
	int num_erased=0;
	vec.erase(std::remove_if( vec.begin(), vec.end(), [&num_erased](int i)->bool{//By capture list, we can use num_erased like in scope. It means we can change value of num_erased in function.
		//if we don't use & use just num_erased, it will be const. so we can't change that value, only read.
		if(num_erased>=2)
			return false;
		else if(i%2==1){
			num_erased++;
			return true;
		}
		return false;
	} ), vec.end());
	
	print(vec.begin(), vec.end());
	
	return 0;
}*/

//4
template<typename Iter>
void print(Iter begin, Iter end){
	while(begin!=end){
		std::cout<<"["<<*begin<<"] ";
		begin++;
	}
	std::cout<<std::endl;
} 
/*4
int main(){
	std::vector<int> vec;
	vec.push_back(5);
	vec.push_back(3);
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	
	std::vector<int> vec2(6, 0);//initialize vec2 to '0' 6 times. 
	
	std::cout<<"initial vec's & vec2's status -----"<<std::endl;
	print(vec.begin(), vec.end());
	print(vec2.begin(), vec2.end());
	
	std::cout<<"add 1 to all element of vec and save to vec2"<<std::endl;
	std::transform(vec.begin(), vec.end(), vec2.begin(), [](int i) {return i+1;});//not need for loop! and high read ability!
	print(vec.begin(), vec.end());
	print(vec2.begin(), vec2.end());
	
	return 0;
}*/

/*5-1
int main(){
	std::vector<int> vec;
	vec.push_back(5);
	vec.push_back(3);
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	
	auto result=std::find(vec.begin(), vec.end(), 3);
	std::cout<<"3 is "<<std::distance(vec.begin(), result)+1<<"st element"<<std::endl;
	
	//if you want to find all e element
	auto current=vec.begin();
	while(true){
		current=std::find(current, vec.end(), 3);
		if(current==vec.end())
			break;
		std::cout<<"3 is "<<std::distance(vec.begin(), current)+1<<"st element"<<std::endl;
		current++;
	}
	
	//find_if function
	auto current2=vec.begin();
	while(true){
		current2=std::find_if(current2, vec.end(), [](int i)->int{return i%3==2;});//find_if function get functor as argument
		if (current2==vec.end())
			break;
		std::cout<<"element that satisfies i%3==2 is : "<<*current2<<std::endl;
		current2++;
	} 
	
	return 0;
}*/

//5-2
struct User{
	std::string name;
	int level;
	
	User(std::string name, int level) : name(name), level(level) {}
	bool operator==(const User& user) const{
		if(name==user.name && level==user.level)
			return true;
		return false;
	}
};

class Party{
	std::vector<User> users;
	
	public:
		bool add_user(std::string name, int level){
			User new_user(name, level);
			if(std::find(users.begin(), users.end(), new_user) != users.end())
				return false;//overlap
			users.push_back(new_user);
			return true;
		}
		bool can_join_dungeon(){//all >15 level
			return std::all_of(users.begin(), users.end(), [](User& user) {return user.level>=15;});
		}
		bool can_use_special_item(){//anyone >19 level
			return std::any_of(users.begin(), users.end(), [](User& user){return user.level>=19;});
		}
};
int main(){
	Party party;
	party.add_user("covid",19);
	party.add_user("column",0);
	party.add_user("row",1);
	party.add_user("cookie", 10);
	party.add_user("covid", 19);
	
	std::cout<<std::boolalpha;
	std::cout<<"can join dungeon? "<<party.can_join_dungeon()<<std::endl;
	std::cout<<"can use special item? "<<party.can_use_special_item()<<std::endl;
	
	return 0;
}


/*
[0.	���⿡ �ռ�]
1.	�����̳ʿ� �ݺ��ڸ� ������ ���� ����ϰ� �����ִ� ���� �˰��� ���̺귯���ε�, ���⿡ ���ǵǾ� �ִ� ���� �Լ���� �۾��� �����Ѵ�.
	template <typename Iter>
	void do_something(Iter begin, Iter end);//get iterator's start and end
	Ȥ��
	template <typename Iter, typename Pred>
	void do_something(Iter begin, Iter end, Prd pred)//get iterator's start and end with 'special condition' that's called Predicate
	���� ������. 
	�̶� Ư���� ������ ������(Predicate)��� �θ��� pred���� ���� bool�� return�ϴ� Functor(�Լ� ��ü)�� �����ϰ� �ȴ�.

[1.	����(sort, stable_sort, partial_sort)]_�븻����, ���Ľ� �� ������ ��������, �Ϻκи� ���� 
1.	std::sort(vec.begin(), vec.end())�� RandomAccessIterator�� �����Ǵ� deque�� vector�� �����ϴ�.
	���� ���� ������������ �����ϰ� �ʹٸ�, compare�� ��� �� �������� ���ڷ� �Ѱ��ָ� �ȴ�. 
2.	stable_sort�� sort�� ���� �������� ���ҵ鰣�� ����� ��ġ�� �ٲٴ°Ͱ��� �޸� ó�� ���� �״�� �����Ѵ�.
	��� ���� �� �ð��� �ɸ��µ�, C++ǥ�ؿ� ������, �־��� ��� sort�� O(nlogn)�� �ݸ�, stable_sort�� O(n(log n)^2)�̴�.
	
[2.	���� ����(remove, remove_if)]
1.	��κ��� �����̳ʿ��� ���Ҹ� �����ϴ� �Լ��� �����ϰ� ������, ���Ұ� ���ŵ� �� ���� ������ �����Ͽ��� �ݺ��ڵ��� �ʱ�ȭ�Ǳ⿡ �ش� ��ġ�� ����Ű�� �ݺ��ڸ� ��� �ٽ� �����;� �ߴ�.
	std::vector<int>::iterator itr=vec.begin();
	for(; itr!=vec.end(); ++itr){
		if(*itr==3){
			vec.erase(itr);
			itr=vec.begin();
		}
	}
2.	remove_if �Լ��� �Լ� ��ü�� ���ڸ� �� 1���޴´ٰ� �����ߴµ�, �̷� ȣ��Ǵ� operator()�� ���ؼ��� ���ҿ� ���� ���� ����� �߰����� ������ �����ϱ� ��ƴ�. 
	��� Ȧ���� ���ҵ��� �����ϵ� ó�� 2���� �����ϴ� ������ ������. 
	 �Լ���ü�� ��� �� �״�� ��ü�̱⿡ ��������� ������ �� �ִ�! 
3.	remove_if�� ������ �������� ��, �Լ� ��ü�� ������ ����� �� �ֱ� ������ remove_if�� ���޵Ǵ� �Լ� ��ü�� ��� ������ ȣ�⿡ ���� ���� ���°� �޶����� �ȵȴ�. ��, �Լ� ��ü �ȿ� �ν��Ͻ� ������ �ִ°��� ��Ģ�� �ȵǴ� ���̴�.
	����, �̴� remove_if�� ��� �����ϳĿ� ���� �޶����µ�,  
template <class ForwardIterator, class UnaryPredicate>
ForwardIterator remove_if(ForwardIterator first, ForwardIterator last,
                          UnaryPredicate pred) {
  ForwardIterator result = first;
  while (first != last) {
    if (!pred(*first)) {  // <-- �Լ� ��ü pred �� �����ϴ� �κ�
      *result = std::move(*first);
      ++result;
    }
    ++first;
  }
  return result;
}
	�� ��� pred�� ������� �ʰ� ȣ��Ǿ� ��Ȯ�� ����� ���´�. �ٸ� C++ǥ���� remove_if�� ��� �����϶�� �����ؼ� �Ʒ��� ���� �����Ǿ���.
template <class ForwardIt, class UnaryPredicate>
ForwardIt remove_if(ForwardIt first, ForwardIt last, UnaryPredicate pred) {
  first = std::find_if(first, last, pred);  // <- pred �� �� �����
  if (first != last)
    // �Ʒ� for ���� first + 1 ���� �����Ѵٰ� ���� �ȴ� (++i != last)
    for (ForwardIt i = first; ++i != last;)
      if (!pred(*i))  // <-- pred ȣ�� �ϴ� �κ�
        *first++ = std::move(*i);
  return first;
}
	�� fund_if�� pred�� ���۷����� �޴� ���� �ƴ϶� ������� ������ �ޱ⿡ for������ ���Ҹ� �����ٴ� ������ �Ҹ�Ǿ� num_delete�� �ٽ� 0���� �����ϰ� �ȴ�.
4.	���, num_delete�� ��ü ���� ������ �ƴ� �ܺ� ������ ���� �� ������ �ذ��� �� �ִ�.
	�Ѱ��� ������ ���� STL�� ����� �� ���� �ܺο� Ŭ������ �Լ��� �ϳ��� �������� �Ѵٴ� ���̴�. ��� ���߿� �ڵ尡Ŀ���� ��, �������� ������ �� �־�
	STL�˰��� �� �ȿ� ���� ����� ���� �̻����� ����̴�. 

[3.	���� �Լ�(lambda function)]
1.	[capture list] (�޴� ����)->���� Ÿ��{�Լ� ��ü} ���� ���ǵǸ�, ���� Ÿ���� �����ϸ� �˾Ƽ� �����Ϸ��� ������ ��. but return�� �������� ������ �� ���ٸ� �����Ͽ��� 
	�̴� auto func=�� �޾Ƽ� func(4)ó�� �Լ� ��ü�� ������ �Ŀ� ȣ���� ���� ����. ��, �� �״�� �Լ� ��. 
	 ������, ������ �߻��� ������ �ٽ� ���캸��, �Լ��� ��ȣ���ϸ� �Լ� ���� ������ �����ǵǾ� �ᱹ odd element�� �� �� �������� �𸥴ٴ� ���� ������ �� ������,
	lambda�Լ��� ĸ�� ���(capture list)�� ����Ͽ� �� ������ ������ �� �ִ�. 
2.	���� Ŭ���� �ȿ� ��� �Լ� �ȿ��� ��� ������ ������ ����, ���� �ٸ��� ��ó�� &num_erased��� �ϸ� �ȵȴ�. �츮�� ���� ������ ��ü ���� ����� �����ؾ��ϱ⿡
	�̷��� ��쿣 this�� class��ü�� ��Ÿ���� ����Ѵ�. 
3.	ĸ�ĸ���Ʈ�� ������ ��� ������ �����ϸ�
	-[] �ƹ��͵� ĸ�� ����
	-[&a, b] a�� ���۷����� ĸ��, b�� ���纻���� ĸ��(���� �Ұ���)
	-[&] �ܺ��� ��� �������� ���۷����� ĸ��
	-[=] �ܺ��� ��� �������� ���纻���� ĸ�� 
	
[4.	���� �����ϱ�(transform)]
1.	transform �Լ��� ����Ͽ� ���ҵ��� ����. 
2.	transform(���� �ݺ���, �� �ݺ���, ����� ������ �����̳��� ���� �ݺ���, Pred) 
	
[5.	���Ҹ� Ž���ϴ� �Լ�(find, 'find_if, any_of, all_od' ���)]
1.	template <class InputIt, class T>
	InputIt find(InputIt first, InputIt last, const T& value)
	first~last�� value�� ������ �ִ��� Ȯ���ϰ� ������ �ݺ��� ����. �ߺ��Ǹ� ���� �ֱٲ�. 
2.	find �迭 �Լ����� ����� �� ������ ����, ���� �⺻������ .find�Լ��� �����ȴٸ� �̸� ����ؾ� �� ������. �ֳĸ� �˰����� find�� �����̳��� ������ ������� �ʴ� find�� �����̴�.
	ex) set�� find�� ���ĵǾ��ֱ⿡ O(logn), unordered_set�� find�� �ؽ����̺��� �̿��ϱ⿡ O(1). ���� �˰����� find�� �ϳ��� Ȯ���ϹǷ� O(n).
	 ��, �˰����� find�� vectoró�� find�� �������� �ʴ� �����̳ʿ� �������! 
3.	any_of�� ���ڷ� ���� �������� �ϳ��� �����ϸ� true����, all_of�� ��ΰ� �����ϸ� true�� �����Ѵ�. and�� or�� ����� �����̴�.
 
*/
