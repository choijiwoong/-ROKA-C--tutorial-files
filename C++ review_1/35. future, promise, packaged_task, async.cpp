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
1.	동기(synchronous);순차적으로 하나씩과 비동기(asynchronous);여러개로 나뉘어 동시 진행 
	쓰레드를 사용하여 비동기적으로 값을 받아내겠다; future에 쓰레드T가 원하는 데이터를 돌려주겠다는 promise이다.
2.	condition_variable을 이용하여 future, promise패턴 구현이 가능하지만, 훨씬 직관적이며 심플하고, 예외 전달이 가능하다. 
3.	wait_for을 사용하여 기다릴 시간을 설정할 수 있는데, 이때 future_status를 사용하여 준비가 되었는지를 확인할 수 있다. 상태로는 ready, timeout, deffered가 있다.
4.	get을 하면 future의 객체가 이동되기 때문에 한번만 get할 수 있다.
	shared_future을 통하여 여러 쓰레드에서 객체를 사용할 수 있는데, 이를 통해 쓰레드를 제어할 수도 있다.
5.	packaged_task에 전달된 함수가 리턴할 때 그 값을 promise에 set_value하고 예외가 던져지면 set_exception을 한다. 
	promise쓸 필요가 없다! 어차피 get_future로 리턴하는 값(like promise)을 future에 저장할 수 있다. 
6.	async를 사용하면 쓰레드를 따로 만들어 줄 필요도 없고 std::launch::async(바로쓰레드생성실행), std::launch:deffered(get함수가 호출되면 실행_쓰레드 안만듬)으로 조절 가능하다.
 
*/
