#include <iostream>
#include <vector>
#include <list>

/*1~4
template <typename T>
void print_vector(std::vector<T>& vec){
	//���� �԰�ʹ�...�õ����� �ڽ�Ʈ�ڿ� �Ĵµ�...�ּҽ��߶����ְ�...������ 
	for(typename std::vector<T>::iterator itr=vec.begin(); itr!=vec.end(); ++itr)//typename must be needed because iterator is dependent type of std::vector<T>.
		std::cout<<*itr<<std::endl; 
}

int main(){
	//make vector
	std::vector<int> vec;
	vec.push_back(10);//add at back
	vec.push_back(20);
	vec.push_back(30);
	vec.push_back(40);
	
	//print vector by int i that is size_type
	//size()'s return type is saved in size_type
	std::cout<<"<print vector by using size_type i>"<<std::endl;
	for(std::vector<int>::size_type i=0; i<vec.size(); i++)
		std::cout<<"vec's "<<i+1<<"th element :: "<<vec[i]<<std::endl;
	std::cout<<std::endl<<std::endl;	
	
	//print vector by iterator
	std::cout<<"<print vector by using iterator itr>"<<std::endl;
	for(std::vector<int>::iterator itr=vec.begin(); itr!=vec.end(); ++itr)//itr acts like address So, for read value, write with *
		std::cout<<*itr<<std::endl;//itr is not pointer! just operator* overloading for using like pointer. Actually, *itr return reference of random element.
	std::cout<<std::endl<<std::endl;
	
	//int arr[4]={10, 20, 30, 40};
	//*(arr+2)==arr[2]==30;
	//*(itr+2)==vec[2]==30; all same
	
	//access random location of vector by begin()+ operation
	std::cout<<"<print 3nd element by vec.begin()+2>"<<std::endl;
	std::vector<int>::iterator itr=vec.begin()+2;
	std::cout<<"3nd element :: "<<*itr<<std::endl<<std::endl;
	
	//how to use insert and erase?
	std::cout<<"<use insert & erase>"<<std::endl;
	std::cout<<"initial vector status"<<std::endl;
	print_vector(vec);//we make template function for convenience
	std::cout<<std::endl;
	
	//insert(address, value)
	std::cout<<"insert 15 to begin()+2"<<std::endl;
	vec.insert(vec.begin()+2, 15);
	print_vector(vec);
	std::cout<<std::endl;
	
	//erase(address)
	std::cout<<"erase vec.begin()+3"<<std::endl;
	vec.erase(vec.begin()+3);
	print_vector(vec);
	std::cout<<std::endl;
	//insert & erase are O(n). it's slow.
	
	//we can think that same code will work with variables that have vec.begin() and vec.end(). but it occur error when element's value are changed.
	std::vector<int>::iterator itr1=vec.begin();
	std::vector<int>::iterator end_itr=vec.end();
	
	//without itr1=vec.begin() command, it occurs error because itr1 becomes trash iterator thanks to changing of element's value
	for(; itr1!=end_itr; ++itr1){//so itr1!=end_itr are infinitely true->infinite loof error
		if(*itr1==20){
			vec.erase(itr1);//error occur! if vector's elements are changed, than we cannot use initial iterator like itr1, end_itr.
			itr1=vec.begin();//can solve this problem! but it's not efficient because it find 20 at first. so
		}
	}
	
	//upgrade upper way that dosen't check location continuously.
	for(std::vector<int>::size_type i=0; i!=vec.size(); i++){//this way is much better.
		if(vec[i]==20){
			vec.erase(vec.begin()+i);//just input vec.begin() in erase!
			i--;//have to check same location because there is not same element now.
		}
	}//but this isn't good way because it's just access by int i like normal array. not by iterator itself.
	//erase result print part
	std::cout<<"erase element that has 20!"<<std::endl;
	print_vector(vec);
	std::cout<<std::endl;
	
	//const iterator can't change value! 
	vec.push_back(35);
	vec.insert(vec.begin()+1,5);//less element,,,so add
	std::cout<<"initial vector status"<<std::endl;
	print_vector(vec);
	//normal iterator can change value of element
	std::vector<int>::iterator itr2=vec.begin()+2;
	*itr2=50;//in here
	std::cout<<"----------------"<<std::endl;
	print_vector(vec);
	std::cout<<std::endl;//show changed value after *itr2=50
	
	//show const_iterator can't change value and just read value.
	std::vector<int>::const_iterator citr=vec.cbegin()+2;//const_iterator! only read. vec.cbegin() used! not begin and also we use vec.cend()
	//*citr=30;//impossible! because const_iterator can't change value of element 
	std::cout<<*citr<<std::endl;//read is possible in const_iterator ofcoursely!
	//it must use cbegin and cend
	
	//reverse iterator use!
	std::cout<<"----------------"<<std::endl;
	std::cout<<"print vec reversely"<<std::endl;
	std::vector<int>::reverse_iterator r_iter=vec.rbegin();//and it also has const_reverse_iterator with crbegin(), crend().
	for(; r_iter!=vec.rend(); r_iter++)//++ direction important! vec.rend() points before first element like vec.end().
		std::cout<<*r_iter<<std::endl; 
	//it must use rbegin like cbegin
	
	//importance of reverse_iterator
	for(std::vector<int>::size_type i=vec.size()-1; i>=0; i--)//common way that we think to access vector reversely.
		std::cout<<vec[i]<<std::endl;//error occur! because vector's index type is unsigned int type!
	//so if we i-- when i==0, it's not -1, is the biggest integer at that type. so for condition can't be stopped.
	//for solve this problem, we have to define index to signed int. but it occur problem that we have to type casting because vector's index are diferent to signed int.
	//so when we have to access reversely, just use reverse_iterator!!
	
	return 0;	
}*/

