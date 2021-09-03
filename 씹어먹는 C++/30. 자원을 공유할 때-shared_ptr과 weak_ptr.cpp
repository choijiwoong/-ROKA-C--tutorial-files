#include <iostream>
#include <memory>
#include <vector>

/*1, 3
class A>{
	int *data;
	
	public:
		A(){
			data=new int[100];
			std::cout<<"get resource!"<<std::endl;
		}
		~A(){
			std::cout<<"call destructor!"<<std::endl;
			delete[] data;
		}
		
		//for show show situation we have to create shared_ptr by address.
		std::shared_ptr<A> get_shared_ptr(){ return std::shared_ptr<A>(this); }//doesn't know reference count because it's in local function! it doesn't know how many shared_ptr exist in whole code.
}; 

int main(){
	std::vector<std::shared_ptr<A>> vec;
	
	vec.emplace_back(std::shared_ptr<A>(new A()));//use emplace_back instead of push_back for fun & understanding
	vec.push_back(std::shared_ptr<A>(vec[0]));
	vec.push_back(std::shared_ptr<A>(vec[1]));
	std::cout<<"reference count: "<<vec[0].use_count()<<std::endl;
	
	std::cout<<"destroy first element!"<<std::endl;
	vec.erase(vec.begin());
	std::cout<<"reference count: "<<vec[0].use_count()<<std::endl;
	
	std::cout<<"destroy next element!"<<std::endl;
	vec.erase(vec.begin());
	std::cout<<"reference count: "<<vec[0].use_count()<<std::endl;
	
	std::cout<<"destroy last element!"<<std::endl;
	vec.erase(vec.begin());
	std::cout<<"reference count: "<<vec[0].use_count()<<std::endl;
	//call destructor after last erase. reference count is 3->2->1->0. we can check reference count by using use_count function.
	
	std::cout<<"exit program!"<<std::endl<<std::endl;
	
	
	//for show warning point of using shared_ptr
	A* a=new A();
	
	std::shared_ptr<A> pa1(a);
	std::shared_ptr<A> pa2(a);//not std::shared_ptr<A> pa2(pa1);
	//pa2 makes another control block so it doesn't know correct reference count. 
	
	std::cout<<pa1.use_count()<<std::endl;//1
	std::cout<<pa2.use_count()<<std::endl<<std::endl;//1
	
	//while exiting this program, destructor of a called twice, so error occur that double free.
	//for avoid this situation, we have not to create shared_ptr by adress.
	//But, there are situation we have to create shared_ptr by address.
	
	
	//for show situation we have to create shared_ptr by address.
	std::shared_ptr<A> PA1=std::make_shared<A>();
	std::shared_ptr<A> PA2=PA1->get_shared_ptr();
	
	std::cout<<PA1.use_count()<<std::endl;
	std::cout<<PA2.use_count()<<std::endl;
	//while exiting this program, occur same error. double free
	//member function doesn't know how many shared_ptr exist in program.
	//we can solve this problem by enable_shared_from_this
}*/

/*3 enable_shared_from_this
class A : public std::enable_shared_from_this<A>{//inheritance for making shared_ptr by this
	int *data;
	
	public:
		A(){
			data=new int[100];
			std::cout<<"get resource!"<<std::endl;
		}
		~A(){
			std::cout<<"call destructor!"<<std::endl;
			delete[] data;
		}
		std::shared_ptr<A> get_shared_ptr_enable(){ return shared_from_this(); } //use shared_from_this() instead of 'return std::shared_ptr<A>(this);'
		//shared_from_this function(member function of enable_shared_from_this class) creates shared_ptr by using predefined control block for prevention of creating two control block to same object.
};

int main(){
	std::shared_ptr<A> pa1=std::make_shared<A>();//(instead of std::shared_ptr<A> pa1(new A()) for efficiency of allocation.)
	std::shared_ptr<A> pa2=pa1->get_shared_ptr_enable();
	
	std::cout<<pa1.use_count()<<std::endl;//2 not 1
	std::cout<<pa2.use_count()<<std::endl;//2 not 1
}*/

/*4
class A{
	int *data;
	std::shared_ptr<A> other;
	
	public:
		A(){
			data=new int[100];
			std::cout<<"get resource!"<<std::endl;
		}
		~A(){
			std::cout<<"call destructor!"<<std::endl;
			delete[] data;
		}
		void set_other(std::shared_ptr<A> o) { other=o; }
}; 

int main(){
	std::shared_ptr<A> pa=std::make_shared<A>();
	std::shared_ptr<A> pb=std::make_shared<A>();
	
	pa->set_other(pb);//pa's other points pb's other
	pb->set_other(pa);//pb's other points pa's other
	//curcular reference!
	//not call desturctor after exiting program.
}*/


