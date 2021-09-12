#include <iostream>
#include <queue>
#include <vector>
#include <thread>
#include <condition_variable>
#include <exception>

#include <chrono>
#include <cstdio>

#include <future>
#include <mutex> 

//1
namespace ThreadPool{
class ThreadPool{
	//Num of Worker thread
	size_t num_threads_;
	//Save Worker thread by vector
	std::vector<std::thread> worker_threads_;
	//Save jobs that we have to handle
	std::queue<std::function<void()>> jobs_;
	//But queue is not safe in multi thread environment, so add mutex that will protect queue
	std::mutex m_job_q_;
	//For wait in producer-consumer model
	std::condition_variable cv_job_q_;
	//all Worker thread stop & for escape infinite loof
	bool stop_all;
	
	//Wait for add of work, do handle work.
	void WorkerThread();
	
	public:
		//Constructor
		ThreadPool(size_t num_threads);
		//Destructor
		~ThreadPool();
		//Add job to queue. privious version
		//void EnqueueJob(std::function<void()> job);
		//Developed EnqueueJob version
		template <class F, class... Args>
		std::future<typename std::result_of<F(Args...)>::type> EnqueueJob(F&& f, Args&&... args);
}; 
//Constructor
ThreadPool::ThreadPool(size_t num_threads):num_threads_(num_threads), stop_all(false){//with initializer list.
	worker_threads_.reserve(num_threads_);//reserve space for efficiency.
	for(size_t i=0; i<num_threads; ++i)
		worker_threads_.emplace_back([this](){ this->WorkerThread(); });//make threads to vector. In lambda function, we have to pass this for access to member function.
}
//wait for work, do work
void ThreadPool::WorkerThread(){
	while(true){
		std::unique_lock<std::mutex> lock(m_job_q_);//mutex lock
		cv_job_q_.wait(lock, [this](){ return !this->jobs_.empty() || stop_all; });//sleep until work add or stop_all activate
		if(stop_all&&this->jobs_.empty())//because of stop_all
			return;

	//because of work add not stop_all
	std::function<void()> job=std::move(jobs_.front());//get function
	jobs_.pop();//remove in queue
	lock.unlock();//mutex unlock
	
	job();//do job
	}//whie end
}
//add job to queue. privious version
//void ThreadPool::EnqueueJob(std::function<void()> job){
	//if(stop_all)//if stop all?
	//	throw std::runtime_error("ThreadPool is stopped");// then throw error
	//{//for calling of lock_guard's destructor
		//std::lock_guard<std::mutex> lock(m_job_q_);//lock!
		//jobs_.push(std::move(job));//add job to queue!
	//}
	//cv_job_q_.notify_one();//job is ready!
//}
//developed version. job add to queue that can handle return value.
template <class F, class... Args>
std::future<typename std::result_of<F(Args...)>::type> ThreadPool::EnqueueJob(F&& f, Args&&... args){
	if (stop_all)
		throw std::runtime_error("ThreadPool is stopped");
	
	using return_type=typename std::result_of<F(Args...)>::type;
	//previous version of job
	//std::packaged_task<return_type()> job(std::bind(f, args...));//2. job object is local variable!
	//new version of job for prevention runtime error because of local variable.
	auto job=std::make_shared<std::packaged_task<return_type()>> (std::bind(f, std::forward<Args>(args)...));//f is pointer of function. so it doesn't have nessecity of std::forward()
	
	std::future<return_type> job_result_future=job->get_future();
	{
		std::lock_guard<std::mutex> lock(m_job_q_);
		jobs_.push([job]() { (*job)(); });//3. job is local variable in lambda so it is broken in this time. how can we solve this problem?
	}//pass copy of shared_ptr to lambda function in returning
	cv_job_q_.notify_one();
	
	return job_result_future;
}
//destructor
ThreadPool::~ThreadPool(){
	stop_all=true;//set stop_all to true
	cv_job_q_.notify_all();//cv response please!
	
	for(auto& t:worker_threads_)
		t.join();//make all threads work for allowing "stop_all is true"
}
}//namespace ThreadPool

