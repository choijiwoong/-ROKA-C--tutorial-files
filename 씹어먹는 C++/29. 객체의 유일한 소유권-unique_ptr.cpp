#include <iostream>

/*1
class A{
	int *data;
	
	public:
		A(){//constructor
			data=new int[100];
			std::cout<<"get resource!"<<std::endl; 
		}
		~A(){
			std::cout<<"call destructor!"<<std::endl;
			delete[] data;
		}
};
void thrower(){
	throw 1;//occur exception
} 
void do_something(){
	A *pa=new A();
	thrower();
	//Compiler doesn't call delete pa because of occured exception.
	delete pa;
}

int main(){
	try{
	do_something();//just print "get resource!" not with "call destructor" because we forgot delete pa
	//no destroy allocated object. it occurs memory leak of 440bites. if we don't delete in do_something, pa that point created object disappear.
	//A's object remains in somewhere at Heap, that object don't delete forever getting space in Heap. 
	} catch(int i){
		std::cout<<"exception occur!"<<std::endl;
	}
	//just print "get resource!" "exception occur!" without "call destructor!" because of exception in thrower().
	//exception is well handled normally, but we can't avoid memory leak. than how can we handle this situation?->[2. Resource Acquisition Is Initialization-RAII]
}*/

#include <memory>
/*3, 5
class A{
	int *data;
	
	public:
		A(){
			std::cout<<"get resource!"<<std::endl;
			data=new int[100];
		}
		
		void some(){ std::cout<<"we can use like common pointer!"<<std::endl;}
		void do_sth(int a){
			std::cout<<"do something!!!"<<std::endl;
			data[0]=a;
		} 
		
		~A(){
			std::cout<<"resource is free! doby is free!"<<std::endl;
			delete[] data;
		}
};
void do_something(){
	std::unique_ptr<A> pa(new A());
	std::cout<<"pa : "; 
	pa->some();
	
	//std::unique_ptr<A> pb =pa;//Can pb point pa?
	//error occur! "attempting to reference a deleted function" what's deleted function of this error?
	//cannot copy because unique_ptr's copy constructor are created to deleted function! by using 'copy constructor=delete;'
	
	//pass ownership
	std::unique_ptr<A> pb=std::move(pa);
	std::cout<<"pb : ";
	pb->some();
	//unique_ptr aren't defined copy constructor but are defined move constructor like concept that pass ownership.
	//move forcely pa to pb.
	pa.get();//print 0(nullptr). pa points nothing.
	//so we have to be care of accessing initial unique_ptr.
}
//void do_something(std::unique_ptr<A>& ptr){ ptr->do_sth(3);}//uncorrect way of pass
void do_something(A* ptr){ ptr->do_sth(3); }//correct way of pass
//it get's normal pointer. this just get permission of accessing object in function without meaning of ownership.

int main(){
	do_something();
	
	//std::cout<<std::endl<<std::endl;
	//std::unique_ptr<A> pa(new A());
	//do_something(pa);
	//
	//std::unique_ptr<A>& ptr is well passed to do_something function
	//but is it right contextly?
	//ptr is used to reference, doesn't destroy object of pa closing do_something(). However, at leat in do_something funxtion, we can own ptr.
	//it's not right contextly to rule that unique_ptr means ownership.
	//so using reference of unique_ptr is just Wrapper of pointer simply.
	//We have to pass correctly unique_ptr to function. Let's pass address of original pointer
	
	std::unique_ptr<A> pa(new A());
	do_something(pa.get());//if we call get() of unique_ptr, it returns address of real object.
}*/

/*7
class Foo{
	int a, b;
	
	public:
		Foo(int a, int b):a(a), b(b){ std::cout<<"call constructor!"<<std::endl; }
		void print(){ std::cout<<"a : "<<a<<", b : "<<b<<std::endl; }
		~Foo(){ std::cout<<"call destructor!"<<std::endl; }
};

int main(){
	auto ptr=std::make_unique<Foo>(3, 5);//make_unique function pass perfectly arguments to constructor of class that is passed by template argument.
	//we don't need to use like 'std::unique_ptr<Foo> ptr(new Foo(3,5));' now, just use 'std::make_unique<Foo>(3,5);'
	ptr->print();
}*/

//8
#include <vector>

class A{
	int *data;
	
	public:
		A(int i){
			std::cout<<"get resource!"<<std::endl;
			data=new int[100];
			data[0]=i;
		}
		
		void some(){ std::cout<<"we can use like common pointer!"<<std::endl; }
		void some2(){ std::cout<<"value : "<<data[0]<<std::endl; } 
		
		~A(){
			std::cout<<"free resource!"<<std::endl;
			delete[] data;
		}
};

int main(){
	std::vector<std::unique_ptr<A>> vec;
	std::unique_ptr<A> pa(new A(1));
	
	//vec.push_back(pa);
	//error occur! it copy pa for input data in vector. but unique_ptr's copy constructor is deleted function.
	//so we have to move pa to inside of vector to overloading getting rvalue reference of push_back.
	
	vec.push_back(std::move(pa));//overload of push_back that receive rvalue reference
	
	vec.emplace_back(new A(1));//It's like vec.push_back(std::unique_ptr<A>(new A(1));
	vec.back()->some2();
}


