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
	mov DWORD PTR b[rip], 1//a=b+1�� �ϴ� ���߿� b=1�� ����!! 
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
[0.	���� ����]
1.	C++ ��Ƽ �������� ���� �����Ǵ� �⺻ ����� ������, ���ؽ�, ���Ǻ����鿡 ���� ���� �� �����ϰ� ��Ʈ�� �� �� �ִ� ��Ҹ� �����̶� �Ѿ�� ����.
	(C++�� ������ ������ ������) 
	
[1. �޸𸮴� ��û ������.]
1.	�⺻������ CPU�� RAM�� ���������� �������ֱ⿡ �����͸� �о���µ��� �ð��� �� �ɸ���. intel i7-6700CPU�� ��� �ּ� 42����Ŭ�� �ɸ��µ�, CPU���� ���� �ѹ��� 1����Ŭ�̶�� ���� ���� 
	�޸𸮿��� ������ �� �� ���� ������ 42���� ��������ð��� ���غ��� ���̴�.

[2.	ĳ��]
1.	�̸� �����ϱ� ���� ������ CPUĨ �ȿ� ���׸��� �޸𸮷� CPU�� ���� �پ��־� �ӵ��� �Ź� ������. (�����ϴ� Core���� ĳ�ð� �� ŭ �����滧��) 
	ĳ�ÿ� �ִ� �����͸� �ٽ� ��û�ؼ� �ð��� �����ϴ� ���� Cache hit�̶�� �ϸ�, ĳ�ÿ� ���� �޸𸮸� ���� ���� ���� Cache miss��� �Ѵ�.
2.	CPU�� ��� ������ ���� ���������� �𸥴�. CPu���� Cache�� �۵��ϴ� ���� ������ �Ʒ��� ����� ������.
	-�޸𸮸� ������ �ϴ� ĳ�÷�
	-ĳ�ð� ������ Ư���� ��Ŀ� ���� ó��
	���⼭�� Ư���� ����� CPU���� �ٸ���, ��ǥ���� ���� ���� ������ ��(LRU-Least Recently Used) ĳ�ø� ������ �� �ڸ��� �� ĳ�ø� ����ϴ� ����� �ִ�.
	�� ����� ������ �ֱٿ� ������ �����͸� ���� �ݺ��Ͽ� �����ϸ� �ſ� �����ϴٴ� ���̴�.
3.	<case 1>
	for(int i=0; i<10000; i++)
		for(int j=0; j<10000; j++)
			s+=data[j];
	<case 2>
	for(int j=0; j<10000; j++)
		for(int i=0; i<10000; i++)
			s+=data[j];
	�� ������ �����ε�, �ι�° ����� �� ���� �۵��Ѵ�. ù��°�� 1KBĳ�ÿ��� j=256�� �ɶ� Cache miss�� �Ǵ� �ݸ鿡 �ι�°�� data[0]�� 10000�� �������� �ϹǷ�, ó�������� ������ ������ 9999���� Cache hit�� �Ǿ� ������ ������ ������ �� �ִ�. 
	
[3.	��ǻ�ʹ� ��� �������� ��Ű�� ��� ���� �ʴ´�.]
1.	a=b+1�κ��� ������ ä �����⵵ ���� b=1�� ���� ������ ���� ���̴�. foo�Լ� ���忡�� ���������� a�� 1, b�� 1�� ����־ ������ ������,
	���� �ٸ� �����尡 �־ a�� b�� ���� Ȯ������ ��, a�� 0�ε� b�� 1�� �� �ִٴ� ���̴�! �̴� ������ CPU�� �� ���� �� ��ɾ �����ϴ� ���� �ƴϱ� �����̴�.
