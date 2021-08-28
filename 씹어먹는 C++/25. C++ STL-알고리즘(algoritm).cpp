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
	//very good way! but it doesn't allow in C++ ㅋ TT but it's solution is made in C++ 11!
	
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
[0.	들어가기에 앞서]
1.	컨데이너에 반복자를 가지로 쉽게 사용하게 도와주는 것이 알고리즘 라이브러리인데, 여기에 정의되어 있는 여러 함수들로 작업을 수행한다.
	template <typename Iter>
	void do_something(Iter begin, Iter end);//get iterator's start and end
	혹은
	template <typename Iter, typename Pred>
	void do_something(Iter begin, Iter end, Prd pred)//get iterator's start and end with 'special condition' that's called Predicate
	꼴을 따른다. 
	이때 특정한 조건을 서술자(Predicate)라고 부르며 pred에는 보통 bool을 return하는 Functor(함수 객체)를 전달하게 된다.

[1.	정렬(sort, stable_sort, partial_sort)]_노말정렬, 정렬시 값 같으면 순서보존, 일부분만 정렬 
1.	std::sort(vec.begin(), vec.end())는 RandomAccessIterator가 지원되는 deque와 vector만 가능하다.
	또한 만약 내림차순으로 정렬하고 싶다면, compare을 어떻게 할 것인지를 인자로 넘겨주면 된다. 
2.	stable_sort는 sort는 정렬 과정에서 원소들간의 상대적 위치를 바꾸는것과는 달리 처음 상태 그대로 유지한다.
	고로 조금 더 시간이 걸리는데, C++표준에 따르면, 최악의 경우 sort는 O(nlogn)인 반면, stable_sort는 O(n(log n)^2)이다.
	
[2.	원소 제거(remove, remove_if)]
1.	대부분의 컨테이너에서 원소를 제거하는 함수를 지원하고 있지만, 원소가 제거될 때 마다 기존에 제거하였던 반복자들이 초기화되기에 해당 위치를 가리키는 반복자를 계속 다시 가져와야 했다.
	std::vector<int>::iterator itr=vec.begin();
	for(; itr!=vec.end(); ++itr){
		if(*itr==3){
			vec.erase(itr);
			itr=vec.begin();
		}
	}
2.	remove_if 함수는 함수 객체가 인자를 딱 1개받는다고 가정했는데, 이럼 호출되는 operator()을 통해서는 원소에 대한 정보 말고는 추가적인 정보르 전달하기 어렵다. 
	고로 홀수인 원소들을 삭제하되 처음 2개만 삭제하는 예제를 만들어보자. 
	 함수객체의 경우 말 그대로 객체이기에 멤버변수를 생각할 수 있다! 
3.	remove_if를 실제로 구현했을 때, 함수 객체가 여러번 복사될 수 있기 때문에 remove_if에 전달되는 함수 객체의 경우 이전의 호출에 의해 내부 상태가 달라지면 안된다. 즉, 함수 객체 안에 인스턴스 변수를 넣는것은 원칙상 안되는 것이다.
	물론, 이는 remove_if를 어떻게 구현하냐에 따라서 달라지는데,  
template <class ForwardIterator, class UnaryPredicate>
ForwardIterator remove_if(ForwardIterator first, ForwardIterator last,
                          UnaryPredicate pred) {
  ForwardIterator result = first;
  while (first != last) {
    if (!pred(*first)) {  // <-- 함수 객체 pred 를 실행하는 부분
      *result = std::move(*first);
      ++result;
    }
    ++first;
  }
  return result;
}
	의 경우 pred가 복사되지 않고 호출되어 정확히 결과가 나온다. 다만 C++표준은 remove_if를 어떻게 구현하라고 안정해서 아래와 같이 구현되었다.
