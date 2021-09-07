#include <iostream>
#include <thread>
#include <vector>
#include <mutex> 

#include <chrono>//std::chrono::miliseconds
#include <queue>
#include <string> 
#include <condition_variable> 

/*1
void worker(int& counter){
	for(int i=0; i<10000; i++)
		counter+=1;
}


int main(){
	int counter=0;
	std::vector<std::thread> workers;
	
	for(int i=0; i<4; i++)
		workers.push_back(std::thread(worker, std::ref(counter)));//we have to use std::ref for passing by reference
	for(int i=0; i<4; i++)
		workers[i].join();
	
	std::cout<<"Final Result of Counter :: "<<counter<<std::endl;
	
	return 0;
}*/

/*2 solution by using mutex
void worker(int& result, std::mutex& m){
	for(int i=0; i<10000; i++){
		m.lock();//give me 'mutex m'! Only one thread can use admission of m
		result+=1;
		m.unlock();//before this, infinitly wait. take care of deadlock situation
	}
} 

int main(){
	int counter=0;
	std::mutex m;//mutex object
	std::vector<std::thread> workers;
	
	for(int i=0; i<4; i++)
		workers.push_back(std::thread(worker, std::ref(counter), std::ref(m)));
	for(int i=0; i<4; i++)
		workers[i].join();
		
	std::cout<<"Final Result of Counter :: "<<counter<<std::endl;
}*/

/*2 use of std::lock_guard
void worker(int& result, std::mutex& m){
	for(int i=0; i<10000; i++){
		std::lock_guard<std::mutex> lock(m);//execute m.lock creating lock(m)
		result+=1;
	}//compiler unlocks m automatically destructing lock after compiler escapes scope
}
int main(){
	int counter=0;
	std::mutex m;
	std::vector<std::thread> workers;
	
	for(int i=0; i<4; i++)
		workers.push_back(std::thread(worker, std::ref(counter), std::ref(m)));
	for(int i=0; i<4; i++)
		workers[i].join();
	
	std::cout<<"Final Result of Counter :: "<<counter<<std::endl;
}*/

/*3 case deadlock with std::lock_guard 
void worker1(std::mutex& m1, std::mutex& m2){
	for(int i=0; i<10000; i++){//for unlock, we have to escape this scope
		std::lock_guard<std::mutex> lock1(m1);//1. m1 lock
		std::lock_guard<std::mutex> lock2(m2);//3. m2 lock possible? for m2 lock, m2's lock in worker2 has to escpe scope
	}
}
void worker2(std::mutex& m1, std::mutex& m2){
	for(int i=0; i<10000; i++){
		std::lock_guard<std::mutex> lock2(m2);//2. m2 lock
		std::lock_guard<std::mutex> lock1(m1);//4. but escape this scope, we have to lock m1. it's impossible because m1 is already locked in worker1
	}
}
int main(){
	int counter=0;
	
	std::mutex m1, m2;
	std::thread t1(worker1, std::ref(m1), std::ref(m2));
	std::thread t2(worker2, std::ref(m1), std::ref(m2));
	
	t1.join();
	t2.join();
	
	std::cout<<"finish!"<<std::endl;
}*/

/*3 get priority on thread
void worker1(std::mutex& m1, std::mutex& m2){
	for(int i=0; i<10; i++){
		m1.lock();//same code with lock_guard. it will be gotten priority so it doesn't have to change code.
		m2.lock();
		std::cout<<"Woker1 Hi!"<<i<<std::endl;
		m2.unlock();
		m1.unlock();
	}
}
void worker2(std::mutex& m1, std::mutex& m2){
	for(int i=0; i<10; i++){
		while(true){
			m2.lock();//it's no problem.
			//if m1 is locked in worker1, deadlock will be occured when we call m1.lock
			if(!m1.try_lock()){//if not, worker1's m1 is locked. we should give priority to worker1, our m2 have to be give to worker1. so unlock m2 and retry until lock both of m1 and m2.
				m2.unlock();
				continue;
			}
			//if m1's lock is possible, pass this code. 
			std::cout<<"Worker2 Hi!"<<i<<std::endl;
			m1.unlock();
			m2.unlock();
			break;
		}
	}
}
int main(){
	std::mutex m1, m2;
	
	std::thread t1(worker1, std::ref(m1), std::ref(m2));
	std::thread t2(worker2, std::ref(m1), std::ref(m2));
	
	t1.join();
	t2.join();
	
	std::cout<<"finish!"<<std::endl;
}*/
 
