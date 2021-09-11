#include <iostream>
#include <queue>
#include <vector>
#include <thread>
#include <condition_variable>
#include <exception>

#include <chrono>
#include <cstdio>

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
		//Add job to queue
		void EnqueueJob(std::function<void()> job);
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
//add job to queue
void ThreadPool::EnqueueJob(std::function<void()> job){
	if(stop_all)//if stop all?
		throw std::runtime_error("ThreadPool is stopped");// then throw error
	{//for calling of lock_guard's destructor
		std::lock_guard<std::mutex> lock(m_job_q_);//lock!
		jobs_.push(std::move(job));//add job to queue!
	}
	cv_job_q_.notify_one();//job is ready!
}
//destructor
ThreadPool::~ThreadPool(){
	stop_all=true;//set stop_all to true
	cv_job_q_.notify_all();//cv response please!
	
	for(auto& t:worker_threads_)
		t.join();//make all threads work for allowing "stop_all is true"
}
}//namespace ThreadPool

void work(int t, int id){
	printf("%d start \n", id);
	std::this_thread::sleep_for(std::chrono::seconds(t));
	printf("%d end after %ds\n",id, t);
}
int main(){
	ThreadPool::ThreadPool pool(3);
	
	for(int i=0; i<10; i++)
		pool.EnqueueJob([i](){ work(i%3+1, i);});
}



/*
[0. 들어가기에 앞서]
1.	쓰레드 풀에 할 일이 들어오면, 대기하고 있던 쓰레드들 중 하나가 이를 실행한다.
	구현은 queue에 추가하는 것인데, C++의 pop의 경우 원소를 제거하지만 리턴하지 않기에 front를 호출한다.
	큐를 이용하여 가장 먼저 들어온 작업을 먼저 처리할 것인데, 만약 최근에 추가한 작업요청을 처리해야할 경우 다른 자료구조를 이용하면 된다.

[1.	클래스 설계 하기]
1.	쓰레드들을 보관하는 벡터를 만들고, 편의상 쓰레드풀에서 돌아가는 쓰레드들을 Worker쓰레드라고 하자.
	사용자 들은 함수들을 쓰레드풀에 전달할 것인데, C++에서는 일반적인 타입의 함수 포인터를 저장할 수 있는 컨테이너가 없기에 우선 void로 만들자. 
*/
