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
[0. ���⿡ �ռ�]
1.	������ Ǯ�� �� ���� ������, ����ϰ� �ִ� ������� �� �ϳ��� �̸� �����Ѵ�.
	������ queue�� �߰��ϴ� ���ε�, C++�� pop�� ��� ���Ҹ� ���������� �������� �ʱ⿡ front�� ȣ���Ѵ�.
	ť�� �̿��Ͽ� ���� ���� ���� �۾��� ���� ó���� ���ε�, ���� �ֱٿ� �߰��� �۾���û�� ó���ؾ��� ��� �ٸ� �ڷᱸ���� �̿��ϸ� �ȴ�.

[1.	Ŭ���� ���� �ϱ�]
1.	��������� �����ϴ� ���͸� �����, ���ǻ� ������Ǯ���� ���ư��� ��������� Worker�������� ����.
	����� ���� �Լ����� ������Ǯ�� ������ ���ε�, C++������ �Ϲ����� Ÿ���� �Լ� �����͸� ������ �� �ִ� �����̳ʰ� ���⿡ �켱 void�� ������. 
*/