/*4
void producer(std::queue<std::string>* downloaded_pages, std::mutex* m, int index){//storage for downloaded pages, mutex for thread work, index for expression of thread and wait second
	for(int i=0; i<5; i++){//for work & make webpage's content by i
		std::this_thread::sleep_for(std::chrono::milliseconds(100*index));//wait 
		std::string content="Website : "+std::to_string(i)+" from thread("+std::to_string(index)+")\n";//make webpage's content
		
		m->lock();//data must be in critical section because downloaded_pages is shared by threads for prevention of race condition.
		downloaded_pages->push(content);//pass content to storage for downloaded pages.  
		m->unlock();
	}
}

void consumer(std::queue<std::string>* downloaded_pages, std::mutex* m, int* num_processed){//storage for sownloaded pages, mutex for thread work, num_processed for expression how many work do
	while(*num_processed<25){//num of pages that we will handle is 5 * 5 =25(5 thread, 5 content). In consumer's perception, it doesn't know when it get work so it must execute in while loop.
		m->lock();
		if(downloaded_pages->empty()){//if download_pageds empty, wait for a second. give priority to producer! commonly downloading speed is lower than consumer. so we pass priority
			m->unlock();//for work other(producer) thread. if it's not in this scope, it will make deadlock
			
			std::this_thread::sleep_for(std::chrono::milliseconds(10));//wait this thread for efficiency because CPU's speed is faster than download speed. 
			continue;//recheck condition
		}
		
		//if there exist downloaded_pages
		std::string content=downloaded_pages->front();//get page
		downloaded_pages->pop();//remove gotten page
		
		(*num_processed)++;
		m->unlock();
		
		//content handling part
		std::cout<<content;
		std::this_thread::sleep_for(std::chrono::milliseconds(80));//suppose working time
	}
}

int main(){
	//downloaded pages make to list, not handled.
	std::queue<std::string> downloaded_pages;//queue(FIFO) for first downloaded file first handling.
	std::mutex m;
	std::vector<std::thread> producers;
	
	for(int i=0; i<5; i++)
		producers.push_back(std::thread(producer, &downloaded_pages, &m, i+1));
	
	int num_processed=0;
	std::vector<std::thread> consumers;
	for(int i=0; i<3; i++)
		consumers.push_back(std::thread(consumer, &downloaded_pages, &m, &num_processed));
		
	for(int i=0; i<5; i++)
		producers[i].join();
		
	for(int i=0; i<3; i++)
		consumers[i].join();
}*/


