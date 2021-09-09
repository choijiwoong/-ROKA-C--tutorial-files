#include <iostream>
#include <atomic>
#include <thread>
#include <vector> 
#include <cstdio>//6

/*3
//C++ version 
int a=0;
int b=0;

void foo(){
	a=b+1;
	b=1;
}

//Assembly version
foo():
	mov eax, DWORD PTR b[rip]
	mov DWORD PTR b[rip], 1//a=b+1을 하는 와중에 b=1을 실행!! 
	add eax, 1
	mov DWORD PTR a[rip], eax
	ret
b:
	.zero 4
a:
	.zero 4
*/

/*5 std::atomic for atomically calculation
void worker(std::atomic<int>& counter){
	for(int i=0; i<10000; i++)
		counter++;//lock add DWORD PTR [rdi], 1  it's expressed by one line in assembly. 
		//lock add do all work like 'read rdi, add 1, write rdi' by once.
}

int main(){
	std::atomic<int> counter(0);
	std::vector<std::thread> workers;
	
	for(int i=0; i<4; i++)
		workers.push_back(std::thread(worker, ref(counter)));
	for(int i=0; i<4; i++)
		workers[i].join();
		
	std::cout<<"Final Result of Counter :: "<<counter<<std::endl;//it's perfectly printed to 40000 without mutex's guard! 

	std::atomic<int> x;
	std::cout<<"is lock free ? : "<<std::boolalpha<<x.is_lock_free()<<std::endl;//we can check if it can be changed to atomic code by .is_lock_free() 
	//lock means do work atomically in assembly. lock free means we can do work correctly without object like mutex(lock, unlock)
}*/

/*6 for show concept of std::memory_order_relaxed 
using std::memory_order_relaxed;
void t1(std::atomic<int>* a, std::atomic<int>* b){
	b->store(1, memory_order_relaxed);//write b=1
	int x=a->load(memory_order_relaxed);//read x=1
	//these can be changed by CPU. memory_order_realaxed gives infinite free of calculation order to CPU. so CPU can calculate fast. 
	
	printf("x : %d \n", x);
}

void t2(std::atomic<int>* a, std::atomic<int>* b){
	a->store(1, memory_order_relaxed);//write a=1
	int y=b->load(memory_order_relaxed);//read y=b
	
	printf("y: %d \n", y);
}
int main(){
	std::vector<std::thread> threads;
	std::atomic<int> a(0);
	std::atomic<int> b(0);
	
	threads.push_back(std::thread(t1, &a, &b));
	threads.push_back(std::thread(t2, &a, &b));
	
	for(int i=0; i<2; i++)
		threads[i].join();
}*/

/*6 example of using std::memory_order_relaxed
using std::memory_order_relaxed;
void worker(std::atomic<int>* counter){
	for(int i=0; i<10000; i++){
		//other works
		counter->fetch_add(1, memory_order_relaxed);//It's same to counter++ but it can set memory approach way unlike counter++
		//The reason that we can use memory_order_relaxed is we don't have to prohibit relocation with other memory operations.
		//It's not problem if counter is added 1 resaultly without ordering of operation.
	}
}
int main(){
	std::vector<std::thread> threads;
	std::atomic<int> counter(0);
	
	for(int i=0; i<4; i++)
		threads.push_back(std::thread(worker, &counter));
	for(int i=0; i<4; i++)
		threads[i].join();
		
	std::cout<<"Counter : "<<counter<<std::endl;
}*/