/*
[0. ���⿡ �ռ�]
1.	���� ������ move semantics�� perfect forwarding���� ������ ����ȭ��, ������ �Ұ����ϴ� �۾��� �����ϰ� �Ǿ���.
	 �̹����� C++11���� �ڿ��� �����ϴ� ����� ���ؼ� �ٷ� ���ε�, resoure�� �ϸ� ���������� ������, �Ҵ��� �޸𸮵� �ڿ��̰�, open�� ���� ���� �ϳ��� �ڿ��̴�.
	�߿��� ���� �ڿ��� ���� ���α׷����� �����Ǿ� �ֱ� ������ ������ �� �ؾ� �Ѵٴ� ���̴�. �޸𸮸� �Ҵ��ϰ� ������ ���� �ʴ´ٸ�, �ᱹ �޸� �������� ���α׷��� crash�� ���� �ִ�.

[1.	�ڿ�(resource)������ �߿伺]
1.	C++������ ���(Java ��)�� ��κ� ���α׷� �󿡼� ������ �ʴ� �ڿ��� �ڵ����� �������ִ� ������ �÷���(Garbage Collector-GC)�� �Ҹ��� �ڿ� û�ұⰡ ����Ǿ� ������, 
	C++���ڿ��� ���� �����ϱ� ���� ���α׷� ���� ������ ������ �����ְ� �ȴ�.(���α׷��� ����Ǹ� �ü���� ��������) 
2.	������ ���α׷��� ũ�Ⱑ Ŀ����, �ڿ��� �����ϴ� ��ġ�� �ָ��� ��찡 ���Ƽ� �ڿ� ������ ��ġ�� �����̴�. 

[2.	Resource Acquisition Is Initialization-RAII]
1.	C++â������ ��߳� ��Ʈ�ν�Ʈ���� �ڿ��� �����ϴ� ������μ� "�ڿ��� ȹ���� �ʱ�ȭ��"(RAII)��� ������ ������ �����Ѵ�. �ڿ� ������ ���ÿ� �Ҵ��� ��ü�� ���� �����ϴ� ���̴�.
	 ���ܰ� �߻��ؼ� �Լ��� ���������鼭 �ش� �Լ��� ���ÿ� ���ǵ� ��� ��ü���� �������� �Ҹ��ڰ� ȣ��ȴٰ� �Ͽ���(stack unwinding)
	�׷��ٸ� �� �Ҹ��ڵ� �ȿ� �� ����� �ڿ��� �����ϴ� ��ƾ�� �ִ´ٸ�? ��, ���� pa�� �Ϲ����� �����Ͱ� �ƴ�, ������'��ü'�� ���� �Ҹ��ڸ� ȣ���ϰ� �Ѵٸ�?
	�̷��� ��ī�������� �۵��ϴ� ������ ��ü�� ����Ʈ ������(smart pointer)��� �Ѵ�.(C++ 11 �������� �̷��� ������ �ذ��ϱ� ���� auto_ptr�̶�� ���� ��� �����߾�����, ������ ���� ����� �����ϰ� �ִ�.)
	 C++������ auto_ptr�� ������ �� ������ ���ο� ����Ʈ �����͸� �����ϰ� �ִµ�, �̰��� �ٷ� unique_ptr�� shared_ptr�̴�.

[3.	��ü�� ������ ������, unique_ptr]
1.	C++���� �޸𸮰����� �������� ��, ũ�� �� ������ �������� �߻��Ѵ�.
	 �ϳ��� �޸� ��� �� �������� ���� ����ε�(memory leak), �̴� ����ó�� ��ð� �۵��ϴ� ���α׷��� ��� �ð��� ������ ���� ���Ǵ� �޸��� ���� �þ�� ��������� �ý��� �޸𸮰� ������������ ������ �״� ��Ȳ�� �߻��� ���ִ�.
	�̴� RAII������ ���� ����� ���� �޸𸮸� �׻� �������ѹ����� �ذ��� �����ϴ�.
	 �ι�°�� �̹� ������ �޸𸮸� �ٽ� �����ϴ� ����̴�.  
	Data* data=new Data();
	Data* data2=data;//point same object
	delete data;//free
	delete data2;//free freed data?!
	�̷��� �̹� �Ҹ�� ��ü�� �ٽ� �Ҹ���Ѽ� �߻��ϴ� ���׸� double free���׶�� �θ���.
	�̷��� ������ �߻������� ������� ��ü�� �������� ��Ȯ���� �ʾƼ��̴�. ���ڱ� ���� �԰�ʹ�. ��� ���� � �����Ϳ� ��ü�� ������ �������� �ο��Ͽ� �� ������ ����� ��ü�� �Ҹ��ų �� ���� �ع����� �̷��� double free���װ� �߻����� ���� ���̴�.
	 C++������ ��ó��, Ư�� ��ü�� ������ �������� �ο��ϴ� ������ ��ü�� unique_ptr��� �Ѵ�.
2.	std::unique_ptr<A> pa(new A()); == A* pa=new A();
	unique_ptr�� ->�����ڸ� �����ε��Ͽ� ��ġ �����͸� �ٷ�� �Ͱ� ���� ����� �� �ִ�. pa�� ���ÿ� ���ǵ� ��ü�̱⿡ do_something()�Լ��� ����� �� �ڵ����� �Ҹ��ڰ� ȣ��Ǿ� �ڽ��� ����Ű�� �ִ� �ڿ��� �������ֱ� ������ RAII������ ����� �� �ִ�.
	 ���� unique_ptr�� �����Ϸ��� �ϸ� ������ �Լ��� ����Ϸ� �ߴٴ� ������ �߻��Ѵ�.

[4.	������ �Լ�]
1.	����� ��ġ �ʴ� �Լ��� �������ѹ����� ����� C++11�� �߰��� ����̴�.
	class A{
		public:
			A(int a){};
			A(const A& a)=delete;//delete copy constructor explicitly!
	}
	
	int main(){
		A a(3);//possible
		A b(a);//impossible(copy constructor was deleted)
	}
	�������ϸ� ���������(const A& a)�� ȣ���ϴ� �κп��� ������ �߻��ϴµ�, ��������ڸ� ��������� �����߱� �����̴�. 
	�̷��� ������� ���α׷��Ӱ� ��������� �� �Լ��� ���� ����� ǥ���԰� ���ÿ� Ȥ�� ����ϴ��� ������ ������ �߻��ϰ� �ȴ�.
2.	unique_ptr�� ���������� unique_ptr�� ��������ڰ� ��������� �����Ǿ� �ִ�. �� ������ �����ϰ� unique_ptr�� ��� ��ü�� �����ϰ� �����ؾ� �ϱ� �����̴�.
	 ���� unique_ptr�� ��������ڸ� ����ϰ� �ȴٸ� ���� unique_ptr���� Ư�� ��ü�� �����ϰ� �Ǵ� ������ �߻��Ͽ� double free���װ� unique_ptr���� �Ҹ��� �� �߻��ϰ� �ȴ�.

[5.	unique_ptr ������ �����ϱ�]
1.	unique_ptr�� ���簡 �Ұ����� ���, �������� ������ �� �ִ�. 
2.	�������� ������ ������ unique_ptr�� ���� �ʵ��� ��������.

[6.	unique_ptr�� �Լ� ���ڷ� �����ϱ�]
1.	������ ����
	-unique_ptr�� � ��ü�� ������ �������� ��Ÿ���� �������̸�, unique_ptr�� �Ҹ�� ��, ����Ű�� ��ü ���� �Ҹ�ȴ�.
	-���� �ٸ� �Լ����� unique_ptr�� ������ ��ü�� �Ͻ������� �����ϰ� �ʹٸ�, get�� ���� �ش� ��ü�� �����͸� �����ϸ� �ȴ�.
	-���� �������� �̵��ϰ��� �Ѵٸ�, unique_ptr�� move�ϸ� �ȴ�.

[7.	unique_ptr�� ���� �����ϱ�]
1.	C++14���� unique_ptr�� �����ϰ� ���� �� �ִ� std::make_unique�Լ��� �����Ѵ�. 
2.	std::unique_ptr<Foo> ptr(new Foo(3, 5)); ���� Foo�� 2�� �Է����� �ʰ� std::make_unique<Foo>(3, 5);�� ���

[8.	unique_ptr�� ���ҷ� ������ �����̳�]
1.	copy constructor�� ȣ������ �ʰ� move constructor�� �����ε����Ѿ� �Ѵ�.
2.	emplace_back�Լ��� �̿��Ͽ� vector�ȿ� unique_ptr�� ���� �����ϸ鼭 ������� �� �ִ�. �� ���ʿ��� ����->�̵������� ������ �� �ִ�.
	emplace_back�� ���޵� ���ڸ� �Ϻ��� ����(perfect forwarding)�� ���� ���� unique_ptr<A>�� �����ڿ� �����ؼ�, vector�� �ڿ� unique_ptr<A> ��ü�� �����ع����� �ȴ�. �� ���ʿ� ������ vector�� �ڿ� �ϱ⿡ ���ʿ��� �̵� ������ �ʿ���� �ȴ�. 
	 �ٸ� emplace_back��� �� ��� �����ڰ� ȣ��Ǵ����� �����ؾ� �ϴµ�,
	std::vector<int> v;
	v.emplace_back(100000);
	�� ��� 100000�� int ���� v�� �߰�������
	std::vector<std::vector<int>> v;
	v.emplace_back(100000);
	�� �ϰ� �Ǹ� ���Ұ� 100000�� ����ִ� ���͸� v�� �߰��ϰ� �ȴ�. 

*/
