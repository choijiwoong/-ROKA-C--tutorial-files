#include <iostream>

/*3 example crawling website
int main(){
	map<string, string> url_and_content;
	for(auto itr=url_and_content.begin(); itr!=url_and_content.end(); ++itr){
		const string& url=itr->first;
		itr->second=download(url);//download and return of site.
	}
}*/

#include <thread>
/*4
using std::thread;
void func1(){
	for(int i=0; i<10; i++)
		std::cout<<"working thread 1!"<<std::endl;
}
void func2(){
	for(int i=0; i<10; i++)
		std::cout<<"working thread 2!"<<std::endl;
}
void func3(){
	for(int i=0; i<10; i++)
		std::cout<<"working thread 3!"<<std::endl;
}

int main(){
	thread t1(func1);//make thread object! 
	thread t2(func2);
	thread t3(func3);
	
	//t1.join();//return when thread done their work.
	//t2.join();
	//t3.join();
	
	t1.detach();
	t2.detach();
	t3.detach();
	
	std::cout<<"exit main \n";
}*/

#include <cstdio>
#include <vector> 
/*5
using std::thread;
using std::vector;
void worker(vector<int>::iterator start, vector<int>::iterator end, int* result){
	int sum=0;
	for(auto itr=start; itr<end; ++itr)
		sum+=*itr;
	*result=sum;
	
	//get id of thread
	thread::id this_id=std::this_thread::get_id();
	printf("calculated result of %d to %d of thread %x : %d \n", *start, *(end-1), sum);//not std::cout!! 
}

int main(){
	vector<int> data(10000);
	for(int i=0; i<10000; i++)
		data[i]=i;
	
	vector<int> partial_sums(4);
	//vector that saves partual sums in each thread
	
	vector<thread> workers;
	for(int i=0; i<4; i++)
		workers.push_back(thread(worker, data.begin()+i*2500, data.begin()+(i+1)*2500, &partial_sums[i]));
		
	for(int i=0; i<4; i++)
		workers[i].join();
		
	int total=0;
	for(int i=0; i<4; i++)
		total+=partial_sums[i];
	
	std::cout<<"total sum : "<<total<<std::endl;
}*/

//6
using std::thread;
using std::vector;

void worker(int& counter){
	for(int i=0; i<10000; i++)
		counter++;
}
int main(){
	int counter=0;
	
	vector<thread> workers;
	for(int i=0; i<4; i++)
		workers.push_back(thread(worker, std::ref(counter)));
	for(int i=0; i<4; i++)
		workers[i].join();
		
	std::cout<<"Final result of Counter : "<<counter<<std::endl;//diffenent value!
}



