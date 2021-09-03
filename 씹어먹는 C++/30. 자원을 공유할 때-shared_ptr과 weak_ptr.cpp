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
[0.	���⿡ �ռ�]
1.	��κ� �ϳ��� �ڿ��� �ϳ��� ����Ʈ �����Ϳ� ���� �����Ǵ� ���� �ٶ����Ͽ� ������ ������ ������ �ƴ� �Ϲ� �����ͷ� ó���ϸ� �ȴ�.
	������ ���� ��ü���� �ϳ��� �ڿ��� ����� �� �������� ����Ʈ �����Ͱ� �ϳ��� ��ü�� ���� �����ؾ��ϴ� ��쵵 �߻��Ѵ�.
	�̷��� ��쿣 ��� �� �ڿ��� ����ϴ� ��� ��ü���� �Ҹ�Ǿ� �ϴµ�, � ��ü�� ���� �Ҹ����� �𸣱⿡ �ڿ��� �������Ѿ��ϴ� Ÿ�̹��� ��ġ�� �ȴ�.
	 �� ���, �� �� ����Ʈ�� �����͸� �̿��Ͽ� Ư�� �ڿ��� �� ���� ��ü���� ����Ű������ ������ ����, �� ���� 0�� �ɶ� ��μ� ������ �����ִ� ����� �����Ͱ� �ʿ��ϴ�.

[1.	shared_ptr]
1.	case shared_ptr:
		std::shared_ptr<A> p1(new A());
		std::shared_ptr<A> p2(p1);
	case unique_ptr;
		std::unique_ptr<A> p1(new A());
		std::unique_ptr<A> p2(p1);//compile error
	�������� shared_ptr�� ���� ��ü�� ���ÿ� ����ų �� �ִ�. 
2.	memory free�� ���� ���� ����(reference count)�� �˾ƾ� �Ѵ�. 0�� �Ǿ�� ������ �� �� �ֱ� �����̴�. 
	reference count�� use_count function�� ���� �� �� �ִ�.
3.	std::shared_ptr<A> p1(new A());
	std::shared_ptr<A> p2(p1);
	
	std::cout<<p1.use_count();//2
	std::cout<<p2.use_count();//2
	��� ���� ��ü�� ����Ű�� shared_ptr���� ����ȭ��ų �� ������? ���� shared_ptr���ο� ���� ������ �����Ѵٸ� p2�� ���������� ++�Ѵٰ� �ص�
	p1�� ���������� �ǵ��� �� ���⿡ �ϳ��� ��ü�� ����Ű���� reference count�� shared_ptr�� ���� �ٸ� ��찡 �߻��� �� �ִ�.
	 �̿� ���� ������ �����ϱ� ���� ���� ��ü�� ����Ű�� shared_ptr�� ������(control block)�� �������� �Ҵ��ϰ�, shared_ptr���� �� �����Ͽ� �ʿ��� ������ �����ϴ� ������� �����ȴ�.
	��, shared_ptr�� ���� ������ �� ���� �������� ��ġ�� �����ϸ� �ȴ�.

[2.	make_shared�� ��������]
1.	�ռ� std::shared_ptr<A> p1(new A());�� share_ptr�� �����Ͽ��µ�, �̴� A������ �����Ҵ�, shared_ptr�� ����������� �����Ҵ�, �� 2���� �����Ҵ��� �߻��ϹǷ�
	�ƿ� �� ���� ũ�⸦ ��ģ ũ��� �ѹ��� �Ҵ��ϴ� ���� �ξ� ȿ�����̴�(�����Ҵ��� ũ�Ⱑ ū �����̱⿡)
	std::shared_ptr<A> p1=std::make_shared<A>();
	make_shared�Լ��� A�� �������� ���ڵ��� �޾� ��ü A�� shared_ptr�� �����ϱ��� �ѹ��� �Ҵ��ϰ� ������� shared_ptr�� �����Ѵ�.
	(make_shared�� A�� �����ڿ� �Ϻ��� ������ �Ѵ�)

[3.	shared_ptr ���� �ÿ� ������ ��]
1.	shared_ptr�� ���ڷ� �ּҰ��� ���޵Ǹ�, �ش� ��ü�� ù��°�� �����ϴ� shared_ptr�� �� ���� �ൿ�Ѵ�.
	A* a=new A();
	std::shared_ptr<A> pa1(a);
	std::shared_ptr<A> pa2(a);//not pa2(pa1)
	��, pa1�� pa2�� ������� ���� �����Ǿ� ������ ���縦 �� ä reference count�� set1�� �ϰ�, �� �� �ϳ� �Ҹ� �� pa2�� ����Ű�� �������� �ұ��ϰ� free�� �ع�����.
	���߿� ���� �ϳ��� shared_ptr�� free�� �� ������ ��ü�� �Ҹ��Ű�⿡ ������ �߻��Ѵ�.
	 �� �ּҰ����� shared_ptr�� ����� �ൿ�� �����ؾ�������, �̷��� �� �� �ۿ� ���� ��쵵 �����Ѵ�. 
	Ŭ���� ����Լ��� return shared_ptr �� reference count ������ �𸣱⿡ double free error�� �߻��� �� �ִ�.
	 �̴� enable_shared_from_this�� ����Ͽ� ����ϰ� �ذ��� �����ϴ�.
	�츮�� this�� ����Ͽ� shared_ptr�� ����� ���� Ŭ������ �ִٸ�, enable_shared_from_this�� ��ӹ���. 
	shared_from_this �Լ��� ������ �������� �̿��Ͽ� shared_ptr�� �����Ѵ�.
	
