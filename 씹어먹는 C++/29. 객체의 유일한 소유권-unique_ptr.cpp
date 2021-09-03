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
[0. 들어가기에 앞서]
1.	지난 강좌의 move semantics와 perfect forwarding덕에 세심한 최적화와, 기존에 불가능하던 작업이 가능하게 되었다.
	 이번에는 C++11에서 자원을 관리하는 방법에 대해서 다룰 것인데, resoure라 하면 여러가지가 있지만, 할당한 메모리도 자원이고, open한 파일 역시 하나의 자원이다.
	중요한 점은 자원의 양은 프로그램마다 한정되어 있기 때문에 관리를 잘 해야 한다는 것이다. 메모리를 할당하고 해제를 하지 않는다면, 결국 메모리 부족으로 프로그램이 crash될 수도 있다.

[1.	자원(resource)관리의 중요성]
1.	C++이후의 언어(Java 등)은 대부분 프로그램 상에서 쓰이지 않는 자원을 자동으로 해제해주는 가비지 컬렉터(Garbage Collector-GC)라 불리는 자원 청소기가 내장되어 있지만, 
	C++의자원은 직접 해제하기 전엔 프로그램 종료 전까지 영원히 남아있게 된다.(프로그램이 종료되면 운영체제가 해제해줌) 
2.	하지만 프로그램의 크기가 커지면, 자원을 해제하는 위치가 애매한 경우가 많아서 자원 해제를 놓치기 쉽상이다. 

[2.	Resource Acquisition Is Initialization-RAII]
1.	C++창시자인 비야네 스트로스트룹은 자원을 관리하는 방법으로서 "자원의 획득은 초기화다"(RAII)라는 디자인 패턴을 제안한다. 자원 관리를 스택에 할당한 객체를 총해 수정하는 것이다.
	 예외가 발생해서 함수를 빠져나가면서 해당 함수의 스택에 정의된 모든 객체들은 빠짐없이 소멸자가 호출된다고 하였다(stack unwinding)
	그렇다면 이 소멸자들 안에 다 사용한 자원을 해제하는 루틴을 넣는다면? 즉, 위의 pa를 일반적인 포인터가 아닌, 포인터'객체'로 만들어서 소멸자를 호출하게 한다면?
	이러한 메카니즘으로 작동하는 포인터 객체를 스마트 포인터(smart pointer)라고 한다.(C++ 11 이전에는 이러한 문제를 해결하기 위해 auto_ptr이라는 것이 잠시 등장했었지만, 문제가 많아 사용을 금지하고 있다.)
	 C++에서는 auto_ptr을 보완한 두 형태의 새로운 스마트 포인터를 제공하고 있는데, 이것이 바로 unique_ptr과 shared_ptr이다.

[3.	객체의 유일한 소유권, unique_ptr]
1.	C++에서 메모리관리에 실패했을 때, 크게 두 가지의 문제점이 발생한다.
	 하나는 메모리 사용 후 해제하지 않은 경우인데(memory leak), 이는 서버처럼 장시간 작동하는 프로그램의 경우 시간이 지남에 따라 사용되는 메모리의 양이 늘어나서 결과적으로 시스템 메모리가 부족해져버려 서버가 죽는 상황이 발생할 수있다.
	이는 RAII패턴을 통해 사용이 끝난 메모리를 항상 해제시켜버리면 해결이 가능하다.
	 두번째는 이미 해제된 메모리를 다시 참조하는 경우이다.  
	Data* data=new Data();
	Data* data2=data;//point same object
	delete data;//free
	delete data2;//free freed data?!
	이렇게 이미 소멸된 객체를 다시 소멸시켜서 발생하는 버그를 double free버그라고 부른다.
	이러한 문제의 발생원인은 만들어진 객체의 소유권이 명확하지 않아서이다. 갑자기 삼겹살 먹고싶다. 고로 만약 어떤 포인터에 객체의 유일한 소유권을 부여하여 이 포인터 말고는 객체를 소멸시킬 수 없게 해버리면 이러한 double free버그가 발생하지 않을 것이다.
	 C++에서는 이처럼, 특정 객체에 유일한 소유권을 부여하는 포인터 객체를 unique_ptr라고 한다.
