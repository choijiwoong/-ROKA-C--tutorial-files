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
1.	Cache hit, Cache miss, ĳ�ð� �� ���� ó���ϴ� Ư���� ����� CPU���� �ٸ���. ex) Least Recently Used_LSU
2.	CPU pipelining; �� �۾��� ������ ���� ���� �۾��� �����ϴ� ������� ���ÿ� �������� �۾��� �����ϴ� �� like decode, execute, write
3.	�����Ϸ��� ��ɾ ���ġ�� �ϴ°� �ƴ϶� CPU�� ĳ�ÿ� �ִ� ���� ������ ���ġ�� ���� �ִ�.(RR(Read-Read) ����) 
4.	C++�� ��� ��ü�� ���� ����(modification order)�� ������ �� �ִ�. "��� ��������� ������ ���� ������ �ʿ�� ����."_����ȭ�ð��� �ɸ��⿡ ����
5.	atomicity(���ڼ�); CPU�� ��ɾ� 1���� ó���ϴ� �������, �߰��� �ٸ� �����尡 ����� ������ ���� ���� �����̴�.(���ؽ��� �ʿ����) 
6.	is_lock_free() �Լ��� atomic��ü�� ������� ���������� �����ɼ� �ִ����� Ȯ������.(lock�� �ʿ����� �ʴٴ� ��) 
7.	memory_order; memory_order_relexed(�����ο� ��ȥ), memory_order_acquire(�ڿ��� ���� ���ġ ����), memory_order_release(������ �Ʒ��� ���ġ ����) 
	memory_order_acq_rel(acquire & release�� ���ü����ϴ� fetch_add���� �Լ�), memory_order_seq_cst(sequential consistency ������ �ϰ����� ����), 
8.	memory_order_relexed�� �ʹ� �����ӱ⿡ �ַ� acquire�� release�� ����ϴµ�, �̴� ��ǥ������ producer-consumer���迡�� is_ready�� true�ε� �����Ͱ� �ε���� �ʴ� ��Ȳ�� �����ش�. 
	counter++�� counter.fetch_add(1, memory_order_seq_cst)�� ������ �����̴�. 
*/ 