2.	�߿��� ���� shared_from_this�� ������ �������� �̿��ϱ⿡ ���� �ش� ��ü�� shared_ptr�� ���� ���ǵǾ� �־�� �Ѵ�.
	A* a=new A();
	std::shared_ptr<A> pa1=a->get_shared_ptr();//error occur!

[4.	���� �����ϴ� shared_ptr]
1.	��ü�� ���̻� ������� ������ reference count�� ����� 0�� ���� �ʴ� ��Ȳ�� �����Ѵ�.(��ȯ ����) 
					object1  <-  shared_ptr(ref_count:2)
	shared_ptr(ref count:2)  ->  object2 
	�� ��ü�� shared_ptr�� �ϳ��� ������ �ִµ�, ��ü1�� sptr�� ��ü2�� ����Ű�� ��ü2�� sptr�� ��ü1�� ����Ų��.
	 �̷��� ��ȯ ���� ������ �ذ��ϱ� ���� weak_ptr�� ��Ÿ����.

[5.	weak_ptr]
1.	Ʈ�� ������ �����ϴ� Ŭ������ ����ٰ� �����غ���(�� ���� ���� �������� �ڽ� ��带 ��������, �� �ϳ��� �θ� ��带 ����)
	class Node{
		std::vector<std::shared_ptr<Node>> shildren;
		//some type// parent;
	
		public:
			Node(){};
			void AddChild(std::shared_ptr<Node> node) { children.push_back(node); }
	};
	�θ� �������� �ڽ� ������ �����⿡ shared_ptr���� ���ͷ� ��Ÿ�� �� �ְ�, �� ��嵵 �θ��尡 �ֱ⿡ �θ��带 ����Ű�� �����͸� ������.
	 ���� parent�� Ÿ���� �Ϲ� �����ͷ� �ϸ� �޸� ������ ���� �ʰų�, ���ܹ߻��� �ڿ��� �����ϱ� ��ưų�, ������ �����͸� ����ų �� �ִ�.
	������ �̸� shared_ptr�� �ϸ� ��ȯ ���� ������ �����. �θ�� �ڽ��� ���θ� ����Ű�⿡ reference count�� 0�� �� �� ����.
2.	weak_ptr�� �Ϲ� �����Ϳ� shared_ptr������ �����ͷ� �Ϲ� �����Ϳ� �ٸ��� �����ϰ� ������ �� ������ shared_ptr�� �ٸ��� reference count�� ++���� �ʴ´�.
	��� weak_ptr�� ��ü�� ����Ų���ϴ��� �ٸ� shared_ptr�� ����Ű������ �ʴ� �̻�, �޸𸮿��� �Ҹ�Ǿ����� ���̴�.
	 ��� weak_ptr��ü�δ� ���� ��ü�� ������ �� ����, �ݵ�� shared_ptr�� ��ȯ�Ͽ� ����ؾ� �Ѵ�. ���� ����Ű�� ��ü�� ��� share_ptr�� ��ȯ�ǰ�, �ƴϸ� �ش� ��ü�� ����Ű�� share_ptr�� ��ȯ�ȴ�.
3.	lock�Լ��� weak_ptr�� ������� �� share_ptr�� ��ȯ�ϰ� �����Ǿ��ִٸ� �� shared_ptr�� ��ȯ�Ѵ�. 
4.	�����Ͽ��� ref count�� �ְ�, �װ��� 0�� �Ǹ� �޸𸮿��� �����ؾ��Ѵ�. ������ 0�� �ɶ� �������� �޸𸮿��� ���������� �ʴµ�, weak_ptr�� �������� ���(�̹� ��ü ����) �������� �����ع����ٸ� �������� ���� ī��Ʈ�� 0�̶�� ����� �� �� ���� �ȴ�.
	��, �������� �޸𸮿��� �����ϱ� ���ؼ��� �̸� ����Ű�� weak_ptr�� 0������ �Ѵ�. ��� �������� ���� ������ ���Ҿ� ���� ��������(weak count)�� ����ϰ� �ȴ�.
	 
*/