template <class ForwardIt, class UnaryPredicate>
ForwardIt remove_if(ForwardIt first, ForwardIt last, UnaryPredicate pred) {
  first = std::find_if(first, last, pred);  // <- pred 한 번 복사됨
  if (first != last)
    // 아래 for 문은 first + 1 부터 시작한다고 봐도 된다 (++i != last)
    for (ForwardIt i = first; ++i != last;)
      if (!pred(*i))  // <-- pred 호출 하는 부분
        *first++ = std::move(*i);
  return first;
}
	이 fund_if가 pred의 레퍼런스를 받는 것이 아니라 복사생성 버전을 받기에 for문에서 원소를 지웠다는 정보가 소멸되어 num_delete가 다시 0부터 시작하게 된다.
4.	고로, num_delete를 객체 내부 변수가 아닌 외부 변수로 빼야 이 문제를 해결할 수 있다.
	한가지 안좋은 점은 STL을 사용할 때 마다 외부에 클래스나 함수를 하나씩 만들어줘야 한다는 것이다. 고로 나중에 코드가커졌을 때, 가독성이 떨어질 수 있어
	STL알고리즘 그 안에 직접 써놓는 것이 이상적인 방법이다. 

[3.	람다 함수(lambda function)]
1.	[capture list] (받는 인자)->리턴 타입{함수 본체} 으로 정의되며, 리턴 타입을 생략하면 알아서 컴파일러가 추측해 줌. but return이 여러개여 추측할 수 없다면 컴파일오류 
	이는 auto func=로 받아서 func(4)처럼 함수 객체를 생성한 후에 호출할 수도 있음. 즉, 말 그대로 함수 임. 
	 하지만, 위에서 발생한 문제를 다시 살펴보면, 함수를 재호출하면 함수 안의 변수가 재정의되어 결국 odd element를 몇 개 지웠는지 모른다는 점이 여전할 것 같지만,
	lambda함수는 캡쳐 목록(capture list)를 사용하여 그 변수에 접근할 수 있다. 
2.	만약 클래스 안에 멤버 함수 안에서 멤버 변수를 참조할 때는, 조금 다른게 위처럼 &num_erased라고 하면 안된다. 우리는 실제 생성된 객체 안의 멤버를 참조해야하기에
	이러한 경우엔 this로 class자체를 나타내어 사용한다. 
3.	캡쳐리스트의 사용법은 몇개만 간단히 정리하면
	-[] 아무것도 캡쳐 안함
	-[&a, b] a는 레퍼런스로 캡쳐, b는 복사본으로 캡쳐(변경 불가능)
	-[&] 외부의 모든 변수들을 레퍼런스로 캡쳐
	-[=] 외부의 모든 변수들을 복사본으로 캡쳐 
	
[4.	원소 수정하기(transform)]
1.	transform 함수를 사용하여 원소들을 수정. 
2.	transform(시작 반복자, 끝 반복자, 결과를 저장할 컨테이너의 시작 반복자, Pred) 
	
[5.	원소를 탐색하는 함수(find, 'find_if, any_of, all_od' 등등)]
1.	template <class InputIt, class T>
	InputIt find(InputIt first, InputIt last, const T& value)
	first~last중 value와 같은게 있는지 확인하고 있으면 반복자 리턴. 중복되면 가장 최근꺼. 
2.	find 계열 함수들을 사용할 때 주의할 점은, 만약 기본적으로 .find함수가 지원된다면 이를 사용해야 더 빠르다. 왜냐면 알고리즘의 find는 컨테이너의 구조를 고려하지 않는 find기 때문이다.
	ex) set의 find는 정렬되어있기에 O(logn), unordered_set의 find는 해시테이블을 이용하기에 O(1). 만약 알고리즘의 find는 하나씩 확인하므로 O(n).
	 즉, 알고리즘의 find는 vector처럼 find를 지원하지 않는 컨테이너에 사용하자! 
3.	any_of는 인자로 받은 범위에서 하나라도 충족하면 true리턴, all_of는 모두가 충족하면 true를 리턴한다. and와 or과 비슷한 느낌이다.
 
*/