/*5
//code is too long,,so cut! with intention of practice.
template <typename T>
void print_vector(std::vector<T>& vec){
	for(typename std::vector<T>::iterator itr=vec.begin(); itr!=vec.end(); ++itr)
		std::cout<<*itr<<std::endl;
}

template <typename T>
void print_vector_range_based(std::vector<T>& vec){
	for(const auto& elem:vec)//range-based used(feat. auto keyword & const keyword)
		std::cout<<elem<<std::endl;//it access vec's element by using const reference. so intuitive! this is adventage of 'range-based for sentenct'
}

int main(){
	std::vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	
	//range-based for block sentence by copy
	for(int elem:vec)//vec's element is copied at elem each loof. like elem=vec[i]. without ';'
		std::cout<<"element : "<<elem<<std::endl;
	
	//print vector by using iterator and range-based for
	std::cout<<"print_vector"<<std::endl;
	print_vector(vec);
	std::cout<<"print_vector_range_based"<<std::endl;
	print_vector_range_based(vec);//same print result with upper code that use iterator!
	
	return 0;
} */

//6. list 

template <typename T>
void print_list(std::list<T>& lst){
	std::cout<<"[ ";
	for(const auto& elem:lst)//use range-based for sentence to print list!(feat. auto & const keyword)
		std::cout<<elem<<" ";
	std::cout<<"]"<<std::endl;
} 

int main(){
	std::list<int> lst;
	
	lst.push_back(10);
	lst.push_back(20);
	lst.push_back(30);
	lst.push_back(40);//(o mo na push_front is exist!)
	
	//list can print like vector with iterator.
	for(std::list<int>::iterator itr=lst.begin(); itr!=lst.end(); ++itr)
		std::cout<<*itr<<std::endl;//completely print! like vector print.
	//but itr can only operate like itr++ or itr--(coursely, possible to prefix operator), can't access randomly like itr+5!
	//only move one space like itr++.
	//list can move left or right. it means elements can locate discontinuously. Unlike vector that can refer random element because of it's continuity.
	
	//list's insert and erase
	std::cout<<"initial list's status"<<std::endl;
	print_list(lst);
	
	for(std::list<int>::iterator itr=lst.begin(); itr!=lst.end(); ++itr){//itr can only ++ and -- operate!
		if(*itr==20)
			lst.insert(itr, 50);//work fast O(1) unlike vector!
	}
	std::cout<<"add 50 infront of element that has 20"<<std::endl;
	print_list(lst);
	
	for(std::list<int>::iterator itr=lst.begin(); itr!=lst.end(); ++itr){
		if(*itr==30){
			lst.erase(itr);//itr is not invalidated when we erase element because each address of elements isn't changed thanks to link structure. 
			break;//for prevent unnessesary calculation.
		}
	}
	std::cout<<"erase element that has 30"<<std::endl;
	print_list(lst);

}