//5 condition_variable used version of producer & consumer
void producer(std::queue<std::string>* downloaded_pages, std::mutex* m, int index, std::condition_variable* cv){
	for(int i=0; i<5; i++){
		std::this_thread::sleep_for(std::chrono::milliseconds(100*index));
		std::string content="Website : "+std::to_string(i)+" from thread("+std::to_string(index)+")\n";
		
		m->lock();
		downloaded_pages->push(content);
		m->unlock();
		
		cv->notify_one();//notify "content is ready" to consumer
		//it wake up one of thread and let it check condition. if condition is true, let it do work.
	}
}
void consumer(std::queue<std::string>* downloaded_pages, std::mutex* m, int* num_processed, std::condition_variable* cv){
	while(*num_processed<25){
		std::unique_lock<std::mutex> lk(*m);//it's simmilar to lock_guard.
		
		cv->wait(lk, [&] {return !downloaded_pages->empty() || *num_processed==25;});
		//we have to pass condition to condition_variable. if that condition is false, it sleep forever after unlocking lk before who wake it up.
		//it condition is true, cv.wait is returned and so next code.
		
		if(*num_processed==25){//for check whether cv's returned reason is end of works.
			lk.unlock();
			return;//exit thread. all works are done.
		}
		//else new work input
		std::string content=downloaded_pages->front();
		downloaded_pages->pop();
		
		(*num_processed)++;
		lk.unlock();
		
		std::cout<<content;
		std::this_thread::sleep_for(std::chrono::milliseconds(80));
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
	
	//if all producer's works are done, there should be some sleeping thread.
	//if we don't wake up sleeping thread, sleeping threads in condumer will not be joined.
	cv.notify_all();//wake up all threads that is sleeping with checking condition.
	//In this time, num_processed will be 25 already, so all threads will wake up.
	
	for(int i=0; i<3; i++)
		consumers[i].join();
}



/*
[0.	들어가기에 앞서]
1.	서로 다른 쓰레드들이 동일한 자원을 사용할 때 발생하는 문제를 경쟁 상태(race condition)이라고 부른다.

[1.	Race Condition]
1.	CPU에서 연산을 수행하기 위해 레지스터(register)에 데이터를 기록한 다음 연산을 수행한다. 레지스터의 크기는 매우 작은데, 64비트 컴퓨터에 경우 8바이트에 불과하다. 또한 일반적인 연산에서 사용되는 범용 레지스터의 경우 불과 16개밖에 없다.
2.	counter+=1이 실제로 처리되는 어셈블리 코드는 이러하다.
	mov rax, qword ptr [rbp - 8] //rbp-8을 rax에 대입. []의미는 해당 주소값을 읽으라는 의미이다.(C++의 포인터에 *의미와 같음). 이때 해당 주소부터 얼마나 읽어야 하는지를 명시해야하는데, qword는 8바이트를 의미한다.
	 ㄴ rax=*(int**)(rbp-8)  C Lang. 
	mov ecx, dword ptr [rax] //현재 rax에는 resault의 주소값이 담겨있기에 ecx에 result의 현재값이 들어가게 된다.
	 ㄴ ecx=*(int*)(rax) C Lang. 
	add ecx, 1//result에 1이 더해짐 
	mov dword ptr [rax], ecx //그 값이 저장됨 
	(add dword ptr [rax],1 이 안되는 이유는 CPU구조상 add명령은 반드시 역참조한 메모리가 아니라 레지스터에서 가능하기 때문이다.)
3.				<초기 counter=0;> 
	쓰레드 1               		쓰레드 2
	mov rax, qword ptr[rbp-8]	
	mov ecx, dword ptr[rax] 
								mov rax, qword ptr[rbp-8]
								mov ecx, dword ptr[rax]
								add ecx, 1
								mov dword ptr[rax], ecx
	add ecx, 1
	mov dword ptr[rax], ecx
			<counter+=1을 쓰레드 2곳에서 했는데 최종 결과가 1>
	각 쓰레드는 메모리를 공유할 수 있지만, 레지스터는 공유하지 않는다. 즉 각 쓰레드별로 고유의 레지스터를 가지고있다고 생각하면 된다.(쓰레드1과 2의 ecx는 다른거) 
	-쓰레드 1의 mov ecx부분에서 counter가 0이다.
	-쓰레드 2에서 ++을 하여 counter가 1이 되었다.
	-쓰레드 1의 add ecx부분에서 쓰레드 1의 ecx는 이전과 마찬가지로 0이기에 mov dword ptr에서 2가 아닌 1이 기록된다.
	-즉, counter에 2가 아닌 1이 기록된다. 이는 쓰레드에서 같은 메모리를 공유할 수 있지만 같은 레지스터 공간을 공유하지 않기 때문이다.
4.	운이 좋으면 쓰레드1중간에 2가 실행되는 일 없이 실행댈지도 모르지만, 그 스케쥴링은 운영체제의 몫이다. 멀티 쓰레드 프로그램의 겨우 프로그램 실행마다 그 결과가 달라질 수 있기에 제대로 플그램을 만들지 않았을 경우 디버깅이 매우매우 어려워질 수 있다.

[2.	뮤텍스(mutex)]
1.	위 문제는 counter+=1;을 여러 쓰레드에서 동시에 실행시켰기 때문이다. 그렇다면 한 번에 한 쓰레드에서만 위 코드를 실행시킬 수 있게 하자(mutex) 
	mutex는 상호 배제(mutual exclusion)에서 나온 단어이다. 
2.	한번에 한쓰레드에서만 mutex m의 사용권을 갖기에 아무리 많은 쓰레드들이 서로 다른 코어에서 돌아가고 있다 하더라도, 결국 mutex m 은 한 번에 한 쓰레드만 얻을 수 있기 때문에, 한 쓰레드만 유일하게 실행할 수 있게 된다.
	이렇게 m.lock()과 m.unlock()사이에 한 쓰레드만이 유일하게 실행할 수 있는 코드 부분을 임계 영역(critical section)이라고 부른다. 
3.	만약 unlock을 하지 않아 아무 쓰레드도 연산을 진행하지 못하게 되는 것을 데드락(deadlock)이라고 한다.
	고로 취득한 뮤텍스는 사용이 끝나면 반드시 반환을 해야 된다. 우리는 예전에 비슷한 문제를 사용한 기억이 있다. 
	 메모리를 할당하였으면 사용 후에 반드시 해제를 해야 하므로, 이 과정을 unique_ptr의 소멸자에서 처리하게 하였다.
4.	std::lock_guard객체는 뮤텍스를 인자로 받아서 생성하게 되는데, 생성자에서 뮤텍스를 lock하게 되고, lock_guard가 소멸될 때(스코프를 나가는 둥) 알아서 lock했던 뮤텍스를 unlock한다. 
	이것만 있으면 데드락은 절대 없는 것일까?

[3.	데드락(deadlock)]
1.	뮤텍스를 lock하면 반드시  unlock한다는 원칙을 지켰지만, 데드락을 피할 수 없었다. 
2.	해결할 수 있는 한가지 방법으로는 한 쓰레드에게 우선권을 주는 것이다. 대신, 한 쓰레드가 다른쓰레드에 비해 우위를 갖게 된다면, 한 쓰레드만 열심히 일하고 다른 쓰레드는 일할 수 없는 기아 상태(starvation)이 발생할 수 있다.
3.	try_lock()은 lock할수있으면 lock하고 true리턴하고 안되면 바로 false리턴. 
4.	이와 같이 데드락을 해결하는 것은 매우 복잡하고 완벽하지 않다. 고로 데드락이 없게끔 설계하는 것이 중요하고, 데드락을 피하기 위한 다음과 같은 가이드라인을 C++ Consurrency in Action이란 책에서 제시하고 있다.
	-중첩된 Lock사용을 피해라. 모든 쓰레드들이 최대 1개의 lock만을 소유하면 데드락은 발생하지 않고, 2개이상은 거의 필요자체가 없다. 정말로 필요한가? 
	-Lock을 소유시에 유저 코드 호출을 피해라. 유저코드에서 Lock을 소유하여 중첩되는 경우가 발생할 수 있기 때문이다.
	-Lock들은 언제나 반드시 정해진 순서로 획득해라. worker2에서 m2 m1순으로 lock하지 않았으면 데드락 자체가 발생하지 않았을 것이다. 

[4.	생산자(Producer)와 소비자(Consumer) 패턴]
1.	멀티 쓰레드 프로그램에서 가장 많이 등장하는 것이 생산자(producer)-소비자(consumer)패턴이다.
 	생산자는 무언가 처리할 일을 받아오는 쓰레드를 의미한다. 크롤링및 분석 프로그램을 생각해보자. 크롤링이 생산자고 분석이 소비자이다.
2.	queueu대신 vector도 가능하지만, 가장 먼저 들어온 page가 first element일텐데 이르 제가하는 것은 다소 느리기 때문이다. 
3.	위의 예시는 상당히 비효율적인게 consumer에서 *num_processed가 <25일때 무한 루프를 돌며 producer의 요청이 있는지를 항상 확인하고 있다(어느정도의 sleep은 만들었지만. )
	고로 아예 Consumer이 일이 없으면 재워두고 Producer가 일이오면 consumer에게 알려주는 것이 효율적이다.
	
[5.	condition_variable]
1.	어떤 조건이 만족할 때 까지 자라! 라는 명령을 조건 변수(condition variable)을 통해 해결할 수 있다.
2.	lock_guard는 생성자에서만 lock을 할 수 있는데, unique_lock은 unlock후에도 다시 lock을 할 수 있다. 
	더불어 cv->wait함수가 unique_lock을 인자로 받기에 사용했다. 
	
[6.	뭘 배웠지?]
1.	여러 쓰레드에서 같은 객체의 값을 수정하면 Race condition이 발생한다. 
	이것을 해결하기 위해 뮤텍스를 사용할 수 있지만 반환을 꼭 해야하기 때문에 안전하게 lock_guard나 unique_lock등을 사용한다. 
	뮤텍스를 사용할 때 데드락이 발생하여 디버깅이 어려울 수 있기에 주의해야 한다.
	생산자-소비자 패턴은 condition_variable을 사용하면 보다 효율적이고 쉬운 구현이 가능하다.

[7.	질의를 통한 보강]
1.	thread를 만드는데에 작업이 필요하기도 하고, 과다하게 많아지면 context-switcing때문에 전체 처리 속도가 늦어질 수 있기 때문에
	condition_variable을 통해 작업이 있을때 쓰레드를 만들기보다 이미 만들어놓은 쓰레드를 대기시켰다. 
2.	잠자는 이발사 문제(뮤텍스로 해결), 식사하는 철학자들 문제(한명을 반대로 움직이게해 대칭성을 제거하여 교착상태를 막는다), 독자-저자 문제(뮤텍스 사용하여 쓰는동안엔 저자만 접근), 생산자-소비자문제(생산자는 빈공간이 생긴 뒤에 mutex확인 후 진입, 소비자는 아이템이 생긴 뒤에 mutex로 진입) 
3.
*/
