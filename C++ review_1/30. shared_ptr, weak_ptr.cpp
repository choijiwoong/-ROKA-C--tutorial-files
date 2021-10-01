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
1.	�������� ����Ʈ �����Ͱ� �ϳ��� ��ü�� ���� �����ؾ� �� ��, shared_ptr�� ����Ѵ�.
 	������ ���Ұ� ������� �Ҹ��ڸ� ȣ���ϱ⿡ ��� �����͸� �����ϴ����� reference count(���� ����)�� ������(��ü ���� �ƴ�)�� �����ϰ�
	�����ϴ� ������� �����ȴ�.
2.	std::shared_ptr<A> p1(new A())�� ������ �� �ֱ��ѵ� maek_uniqueó�� make_shared�� ����Ͽ� �����ϸ� ������.
	std::shared_ptr<A> p1=std::make_shared<A>() 
3.	shared_ptr�� ���� �ּҰ��� ������ �ٸ� �������� �����ϱ⿡ �̸� �����ؾ� �Ѵ�.
	A* a=new A();
	std::shared_ptr<A> pa1(a);
4.	shared_ptr�� �����Ǵ� block�� �ٸ� ���, �� ��ü ���ο��� �ڽ��� ����Ű�� shared_ptr�� �����Ҷ����� ��� ���ο� �������� �Ҵ��ϱ⿡ �Ҹ��� ȣ�⿡�� ������ �߻��� �� �ִµ�
	�׷���� enable_shared_from_this�� ��ӹ����� �ȴ�. 
5.	���� �����ϴ� shared_ptr �� ��ȯ����(Ʈ�������� �θ��ڽĳ��)�� �Ǹ�, ���� �Ҹ��ų �� ���� ���°� �Ǵµ�, �̶��� weak_ptr�� ����ϸ� �ȴ�.
	weak_ptr�� shared_ptr������ ���������� �ø��� �ʴ´�. ����Ϸ��� shared_ptr�� ��ȯ�Ͽ� ����Ѵ�.  
6.	shared_ptr�� ����� ��ü�� �̹� �����Ǿ�������, �����ϵ� ����������� weak_ptr�� ����ī��Ʈ�� 0���� ����� �𸣱⿡ weak count�� �����Ͽ� ����Ѵ�. 
*/ 