2.	CPU ���������̴�(pipelining)
	���� CPU���� ��ɾ ������ �� fetch, decode, execute, write���� ���� �ܰ踦 ��ġ�� �Ǵµ�, fetch�� ������ ���� decode�� ��ٸ��� �ϴ� ���� ��ȿ�� ���̱⿡(������ ��ٸ����� ������ ��� ���ϱ⿡) 
	�����Ϸ��� �ִ��� CPU�� ������������ ȿ�������� Ȱ���� �� �ֵ��� ��ɾ ���ġ �Ѵ�.
	 �̶� ���� ������� �翬�� �޶����� �ȵǰ�����, ������ �ٸ� ��������� ������� �ʴ´ٴ� ���̴�. 
	//���� a, b=0
	a=1;//ĳ�ÿ� ���� 
	b=1;//ĳ�ÿ� ����
	b�� ĳ�ÿ� �ֱ⿡ a���� b�� ������ ó�� �����ϴ�. ���� CPU���� �� �ڵ尡 ����� ��, b=1�� a=1���� ���� ����� �� �ִ�.
	 ���� �ٸ� �����忡�� a�� 0�ε�, b�� 1�� ������ ������ �� �ִٴ� ���̴�!
	(p.s)
	�б�-�б� ���� ��ɾ RR(Read-Read)������� �ϴµ�, ����CPU������ RR��ɾ��� ���ġ�� �����ϱ⿡ ���� ��Ȳ�� �߻����� �ʴ´�.
	������ ARM�� ��� ���� ����ϹǷ� ���� ���� ��Ȳ�� �߻��� �� �ִ�.
	����� ���� CPU�� �����ϰ� ����-�б��� ���ġ�� �����������滧��

[4.	������ �Ͼ�� �ϴ°�?]
1.	C++�� ��� ��ü���� ���� ����(mofification order)�� ������ �� �ִ�. �̴� ��ü�� ���� �ǽð����� Ȯ�ΰ����� ���������� ���� �ִ� �Ҷ�, �ش簴ü�� ����ȭ�� ����� ���̴�.
	a=5->8->6->3
	T1�� ������ ��������: 5->3 
	T2�� ������ ��������: 8->6->3
	T3�� ������ ��������: 5->6->3
	��� ��������� ���� ������ �����Ѵ�.(T3�� 8->5������ ������ �Ұ���) 
	C++������ ������ ������ �� ��쿡 ��� �����忡�� ���� ��ü�� ���Ͽ� ������ ���� ������ ������ �� �ִ�. 
	�ٸ� ����, ���� �ð��� ���� a�� ���� �����ߴٰ� �ؼ� ����� ������ �Ǳ⿡ ���� ��� ��������� ������ ���� ������ �ʿ�� ���ٶ�� ���̴�.
	 ������ ���� ���� �ð��� �ٸ� ���� �����ص� �ȴٴ� ���� �������� ���� ������, CPUĳ�ð� �� �ھ�� �����ϱ� ������ �̸� ������ �� ����.
	��, ������ 1���� a=5�Ŀ� �ڽ��� ĳ�ÿ��� ����ϰ� �ٸ� �ھ �˸��� ������ ������3���� a�� Ȯ�� �� 5�� ��´ٴ� ������ ���ٴ� ���̴�.
2.	���� �Ź� ���� ����� ��, ��� ĳ�ÿ� ����ȭ�� ��ų �� �ְ�����, �� �۾��� �ð��� �ϳ� ��ƸԱ⿡ C++������ �ο췹�� ��� ���, �̸� �����ϰ� ������ �� �ִ� �������� �������� ������ �� �ִ�.

[5.	���ڼ�(atomicity)]
1.	�ռ� C++���� ��� ��������� ���� ������ �����ؾ߸� �ϴ� ��츦 ��� ������� �������� ����� �Ͽ���.
	�������� ������ �ƴ� ��쿣 ���� ������ ����ȭ ������� ó���ؾ� �Ѵ�. �׷��� ������ ���α׷��� ���ǵ��� ���� �ൿ(undefined behavior)�� �� �� �ִ�.
2.	������ �����̶�, CPU�� ��ɾ� 1���� ó���ϴ� ������� ,�߰��� �ٸ� �����尡 ����� ������ ���� ���� ������ ���Ѵ�. �� ������ �ߴ� Ȥ�� ���ߴٸ� �����ϱ⿡ �̸� ������(atomic)�̶�� �Ѵ�.
	C++���� �����ϴ� ������ ������� �ùٸ� ������ ���� ���ؽ��� �ʿ����� �ʱ⿡ �ӵ��� �� ������. 
