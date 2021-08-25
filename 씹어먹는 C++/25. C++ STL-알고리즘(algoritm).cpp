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
1.	
*/