/*
[1.	멀티 쓰레드 프로그램]
1.	작업관리자를 열업면 막대한 개수의 프로세스를 볼 수 있다. 우리가 흔히 1개의 프로그램을 가리킬 때 1개의 프로세스를 의미한다.
	이러한 프로세스는 CPU 코어에서 실행되는데, CPU는 한번에 한가지 연산밖에 못하기에 컨텍스트 스위칭(Context switching)을 이용하여 프로그램을 스위칭 하며 조금씩 연속적으로 실행시켜 처리한다.
	즉, CPU는 운영체제가 시키는 명령어를 실행할 뿐, 프로그램의 실행여부, 시간, 다음으로 스위치할 프로그램 등은 운영체제의 스케쥴러(scheduler)가 결정하게 된다.
	 이 CPU코어에서 돌아가는 프로그램 단위를 쓰레드(thread)라고 하는데, 즉 CPU코어하나에는 한번에 한 개의 쓰레드의 명령을 실행하게 된다.
	한 개의 프로세스는 최소 한 개의 쓰레드로 구성되며, 여러개의 쓰레드로 구성된 프로그램은 멀티 쓰레드(multithread) 프로그램이라고 한다.
	쓰레드와 프로세스의 가장 큰 차이점은 한 프로세스 안에 쓰레드가 여러개면 서로 같은 메모리를 공유하는 반면, 프로세스들은 서로 메모리를 공유하지 않는다는 것이다. 

[2.	CPU의 코어는 한 개가 아니다]
1.	근래의 CPU발전방향이 코어 하나의 동작속도를 높이기 보다는, CPU에 장착된 코어 개수를 늘리는 식으로 발전해왔다.
	따라서 싱글코어 CPU에서 아무리 멀티 쓰레드 프로그램이라 하더라도 결국 한번에 한 쓰레드만 실행할 수 있었지만, 멀티코어 CPU에서는 여러개의 쓰레드들을 효과적으로 실행할 수 있게되었다.
	(p.s SMT(Simultaneous Multithreading)기술을 통해 여러개의 코어처럼 쓸 수 있음) 

[3.	그래서 왜 멀티 쓰레드 인데?]
1.	병렬 가능한(Parallelizable)작업들을 분산하여 게산하는데에 효과적이다. 
	다만 피보나치 제귀계산과 같은 경우, Fn을 구하려면 Fn-1 Fn-2를 알아야하기에 parallelize(병렬화)한 속도가 차이가 없게 된다.
	고로 피보나치 수열을 계산하는 프로그램을 병렬화하는것은 매우 어렵다. 어떠한 연산(A)를 수행하기 위해 다른 연산(B)의 결과가 필요하기 때문인데, 우리는 이를 A가 B에 의존한다 라고 표현한다.
	즉, 프로그램 논리구조 상에서 연산들간의 의존관계가 많으면 병렬화가 어려워지고, 독립구조가 많으면 병렬화가 매우 쉬워진다.
2.	대기시간이 긴 작업들을 처리하는데 효과적이다.
	인터넷은 CPU처리속도에 비해 매우 느리다. ping속도가 요청을 보낸뒤 다시 돌아오는 시간을 의미하는데, 보통의 CPU가 1초에 10^9의 연산을 할 수 있기에, CPU를 비효율적으로 사용하는 셈이 된다.
	고로 다운로드 함수를 여러 쓰레드에서 부르면 컨텍스트 스위칭을 통해 기다리는 시간 없이 CPU를 최대한으로 사용할 수 있게 된다.
	
[4.	C++에서 쓰레드 생성하기]
1.	C++ 11부터 표준에 쓰레드가 추가되어 기존에 플랫폼마다 구현방법이 달랐던것과는 달리 쓰레드 사용이 매우 편리해졌다.
2.	#include <thread>하고 thread t1(func2) thread객체를 생성하면 끝이다.  t1은 인자로 전달받은 함수르 새로운 쓰레드에서 실행하게 된다.(그냥 한 코어에 쓰레드 3개가 컨텍스트 스위칭을 하면서 돌아갈 수도 있음. 그건 운영체제의 마음) 
	join()은 쓰레드가 실행을 종료하면 리턴하는 함수이다. 
	 만약 t2가 t1보다 먼저 종료되어도 t1.join()이 끝나고 t2.join()에서 바로 리턴된다. 
3.	만약 join을 하지 않게 되면 쓰레드의 내용이 채 실행되기도 전에 main함수가 종료되어 thread 객체의 소멸자가 호출된다. 근데 난 잘 되넴 헿 
	C++표준에 따르면 join되거나 detach되지 않는 쓰레드들의 소멸자가 호출되면 예외르 발생시키게 되어있다.(위의 경우)
4.	detach는 해당 쓰레드를 실행 시킨 후, 잊어버리는 것이다. 즉 백그라운드에서 돌아가는 것이다. 
	기본적으로 프로세스가 종료될 때, 해당 프로세스 안의 모든 쓰레드들은 종료 여부와 상관없이 자동으로 종료된다. 즉, main function에서 exit main을 print한다면 work thread ~를 출력할 수 없게 된다.
	 쓰레드를 detach하게 되면 main함수에서는 쓰레드들이 종료될 때 까지 기다리지 않는다. 고로 문자열을 표기하기도 전에 프로세스가 종료되거나 어느정도 실행되고 종료될 수 있다. 

[5.	쓰레드에 인자 전달하기]
1.	thread::id this_id=std::this_thread::get_id();로 어떤 쓰레드에서 작업중인지를 볼 수 있다.
	std::cout<<A<<B의 경우 A가 출력되는 동안은 다른 쓰레드가 내용을 출력할 수 없게 보장을 하지만, A의 출력이 끝나고 B가 출력되기 전에는 다른 쓰레드의 내용을 출력시킬 수 있기에
	printf를 사용했다. printf는 ""안에 있는 문자열을 출력할 때, 다른 쓰레드들이 그 사이에 메세지를 집어넣지 못하게 막아 방해받지 않고 출력이 가능하다. 

[6.	다른 쓰레드에서 메모리를 같이 접근한다면?]
1.	다음강좌에서 알아보자 

*/