/*6 limit of std::memory_order_relaxed
using std::memory_order_relaxed;

void producer(std::atomic<bool>* is_ready, int* data){
	*data=10;
	is_ready->store(true, memory_order_relaxed);//if CPU change order, it can pass signal is_ready is true before *data=10;
}

void consumer(std::atomic<bool>* is_ready, int* data){
	while(!is_ready->load(memory_order_relaxed)){//read is_ready's value by load function with rule memory_order_relaxed that allow changable to CPU. 
	}
	std::cout<<"Data : "<<*data<<std::endl;//if CPU change order, it can print Data : ~ before get signal is_ready is true or before set *data=10 in producer
}

int main(){
	std::vector<std::thread> threads;
	std::atomic<bool> is_ready(false);
	int data=0;
	
	threads.push_back(std::thread(producer, &is_ready, &data));
	threads.push_back(std::thread(consumer, &is_ready, &data));
	for(int i=0; i<2; i++)
		threads[i].join();
	//it can print Data : 0!
}*/

/*6 solution of limit of std::memory_order_relaxed by using std::memory_order_release & std::memory_order_acquire
void producer(std::atomic<bool>* is_ready, int* data){
	*data=10;
	is_ready->store(true, std::memory_order_release);//it means not replacing by CPU now without this line. up->down X
	//so *data=10 can't here by CPU
}

void consumer(std::atomic<bool>* is_ready, int* data){
	//so std::cout can't here by CPU
	while(!is_ready->load(std::memory_order_acquire)){//it means let replacing by CPU now without this line. down->up X
	}
	std::cout<<"Data : "<<*data<<std::endl;
}

int main(){
	std::vector<std::thread> threads;
	std::atomic<bool> is_ready(false);
	int data=0;
	
	threads.push_back(std::thread(producer, &is_ready, &data));
	threads.push_back(std::thread(consumer, &is_ready, &data));
	for(int i=0; i<2; i++)
		threads[i].join();
	//It's impossible print Data : 0!
}*/

/*6 example of understanding of release & acquire with synchronizing.
using std::memory_order_relaxed;

std::atomic<bool> is_ready;
std::atomic<int> data[3];

void producer(){
	data[0].store(1, memory_order_relaxed);
	data[1].store(2, memory_order_relaxed);
	data[2].store(3, memory_order_relaxed);//these can replace each other, but it can't change to under of is_ready.st~
	is_ready.store(true, std::memory_order_release);
}

void consumer(){
	while(!is_ready.load(std::memory_order_acquire)){
	}//wait ready of data
	
	std::cout<<"data[0] : "<<data[0].load(memory_order_relaxed)<<std::endl;//these can replace each other, but it can't change to upper of is_ready.lo~
	std::cout<<"data[1] : "<<data[1].load(memory_order_relaxed)<<std::endl;
	std::cout<<"data[2] : "<<data[2].load(memory_order_relaxed)<<std::endl;
}

int main(){
	std::vector<std::thread> threads;
	
	threads.push_back(std::thread(producer));
	threads.push_back(std::thread(consumer));
	for(int i=0; i<2; i++)
		threads[i].join();
}*/

/*6 for necessity of sequential consistency by memory_order_seq_cst
using std::thread;
std::atomic<bool> x(false);
std::atomic<bool> y(false);
std::atomic<int> z(0);

void write_x() { x.store(true, std::memory_order_release); }
void write_y() { y.store(true, std::memory_order_release); }

void read_x_then_y(){
	while(!x.load(std::memory_order_acquire)){
	}
	
	if(y.load(std::memory_order_acquire)){
		++z;
	}
}
void read_y_then_x(){
	while(!y.load(std::memory_order_acquire)){
	}
	if(x.load(std::memory_order_acquire)){
		++z;
	}
}

int main(){
	thread a(write_x);
	thread b(write_y);
	thread c(read_x_then_y);
	thread d(read_y_then_x);
	
	a.join();
	b.join();
	c.join();
	d.join();
	
	std::cout<<"z : "<<z<<std::endl;
	//it can print 0 because these code is happening release-acquire  synchronizing of write_x & read_x_then_y, write_y & read_y_then_x.
	//it means x.store can execute before y.store in perception of read_x_then_y and y.store can execute before x.store in perception of read_y_then_x.
	//if both situation is occured, both if's load become false, it makes z to 0..
	//but if we use memory_order_seq_cst, it vouchs sequential consistency that makes we can see same calculation order at all threads.
}*/

