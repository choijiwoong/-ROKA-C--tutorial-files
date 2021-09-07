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
[0.	���⿡ �ռ�]
1.	���� �ٸ� ��������� ������ �ڿ��� ����� �� �߻��ϴ� ������ ���� ����(race condition)�̶�� �θ���.

[1.	Race Condition]
1.	CPU���� ������ �����ϱ� ���� ��������(register)�� �����͸� ����� ���� ������ �����Ѵ�. ���������� ũ��� �ſ� ������, 64��Ʈ ��ǻ�Ϳ� ��� 8����Ʈ�� �Ұ��ϴ�. ���� �Ϲ����� ���꿡�� ���Ǵ� ���� ���������� ��� �Ұ� 16���ۿ� ����.
2.	counter+=1�� ������ ó���Ǵ� ����� �ڵ�� �̷��ϴ�.
	mov rax, qword ptr [rbp - 8] //rbp-8�� rax�� ����. []�ǹ̴� �ش� �ּҰ��� ������� �ǹ��̴�.(C++�� �����Ϳ� *�ǹ̿� ����). �̶� �ش� �ּҺ��� �󸶳� �о�� �ϴ����� ����ؾ��ϴµ�, qword�� 8����Ʈ�� �ǹ��Ѵ�.
	 �� rax=*(int**)(rbp-8)  C Lang. 
	mov ecx, dword ptr [rax] //���� rax���� resault�� �ּҰ��� ����ֱ⿡ ecx�� result�� ���簪�� ���� �ȴ�.
	 �� ecx=*(int*)(rax) C Lang. 
	add ecx, 1//result�� 1�� ������ 
	mov dword ptr [rax], ecx //�� ���� ����� 
	(add dword ptr [rax],1 �� �ȵǴ� ������ CPU������ add����� �ݵ�� �������� �޸𸮰� �ƴ϶� �������Ϳ��� �����ϱ� �����̴�.)
3.				<�ʱ� counter=0;> 
	������ 1               		������ 2
	mov rax, qword ptr[rbp-8]	
	mov ecx, dword ptr[rax] 
								mov rax, qword ptr[rbp-8]
								mov ecx, dword ptr[rax]
								add ecx, 1
								mov dword ptr[rax], ecx
	add ecx, 1
	mov dword ptr[rax], ecx
			<counter+=1�� ������ 2������ �ߴµ� ���� ����� 1>
	�� ������� �޸𸮸� ������ �� ������, �������ʹ� �������� �ʴ´�. �� �� �����庰�� ������ �������͸� �������ִٰ� �����ϸ� �ȴ�.(������1�� 2�� ecx�� �ٸ���) 
	-������ 1�� mov ecx�κп��� counter�� 0�̴�.
	-������ 2���� ++�� �Ͽ� counter�� 1�� �Ǿ���.
	-������ 1�� add ecx�κп��� ������ 1�� ecx�� ������ ���������� 0�̱⿡ mov dword ptr���� 2�� �ƴ� 1�� ��ϵȴ�.
	-��, counter�� 2�� �ƴ� 1�� ��ϵȴ�. �̴� �����忡�� ���� �޸𸮸� ������ �� ������ ���� �������� ������ �������� �ʱ� �����̴�.
4.	���� ������ ������1�߰��� 2�� ����Ǵ� �� ���� ��������� ������, �� �����층�� �ü���� ���̴�. ��Ƽ ������ ���α׷��� �ܿ� ���α׷� ���ึ�� �� ����� �޶��� �� �ֱ⿡ ����� �ñ׷��� ������ �ʾ��� ��� ������� �ſ�ſ� ������� �� �ִ�.

[2.	���ؽ�(mutex)]
1.	�� ������ counter+=1;�� ���� �����忡�� ���ÿ� ������ױ� �����̴�. �׷��ٸ� �� ���� �� �����忡���� �� �ڵ带 �����ų �� �ְ� ����(mutex) 
	mutex�� ��ȣ ����(mutual exclusion)���� ���� �ܾ��̴�. 
2.	�ѹ��� �Ѿ����忡���� mutex m�� ������ ���⿡ �ƹ��� ���� ��������� ���� �ٸ� �ھ�� ���ư��� �ִ� �ϴ���, �ᱹ mutex m �� �� ���� �� �����常 ���� �� �ֱ� ������, �� �����常 �����ϰ� ������ �� �ְ� �ȴ�.
	�̷��� m.lock()�� m.unlock()���̿� �� �����常�� �����ϰ� ������ �� �ִ� �ڵ� �κ��� �Ӱ� ����(critical section)�̶�� �θ���. 
3.	���� unlock�� ���� �ʾ� �ƹ� �����嵵 ������ �������� ���ϰ� �Ǵ� ���� �����(deadlock)�̶�� �Ѵ�.
	��� ����� ���ؽ��� ����� ������ �ݵ�� ��ȯ�� �ؾ� �ȴ�. �츮�� ������ ����� ������ ����� ����� �ִ�. 
	 �޸𸮸� �Ҵ��Ͽ����� ��� �Ŀ� �ݵ�� ������ �ؾ� �ϹǷ�, �� ������ unique_ptr�� �Ҹ��ڿ��� ó���ϰ� �Ͽ���.
