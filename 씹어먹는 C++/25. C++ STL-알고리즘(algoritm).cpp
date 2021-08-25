#include <iostream>
#include <algorithm>
#include <vector> 

template <typename Iter>
void print(Iter begin, Iter end){
	while(begin!=end){
		std::cout<<*begin<<" ";
		begin++;
	}
	std::cout<<std::endl;
}

int main(){
	std::vector<int> vec;
	vec.push_back(5);
	vec.push_back(3);
	vec.push_back(1);
	vec.push_back(6);
	vec.push_back(4);
	vec.push_back(7);
	vec.push_back(2);
	
	std::cout<<"before sort ----"<<std::endl;
	print(vec.begin(), vec.end());
	std::sort(vec.begin(), vec.end());
	
	std::cout<<"after sort ----"<<std::endl;
	print(vec.begin(), vec.end());
	
	
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
1.	
*/