3.	std::atomic<int> counter(0); ó�� ���ø� ���ڷ� Ÿ���� �����ϸ� �ȴ�. �̴� �츮�� ��� CPU���� ������ ��(x86) �����Ϸ��� �˱� ������ Ư������ ��ɾ ������ �� �ִ� ���̴�.
	CPU�� ���� ���� lock add�� ���� ����� ���� �������� �ڵ带 ������ �� ���� ��쵵 �ִµ�, �̴� atomic ��ü�� ������� ���� ���������� ������ �� �ִ����� Ȯ���ϴ� is_lock_free()�Լ��� ȣ���ϸ� �ȴ�.

[6.	memory_order]
1.	atomic��ü���� ��� ������ ���� �ÿ� ��� ������� �޸𸮿� �������� �����Ҽ� �ִ�.
	memory_order_relexed�� ���� ������ �����̴�. ��, �� ����� ����� ���, ������ �ٸ� �޸� ���ٵ�� ������ �ٲ� �����ϴ�.
	�ٽ� ���� ���� �ٸ� ������ relaxed�޸� ������ CPU������� ���ġ �� �� �ִ�(���� ������ �������� ����� �����ϴٸ�)
2.	relaxed�޸� ������ ����ϸ� ����ġ ���� ����� ���� �� ������, ��� �۾��� �ʰ� �ǵ� �ȵǵ� ��������� ���ุ �Ǹ� ��쿡 ����Ѵ�.(�ӵ��� �������⿡ CPU�� ���ġ��)
3.	memory_order_acquire�� memory_order_release
	memory_order_relaxed�� CPU�� �ʹ� ���� ������ �ο��ϱ⿡ ������ ���Ǵ� ��찡 �������̴�.
	 ���� ���ÿ� ���� �����-�Һ��� ���迡���� memory_order_relaxed�� ����� �� ����. 
	memory_order_release�� �ش� ��� ������ ��� �޸� ��ɵ��� �ش� ��� ���ķ� ���ġ �Ǵ� ���� �����Ѵ�. ���� ���� ������ acquire���� �д� ������� release������ ��� ��ɵ��� �ش� �����忡 ���� ���� �� �� �־�� �Ѵ�.
	memory_order_acquire�� �ش� ��� �ڿ����� ��� �޸� ��ɵ��� �ش� ��� ���� ���ġ �Ǵ� ���� �����Ѵ�.(release�� �ݴ�) 
	 ����ϱ� ���� �����ϸ� ������ relaxed�� �Ӽ��� release�Ҿ� �Ʒ��δ� chage�Ұ�, acquire��� �Ʒ����� change ����.
4.	memory_order_acq_rel�� acquire�� release�� ��� �����ϴ� ������, �б�� ���⸦ ��� �����ϴ� fetch_add�� ���� �Լ����� ���ȴ�.
	memory_order_seq_cst�� �޸� ����� ������ �ϰ���(sequential consistency)�� �������ش�. ��, �޸� ��� ���ġ�� ����, ��� �����忡�� ��� ������ ������ ���� ������ �� �ִ�, CPU�� �״�� �۵��ϴ� ����̴�. 
	 ������ ��Ƽ �ھ� �ý��ۿ��� memory_order_seq_cst�� �� ��� �����̴�. AMD�� x86 CPU�� ��� ���� sequential consistency�� ����Ǿ� ū ���̰� ������ ARM�迭�� CPU�� consumes a lot of CPU's synchronizing cost for vouching sequential consistancy. 
	��� �� �ʿ��� ��쿡�� memory_order_seq_cst�� ����ϱ�� ����(��� atomic��ü�� default setting �� memory_order_seq_cst�� �����滧��)
5.	���� memory_order�� ����, �б�, �а�����ϰ��� ���� ������ �ִµ�, ���� �����ϸ� default setting�� seq_cst���� ���� ����� ����Ͽ� ���α׷��� ȿ���� ���� �� �ִ�! 
*/ 