4.	std::lock_guard��ü�� ���ؽ��� ���ڷ� �޾Ƽ� �����ϰ� �Ǵµ�, �����ڿ��� ���ؽ��� lock�ϰ� �ǰ�, lock_guard�� �Ҹ�� ��(�������� ������ ��) �˾Ƽ� lock�ߴ� ���ؽ��� unlock�Ѵ�. 
	�̰͸� ������ ������� ���� ���� ���ϱ�?

[3.	�����(deadlock)]
1.	���ؽ��� lock�ϸ� �ݵ��  unlock�Ѵٴ� ��Ģ�� ��������, ������� ���� �� ������. 
2.	�ذ��� �� �ִ� �Ѱ��� ������δ� �� �����忡�� �켱���� �ִ� ���̴�. ���, �� �����尡 �ٸ������忡 ���� ������ ���� �ȴٸ�, �� �����常 ������ ���ϰ� �ٸ� ������� ���� �� ���� ��� ����(starvation)�� �߻��� �� �ִ�.
3.	try_lock()�� lock�Ҽ������� lock�ϰ� true�����ϰ� �ȵǸ� �ٷ� false����. 
4.	�̿� ���� ������� �ذ��ϴ� ���� �ſ� �����ϰ� �Ϻ����� �ʴ�. ��� ������� ���Բ� �����ϴ� ���� �߿��ϰ�, ������� ���ϱ� ���� ������ ���� ���̵������ C++ Consurrency in Action�̶� å���� �����ϰ� �ִ�.
	-��ø�� Lock����� ���ض�. ��� ��������� �ִ� 1���� lock���� �����ϸ� ������� �߻����� �ʰ�, 2���̻��� ���� �ʿ���ü�� ����. ������ �ʿ��Ѱ�? 
	-Lock�� �����ÿ� ���� �ڵ� ȣ���� ���ض�. �����ڵ忡�� Lock�� �����Ͽ� ��ø�Ǵ� ��찡 �߻��� �� �ֱ� �����̴�.
	-Lock���� ������ �ݵ�� ������ ������ ȹ���ض�. worker2���� m2 m1������ lock���� �ʾ����� ����� ��ü�� �߻����� �ʾ��� ���̴�. 

[4.	������(Producer)�� �Һ���(Consumer) ����]
1.	��Ƽ ������ ���α׷����� ���� ���� �����ϴ� ���� ������(producer)-�Һ���(consumer)�����̴�.
 	�����ڴ� ���� ó���� ���� �޾ƿ��� �����带 �ǹ��Ѵ�. ũ�Ѹ��� �м� ���α׷��� �����غ���. ũ�Ѹ��� �����ڰ� �м��� �Һ����̴�.
2.	queueu��� vector�� ����������, ���� ���� ���� page�� first element���ٵ� �̸� �����ϴ� ���� �ټ� ������ �����̴�. 
3.	���� ���ô� ����� ��ȿ�����ΰ� consumer���� *num_processed�� <25�϶� ���� ������ ���� producer�� ��û�� �ִ����� �׻� Ȯ���ϰ� �ִ�(��������� sleep�� ���������. )
	��� �ƿ� Consumer�� ���� ������ ����ΰ� Producer�� ���̿��� consumer���� �˷��ִ� ���� ȿ�����̴�.
	
[5.	condition_variable]
1.	� ������ ������ �� ���� �ڶ�! ��� ����� ���� ����(condition variable)�� ���� �ذ��� �� �ִ�.
2.	lock_guard�� �����ڿ����� lock�� �� �� �ִµ�, unique_lock�� unlock�Ŀ��� �ٽ� lock�� �� �� �ִ�. 
	���Ҿ� cv->wait�Լ��� unique_lock�� ���ڷ� �ޱ⿡ ����ߴ�. 
	
[6.	�� �����?]
1.	���� �����忡�� ���� ��ü�� ���� �����ϸ� Race condition�� �߻��Ѵ�. 
	�̰��� �ذ��ϱ� ���� ���ؽ��� ����� �� ������ ��ȯ�� �� �ؾ��ϱ� ������ �����ϰ� lock_guard�� unique_lock���� ����Ѵ�. 
	���ؽ��� ����� �� ������� �߻��Ͽ� ������� ����� �� �ֱ⿡ �����ؾ� �Ѵ�.
	������-�Һ��� ������ condition_variable�� ����ϸ� ���� ȿ�����̰� ���� ������ �����ϴ�.

[7.	���Ǹ� ���� ����]
1.	thread�� ����µ��� �۾��� �ʿ��ϱ⵵ �ϰ�, �����ϰ� �������� context-switcing������ ��ü ó�� �ӵ��� �ʾ��� �� �ֱ� ������
	condition_variable�� ���� �۾��� ������ �����带 ����⺸�� �̹� �������� �����带 �����״�. 
2.	���ڴ� �̹߻� ����(���ؽ��� �ذ�), �Ļ��ϴ� ö���ڵ� ����(�Ѹ��� �ݴ�� �����̰��� ��Ī���� �����Ͽ� �������¸� ���´�), ����-���� ����(���ؽ� ����Ͽ� ���µ��ȿ� ���ڸ� ����), ������-�Һ��ڹ���(�����ڴ� ������� ���� �ڿ� mutexȮ�� �� ����, �Һ��ڴ� �������� ���� �ڿ� mutex�� ����) 
3.
*/