//5
class A{
	std::string s;
	std::weak_ptr<A> other;
	
	public:
		A(const std::string& s):s(s){ std::cout<<"ger resource!"<<std::endl; }
		~A(){ std::cout<<"call destructor!"<<std::endl;}
		void set_other(std::weak_ptr<A> o){ other = o;}//make smart pointer for argument that doesn't add reference count
		void access_other(){
			std::shared_ptr<A> o=other.lock();//we can't refer element with weak_ptr. so convert by using .lock()
			if(o)//object exist in memory 
				std::cout<<"access : "<<o->name()<<std::endl;
			else//object doesn't exist in memory. (lock function return empty shared_ptr)
				std::cout<<"already freed TT"<<std::endl;
		}
		std::string name(){ return s; }
}; 

int main(){
	std::vector<std::shared_ptr<A>> vec;
	vec.push_back(std::make_shared<A>("resource 1"));
	vec.push_back(std::make_shared<A>("resource 2"));
	
	vec[0]->set_other(vec[1]);
	vec[1]->set_other(vec[0]);
	
	//reference coun of pa & pb is like that
	std::cout<<"vec[0] reference count : "<<vec[0].use_count()<<std::endl;
	std::cout<<"vec[1] reference count : "<<vec[1].use_count()<<std::endl;
	
	//access that object with weak_ptr
	vec[0]->access_other();
	
	//remove last element(vec[1])
	vec.pop_back();
	vec[0]->access_other();
}