int work(int t, int id){
	printf("%d start \n", id);
	std::this_thread::sleep_for(std::chrono::seconds(t));
	printf("%d end after %ds\n",id, t);
	return t+id;//return!
}
int main(){
	ThreadPool::ThreadPool pool(3);
	
	std::vector<std::future<int>> futures;//vector for saving std::future
	for(int i=0; i<10; i++)
		futures.emplace_back(pool.EnqueueJob(work, i%3+1,i));//pool's EnqueueJob returns std::future type's object. pass return object to futures(vector)
	
	for(auto& f : futures)//range based for loop in chap.23
		printf("result : %d \n", f.get());//1. runtime error occur! Broken promise exception means future object is destoied before sel_value to promise.
	//we can solve this problem by 2 ways
	//Storing pasckaged_task to container or Storing packaged_task to shared_ptr
	//first way has problem packaged_task remain in containter when we don't use packaged_task.
	//second way is convenient because shared_ptr's destuctor remove object.
}



/*
[0. 들어가기에 앞서]
1.	쓰레드 풀에 할 일이 들어오면, 대기하고 있던 쓰레드들 중 하나가 이를 실행한다.
	구현은 queue에 추가하는 것인데, C++의 pop의 경우 원소를 제거하지만 리턴하지 않기에 front를 호출한다.
	큐를 이용하여 가장 먼저 들어온 작업을 먼저 처리할 것인데, 만약 최근에 추가한 작업요청을 처리해야할 경우 다른 자료구조를 이용하면 된다.

[1.	클래스 설계 하기]
1.	쓰레드들을 보관하는 벡터를 만들고, 편의상 쓰레드풀에서 돌아가는 쓰레드들을 Worker쓰레드라고 하자.
	사용자 들은 함수들을 쓰레드풀에 전달할 것인데, C++에서는 일반적인 타입의 함수 포인터를 저장할 수 있는 컨테이너가 없기에 우선 void로 만들자. 
2.	쓰레드 풀을 받는 함수의 리턴타임이 void고 인자를 받지 않는다 한 이유는 걍 람다로 인자가 들어간 함수를 전달할 수 있기 때문 쿠쿠루빙봉 
3.	메카니즘: 쓰레드풀을 생성하면 그 수 만큼 쓰레드를 만들어서 쓰레드 저장소(vector)에 저장. 작업이 EnqueueJob으로 작업 저장소(queue)에 들어가면 쓰레드가 처리. 

[2.	임의의 함수 받기]
1.	현재의 ThreadPool은 우리가 전달한 함수가 어떤 값을 리턴할 때를 잘 처리하지 못한다. 그 함수에 포인터로 리턴값을 저장할 변수를 전달하면 되지만,
	기존의 future처럼 그 값이 설정될 때 까지 기다릴 수 없다.
	 고로 아예 EnqueueJob함수가 임의의 현태의 함수를 받고, 그 함수의 리턴값을 보관하는 future을 리턴하는 꼴로 바꾸어보자. 
2.	std::result_of<F(Args...)> 으로 함수 F의 리턴값을 알 수있다. 고로 
	std::future<f의 리턴타입> EnqueueJob(F f, Args... args);인 것이다.
3.	void()꼴의 함수만 저장할 수 있는 컨테이너에 넣을수 있든 말든 그냥 lmabda사용해서
	jobs_.push([f, args...]() {f(args...);});를 시전해버리면 Worker쓰레드 안에서 바로 f(args...)를 싱행할 수 있다.
	 다만 그렇게되면 리턴값을 얻지 못하게 되니 비동기적으로 실행되는 함수의 리턴값을 쉽게 받아낼 수 있는 packaged_task를 이용해보자.
	using return_type=typename std::result_of<F(Args...)>::type; 편의상 정의 
	std::packaged_task<return_type()> job(std::bind(f, args...)); 
	 다만 여기서 주의해야하는 점은 packaged_task의 생성자는 함수만을 받기에 인자를 전달하기 위해서는 아예 job(args...)나 위처럼 std::bind(f, args...)로 호출해주면 된다.

[3.	완벽한 전달]
1.	EnqueueJob함수의 아쉬운 점은
	ThreadPool::EnqueueJob(F f, Args... args);에서 인자들의 복사본을 받는다는 것이다. 불필요한 복사를 막기 위해 완벽한 전달 패턴을 사용하자.
2.	우선 EnqueueJob 함수들의 인자들을 우측값 레퍼런스로 바꾸고 bind함수에 forward로 인자를 전달해주자. 
*/