2.	std::unique_ptr<A> pa(new A()); == A* pa=new A();
	unique_ptr은 ->연산자를 오버로드하여 마치 포인터를 다루는 것과 같이 사용할 수 있다. pa는 스택에 정의된 객체이기에 do_something()함수가 종료될 때 자동으로 소멸자가 호출되어 자신이 가리키고 있는 자원을 해제해주기 때문애 RAII패턴을 사용할 수 있다.
	 만약 unique_ptr을 복사하려고 하면 삭제된 함수를 사용하려 했다는 오류가 발생한다.

[4.	삭제된 함수]
1.	사용을 원치 않는 함수를 삭제시켜버리는 방법은 C++11에 추가된 기능이다.
	class A{
		public:
			A(int a){};
			A(const A& a)=delete;//delete copy constructor explicitly!
	}
	
	int main(){
		A a(3);//possible
		A b(a);//impossible(copy constructor was deleted)
	}
	컴파일하면 복사생성자(const A& a)를 호출하는 부분에서 오류가 발생하는데, 복사생성자를 명시적으로 삭제했기 때문이다. 
	이러한 방법으로 프로그래머가 명시적으로 이 함수를 쓰지 말라고 표현함과 동시에 혹시 사용하더라도 컴파일 오류가 발생하게 된다.
2.	unique_ptr도 마찬가지로 unique_ptr의 복사생성자가 명시적으로 삭제되어 있다. 그 이유는 간단하게 unique_ptr은 어떠한 객체를 유일하게 소유해야 하기 때문이다.
	 만약 unique_ptr이 복사생성자를 사용하게 된다면 여러 unique_ptr들이 특정 객체를 소유하게 되는 문제가 발생하여 double free버그가 unique_ptr들이 소멸할 때 발생하게 된다.

[5.	unique_ptr 소유권 이전하기]
1.	unique_ptr은 복사가 불가능한 대신, 소유권을 이전할 수 있다. 
2.	소유권을 이전한 이전의 unique_ptr을 쓰지 않도록 유의하자.

[6.	unique_ptr을 함수 인자로 전달하기]
1.	대충의 정리
	-unique_ptr은 어떤 객체의 유일한 소유권을 나타내는 포인터이며, unique_ptr이 소멸될 때, 가리키던 객체 역시 소멸된다.
	-만약 다른 함수에서 unique_ptr이 소유한 객체에 일시적으로 접근하고 싶다면, get을 통해 해당 객체의 포인터를 전달하면 된다.
	-만약 소유권을 이동하고자 한다면, unique_ptr을 move하면 된다.

[7.	unique_ptr을 쉽게 생성하기]
1.	C++14부터 unique_ptr을 간단하게 만들 수 있는 std::make_unique함수를 제공한다. 
2.	std::unique_ptr<Foo> ptr(new Foo(3, 5)); 에서 Foo를 2번 입력하지 않게 std::make_unique<Foo>(3, 5);로 사용

[8.	unique_ptr을 원소로 가지는 컨테이너]
1.	copy constructor를 호출하지 않게 move constructor을 오버로딩시켜야 한다.
2.	emplace_back함수를 이용하여 vector안에 unique_ptr을 직접 생성하면서 집어넣을 수 있다. 즉 불필요한 생성->이동과정을 생략할 수 있다.
	emplace_back은 전달된 인자를 완벽한 전달(perfect forwarding)을 통해 직접 unique_ptr<A>의 생성자에 전달해서, vector맨 뒤에 unique_ptr<A> 객체를 생성해버리게 된다. 즉 애초에 생성을 vector맨 뒤에 하기에 불필요한 이동 연산이 필요없게 된다. 
	 다만 emplace_back사용 시 어떠한 생성자가 호출되는지를 주의해야 하는데,
	std::vector<int> v;
	v.emplace_back(100000);
	의 경우 100000의 int 값을 v에 추가하지만
	std::vector<std::vector<int>> v;
	v.emplace_back(100000);
	을 하게 되면 원소가 100000개 들어있는 벡터를 v에 추가하게 된다. 

*/
