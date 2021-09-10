#include <iostream>
#include <future>
#include <string>
#include <thread>

#include <condition_variable>
#include <mutex>
#include <exception>

#include <chrono>

#include <vector> 

/*1 for showing unefficiency of this code.
string txt=read("a.txt");//5ms
string resault=do_something_with_txt(txt);//5ms
do_other_computation();//5ms
//read function waits while files are read in hard disk.

//1 solution for eficiency by using thread we have learned.
void file_read(string* result){
	string txt=read("a.txt");//0ms thanks to thread
	//Now, CPU can move to main thread and execute do_other_computation
	*result=do_something_with_txt(txt);//5ms
}
int main(){
	string result;
	thread t(file_read, &result);
	do_other_computation();//5ms
	t.join();//do work by thread. CPU don't rest once.
}*/

/*2 common concept of std::promise & std::future
using std::string;

void worker(std::promise<string>* p){
	p->set_value("some data");//do work promise. it enter to future
}
int main(){
	std::promise<string> p;//get type that will be returned as template argument.
	std::future<string> data=p.get_future();//promise that will be get back string data
	std::thread t(worker, &p);
	data.wait();//wait before getting data.
	
	//return of wait() means data is ready to future.
	//if we do get() without wait, it's same to wait()
	std::cout<<"Received data : "<<data.get()<<std::endl;
	
	t.join();
}*/

/*2 implementing of promise-future pattern by condition variable & limit of this way(why we use future-promise).
std::condition_variable cv;
std::mutex m;
bool done=false;
std::string info;

void worker(){
	{//for call destructor of std::lock_guard()
		std::lock_guard<std::mutex> lk(m);
		info="some data";
		done=true;
	}
	cv.notify_all()//after work, notify to cv that is condition_variable
}

int main(){
	std::thread t(worker);
	std::unique_lock<std::mutex> lk(m);//Lock! (unique_lock can relock after unlock)
	cv.wait(lk, []{return done;});//wait until "done is true". wait untill j.join() handle worker function in critical section.
	lk.unlock();//Unlock! after returning od lk that is unique_lock
	
	std::cout<<"Received data : "<<info<<std::endl;//print. In this time, info is already returned because condition variable waited end of thread work in critical section.
	t.join();//thread!
	//but promise & future is more simple then this.
	//In addition, we can pass exception to future!
}*/

/*2 we can throw exception to future!
using std::string;
void worker(std::promise<string>* p){
	try{
		throw std::runtime_error("Some Error!");//3. throw exception!
	} catch(...){//4. and catch with putting exception value to p
		p->set_exception(std::current_exception());//pass current error by std::current_exception() to p by set_exception()
		//we have to pass ***exception_ptr*** to set_exception
		//not exception object! just only get exception_ptr. 
		//now, we get exception object's pointer at current_exception function that return information of catched exception, not exception object's pointer getting by catch.
		//we can also get exception by object passed by catch, but calling current_exception() is mush simple to use.
	}
}
int main(){
	std::promise<string> p;//set promise object
	std::future<string> data=p.get_future();//set future object getting p's content.
	std::thread t(worker, &p);//make thread to worker with p(promise object)
	
	data.wait();//1. wait untill future object get returned value.
	//4. p get value & data.wait() is returned!
	try{//we can handle exception like using try-catch after throwing exception object to future.
		data.get();//5. get data(promise object)
	} catch(const std::exception& e){//6. catch exception in data(promise object)
		std::cout<<"Exception : "<<e.what()<<std::endl;//6. print Some Error! 
	}
	t.join();//2. thread execute! 
}*/

/*2. wait_for that let future wait for a defined seconds.
void worker(std::promise<void>* p){
	std::this_thread::sleep_for(std::chrono::seconds(10));
	p->set_value();
}
int main(){
	std::promise<void> p;//In case void, it doesn't pass any object, but it can be used flag by set or not.
	std::future<void> data=p.get_future();
	std::thread t(worker, &p);
	
	while(true){//infinite loof until break
		std::future_status status=data.wait_for(std::chrono::seconds(1));//wait 1second.
		//std::future_status can get status of future object.
		
		//Let's check status of std::future_status that gets status of data(future<void> objext)
		if(status==std::future_status::timeout)//not ready
			std::cerr<<">";//erase buffer after print unlike std::cout(with std::endl)
		else if(status==std::future_status::ready)//promise gets future
			break;
	}
	t.join();
}*/

/*3 shared_future (In situation many thread need to get future object)
using std::thread;
void runner(std::shared_future<void>* start){
	start->get();//all threads wait before return. 
	std::cout<<"Start!"<<std::endl;//if p get value? print start! Let's go!
}
int main(){
	std::promise<void> p;
	std::shared_future<void> start=p.get_future();
	
	thread t1(runner, &start);
	thread t2(runner, &start);
	thread t3(runner, &start);
	thread t4(runner, &start);
	
	std::cerr<<"Ready...";
	std::this_thread::sleep_for(std::chrono::seconds(1));//it means ready
	std::cerr<<"Go!"<<std::endl;
	p.set_value();//p get value!
	
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	//make all thread and join but, not execute because of start->get().
	//By getting value to promise, we make compiler do work thread!
}*/

