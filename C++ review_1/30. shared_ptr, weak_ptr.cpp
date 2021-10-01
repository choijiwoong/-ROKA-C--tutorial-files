#include <iostream>
#include <memory>

/*return shared_ptr that point itself in class
class A:public std::enable_shared_from_this<A>{//for use shared_from_this() function
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
		
		std::shared_ptr<A> get_shared_ptr(){ return shared_from_this(); }//not return std::shared_ptr<A>(this);
		//use same control block with pa1!
};

int main(){
	std::shared_ptr<A> pa1=std::make_shared<A>();//first define!
	std::shared_ptr<A> pa2=pa1->get_shared_ptr();//for use
	
	std::cout<<pa1.use_count()<<std::endl;
	std::cout<<pa2.use_count()<<std::endl;
}*/

#include <string>
#include <vector>
//use of weak_ptr
class A{
	std::string s;
	std::weak_ptr<A> other;//
	
	public:
		A(const std::string& s): s(s){ std::cout<<"get resource!"<<std::endl; }
		~A(){ std::cout<<"call destructor!"<<std::endl; }
		
		void set_other(std::weak_ptr<A> o){ other=o; }
		void access_other(){
			std::shared_ptr<A> o=other.lock();//if no shared_ptr, become empty shared_ptr
			if(o)
				std::cout<<"access: "<<o->name()<<std::endl;
			else//empty shared_ptr
				std::cout<<"already destroyed!"<<std::endl;
		}
		std::string name(){ return s; }
};

int main(){
	std::vector<std::shared_ptr<A>> vec;
	vec.push_back(std::make_shared<A>("resource 1"));
	vec.push_back(std::make_shared<A>("resource 2"));
	
	vec[0]->set_other(vec[1]);
	vec[1]->set_other(vec[0]);//circle reference
	
	std::cout<<"vec[0] ref count: "<<vec[0].use_count()<<std::endl;//1 not 2!
	std::cout<<"vec[1] ref count: "<<vec[1].use_count()<<std::endl;
	
	vec[0]->access_other();
	
	vec.pop_back();//destroy!
	vec[0]->access_other();
}
 

/*
1.	여러개의 스마트 포인터가 하나의 객체를 같이 소유해야 할 때, shared_ptr을 사용한다.
 	마지막 원소가 사라지면 소멸자를 호출하기에 몇개의 포인터를 공유하는지를 reference count(참조 개수)를 제어블록(객체 내부 아님)에 저장하고
	공유하는 방식으로 구현된다.
2.	std::shared_ptr<A> p1(new A())로 생성할 수 있긴한데 maek_unique처럼 make_shared를 사용하여 생성하면 빠르다.
	std::shared_ptr<A> p1=std::make_shared<A>() 
3.	shared_ptr에 직접 주소값을 넣으면 다른 제어블록을 생성하기에 이를 지양해야 한다.
	A* a=new A();
	std::shared_ptr<A> pa1(a);
4.	shared_ptr이 생성되는 block이 다른 경우, 즉 객체 내부에서 자신을 가리키는 shared_ptr을 리턴할때같은 경우 새로운 제어블록을 할당하기에 소멸자 호출에서 오류가 발생할 수 있는데
	그런경우 enable_shared_from_this를 상속받으면 된다. 
5.	서로 참조하는 shared_ptr 즉 순환참조(트리구조의 부모자식노드)가 되면, 서로 소멸시킬 수 없는 상태가 되는데, 이때는 weak_ptr을 사용하면 된다.
	weak_ptr은 shared_ptr같지만 참조개수를 늘리지 않는다. 사용하려면 shared_ptr로 변환하여 사용한다.  
6.	shared_ptr이 사라져 객체가 이미 해제되어있을때, 제어블록도 사라져있으면 weak_ptr이 참조카운트가 0인지 몇개인지 모르기에 weak count도 제어블록에 기록한다. 
*/ 
