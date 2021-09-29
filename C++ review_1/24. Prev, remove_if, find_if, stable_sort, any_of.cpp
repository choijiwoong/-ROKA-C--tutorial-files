#include <iostream>
#include <algorithm>
#include <vector>
#include <string> 
#include <functional>

/*remove_if
template <typename Iter>
void print(Iter begin, Iter end){
	while(begin!=end){
		std::cout<<"["<<*begin<<"] ";
		begin++;
	}
	std::cout<<std::endl;
}

struct is_odd{
	int* num_delete;//count delete
	
	is_odd(int* num_delete): num_delete(num_delete){}
	
	bool operator()(const int& i){
		if(*num_delete>=2)
			return false;
		if(i%2==1){
			(*num_delete)++;
			return true;
		}
		
		return false;
	}
};

int main(){
	std::vector<int> vec;
	vec.push_back(3);
	vec.push_back(2);
	vec.push_back(0);
	vec.push_back(10);
	vec.push_back(1.5);
	vec.push_back(7);
	
	std::cout<<"initial status of vec---------"<<std::endl;
	print(vec.begin(), vec.end());
	
	std::cout<<"remove two odd elements at first ---"<<std::endl;
	
	//remove_if by lambda
	int num_delete=0;//In remove_if's prev doesn't change inner status because it can copy that object.
	vec.erase(std::remove_if(vec.begin(), vec.end(), is_odd(&num_delete)), vec.end());
	//same
	vec.erase(std::remove_if(vec.begin(), vec.end(),
	[&num_delete](int i){
			if(num_delete>=2)
				return false;
			else if(i%2==1){
				num_delete++;
				return true;
			}
			return false;
		}),
	vec.end());
	
	//transform to all element
	std::transform(vec.begin(), vec.end(), vec.begin(), [](int i){ return i+1; });
	
	print(vec.begin(), vec.end());
}*/

//find, any_of, all_of
template <typename Iter>
void print(Iter begin, Iter end){
	while(begin!=end){
		std::cout<<"["<<*begin<<"] ";
		begin++;
	}
	std::cout<<std::endl;
}

struct User{
	std::string name;
	int level;
	
	User(std::string name, int level): name(name), level(level){}
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
			if(std::find(users.begin(), users.end(), new_user)!=users.end())
				return false;
			users.push_back(new_user);
			return true;
		}
		
		bool can_join_dungeon(){
			return std::all_of(users.begin(), users.end(), [](User& user){ return user.level>=15;});
		}
		
		bool can_use_special_item(){
			return std::any_of(users.begin(), users.end(), [](User& user){ return user.level>=19;});
		}
};

int main(){
	Party party;
	party.add_user("our class", 11);
	party.add_user("is bomb", 12);
	party.add_user("managers are", 13);
	party.add_user("mad at cheap", 20);
	
	std::cout<<std::boolalpha;
	std::cout<<"can join? : "<<party.can_join_dungeon()<<std::endl;
	std::cout<<"can use?: "<<party.can_use_special_item()<<std::endl;
}

/*
1.	algorithms라이브러리에 보통 iterator를 전달하고 특정한 조건을 의미하는 서술자(Predicate)로 Functor를 넣는다.
2.	sort, stable_sort, partial_sort on RandomAccessIterator
3.	vec.erase(remove(vec.begin(), vec.end(), 3), vec.end()); remove는 실제 delete가 아닌 이동을 시켜준다. 고로 값이 3인걸 뒤로 보내고 그 원소들을 삭제한다. 
4.	람다함수는 [capture list] (argument) -> return_type { body }로 구성된다. 
5.	container의 원소에 일괄적으로 적용하는 작업은 transform함수를 이용한다. 
	transform(시작 반복자, 끝 반복자, 결과저장컴테이너 시작 반복자, pred) 
6.	find, find_if, any_of(or), all_of(and)
*/