/*4 packaged_task
int some_task(int x){ return 10+x; }

int main(){
	std::packaged_task<int(int)> task(some_task);//make packaged_task object by some_task function. it's like promise object 
	std::future<int> start=task.get_future();//get task by int type
	std::thread t(std::move(task), 5);//make thread with perfect move by std::move function with 5 as argument. 
	//std::packaged_task can't be made by copy so we use std::move for perfect move 
	
	std::cout<<"Resault value : "<<start.get()<<std::endl;//wait or getting value
	t.join();//thread work!
}*/

/*5 std::async
int sum(const std::vector<int>& v, int start, int end){
	int total=0;
	for(int i=start; i<end; ++i)
		total+=v[i];
	return total;
}
int parallel_sum(const std::vector<int>& v){//for calculation by multi threads 
	std::future<int> lower_half_future=std::async(std::launch::async, sum, cref(v), 0, v.size()/2);//make promise object & return like promise.get() in other thread
	//std::async([&v]() { return sum(v, 0, v.size()/2);});
	
	int upper_half=sum(v, v.size()/2, v.size());//normal call of sum function in original thread
	return lower_half_future.get()+upper_half;
}
int main(){
	std::vector<int> v;
	
	v.reserve(1000);
	for(int i=0; i<1000; ++i)
		v.push_back(i+1);
		
	std::cout<<"sum of 1 to 1000 : "<<parallel_sum(v)<<std::endl;
}*/

//5 for showing necessity of std::async(multi threading)
int do_work(int x){
	std::this_thread::sleep_for(std::chrono::seconds(3));
	return x;
}
void do_work_parallel(){
	auto f1=std::async([](){do_work(3);});
	auto f2=std::async([](){do_work(3);});
	do_work(3);
	f1.get();
	f2.get();
}
void do_work_sequential(){
	do_work(3);
	do_work(3);
	do_work(3);
}
int main(){ do_work_parallel();}//why spend 9 seconds...?
//in commonly, parallel spend 3 seconds, and sequential spend 9 seconds.



//LIKE WAT3R 노래 개좋네 넘모 감각적인걸? June 15도 ㅈ되네 분위기 미쳤다. honestly ㅈ댐 . Monday Soup. Bornfire with Friends

