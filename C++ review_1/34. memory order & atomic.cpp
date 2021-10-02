#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

/*memory_order_relaxed adding order is not problem
void worker(std::atomic<int>* counter){
	for(int i=0; i<10000; i++)
		counter->fetch_add(1, std::memory_order_relaxed);//fetch_add is add with memory_order atomically
}

int main(){
	std::vector<std::thread> threads;
	std::atomic<int> counter(0);
	
	for(int i=0; i<4; i++)
		threads.push_back(std::thread(worker, &counter));
	
	for(int i=0; i<4; i++)
		threads[i].join();
		
	std::cout<<"Counter: "<<counter<<std::endl;
}*/

//synchronize by release, acquire
std::atomic<bool> is_ready;
std::atomic<int> data[3];

void producer(){
	data[0].store(1, std::memory_order_relaxed);
	data[1].store(2, std::memory_order_relaxed);
	data[2].store(3, std::memory_order_relaxed);
	is_ready.store(true, std::memory_order_release);//release!
}

void consumer(){
	while(!is_ready.load(std::memory_order_acquire)){}//acquire!
	
	std::cout<<"data[0]: "<<data[0].load(std::memory_order_relaxed)<<std::endl;
	std::cout<<"data[1]: "<<data[1].load(std::memory_order_relaxed)<<std::endl;
	std::cout<<"data[2]: "<<data[2].load(std::memory_order_relaxed)<<std::endl;
}

int main(){
	std::vector<std::thread> threads;
	
	threads.push_back(std::thread(producer));
	threads.push_back(std::thread(consumer));
	
	for(int i=0; i<2; i++)
		threads[i].join();
		
}

/*
1.	Cache hit, Cache miss, 캐시가 다 차면 처리하는 특정한 방식은 CPU마다 다르다. ex) Least Recently Used_LSU
2.	CPU pipelining; 한 작업이 끝나기 전에 다음 작업을 시작하는 방식으로 동시에 여러개의 작업을 실행하는 것 like decode, execute, write
3.	컴파일러만 명령어를 재배치를 하는게 아니라 CPU가 캐시에 있는 변수 순서로 재배치할 수도 있다.(RR(Read-Read) 순서) 
4.	C++의 모든 객체는 수정 순서(modification order)를 정의할 수 있다. "모든 쓰레드들이 동일한 값을 관찰할 필요는 없다."_동기화시간이 걸리기에 생략
5.	atomicity(원자성); CPU가 명령어 1개로 처리하는 명령으로, 중간에 다른 쓰레드가 끼어들 여지가 전혀 없는 연산이다.(뮤텍스가 필요없다) 
6.	is_lock_free() 함수로 atomic객체의 연산들이 원자적으로 구현될수 있는지를 확인하자.(lock이 필요하지 않다는 뜻) 
7.	memory_order; memory_order_relexed(자유로운 영혼), memory_order_acquire(뒤에께 위로 재배치 금지), memory_order_release(위에께 아래로 재배치 금지) 
	memory_order_acq_rel(acquire & release를 동시수행하는 fetch_add같은 함수), memory_order_seq_cst(sequential consistency 순차적 일관성을 보장), 
8.	memory_order_relexed는 너무 자유롭기에 주로 acquire나 release를 사용하는데, 이는 대표적으로 producer-consumer관계에서 is_ready가 true인데 데이터가 로드되지 않는 상황을 막아준다. 
	counter++은 counter.fetch_add(1, memory_order_seq_cst)와 동일한 연산이다. 
*/ 
