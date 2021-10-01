#include <iostream>
#include <mutex>
#include <thread>

/*deadlock
void worker1(std::mutex& m1, std::mutex& m2){
	for(int i=0; i<10; i++){
		std::lock_guard<std::mutex> lock1(m1);//1. m1 lock!
		std::lock_guard<std::mutex> lock2(m2);//3. wait m2's unlock!
	}
}

void worker2(std::mutex& m1, std::mutex& m2){
	for(int i=0; i<10; i++){
		std::lock_guard<std::mutex> lock2(m2);//2. m2 lock!
		std::lock_guard<std::mutex> lock1(m1);//4. wait m1's unlock!
	}
}

int main(){
	int counter=0;
	std::mutex m1, m2;
	
	std::thread t1(worker1, std::ref(m1), std::ref(m2));
	std::thread t2(worker2, std::ref(m1), std::ref(m2));
	
	t1.join();
	t2.join();
	
	std::cout<<"end!"<<std::endl;
}*/

#include <chrono>
#include <condition_variable>
#include <queue>
#include <string>
#include <vector>
//producer-consumer pattern with condition_variable
void producer(std::queue<std::string>* downloaded_pages, std::mutex* m, int index, std::condition_variable* cv){
	for(int i=0; i<5; i++){
		std::this_thread::sleep_for(std::chrono::milliseconds(100*index));//suppose downloading speed
		std::string content="Website: "+std::to_string(i)+" from thread("+std::to_string(index)+")\n";
		
		m->lock();
		downloaded_pages->push(content);//same memory to threads. so let's in critical section
		m->unlock();
		
		cv->notify_one();//let's it know
	}
}

void consumer(std::queue<std::string>* downloaded_pages, std::mutex* m, int* num_processed, std::condition_variable* cv){
	while(*num_processed<25){
		std::unique_lock<std::mutex> lk(*m);
		cv->wait(lk, [&]{return !downloaded_pages->empty() || *num_processed==25; });
		
		if(*num_processed==25){//check is works done 
			lk.unlock();//unlock mutex
			return;
		}
		
		std::string content=downloaded_pages->front();
		downloaded_pages->pop();
		
		(*num_processed)++;
		lk.unlock();
		
		std::cout<<content;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

int main(){
	std::queue<std::string> downloaded_pages;
	std::mutex m;
	std::condition_variable cv;
	
	std::vector<std::thread> producers;
	
	for(int i=0; i<5; i++)
		producers.push_back(std::thread(producer, &downloaded_pages, &m, i+1, &cv));
		
	int num_processed=0;
	std::vector<std::thread> consumers;
	
	for(int i=0; i<3; i++)
		consumers.push_back(std::thread(consumer, &downloaded_pages, &m, &num_processed, &cv));
	
	for(int i=0; i<5; i++)
		producers[i].join();
	
	cv.notify_all();//awake sleeping thread
	
	for(int i=0; i<3; i++)
		consumers[i].join();
}
 
/*
1.	경쟁상태(Race condition); 서로 다른 쓰레드들이 동일한 자원을 사용할때 
2.	멀티쓰레딩은 제대로 프로그램을 만들지 않았을 경우 디버기이 겁나 어렵다. 고로 mutex(상호 배제_mutual exclusion)를 사용한다.
3.	임계 영역(critical section); 한 쓰레드만이 유일하게 실행할 수 있는 코드 부분
4.	데드락(deadlock); unlock안해서 무한정 기다림. 고로 mutual exclusion은 사용 후 무조건 반환을 해야한다. 
	이때 unique_ptr처럼 lock_guard<std::mutex>로 mutex의 소멸자를 처리할 수 있다. 
5.	데드락을 피하기 위해 어떤 쓰레드에게 우선순위를 주게 된다면, 우선적인 쓰레드에 작업이 쏠리고 다른 쓰레드를 일하지 않는 기아 상태(starvation)이 발생할 수 있다.
	우선순위는 try_lock으로 뮤텍스의 상태를 if에 넣어 처리 가능하다. 
6.	데드락을 피하려면 하나의 쓰레드에서 여러개의 mutex사용을 지양하고, Lock들을 정해진 순서로 획득하자. 
7.	생산자-소비자 패턴에선 FIFO의 queue를 사용했다. vector는 먼저들어온게 첫번째 원소에 저장되는데 이를 제거하는 속도가 느리기에.
8.	일이있는지 수시로 확인하는것보다 일이있으면 신호를 보내 깨우는 것이 효율적이다. condition_variable
9.	lock_guard의 경우 생성자 외에 따로 lock이 불가하지만, unique_lock은 unlock후에 lock이 가능하다는 차이점밖에 없다. 그냥 cv->wait가 unique_lock을 인자로 받아서 그리 주었다.
10.	cv->wait(lk, [&]{ return 조건;});으로 함 
*/ 
