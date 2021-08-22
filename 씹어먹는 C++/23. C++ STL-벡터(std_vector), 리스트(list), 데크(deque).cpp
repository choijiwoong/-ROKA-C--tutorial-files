#include <iostream>
#include <vector>
#include <list>

/*1~4
template <typename T>
void print_vector(std::vector<T>& vec){
	//핫윙 먹고싶다...냉동으로 코스트코에 파는뎀...핫소스발라져있고...으헝헝 
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
[0.	들어가기 앞서]
1.	이번 강좌에서 배우게 될 C++의 표준 템플릿 라이브러리 (STL)은 사용하는 것도 엄청 간단한데, 프로그래밍의 능률을 100%향상 시킬 수 있는 엄청난 도구이다.
	사실 이 STL의 도입으로 C++이 한발 더 도약한 것을 과언이 아니라 볼 수 있을 정도이다.

[1.	C++표준 템플릿 라이브러리(Standard Template library-STL)]
1.	C++ 표준 라이브러리에는 꽤나 많은 종류의 라이브러리 들이 있다. 대표적으로 입출력 라이브러리(iostream 등등), 시간 관련 라이브러리(chrono), 정규표현식 라이브러리(regex)등등 들이 있다.
	하지만 보통 C++템플릿 라이브러리(STL)을 일컫는다면 다음의 세 개의 라이브러리들을 의미한다.
	-임의 타입의 객체를 보관할 수 있는 컨테이너(container)_편지함 
	-컨테이너에 보관된 원소에 접근할 수 있는 반복자(iterator)_편지를 보고 원하는 편지함을 찾는 일 
	-반복자들을 가지로 일련의 작업을 수행하는 알고리즘(algorithm)_편지들을 편지함에 날짜 순서로 정렬하여 넣는 일
	 여기서 컨테이너는 템플릿의 특성 덕분에 int나 string뿐만이 아닌 우리가 만든 임의의 클래스여도 자유롭게 위 기능들을 모두 활용할 수 있다. 
	또한 반복자의 도입으로 M종류의 컨테이너, N종류의 알고리즘을 위해 MN개의 알고리즘 코드가 있어야했던 반면에, 최소한의 코드만을 작성할 수 있게 되었다.
	즉, 반복자를 이용하여 컨테이너를 추상화 시켜서 접근할 수 있기에, N개의 알고리즘으로 M종류의 컨테이너들을 모두 지원할 수 있게 되는 것이다.(후에 알고리즘 라이브러리에서 설명) 

[2.	C++ 'STL'컨테이너-벡터(std::vector)]
1.	C++ STL에서 컨테이너는 크게 두 가지 종류가 있는데, 배열처럼 객체들을 순차적으로 보관하는 스퀀스 컨테이너(sequence container)와, 키를 바탕으로 대응되는 값을 찾아주는 연관 컨테이너(associative contatiner)가 있다.
2.	먼저, 시퀀스 컨테이너의 경우 vector, list, deque이렇게 3가지가 정의되어 있고, 먼저 vector의 경우 가변길이 배열이라고 보면 된다.
	벡터에는 원소들이 메모리 상에서 실제로 순차적으로 저장되어 있고, 따라서 임의의 위치에 있는 원소를 접근하는 것을 매우 빠르게 수행할 수 있다.

[3.	정확히 얼마나 빠르다고?]
1.	컴퓨터 공학에선 어떠한 작업의 처리 속도를 복잡도(complexity)라고 부르고, Big O표기법으로 나타낸다. 
	버블 정렬의 경우 최고차항만 나타내어 O(N^2)인데, 큇고트(Quicksort)알고리즘을 활용하면 O(NlogN)의 복잡도로 연산을 할 수 있다. 
	 물론, 퀵소트가 항상 버블정렬보다 빠른것은 아닌데(계수가 얼마나 붙어있는지 모르기에) N이 정말 커진다면 언젠가 퀵소트가 버블정렬보다 더 빨리 수행되는 때가 발생한다.
2.	여기서 vector의 경우, 임의의 위치에 있는 원소에 접근, 추가, 제거를 O(1)로 수행할 수 있다. 또한 배열처럼 []로 접근하거나, at함수를 이용하여 접근이 가능하고, 맨 뒹 원솔르 추가하거나 제거하는데에 push_back혹은 pop_back을 사용하면 된다.
3.	참고로 맨 뒤에 원소를 추가하는 작업은 엄밀히 말하자면 amortized O(1)이라고 하는데(amortized 분할상환) 
	보통 vector의 경우 현재 가지고 있는 원소보다 더 많은 공간을 항당해놓고 있다. 문제는 할당된 공간이 다 찼을 때 인데, 이때는 큰 공간을 다시 할당하고, 기존의 원소들을 복사할 수 밖에 없다. 따라서 n개의 원소를 모두 복사해야하니 O(n)으로 수행된느데,
	이 O(n)으로 수행되는 경우가 매우 드물기 때문에, 전체적인 평균값으로 O(1)으로 수행됨을 알 수있다. 그리하여 amortized O(1)이라고 부른다. 
4.	vector하고 만능은 아닌 것이, 맨 뒤의 원소를 추가하거나 제거하는 것은 빠르지만, 임의의 위치에 원소를 추가하거나 빼는 경우 그 뒤 원소들을 한칸씩 이동시켜야하기에 n번의 복사가 필요하다.
	즉, 맨 뒤가 아닌 위치에 데이터를 추가하거나 제거하는 작업이 많을 경우, vector를 지양해야한다.
5.	결과적으로 vector의 복잡도를 정리하면
	-임의의 위치 원소 접근([], at): O(1)
	-맨 뒤에 원소 추가 및 제거(push_back / pop_back):amortized O(1); (평균적으로 O(1)이지만 최악의 경우 O(n))
	-임의의 위치 원소 추가 및 제거(insert, erase): O(n) 
	위처럼 작업에 따른 속도차이가 크기 때문에 어떠한 작업을 위해 이 컨테이너를 사용할 지 정확히 인지하고 최적의 컨테이너를 골라야 한다.

[4.	반복자(iterator)]
1.	앞서 반복자는 컨테이너에 원소에 접근할 수 있는 포인터와 같은 객체라고 하였다. 벡터의 경우 []말고 반복자를 사용해서도 마찬가지의 작업을 수행할 수 있는데, 후에 설명할 알고리즘 라이브러리의 경우 대부분이 반복자를 인자로 받아 알고리즘을 수행한다. 
2.	반복자는 컨테이너에 iterator멤버 타입으로 정의되어 있는데, vector의 경우 begin()함수(첫원소가리키는 반복자)와 end()함수(마지막 원소 한 칸 뒤를 가리키는 반복자)를 사용할 수 있다.  
	end(0)가 마지막 원소의 뒤를 가리키는 가장 큰 이유는, begin()==end()로 원소가 없는 벡터를 표현할 수 있게 되기 때문이다. 
3.	vector에서 interator로 erase나 insert를 사용할때의 주의점은 컨테이너에 원소를 추가하거나 제거하게 되면 기존에 사용하였던 모든 반복자들을 사용할 수 없게 된다는 것이다. 
4.	vector에서 지원하는 반복자로 const_iterator도 있다. 이는 마치 const포인터를 생각하면 되는데, 가리키고 있는 원소의 값을 바꿀 수 없다.
	이때, 주의할 점은 const반복자의 경우 cbegin()과 cend()함수를 이용한다. 웬만하면 참조값을 바꾸지 않으니 iterator로는 const_iterator을 이용하는 것이 권장된다.
5.	vector에서 지원하는 반복자 중 마지막으로 역반복자(reverse iterator)가 있다.
6.	역으로 접근하는 경우, 통상적인 방법으로 type_size()-1~0으로 하면 오류가 생기므로 무조건 역반복자를 사용하도록 하자. 

[5.	범위 기반 for문(range based for loop)]
1.	컨테이너 원소를 for문드로 접근하는 패턴은 많이 등장하는데, C++부터 이와 같은 패턴을 매우 간단하게 나타내기 위해 범위 기반(range-based) for문을 제공하고있다.
2.	사용은 int elem:vec으로 하고 elements를 elem으로 접근한다. ㅈ된다. 
3.	참고로 앞서 설명한 함수들 말고도 vector에는 수 많은 함수들이 있고, 또 오버로드 되는 여러가지 버전이 있다.(insert만 5개 오버로드)_ https://en.cppreference.com/w/cpp/container/std::vector 참고 

[6.	리스트(list)]
1.	리스트는 양방향 연결 구조를 가진 자료형이다. (start element)1<->2<->3<->4(last element) 
	따라서 vector와는 달리 임의의 위치에 있는 원소에 접근을 바로 할 수 있다. list 컨테이너 자체에서는 시작 원소와 마지막 원소의 위치만을 기억하기 때문에, 임의의 위치에 있는 원소에 접근하기 위해서는 하나씩 링크릉 따라가야 한다. 
	그래서 리스트에는 아예 []나 at함수가 정의되어있지 않다.
	 대신, vector의 경우 맨 뒤를 제외하고는 random location에 insert하거나 erase하는 작업이 O(n)이었지만, 리스트의 경우 O(1)으로 매우 빠르게 수행될 수 있다.
	그 이유는 링크를 기반으로 움직이기에 원하는 위치 앞과 뒤에 있는 링크값만 바꿔주면 되기 때문이다.
2.	list는 한번에 한칸, 왼쪽 혹은 오른쪽으로만 이동이 가능하기에 리스트에서 정의되는 반복자의 타입을 보면 BidirectionalIterator 타입임을 알 수 있다.
	이름 그대로, 양방향으로 이동할 수 있되, 한 칸 씩 이동할 수 있다.
	 반면에 vector는 RandomAccessItertor이다. 즉 임의의 위치에 접근할 수 있는 반복자인 것이다.(p.s RandomAccessIterator는 BidirectionalIterator를 상속받고 있다.)
3.	리스트는 벡터와 다르게, 각 원소들의 주소값들은 바귀지 않기 때문에 원소를 지워도 반복자가 무효화되지 않는다. 

[7.	덱(deque-double ended queue)]
1.	 
*/