//6 solution by using std::memory_order_seq_cst
using std::memory_order_seq_cst;
using std::thread;

std::atomic<bool> x(false);
std::atomic<bool> y(false);
std::atomic<int> z(0);

void write_x(){ x.store(true, memory_order_seq_cst); }
void write_y(){ y.store(true, memory_order_seq_cst); }

void read_x_then_y(){
	while(!x.load(memory_order_seq_cst)){
	}
	if(y.load(memory_order_seq_cst)){
		++z;
	}
}
void read_y_then_x(){
	while(!y.load(memory_order_seq_cst)){
	}
	if(x.load(memory_order_seq_cst)){
		++z;
	}
}

int main(){
	thread a(write_x);
	thread b(write_y);
	thread c(read_x_then_y);
	thread d(read_y_then_x);
	
	a.join();
	b.join();
	c.join();
	d.join();
	
	std::cout<<"z : "<<z<<std::endl;//print 1 or 2???
}

/*
[0.	들어가기 전에]
1.	C++ 멀티 쓰레딩을 위해 제공되는 기본 요소인 쓰레드, 뮤텍스, 조건변수들에 대해 조금 더 세밀하게 컨트롤 할 수 있는 요소를 볼것이라 넘어가도 좋다.
	(C++의 굉장히 섬세한 디테일) 
	
[1. 메모리는 엄청 느리다.]
1.	기본적으로 CPU와 RAM은 물리적으로 떨어져있기에 데이터를 읽어오는데에 시간이 좀 걸린다. intel i7-6700CPU의 경우 최소 42사이클이 걸리는데, CPU에서 덧셈 한번이 1사이클이라는 것을 보아 
	메모리에서 데이터 한 번 읽을 때마다 42번의 덧셈연산시간을 손해보는 것이다.

[2.	캐시]
1.	이를 보완하기 위한 것으로 CPU칩 안에 조그마난 메모리로 CPU와 거의 붙어있어 속도가 매무 빠르다. (연산하는 Core보다 캐시가 더 큼 쿠쿠루삥빵뽕) 
	캐시에 있는 데이터를 다시 요청해서 시간을 절약하는 것을 Cache hit이라고 하며, 캐시에 없어 메모리를 갔다 오는 것을 Cache miss라고 한다.
2.	CPU가 어느 영역에 자주 접근할지는 모른다. CPu에서 Cache가 작동하는 것은 오로지 아래의 방식을 따른다.
	-메모리를 읽으면 일단 캐시로
	-캐시가 다차면 특정한 방식에 따라 처리
	여기서의 특정한 방식은 CPU마다 다른데, 대표적인 예로 가장 이전에 쓴(LRU-Least Recently Used) 캐시를 날리고 그 자리에 새 캐시를 기록하는 방식이 있다.
	이 방식의 장점은 최근에 접근한 데이터를 자주 반복하여 접근하면 매우 유리하다는 것이다.
3.	<case 1>
	for(int i=0; i<10000; i++)
		for(int j=0; j<10000; j++)
			s+=data[j];
	<case 2>
	for(int j=0; j<10000; j++)
		for(int i=0; i<10000; i++)
			s+=data[j];
	는 동일한 연산인데, 두번째 방식이 더 빨리 작동한다. 첫번째는 1KB캐시에서 j=256이 될때 Cache miss가 되는 반면에 두번째는 data[0]을 10000번 연속접근 하므로, 처음접근을 제외한 나머지 9999번이 Cache hit이 되어 빠르게 덧셈을 수행할 수 있다. 
	
[3.	컴퓨터는 사실 여러분이 시키는 대로 하지 않는다.]
1.	a=b+1부분의 실행이 채 끝나기도 전에 b=1이 먼저 실행이 끝난 것이다. foo함수 입장에서 최종적으로 a는 1, b는 1이 들어있어서 문제가 없지만,
	만약 다른 쓰레드가 있어서 a와 b의 값을 확인했을 때, a가 0인데 b가 1일 수 있다는 것이다! 이는 현대의 CPU가 한 번에 한 명령어씩 실행하는 것이 아니기 때문이다.
2.	CPU 파이프라이닝(pipelining)
	실제 CPU에서 명령어를 실행할 때 fetch, decode, execute, write등의 여러 단계를 거치게 되는데, fetch가 끝날때 까지 decode를 기다리게 하는 것은 비효율 적이기에(건조기 기다리느라 빨래를 계속 못하기에) 
	컴파일러는 최대한 CPU의 파이프라인을 효율적으로 활용할 수 있도록 명령어를 재배치 한다.
	 이때 최종 결과물은 당연히 달라지면 안되겠지만, 문제는 다른 쓰레드들을 고려하지 않는다는 점이다. 
	//현재 a, b=0
	a=1;//캐시에 없음 
	b=1;//캐시에 있음
	b가 캐시에 있기에 a보다 b를 빠르게 처리 가능하다. 따라서 CPU에서 위 코드가 실행될 때, b=1이 a=1보다 먼저 실행될 수 있다.
	 따라서 다른 쓰레드에서 a는 0인데, b가 1인 순간을 관찰할 수 있다는 것이다!
	(p.s)
	읽기-읽기 순의 명령어를 RR(Read-Read)순서라고 하는데, 인텔CPU에서는 RR명령어의 재배치를 금지하기에 위의 상황이 발생하지 않는다.
	하지만 ARM의 경우 위를 허용하므로 위와 같은 상황이 발생할 수 있다.
	참고로 인텔 CPU는 유일하게 쓰기-읽기의 재비치는 가능하쿠쿠루삥빵뽕

[4.	무엇을 믿어야 하는가?]
1.	C++의 모든 객체들은 수정 순서(mofification order)을 정의할 수 있다. 이는 객체의 값을 실시간으로 확인가능한 전지전능한 것이 있다 할때, 해당객체의 값변화를 기록한 것이다.
	a=5->8->6->3
	T1이 관찰한 수정순서: 5->3 
	T2가 관찰한 수정순서: 8->6->3
	T3이 관찰한 수정순서: 5->6->3
	모든 쓰레드들이 수정 순서에 동의한다.(T3이 8->5순으로 관찰이 불가능) 
	C++에서는 원자적 연산을 할 경우에 모든 쓰레드에서 같은 객체에 대하여 동일한 수정 순서를 관찰할 수 있다. 
	다른 말로, 같은 시간에 변수 a의 값을 관찰했다고 해서 결과만 같으면 되기에 굳이 모든 쓰레드들이 동일한 값을 관찰할 필요는 없다라는 것이다.
	 쓰레드 간에 같은 시간에 다른 값을 리턴해도 된다는 점이 이질적일 수도 있으나, CPU캐시가 각 코어별로 존재하기 때문에 이를 강제할 수 없다.
	즉, 쓰레드 1에서 a=5후에 자신의 캐시에만 기록하고 다른 코어에 알리지 않으면 쓰레드3에서 a를 확인 시 5를 얻는다는 보장이 없다는 것이다.
2.	물론 매번 값을 기록할 때, 모든 캐시에 동기화를 시킬 수 있겠지만, 이 작업은 시간을 꽤나 잡아먹기에 C++에서는 로우레벨 언어 답게, 이를 세밀하게 조정할 수 있는 여러가지 도구들을 제공할 수 있다.

[5.	원자성(atomicity)]
1.	앞서 C++에서 모든 쓰레드들이 수정 순서에 동의해야만 하는 경우를 모든 연산들이 원자적일 때라고 하였다.
	원자적인 연산이 아닌 경우엔 직접 적절한 동기화 방법으로 처리해야 한다. 그렇지 않으면 프로그램이 정의되지 않은 행동(undefined behavior)을 할 수 있다.
2.	원자적 연산이란, CPU가 명령어 1개로 처리하는 명령으로 ,중간에 다른 쓰레드가 끼어들 여지가 전혀 없는 연산을 말한다. 즉 연산을 했다 혹은 안했다만 존재하기에 이를 원자적(atomic)이라고 한다.
	C++에서 지원하는 원자적 연산들은 올바른 연산을 위해 뮤텍스가 필요하지 않기에 속도도 더 빠르다. 
3.	std::atomic<int> counter(0); 처럼 템플릿 인자로 타입을 전달하면 된다. 이는 우리가 어느 CPU에서 실행할 지(x86) 컴파일러가 알기 때문에 특이적인 명령어를 제공할 수 있는 것이다.
	CPU에 따라 위의 lock add와 같은 명령이 없어 원자적인 코드를 생성할 수 없는 경우도 있는데, 이는 atomic 객체의 연산들이 정말 원자적으로 구현될 수 있는지를 확인하는 is_lock_free()함수를 호출하면 된다.

[6.	memory_order]
1.	atomic객체들의 경우 원자적 연산 시에 어떠한 방식으로 메모리에 접근할지 지정할수 있다.
	memory_order_relexed는 가장 느슨한 조건이다. 즉, 이 방식을 사용할 경우, 주위의 다른 메모리 접근들과 순서가 바뀌어도 무방하다.
	다시 말해 서로 다른 변수의 relaxed메모리 연산은 CPU마음대로 재배치 할 수 있다(단일 쓰레드 관점에서 결과가 동일하다면)
2.	relaxed메모리 연산을 사용하면 예상치 못한 결과가 나올 수 있지만, 어떠한 작업이 늦게 되든 안되든 결과적으로 수행만 되면 경우에 사용한다.(속도가 빨라지기에 CPU의 재배치로)
3.	memory_order_acquire과 memory_order_release
	memory_order_relaxed는 CPU에 너무 많은 자유를 부여하기에 실제로 사용되는 경우가 제한적이다.
	 위의 예시와 같은 생산사-소비자 관계에서는 memory_order_relaxed를 사용할 수 없다. 
	memory_order_release는 해당 명령 이전의 모든 메모리 명령들이 해당 명령 이후로 재배치 되는 것을 금지한다. 만약 같은 변수를 acquire으로 읽는 쓰레드는 release이전의 모든 명령들이 해당 쓰레드에 의해 관찰 될 수 있어야 한다.
	memory_order_acquire은 해당 명령 뒤에오는 모든 메모리 명령들이 해당 명령 위로 재배치 되는 것을 금지한다.(release와 반대) 
	 기억하기 쉽게 생각하면 기존의 relaxed의 속성을 release잃어 아래로는 chage불가, acquire얻어 아래부터 change 가능.
4.	memory_order_acq_rel은 acquire과 release를 모두 수행하는 것으로, 읽기와 쓰기를 모두 수행하는 fetch_add와 같은 함수에서 사용된다.
	memory_order_seq_cst는 메모리 명령의 순차적 일관성(sequential consistency)를 보장해준다. 즉, 메모리 명령 재배치도 없고, 모든 쓰레드에서 모든 시점에 동일한 값을 관찰할 수 있는, CPU가 그대로 작동하는 방식이다. 
	 하지만 멀티 코어 시스템에서 memory_order_seq_cst는 꽤 비싼 연산이다. AMD의 x86 CPU의 경우 거의 sequential consistency가 보장되어 큰 차이가 없지만 ARM계열의 CPU는 consumes a lot of CPU's synchronizing cost for vouching sequential consistancy. 
	고로 꼭 필요한 경우에만 memory_order_seq_cst를 사용하기로 하자(사실 atomic객체의 default setting 이 memory_order_seq_cst임 쿠쿠루삥빵뽕)
5.	허용된 memory_order는 쓰기, 읽기, 읽고수정하고쓰기 마다 나뉘어 있는데, 대충 정리하면 default setting인 seq_cst보다 값싼 명령을 사용하여 프로그램의 효율을 높일 수 있다! 
*/ 