/*
[0.	들어가기에 앞서]
-	이번 강좌에서는 멀티 쓰레딩의 강력함을 더 쉽게 활용할 수 있게 해주는 몇 가지 도구들을 살펴보자. 

[1.	동기(sunchronous)와 비동기(asynchronous) 실행]
1.	한 번에 하나씩 순차적으로 실행되는 작업을 동기적(synchronous)으로 실행된다고 한다. 한 작업이 끝날 때 까지 다음 작업으로 이동하지 않기 때문이다.
	하지만, read가 하드 디스크에서 데이터를 읽어오는 동안 CPU는 아무런 작업을 하지 않기에 그 시간에 CPU에게 do_other_computation과 같은 작업을 실행시키는 것이 더 효율적이고 바람직하다.
	 그렇기에 C++은 thread로 빼어 do_other_computaion을 하는 동안 read를 하도록 하여 기다리는 시간을 단축하였다.
	이처럼 프로그램의 실행이, 한 갈래가 아니라 여러 갈래로 갈라져서 동시에 진행되는 것을 비동기적(asynchronous) 실행이라고 부른다. 
2.	자바스크립트와 같은 언어들은 언어 차원에서 비동기적 실행을 지원하지만, C++의 경우 명시적으로 쓰레드를 생성해서 적절히 수행해야 했다.
	이를 돕기 위해 C++11 표준 라이브러리에는 매우 간단히 비동기적 실행을 할 수 있게 해주는 도구들을 제공하고 있다.
	
[2.	std::promise와 std::future]
1.	비동기적으로 실행한다==어떠한 데이터를 다른 쓰레드를 통해 처리해서 받아낸다. 즉, 미래에(future) 쓰레드T가 원하는 데이터를 돌려 주겠다라는 약속(promise)
2.	std::future<string> data=p.get_future();은 p->set_value("some data");와 같이 future객체에 데이터를 제공한 후에 대응되는 get함수를 호출하기 전까지 실제결과를 포함하고 있지 않다.
	get을 호출하면 자동으로 wait를 한 다음에 값을 받고 리턴하기에 get을 다시 호출해서는 안된다. get을 두번 호출하면 실제로 설정된 객체가 이동된다. 
	 promise는 생산자-소비자 패턴에서 마치 생산자(producer)의 역활을 수행하고, future은 소비자(consumer)의 역활을 수행하는 것과 비슷하다. 
	promise-future에서는 condition_variable을 이용한 promise-future패턴에서 불가능한 예외처리가 가능하다.
	이때, 오류는 무조건 promise객체에 set_exception멤버 변수로 전달해야 future객체에서 .get()으로 데이터를 받을 수 있다.
	catch로 전달된 예외 객체르 받아도 되지만, current_exception()을 호출하여 받는게 사용하는데에 더 편리하다.
	그렇기에 그냥 get을 호출했을때 실제로 future의 예외객체가 던지어져, try_catch문을 사용한 것 처럼 처리가 가능하다.
	 즉, 쓰레드에서 발생한 오류 객체 역시 편리하게 handling할 수 있다.
3.	 std::future_status객체로 future객체의 상태를 담을 수 있다. 담아진 상태는 std::future_status::timeout과 std::future_status::ready와의 비교연산을 진행할 수 있다.
	wait_for함수는 primise가 설정될 때 까지 기다리는 대신에 전달된 시간만큼 기다렸다가 바로 리턴해버린다. 리턴하는 값을 future의 상태를 나타내는 std::future_status 객체이다.
	std::future_status는 ready, timeout, deferred가 있는데, deferred는 나중에 다루도록 하자. 의미는 결과값을 게산한느 함수가 아직 실행되지 않았다는 것이다.
	(std::cerr은 출력과 동시에 버퍼를 지운다. 즉 cout의 경우 버퍼를 이용하기에 원하는 위치에서 정상적으로 실행되지 않을 가능성이 있지만, cerr의 경우 버퍼를 비우지 않더라도 정상적인 위치에서 실행된다.) 
	(쉽게말해 cerr은 어떤 상황이든 바로 출력됨_쓰레드라던가,,,) 

[3.	shared_future]
1.	앞서 future의 경우 한번만 get할 수 있다고 했는데, get을 여러번 호출하면 future 내부의 객체가 이동되기 때문이다. 하지만 종종 여러 개의 thread에서 future을 get해야하는 상황이 있다.
 	그럴 경우 shared_future을 사용한다. 
 	즉, 이걸로 많은 쓰레드들의 동작을 멈췄다 켰다 조절 가능.

[4.	packaged_task]
1.	C++에서는 위 promise-future패턴을 비동기적 함수(정확히는 Callable-함다함수, Funtor 포함)의 리턴값에 간단히 적용할 수 있는 packaged_task를 지원한다.
	packaged_task에 전달된 함수가 리턴할 때, 그 값을 promise에 set_value하고, 예외를 던졌다면 기존의 방식처럼 set_exception을 한다. 
2.	std::packaged_task<리턴타입(인자타입)>와 같이 템플릿 인자로 리턴타입과 인자 타입을 받는다.  
	얘는 task(some_task);처럼 수행할 함수 자체를 생성자의 인자로 받는다. 또한 복사생성이 되지 않기에 thread에 넣을 때 std::move로 완벽한 이동을 시켜야 한다.
	 이와같이 packaged_task를 사용한다면 쓰레드에 굳이 promise를 전달하지 않아도 그 자체가 promise처럼 움직이기에 알아서 함수의 리턴값을 처리해주어 매우 편리하다.
	즉, 함수의 리턴값을 promise로 사용할 때 유용. 따로 promise object를 안만들어도 알아서 만든것처럼 처리해줌.
	
[5.	std::async]
1.	앞서 promise나 packaged_task는 비동기적으로 실행하기 위해 쓰레드를 명시적으로 생성하고 실행해야 했다.  
	하지만 std::async에 어떤 함수를 전달하면, 아예 쓰레드를 만들어서 해당 함수를 비동기적으로 실행하고, 그 결과값을 future에 전달한다. 이런 미친 
2.	std::async함수는 인자로 받은 함수를 비동기적으로 실행한 후에, 해당 결과값을 보관할 future을 리턴하는데, 첫번째 인자로는 실행형태를 전달한다.	
	std::launch::async는 바로쓰레드를 생성하여 실행하는 반면,
	std::launch::deferred는 future의 get함수가 호출되었을 때 실핸한다.(새로운 쓰레드를 생성하지 않음)_즉, 당장 비동기적으로 실행할 필요가 없을 때. 
	 이를 이용하여 쉽게 멀티 쓰레딩으로 프로그래밍이 가능. promise와 future을 쓰레드안에서 알아서 처리하고 future객체로 반환함. 

[6.	정리]
-	한번 발생하는 이벤트에 대해서 promise-future패턴으로 간단하게 처리 가능. 
-	shared_future을 통해 여러 쓰레드를 한번에 관리 가능
-	packaged_task로 원하는 함수의 promise와 future패턴 생성 가능
-	async로 원하는 함수를 비동기적으로 실행 가능. 
*/ 
