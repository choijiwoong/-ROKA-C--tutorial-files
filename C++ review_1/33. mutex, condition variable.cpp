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
1.	�������(Race condition); ���� �ٸ� ��������� ������ �ڿ��� ����Ҷ� 
2.	��Ƽ�������� ����� ���α׷��� ������ �ʾ��� ��� ������� �̳� ��ƴ�. ��� mutex(��ȣ ����_mutual exclusion)�� ����Ѵ�.
3.	�Ӱ� ����(critical section); �� �����常�� �����ϰ� ������ �� �ִ� �ڵ� �κ�
4.	�����(deadlock); unlock���ؼ� ������ ��ٸ�. ��� mutual exclusion�� ��� �� ������ ��ȯ�� �ؾ��Ѵ�. 
	�̶� unique_ptró�� lock_guard<std::mutex>�� mutex�� �Ҹ��ڸ� ó���� �� �ִ�. 
5.	������� ���ϱ� ���� � �����忡�� �켱������ �ְ� �ȴٸ�, �켱���� �����忡 �۾��� �򸮰� �ٸ� �����带 ������ �ʴ� ��� ����(starvation)�� �߻��� �� �ִ�.
	�켱������ try_lock���� ���ؽ��� ���¸� if�� �־� ó�� �����ϴ�. 
6.	������� ���Ϸ��� �ϳ��� �����忡�� �������� mutex����� �����ϰ�, Lock���� ������ ������ ȹ������. 
7.	������-�Һ��� ���Ͽ��� FIFO�� queue�� ����ߴ�. vector�� �������°� ù��° ���ҿ� ����Ǵµ� �̸� �����ϴ� �ӵ��� �����⿡.
8.	�����ִ��� ���÷� Ȯ���ϴ°ͺ��� ���������� ��ȣ�� ���� ����� ���� ȿ�����̴�. condition_variable
9.	lock_guard�� ��� ������ �ܿ� ���� lock�� �Ұ�������, unique_lock�� unlock�Ŀ� lock�� �����ϴٴ� �������ۿ� ����. �׳� cv->wait�� unique_lock�� ���ڷ� �޾Ƽ� �׸� �־���.
10.	cv->wait(lk, [&]{ return ����;});���� �� 
*/ 