/*
[0.	���� �ռ�]
1.	�̹� ���¿��� ���� �� C++�� ǥ�� ���ø� ���̺귯�� (STL)�� ����ϴ� �͵� ��û �����ѵ�, ���α׷����� �ɷ��� 100%��� ��ų �� �ִ� ��û�� �����̴�.
	��� �� STL�� �������� C++�� �ѹ� �� ������ ���� ������ �ƴ϶� �� �� ���� �����̴�.

[1.	C++ǥ�� ���ø� ���̺귯��(Standard Template library-STL)]
1.	C++ ǥ�� ���̺귯������ �ϳ� ���� ������ ���̺귯�� ���� �ִ�. ��ǥ������ ����� ���̺귯��(iostream ���), �ð� ���� ���̺귯��(chrono), ����ǥ���� ���̺귯��(regex)��� ���� �ִ�.
	������ ���� C++���ø� ���̺귯��(STL)�� ���´´ٸ� ������ �� ���� ���̺귯������ �ǹ��Ѵ�.
	-���� Ÿ���� ��ü�� ������ �� �ִ� �����̳�(container)_������ 
	-�����̳ʿ� ������ ���ҿ� ������ �� �ִ� �ݺ���(iterator)_������ ���� ���ϴ� �������� ã�� �� 
	-�ݺ��ڵ��� ������ �Ϸ��� �۾��� �����ϴ� �˰���(algorithm)_�������� �����Կ� ��¥ ������ �����Ͽ� �ִ� ��
	 ���⼭ �����̳ʴ� ���ø��� Ư�� ���п� int�� string�Ӹ��� �ƴ� �츮�� ���� ������ Ŭ�������� �����Ӱ� �� ��ɵ��� ��� Ȱ���� �� �ִ�. 
	���� �ݺ����� �������� M������ �����̳�, N������ �˰����� ���� MN���� �˰��� �ڵ尡 �־���ߴ� �ݸ鿡, �ּ����� �ڵ常�� �ۼ��� �� �ְ� �Ǿ���.
	��, �ݺ��ڸ� �̿��Ͽ� �����̳ʸ� �߻�ȭ ���Ѽ� ������ �� �ֱ⿡, N���� �˰������� M������ �����̳ʵ��� ��� ������ �� �ְ� �Ǵ� ���̴�.(�Ŀ� �˰��� ���̺귯������ ����) 

[2.	C++ 'STL'�����̳�-����(std::vector)]
1.	C++ STL���� �����̳ʴ� ũ�� �� ���� ������ �ִµ�, �迭ó�� ��ü���� ���������� �����ϴ� ������ �����̳�(sequence container)��, Ű�� �������� �����Ǵ� ���� ã���ִ� ���� �����̳�(associative contatiner)�� �ִ�.
2.	����, ������ �����̳��� ��� vector, list, deque�̷��� 3������ ���ǵǾ� �ְ�, ���� vector�� ��� �������� �迭�̶�� ���� �ȴ�.
	���Ϳ��� ���ҵ��� �޸� �󿡼� ������ ���������� ����Ǿ� �ְ�, ���� ������ ��ġ�� �ִ� ���Ҹ� �����ϴ� ���� �ſ� ������ ������ �� �ִ�.

[3.	��Ȯ�� �󸶳� �����ٰ�?]
1.	��ǻ�� ���п��� ��� �۾��� ó�� �ӵ��� ���⵵(complexity)��� �θ���, Big Oǥ������� ��Ÿ����. 
	���� ������ ��� �ְ����׸� ��Ÿ���� O(N^2)�ε�, ţ��Ʈ(Quicksort)�˰����� Ȱ���ϸ� O(NlogN)�� ���⵵�� ������ �� �� �ִ�. 
	 ����, ����Ʈ�� �׻� �������ĺ��� �������� �ƴѵ�(����� �󸶳� �پ��ִ��� �𸣱⿡) N�� ���� Ŀ���ٸ� ������ ����Ʈ�� �������ĺ��� �� ���� ����Ǵ� ���� �߻��Ѵ�.
2.	���⼭ vector�� ���, ������ ��ġ�� �ִ� ���ҿ� ����, �߰�, ���Ÿ� O(1)�� ������ �� �ִ�. ���� �迭ó�� []�� �����ϰų�, at�Լ��� �̿��Ͽ� ������ �����ϰ�, �� �� ���ָ� �߰��ϰų� �����ϴµ��� push_backȤ�� pop_back�� ����ϸ� �ȴ�.
3.	����� �� �ڿ� ���Ҹ� �߰��ϴ� �۾��� ������ �����ڸ� amortized O(1)�̶�� �ϴµ�(amortized ���һ�ȯ) 
	���� vector�� ��� ���� ������ �ִ� ���Һ��� �� ���� ������ �״��س��� �ִ�. ������ �Ҵ�� ������ �� á�� �� �ε�, �̶��� ū ������ �ٽ� �Ҵ��ϰ�, ������ ���ҵ��� ������ �� �ۿ� ����. ���� n���� ���Ҹ� ��� �����ؾ��ϴ� O(n)���� ����ȴ���,
	�� O(n)���� ����Ǵ� ��찡 �ſ� �幰�� ������, ��ü���� ��հ����� O(1)���� ������� �� ���ִ�. �׸��Ͽ� amortized O(1)�̶�� �θ���. 
4.	vector�ϰ� ������ �ƴ� ����, �� ���� ���Ҹ� �߰��ϰų� �����ϴ� ���� ��������, ������ ��ġ�� ���Ҹ� �߰��ϰų� ���� ��� �� �� ���ҵ��� ��ĭ�� �̵����Ѿ��ϱ⿡ n���� ���簡 �ʿ��ϴ�.
	��, �� �ڰ� �ƴ� ��ġ�� �����͸� �߰��ϰų� �����ϴ� �۾��� ���� ���, vector�� �����ؾ��Ѵ�.
5.	��������� vector�� ���⵵�� �����ϸ�
	-������ ��ġ ���� ����([], at): O(1)
	-�� �ڿ� ���� �߰� �� ����(push_back / pop_back):amortized O(1); (��������� O(1)������ �־��� ��� O(n))
	-������ ��ġ ���� �߰� �� ����(insert, erase): O(n) 
	��ó�� �۾��� ���� �ӵ����̰� ũ�� ������ ��� �۾��� ���� �� �����̳ʸ� ����� �� ��Ȯ�� �����ϰ� ������ �����̳ʸ� ���� �Ѵ�.

[4.	�ݺ���(iterator)]
1.	�ռ� �ݺ��ڴ� �����̳ʿ� ���ҿ� ������ �� �ִ� �����Ϳ� ���� ��ü��� �Ͽ���. ������ ��� []���� �ݺ��ڸ� ����ؼ��� ���������� �۾��� ������ �� �ִµ�, �Ŀ� ������ �˰��� ���̺귯���� ��� ��κ��� �ݺ��ڸ� ���ڷ� �޾� �˰����� �����Ѵ�. 
2.	�ݺ��ڴ� �����̳ʿ� iterator��� Ÿ������ ���ǵǾ� �ִµ�, vector�� ��� begin()�Լ�(ù���Ұ���Ű�� �ݺ���)�� end()�Լ�(������ ���� �� ĭ �ڸ� ����Ű�� �ݺ���)�� ����� �� �ִ�.  
	end(0)�� ������ ������ �ڸ� ����Ű�� ���� ū ������, begin()==end()�� ���Ұ� ���� ���͸� ǥ���� �� �ְ� �Ǳ� �����̴�. 
3.	vector���� interator�� erase�� insert�� ����Ҷ��� �������� �����̳ʿ� ���Ҹ� �߰��ϰų� �����ϰ� �Ǹ� ������ ����Ͽ��� ��� �ݺ��ڵ��� ����� �� ���� �ȴٴ� ���̴�. 
4.	vector���� �����ϴ� �ݺ��ڷ� const_iterator�� �ִ�. �̴� ��ġ const�����͸� �����ϸ� �Ǵµ�, ����Ű�� �ִ� ������ ���� �ٲ� �� ����.
	�̶�, ������ ���� const�ݺ����� ��� cbegin()�� cend()�Լ��� �̿��Ѵ�. �����ϸ� �������� �ٲ��� ������ iterator�δ� const_iterator�� �̿��ϴ� ���� ����ȴ�.
5.	vector���� �����ϴ� �ݺ��� �� ���������� ���ݺ���(reverse iterator)�� �ִ�.
6.	������ �����ϴ� ���, ������� ������� type_size()-1~0���� �ϸ� ������ ����Ƿ� ������ ���ݺ��ڸ� ����ϵ��� ����. 

[5.	���� ��� for��(range based for loop)]
1.	�����̳� ���Ҹ� for����� �����ϴ� ������ ���� �����ϴµ�, C++���� �̿� ���� ������ �ſ� �����ϰ� ��Ÿ���� ���� ���� ���(range-based) for���� �����ϰ��ִ�.
2.	����� int elem:vec���� �ϰ� elements�� elem���� �����Ѵ�. ���ȴ�. 
3.	����� �ռ� ������ �Լ��� ���� vector���� �� ���� �Լ����� �ְ�, �� �����ε� �Ǵ� �������� ������ �ִ�.(insert�� 5�� �����ε�)_ https://en.cppreference.com/w/cpp/container/std::vector ���� 

[6.	����Ʈ(list)]
1.	����Ʈ�� ����� ���� ������ ���� �ڷ����̴�. (start element)1<->2<->3<->4(last element) 
	���� vector�ʹ� �޸� ������ ��ġ�� �ִ� ���ҿ� ������ �ٷ� �� �� �ִ�. list �����̳� ��ü������ ���� ���ҿ� ������ ������ ��ġ���� ����ϱ� ������, ������ ��ġ�� �ִ� ���ҿ� �����ϱ� ���ؼ��� �ϳ��� ��ũ�� ���󰡾� �Ѵ�. 
	�׷��� ����Ʈ���� �ƿ� []�� at�Լ��� ���ǵǾ����� �ʴ�.
	 ���, vector�� ��� �� �ڸ� �����ϰ�� random location�� insert�ϰų� erase�ϴ� �۾��� O(n)�̾�����, ����Ʈ�� ��� O(1)���� �ſ� ������ ����� �� �ִ�.
	�� ������ ��ũ�� ������� �����̱⿡ ���ϴ� ��ġ �հ� �ڿ� �ִ� ��ũ���� �ٲ��ָ� �Ǳ� �����̴�.
2.	list�� �ѹ��� ��ĭ, ���� Ȥ�� ���������θ� �̵��� �����ϱ⿡ ����Ʈ���� ���ǵǴ� �ݺ����� Ÿ���� ���� BidirectionalIterator Ÿ������ �� �� �ִ�.
	�̸� �״��, ��������� �̵��� �� �ֵ�, �� ĭ �� �̵��� �� �ִ�.
	 �ݸ鿡 vector�� RandomAccessItertor�̴�. �� ������ ��ġ�� ������ �� �ִ� �ݺ����� ���̴�.(p.s RandomAccessIterator�� BidirectionalIterator�� ��ӹް� �ִ�.)
3.	����Ʈ�� ���Ϳ� �ٸ���, �� ���ҵ��� �ּҰ����� �ٱ��� �ʱ� ������ ���Ҹ� ������ �ݺ��ڰ� ��ȿȭ���� �ʴ´�. 

[7.	��(deque-double ended queue)]
1.	 
*/
