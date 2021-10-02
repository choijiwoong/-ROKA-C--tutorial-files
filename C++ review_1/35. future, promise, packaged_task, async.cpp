#include <iostream>
#include <future>
#include <string>
#include <thread>
#include <exception>
#include <chrono>
using std::string; 

/*wait_for future-promise pattern
void worker(std::promise<string>* p){
	std::this_thread::sleep_for(std::chrono::seconds(3));
	p->set_value("catcatdog");
}

int main(){
	std::promise<string> p;//make promise object
	
	std::future<string> data=p.get_future();//data will be get future
	std::thread t(worker, &p);//make thread;
	
	while(true){
			std::future_status status=data.wait_for(std::chrono::seconds(1));
			
			if(status==std::future_status::timeout)
				std::cerr<<">";
			else if(status==std::future_status::ready)
				break;
	}

	t.join();
}*/

using std::thread;
/*signal to many threads by shared_future(It can also be made by condition_variable but using future is more convenient
void runner(std::shared_future<void>* start){
	start->get();//wait before set value because start is future object
	std::cout<<"start!"<<std::endl;
}

int main(){
	std::promise<void> p;
	std::shared_future<void> start=p.get_future();
	
	thread t1(runner, &start);
	thread t2(runner, &start);
	thread t3(runner, &start);
	thread t4(runner, &start);
	
	std::cerr<<"ready...";
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cerr<<"Go!"<<std::endl;
	
	p.set_value();//p's value is set!
	
	t1.join();//Threads are already working!
	t2.join();
	t3.join();
	t4.join();
}*/

/*packaged_task for skip std::promise
int some_task(int x){ return 10+x; }
int main(){
	std::packaged_task<int(int)> task(some_task);//pass function with input&return type as template argument
	
	std::future<int> start=task.get_future();//get future
	std::thread t(std::move(task), 5);//make thread. packaged_task cannot be copied! so use std::move
	std::cout<<"result value: "<<start.get()<<std::endl;
	t.join();
} */

#include <vector>
//async for skip thread
int sum(const std::vector<int>& v, int start, int end){
	int total=0;
	for(int i=start; i<end; i++)
		total+=v[i];
	return total;
}

int parallel_sum(const std::vector<int>& v){
	std::future<int> lower_half_future=std::async(std::launch::async, sum, cref(v), 0, v.size()/2);//make thread, promise by itself, also join()
	//=std::async([&v]() { return sum(v, 0, v.size()/2); } );//by lambda
	int upper_half=sum(v, v.size()/2, v.size());
	
	return lower_half_future.get()+upper_half;
}

int main(){
	std::vector<int> v;
	v.reserve(1000);
	
	for(int i=0; i<1000; ++i)
		v.push_back(i+1);
		
	std::cout<<"sum of 1 to 1000: "<<parallel_sum(v)<<std::endl;
}


/*
1.	����(synchronous);���������� �ϳ����� �񵿱�(asynchronous);�������� ������ ���� ���� 
	�����带 ����Ͽ� �񵿱������� ���� �޾Ƴ��ڴ�; future�� ������T�� ���ϴ� �����͸� �����ְڴٴ� promise�̴�.
2.	condition_variable�� �̿��Ͽ� future, promise���� ������ ����������, �ξ� �������̸� �����ϰ�, ���� ������ �����ϴ�. 
3.	wait_for�� ����Ͽ� ��ٸ� �ð��� ������ �� �ִµ�, �̶� future_status�� ����Ͽ� �غ� �Ǿ������� Ȯ���� �� �ִ�. ���·δ� ready, timeout, deffered�� �ִ�.
4.	get�� �ϸ� future�� ��ü�� �̵��Ǳ� ������ �ѹ��� get�� �� �ִ�.
	shared_future�� ���Ͽ� ���� �����忡�� ��ü�� ����� �� �ִµ�, �̸� ���� �����带 ������ ���� �ִ�.
5.	packaged_task�� ���޵� �Լ��� ������ �� �� ���� promise�� set_value�ϰ� ���ܰ� �������� set_exception�� �Ѵ�. 
	promise�� �ʿ䰡 ����! ������ get_future�� �����ϴ� ��(like promise)�� future�� ������ �� �ִ�. 
6.	async�� ����ϸ� �����带 ���� ����� �� �ʿ䵵 ���� std::launch::async(�ٷξ������������), std::launch:deffered(get�Լ��� ȣ��Ǹ� ����_������ �ȸ���)���� ���� �����ϴ�.
 
*/