/*
[0.	들어가기에 앞서]
1.	대부분 하나의 자원은 하나의 스마트 포인터에 의해 소유되는 것이 바람직하여 나머지 접근은 소유가 아닌 일반 포인터로 처리하면 된다.
	하지만 여러 객체에서 하나의 자원을 사용할 때 여러개의 스마트 포인터가 하나의 객체를 같이 소유해야하는 경우도 발생한다.
	이러한 경우엔 사용 후 자원을 사용하는 모든 객체들이 소멸되야 하는데, 어떤 객체가 먼저 소멸됬는지 모르기에 자원을 해제시켜야하는 타이밍을 놓치게 된다.
	 이 경우, 좀 더 스마트한 포인터를 이용하여 특정 자원을 몇 개의 객체에서 가리키는지를 추적한 다음, 그 수가 0이 될때 비로소 해제를 시켜주는 방식의 포인터가 필요하다.

[1.	shared_ptr]
1.	case shared_ptr:
		std::shared_ptr<A> p1(new A());
		std::shared_ptr<A> p2(p1);
	case unique_ptr;
		std::unique_ptr<A> p1(new A());
		std::unique_ptr<A> p2(p1);//compile error
	여러개의 shared_ptr은 같은 객체를 동시에 가리킬 수 있다. 
2.	memory free를 위해 참조 개수(reference count)를 알아야 한다. 0이 되어야 해제를 할 수 있기 때문이다. 
	reference count는 use_count function을 통해 알 수 있다.
3.	std::shared_ptr<A> p1(new A());
	std::shared_ptr<A> p2(p1);
	
	std::cout<<p1.use_count();//2
	std::cout<<p2.use_count();//2
	어떻게 같은 객체를 가리키는 shared_ptr끼리 동기화시킬 수 있을까? 만약 shared_ptr내부에 참조 개수를 저장한다면 p2의 참조개수를 ++한다고 해도
	p1의 참조개수를 건들일 수 없기에 하나의 객체를 가리키지만 reference count가 shared_ptr에 따라 다른 경우가 발생할 수 있다.
	 이와 같은 문제를 방지하기 위해 실제 객체를 가리키는 shared_ptr이 제어블록(control block)을 동적으로 할당하고, shared_ptr들이 이 제어블록에 필요한 정보를 공유하는 방식으로 구현된다.
	즉, shared_ptr은 복사 생성할 때 마다 제어블록의 위치만 공유하면 된다.

[2.	make_shared로 생성하자]
1.	앞서 std::shared_ptr<A> p1(new A());로 share_ptr을 생성하였는데, 이는 A생성시 동적할당, shared_ptr의 제어블럭생성시 동적할당, 총 2번의 동적할당이 발생하므로
	아예 두 개의 크기를 합친 크기로 한번에 할당하는 것이 훨씬 효율적이다(동적할당은 크기가 큰 연산이기에)
	std::shared_ptr<A> p1=std::make_shared<A>();
	make_shared함수응 A의 생성자의 인자들을 받아 객체 A와 shared_ptr의 제어블록까지 한번에 할당하고 만들어진 shared_ptr을 리턴한다.
	(make_shared가 A의 생성자에 완벽한 전달을 한다)

[3.	shared_ptr 생성 시에 주의할 점]
1.	shared_ptr은 인자로 주소값이 전달되면, 해당 객체를 첫번째로 소유하느 shared_ptr인 것 마냥 행동한다.
	A* a=new A();
	std::shared_ptr<A> pa1(a);
	std::shared_ptr<A> pa2(a);//not pa2(pa1)
	즉, pa1와 pa2의 제어블럭이 따로 생성되어 서로의 존재를 모른 채 reference count를 set1로 하고, 둘 중 하나 소멸 시 pa2가 가리키고 있음에도 불구하고 free를 해버린다.
	나중에 남은 하나의 shared_ptr이 free될 때 해제된 객체를 소멸시키기에 오류가 발생한다.
	 즉 주소값으로 shared_ptr을 만드는 행동을 지양해야하지만, 이렇게 할 수 밖에 없는 경우도 존재한다. 
	클래스 멤버함수로 return shared_ptr 시 reference count 정보를 모르기에 double free error가 발생할 수 있다.
	 이는 enable_shared_from_this를 사용하여 깔끔하게 해결이 가능하다.
	우리가 this를 사용하여 shared_ptr을 만들고 싶은 클래스가 있다면, enable_shared_from_this를 상속받자. 
	shared_from_this 함수는 기존의 제어블록을 이용하여 shared_ptr을 생성한다.
	
2.	중요한 점은 shared_from_this는 기존의 제어블록을 이용하기에 먼저 해당 객체의 shared_ptr가 먼저 정의되어 있어야 한다.
	A* a=new A();
	std::shared_ptr<A> pa1=a->get_shared_ptr();//error occur!

[4.	서로 참조하는 shared_ptr]
1.	객체를 더이상 사용하지 않지만 reference count가 절대로 0이 되지 않는 상황이 존재한다.(순환 참조) 
					object1  <-  shared_ptr(ref_count:2)
	shared_ptr(ref count:2)  ->  object2 
	각 객체는 shared_ptr을 하나씩 가지고 있는데, 객체1의 sptr은 객체2를 가리키고 객체2의 sptr은 객체1을 가리킨다.
	 이러한 순환 참조 문제를 해결하기 위해 weak_ptr이 나타났다.

[5.	weak_ptr]
1.	트리 구조를 지원하는 클래스를 만든다고 생각해보자(한 개의 노드느 여러개의 자식 노드를 가지지만, 단 하나의 부모 노드를 가짐)
	class Node{
		std::vector<std::shared_ptr<Node>> shildren;
		//some type// parent;
	
		public:
			Node(){};
			void AddChild(std::shared_ptr<Node> node) { children.push_back(node); }
	};
	부모가 여러개의 자식 노드들을 가지기에 shared_ptr들의 벡터로 나타낼 수 있고, 그 노드도 부모노드가 있기에 부모노드를 가리키는 포인터를 가진다.
	 만약 parent의 타입을 일반 포인터로 하면 메모리 해제를 하지 않거나, 예외발생시 자원을 해제하기 어렵거나, 해제된 포인터를 가리킬 수 있다.
	하지만 이를 shared_ptr로 하면 순환 참조 문제가 생긴다. 부모와 자식은 서로를 가리키기에 reference count가 0이 될 수 없다.
2.	weak_ptr은 일반 포인터와 shared_ptr사이의 포인터로 일반 포인터와 다르게 안전하게 참조할 수 있지만 shared_ptr와 다르게 reference count를 ++하지 않는다.
	고로 weak_ptr이 객체를 가리킨다하더라도 다른 shared_ptr이 가리키고있지 않는 이상, 메모리에서 소멸되어있을 것이다.
	 고로 weak_ptr자체로는 원래 객체를 참조할 수 없고, 반드시 shared_ptr로 변환하여 사용해야 한다. 만약 가리키는 객체가 비면 share_ptr로 변환되고, 아니면 해당 객체를 가리키는 share_ptr로 변환된다.
3.	lock함수는 weak_ptr이 살아있음 그 share_ptr을 반환하고 해제되어있다면 빈 shared_ptr을 반환한다. 
4.	제어블록에는 ref count가 있고, 그것이 0이 되면 메모리에서 해제해야한다. 하지만 0이 될때 제어블록을 메모리에서 해제하지는 않는데, weak_ptr이 남아있을 경우(이미 객체 해제) 제어블록을 해제해버린다면 제어블록의 참조 카운트가 0이라는 사실을 알 수 없게 된다.
	즉, 제어블록을 메모리에서 해제하기 위해서는 이를 가리키는 weak_ptr도 0개여야 한다. 고로 제어블록은 참조 개수와 더불어 약한 참조개수(weak count)를 기록하게 된다.
	 
*/
